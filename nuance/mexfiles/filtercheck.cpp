/*
 * filtercheck.cpp
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

	const cri_FilterHandle handle = (cri_FilterHandle) mxGetScalar(prhs[0]);

	nuance::FILTER_STATUS status = nuance::checkFilter(handle);
	plhs[0] = mxCreateDoubleScalar((double) status);
}
