/* temp.cpp
 *
 *  Created on: May 22, 2012
 *      Author: igkiou
 */

#include "nuancefx_mex.h"

namespace nuance {

void getCameraProperty(const cri_CameraHandle handle, \
							const char* propertyName, \
							mxArray** mxarr) {

	cri_ErrorCode errorCode;
	if (!strcasecmp(propertyName, "name")) {
		char name[cri_MAX_STRING_LENGTH];
		char serial[cri_MAX_STRING_LENGTH];
		char sensor[cri_MAX_STRING_LENGTH];
		cri_ECameraBitDepth maxBitDepth;
		int sensorWidth;
		int sensorHeight;
		char driver[cri_MAX_STRING_LENGTH];
		char firmware[cri_MAX_STRING_LENGTH];
		errorCode = cri_GetCameraDescription(handle, name, serial, sensor, \
										&maxBitDepth, &sensorWidth, &sensorHeight, \
										driver, firmware);
		*mxarr = mxCreateString(name);
	} else if (!strcasecmp(propertyName, "serial")) {
		char name[cri_MAX_STRING_LENGTH];
		char serial[cri_MAX_STRING_LENGTH];
		char sensor[cri_MAX_STRING_LENGTH];
		cri_ECameraBitDepth maxBitDepth;
		int sensorWidth;
		int sensorHeight;
		char driver[cri_MAX_STRING_LENGTH];
		char firmware[cri_MAX_STRING_LENGTH];
		errorCode = cri_GetCameraDescription(handle, name, serial, sensor, \
										&maxBitDepth, &sensorWidth, &sensorHeight, \
										driver, firmware);
		*mxarr = mxCreateString(serial);
	} else if (!strcasecmp(propertyName, "driver")) {
		char name[cri_MAX_STRING_LENGTH];
		char serial[cri_MAX_STRING_LENGTH];
		char sensor[cri_MAX_STRING_LENGTH];
		cri_ECameraBitDepth maxBitDepth;
		int sensorWidth;
		int sensorHeight;
		char driver[cri_MAX_STRING_LENGTH];
		char firmware[cri_MAX_STRING_LENGTH];
		errorCode = cri_GetCameraDescription(handle, name, serial, sensor, \
										&maxBitDepth, &sensorWidth, &sensorHeight, \
										driver, firmware);
		*mxarr = mxCreateString(driver);
	} else if (!strcasecmp(propertyName, "firmware")) {
		char name[cri_MAX_STRING_LENGTH];
		char serial[cri_MAX_STRING_LENGTH];
		char sensor[cri_MAX_STRING_LENGTH];
		cri_ECameraBitDepth maxBitDepth;
		int sensorWidth;
		int sensorHeight;
		char driver[cri_MAX_STRING_LENGTH];
		char firmware[cri_MAX_STRING_LENGTH];
		errorCode = cri_GetCameraDescription(handle, name, serial, sensor, \
										&maxBitDepth, &sensorWidth, &sensorHeight, \
										driver, firmware);
		*mxarr = mxCreateString(firmware);
	} else if (!strcasecmp(propertyName, "sensor")) {
		char name[cri_MAX_STRING_LENGTH];
		char serial[cri_MAX_STRING_LENGTH];
		char sensor[cri_MAX_STRING_LENGTH];
		cri_ECameraBitDepth maxBitDepth;
		int sensorWidth;
		int sensorHeight;
		char driver[cri_MAX_STRING_LENGTH];
		char firmware[cri_MAX_STRING_LENGTH];
		errorCode = cri_GetCameraDescription(handle, name, serial, sensor, \
										&maxBitDepth, &sensorWidth, &sensorHeight, \
										driver, firmware);
		*mxarr = mxCreateString(sensor);
	} else if (!strcasecmp(propertyName, "sensorsize")) {
		int width;
		int height;
		errorCode = cri_GetCameraSensorSize(handle, &width, &height);
		*mxarr = mxCreateDoubleMatrix(2, 1, mxREAL);
		double *data = (double *) mxGetData(*mxarr);
		data[0] = (double) width;
		data[1] = (double) height;
	} else if (!strcasecmp(propertyName, "imagesize")) {
		int width;
		int height;
		errorCode = cri_GetCameraImageSize(handle, &width, &height);
		*mxarr = mxCreateDoubleMatrix(2, 1, mxREAL);
		double *data = (double *) mxGetData(*mxarr);
		data[0] = (double) width;
		data[1] = (double) height;
	} else if (!strcasecmp(propertyName, "maxbitdepth")) {
		char name[cri_MAX_STRING_LENGTH];
		char serial[cri_MAX_STRING_LENGTH];
		char sensor[cri_MAX_STRING_LENGTH];
		cri_ECameraBitDepth maxBitDepth;
		int sensorWidth;
		int sensorHeight;
		char driver[cri_MAX_STRING_LENGTH];
		char firmware[cri_MAX_STRING_LENGTH];
		errorCode = cri_GetCameraDescription(handle, name, serial, sensor, \
										&maxBitDepth, &sensorWidth, &sensorHeight, \
										driver, firmware);
		*mxarr = mxCreateDoubleScalar((double) maxBitDepth);
	} else if(!strcasecmp(propertyName, "bitdepth")) {
		cri_ECameraBitDepth bitDepth;
		errorCode = cri_GetCameraBitDepth(handle, &bitDepth);
		*mxarr = mxCreateDoubleScalar((double) bitDepth);
	} else if(!strcasecmp(propertyName, "gainrange")) {
		int lowRange;
		int highRange;
		errorCode = cri_GetCameraGainRange(handle, &lowRange, &highRange);
		*mxarr = mxCreateDoubleMatrix(2, 1, mxREAL);
		double *data = (double *) mxGetData(*mxarr);
		data[0] = (double) lowRange;
		data[1] = (double) highRange;
	} else if(!strcasecmp(propertyName, "gain")) {
		cri_ECameraGain gain;
		errorCode = cri_GetCameraGain(handle, &gain);
		mxarr = mxCreateDoubleScalar((double) gain);
	} else if(!strcasecmp(propertyName, "exposurerange")) {
		float lowRange;
		float highRange;
		errorCode = cri_GetCameraExposureRangeMs(handle, &lowRange, &highRange);
		*mxarr = mxCreateDoubleMatrix(2, 1, mxREAL);
		double *data = (double *) mxGetData(*mxarr);
		data[0] = (double) lowRange;
		data[1] = (double) highRange;
	} else if(!strcasecmp(propertyName, "exposure")) {
		float exposure;
		errorCode = cri_GetCameraExposureMs(handle, &exposure);
		*mxarr = mxCreateDoubleScalar((double) exposure);
	} else if(!strcasecmp(propertyName, "binning")) {
		cri_ECameraBinning binning;
		errorCode = cri_GetCameraBinning(handle, &binning);
		*mxarr = mxCreateDoubleScalar((double) binning);
	} else if(!strcasecmp(propertyName, "offsetrange")) {
		int lowRange;
		int highRange;
		errorCode = cri_GetCameraOffsetRange(handle, &lowRange, &highRange);
		*mxarr = mxCreateDoubleMatrix(2, 1, mxREAL);
		double *data = (double *) mxGetData(*mxarr);
		data[0] = (double) lowRange;
		data[1] = (double) highRange;
	} else if(!strcasecmp(propertyName, "offset")) {
		int offset;
		errorCode = cri_GetCameraOffset(handle, &offset);
		*mxarr = mxCreateDoubleScalar((double) offset);
	} else {
		errorCode = cri_NoError;
		mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported camera property: %s.", propertyName);
	}
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
	}
}

void getCameraProperties(const cri_CameraHandle handle, mxArray** mxstruct) {

	char **propertyNames = (char **) \
			mxMalloc((size_t) CAMERA_PROPERTY_LENGTH * sizeof(*propertyNames));
	for (unsigned iterProperty = 0; iterProperty < (unsigned) CAMERA_PROPERTY_LENGTH; ++iterProperty) {
		propertyNames[iterProperty] = (char *) mxMalloc(cri_MAX_STRING_LENGTH * sizeof(char));
		cameraPropertyToString((CAMERA_PROPERTY) iterProperty, propertyNames[iterProperty]);
	}
	*mxstruct = mxCreateStructMatrix(1, 1, (unsigned) CAMERA_PROPERTY_LENGTH, (const char **) propertyNames);
	mxArray *temp = NULL;
	for (unsigned iterProperty = 0; iterProperty < (unsigned) CAMERA_PROPERTY_LENGTH; ++iterProperty) {
		getCameraProperty(handle, propertyNames[iterProperty], temp);
		mxSetFieldByNumber(*mxstruct, 0, iterProperty, temp);
	}
	for (unsigned iterProperty = 0; iterProperty < (unsigned) CAMERA_PROPERTY_LENGTH; ++iterProperty) {
		mxFree((void *) propertyNames[iterProperty]);
	}
	mxFree((void *) propertyNames);
}

void setCameraProperty(const cri_CameraHandle handle, \
							const char* propertyName, \
							const mxArray* mxarr) {

	cri_ErrorCode errorCode;
	double val = mxGetScalar(mxarr);
	if(!strcasecmp(propertyName, "bitdepth")) {
		errorCode = cri_SetCameraBitDepth(handle, (cri_ECameraBitDepth) val);
	} else if(!strcasecmp(propertyName, "gain")) {
		errorCode = cri_SetCameraGain(handle, (cri_ECameraGain) val);
	} else if(!strcasecmp(propertyName, "exposure")) {
		errorCode = cri_SetCameraExposureMs(handle, (float) val);
	} else if(!strcasecmp(propertyName, "binning")) {
		errorCode = cri_SetCameraBinning(handle, (cri_ECameraBinning) val);
	} else if(!strcasecmp(propertyName, "offset")) {
		errorCode = cri_SetCameraOffset(handle, (int) val);
	} else {
		errorCode = cri_NoError;
		mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported camera property: %s.", propertyName);
	}
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
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

void getFilterProperty(const cri_FilterHandle handle, \
							const char* propertyName, \
							mxArray* mxarr) {

	cri_ErrorCode errorCode;
	if (!strcasecmp(propertyName, "serial")) {
		int serial;
		float lowWavelengthRange;
		float highWavelengthRange;
		int waveplateStages;
		int firmware;
		errorCode = cri_GetFilterDescription(handle, &serial, \
										&lowWavelengthRange, &highWavelengthRange, \
										&waveplateStages, &firmware);
		mxarr = mxCreateDoubleScalar((double) serial);
	} else if (!strcasecmp(propertyName, "firmware")) {
		int serial;
		float lowWavelengthRange;
		float highWavelengthRange;
		int waveplateStages;
		int firmware;
		errorCode = cri_GetFilterDescription(handle, &serial, \
										&lowWavelengthRange, &highWavelengthRange, \
										&waveplateStages, &firmware);
		mxarr = mxCreateDoubleScalar((double) firmware);
	} else if(!strcasecmp(propertyName, "range")) {
		float lowWavelengthRange;
		float highWavelengthRange;
		float stepSize;
		errorCode = cri_GetFilterRangeAndStepSize(handle, &lowWavelengthRange, \
												&highWavelengthRange, &stepSize);
		mxarr = mxCreateDoubleMatrix(2, 1, mxREAL);
		double *data = (double *) mxGetData(mxarr);
		data[0] = (double) lowWavelengthRange;
		data[1] = (double) highWavelengthRange;
	} else if(!strcasecmp(propertyName, "stepsize")) {
		float lowWavelengthRange;
		float highWavelengthRange;
		float stepSize;
		errorCode = cri_GetFilterRangeAndStepSize(handle, &lowWavelengthRange, \
												&highWavelengthRange, &stepSize);
		mxarr = mxCreateDoubleScalar((double) stepSize);
	} else if(!strcasecmp(propertyName, "wavelength")) {
		cri_FilterState filterState;
		filterState.reserved[0] = 0.0f;
		filterState.reserved[1] = 0.0f;
		errorCode = cri_GetFilterState(handle, &filterState);
		mxarr = mxCreateDoubleScalar((double) filterState.wavelength);
	} else {
		errorCode = cri_NoError;
		mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported filter property: %s.", propertyName);
	}
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
	}
}

void getFilterProperties(const cri_FilterHandle handle, mxArray* mxstruct) {

	char **propertyNames = (char **) \
			mxMalloc((size_t) FILTER_PROPERTY_LENGTH * sizeof(*propertyNames));
	for (unsigned iterProperty = 0; iterProperty < (unsigned) FILTER_PROPERTY_LENGTH; ++iterProperty) {
		propertyNames[iterProperty] = (char *) mxMalloc(cri_MAX_STRING_LENGTH * sizeof(char));
		filterPropertyToString((FILTER_PROPERTY) iterProperty, propertyNames[iterProperty]);
	}
	mxstruct = mxCreateStructMatrix(1, 1, (unsigned) FILTER_PROPERTY_LENGTH, (const char **) propertyNames);
	mxArray *temp = NULL;
	for (unsigned iterProperty = 0; iterProperty < (unsigned) FILTER_PROPERTY_LENGTH; ++iterProperty) {
		getFilterProperty(handle, propertyNames[iterProperty], temp);
		mxSetFieldByNumber(mxstruct, 0, iterProperty, temp);
	}
	for (unsigned iterProperty = 0; iterProperty < (unsigned) FILTER_PROPERTY_LENGTH; ++iterProperty) {
		mxFree((void *) propertyNames[iterProperty]);
	}
	mxFree((void *) propertyNames);
}

void setFilterProperty(const cri_FilterHandle handle, \
							const char* propertyName, \
							const mxArray* mxarr) {

	cri_ErrorCode errorCode;
	double val = mxGetScalar(mxarr);
	if(!strcasecmp(propertyName, "wavelength")) {
		cri_FilterState filterState;
		filterState.wavelength = (double) val;
		filterState.reserved[0] = 0.0f;
		filterState.reserved[1] = 0.0f;
		errorCode = cri_SetFilterState(handle, filterState, true);
	} else {
		errorCode = cri_NoError;
		mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported filter property: %s.", propertyName);
	}
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
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
	} else if (numCameras < 0) {
		mexErrMsgIdAndTxt(ERROR_ID, "No available camera found.");
		return cri_InvalidCameraHandle;
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

//CAMERA_STATUS checkCamera(const cri_CameraHandle handle);

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
	} else if (numFilters < 0) {
		mexErrMsgIdAndTxt(ERROR_ID, "No available filter found.");
		return cri_InvalidFilterHandle;
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

void closeFilter(cri_FilterHandle handle) {
	cri_ErrorCode errorCode = cri_CloseFilter(&handle);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
	}
}

}	/* namespace nuance */
