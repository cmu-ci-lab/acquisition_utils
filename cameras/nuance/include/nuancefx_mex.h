/*
 * nuancefx.h
 *
 *  Created on: Apr 21, 2012
 *      Author: igkiou
 */

#ifndef NUANCEFX_MEX_H_
#define NUANCEFX_MEX_H_

#include <math.h>
#include <string.h>

#include "CriAcquireAPI.h"

#include "mex.h"
#include "matrix.h"

namespace nuance {

/*
 * TODO: Replace all casts to static_cast.
 * TODO: Maybe enforce const-ness better.
 */
const char * const ERROR_ID = "MATLAB:nuancefx_mex";

const unsigned int CUBE_ACQUIRE_FRAMES_TO_AVERAGE = 1;

typedef enum CAMERA_PROPERTY {
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

/*
 * TODO: Find better way to do these conversions, perhaps using bimap.
 */
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

inline CAMERA_PROPERTY stringToCameraProperty(const char *propertyName) {

	if(!strcasecmp(propertyName, "name")) {
		return CAMERA_NAME;
	} else if(!strcasecmp(propertyName, "serial")) {
		return CAMERA_SERIAL;
	} else if(!strcasecmp(propertyName, "driver")) {
		return CAMERA_DRIVER;
	} else if(!strcasecmp(propertyName, "firmware")) {
		return CAMERA_FIRMWARE;
	} else if(!strcasecmp(propertyName, "sensor")) {
		return CAMERA_SENSOR;
	} else if(!strcasecmp(propertyName, "sensorsize")) {
		return CAMERA_SENSORSIZE;
	} else if(!strcasecmp(propertyName, "imagesize")) {
		return CAMERA_IMAGESIZE;
	} else if(!strcasecmp(propertyName, "maxbitdepth")) {
		return CAMERA_MAXBITDEPTH;
	} else if(!strcasecmp(propertyName, "bitdepth")) {
		return CAMERA_BITDEPTH;
	} else if(!strcasecmp(propertyName, "gain")) {
		return CAMERA_GAIN;
	} else if(!strcasecmp(propertyName, "exposurerange")) {
		return CAMERA_EXPOSURERANGE;
	} else if(!strcasecmp(propertyName, "exposure")) {
		return CAMERA_EXPOSURE;
	} else if(!strcasecmp(propertyName, "binning")) {
		return CAMERA_BINNING;
	} else if(!strcasecmp(propertyName, "offsetrange")) {
		return CAMERA_OFFSETRANGE;
	} else if(!strcasecmp(propertyName, "offset")) {
		return CAMERA_OFFSET;
	} else {
		return CAMERA_PROPERTY_INVALID;
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
						const CAMERA_PROPERTY property);

mxArray* getCameraProperty(const cri_CameraHandle handle);

void setCameraProperty(const cri_CameraHandle handle, \
					const CAMERA_PROPERTY property, \
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

/*
 * TODO: Maybe add an m_init flag to these classes?
 */
/* Simple classes using the above functions. */
struct Camera {
public:
	Camera() { m_handle = openCamera(); }

	inline mxArray* get(const CAMERA_PROPERTY property) const {
		return getCameraProperty(m_handle, property);
	}

	inline mxArray* get() const {
		return getCameraProperty(m_handle);
	}

	inline void set(const CAMERA_PROPERTY property, const mxArray* mxarr) const {
		setCameraProperty(m_handle, property, mxarr);
	}

	inline void set(const mxArray* mxstruct) const {
		setCameraProperty(m_handle, mxstruct);
	}

	inline cri_CameraHandle handle() const {
		return m_handle;
	}

	inline CAMERA_STATUS status() const {
		return checkCamera(m_handle);
	}

	~Camera() { closeCamera(m_handle); }

private:
	cri_CameraHandle m_handle;
};

struct Filter {
public:
	Filter() { m_handle = openFilter(); }

	inline mxArray* get(const FILTER_PROPERTY property) const {
		return getFilterProperty(m_handle, property);
	}

	inline mxArray* get() const {
		return getFilterProperty(m_handle);
	}

	inline void set(const FILTER_PROPERTY property, const mxArray* mxarr) const {
		setFilterProperty(m_handle, property, mxarr);
	}

	inline void set(const mxArray* mxstruct) const {
		setFilterProperty(m_handle, mxstruct);
	}

	inline cri_FilterHandle handle() const {
		return m_handle;
	}

	inline FILTER_STATUS status() const {
		return checkFilter(m_handle);
	}

	~Filter() { closeFilter(m_handle); }

private:
	cri_FilterHandle m_handle;
};

struct Device {
public:
	Device() : m_camera(), m_filter() {	}

	inline Camera& camera() {
		return m_camera;
	}

	inline Filter& filter() {
		return m_filter;
	}

	inline mxArray* acquire(const double *wavelengths, \
							const double *exposureTimes, \
							const unsigned numWavelengths) {
		return capture(m_camera.handle(), m_filter.handle(), \
					wavelengths, exposureTimes, numWavelengths);
	}

	inline mxArray* autoexpose(const double *wavelengths, \
								const unsigned numWavelengths) {
		return getAutoExposure(m_camera.handle(), m_filter.handle(), wavelengths, numWavelengths);
	}

	~Device() { m_camera.~Camera(); m_filter.~Filter(); }

private:
	Camera m_camera;
	Filter m_filter;
};

}	/* namespace nuance */

#endif /* _NUANCEFX_MEX_H_ */
