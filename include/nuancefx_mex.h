/*
 * nuancefx.h
 *
 *  Created on: Apr 21, 2012
 *      Author: igkiou
 */

#ifndef _NUANCEFX_MEX_H_
#define _NUANCEFX_MEX_H_

#include <math.h>
#include <string.h>

#include "CriAcquireAPI.h"
#include "mex.h"
#include "matrix.h"

namespace nuance {

typedef enum {
	CAMERA_NAME = 0,
	CAMERA_SERIAL = 1,
	CAMERA_DRIVERREVISION = 2,
	CAMERA_FIRMWAREREVISION = 3,
	CAMERA_SENSOR = 4,
	CAMERA_SENSORSIZE = 5,
	CAMERA_IMAGESIZE = 6,
	CAMERA_MAXBITDEPTH = 7,
	CAMERA_BITDEPTH = 8,
	CAMERA_GAINRANGE = 9,
	CAMERA_GAIN = 10,
	CAMERA_EXPOSURERANGE = 11,
	CAMERA_EXPOSURE = 12,
	CAMERA_BINNING = 13,
	CAMERA_OFFSETRANGE = 14,
	CAMERA_OFFSET = 15,
//	CAMERA_COOLERSTATUS,
//	CAMERA_TEMPERATURE,
//	CAMERA_ROI = 16,
	CAMERA_INVALID = -1
} CAMERA_PROPERTY;

typedef enum {
	FILTER_RANGE = 0,
	FILTER_WAVELENGTH = 1,
	FILTER_INVALID = -1
} FILTER_PROPERTY;

inline void setCameraProperty(const cri_CameraHandle handle, \
							const char* propertyName, \
							const mxArray* mxarr) {

	cri_ErrorCode errorCode;
	if(!strcasecmp(propertyName, "bitdepth")) {
		errorCode = cri_SetCameraBitDepth(handle, (cri_ECameraBitDepth) mxGetScalar(mxarr));
	} else if(!strcasecmp(propertyName, "gain")) {
		errorCode = cri_SetCameraGain(handle, (cri_ECameraGain) mxGetScalar(mxarr));
	} else if(!strcasecmp(propertyName, "exposure")) {
		errorCode = cri_SetCameraExposureMs(handle, (float) mxGetScalar(mxarr));
	} else if(!strcasecmp(propertyName, "binning")) {
		errorCode = cri_SetCameraBinning(handle, (cri_ECameraBinning) mxGetScalar(mxarr));
	} else if(!strcasecmp(propertyName, "offset")) {
		errorCode = cri_SetCameraOffset(handle, (int) mxGetScalar(mxarr));
	} else {
		mexErrMsgTxt("Unknown or unsupported camera property.");
	}
	if (errorCode == cri_NoError) {
		return;
	} else {
		handleErrorCode(errorCode);
	}
}

inline void handleErrorCode(const cri_ErrorCode errorCode) {

	switch(errorCode) {
		case cri_IllegalParameter:
		{
			mexErrMsgTxt("Illegal parameter.");
			return;
		}
		case cri_ParameterOutOfRangeError:
		{
			mexErrMsgTxt("Parameter out of range.");
			return;
		}
		case cri_IllegalDataFormat:
		{
			mexErrMsgTxt("Illegal data format.");
			return;
		}
		case cri_OperationUnavailableWhileCameraOpen:
		{
			mexErrMsgTxt("Operation unavailable while camera open.");
			return;
		}
		case cri_DataUnavailable:
		{
			mexErrMsgTxt("Data unavailable.");
			return;
		}
		case cri_CameraNotOpen:
		{
			mexErrMsgTxt("Camera not open.");
			return;
		}
		case cri_CameraDeviceNotAvailable:
		{
			mexErrMsgTxt("Camera device not available.");
			return;
		}
		case cri_IllegalCameraHandle:
		{
			mexErrMsgTxt("Illegal camera handle.");
			return;
		}
		case cri_CameraHandleNoLongerOpen:
		{
			mexErrMsgTxt("Camera handle no longer open.");
			return;
		}
		case cri_CameraAlreadyStreaming:
		{
			mexErrMsgTxt("Camera already streaming.");
			return;
		}
		case cri_CameraNotStreaming:
		{
			mexErrMsgTxt("Camera not streaming.");
			return;
		}
		case cri_CameraStreamError:
		{
			mexErrMsgTxt("Camera stream error.");
			return;
		}
		case cri_CameraBusy:
		{
			mexErrMsgTxt("Camera busy.");
			return;
		}
		case cri_InternalCameraError:
		{
			mexErrMsgTxt("Internal camera error.");
			return;
		}
		case cri_InternalCameraQueryError:
		{
			mexErrMsgTxt("Internal camera query error.");
			return;
		}
		case cri_FilterNotOpen:
		{
			mexErrMsgTxt("Filter not open.");
			return;
		}
		case cri_FilterDeviceNotAvailable:
		{
			mexErrMsgTxt("Filter device not available.");
			return;
		}
		case cri_IllegalFilterHandle:
		{
			mexErrMsgTxt("Illegal filter handle.");
			return;
		}
		case cri_FilterHandleNoLongerOpen:
		{
			mexErrMsgTxt("Filter handle no longer open.");
			return;
		}
		case cri_InternalFilterError:
		{
			mexErrMsgTxt("Internal filter error.");
			return;
		}
		case cri_InternalAcquireError:
		{
			mexErrMsgTxt("Internal acquire error.");
			return;
		}
		case cri_TransmissionError:
		{
			mexErrMsgTxt("Transmission error.");
			return;
		}
	}
}

CRI_MSI_API cri_ErrorCode
cri_GetCameraBinning(cri_CameraHandle handle, cri_ECameraBinning* binning);

CRI_MSI_API cri_ErrorCode
cri_GetCameraBitDepth(cri_CameraHandle handle, cri_ECameraBitDepth* depth);


CRI_MSI_API cri_ErrorCode
cri_GetCurrentCameraSettings(cri_CameraHandle handle, int* width, int* height,
					cri_ECameraBitDepth* bitDepth, cri_ECameraBinning* binning);

CRI_MSI_API cri_ErrorCode
cri_GetCameraDescription(cri_CameraHandle handle, char* name, char* serialNumber,
						char* sensor, cri_ECameraBitDepth* maxBitDepth,
						int* sensorWidth, int* sensorHeight,
						char* driverRevision, char* firmwareRevision);


CRI_MSI_API cri_ErrorCode
cri_GetCameraImageSize(cri_CameraHandle handle, int* width, int* height);

CRI_MSI_API cri_ErrorCode
cri_GetCameraGainRange(cri_CameraHandle handle, int* lowRange, int* highRange);

CRI_MSI_API cri_ErrorCode
cri_GetCameraGain(cri_CameraHandle handle, cri_ECameraGain* gain);



CRI_MSI_API cri_ErrorCode
cri_GetCameraExposureRangeMs(cri_CameraHandle handle, float* lowRange, \
							float* highRange);

CRI_MSI_API cri_ErrorCode
cri_GetCameraExposureMs(cri_CameraHandle handle, float* exposureMs);

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
cri_GetCameraOffset(cri_CameraHandle handle, int* cameraOffset);

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

}	/* namespace nuance */

#endif /* _NUANCEFX_MEX_H_ */
