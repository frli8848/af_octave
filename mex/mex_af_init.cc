#include "mex.h"
#include <arrayfire.h>
#include <iostream>

#include <iostream>

/***
 *
 *  MATLAB (mex) gateway function to initialze ArrayFire
 *
 ***/

extern void _main();

void  mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  // Check for proper number of arguments

  if (nrhs != 0) {
    mexErrMsgTxt("af_init has no input arguments!");
  }

  std::cout << "ArrayFire backend init" << std::endl;

  bool got_a_af_backend = false;

  // First try CUDA
  std::cout << "Trying ArrayFire CUDA backend..." << std::flush;
  try {
    af::setBackend(AF_BACKEND_CUDA);
    got_a_af_backend = true;
    std::cout << "working!" << std::endl;
  }

  catch (...) {
    std::cout << "failed!" << std::endl;
  }

  // Then try OpenCL
  if (!got_a_af_backend) {
    std::cout << "Trying ArrayFire OpenCL backend..." << std::flush;
    try {
      af::setBackend(AF_BACKEND_OPENCL);
      got_a_af_backend = true;
      std::cout << "working!" << std::endl;
    }

    catch (...) {
      std::cerr << "failed!" << std::endl;
    }
  }

  //  Fallback to CPU
  if (!got_a_af_backend) {
    af::setBackend(AF_BACKEND_CPU); // Do not catch exeptions here.
    got_a_af_backend = true;
    std::cout << "Using CPU ArrayFire backend" << std::endl;
  }

  return;
}
