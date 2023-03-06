#include "mex.h"
#include <arrayfire.h>

/***
 *
 *  MATLAB (mex) gateway function for af::fftConvolve
 *
 ***/

extern void _main();

void  mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  // Check for proper number of arguments

  if (nrhs != 2) {
    mexErrMsgTxt("af_fftconv requires 2 input arguments!");
  }

  double *A = (double*) mxGetPr(prhs[0]);
  size_t M_A = mxGetM(prhs[0]);
  size_t N_A = mxGetN(prhs[0]);

  double *B = (double*) mxGetPr(prhs[1]);
  size_t M_B = mxGetM(prhs[1]);
  size_t N_B = mxGetN(prhs[1]);

  // Check filter dim.
  if ( (N_B != N_A) && (N_B != 1) ) {
    mexErrMsgTxt("Wrong dim of 2nd argument. The number of columns in arg 2 must be 1 or must match the number of columns in 1st arg!");
  }

  // Create device arrays and copy host data.
  af::array af_A(M_A, N_A, A);
  af::array af_B(M_B, N_B, B);

  // AF_CONV_DEFAULT Output of the convolution is the same size as input.
  // AF_CONV_EXPAND  Output of the convolution is signal_len + filter_len - 1.
  af::array af_Y = af::fftConvolve1(af_A, af_B, AF_CONV_EXPAND);

  // Create an output matrix for the impulse response
  plhs[0] = mxCreateDoubleMatrix(M_A+M_B-1, N_A,mxREAL);

  // Copy data back to the host.
  af_Y.host(plhs[0]);

  return;
}
