/*
 * nuancefx.h
 *
 *  Created on: Apr 21, 2012
 *      Author: igkiou
 */

#ifndef NUANCE_H_
#define NUANCE_H_

#include <math.h>
#include <string.h>

#include "CriAcquireAPI.h"

#include "mex.h"
#include "matrix.h"

namespace ph {

/*
 * TODO: Replace all casts to static_cast.
 * TODO: Maybe enforce const-ness better.
 */
const char * const ERROR_ID = "MATLAB:nuancefx_mex";

const unsigned int CUBE_ACQUIRE_FRAMES_TO_AVERAGE = 1;

typedef enum PH_PROPERTY {
	PH_NAME = 0,
	PH_SERIAL = 1,
	PH_DRIVER = 2,
	PH_FIRMWARE = 3,
	PH_SENSOR = 4,
	PH_SENSORSIZE = 5,
	PH_IMAGESIZE = 6,
	PH_MAXBITDEPTH = 7,
	PH_BITDEPTH = 8,
//	CAMERA_GAINRANGE = 9,
	PH_GAIN = 9,
	PH_EXPOSURERANGE = 10,
	PH_EXPOSURE = 11,
	PH_BINNING = 12,
	PH_OFFSETRANGE = 13,
	PH_OFFSET = 14,
	PH_PROPERTY_LENGTH = 15,
	PH_PROPERTY_INVALID = -1
} PH_PROPERTY;

/*
 * TODO: Find better way to do these conversions, perhaps using bimap.
 */
inline void cameraPropertyToString(const PH_PROPERTY property, \
								char *propertyName) {

	switch (property) {
		case PH_NAME: { strcpy(propertyName, "name"); return; }
		case PH_SERIAL: { strcpy(propertyName, "serial"); return; }
		case PH_DRIVER: { strcpy(propertyName, "driver"); return; }
		case PH_FIRMWARE: { strcpy(propertyName, "firmware"); return; }
		case PH_SENSOR: { strcpy(propertyName, "sensor"); return; }
		case PH_SENSORSIZE: { strcpy(propertyName, "sensorsize"); return; }
		case PH_IMAGESIZE: { strcpy(propertyName, "imagesize"); return; }
		case PH_MAXBITDEPTH: { strcpy(propertyName, "maxbitdepth"); return; }
		case PH_BITDEPTH: { strcpy(propertyName, "bitdepth"); return; }
//		case CAMERA_GAINRANGE: { strcpy(propertyName, "gainrange"); return; }
		case PH_GAIN: { strcpy(propertyName, "gain"); return; }
		case PH_EXPOSURERANGE: { strcpy(propertyName, "exposurerange"); return; }
		case PH_EXPOSURE: { strcpy(propertyName, "exposure"); return; }
		case PH_BINNING: { strcpy(propertyName, "binning"); return; }
		case PH_OFFSETRANGE: { strcpy(propertyName, "offsetrange"); return; }
		case PH_OFFSET: { strcpy(propertyName, "offset"); return; }
		default: { strcpy(propertyName, "unknown"); return; }
	}
}

inline PH_PROPERTY stringToCameraProperty(const char *propertyName) {

	if(!strcasecmp(propertyName, "name")) {
		return PH_NAME;
	} else if(!strcasecmp(propertyName, "serial")) {
		return PH_SERIAL;
	} else if(!strcasecmp(propertyName, "driver")) {
		return PH_DRIVER;
	} else if(!strcasecmp(propertyName, "firmware")) {
		return PH_FIRMWARE;
	} else if(!strcasecmp(propertyName, "sensor")) {
		return PH_SENSOR;
	} else if(!strcasecmp(propertyName, "sensorsize")) {
		return PH_SENSORSIZE;
	} else if(!strcasecmp(propertyName, "imagesize")) {
		return PH_IMAGESIZE;
	} else if(!strcasecmp(propertyName, "maxbitdepth")) {
		return PH_MAXBITDEPTH;
	} else if(!strcasecmp(propertyName, "bitdepth")) {
		return PH_BITDEPTH;
	} else if(!strcasecmp(propertyName, "gain")) {
		return PH_GAIN;
	} else if(!strcasecmp(propertyName, "exposurerange")) {
		return PH_EXPOSURERANGE;
	} else if(!strcasecmp(propertyName, "exposure")) {
		return PH_EXPOSURE;
	} else if(!strcasecmp(propertyName, "binning")) {
		return PH_BINNING;
	} else if(!strcasecmp(propertyName, "offsetrange")) {
		return PH_OFFSETRANGE;
	} else if(!strcasecmp(propertyName, "offset")) {
		return PH_OFFSET;
	} else {
		return PH_PROPERTY_INVALID;
	}
}

typedef enum CAMERA_STATUS {
	CAMERA_READY = 0,
	CAMERA_BUSY = 1,
	CAMERA_STREAMING = 2,
	CAMERA_ACQUIRING = 3,
	CAMERA_STATUS_LENGTH = 4,
	CAMERA_STATUS_INVALID = -1
} CAMERA_STATUS;

typedef enum FILTER_PROPERTY {
	FILTER_SERIAL = 0,
	FILTER_FIRMWARE = 1,
	FILTER_RANGE = 2,
	FILTER_STEPSIZE = 3,
	FILTER_WAVELENGTH = 4,
	FILTER_PROPERTY_LENGTH = 5,
	FILTER_PROPERTY_INVALID = -1
} FILTER_PROPERTY;

/*
 * TODO: Find better way to do these conversions, perhaps using bimap.
 */
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

inline FILTER_PROPERTY stringToFilterProperty(const char *propertyName) {

	if(!strcasecmp(propertyName, "serial")) {
		return FILTER_SERIAL;
	} else if(!strcasecmp(propertyName, "firmware")) {
		return FILTER_FIRMWARE;
	} else if(!strcasecmp(propertyName, "range")) {
		return FILTER_RANGE;
	} else if(!strcasecmp(propertyName, "stepsize")) {
		return FILTER_STEPSIZE;
	} else if(!strcasecmp(propertyName, "wavelength")) {
		return FILTER_WAVELENGTH;
	} else {
		return FILTER_PROPERTY_INVALID;
	}
}

typedef enum FILTER_STATUS {
	FILTER_READY = 0,
	FILTER_BUSY = 1,
	FILTER_STATUS_LENGTH = 2,
	FILTER_STATUS_INVALID = -1
} FILTER_STATUS;

/*
 * TODO: Maybe rewrite with cri_GetLastError?
 */
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

/*
 * TODO: Separate out name handling in case of multiple variants of
 * getters/setters (maybe move in mex?).
 */

/* Camera getters and setters. */
mxArray* getCameraProperty(const cri_CameraHandle handle, \
						const PH_PROPERTY property);

mxArray* getCameraProperty(const cri_CameraHandle handle);

void setCameraProperty(const cri_CameraHandle handle, \
					const PH_PROPERTY property, \
					const mxArray* mxarr);

void setCameraProperty(const cri_CameraHandle handle, const mxArray* mxstruct);

/* Filter getters and setters. */
mxArray* getFilterProperty(const cri_FilterHandle handle, \
						const FILTER_PROPERTY property);

mxArray* getFilterProperty(const cri_FilterHandle handle);

void setFilterProperty(const cri_FilterHandle handle, \
					const FILTER_PROPERTY property, \
					const mxArray* mxarr);

void setFilterProperty(const cri_FilterHandle handle, const mxArray* mxstruct);

/*
 * TODO: Maybe rewrite access functions to also return void or mxArray*,
 * as in rest of interface? On the other hand, this would mean these can no
 * longer be used in the classes above.
 */

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

/*
 * TODO: These probably not necessary, consider getting rid of.
 */
/* Device access. */
void queryDevice(unsigned *numCameras, unsigned *numFilters);
void openDevice(cri_CameraHandle *cameraHandle, cri_FilterHandle *filterHandle);
void checkDevice(const cri_CameraHandle cameraHandle, \
				const cri_FilterHandle filterHandle, \
				CAMERA_STATUS *cameraStatus, \
				FILTER_STATUS *filterStatus);
void closeDevice(cri_CameraHandle cameraHandle, cri_FilterHandle filterHandle);

/* Do some actual acquisition. */
mxArray* getAutoExposure(const cri_CameraHandle cameraHandle, \
						const cri_FilterHandle filterHandle, \
						const double *wavelengths, \
						const unsigned numWavelengths);

mxArray* capture(const cri_CameraHandle cameraHandle, \
				const cri_FilterHandle filterHandle, \
				const double *wavelengths, const double *exposureTimes, \
				const unsigned numWavelengths);

mxArray* captureSingle(const cri_CameraHandle cameraHandle, \
				const cri_FilterHandle filterHandle, \
				const double wavelength, const double exposureTime);

mxArray* snap(const cri_CameraHandle cameraHandle);

mxArray* snapFrames(const cri_CameraHandle cameraHandle, const unsigned numFrames);

void snapPreAlloc(const cri_CameraHandle cameraHandle, const mxArray *mxarr);

void snapPreAllocFrames(const cri_CameraHandle cameraHandle, const mxArray *mxarr,
						const unsigned numFrames);

}	/* namespace nuance */

#endif /* _NUANCE_H_ */
