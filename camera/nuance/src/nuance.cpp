/* temp.cpp
 *
 *  Created on: May 22, 2012
 *      Author: igkiou
 */

#include <iostream>
#include "nuance.h"

namespace ph {

mxArray* getCameraProperty(const cri_CameraHandle handle, \
							const PH_PROPERTY property) {

	switch(property) {
		case PH_NAME:
		{
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
		}
		case PH_SERIAL:
		{
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
		}
		case PH_DRIVER:
		{
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
		}
		case PH_FIRMWARE:
		{
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
		}
		case PH_SENSOR:
		{
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
		}
		case PH_SENSORSIZE:
		{
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
		}
		case PH_IMAGESIZE:
		{
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
		}
		case PH_MAXBITDEPTH:
		{
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
		}
		case PH_BITDEPTH:
		{
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
		}
		case PH_GAIN:
		{
			cri_ECameraGain gain;
			cri_ErrorCode errorCode = cri_GetCameraGain(handle, &gain);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
			}
			mxArray *mxarr = mxCreateDoubleScalar((double) gain);
			return mxarr;
		}
		case PH_EXPOSURERANGE:
		{
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
		}
		case PH_EXPOSURE:
		{
			float exposure;
			cri_ErrorCode errorCode = cri_GetCameraExposureMs(handle, &exposure);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
			}
			mxArray *mxarr = mxCreateDoubleScalar((double) exposure);
			return mxarr;
		}
		case PH_BINNING:
		{
			cri_ECameraBinning binning;
			cri_ErrorCode errorCode = cri_GetCameraBinning(handle, &binning);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
			}
			mxArray *mxarr = mxCreateDoubleScalar((double) binning);
			return mxarr;
		}
		case PH_OFFSETRANGE:
		{
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
		}
		case PH_OFFSET:
		{
			int offset;
			cri_ErrorCode errorCode = cri_GetCameraOffset(handle, &offset);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
			}
			mxArray *mxarr = mxCreateDoubleScalar((double) offset);
			return mxarr;
		}
		default:
		{
			char propertyName[cri_MAX_STRING_LENGTH];
			cameraPropertyToString(property, propertyName);
			mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported camera property: %s.", propertyName);
			return NULL;
		}
	}
}

mxArray* getCameraProperty(const cri_CameraHandle handle) {

	unsigned numProperties = (unsigned) PH_PROPERTY_LENGTH;
	mxArray *mxstruct;
	char **propertyNames = (char **) \
			mxMalloc(numProperties * sizeof(*propertyNames));
	for (unsigned iterProperty = 0; iterProperty < numProperties; ++iterProperty) {
		propertyNames[iterProperty] = (char *) mxMalloc(cri_MAX_STRING_LENGTH * sizeof(char));
		cameraPropertyToString((PH_PROPERTY) iterProperty, propertyNames[iterProperty]);
	}
	mxstruct = mxCreateStructMatrix(1, 1, numProperties, (const char **) propertyNames);
	for (unsigned iterProperty = 0; iterProperty < numProperties; ++iterProperty) {
		mxSetFieldByNumber(mxstruct, 0, iterProperty, getCameraProperty(handle, (PH_PROPERTY) iterProperty));
	}
	for (unsigned iterProperty = 0; iterProperty < numProperties; ++iterProperty) {
		mxFree((void *) propertyNames[iterProperty]);
	}
	mxFree((void *) propertyNames);
	return mxstruct;
}

void setCameraProperty(const cri_CameraHandle handle, \
							const PH_PROPERTY property, \
							const mxArray* mxarr) {

	double val = mxGetScalar(mxarr);
	switch(property) {
		case PH_BITDEPTH:
		{
			cri_ErrorCode errorCode = cri_SetCameraBitDepth(handle, (cri_ECameraBitDepth) val);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
			}
			break;
		}
		case PH_GAIN:
		{
			cri_ErrorCode errorCode = cri_SetCameraGain(handle, (cri_ECameraGain) val);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
			}
			break;
		}
		case PH_EXPOSURE:
		{
			cri_ErrorCode errorCode = cri_SetCameraExposureMs(handle, (float) val);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
			}
			break;
		}
		case PH_BINNING:
		{
			cri_ErrorCode errorCode = cri_SetCameraBinning(handle, (cri_ECameraBinning) val);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
			}
			break;
		}
		case PH_OFFSET:
		{
			cri_ErrorCode errorCode = cri_SetCameraOffset(handle, (int) val);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
			}
			break;
		}
		default:
		{
			char propertyName[cri_MAX_STRING_LENGTH];
			cameraPropertyToString(property, propertyName);
			mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported camera property: %s.", propertyName);
		}
	}
}

void setCameraProperty(const cri_CameraHandle handle, const mxArray* mxstruct) {

	if (mxIsStruct(mxstruct)) {
		unsigned numProperties = mxGetNumberOfFields(mxstruct);
		for (unsigned iterProperty = 0; iterProperty < numProperties; ++iterProperty) {
			setCameraProperty(handle, stringToCameraProperty(mxGetFieldNameByNumber(mxstruct, iterProperty)), \
							mxGetFieldByNumber(mxstruct, 0, iterProperty));
		}
	} else if (!mxIsEmpty(mxstruct)) {
		mexErrMsgIdAndTxt(ERROR_ID, "For setting multiple attributes, a struct array must be provided.");
	}
}

mxArray* getFilterProperty(const cri_FilterHandle handle, \
							const FILTER_PROPERTY property) {

	switch (property) {
		case FILTER_SERIAL:
		{
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
		}
		case FILTER_FIRMWARE:
		{
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
		}
		case FILTER_RANGE:
		{
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
		}
		case FILTER_STEPSIZE:
		{
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
		}
		case FILTER_WAVELENGTH:
		{
			cri_FilterState filterState;
			filterState.reserved[0] = 0.0f;
			filterState.reserved[1] = 0.0f;
			cri_ErrorCode errorCode = cri_GetFilterState(handle, &filterState);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
			}
			mxArray *mxarr = mxCreateDoubleScalar((double) filterState.wavelength);
			return mxarr;
		}
		default:
		{
			char propertyName[cri_MAX_STRING_LENGTH];
			filterPropertyToString(property, propertyName);
			mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported filter property: %s.", propertyName);
			return NULL;
		}
	}
}

mxArray* getFilterProperty(const cri_FilterHandle handle) {

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
		mxSetFieldByNumber(mxstruct, 0, iterProperty, getFilterProperty(handle, (FILTER_PROPERTY) iterProperty));
	}
	for (unsigned iterProperty = 0; iterProperty < numProperties; ++iterProperty) {
		mxFree((void *) propertyNames[iterProperty]);
	}
	mxFree((void *) propertyNames);
	return mxstruct;
}

void setFilterProperty(const cri_FilterHandle handle, \
							const FILTER_PROPERTY property, \
							const mxArray* mxarr) {

	double val = mxGetScalar(mxarr);
	switch (property) {
		case FILTER_WAVELENGTH:
		{
			cri_FilterState filterState;
			filterState.wavelength = (float) val;
			filterState.reserved[0] = 0.0f;
			filterState.reserved[1] = 0.0f;
			cri_ErrorCode errorCode = cri_SetFilterState(handle, filterState, true);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
			}
			break;
		}
		default:
		{
			char propertyName[cri_MAX_STRING_LENGTH];
			filterPropertyToString(property, propertyName);
			mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported filter property: %s.", propertyName);
		}
	}
}

void setFilterProperty(const cri_FilterHandle handle, const mxArray* mxstruct) {

	if (mxIsStruct(mxstruct)) {
		unsigned numProperties = mxGetNumberOfFields(mxstruct);
		for (unsigned iterProperty = 0; iterProperty < numProperties; ++iterProperty) {
			setFilterProperty(handle, stringToFilterProperty(mxGetFieldNameByNumber(mxstruct, iterProperty)), \
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

// TODO: This gives different results from software.
// TODO: Maybe add version for cube?
mxArray* getAutoExposure(const cri_CameraHandle cameraHandle, \
						const cri_FilterHandle filterHandle, \
						const double *wavelengths, \
						const unsigned numWavelengths) {
	cri_AutoExposeParameters parameters;
	parameters.rule = cri_AutoExposeRuleBrightest;
	parameters.targetRatioFullScale = 1.0f;
	cri_ErrorCode errorCode;
	errorCode = cri_GetCameraExposureRangeMs(cameraHandle, \
												&(parameters.minExposureMs), \
												&(parameters.maxExposureMs));
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
		return NULL;
	}

//	TODO: Check if these should be 1 or 0, and sensor or image dims.
	parameters.roiOriginX = 0;
	parameters.roiOriginY = 0;
	errorCode = cri_GetCameraImageSize(cameraHandle, &(parameters.roiWidth), \
									&(parameters.roiHeight));

	parameters.minAcceptableRatioFullScale = 0.0f;
	parameters.maxAcceptableRatioFullScale = 0.0f;

	float *exposureTimesFloat = new float[numWavelengths];
	cri_FilterState filterState;
	for (unsigned wavelengthIndex = 0; wavelengthIndex < numWavelengths; \
			++wavelengthIndex) {
		filterState.wavelength = (float) wavelengths[wavelengthIndex];
		filterState.reserved[0] = 0.0f;
		filterState.reserved[1] = 0.0f;
		errorCode = cri_SetFilterState(filterHandle, filterState, true);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
			return NULL;
		}
		errorCode = cri_AutoExposePlane(cameraHandle, filterHandle, parameters, \
										&exposureTimesFloat[wavelengthIndex]);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
			return NULL;
		}
	}

	mxArray *mxarr = mxCreateDoubleMatrix(numWavelengths, 1, mxREAL);
	double *mxarrData = (double *) mxGetPr(mxarr);
	for (unsigned wavelengthIndex = 0; wavelengthIndex < numWavelengths; \
				++wavelengthIndex) {
		mxarrData[wavelengthIndex] = (double) exposureTimesFloat[wavelengthIndex];
	}
	delete [] exposureTimesFloat;
	return mxarr;
}


void errorCallback(cri_ErrorCode errorCode) {
	mexPrintf("errorCallback: %d\n.", errorCode);
}

void captureInt8Callback(cri_Int8Image images, cri_Int8Image planarImage, \
					cri_FilterState filterStates[], float exposureTimesMs[], \
					unsigned int curImage, unsigned int totalToAcquire, \
					unsigned int framesToAverage) {

	mexPrintf("Uint8 im. %u/%u, wavelength %f nm, exp. time %f ms.\n", \
			curImage + 1, totalToAcquire, images.wavelengths[curImage], exposureTimesMs[curImage]);
}

void captureInt16Callback(cri_Int16Image images, cri_Int16Image planarImage, \
					cri_FilterState filterStates[], float exposureTimesMs[], \
					unsigned int curImage, unsigned int totalToAcquire, \
					unsigned int framesToAverage) {

	mexPrintf("Uint16 im. %u/%u, wavelength %f nm, exp. time %f ms.\n", \
			curImage + 1, totalToAcquire, images.wavelengths[curImage], exposureTimesMs[curImage]);
}

// TODO: Maybe write separate for single capture?
mxArray* capture(const cri_CameraHandle cameraHandle, \
				const cri_FilterHandle filterHandle, \
				const double *wavelengths, const double *exposureTimes, \
				const unsigned numWavelengths) {

	int width;
	int height;
	cri_ErrorCode errorCode;
	errorCode = cri_GetCameraImageSize(cameraHandle, &width, &height);
	if (errorCode != cri_NoError){
		handleErrorCode(errorCode);
		return NULL;
	}

	cri_FilterState *filterStates = new cri_FilterState[numWavelengths];
	float *exposureTimesFloat = new float[numWavelengths];

	for (unsigned wavelengthIndex = 0; wavelengthIndex < numWavelengths; \
		++wavelengthIndex) {
		filterStates[wavelengthIndex].wavelength = (float) wavelengths[wavelengthIndex];
		filterStates[wavelengthIndex].reserved[0] = 0.0f;
		filterStates[wavelengthIndex].reserved[1] = 0.0f;
		exposureTimesFloat[wavelengthIndex] = (float) exposureTimes[wavelengthIndex];
	}

	cri_ECameraBitDepth bitDepth;
	errorCode = cri_GetCameraBitDepth(cameraHandle, &bitDepth);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
		return NULL;
	}

	if (bitDepth == cri_CameraBitDepth8) {
		cri_Int8Image cube;
		cube.width = width;
		cube.height = height;
		cube.image = new unsigned char[width * height * numWavelengths];
//		cube.image = (unsigned char *) mxGetData(mxarr);
		cube.numberOfChannels = numWavelengths;
		cube.wavelengths = new float[numWavelengths];

		errorCode= cri_AcquireInt8Cube(cameraHandle, filterHandle, cube, \
									filterStates, exposureTimesFloat, \
									numWavelengths, \
									CUBE_ACQUIRE_FRAMES_TO_AVERAGE,
									true, NULL, errorCallback);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
			return NULL;
		}

		mxArray *mxarr;
		if (numWavelengths > 1) {
			const mwSize ndims = 3;
			const mwSize dims[]={height, width, numWavelengths};
			mxarr = mxCreateNumericArray(ndims, dims, mxUINT8_CLASS, mxREAL);
		} else {
			mxarr = mxCreateNumericMatrix(height, width, mxUINT8_CLASS, mxREAL);
		}
		unsigned char *mxarrData = (unsigned char *) mxGetData(mxarr);

		for (int iterWavelength = 0; iterWavelength < (int) numWavelengths; ++iterWavelength) {
			unsigned char *currWavelengthData = &mxarrData[width * height * iterWavelength];
			for (int iterWidth = 0; iterWidth < width; ++iterWidth) {
				for (int iterHeight = 0; iterHeight < height; ++iterHeight) {
					currWavelengthData[height * iterWidth + iterHeight] = \
							cube.image[iterHeight * width + iterWidth];
				}
			}
		}

		delete [] cube.image;
		delete [] cube.wavelengths;
		delete [] filterStates;
		delete [] exposureTimesFloat;
		return mxarr;
	} else if (bitDepth == cri_CameraBitDepth12) {
		cri_Int16Image cube;
		cube.width = width;
		cube.height = height;
		cube.image = new short[width * height * numWavelengths];
		cube.numberOfChannels = numWavelengths;
		cube.wavelengths = new float[numWavelengths];

		errorCode= cri_AcquireInt16Cube(cameraHandle, filterHandle, cube, \
									filterStates, exposureTimesFloat, \
									numWavelengths, \
									CUBE_ACQUIRE_FRAMES_TO_AVERAGE,
									true, NULL, errorCallback);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
			return NULL;
		}

		mxArray *mxarr;
		if (numWavelengths > 1) {
			const mwSize ndims = 3;
			const mwSize dims[]={height, width, numWavelengths};
			mxarr = mxCreateNumericArray(ndims, dims, mxUINT16_CLASS, mxREAL);
		} else {
			mxarr = mxCreateNumericMatrix(height, width, mxUINT16_CLASS, mxREAL);
		}
		short *mxarrData = (short *) mxGetData(mxarr);
		for (int iterWavelength = 0; iterWavelength < (int) numWavelengths; ++iterWavelength) {
			short *currWavelengthData = &mxarrData[width * height * iterWavelength];
			for (int iterWidth = 0; iterWidth < width; ++iterWidth) {
				for (int iterHeight = 0; iterHeight < height; ++iterHeight) {
					currWavelengthData[height * iterWidth + iterHeight] = \
							cube.image[iterWavelength \
							          + iterWidth * numWavelengths \
							          + iterHeight * width * numWavelengths];
				}
			}
		}

		delete [] cube.image;
		delete [] cube.wavelengths;
		delete [] filterStates;
		delete [] exposureTimesFloat;
		return mxarr;
	} else {
		mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported BITDEPTH: %d.", bitDepth);
		return NULL;
	}
}

typedef void (*cri_Int8StreamCallback) (cri_Int8Image image);

void streamInt8Callback(cri_Int8Image image) {

	mexPrintf("Uint8 single im., wavelength %f nm.\n", image.wavelengths[0]);
}

void streamInt16Callback(cri_Int16Image image) {

	mexPrintf("Uint16 single im., wavelength %f nm.\n", image.wavelengths[0]);
}

// TODO: Maybe write separate for single capture?
mxArray* captureSingle(const cri_CameraHandle cameraHandle, \
				const cri_FilterHandle filterHandle, \
				const double wavelength, const double exposureTime) {

	int width;
	int height;
	cri_ErrorCode errorCode;
	errorCode = cri_GetCameraImageSize(cameraHandle, &width, &height);
	if (errorCode != cri_NoError){
		handleErrorCode(errorCode);
		return NULL;
	}

	cri_FilterState filterState;
	filterState.wavelength = (float) wavelength;
	filterState.reserved[0] = 0.0f;
	filterState.reserved[1] = 0.0f;
	errorCode = cri_SetFilterState(filterHandle, filterState, true);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
	}

	errorCode = cri_SetCameraExposureMs(cameraHandle, (float) exposureTime);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
	}

	cri_ECameraBitDepth bitDepth;
	errorCode = cri_GetCameraBitDepth(cameraHandle, &bitDepth);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
		return NULL;
	}

	if (bitDepth == cri_CameraBitDepth8) {
		mxArray *mxarr = mxCreateNumericMatrix(width, height, mxUINT8_CLASS, mxREAL);

		cri_Int8Image image;
		image.width = width;
		image.height = height;
//		image.image = new unsigned char[width * height];
		image.image = (unsigned char *) mxGetData(mxarr);
		image.numberOfChannels = 1;
		image.wavelengths = new float;

		errorCode= cri_SnapInt8(cameraHandle, &image, true, NULL);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
			return NULL;
		}

		delete image.wavelengths;
		return mxarr;
	} else if (bitDepth == cri_CameraBitDepth12) {
		mxArray *mxarr = mxCreateNumericMatrix(width, height, mxUINT16_CLASS, mxREAL);

		cri_Int16Image image;
		image.width = width;
		image.height = height;
//		image.image = new short[width * height];
		image.image = (short *) mxGetData(mxarr);
		image.numberOfChannels = 1;
		image.wavelengths = new float;

		errorCode= cri_SnapInt16(cameraHandle, &image, true, NULL);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
			return NULL;
		}

		delete image.wavelengths;
		return mxarr;
	} else {
		mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported BITDEPTH: %d.", bitDepth);
		return NULL;
	}
}

mxArray* snap(const cri_CameraHandle cameraHandle) {

	int width;
	int height;
	cri_ErrorCode errorCode;
	errorCode = cri_GetCameraImageSize(cameraHandle, &width, &height);
	if (errorCode != cri_NoError){
		handleErrorCode(errorCode);
		return NULL;
	}

	cri_ECameraBitDepth bitDepth;
	errorCode = cri_GetCameraBitDepth(cameraHandle, &bitDepth);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
		return NULL;
	}

	if (bitDepth == cri_CameraBitDepth8) {
		mxArray *mxarr = mxCreateNumericMatrix(width, height, mxUINT8_CLASS, mxREAL);

		cri_Int8Image image;
		image.width = width;
		image.height = height;
//		image.image = new unsigned char[width * height];
		image.image = (unsigned char *) mxGetData(mxarr);
		image.numberOfChannels = 1;
		image.wavelengths = new float;

		errorCode= cri_SnapInt8(cameraHandle, &image, true, NULL);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
			return NULL;
		}

		delete image.wavelengths;
		return mxarr;
	} else if (bitDepth == cri_CameraBitDepth12) {
		mxArray *mxarr = mxCreateNumericMatrix(width, height, mxUINT16_CLASS, mxREAL);

		cri_Int16Image image;
		image.width = width;
		image.height = height;
//		image.image = new short[width * height];
		image.image = (short *) mxGetData(mxarr);
		image.numberOfChannels = 1;
		image.wavelengths = new float;

		errorCode= cri_SnapInt16(cameraHandle, &image, true, NULL);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
			return NULL;
		}

		delete image.wavelengths;
		return mxarr;
	} else {
		mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported BITDEPTH: %d.", bitDepth);
		return NULL;
	}
}

mxArray* snapFrames(const cri_CameraHandle cameraHandle, const unsigned numFrames) {

	int width;
	int height;
	cri_ErrorCode errorCode;
	errorCode = cri_GetCameraImageSize(cameraHandle, &width, &height);
	if (errorCode != cri_NoError){
		handleErrorCode(errorCode);
		return NULL;
	}

	cri_ECameraBitDepth bitDepth;
	errorCode = cri_GetCameraBitDepth(cameraHandle, &bitDepth);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
		return NULL;
	}

	if (bitDepth == cri_CameraBitDepth8) {
		const mwSize ndims = 3;
		const mwSize dims[]={width, height, numFrames};
		mxArray *mxarr = mxCreateNumericArray(ndims, dims, mxUINT8_CLASS, mxREAL);
		unsigned char *mxdata = (unsigned char *) mxGetData(mxarr);

		cri_Int8Image image;
		image.width = width;
		image.height = height;
//		image.image = new unsigned char[width * height];
		image.numberOfChannels = 1;
		image.wavelengths = new float;

		for (unsigned iterFrame = 0; iterFrame < numFrames; ++iterFrame) {
			image.image = &mxdata[iterFrame * width * height];
			errorCode= cri_SnapInt8(cameraHandle, &image, true, NULL);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
				return NULL;
			}
		}

		delete image.wavelengths;
		return mxarr;
	} else if (bitDepth == cri_CameraBitDepth12) {
		const mwSize ndims = 3;
		const mwSize dims[]={width, height, numFrames};
		mxArray *mxarr = mxCreateNumericArray(ndims, dims, mxUINT16_CLASS, mxREAL);
		short *mxdata = (short *) mxGetData(mxarr);

		cri_Int16Image image;
		image.width = width;
		image.height = height;
//		image.image = new short[width * height];
		image.image = (short *) mxGetData(mxarr);
		image.numberOfChannels = 1;
		image.wavelengths = new float;

		for (unsigned iterFrame = 0; iterFrame < numFrames; ++iterFrame) {
			image.image = &mxdata[iterFrame * width * height];
			errorCode= cri_SnapInt16(cameraHandle, &image, true, NULL);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
				return NULL;
			}
		}

		delete image.wavelengths;
		return mxarr;
	} else {
		mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported BITDEPTH: %d.", bitDepth);
		return NULL;
	}
}

void snapPreAlloc(const cri_CameraHandle cameraHandle, const mxArray *mxarr) {

	int width;
	int height;
	cri_ErrorCode errorCode;
	errorCode = cri_GetCameraImageSize(cameraHandle, &width, &height);
	if (errorCode != cri_NoError){
		handleErrorCode(errorCode);
		return;
	}

	cri_ECameraBitDepth bitDepth;
	errorCode = cri_GetCameraBitDepth(cameraHandle, &bitDepth);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
		return;
	}

	if (bitDepth == cri_CameraBitDepth8) {
		cri_Int8Image image;
		image.width = width;
		image.height = height;
//		image.image = new unsigned char[width * height];
		image.image = (unsigned char *) mxGetData(mxarr);
		image.numberOfChannels = 1;
		image.wavelengths = new float;

		errorCode= cri_SnapInt8(cameraHandle, &image, true, NULL);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
			return;
		}

		delete image.wavelengths;
	} else if (bitDepth == cri_CameraBitDepth12) {
		cri_Int16Image image;
		image.width = width;
		image.height = height;
//		image.image = new short[width * height];
		image.image = (short *) mxGetData(mxarr);
		image.numberOfChannels = 1;
		image.wavelengths = new float;

		errorCode= cri_SnapInt16(cameraHandle, &image, true, NULL);
		if (errorCode != cri_NoError) {
			handleErrorCode(errorCode);
			return;
		}

		delete image.wavelengths;
	} else {
		mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported BITDEPTH: %d.", bitDepth);
		return;
	}
}

void snapPreAllocFrames(const cri_CameraHandle cameraHandle, const mxArray *mxarr,
						const unsigned numFrames) {

	int width;
	int height;
	cri_ErrorCode errorCode;
	errorCode = cri_GetCameraImageSize(cameraHandle, &width, &height);
	if (errorCode != cri_NoError){
		handleErrorCode(errorCode);
		return;
	}

	cri_ECameraBitDepth bitDepth;
	errorCode = cri_GetCameraBitDepth(cameraHandle, &bitDepth);
	if (errorCode != cri_NoError) {
		handleErrorCode(errorCode);
		return;
	}

	if (bitDepth == cri_CameraBitDepth8) {
		cri_Int8Image image;
		image.width = width;
		image.height = height;
//		image.image = new unsigned char[width * height];
		image.numberOfChannels = 1;
		image.wavelengths = new float;

		unsigned char *mxdata = (unsigned char *) mxGetData(mxarr);

		for (unsigned iterFrame = 0; iterFrame < numFrames; ++iterFrame) {
			image.image = &mxdata[iterFrame * width * height];
			errorCode= cri_SnapInt8(cameraHandle, &image, true, NULL);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
				return;
			}
		}

		delete image.wavelengths;
	} else if (bitDepth == cri_CameraBitDepth12) {
		cri_Int16Image image;
		image.width = width;
		image.height = height;
//		image.image = new short[width * height];
		image.numberOfChannels = 1;
		image.wavelengths = new float;

		short *mxdata = (short *) mxGetData(mxarr);

		for (unsigned iterFrame = 0; iterFrame < numFrames; ++iterFrame) {
			image.image = &mxdata[iterFrame * width * height];
			errorCode= cri_SnapInt16(cameraHandle, &image, true, NULL);
			if (errorCode != cri_NoError) {
				handleErrorCode(errorCode);
				return;
			}
		}

		delete image.wavelengths;
	} else {
		mexErrMsgIdAndTxt(ERROR_ID, "Unknown or unsupported BITDEPTH: %d.", bitDepth);
		return;
	}
}

}	/* namespace nuance */
