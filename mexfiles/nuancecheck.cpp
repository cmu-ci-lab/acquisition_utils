/*
 * nuancecheck.cpp
 *
 *  Created on: Aug 17, 2012
 *      Author: igkiou
 */

#include "nuancefx_mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

	/* Check number of input arguments */
	if (nrhs != 1) {
		mexErrMsgTxt("One input argument is required.");
    }

	/* Check number of output arguments */
	if (nlhs > 1) {
		mexErrMsgTxt("Too many output arguments.");
    }

	const cri_CameraHandle handle = (cri_CameraHandle) mxGetScalar(prhs[0]);

	nuance::CAMERA_STATUS status = nuance::checkCamera(handle);
	plhs[0] = mxCreateDoubleScalar((double) status);
}
