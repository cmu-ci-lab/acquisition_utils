/*
 * nuancecapturesingle.cpp
 *
 *  Created on: Dec 17, 2013
 *      Author: igkiou
 */

#include "nuancefx_mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

	/* Check number of input arguments */
	if (nrhs != 4) {
		mexErrMsgTxt("Four input arguments are required.");
	}

	/* Check number of output arguments */
	if (nlhs > 1) {
		mexErrMsgTxt("Too many output arguments.");
	}

	const cri_CameraHandle cameraHandle = (cri_CameraHandle) mxGetScalar(prhs[0]);
	const cri_FilterHandle filterHandle = (cri_FilterHandle) mxGetScalar(prhs[1]);
	const double wavelength = (double) mxGetScalar(prhs[2]);
	const double exposureTime = (double) mxGetScalar(prhs[3]);

	plhs[0] = nuance::captureSingle(cameraHandle, filterHandle, \
							wavelength, exposureTime);

}
