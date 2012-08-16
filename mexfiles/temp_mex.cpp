/*
#define __DEBUG__
*/

#include "nuancefx_mex.h"

#include <iostream>
#include <cstring>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	
	/* Check number of input arguments */
	if (nrhs != 2) {
		mexErrMsgTxt("Two or less input arguments are required.");
    }
	
	/* Check number of output arguments */
	if (nlhs > 1) {
		mexErrMsgTxt("Too many output arguments.");
    }  
	
	double *X = (double*) mxGetData(prhs[0]);
	double *lambda = (double*) mxGetData(prhs[1]);

	int M = (int) mxGetM(prhs[0]);
	int N = (int) mxGetN(prhs[0]);
	
	plhs[0] = mxCreateNumericMatrix(M, N, mxDOUBLE_CLASS, mxREAL); /* x */
	double *S = (double *) mxGetData(plhs[0]);

	for (int iterN = 0; iterN < N; ++iterN) {
		for (int iterM = 0; iterM < M; ++iterM) {
			S[iterN * M + iterM] = X[iterN * M + iterM] + *lambda * (double) (iterN + 1);
		}
	}
	
//   for (int idx = 0; idx < ALLOWED_STREAM_COUNT; ++idx){
//      m_StreamImages[idx].image = NULL;
//      m_StreamImages[idx].wavelengths = NULL;
//   };
//
//   char desc[cri_MAX_STRING_LENGTH];
//   int version;
//
//   cri_ErrorCode errorCode = cri_GetDescription(
//      desc,
//      &version);
//
//   std::cout << desc << std::endl;
//   std::cout << std::endl;

   //
   //  Open up the devices.
   //
//   OpenDevices();
//
//   if (m_CameraHandle == -1 || m_FilterHandle == -1){
//      ShutdownDevices();
//
//      return;
//   };

   //
   //  Set the camera to 8 bit and 1x1 binning.
   //
//   SetCameraBitDepthTo(cri_CameraBitDepth8);
//   SetCameraBinningTo(cri_CameraBinning1x1);

   //
   //  Auto expose the camera for single snapshot.
   //
//   AutoExposeForPlane();

   //
   //  Get image size.
   //
//   int width;
//   int height;
//   GetCameraImageSize(&width, &height);

   //
   //  Snap camera image asynchronously.
   //
//   m_SnapImage.width = width;
//   m_SnapImage.height = height;
//
//   m_SnapImage.image = new unsigned char[width * height];

//   errorCode = cri_SnapInt8(
//      m_CameraHandle,
//      &m_SnapImage,
//      false,
//      SnapInt8Callback);

   //
   //  Wait for the camera to be ready.
   //
//   WaitForCameraToBeReady();

   //
   //  Snap another image asynchronously but do not wait around.  Call
   //  another API routine and note the blocking behavior till the async
   //  operation is complete.
   //
//   errorCode = cri_SnapInt8(
//      m_CameraHandle,
//      &m_SnapImage,
//      false,
//      SnapInt8Callback);

   //
   //  Temperature is not available for all cameras.
   //
//   float temperatureC = 0.0F;

//   if (cri_GetCameraTemperature(m_CameraHandle, &temperatureC) == cri_NoError)
//      std::cout << "Camera Temperature : " << temperatureC << std::endl;

   //
   //  Start a camera stream and wait for N images have been captured.
   //
//   errorCode = cri_StartInt8Stream(
//      m_CameraHandle,
//      StreamInt8Callback,
//      ErrorCallback);
//
//   bool isStreaming = true;
//
//   while(isStreaming && m_CameraImageStreamCount < ALLOWED_STREAM_COUNT &&
//         errorCode == cri_NoError)
//   {
////      Sleep();
//
//      errorCode = cri_IsCameraStreaming(m_CameraHandle, &isStreaming);
//   }
//
//   cri_StopStream(m_CameraHandle, true);
//
//   //
//   //  Auto expose the cube for cube acquisition.
//   //
//   AutoExposeForCube();
//
//   //
//   //  Acquire a cube asynchronously.
//   //
//   AcquireCube();
//
//   WaitForCubeAcquireToBeFinished();
//
//   cri_CloseCamera(&m_CameraHandle);
//   cri_CloseFilter(&m_FilterHandle);
//
//   delete [] m_AcquireCube.wavelengths;
//   delete [] m_AcquireCube.image;
//
//   delete [] m_SnapImage.image;
//
//   for (int idx = 0; idx < ALLOWED_STREAM_COUNT; ++idx){
//      delete [] m_StreamImages[idx].image;
//      delete [] m_StreamImages[idx].wavelengths;
//   };
//
//   ShutdownDevices();
//
//   cri_Shutdown();

   return;
}

