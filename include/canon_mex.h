/*
 * canon_mex.h
 *
 *  Created on: Dec 17, 2013
 *      Author: igkiou
 */

#ifndef CANON_MEX_H_
#define CANON_MEX_H_

#include <math.h>
#include <string.h>

#include "EDSDK.h"
#include "EDSDKErrors.h"
#include "EDSDKTypes.h"

#include "mex.h"
#include "matrix.h"

namespace canon {

/*
 * Replace all casts to static_cast.
 */
const char * const ERROR_ID = "MATLAB:canon_mex";

typedef enum CAMERA_PROPERTY {
	CAMERA_DRIVEMODE = 0,
	CAMERA_IMAGEQUALITY = 1,
	CAMERA_ISOSPEED = 2,
	CAMERA_APERTUREVALUE = 3,
	CAMERA_SHUTTERSPEED = 4,
	CAMERA_EVFOUTPUTDEVICE = 5,
	CAMERA_EVFMODE = 6,
	CAMERA_PROPERTY_LENGTH = 7,
	CAMERA_PROPERTY_INVALID = -1
} CAMERA_PROPERTY;

/*
 * TODO: Find better way to do these conversions, perhaps using bimap.
 */
inline void cameraPropertyToString(const CAMERA_PROPERTY property, \
								char *propertyName) {

	switch (property) {
		case CAMERA_DRIVEMODE: { strcpy(propertyName, "drivemode"); return; }
		case CAMERA_IMAGEQUALITY: { strcpy(propertyName, "imagequality"); return; }
		case CAMERA_ISOSPEED: { strcpy(propertyName, "isospeed"); return; }
		case CAMERA_APERTUREVALUE: { strcpy(propertyName, "aperturevalue"); return; }
		case CAMERA_SHUTTERSPEED: { strcpy(propertyName, "shutterspeed"); return; }
		case CAMERA_EVFOUTPUTDEVICE: { strcpy(propertyName, "evfoutputdevice"); return; }
		case CAMERA_EVFMODE: { strcpy(propertyName, "evfmode"); return; }
		default: { strcpy(propertyName, "unknown"); return; }
	}
}

inline CAMERA_PROPERTY stringToCameraProperty(const char *propertyName) {

	if(!strcasecmp(propertyName, "drivemode")) {
		return CAMERA_DRIVEMODE;
	} else if(!strcasecmp(propertyName, "imagequality")) {
		return CAMERA_IMAGEQUALITY;
	} else if(!strcasecmp(propertyName, "isospeed")) {
		return CAMERA_ISOSPEED;
	} else if(!strcasecmp(propertyName, "aperturevalue")) {
		return CAMERA_APERTUREVALUE;
	} else if(!strcasecmp(propertyName, "shutterspeed")) {
		return CAMERA_SHUTTERSPEED;
	} else if(!strcasecmp(propertyName, "evfoutputdevide")) {
		return CAMERA_EVFOUTPUTDEVICE;
	} else if(!strcasecmp(propertyName, "evfmode")) {
		return CAMERA_EVFMODE;
	} else {
		return CAMERA_PROPERTY_INVALID;
	}
}

inline EdsUInt32 isoDoubleToEds(const double isoSpeedDouble) {
	if (isoSpeedDouble == 0) {
		return 0x00000000;
	} else if (isoSpeedDouble == 50) {
		return 0x00000040;
	} else if (isoSpeedDouble == 100) {
		return 0x00000048;
	} else if (isoSpeedDouble == 125) {
		return 0x0000004b;
	} else if (isoSpeedDouble == 160) {
		return 0x0000004d;
	} else if (isoSpeedDouble == 200) {
		return 0x00000050;
	} else if (isoSpeedDouble == 250) {
		return 0x00000053;
	} else if (isoSpeedDouble == 320) {
		return 0x00000055;
	} else if (isoSpeedDouble == 400) {
		return 0x00000058;
	} else if (isoSpeedDouble == 500) {
		return 0x0000005b;
	} else if (isoSpeedDouble == 640) {
		return 0x0000005d;
	} else if (isoSpeedDouble == 800) {
		return 0x00000060;
	} else if (isoSpeedDouble == 1000) {
		return 0x00000063;
	} else if (isoSpeedDouble == 1250) {
		return 0x00000065;
	} else if (isoSpeedDouble == 1600) {
		return 0x00000068;
	} else if (isoSpeedDouble == 2000) {
		return 0x0000006b;
	} else if (isoSpeedDouble == 2500) {
		return 0x0000006d;
	} else if (isoSpeedDouble == 3200) {
		return 0x00000070;
	} else if (isoSpeedDouble == 4000) {
		return 0x00000073;
	} else if (isoSpeedDouble == 5000) {
		return 0x00000075;
	} else if (isoSpeedDouble == 6400) {
		return 0x00000078;
	} else if (isoSpeedDouble == 8000) {
		return 0x0000007b;
	} else if (isoSpeedDouble == 10000) {
		return 0x0000007d;
	} else if (isoSpeedDouble == 12800) {
		return 0x00000080;
	} else if (isoSpeedDouble == 25600) {
		return 0x00000088;
	} else if (isoSpeedDouble == 51200) {
		return 0x00000090;
	} else if (isoSpeedDouble == 102400) {
		return 0x00000098;
	} else {
		return 0xffffffff;
	}
}

0x08
1
0x40
11
0x0B
1.1
0x43
13 (1/3)
0x0C
1.2
0x44
13
0x0D
1.2 (1/3)
0x45
14
0x10
1.4
0x48
16
0x13
1.6
0x4B
18
0x14
1.8
0x4C
19
0x15
1.8 (1/3)
0x4D
20
0x18
2
0x50
22
0x1B
2.2
0x53
25
0x1C
2.5
0x54
27
0x1D
2.5 (1/3)
0x55
29
0x20
2.8
0x58
32
0x23
3.2
0x5B
36
0x24
3.5
0x5C
38
0x25
3.5 (1/3)
0x5D
40
0x28
4
0x60
45
0x2B
4.5
0x63
51
0x2C
4.5
0x64
54
0x2D
5.0
0x65
57
0x30
5.6
0x68
64
0x33
6.3
0x6B
72
0x34
6.7
0x6C
76
0x35
7.1
0x6D
80
0x38
8
0x70
91
0x3B
9
0xffffffff
Not valid/no settings changes
0x3C
9.5
0x3D
10

typedef enum CAMERA_STATUS {
	CAMERA_READY = 0,
	CAMERA_BUSY = 1,
	CAMERA_STREAMING = 2,
	CAMERA_ACQUIRING = 3,
	CAMERA_STATUS_LENGTH = 4,
	CAMERA_STATUS_INVALID = -1
} CAMERA_STATUS;

/*
 * TODO: Maybe rewrite with cri_GetLastError?
 */
inline void handleErrorCode(const EdsError errorCode) {

	switch(errorCode) {
		case EDS_ERR_OK:
		{
			return;
		}
		default:
		{
			mexErrMsgIdAndTxt(ERROR_ID, "Error %X.", errorCode);
			return;
		}
	}
}

/*
 * TODO: Separate out name handling in case of multiple variants of
 * getters/setters (maybe move in mex?).
 */

/* Camera getters and setters. */
mxArray* getCameraProperty(const EdsCameraRef handle, \
						const CAMERA_PROPERTY property);

mxArray* getCameraProperty(const EdsCameraRef handle);

void setCameraProperty(const EdsCameraRef handle, \
					const CAMERA_PROPERTY property, \
					const mxArray* mxarr);

void setCameraProperty(const EdsCameraRef handle, const mxArray* mxstruct);

mxArray* getCameraPropertyInfo(const EdsCameraRef handle, \
						const CAMERA_PROPERTY property);

/*
 * TODO: Maybe rewrite access functions to also return void or mxArray*,
 * as in rest of interface? On the other hand, this would mean these can no
 * longer be used in the classes above.
 */

/* Camera access. */
unsigned queryCamera();
EdsCameraRef openCamera();
CAMERA_STATUS checkCamera(const EdsCameraRef handle);
void closeCamera(EdsCameraRef handle);

/* Do some actual acquisition. */
void capture(const EdsCameraRef handle, \
			const double isoSpeed, const double apertureValue, \
			const double shutterSpeed);

void captureBracket(const EdsCameraRef handle, \
			const double *isoSpeeds, const double *apertureValues, \
			const double *shutterSpeeds, const unsigned bracketLength);

void snap(const EdsCameraRef handle);

void pressShutter(const EdsCameraRef handle);

void releaseShutter(const EdsCameraRef handle);

}	/* namespace canon */

#endif /* CANON_MEX_H_ */
