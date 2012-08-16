/*** INCLUDE FILES ***/

#include "nuancefx_mex.h"

#include <iostream>
#include <cstring>

/*** CLASSES ***/

//-----------------------------------------------------------------------------

void StreamInt8Callback(cri_Int8Image image)
{
   //
   //  Tell the world what happened.
   //
   std::cout << "CRI Camera StreamInt8Callback" << std::endl;

   //
   //  The image parameter is valid only during the callback.
   //
   if (m_CameraImageStreamCount < ALLOWED_STREAM_COUNT)
   {
      //
      //  Allocate and copy.
      //
      m_StreamImages[m_CameraImageStreamCount].width = image.width;
      m_StreamImages[m_CameraImageStreamCount].height = image.height;
      m_StreamImages[m_CameraImageStreamCount].numberOfChannels = 1;
      m_StreamImages[m_CameraImageStreamCount].wavelengths = NULL;

      m_StreamImages[m_CameraImageStreamCount].image =
         new unsigned char[image.width * image.height];

      memcpy(
         m_StreamImages[m_CameraImageStreamCount].image,
         image.image,
         image.width * image.height * sizeof(unsigned char));

      m_CameraImageStreamCount++;
   }
}

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

bool queryCamera() {
	int numberAvailableCameras = cri_GetNumberAvailableCameras();
	return (numberAvailableCameras > 0);
	   //
	   //  Allocate camera id list and query for camera ids.
	   //
	   int * cameraIds = new int[numberAvailableCameras];

	   int numberIdCount = cri_FindAvailableCameras(
	      cameraIds,
	      numberAvailableCameras);

	   if (numberIdCount > 0){
	      //
	      //  Open the first camera id.
	      //
	      cri_ErrorCode errorCode = cri_OpenCamera(cameraIds[0], &m_CameraHandle);

	      if (errorCode != cri_NoError)
	         std::cout << "Error Opening Camera" << std::endl;
	   }

	   if (m_CameraHandle == -1)
	      std::cout << "No Camera Devices Available" << std::endl;

	   delete [] cameraIds;

	   return (m_CameraHandle != -1);

}

bool OpenCamera()
{
   //
   //  Ask API for available cameras.
   //
   int numberAvailableCameras = cri_GetNumberAvailableCameras();

   //
   //  Allocate camera id list and query for camera ids.
   //
   int * cameraIds = new int[numberAvailableCameras];

   int numberIdCount = cri_FindAvailableCameras(
      cameraIds,
      numberAvailableCameras);

   if (numberIdCount > 0){
      //
      //  Open the first camera id.
      //
      cri_ErrorCode errorCode = cri_OpenCamera(cameraIds[0], &m_CameraHandle);

      if (errorCode != cri_NoError)
         std::cout << "Error Opening Camera" << std::endl;
   }

   if (m_CameraHandle == -1)
      std::cout << "No Camera Devices Available" << std::endl;

   delete [] cameraIds;

   return (m_CameraHandle != -1);
};

//-----------------------------------------------------------------------------

bool OpenFilter()
{
   //
   //  Ask API for available filters.
   //
   int numberAvailableFilters = cri_GetNumberAvailableFilters();

   //
   //  Allocate filter id list and query for filter ids.
   //
   int * filterIds = new int[numberAvailableFilters];

   int numberIdCount = cri_FindAvailableFilters(
      filterIds,
      numberAvailableFilters);

   if (numberIdCount > 0){
      //
      //  Open the first filter id.
      //
      cri_OpenFilter(filterIds[0], &m_FilterHandle);
   }

   delete [] filterIds;

   if (m_FilterHandle == -1)
      std::cout << "No Filter Devices Available" << std::endl;

   return (m_FilterHandle != -1);
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

void DisplayCameraCharacteristics()
{
   char cName[cri_MAX_STRING_LENGTH];
   char cSerialNumber[cri_MAX_STRING_LENGTH];
   char cSensor[cri_MAX_STRING_LENGTH];

   cri_ECameraBitDepth maxBitDepth;

   int sensorWidth = 0;
   int sensorHeight = 0;

   char cDriverRevision[cri_MAX_STRING_LENGTH];
   char cFirmwareRevision[cri_MAX_STRING_LENGTH];

   cri_ErrorCode errorCode = cri_GetCameraDescription(
      m_CameraHandle,
      cName,
      cSerialNumber,
      cSensor,
      &maxBitDepth,
      &sensorWidth,
      &sensorHeight,
      cDriverRevision,
      cFirmwareRevision);

   if (errorCode != cri_NoError)
   {
      DisplayErrorMessage();
      return;
   };

   std::cout << "Camera Information For Handle #"
             << m_CameraHandle
             << std::endl;

   std::cout << "Name : " << cName << std::endl;
   std::cout << "Serial Number : " << cSerialNumber << std::endl;
   std::cout << "Sensor : " << cSensor << std::endl;
   std::cout << "Driver : " << cDriverRevision << std::endl;
   std::cout << "Firmware : " << cFirmwareRevision << std::endl;

   std::cout << "Max Bit Depth : " << maxBitDepth << std::endl;
   std::cout << "Sensor Width : " << sensorWidth << std::endl;
   std::cout << "Sensor Height : " << sensorHeight << std::endl;

   std::cout << std::endl;
};

//-----------------------------------------------------------------------------

void DisplayFilterCharacteristics()
{
   int serialNumber = 0;

   float lowWavelengthRange = 0.0F;
   float highWavelengthRange = 0.0F;

   int waveplateStages = 0;
   int firmwareRevision = 0;

   cri_ErrorCode errorCode = cri_GetFilterDescription(
      m_FilterHandle,
      &serialNumber, 
      &lowWavelengthRange,
      &highWavelengthRange,
      &waveplateStages, 
      &firmwareRevision);

   if (errorCode != cri_NoError)
   {
      DisplayErrorMessage();
      return;
   };

   std::cout << "Filter Information For Handle #"
             << m_FilterHandle
             << std::endl;

   std::cout << "Filter Serial Number : " << serialNumber << std::endl;

   std::cout << "Filter Low Wavelength Range : "
             << lowWavelengthRange
             << std::endl;

   std::cout << "Filter High Wavelength Range : "
             << highWavelengthRange
             << std::endl;

   std::cout << "Filter Waveplate Stages : "
             << waveplateStages
             << std::endl;

   std::cout << "Firmware Revision : " << firmwareRevision << std::endl;

   std::cout << std::endl;
};

//-----------------------------------------------------------------------------

bool OpenDevices()
{
   if (!OpenCamera()){
      return false;
   };

   DisplayCameraCharacteristics();

   if (!OpenFilter()){
      return false;
   };

   DisplayFilterCharacteristics();

   return true;
};

//-----------------------------------------------------------------------------

void ShutdownDevices()
{
   if (m_CameraHandle != -1)
      cri_CloseCamera(&m_CameraHandle);

   if (m_FilterHandle != -1)
      cri_CloseFilter(&m_FilterHandle);
};

//-----------------------------------------------------------------------------

void SetCameraBitDepthTo(cri_ECameraBitDepth depth)
{
   if (m_CameraHandle != -1){
      cri_ErrorCode errorCode = cri_SetCameraBitDepth(m_CameraHandle, depth);

      if (errorCode != cri_NoError){
         DisplayErrorMessage();
      };
   };
};

//-----------------------------------------------------------------------------

void SetCameraBinningTo(cri_ECameraBinning binning)
{
   if (m_CameraHandle != -1){
      cri_ErrorCode errorCode = cri_SetCameraBinning(m_CameraHandle, binning);

      if (errorCode != cri_NoError){
         DisplayErrorMessage();
      };
   };
};

//-----------------------------------------------------------------------------

void GetCameraImageSize(int * width, int * height)
{
   cri_ErrorCode errorCode = cri_GetCameraImageSize(
      m_CameraHandle,
      width,
      height);

   if (errorCode != cri_NoError){
      DisplayErrorMessage();
   };
};

//-----------------------------------------------------------------------------

void SetDisplayCameraSettings()
{
   if (m_CameraHandle != -1){
      int width;
      int height;

      cri_ECameraBitDepth bitDepth;
      cri_ECameraBinning binning;

      cri_ErrorCode errorCode = cri_GetCurrentCameraSettings(
         m_CameraHandle,
         &width,
         &height,
         &bitDepth,
         &binning);

      std::cout << "Camera Width : " << width << std::endl;
      std::cout << "Camera Height : " << height << std::endl;

      std::cout << "Camera Bit Depth : " << bitDepth << std::endl;
      std::cout << "Camera Binning : " << binning << std::endl;
   };
};

//-----------------------------------------------------------------------------

void Sleep()
{
   for (long i=0; i < 50000000; i++);
};

//-----------------------------------------------------------------------------

void WaitForCameraToBeReady()
{
   bool ready = false;
   cri_ErrorCode errorCode = cri_NoError;

   while (!ready && errorCode == cri_NoError)
   {
      Sleep();

      errorCode = cri_CameraReady(m_CameraHandle, &ready);
   }
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
