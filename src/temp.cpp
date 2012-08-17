/*
 * temp.cpp
 *
 *  Created on: Aug 16, 2012
 *      Author: igkiou
 */

/*** INCLUDE FILES ***/

#include "nuancefx_mex.h"

#include <iostream>
#include <cstring>

/*** CLASSES ***/

//-----------------------------------------------------------------------------

void SnapInt8Callback(cri_Int8Image image)
{
   //
   //  Tell the world what happened.
   //
   std::cout << "CRI Camera SnapInt8Callback" << std::endl;

   //
   //  The image parameter is valid during and after the callback.
   //  Manipulate as necessary.
   //

   //
   //  Flip the image X and Y.
   //
   cri_FlipInt8Image(image, &image, cri_FlipAxisX | cri_FlipAxisY);
}

//-----------------------------------------------------------------------------

void AcquireCubeInt8Callback(
   cri_Int8Image images,
   cri_Int8Image planarImage,
   cri_FilterState filterStates[],
   float exposureTimesMs[],
   unsigned int curImage,
   unsigned int totalToAcquire,
   unsigned int framesToAverage)
{
   //
   //  Tell the world what happened.
   //
   std::cout << "AcquireCubeInt8Callback Image #"
             << curImage
             << " out of "
             << totalToAcquire
             << " images."
             << "  Wavelength = "
             << images.wavelengths[curImage]
             << std::endl;

   //
   //  The images parameter is valid during and after the callback.
   //  Manipulate as necessary.
   //
   //  The planarImage parameter is valid ONLY during the callback.
   //  Allocate and copy if caller wishes to own their private copy.
   //
   //  Note:  The images format is interleaved wih each acquired image.
   //         The parameter planarImage is provided for convenience.  The
   //         contents of planarImage is the same as the interleaved contents
   //         within images.
   //
};

//-----------------------------------------------------------------------------

void ErrorCallback(cri_ErrorCode errorCode)
{
   std::cout << "ERROR Callback" << std::endl;
};

//-----------------------------------------------------------------------------

void DisplayErrorMessage()
{
   cri_ErrorCode errorCode;

   char description[cri_MAX_STRING_LENGTH];

   cri_GetLastError(&errorCode, description);

   std::cout << "CRi Error: " << description << std::endl;
   std::cout << "CRi Error Code: " << errorCode << std::endl;
};


//-----------------------------------------------------------------------------

void GetAutoExposeParameters(cri_AutoExposeParameters * parameters)
{
   //
   //  Get Camera ROI.
   //
   int originX;
   int originY;
   int width;
   int height;

   cri_ErrorCode errorCode = cri_GetCameraROI(
      m_CameraHandle,
      &originX,
      &originY,
      &width,
      &height);

   if (errorCode != cri_NoError){
      DisplayErrorMessage();
      return;
   };

   //
   //  Get the filter exposure range.
   //
   float lowRange;
   float highRange;

   errorCode = cri_GetCameraExposureRangeMs(
      m_CameraHandle,
      &lowRange,
      &highRange);

   if (errorCode != cri_NoError){
      DisplayErrorMessage();
      return;
   };

   //
   //  Ask for the best exposure settings.
   //
   parameters->rule = cri_AutoExposeRuleBrightest;

   parameters->targetRatioFullScale = 1.0;

   parameters->minExposureMs = lowRange;
   parameters->maxExposureMs = highRange;

   parameters->roiOriginX = originX;
   parameters->roiOriginY = originY;
   parameters->roiWidth = width;
   parameters->roiHeight = height;

   parameters->minAcceptableRatioFullScale = 0.0;
   parameters->maxAcceptableRatioFullScale = 0.0;
};

//-----------------------------------------------------------------------------

void AutoExposeForPlane()
{
   cri_AutoExposeParameters parameters;
   GetAutoExposeParameters(&parameters);

   float exposureTimeMS;

   cri_ErrorCode errorCode = cri_AutoExposePlane(
      m_CameraHandle,
      m_FilterHandle,
      parameters,
      &exposureTimeMS);

   if (errorCode != cri_NoError){
      DisplayErrorMessage();
      return;
   };

   //
   //  Apply auto exposure.
   //
   errorCode = cri_SetCameraExposureMs(
      m_CameraHandle,
      exposureTimeMS);

   if (errorCode != cri_NoError){
      DisplayErrorMessage();
      return;
   };
};

//-----------------------------------------------------------------------------

void AutoExposeForCube()
{
   cri_AutoExposeParameters parameters;
   GetAutoExposeParameters(&parameters);

   //
   //  Find the best single exposure time for the entire cube at the current
   //  wavelength.
   //
   cri_FilterState filterState;
   filterState.wavelength = 0.0;
   filterState.reserved[0] = 0.0;
   filterState.reserved[1] = 0.0;

   cri_ErrorCode errorCode = cri_GetFilterState(m_FilterHandle, &filterState);

   if (errorCode != cri_NoError){
      DisplayErrorMessage();
      return;
   };

   cri_FilterState filterStates[NUMBER_ACQUIRE_IMAGES];

   for (int idx = 0; idx < NUMBER_ACQUIRE_IMAGES; ++idx){
      filterStates[idx] = filterState;
   };

   float exposureTimesMS[NUMBER_ACQUIRE_IMAGES];

   for (int idx = 0; idx < NUMBER_ACQUIRE_IMAGES; ++idx){
      exposureTimesMS[idx] = 0.0;
   };

   errorCode = cri_AutoExposeCube(
      m_CameraHandle,
      m_FilterHandle,
      parameters,
      filterStates,
      exposureTimesMS,
      NUMBER_ACQUIRE_IMAGES,
      true);

   if (errorCode != cri_NoError){
      DisplayErrorMessage();
      return;
   };

   //
   //  Apply auto exposure.
   //
   float exposureTimeMS = exposureTimesMS[0];

   errorCode = cri_SetCameraExposureMs(m_CameraHandle, exposureTimeMS);

   if (errorCode != cri_NoError){
      DisplayErrorMessage();
      return;
   };
};

//-----------------------------------------------------------------------------

void WaitForCubeAcquireToBeFinished()
{
   bool isAcquiring = true;
   cri_ErrorCode errorCode = cri_NoError;

   while ((isAcquiring && errorCode == cri_NoError) ||
          errorCode == cri_CameraBusy)
   {
      Sleep();

      errorCode = cri_IsCameraAcquiring(m_CameraHandle, &isAcquiring);
   }
};

//-----------------------------------------------------------------------------

void AcquireCube()
{
   int width;
   int height;

   cri_ErrorCode errorCode = cri_GetCameraImageSize(
      m_CameraHandle,
      &width,
      &height);

   if (errorCode != cri_NoError){
      DisplayErrorMessage();
      return;
   };

   m_AcquireCube.width = width;
   m_AcquireCube.height = height;

   m_AcquireCube.image =
      new unsigned char[width * height * NUMBER_ACQUIRE_IMAGES];

   m_AcquireCube.numberOfChannels = NUMBER_ACQUIRE_IMAGES;

   m_AcquireCube.wavelengths = new float[NUMBER_ACQUIRE_IMAGES];

   float lowWavelengthRange;
   float highWavelengthRange;
   float minWavelengthStepSize;

   errorCode = cri_GetFilterRangeAndStepSize(
      m_FilterHandle,
      &lowWavelengthRange,
      &highWavelengthRange,
      &minWavelengthStepSize);

   if (errorCode != cri_NoError){
      DisplayErrorMessage();
      return;
   }

   //
   //  Setup the filter states and exposures for cube acquire.
   //
   cri_FilterState filterStates[NUMBER_ACQUIRE_IMAGES];
   float exposureTimesMs[NUMBER_ACQUIRE_IMAGES];

   float step =
      (highWavelengthRange - lowWavelengthRange) / NUMBER_ACQUIRE_IMAGES;

   float wavelength = lowWavelengthRange;

   for (int idx = 0; idx < NUMBER_ACQUIRE_IMAGES; ++idx, wavelength+=step)
   {
      filterStates[idx].wavelength = wavelength;

      exposureTimesMs[idx] = DEFAULT_CUBE_ACQUIRE_EXPOSURE_MS;
   }

   //
   //  Acquire cube.
   //
   errorCode= cri_AcquireInt8Cube(
      m_CameraHandle,
      m_FilterHandle,
      m_AcquireCube,
      filterStates,
      exposureTimesMs,
      NUMBER_ACQUIRE_IMAGES,
      CUBE_ACQUIRE_FRAMES_TO_AVERAGE,
      false,
      AcquireCubeInt8Callback,
      ErrorCallback);

   if (errorCode != cri_NoError){
      DisplayErrorMessage();
   };
};

//-----------------------------------------------------------------------------
