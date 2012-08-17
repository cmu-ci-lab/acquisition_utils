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

#define ERROR_ID "MATLAB:nuancefx_mex"

namespace nuance {

typedef enum {
	CAMERA_NAME = 0,
	CAMERA_SERIAL = 1,
	CAMERA_DRIVER = 2,
	CAMERA_FIRMWARE = 3,
	CAMERA_SENSOR = 4,
	CAMERA_SENSORSIZE = 5,
	CAMERA_IMAGESIZE = 6,
	CAMERA_MAXBITDEPTH = 7,
	CAMERA_BITDEPTH = 8,
//	CAMERA_GAINRANGE = 9,
	CAMERA_GAIN = 9,
	CAMERA_EXPOSURERANGE = 10,
	CAMERA_EXPOSURE = 11,
	CAMERA_BINNING = 12,
	CAMERA_OFFSETRANGE = 13,
	CAMERA_OFFSET = 14,
	CAMERA_PROPERTY_LENGTH = 15,
	CAMERA_PROPERTY_INVALID = -1
} CAMERA_PROPERTY;

typedef enum {
	CAMERA_READY = 0,
	CAMERA_BUSY = 1,
	CAMERA_STATUS_LENGTH = 2,
	CAMERA_STATUS_INVALID = -1
} CAMERA_STATUS;

typedef enum {
	FILTER_SERIAL = 0,
	FILTER_FIRMWARE = 1,
	FILTER_RANGE = 2,
	FILTER_STEPSIZE = 3,
	FILTER_WAVELENGTH = 4,
	FILTER_PROPERTY_LENGTH = 5,
	FILTER_PROPERTY_INVALID = -1
} FILTER_PROPERTY;

typedef enum {
	FILTER_READY = 0,
	FILTER_BUSY = 1,
	FILTER_STATUS_LENGTH = 2,
	FILTER_STATUS_INVALID = -1
} FILTER_STATUS;

inline void handleErrorCode(const cri_ErrorCode errorCode) {

	switch(errorCode) {
		case cri_IllegalParameter:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Illegal parameter.");
			return;
		}
		case cri_ParameterOutOfRangeError:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Parameter out of range.");
			return;
		}
		case cri_IllegalDataFormat:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Illegal data format.");
			return;
		}
		case cri_OperationUnavailableWhileCameraOpen:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Operation unavailable while camera open.");
			return;
		}
		case cri_DataUnavailable:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Data unavailable.");
			return;
		}
		case cri_CameraNotOpen:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Camera not open.");
			return;
		}
		case cri_CameraDeviceNotAvailable:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Camera device not available.");
			return;
		}
		case cri_IllegalCameraHandle:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Illegal camera handle.");
			return;
		}
		case cri_CameraHandleNoLongerOpen:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Camera handle no longer open.");
			return;
		}
		case cri_CameraAlreadyStreaming:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Camera already streaming.");
			return;
		}
		case cri_CameraNotStreaming:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Camera not streaming.");
			return;
		}
		case cri_CameraStreamError:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Camera stream error.");
			return;
		}
		case cri_CameraBusy:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Camera busy.");
			return;
		}
		case cri_InternalCameraError:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Internal camera error.");
			return;
		}
		case cri_InternalCameraQueryError:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Internal camera query error.");
			return;
		}
		case cri_FilterNotOpen:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Filter not open.");
			return;
		}
		case cri_FilterDeviceNotAvailable:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Filter device not available.");
			return;
		}
		case cri_IllegalFilterHandle:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Illegal filter handle.");
			return;
		}
		case cri_FilterHandleNoLongerOpen:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Filter handle no longer open.");
			return;
		}
		case cri_InternalFilterError:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Internal filter error.");
			return;
		}
		case cri_InternalAcquireError:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Internal acquire error.");
			return;
		}
		case cri_TransmissionError:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Transmission error.");
			return;
		}
	}
}

inline void cameraPropertyToString(const CAMERA_PROPERTY property, \
								char *propertyName) {

	switch (property) {
		case CAMERA_NAME: { strcpy(propertyName, "name"); return; }
		case CAMERA_SERIAL: { strcpy(propertyName, "serial"); return; }
		case CAMERA_DRIVER: { strcpy(propertyName, "driver"); return; }
		case CAMERA_FIRMWARE: { strcpy(propertyName, "firmware"); return; }
		case CAMERA_SENSOR: { strcpy(propertyName, "sensor"); return; }
		case CAMERA_SENSORSIZE: { strcpy(propertyName, "sensorsize"); return; }
		case CAMERA_IMAGESIZE: { strcpy(propertyName, "imagesize"); return; }
		case CAMERA_MAXBITDEPTH: { strcpy(propertyName, "maxbitdepth"); return; }
		case CAMERA_BITDEPTH: { strcpy(propertyName, "bitdepth"); return; }
//		case CAMERA_GAINRANGE: { strcpy(propertyName, "gainrange"); return; }
		case CAMERA_GAIN: { strcpy(propertyName, "gain"); return; }
		case CAMERA_EXPOSURERANGE: { strcpy(propertyName, "exposurerange"); return; }
		case CAMERA_EXPOSURE: { strcpy(propertyName, "exposure"); return; }
		case CAMERA_BINNING: { strcpy(propertyName, "binning"); return; }
		case CAMERA_OFFSETRANGE: { strcpy(propertyName, "offsetrange"); return; }
		case CAMERA_OFFSET: { strcpy(propertyName, "offset"); return; }
		default: { strcpy(propertyName, "unknown"); return; }
	}
}

inline void filterPropertyToString(const FILTER_PROPERTY property, \
								char *propertyName) {

	switch (property) {
		case FILTER_SERIAL: { strcpy(propertyName, "serial"); return; }
		case FILTER_FIRMWARE: { strcpy(propertyName, "firmware"); return; }
		case FILTER_RANGE: { strcpy(propertyName, "range"); return; }
		case FILTER_STEPSIZE: { strcpy(propertyName, "stepsize"); return; }
		case FILTER_WAVELENGTH: { strcpy(propertyName, "wavelength"); return; }
		default: { strcpy(propertyName, "unknown"); return; }
	}
}


/* Camera getters and setters. */
mxArray* getCameraProperty(const cri_CameraHandle handle, \
					const char* propertyName);

mxArray* getCameraProperties(const cri_CameraHandle handle);

void setCameraProperty(const cri_CameraHandle handle, \
					const char* propertyName, \
					const mxArray* mxarr);

void setCameraProperties(const cri_CameraHandle handle, \
						const mxArray* mxstruct);

/* Filter getters and setters. */
mxArray* getFilterProperty(const cri_FilterHandle handle, \
					const char* propertyName);

mxArray* getFilterProperties(const cri_FilterHandle handle);

void setFilterProperty(const cri_FilterHandle handle, \
					const char* propertyName, \
					const mxArray* mxarr);

void setFilterProperties(const cri_FilterHandle handle, \
						const mxArray* mxstruct);

/* Camera access. */
unsigned queryCamera();
cri_CameraHandle openCamera();
CAMERA_STATUS checkCamera(const cri_CameraHandle handle);
void closeCamera(cri_CameraHandle handle);

/* Filter access. */
unsigned queryFilter();
cri_FilterHandle openFilter();
FILTER_STATUS checkFilter(const cri_FilterHandle handle);
void closeFilter(cri_FilterHandle handle);

//cri_Int8Image m_SnapImage;
//cri_Int8Image m_StreamImages[ALLOWED_STREAM_COUNT];
//cri_Int8Image m_AcquireCube;
//
//const int NUMBER_ACQUIRE_IMAGES = 11;
//const int CUBE_ACQUIRE_FRAMES_TO_AVERAGE = 1;
//const float DEFAULT_CUBE_ACQUIRE_EXPOSURE_MS = 100.0;
//
//
//void StreamInt8Callback(cri_Int8Image image);
//void SnapInt8Callback(cri_Int8Image image);
//void AcquireCubeInt8Callback(cri_Int8Image images, cri_Int8Image planarImage, cri_FilterState filterStates[],
//   float exposureTimesMs[],
//   unsigned int curImage,
//   unsigned int totalToAcquire,
//   unsigned int framesToAverage);
//void ErrorCallback(cri_ErrorCode errorCode);
//bool OpenCamera();
//bool OpenFilter();
//void DisplayErrorMessage();
//void DisplayCameraCharacteristics();
//void DisplayFilterCharacteristics();
//bool OpenDevices();
//void ShutdownDevices();
//void SetCameraBitDepthTo(cri_ECameraBitDepth depth);
//void SetCameraBinningTo(cri_ECameraBinning binning);
//void GetCameraImageSize(int * width, int * height);
//void SetDisplayCameraSettings();
//void WaitForCameraToBeReady();
//void GetAutoExposeParameters(cri_AutoExposeParameters * parameters);
//void AutoExposeForPlane();
//void AutoExposeForCube();
//void WaitForCubeAcquireToBeFinished();
//void AcquireCube();

}	/* namespace nuance */

#endif /* _NUANCEFX_MEX_H_ */
