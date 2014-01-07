/*
 * nuancesnapprealloc.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: igkiou
 */

#include "nuancefx_mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

	/* Check number of input arguments */
	if (nrhs < 2) {
		mexErrMsgTxt("Two input arguments are required.");
	}

	/* Check number of output arguments */
	if (nlhs > 0) {
		mexErrMsgTxt("Too many output arguments.");
	}

	const cri_CameraHandle cameraHandle = (cri_CameraHandle) mxGetScalar(prhs[0]);

	nuance::snapPreAlloc(cameraHandle, prhs[1]);

}
