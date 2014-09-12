/*
 * nuancesnap.cpp
 *
 *  Created on: Dec 17, 2013
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

	const cri_CameraHandle cameraHandle = (cri_CameraHandle) mxGetScalar(prhs[0]);

	plhs[0] = nuance::snap(cameraHandle);

}
