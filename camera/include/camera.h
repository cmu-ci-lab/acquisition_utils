/*
 * acquisition_utils//acquisition_utils/camera/include/camera.h/camera.h
 *
 *  Created on: Apr 11, 2015
 *      Author: igkiou
 */

#ifndef CAMERA_INCLUDE_CAMERA_H_
#define CAMERA_INCLUDE_CAMERA_H_

namespace camera {

class CameraBaseInterface {
public:
	virtual bool isOpen() = 0;


	virtual ~CameraBaseInterface() = default;
};

}  // namespace camera


/*
 * acquisition_utils//acquisition_utils/camera/include/camera.h/camera.h
 *
 *  Created on: Sep 12, 2014
 *      Author: igkiou
 */

#ifndef CAMERA_H_
#define CAMERA_H_

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
	CAMERA_ROI = 13,
	CAMERA_
	CAMERA_PROPERTY_LENGTH = 15,
	CAMERA_PROPERTY_INVALID = -1
} CAMERA_PROPERTY;




typedef enum FILTER_PROPERTY {
	FILTER_SERIAL = 0,
	FILTER_FIRMWARE = 1,
	FILTER_RANGE = 2,
	FILTER_STEPSIZE = 3,
	FILTER_WAVELENGTH = 4,
	FILTER_PROPERTY_LENGTH = 5,
	FILTER_PROPERTY_INVALID = -1
} FILTER_PROPERTY;

/* Simple classes using the above functions. */
class Camera {
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

#endif  // CAMERA_INCLUDE_CAMERA_H_
