/* temp.cpp
 *
 *  Created on: May 22, 2012
 *      Author: igkiou
 */

#include "nuancefx_mex.h"

namespace nuance {

mxArray* getCameraProperty(const cri_CameraHandle handle, \
							const char* propertyName) {

	if (!strcasecmp(propertyName, "name")) {
		char name[cri_MAX_STRING_LENGTH];
		char serial[cri_MAX_STRING_LENGTH];
		char sensor[cri_MAX_STRING_LENGTH];
		cri_ECameraBitDepth maxBitDepth;
		int sensorWidth;
		int sensorHeight;
		char driver[cri_MAX_STRING_LENGTH];
		char firmware[cri_MAX_STRING_LENGTH];
		cri_ErrorCode errorCode = cri_GetCameraDescription(handle, name, serial, sensor, \
										&maxBitDepth, &sensorWidth, &sensorHeight, \
										driver, firmware);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateString(name);
		return mxarr;
	} else if (!strcasecmp(propertyName, "serial")) {
		char name[cri_MAX_STRING_LENGTH];
		char serial[cri_MAX_STRING_LENGTH];
		char sensor[cri_MAX_STRING_LENGTH];
		cri_ECameraBitDepth maxBitDepth;
		int sensorWidth;
		int sensorHeight;
		char driver[cri_MAX_STRING_LENGTH];
		char firmware[cri_MAX_STRING_LENGTH];
		cri_ErrorCode errorCode = cri_GetCameraDescription(handle, name, serial, sensor, \
										&maxBitDepth, &sensorWidth, &sensorHeight, \
										driver, firmware);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateString(serial);
		return mxarr;
	} else if (!strcasecmp(propertyName, "driver")) {
		char name[cri_MAX_STRING_LENGTH];
		char serial[cri_MAX_STRING_LENGTH];
		char sensor[cri_MAX_STRING_LENGTH];
		cri_ECameraBitDepth maxBitDepth;
		int sensorWidth;
		int sensorHeight;
		char driver[cri_MAX_STRING_LENGTH];
		char firmware[cri_MAX_STRING_LENGTH];
		cri_ErrorCode errorCode = cri_GetCameraDescription(handle, name, serial, sensor, \
										&maxBitDepth, &sensorWidth, &sensorHeight, \
										driver, firmware);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateString(driver);
		return mxarr;
	} else if (!strcasecmp(propertyName, "firmware")) {
		char name[cri_MAX_STRING_LENGTH];
		char serial[cri_MAX_STRING_LENGTH];
		char sensor[cri_MAX_STRING_LENGTH];
		cri_ECameraBitDepth maxBitDepth;
		int sensorWidth;
		int sensorHeight;
		char driver[cri_MAX_STRING_LENGTH];
		char firmware[cri_MAX_STRING_LENGTH];
		cri_ErrorCode errorCode = cri_GetCameraDescription(handle, name, serial, sensor, \
										&maxBitDepth, &sensorWidth, &sensorHeight, \
										driver, firmware);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateString(firmware);
		return mxarr;
	} else if (!strcasecmp(propertyName, "sensor")) {
		char name[cri_MAX_STRING_LENGTH];
		char serial[cri_MAX_STRING_LENGTH];
		char sensor[cri_MAX_STRING_LENGTH];
		cri_ECameraBitDepth maxBitDepth;
		int sensorWidth;
		int sensorHeight;
		char driver[cri_MAX_STRING_LENGTH];
		char firmware[cri_MAX_STRING_LENGTH];
		cri_ErrorCode errorCode = cri_GetCameraDescription(handle, name, serial, sensor, \
										&maxBitDepth, &sensorWidth, &sensorHeight, \
										driver, firmware);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateString(sensor);
		return mxarr;
	} else if (!strcasecmp(propertyName, "sensorsize")) {
		int width;
		int height;
		cri_ErrorCode errorCode = cri_GetCameraSensorSize(handle, &width, &height);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleMatrix(2, 1, mxREAL);
		double *data = (double *) mxGetData(mxarr);
		data[0] = (double) width;
		data[1] = (double) height;
		return mxarr;
	} else if (!strcasecmp(propertyName, "imagesize")) {
		int width;
		int height;
		cri_ErrorCode errorCode = cri_GetCameraImageSize(handle, &width, &height);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleMatrix(2, 1, mxREAL);
		double *data = (double *) mxGetData(mxarr);
		data[0] = (double) width;
		data[1] = (double) height;
		return mxarr;
	} else if (!strcasecmp(propertyName, "maxbitdepth")) {
		char name[cri_MAX_STRING_LENGTH];
		char serial[cri_MAX_STRING_LENGTH];
		char sensor[cri_MAX_STRING_LENGTH];
		cri_ECameraBitDepth maxBitDepth;
		int sensorWidth;
		int sensorHeight;
		char driver[cri_MAX_STRING_LENGTH];
		char firmware[cri_MAX_STRING_LENGTH];
		cri_ErrorCode errorCode = cri_GetCameraDescription(handle, name, serial, sensor, \
										&maxBitDepth, &sensorWidth, &sensorHeight, \
										driver, firmware);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleScalar((double) maxBitDepth);
		return mxarr;
	} else if(!strcasecmp(propertyName, "bitdepth")) {
		cri_ECameraBitDepth bitDepth;
		cri_ErrorCode errorCode = cri_GetCameraBitDepth(handle, &bitDepth);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleScalar((double) bitDepth);
		return mxarr;
//	} else if(!strcasecmp(propertyName, "gainrange")) {
//		int lowRange;
//		int highRange;
//		cri_ErrorCode errorCode = cri_GetCameraGainRange(handle, &lowRange, &highRange);
//		mxarr = mxCreateDoubleMatrix(2, 1, mxREAL);
//		double *data = (double *) mxGetData(*mxarr);
//		data[0] = (double) lowRange;
//		data[1] = (double) highRange;
	} else if(!strcasecmp(propertyName, "gain")) {
		cri_ECameraGain gain;
		cri_ErrorCode errorCode = cri_GetCameraGain(handle, &gain);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleScalar((double) gain);
		return mxarr;
	} else if(!strcasecmp(propertyName, "exposurerange")) {
		float lowRange;
		float highRange;
		cri_ErrorCode errorCode = cri_GetCameraExposureRangeMs(handle, &lowRange, &highRange);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleMatrix(2, 1, mxREAL);
		double *data = (double *) mxGetData(mxarr);
		data[0] = (double) lowRange;
		data[1] = (double) highRange;
		return mxarr;
	} else if(!strcasecmp(propertyName, "exposure")) {
		float exposure;
		cri_ErrorCode errorCode = cri_GetCameraExposureMs(handle, &exposure);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleScalar((double) exposure);
		return mxarr;
	} else if(!strcasecmp(propertyName, "binning")) {
		cri_ECameraBinning binning;
		cri_ErrorCode errorCode = cri_GetCameraBinning(handle, &binning);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleScalar((double) binning);
		return mxarr;
	} else if(!strcasecmp(propertyName, "offsetrange")) {
		int lowRange;
		int highRange;
		cri_ErrorCode errorCode = cri_GetCameraOffsetRange(handle, &lowRange, &highRange);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleMatrix(2, 1, mxREAL);
		double *data = (double *) mxGetData(mxarr);
		data[0] = (double) lowRange;
		data[1] = (double) highRange;
		return mxarr;
	} else if(!strcasecmp(propertyName, "offset")) {
		int offset;
		cri_ErrorCode errorCode = cri_GetCameraOffset(handle, &offset);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleScalar((double) offset);
		return mxarr;
	} else {
		mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported camera property: %s.", propertyName);
		return NULL;
	}
}

mxArray* getCameraProperties(const cri_CameraHandle handle) {

	unsigned numProperties = (unsigned) CAMERA_PROPERTY_LENGTH;
	mxArray *mxstruct;
	char **propertyNames = (char **) \
			mxMalloc(numProperties * sizeof(*propertyNames));
	for (unsigned iterProperty = 0; iterProperty < numProperties; ++iterProperty) {
		propertyNames[iterProperty] = (char *) mxMalloc(cri_MAX_STRING_LENGTH * sizeof(char));
		cameraPropertyToString((CAMERA_PROPERTY) iterProperty, propertyNames[iterProperty]);
	}
	mxstruct = mxCreateStructMatrix(1, 1, numProperties, (const char **) propertyNames);
	for (unsigned iterProperty = 0; iterProperty < numProperties; ++iterProperty) {
		mxSetFieldByNumber(mxstruct, 0, iterProperty, getCameraProperty(handle, propertyNames[iterProperty]));
	}
	for (unsigned iterProperty = 0; iterProperty < numProperties; ++iterProperty) {
		mxFree((void *) propertyNames[iterProperty]);
	}
	mxFree((void *) propertyNames);
	return mxstruct;
}

void setCameraProperty(const cri_CameraHandle handle, \
							const char* propertyName, \
							const mxArray* mxarr) {

	double val = mxGetScalar(mxarr);
	if(!strcasecmp(propertyName, "bitdepth")) {
		cri_ErrorCode errorCode = cri_SetCameraBitDepth(handle, (cri_ECameraBitDepth) val);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
	} else if(!strcasecmp(propertyName, "gain")) {
		cri_ErrorCode errorCode = cri_SetCameraGain(handle, (cri_ECameraGain) val);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
	} else if(!strcasecmp(propertyName, "exposure")) {
		cri_ErrorCode errorCode = cri_SetCameraExposureMs(handle, (float) val);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
	} else if(!strcasecmp(propertyName, "binning")) {
		cri_ErrorCode errorCode = cri_SetCameraBinning(handle, (cri_ECameraBinning) val);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
	} else if(!strcasecmp(propertyName, "offset")) {
		cri_ErrorCode errorCode = cri_SetCameraOffset(handle, (int) val);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
	} else {
		mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported camera property: %s.", propertyName);
	}
}

void setCameraProperties(const cri_CameraHandle handle, \
						const mxArray* mxstruct) {

	if (mxIsStruct(mxstruct)) {
		unsigned numProperties = mxGetNumberOfFields(mxstruct);
		for (unsigned iterProperty = 0; iterProperty < numProperties; ++iterProperty) {
			setCameraProperty(handle, mxGetFieldNameByNumber(mxstruct, iterProperty), \
							mxGetFieldByNumber(mxstruct, 0, iterProperty));
		}
	} else if (!mxIsEmpty(mxstruct)) {
		mexErrMsgIdAndTxt(ERROR_ID, "For setting multiple attributes, a struct array must be provided.");
	}
}

mxArray* getFilterProperty(const cri_FilterHandle handle, \
							const char* propertyName) {

	if (!strcasecmp(propertyName, "serial")) {
		int serial;
		float lowWavelengthRange;
		float highWavelengthRange;
		int waveplateStages;
		int firmware;
		cri_ErrorCode errorCode = cri_GetFilterDescription(handle, &serial, \
										&lowWavelengthRange, &highWavelengthRange, \
										&waveplateStages, &firmware);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleScalar((double) serial);
		return mxarr;
	} else if (!strcasecmp(propertyName, "firmware")) {
		int serial;
		float lowWavelengthRange;
		float highWavelengthRange;
		int waveplateStages;
		int firmware;
		cri_ErrorCode errorCode = cri_GetFilterDescription(handle, &serial, \
										&lowWavelengthRange, &highWavelengthRange, \
										&waveplateStages, &firmware);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleScalar((double) firmware);
		return mxarr;
	} else if(!strcasecmp(propertyName, "range")) {
		float lowWavelengthRange;
		float highWavelengthRange;
		float stepSize;
		cri_ErrorCode errorCode = cri_GetFilterRangeAndStepSize(handle, &lowWavelengthRange, \
												&highWavelengthRange, &stepSize);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleMatrix(2, 1, mxREAL);
		double *data = (double *) mxGetData(mxarr);
		data[0] = (double) lowWavelengthRange;
		data[1] = (double) highWavelengthRange;
		return mxarr;
	} else if(!strcasecmp(propertyName, "stepsize")) {
		float lowWavelengthRange;
		float highWavelengthRange;
		float stepSize;
		cri_ErrorCode errorCode = cri_GetFilterRangeAndStepSize(handle, &lowWavelengthRange, \
												&highWavelengthRange, &stepSize);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleScalar((double) stepSize);
		return mxarr;
	} else if(!strcasecmp(propertyName, "wavelength")) {
		cri_FilterState filterState;
		filterState.reserved[0] = 0.0f;
		filterState.reserved[1] = 0.0f;
		cri_ErrorCode errorCode = cri_GetFilterState(handle, &filterState);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		mxArray *mxarr = mxCreateDoubleScalar((double) filterState.wavelength);
		return mxarr;
	} else {
		mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported filter property: %s.", propertyName);
		return NULL;
	}
}

mxArray* getFilterProperties(const cri_FilterHandle handle) {

	unsigned numProperties = (unsigned) FILTER_PROPERTY_LENGTH;
	mxArray *mxstruct;
	char **propertyNames = (char **) \
			mxMalloc(numProperties * sizeof(*propertyNames));
	for (unsigned iterProperty = 0; iterProperty < numProperties; ++iterProperty) {
		propertyNames[iterProperty] = (char *) mxMalloc(cri_MAX_STRING_LENGTH * sizeof(char));
		filterPropertyToString((FILTER_PROPERTY) iterProperty, propertyNames[iterProperty]);
	}
	mxstruct = mxCreateStructMatrix(1, 1, numProperties, (const char **) propertyNames);
	for (unsigned iterProperty = 0; iterProperty < numProperties; ++iterProperty) {
		mxSetFieldByNumber(mxstruct, 0, iterProperty, getFilterProperty(handle, propertyNames[iterProperty]));
	}
	for (unsigned iterProperty = 0; iterProperty < numProperties; ++iterProperty) {
		mxFree((void *) propertyNames[iterProperty]);
	}
	mxFree((void *) propertyNames);
	return mxstruct;
}

void setFilterProperty(const cri_FilterHandle handle, \
							const char* propertyName, \
							const mxArray* mxarr) {

	double val = mxGetScalar(mxarr);
	if(!strcasecmp(propertyName, "wavelength")) {
		cri_FilterState filterState;
		filterState.wavelength = (double) val;
		filterState.reserved[0] = 0.0f;
		filterState.reserved[1] = 0.0f;
		cri_ErrorCode errorCode = cri_SetFilterState(handle, filterState, true);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
	} else {
		mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported filter property: %s.", propertyName);
	}
}

void setFilterProperties(const cri_FilterHandle handle, \
						const mxArray* mxstruct) {

	if (mxIsStruct(mxstruct)) {
		unsigned numProperties = mxGetNumberOfFields(mxstruct);
		for (unsigned iterProperty = 0; iterProperty < numProperties; ++iterProperty) {
			setFilterProperty(handle, mxGetFieldNameByNumber(mxstruct, iterProperty), \
							mxGetFieldByNumber(mxstruct, 0, iterProperty));
		}
	} else if (!mxIsEmpty(mxstruct)) {
		mexErrMsgIdAndTxt(ERROR_ID, "For setting multiple attributes, a struct array must be provided.");
	}
}

unsigned queryCamera() {
	return (unsigned) cri_GetNumberAvailableCameras();
}

cri_CameraHandle openCamera() {

	int numCameras = cri_GetNumberAvailableCameras();
	if (numCameras > 1) {
		mexWarnMsgTxt("Warning: more than one available cameras found. Multiple cameras are not well supported.");
	} else if (numCameras <= 0) {
		mexErrMsgIdAndTxt(ERROR_ID, "No available camera found.");
		return -1;
	}
	int *cameraIDs = new int[numCameras];
	int numCameraIDs = cri_FindAvailableCameras(cameraIDs, numCameras);

	if (numCameraIDs > 0){
		cri_CameraHandle handle;
		cri_ErrorCode errorCode = cri_OpenCamera(cameraIDs[0], &handle);

		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		delete [] cameraIDs;
		return handle;
	} else {
		delete [] cameraIDs;
		mexErrMsgIdAndTxt(ERROR_ID, "No available camera found.");
		return -1;
	}
}

CAMERA_STATUS checkCamera(const cri_CameraHandle handle) {
	cri_ErrorCode errorCode;
	bool ready = false;
	errorCode = cri_CameraReady(handle, &ready);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
	}
	if (!ready) {
		return CAMERA_BUSY;
	}

	bool streaming = false;
	errorCode = cri_IsCameraStreaming(handle, &streaming);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
	}
	if (!streaming) {
		return CAMERA_STREAMING;
	}

	bool acquiring = false;
	errorCode = cri_IsCameraAcquiring(handle, &acquiring);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
	}
	if (!acquiring) {
		return CAMERA_ACQUIRING;
	}

	return CAMERA_READY;
}

void closeCamera(cri_CameraHandle handle) {
	cri_ErrorCode errorCode = cri_CloseCamera(&handle);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
	}
}

unsigned queryFilter() {
	return (unsigned) cri_GetNumberAvailableFilters();
}

cri_FilterHandle openFilter() {

	int numFilters = cri_GetNumberAvailableFilters();
	if (numFilters > 1) {
		mexWarnMsgTxt("Warning: more than one available filters found. Multiple filters are not well supported.");
	} else if (numFilters <= 0) {
		mexErrMsgIdAndTxt(ERROR_ID, "No available filter found.");
		return -1;
	}
	int *filterIDs = new int[numFilters];
	int numFilterIDs = cri_FindAvailableFilters(filterIDs, numFilters);

	if (numFilterIDs > 0){
		cri_FilterHandle handle;
		cri_ErrorCode errorCode = cri_OpenFilter(filterIDs[0], &handle);

		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
		}
		delete [] filterIDs;
		return handle;
	} else {
		delete [] filterIDs;
		mexErrMsgIdAndTxt(ERROR_ID, "No available filter found.");
		return -1;
	}
}

FILTER_STATUS checkFilter(const cri_FilterHandle handle) {
	cri_ErrorCode errorCode;
	bool ready = false;
	errorCode = cri_FilterReady(handle, &ready);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
	}
	if (!ready) {
		return FILTER_BUSY;
	}

	return FILTER_READY;
}

void closeFilter(cri_FilterHandle handle) {
	cri_ErrorCode errorCode = cri_CloseFilter(&handle);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
	}
}

void queryDevice(unsigned *numCameras, unsigned *numFilters) {
	*numCameras = queryCamera();
	*numFilters = queryFilter();
}

void openDevice(cri_CameraHandle *cameraHandle, cri_FilterHandle *filterHandle) {
	*cameraHandle = openCamera();
	*filterHandle = openFilter();
}

void checkDevice(const cri_CameraHandle cameraHandle, \
				const cri_FilterHandle filterHandle, \
				CAMERA_STATUS *cameraStatus, \
				FILTER_STATUS *filterStatus) {
	*cameraStatus = checkCamera(cameraHandle);
	*filterStatus = checkFilter(filterHandle);
}

void closeDevice(cri_CameraHandle cameraHandle, cri_FilterHandle filterHandle) {
	closeCamera(cameraHandle);
	closeFilter(filterHandle);
}

float getAutoExposure(const cri_CameraHandle cameraHandle, \
					const cri_FilterHandle filterHandle) {
	cri_AutoExposeParameters parameters;
	parameters.rule = cri_AutoExposeRuleBrightest;
	parameters.targetRatioFullScale = 1.0f;
	cri_ErrorCode errorCode;
	errorCode = cri_GetCameraExposureRangeMs(cameraHandle, \
												&(parameters.minExposureMs), \
												&(parameters.maxExposureMs));
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
		return 0.0f;
	}

//	TODO: Check if these should be 1 or 0, and sensor or image dims.
	parameters.roiOriginX = 1;
	parameters.roiOriginY = 1;
	errorCode = cri_GetCameraImageSize(cameraHandle, &(parameters.roiWidth), \
									&(parameters.roiWidth));

	parameters.minAcceptableRatioFullScale = 0.0f;
	parameters.maxAcceptableRatioFullScale = 0.0f;

	float exposure;
	errorCode = cri_AutoExposePlane(cameraHandle, filterHandle, parameters,
									&exposure);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
		return 0.0f;
	}
	return exposure;
}


}	/* namespace nuance */
