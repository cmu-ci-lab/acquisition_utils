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

enum {canon_MAX_STRING_LENGTH=128};

/*
 * Replace all casts to static_cast.
 */
const char * const ERROR_ID = "MATLAB:canon_mex";

typedef enum CAMERA_PROPERTY {
	CAMERA_AEMODE = 0,
	CAMERA_DRIVEMODE = 1,
	CAMERA_IMAGEQUALITY = 2,
	CAMERA_ISOSPEED = 3,
	CAMERA_APERTUREVALUE = 4,
	CAMERA_SHUTTERSPEED = 5,
	CAMERA_EVFOUTPUTDEVICE = 6,
	CAMERA_EVFMODE = 7,
	CAMERA_SAVETO = 8,
	CAMERA_AVAILABLESHOTS = 9,
	CAMERA_PROPERTY_LENGTH = 10,
	CAMERA_PROPERTY_INVALID = -1
} CAMERA_PROPERTY;

/*
 * TODO: Find better way to do these conversions, perhaps using bimap.
 */
inline void cameraPropertyToString(const CAMERA_PROPERTY property, \
								char *propertyName) {
	switch (property) {
		case CAMERA_AEMODE: { strcpy(propertyName, "aemode"); return; }
		case CAMERA_DRIVEMODE: { strcpy(propertyName, "drivemode"); return; }
		case CAMERA_IMAGEQUALITY: { strcpy(propertyName, "imagequality"); return; }
		case CAMERA_ISOSPEED: { strcpy(propertyName, "isospeed"); return; }
		case CAMERA_APERTUREVALUE: { strcpy(propertyName, "aperturevalue"); return; }
		case CAMERA_SHUTTERSPEED: { strcpy(propertyName, "shutterspeed"); return; }
		case CAMERA_EVFOUTPUTDEVICE: { strcpy(propertyName, "evfoutputdevice"); return; }
		case CAMERA_EVFMODE: { strcpy(propertyName, "evfmode"); return; }
		case CAMERA_SAVETO: { strcpy(propertyName, "saveto"); return; }
		case CAMERA_AVAILABLESHOTS: { strcpy(propertyName, "availableshots"); return; }
		default: { strcpy(propertyName, "unknown"); return; }
	}
}

inline CAMERA_PROPERTY stringToCameraProperty(const char *propertyName) {
	if(!strcasecmp(propertyName, "aemode")) {
		return CAMERA_AEMODE;
	}else if(!strcasecmp(propertyName, "drivemode")) {
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
	} else if(!strcasecmp(propertyName, "saveto")) {
		return CAMERA_SAVETO;
	} else {
		return CAMERA_PROPERTY_INVALID;
	}
}

inline EdsUInt32 AEModeDoubleToEds(const double AEModeDouble) {
	if (AEModeDouble == 1) {
		return kEdsAEMode_Tv;
	} else if (AEModeDouble == 2) {
		return kEdsAEMode_Av;
	} else if (AEModeDouble == 3) {
		return kEdsAEMode_Manual;
	} else {
		return kEdsAEMode_Unknown;
	}
}

inline double AEModeEdsToDouble(const EdsUInt32 AEMode) {
	if (AEMode == kEdsAEMode_Tv) {
		return 1;
	} else if (AEMode == kEdsAEMode_Av) {
		return 2;
	} else if (AEMode == kEdsAEMode_Manual) {
		return 3;
	} else {
		return -1;
	}
}

inline EdsUInt32 driveModeDoubleToEds(const double driveModeDouble) {
	if (driveModeDouble == 0) { /* single-frame shooting */
		return 0x00000000;
	} else if (driveModeDouble == 1) { /* continuous shooting */
		return 0x00000001;
	} else if (driveModeDouble == 4) { /* high-speed continuous shooting */
		return 0x00000004;
	} else if (driveModeDouble == 5) { /* low-speed continuous shooting */
		return 0x00000005;
	} else if (driveModeDouble == 6) { /* silent single shooting */
		return 0x00000006;
	} else {
		return 0xffffffff;
	}
}

inline double driveModeEdsToDouble(const EdsUInt32 driveMode) {
	if (driveMode == 0x00000000) { /* single-frame shooting */
		return 0;
	} else if (driveMode == 0x00000001) { /* continuous shooting */
		return 1;
	} else if (driveMode == 0x00000004) { /* high-speed continuous shooting */
		return 4;
	} else if (driveMode == 0x00000005) { /* low-speed continuous shooting */
		return 5;
	} else if (driveMode == 0x00000006) { /* silent single shooting */
		return 6;
	} else {
		return -1;
	}
}

inline EdsUInt32 imageQualityDoubleToEds(const double imageQualityDouble) {
	if (imageQualityDouble == 0) { /* RAW only */
		return EdsImageQuality_LR;
	} else if (imageQualityDouble == 1) { /* Jpeg Large only */
		return EdsImageQuality_LJ;
	} else if (imageQualityDouble == 2) { /* RAW + Jpeg Large */
		return EdsImageQuality_LRLJ;
	} else {
		return EdsImageQuality_Unknown;
	}
}

inline EdsUInt32 imageQualityEdsToDouble(const EdsUInt32 imageQuality) {
	if (imageQuality == EdsImageQuality_LR) { /* RAW only */
		return 0;
	} else if (imageQuality == EdsImageQuality_LJ) { /* Jpeg Large only */
		return 1;
	} else if (imageQuality == EdsImageQuality_LRLJ) { /* RAW + Jpeg Large */
		return 2;
	} else {
		return -1;
	}
}

inline EdsUInt32 isoSpeedDoubleToEds(const double isoSpeedDouble) {
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

inline double isoSpeedEdsToDouble(const EdsUInt32 isoSpeed) {
	if (isoSpeed == 0x00000000) {
		return 0;
	} else if (isoSpeed == 0x00000040) {
		return 50;
	} else if (isoSpeed == 0x00000048) {
		return 100;
	} else if (isoSpeed == 0x0000004b) {
		return 125;
	} else if (isoSpeed == 0x0000004d) {
		return 160;
	} else if (isoSpeed == 0x00000050) {
		return 200;
	} else if (isoSpeed == 0x00000053) {
		return 250;
	} else if (isoSpeed == 0x00000055) {
		return 320;
	} else if (isoSpeed == 0x00000058) {
		return 400;
	} else if (isoSpeed == 0x0000005b) {
		return 500;
	} else if (isoSpeed == 0x0000005d) {
		return 640;
	} else if (isoSpeed == 0x00000060) {
		return 800;
	} else if (isoSpeed == 0x00000063) {
		return 1000;
	} else if (isoSpeed == 0x00000065) {
		return 1250;
	} else if (isoSpeed == 0x00000068) {
		return 1600;
	} else if (isoSpeed == 0x0000006b) {
		return 2000;
	} else if (isoSpeed == 0x0000006d) {
		return 2500;
	} else if (isoSpeed == 0x00000070) {
		return 3200;
	} else if (isoSpeed == 0x00000073) {
		return 4000;
	} else if (isoSpeed == 0x00000075) {
		return 5000;
	} else if (isoSpeed == 0x00000078) {
		return 6400;
	} else if (isoSpeed == 0x0000007b) {
		return 8000;
	} else if (isoSpeed == 0x0000007d) {
		return 10000;
	} else if (isoSpeed == 0x00000080) {
		return 12800;
	} else if (isoSpeed == 0x00000088) {
		return 25600;
	} else if (isoSpeed == 0x00000090) {
		return 51200;
	} else if (isoSpeed == 0x00000098) {
		return 102400;
	} else {
		return -1;
	}
}

inline EdsUInt32 apertureValueDoubleToEds(const double apertureValueDouble) {
	if (apertureValueDouble == 1) {
		return 0x08;
	} else if (apertureValueDouble == 1.1) {
		return 0x0B;
	} else if (apertureValueDouble == 1.2) {
		return 0x0C;
	} else if (apertureValueDouble == 1.23) {
		return 0x0D;
	} else if (apertureValueDouble == 1.4) {
		return 0x10;
	} else if (apertureValueDouble == 1.6) {
		return 0x13;
	} else if (apertureValueDouble == 1.8) {
		return 0x14;
	} else if (apertureValueDouble == 1.83) {
		return 0x15;
	} else if (apertureValueDouble == 2) {
		return 0x18;
	} else if (apertureValueDouble == 2.2) {
		return 0x1B;
	} else if (apertureValueDouble == 2.5) {
		return 0x1C;
	} else if (apertureValueDouble == 2.53) {
		return 0x1D;
	} else if (apertureValueDouble == 2.8) {
		return 0x20;
	} else if (apertureValueDouble == 3.2) {
		return 0x23;
	} else if (apertureValueDouble == 3.5) {
		return 0x24;
	} else if (apertureValueDouble == 3.53) {
		return 0x25;
	} else if (apertureValueDouble == 4) {
		return 0x28;
	} else if (apertureValueDouble == 4.5) {
		return 0x2B;
	} else if (apertureValueDouble == 4.52) {
		return 0x2C;
	} else if (apertureValueDouble == 5.0) {
		return 0x2D;
	} else if (apertureValueDouble == 5.6) {
		return 0x30;
	} else if (apertureValueDouble == 6.3) {
		return 0x33;
	} else if (apertureValueDouble == 6.7) {
		return 0x34;
	} else if (apertureValueDouble == 7.1) {
		return 0x35;
	} else if (apertureValueDouble == 8) {
		return 0x38;
	} else if (apertureValueDouble == 9) {
		return 0x3B;
	} else if (apertureValueDouble == 9.5) {
		return 0x3C;
	} else if (apertureValueDouble == 10) {
		return 0x3D;
	} else if (apertureValueDouble == 11) {
		return 0x40;
	} else if (apertureValueDouble == 13) {
		return 0x44;
	} else if (apertureValueDouble == 133) {
		return 0x43;
	} else if (apertureValueDouble == 14) {
		return 0x45;
	} else if (apertureValueDouble == 16) {
		return 0x48;
	} else if (apertureValueDouble == 18) {
		return 0x4B;
	} else if (apertureValueDouble == 19) {
		return 0x4C;
	} else if (apertureValueDouble == 20) {
		return 0x4D;
	} else if (apertureValueDouble == 22) {
		return 0x50;
	} else if (apertureValueDouble == 25) {
		return 0x53;
	} else if (apertureValueDouble == 27) {
		return 0x54;
	} else if (apertureValueDouble == 29) {
		return 0x55;
	} else if (apertureValueDouble == 32) {
		return 0x58;
	} else if (apertureValueDouble == 36) {
		return 0x5B;
	} else if (apertureValueDouble == 38) {
		return 0x5C;
	} else if (apertureValueDouble == 40) {
		return 0x5D;
	} else if (apertureValueDouble == 45) {
		return 0x60;
	} else if (apertureValueDouble == 51) {
		return 0x63;
	} else if (apertureValueDouble == 54) {
		return 0x64;
	} else if (apertureValueDouble == 57) {
		return 0x65;
	} else if (apertureValueDouble == 64) {
		return 0x68;
	} else if (apertureValueDouble == 72) {
		return 0x6B;
	} else if (apertureValueDouble == 76) {
		return 0x6C;
	} else if (apertureValueDouble == 80) {
		return 0x6D;
	} else if (apertureValueDouble == 91) {
		return 0x70;
	} else {
		return 0xffffffff;
	}
}

inline double apertureValueEdsToDouble(const EdsUInt32 apertureValue) {
	if (apertureValue == 0x08) {
		return 1;
	} else if (apertureValue == 0x0B) {
		return 1.1;
	} else if (apertureValue == 0x0C) {
		return 1.2;
	} else if (apertureValue == 0x0D) {
		return 1.23;
	} else if (apertureValue == 0x10) {
		return 1.4;
	} else if (apertureValue == 0x13) {
		return 1.6;
	} else if (apertureValue == 0x14) {
		return 1.8;
	} else if (apertureValue == 0x15) {
		return 1.83;
	} else if (apertureValue == 0x18) {
		return 2;
	} else if (apertureValue == 0x1B) {
		return 2.2;
	} else if (apertureValue == 0x1C) {
		return 2.5;
	} else if (apertureValue == 0x1D) {
		return 2.53;
	} else if (apertureValue == 0x20) {
		return 2.8;
	} else if (apertureValue == 0x23) {
		return 3.2;
	} else if (apertureValue == 0x24) {
		return 3.5;
	} else if (apertureValue == 0x25) {
		return 3.53;
	} else if (apertureValue == 0x28) {
		return 4;
	} else if (apertureValue == 0x2B) {
		return 4.5;
	} else if (apertureValue == 0x2C) {
		return 4.52;
	} else if (apertureValue == 0x2D) {
		return 5.0;
	} else if (apertureValue == 0x30) {
		return 5.6;
	} else if (apertureValue == 0x33) {
		return 6.3;
	} else if (apertureValue == 0x34) {
		return 6.7;
	} else if (apertureValue == 0x35) {
		return 7.1;
	} else if (apertureValue == 0x38) {
		return 8;
	} else if (apertureValue == 0x3B) {
		return 9;
	} else if (apertureValue == 0x3C) {
		return 9.5;
	} else if (apertureValue == 0x3D) {
		return 10;
	} else if (apertureValue == 0x40) {
		return 11;
	} else if (apertureValue == 0x44) {
		return 13;
	} else if (apertureValue == 0x43) {
		return 133;
	} else if (apertureValue == 0x45) {
		return 14;
	} else if (apertureValue == 0x48) {
		return 16;
	} else if (apertureValue == 0x4B) {
		return 18;
	} else if (apertureValue == 0x4C) {
		return 19;
	} else if (apertureValue == 0x4D) {
		return 20;
	} else if (apertureValue == 0x50) {
		return 22;
	} else if (apertureValue == 0x53) {
		return 25;
	} else if (apertureValue == 0x54) {
		return 27;
	} else if (apertureValue == 0x55) {
		return 29;
	} else if (apertureValue == 0x58) {
		return 32;
	} else if (apertureValue == 0x5B) {
		return 36;
	} else if (apertureValue == 0x5C) {
		return 38;
	} else if (apertureValue == 0x5D) {
		return 40;
	} else if (apertureValue == 0x60) {
		return 45;
	} else if (apertureValue == 0x63) {
		return 51;
	} else if (apertureValue == 0x64) {
		return 54;
	} else if (apertureValue == 0x65) {
		return 57;
	} else if (apertureValue == 0x68) {
		return 64;
	} else if (apertureValue == 0x6B) {
		return 72;
	} else if (apertureValue == 0x6C) {
		return 76;
	} else if (apertureValue == 0x6D) {
		return 80;
	} else if (apertureValue == 0x70) {
		return 91;
	} else {
		return -1;
	}
}

inline EdsUInt32 shutterSpeedDoubleToEds(const double shutterSpeedDouble) {
	if (shutterSpeedDouble == 100) {
		return 0x0C;
	} else if (shutterSpeedDouble == 30) {
		return 0x10;
	} else if (shutterSpeedDouble == 25) {
		return 0x13;
	} else if (shutterSpeedDouble == 20.3) {
		return 0x15;
	} else if (shutterSpeedDouble == 20) {
		return 0x14;
	} else if (shutterSpeedDouble == 15) {
		return 0x18;
	} else if (shutterSpeedDouble == 13) {
		return 0x1B;
	} else if (shutterSpeedDouble == 10.3) {
		return 0x1D;
	} else if (shutterSpeedDouble == 10) {
		return 0x1C;
	} else if (shutterSpeedDouble == 8) {
		return 0x20;
	} else if (shutterSpeedDouble == 6.3) {
		return 0x23;
	} else if (shutterSpeedDouble == 6) {
		return 0x24;
	} else if (shutterSpeedDouble == 5) {
		return 0x25;
	} else if (shutterSpeedDouble == 4) {
		return 0x28;
	} else if (shutterSpeedDouble == 3.2) {
		return 0x2B;
	} else if (shutterSpeedDouble == 3) {
		return 0x2C;
	} else if (shutterSpeedDouble == 2.5) {
		return 0x2D;
	} else if (shutterSpeedDouble == 2) {
		return 0x30;
	} else if (shutterSpeedDouble == 1.6) {
		return 0x33;
	} else if (shutterSpeedDouble == 1.5) {
		return 0x34;
	} else if (shutterSpeedDouble == 1.3) {
		return 0x35;
	} else if (shutterSpeedDouble == 1) {
		return 0x38;
	} else if (shutterSpeedDouble == 0.8) {
		return 0x3B;
	} else if (shutterSpeedDouble == 0.7) {
		return 0x3C;
	} else if (shutterSpeedDouble == 0.6) {
		return 0x3D;
	} else if (shutterSpeedDouble == 0.5) {
		return 0x40;
	} else if (shutterSpeedDouble == 0.4) {
		return 0x43;
	} else if (shutterSpeedDouble == 0.33) {
		return 0x45;
	} else if (shutterSpeedDouble == 0.3) {
		return 0x44;
	} else if (shutterSpeedDouble == 0.25) {
		return 0x48;
	} else if (shutterSpeedDouble == 0.2) {
		return 0x4B;
	} else if (shutterSpeedDouble == 0.16663) {
		return 0x4D;
	} else if (shutterSpeedDouble == 0.1666) {
		return 0x4C;
	} else if (shutterSpeedDouble == 0.13) {
		return 0x53;
	} else if (shutterSpeedDouble == 0.125) {
		return 0x50;
	} else if (shutterSpeedDouble == 0.04) {
		return 0x5D;
	} else if (shutterSpeedDouble == 0.0333) {
		return 0x60;
	} else if (shutterSpeedDouble == 0.025) {
		return 0x63;
	} else if (shutterSpeedDouble == 0.0222) {
		return 0x64;
	} else if (shutterSpeedDouble == 0.02) {
		return 0x65;
	} else if (shutterSpeedDouble == 0.0167) {
		return 0x68;
	} else if (shutterSpeedDouble == 0.0125) {
		return 0x6B;
	} else if (shutterSpeedDouble == 0.0111) {
		return 0x6C;
	} else if (shutterSpeedDouble == 0.01) {
		return 0x6D;
	} else if (shutterSpeedDouble == 0.008) {
		return 0x70;
	} else if (shutterSpeedDouble == 0.0063) {
		return 0x73;
	} else if (shutterSpeedDouble == 0.0056) {
		return 0x74;
	} else if (shutterSpeedDouble == 0.005) {
		return 0x75;
	} else if (shutterSpeedDouble == 0.004) {
		return 0x78;
	} else if (shutterSpeedDouble == 0.0031) {
		return 0x7B;
	} else if (shutterSpeedDouble == 0.0029) {
		return 0x7C;
	} else if (shutterSpeedDouble == 0.0025) {
		return 0x7D;
	} else if (shutterSpeedDouble == 0.002) {
		return 0x80;
	} else if (shutterSpeedDouble == 0.0016) {
		return 0x83;
	} else if (shutterSpeedDouble == 0.00133) {
		return 0x84;
	} else if (shutterSpeedDouble == 0.00125) {
		return 0x85;
	} else if (shutterSpeedDouble == 0.001) {
		return 0x88;
	} else if (shutterSpeedDouble == 0.0008) {
		return 0x8B;
	} else if (shutterSpeedDouble == 0.000666) {
		return 0x8C;
	} else if (shutterSpeedDouble == 0.000625) {
		return 0x8D;
	} else if (shutterSpeedDouble == 0.0005) {
		return 0x90;
	} else if (shutterSpeedDouble == 0.0004) {
		return 0x93;
	} else if (shutterSpeedDouble == 0.000333) {
		return 0x94;
	} else if (shutterSpeedDouble == 0.0003125) {
		return 0x95;
	} else if (shutterSpeedDouble == 0.00025) {
		return 0x98;
	} else if (shutterSpeedDouble == 0.0002) {
		return 0x9B;
	} else if (shutterSpeedDouble == 0.0001666) {
		return 0x9C;
	} else if (shutterSpeedDouble == 0.00015625) {
		return 0x9D;
	} else if (shutterSpeedDouble == 0.000125) {
		return 0xA0;
	} else {
		return 0xffffffff;
	}
}

inline double shutterSpeedEdsToDouble(const EdsUInt32 shutterSpeed) {
	if (shutterSpeed == 0x0C) {
		return 100;
	} else if (shutterSpeed == 0x10) {
		return 30;
	} else if (shutterSpeed == 0x13) {
		return 25;
	} else if (shutterSpeed == 0x15) {
		return 20.3;
	} else if (shutterSpeed == 0x14) {
		return 20;
	} else if (shutterSpeed == 0x18) {
		return 15;
	} else if (shutterSpeed == 0x1B) {
		return 13;
	} else if (shutterSpeed == 0x1D) {
		return 10.3;
	} else if (shutterSpeed == 0x1C) {
		return 10;
	} else if (shutterSpeed == 0x20) {
		return 8;
	} else if (shutterSpeed == 0x23) {
		return 6.3;
	} else if (shutterSpeed == 0x24) {
		return 6;
	} else if (shutterSpeed == 0x25) {
		return 5;
	} else if (shutterSpeed == 0x28) {
		return 4;
	} else if (shutterSpeed == 0x2B) {
		return 3.2;
	} else if (shutterSpeed == 0x2C) {
		return 3;
	} else if (shutterSpeed == 0x2D) {
		return 2.5;
	} else if (shutterSpeed == 0x30) {
		return 2;
	} else if (shutterSpeed == 0x33) {
		return 1.6;
	} else if (shutterSpeed == 0x34) {
		return 1.5;
	} else if (shutterSpeed == 0x35) {
		return 1.3;
	} else if (shutterSpeed == 0x38) {
		return 1;
	} else if (shutterSpeed == 0x3B) {
		return 0.8;
	} else if (shutterSpeed == 0x3C) {
		return 0.7;
	} else if (shutterSpeed == 0x3D) {
		return 0.6;
	} else if (shutterSpeed == 0x40) {
		return 0.5;
	} else if (shutterSpeed == 0x43) {
		return 0.4;
	} else if (shutterSpeed == 0x45) {
		return 0.33;
	} else if (shutterSpeed == 0x44) {
		return 0.3;
	} else if (shutterSpeed == 0x48) {
		return 0.25;
	} else if (shutterSpeed == 0x4B) {
		return 0.2;
	} else if (shutterSpeed == 0x4D) {
		return 0.16663;
	} else if (shutterSpeed == 0x4C) {
		return 0.1666;
	} else if (shutterSpeed == 0x53) {
		return 0.13;
	} else if (shutterSpeed == 0x50) {
		return 0.125;
	} else if (shutterSpeed == 0x5D) {
		return 0.04;
	} else if (shutterSpeed == 0x60) {
		return 0.0333;
	} else if (shutterSpeed == 0x63) {
		return 0.025;
	} else if (shutterSpeed == 0x64) {
		return 0.0222;
	} else if (shutterSpeed == 0x65) {
		return 0.02;
	} else if (shutterSpeed == 0x68) {
		return 0.0167;
	} else if (shutterSpeed == 0x6B) {
		return 0.0125;
	} else if (shutterSpeed == 0x6C) {
		return 0.0111;
	} else if (shutterSpeed == 0x6D) {
		return 0.01;
	} else if (shutterSpeed == 0x70) {
		return 0.008;
	} else if (shutterSpeed == 0x73) {
		return 0.0063;
	} else if (shutterSpeed == 0x74) {
		return 0.0056;
	} else if (shutterSpeed == 0x75) {
		return 0.005;
	} else if (shutterSpeed == 0x78) {
		return 0.004;
	} else if (shutterSpeed == 0x7B) {
		return 0.0031;
	} else if (shutterSpeed == 0x7C) {
		return 0.0029;
	} else if (shutterSpeed == 0x7D) {
		return 0.0025;
	} else if (shutterSpeed == 0x80) {
		return 0.002;
	} else if (shutterSpeed == 0x83) {
		return 0.0016;
	} else if (shutterSpeed == 0x84) {
		return 0.00133;
	} else if (shutterSpeed == 0x85) {
		return 0.00125;
	} else if (shutterSpeed == 0x88) {
		return 0.001;
	} else if (shutterSpeed == 0x8B) {
		return 0.0008;
	} else if (shutterSpeed == 0x8C) {
		return 0.000666;
	} else if (shutterSpeed == 0x8D) {
		return 0.000625;
	} else if (shutterSpeed == 0x90) {
		return 0.0005;
	} else if (shutterSpeed == 0x93) {
		return 0.0004;
	} else if (shutterSpeed == 0x94) {
		return 0.000333;
	} else if (shutterSpeed == 0x95) {
		return 0.0003125;
	} else if (shutterSpeed == 0x98) {
		return 0.00025;
	} else if (shutterSpeed == 0x9B) {
		return 0.0002;
	} else if (shutterSpeed == 0x9C) {
		return 0.0001666;
	} else if (shutterSpeed == 0x9D) {
		return 0.00015625;
	} else if (shutterSpeed == 0xA0) {
		return 0.000125;
	} else {
		return -1;
	}
}

inline EdsUInt32 evfOutputDeviceDoubleToEds(const double evfOutputDeviceDouble) {
	if (evfOutputDeviceDouble == 1) { /* camera */
		return kEdsEvfOutputDevice_TFT;
	} else if (evfOutputDeviceDouble == 2) { /* PC */
		return kEdsEvfOutputDevice_PC;
	} else {
		return 0xffffffff;
	}
}

inline EdsUInt32 evfOutputDeviceEdsToDouble(const EdsUInt32 evfOutputDevice) {
	if (evfOutputDevice == kEdsEvfOutputDevice_TFT) { /* camera */
		return 1;
	} else if (evfOutputDevice == kEdsEvfOutputDevice_PC) { /* PC */
		return 2;
	} else {
		return -1;
	}
}

inline EdsUInt32 evfModeDoubleToEds(const double evfModeDouble) {
	if (evfModeDouble == 0) { /* off */
		return 0;
	} else if (evfModeDouble == 1) { /* on */
		return 1;
	} else {
		return 0xffffffff;
	}
}

inline EdsUInt32 evfModeEdsToDouble(const EdsUInt32 evfMode) {
	if (evfMode == 0) { /* off */
		return 0;
	} else if (evfMode == 1) { /* on */
		return 1;
	} else {
		return -1;
	}
}


inline EdsUInt32 saveToDoubleToEds(const double saveToDouble) {
	if (saveToDouble == 1) { /* camera */
		return kEdsSaveTo_Camera;
	} else if (saveToDouble == 2) { /* PC */
		return kEdsSaveTo_Host;
	} else if (saveToDouble == 3) { /* camera + PC */
		return kEdsSaveTo_Both;
	} else {
		return 0xffffffff;
	}
}


inline EdsUInt32 saveToEdsToDouble(const EdsUInt32 saveTo) {
	if (saveTo == kEdsSaveTo_Camera) { /* camera */
		return 1;
	} else if (saveTo == kEdsSaveTo_Host) { /* PC */
		return 2;
	} else if (saveTo == kEdsSaveTo_Both) { /* camera + PC */
		return 3;
	} else {
		return -1;
	}
}

inline EdsUInt32 availableShotsDoubleToEds(const double availableShotsDouble) {
	return (EdsUInt32) availableShotsDouble;
}

inline double availableShotsEdsToDouble(const EdsUInt32 availableShots) {
	return (double) availableShots;
}

typedef enum CAMERA_STATUS {
	CAMERA_READY = 0,
	CAMERA_BUSY = 1,
	CAMERA_STREAMING = 2,
	CAMERA_ACQUIRING = 3,
	CAMERA_STATUS_LENGTH = 4,
	CAMERA_STATUS_INVALID = -1
} CAMERA_STATUS;

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
//CAMERA_STATUS checkCamera(const EdsCameraRef handle);
void closeCamera(EdsCameraRef handle);

/* Do some actual acquisition. */
void snap(const EdsCameraRef handle);

void capture(const EdsCameraRef handle, \
			const double isoSpeed, const double apertureValue, \
			const double shutterSpeed);

void captureBracket(const EdsCameraRef handle, \
			const double *isoSpeeds, const double *apertureValues, \
			const double *shutterSpeeds, const unsigned bracketLength);

void pressShutter(const EdsCameraRef handle);

void releaseShutter(const EdsCameraRef handle);

}	/* namespace canon */

#endif /* CANON_MEX_H_ */
