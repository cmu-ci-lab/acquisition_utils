/*
 * acquisition_utils//acquisition_utils/camera/include/camera.h/camera.h
 *
 *  Created on: Apr 11, 2015
 *      Author: igkiou
 */

#ifndef CAMERA_INCLUDE_CAMERA_H_
#define CAMERA_INCLUDE_CAMERA_H_

#include "mex_utils.h"

namespace camera {

class CameraBaseInterface {
public:
	CameraBaseInterface() = default;
	CameraBaseInterface(const CameraBaseInterface& other) = delete;
	CameraBaseInterface& operator=(const CameraBaseInterface& other) = delete;

	virtual bool isOpen() = 0;
	virtual void snap() = 0;
	virtual void stream() = 0;

	virtual void getProperty() = 0;

	virtual ~CameraBaseInterface() = default;
};


class LensInterface {
	LensInterface() = default;
	LensInterface(const LensInterface& other) = delete;
	LensInterface& operator=(const LensInterface& other) = delete;

	virtual bool isOpen() = 0;
	virtual void autofocus() = 0;

	virtual ~LensInterface() = default;
};

class ColorFilterInterface {

};

class FrameGrabberInterface {
	FrameGrabberInterface() = default;
	FrameGrabberInterface(const FrameGrabberInterface& other) = delete;
	FrameGrabberInterface& operator=(const FrameGrabberInterface& other) = delete;

	virtual void grab() = 0;
	virtual ~FrameGrabberInterface() = default;
};


}  // namespace camera

#endif  // CAMERA_INCLUDE_CAMERA_H_
