/*
 * test.cpp
 *
 *  Created on: Dec 18, 2013
 *      Author: igkiou
 */

#include "EDSDK.h"
#include "EDSDKErrors.h"
#include "EDSDKTypes.h"
#include "canon_mex.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <unistd.h>
#include <windows.h>

EdsError getFirstCamera(EdsCameraRef *camera) {
	EdsError err = EDS_ERR_OK;
	EdsCameraListRef cameraList = NULL;
	EdsUInt32 count = 0;

	// Get camera list
	err = EdsGetCameraList(&cameraList);

	// Get number of cameras
	if (err == EDS_ERR_OK) {
		err = EdsGetChildCount(cameraList, &count);
		if (count == 0) {
			err = EDS_ERR_DEVICE_NOT_FOUND;
		}
	}
	std::cout << "Cameras found:" << count << std::endl;

	// Get first camera retrieved
	if (err == EDS_ERR_OK) {
		err = EdsGetChildAtIndex(cameraList , 0 , camera);
	}

	// Release camera list
	if (cameraList != NULL) {
		EdsRelease(cameraList);
		cameraList = NULL;
	}
	return err;
}
EdsError takePicture(EdsCameraRef camera) {
	return EdsSendCommand(camera, kEdsCameraCommand_TakePicture, 0);
}

EdsUInt32 getNumberOfFiles_sub(EdsDirectoryItemRef directoryItem) {

	EdsUInt32 numChildren;
	EdsGetChildCount(directoryItem, &numChildren);
	EdsDirectoryItemInfo directoryItemInfo;
	EdsGetDirectoryItemInfo(directoryItem, &directoryItemInfo);
//	printf("Now counting %s\n", directoryItemInfo.szFileName);
	EdsUInt32 numFiles = 0;
	EdsDirectoryItemRef childItem;
	EdsDirectoryItemInfo childItemInfo;
//	std::cout << "Number of children " << numChildren << std::endl;
	for (int iter = 0; iter < numChildren; ++iter) {
		EdsGetChildAtIndex(directoryItem, iter, &childItem);
		EdsGetDirectoryItemInfo(childItem, &childItemInfo);
//		printf("Now parsing %s\n", childItemInfo.szFileName);
		if (childItemInfo.isFolder == true) {
			numFiles += getNumberOfFiles_sub(childItem);
		} else {
			++numFiles;
		}
		EdsRelease(childItem);
	}
	return numFiles;
}

EdsUInt32 getNumberOfFiles(EdsCameraRef camera) {

	EdsVolumeRef volume;
	EdsGetChildAtIndex(camera, 0, &volume);
	EdsDirectoryItemRef dcim;
	EdsGetChildAtIndex(volume, 0 , &dcim);
	EdsUInt32 numFiles = getNumberOfFiles_sub(dcim);
	EdsRelease(dcim);
	EdsRelease(volume);
	return numFiles;
}

EdsError downloadImage(EdsDirectoryItemRef directoryItem) {
	EdsError err = EDS_ERR_OK;
	EdsStreamRef stream = NULL;

	// Get directory item information
	EdsDirectoryItemInfo dirItemInfo;
	err = EdsGetDirectoryItemInfo(directoryItem, & dirItemInfo);

	std::string str_path("C:\\Users\\igkiou\\img.cr2");
	const char* ch_dest = str_path.c_str();

	// Create file stream for transfer destination
	if (err == EDS_ERR_OK) {
//		err = EdsCreateFileStream(dirItemInfo.szFileName, kEdsFileCreateDisposition_CreateAlways, kEdsAccess_ReadWrite, &stream);
		err = EdsCreateFileStream(ch_dest, kEdsFileCreateDisposition_CreateAlways,kEdsAccess_ReadWrite, &stream);
	}

	// Download image
	if (err == EDS_ERR_OK) {
		err = EdsDownload(directoryItem, dirItemInfo.size, stream);
	}

	// Issue notification that download is complete
	if (err == EDS_ERR_OK) {
//		std::cout << "Download complete." << std::endl;
		err = EdsDownloadComplete(directoryItem);
	}

	// Release stream
	if ( stream != NULL) {
		EdsRelease(stream);
		stream = NULL;
	}
	return err;
}

EdsError EDSCALLBACK handleObjectEvent(EdsObjectEvent event, EdsBaseRef object,
									EdsVoid * context) {
	// do something
	switch(event) {
		case kEdsObjectEvent_DirItemRequestTransfer:
//			std::cout << "Downloading image" << std::endl;
			downloadImage(object);
			break;
		default:
//			std::cout << "Other event" << std::endl;
			break;
	}

	// Object must be released
	if (object) {
		EdsRelease(object);
	}
	return EDS_ERR_OK;
}

EdsError EDSCALLBACK handlePropertyEvent(EdsPropertyEvent event, EdsPropertyID property,
										EdsUInt32 inParam, EdsVoid * context) {
	// do something
	return EDS_ERR_OK;
}

EdsError EDSCALLBACK handleStateEvent(EdsStateEvent event, EdsUInt32 parameter,
									EdsVoid * context) {
	// do something
	return EDS_ERR_OK;
}

int main() {
	EdsError err = EDS_ERR_OK;
	EdsCameraRef camera = NULL;
	bool isSDKLoaded = false;

	// Initialize SDK
	err = EdsInitializeSDK();
	if (err == EDS_ERR_OK) {
		isSDKLoaded = true;
	}

	// Get first camera
	if (err == EDS_ERR_OK) {
		err = getFirstCamera (&camera);
	}

	// Set event handler
	if (err == EDS_ERR_OK) {
		err = EdsSetObjectEventHandler(camera, kEdsObjectEvent_All,
		handleObjectEvent, NULL);
	}

	// Set event handler
	if (err == EDS_ERR_OK) {
		err = EdsSetPropertyEventHandler(camera, kEdsPropertyEvent_All,
		handlePropertyEvent, NULL);
	}

	// Set event handler
	if (err == EDS_ERR_OK) {
		err = EdsSetCameraStateEventHandler(camera, kEdsStateEvent_All,
		handleStateEvent, NULL);
	}

	// Open session with camera
	if (err == EDS_ERR_OK) {
		err = EdsOpenSession(camera);
	}

	EdsUInt32 property;
	property = canon::AEModeDoubleToEds(3);
	err = EdsSetPropertyData(camera, kEdsPropID_AEMode, 0, sizeof(property), &property);
	err = EdsGetPropertyData(camera, kEdsPropID_AEMode, 0, sizeof(property), &property);
	if (err != EDS_ERR_OK) {
		std::cout << "error at property" << std::endl;
	} else {
		std::cout << "AE mode is set to " << canon::AEModeEdsToDouble(property) << " " << property;
		printf(" %X\n", property);
	}
	property = canon::driveModeDoubleToEds(4);
	err = EdsSetPropertyData(camera, kEdsPropID_DriveMode, 0, sizeof(property), &property);
	err = EdsGetPropertyData(camera, kEdsPropID_DriveMode, 0, sizeof(property), &property);
	if (err != EDS_ERR_OK) {
		std::cout << "error at property" << std::endl;
	} else {
		std::cout << "Drive mode is set to " << canon::driveModeEdsToDouble(property) << " " << property;
		printf(" %X\n", property);
	}
	property = canon::imageQualityDoubleToEds(0);
	err = EdsSetPropertyData(camera, kEdsPropID_ImageQuality, 0, sizeof(property), &property);
	err = EdsGetPropertyData(camera, kEdsPropID_ImageQuality, 0, sizeof(property), &property);
	if (err != EDS_ERR_OK) {
		std::cout << "error at property" << std::endl;
	} else {
		std::cout << "Image quality is set to " << canon::imageQualityEdsToDouble(property) << " " << property;
		printf(" %X\n", property);
	}
	property = canon::isoSpeedDoubleToEds(100);
	err = EdsSetPropertyData(camera, kEdsPropID_ISOSpeed, 0, sizeof(property), &property);
	err = EdsGetPropertyData(camera, kEdsPropID_ISOSpeed, 0, sizeof(property), &property);
	if (err != EDS_ERR_OK) {
		std::cout << "error at property" << std::endl;
	} else {
		std::cout << "ISO quality is set to " << canon::isoSpeedEdsToDouble(property) << " " << property;
		printf(" %X\n", property);
	}
	property = canon::apertureValueDoubleToEds(3.5);
	err = EdsSetPropertyData(camera, kEdsPropID_Av, 0, sizeof(property), &property);
	err = EdsGetPropertyData(camera, kEdsPropID_Av, 0, sizeof(property), &property);
	if (err != EDS_ERR_OK) {
		std::cout << "error at property" << std::endl;
	} else {
		std::cout << "Aperture value is set to " << canon::apertureValueEdsToDouble(property) << " " << property;
		printf(" %X\n", property);
	}
	property = canon::shutterSpeedDoubleToEds(1);
	err = EdsSetPropertyData(camera, kEdsPropID_Tv, 0, sizeof(property), &property);
	err = EdsGetPropertyData(camera, kEdsPropID_Tv, 0, sizeof(property), &property);
	if (err != EDS_ERR_OK) {
		std::cout << "error at property" << std::endl;
	} else {
		std::cout << "Shutter speed is set to " << canon::shutterSpeedEdsToDouble(property) << " " << property;
		printf(" %X\n", property);
	}
	property = canon::evfOutputDeviceDoubleToEds(1);
	err = EdsSetPropertyData(camera, kEdsPropID_Evf_OutputDevice, 0 , sizeof(property), &property);
	err = EdsGetPropertyData(camera, kEdsPropID_Evf_OutputDevice, 0 , sizeof(property), &property);
	if (err != EDS_ERR_OK) {
		std::cout << "error at property" << std::endl;
	} else {
		std::cout << "Evf output device is set to " << canon::evfOutputDeviceEdsToDouble(property) << " " << property;
		printf(" %X\n", property);
	}
	property = canon::evfModeDoubleToEds(1);
	err = EdsSetPropertyData(camera, kEdsPropID_Evf_Mode, 0, sizeof(property), &property);
	err = EdsGetPropertyData(camera, kEdsPropID_Evf_Mode, 0, sizeof(property), &property);
	if (err != EDS_ERR_OK) {
		std::cout << "error at property" << std::endl;
	} else {
		std::cout << "Evf mode is set to " << canon::evfOutputDeviceEdsToDouble(property) << " " << property;
		printf(" %X\n", property);
	}

	property = kEdsSaveTo_Camera;
	err = EdsSetPropertyData(camera, kEdsPropID_SaveTo, 0, sizeof(property), &property);
//	EdsCapacity newCapacity = {0x7FFFFFFF, 0x100000, 1};
//	err = EdsSetCapacity(camera, newCapacity);

	err = EdsSendCommand(camera, kEdsCameraCommand_PressShutterButton, kEdsCameraCommand_ShutterButton_Completely_NonAF);

//	std::string empname = "";
//	std::cout << "Press key to continue:" << std::endl;
//	std::getline(std::cin, empname);
	Sleep(20 * 1000);

	err = EdsSendCommand(camera, kEdsCameraCommand_PressShutterButton, kEdsCameraCommand_ShutterButton_OFF);

	EdsUInt32 numFiles = getNumberOfFiles(camera);
	std::cout << "Number of files " << numFiles << " " << numFiles;
	printf(" %X\n", numFiles);
	// Close session with camera
	if (err == EDS_ERR_OK) {
		err = EdsCloseSession(camera);
	}
	// Release camera
	if (camera != NULL) {
		EdsRelease(camera);
	}

	// Terminate SDK
	if (isSDKLoaded) {
		EdsTerminateSDK();
	}
	return 0;
}
