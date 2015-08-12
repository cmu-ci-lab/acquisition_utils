/*
 * acquisition_utils//acquisition_utils/camera/avt/include/avt.h/avt.h
 *
 *  Created on: Sep 13, 2014
 *      Author: igkiou
 */

#ifndef AVT_H_
#define AVT_H_

#include <PvApi.h>
#include "../include/camera.h"

class AvtCamera : public camera::CameraBaseInterface,
				public camera::FrameGrabberInterface,
				public camera::LensInterface {
public:

	AvtCamera(unsigned long uid) :
			m_uid(uid),
			m_address(),
			m_camera() {
		tPvErr errorCode = PvCameraOpen(m_uid, Flags, &m_camera);
		mexAssert)
	}


private:
    unsigned long m_uid;
    unsigned long m_address;
    tPvHandle m_camera;

};


#endif /* AVT_H_ */
