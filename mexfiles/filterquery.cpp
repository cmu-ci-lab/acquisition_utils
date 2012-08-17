/*
 * filterquery.cpp
 *
 *  Created on: Aug 17, 2012
 *      Author: igkiou
 */

#include "nuancefx_mex.h"

#include <iostream>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

	/* Check number of input arguments */
	if (nrhs > 0) {
		mexErrMsgTxt("Too many input arguments.");
    }

	/* Check number of output arguments */
	if (nlhs > 1) {
		mexErrMsgTxt("Too many output arguments.");
    }

	unsigned numFilters = nuance::queryFilter();
	plhs[0] = mxCreateDoubleScalar((double) numFilters);
//	mexPrintf("Available filters: %u.\n", numFilters);
}

