/*
 * nuancefx.h
 *
 *  Created on: Apr 21, 2012
 *      Author: igkiou
 */

#ifndef _NUANCEFX_H_
#define _NUANCEFX_H_

#include "CriAcquireAPI.h"
#include <math.h>

typedef enum {
	CAMERA_NAME = 0,
	CAMERA_SERIAL = 1,
	CAMERA_SENSOR = 2,
	CAMERA_MAXBITDEPTH = 3,
	CAMERA_SENSORSIZE = 4,
	CAMERA_DRIVERREVISION = 5,
	CAMERA_FIRMWAREREVISION = 6,
	CAMERA_EXPOSURE = 7,
	CAMERA_EXPOSURERANGE = 8,
	CAMERA_BINNING = 9,
	CAMERA_BITDEPTH = 10,
	CAMERA_IMAGESIZE = 11,
	CAMERA_GAINRANGE = 12,
	CAMERA_GAIN = 13,
	CAMERA_COOLERSTATUS = 14,
	CAMERA_TEMPERATURE = 15,
	CAMERA_SENSORSISE = 16,
	CAMERA_INVALID = - 1
} CAMERA_PROPERTY;

CRI_MSI_API cri_ErrorCode
cri_GetCameraBinning(cri_CameraHandle handle, cri_ECameraBinning* binning);

CRI_MSI_API cri_ErrorCode
cri_SetCameraBinning(cri_CameraHandle handle, cri_ECameraBinning binning);

CRI_MSI_API cri_ErrorCode
cri_GetCameraBitDepth(cri_CameraHandle handle, cri_ECameraBitDepth* depth);

CRI_MSI_API cri_ErrorCode
cri_SetCameraBitDepth(cri_CameraHandle handle, cri_ECameraBitDepth depth);

CRI_MSI_API cri_ErrorCode
cri_GetCameraImageSize(cri_CameraHandle handle, int* width, int* height);

CRI_MSI_API cri_ErrorCode
cri_GetCameraGainRange(cri_CameraHandle handle, int* lowRange, int* highRange);

CRI_MSI_API cri_ErrorCode
cri_GetCameraGain(cri_CameraHandle handle, cri_ECameraGain* gain);

CRI_MSI_API cri_ErrorCode
cri_SetCameraGain(cri_CameraHandle handle, cri_ECameraGain gain);

CRI_MSI_API cri_ErrorCode
cri_GetCameraExposureRangeMs(cri_CameraHandle handle, float* lowRange, \
							float* highRange);

CRI_MSI_API cri_ErrorCode
cri_GetCameraExposureMs(cri_CameraHandle handle, float* exposureMs);

CRI_MSI_API cri_ErrorCode
cri_SetCameraExposureMs(cri_CameraHandle handle, float exposureMs);

CRI_MSI_API cri_ErrorCode
cri_GetCameraCoolerEnabled(cri_CameraHandle handle, bool* enabled);

CRI_MSI_API cri_ErrorCode
cri_GetCameraTemperature(cri_CameraHandle handle, float* temperatureC);

CRI_MSI_API cri_ErrorCode
cri_GetCameraSensorSize(cri_CameraHandle handle, int* width, int* height);

CRI_MSI_API cri_ErrorCode
cri_GetCameraDescription(cri_CameraHandle handle, char* name, \
						char* serialNumber, char* sensor, \
						cri_ECameraBitDepth* maxBitDepth, int* sensorWidth, \
						int* sensorHeight, char* driverRevision, \
						char* firmwareRevision);
//
//  Offset settings.
//
//
//  Camera offset ranges can either be defined by a low to high range
//  (step size of 1) or varied.  The below range interfaces will only return
//  ranges as defined by the function name.
//
//  The function cri_GetCameraOffsetRange() will return low and high range
//  values if the range has a step size of 1.
//
//  The function cri_GetCameraOffsetSparseRange() will return a range with
//  values that do not necessarily have a step size of 1.
//
//  The error code cri_NoError can be used to determine if the range function
//  provides the values.  Otherwise the erorr code cri_DataUnavailable will be
//  returned.
//
CRI_MSI_API cri_ErrorCode
cri_GetCameraOffsetRange(cri_CameraHandle handle,
                         int* lowRange,
                         int* highRange);

CRI_MSI_API cri_ErrorCode
cri_GetNumberCameraOffsetSparseRange(cri_CameraHandle handle, int *rangeCount);

CRI_MSI_API cri_ErrorCode
cri_GetCameraOffsetSparseRange(cri_CameraHandle handle,
                               int range[],
                               int maxRanges);

CRI_MSI_API cri_ErrorCode
cri_GetCameraOffset(cri_CameraHandle handle, int* cameraOffset);

CRI_MSI_API cri_ErrorCode
cri_SetCameraOffset(cri_CameraHandle handle, int cameraOffset);


cri_CameraHandle m_CameraHandle = -1;
cri_FilterHandle m_FilterHandle = -1;

int m_CameraImageStreamCount = 0;

const int ALLOWED_STREAM_COUNT = 8;

cri_Int8Image m_SnapImage;
cri_Int8Image m_StreamImages[ALLOWED_STREAM_COUNT];
cri_Int8Image m_AcquireCube;

const int NUMBER_ACQUIRE_IMAGES = 11;
const int CUBE_ACQUIRE_FRAMES_TO_AVERAGE = 1;
const float DEFAULT_CUBE_ACQUIRE_EXPOSURE_MS = 100.0;


void StreamInt8Callback(cri_Int8Image image);
void SnapInt8Callback(cri_Int8Image image);
void AcquireCubeInt8Callback(cri_Int8Image images, cri_Int8Image planarImage, cri_FilterState filterStates[],
   float exposureTimesMs[],
   unsigned int curImage,
   unsigned int totalToAcquire,
   unsigned int framesToAverage);
void ErrorCallback(cri_ErrorCode errorCode);
bool OpenCamera();
bool OpenFilter();
void DisplayErrorMessage();
void DisplayCameraCharacteristics();
void DisplayFilterCharacteristics();
bool OpenDevices();
void ShutdownDevices();
void SetCameraBitDepthTo(cri_ECameraBitDepth depth);
void SetCameraBinningTo(cri_ECameraBinning binning);
void GetCameraImageSize(int * width, int * height);
void SetDisplayCameraSettings();
void WaitForCameraToBeReady();
void GetAutoExposeParameters(cri_AutoExposeParameters * parameters);
void AutoExposeForPlane();
void AutoExposeForCube();
void WaitForCubeAcquireToBeFinished();
void AcquireCube();


#endif /* _NUANCEFX_H_ */
