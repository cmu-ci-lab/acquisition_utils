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
	CAMERA_DRIVER = 2,
	CAMERA_FIRMWARE = 3,
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
	CAMERA_PROPERTY_LENGTH = 16,
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

inline void cameraPropertyToString(const CAMERA_PROPERTY property, \
								char *propertyName) {

	switch (property) {
		case CAMERA_NAME: { strcpy(propertyName, "name"); }
		case CAMERA_SERIAL: { strcpy(propertyName, "serial"); }
		case CAMERA_DRIVER: { strcpy(propertyName, "driver"); }
		case CAMERA_FIRMWARE: { strcpy(propertyName, "firmware"); }
		case CAMERA_SENSOR: { strcpy(propertyName, "sensor"); }
		case CAMERA_SENSORSIZE: { strcpy(propertyName, "sensorsize"); }
		case CAMERA_IMAGESIZE: { strcpy(propertyName, "imagesize"); }
		case CAMERA_MAXBITDEPTH: { strcpy(propertyName, "maxbitdepth"); }
		case CAMERA_BITDEPTH: { strcpy(propertyName, "bitdepth"); }
		case CAMERA_GAINRANGE: { strcpy(propertyName, "gainrange"); }
		case CAMERA_GAIN: { strcpy(propertyName, "gain"); }
		case CAMERA_EXPOSURERANGE: { strcpy(propertyName, "exposurerange"); }
		case CAMERA_EXPOSURE: { strcpy(propertyName, "exposure"); }
		case CAMERA_BINNING: { strcpy(propertyName, "binning"); }
		case CAMERA_OFFSETRANGE: { strcpy(propertyName, "offsetrange"); }
		case CAMERA_OFFSET: { strcpy(propertyName, "offset"); }
		default: { strcpy(propertyName, "unknown"); }
	}
}

inline void filterPropertyToString(const FILTER_PROPERTY property, \
								char *propertyName) {

	switch (property) {
		case FILTER_SERIAL: { strcpy(propertyName, "serial"); }
		case FILTER_FIRMWARE: { strcpy(propertyName, "firmware"); }
		case FILTER_RANGE: { strcpy(propertyName, "range"); }
		case FILTER_STEPSIZE: { strcpy(propertyName, "stepsize"); }
		case FILTER_WAVELENGTH: { strcpy(propertyName, "wavelength"); }
		default: { strcpy(propertyName, "unknown"); }
	}
}


/* Camera getters and setters. */
void getCameraProperty(const cri_CameraHandle handle, \
					const char* propertyName, \
					mxArray* mxarr);

void getCameraProperties(const cri_CameraHandle handle, \
						mxArray* mxstruct);

void setCameraProperty(const cri_CameraHandle handle, \
					const char* propertyName, \
					const mxArray* mxarr);

void setCameraProperties(const cri_CameraHandle handle, \
						const mxArray* mxstruct);

/* Filter getters and setters. */
void getFilterProperty(const cri_FilterHandle handle, \
					const char* propertyName, \
					mxArray* mxarr);

void getFilterProperties(const cri_FilterHandle handle, \
						mxArray* mxstruct);

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
