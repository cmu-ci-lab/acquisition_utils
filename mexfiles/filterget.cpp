/*
 * filterget.cpp
 *
 *  Created on: Aug 17, 2012
 *      Author: igkiou
 */

#include "nuancefx_mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

	/* Check number of input arguments */
	if (nrhs < 1) {
		mexErrMsgTxt("At least one input argument is required.");
	} else if (nrhs > 2) {
		mexErrMsgTxt("Two or fewer input arguments are required.");
	}

	/* Check number of output arguments */
	if (nlhs > 1) {
		mexErrMsgTxt("Too many output arguments.");
	}

	const cri_FilterHandle handle = (cri_CameraHandle) mxGetScalar(prhs[0]);

	if (nrhs >= 2) {
		if (!mxIsChar(prhs[1])) {
			mexErrMsgTxt("Second argument must be a string.");
		}
		const int lengthPropertyName = mxGetNumberOfElements(prhs[1]) + 1;
		char* propertyName = (char *) mxMalloc(lengthPropertyName * sizeof(char));
		mxGetString(prhs[1], propertyName, lengthPropertyName);
		nuance::getFilterProperty(handle, propertyName, plhs[0]);
		mxFree(propertyName);
	} else {
		nuance::getFilterProperties(handle, plhs[0]);
	}
}
