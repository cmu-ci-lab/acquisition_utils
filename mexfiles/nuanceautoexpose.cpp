/*
 * nuanceautoexpose.cpp
 *
 *  Created on: Aug 20, 2012
 *      Author: igkiou
 */

#include "nuancefx_mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

	/* Check number of input arguments */
	if (nrhs != 2) {
		mexErrMsgTxt("Two input arguments are required.");
	}

	/* Check number of output arguments */
	if (nlhs > 1) {
		mexErrMsgTxt("Too many output arguments.");
	}

	const cri_CameraHandle cameraHandle = (cri_CameraHandle) mxGetScalar(prhs[0]);
	const cri_FilterHandle filterHandle = (cri_FilterHandle) mxGetScalar(prhs[1]);
//	const double *wavelengths = (double *) mxGetPr(prhs[2]);
//	const double *exposureTimes = (double *) mxGetPr(prhs[3]);
//	const unsigned numWavelengths = mxGetNumberOfElements(prhs[2]);

//	if(mxGetNumberOfElements(prhs[3]) != numWavelengths) {
//		mexErrMsgIdAndTxt(ERROR_ID, "EXPOSURETIMES (fourth argument) must have the same length as WAVELENGTHS (third argument).\n");
//	}

	plhs[0] = nuance::getAutoExposure(cameraHandle, filterHandle);

}
