/*
 * nuanceset.cpp
 *
 *  Created on: May 22, 2012
 *      Author: igkiou
 */

#include "nuancefx_mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

	/* Check number of input arguments */
	if (nrhs < 2) {
		mexErrMsgTxt("At least two input arguments are required.");
	} else if (nrhs > 3) {
		mexErrMsgTxt("Three or fewer input arguments are required.");
	}

	/* Check number of output arguments */
	if (nlhs > 1) {
		mexErrMsgTxt("Too many output arguments.");
	}

	const cri_CameraHandle handle = (cri_CameraHandle) mxGetScalar(prhs[0]);

	if (nrhs == 3) {
		if (!mxIsChar(prhs[1])) {
			mexErrMsgTxt("Second argument must be a string.");
		}
		const int lengthPropertyName = mxGetNumberOfElements(prhs[1]) + 1;
		char* propertyName = (char *) mxMalloc(lengthPropertyName * sizeof(char));
		mxGetString(prhs[1], propertyName, lengthPropertyName);
		nuance::CAMERA_PROPERTY property = nuance::stringToCameraProperty(propertyName);
		nuance::setCameraProperty(handle, property, prhs[2]);
	} else {
		nuance::setCameraProperty(handle, prhs[1]);
	}
}
