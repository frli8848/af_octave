#include "mex.h"
#include <arrayfire.h>
#include <iostream>

#include <iostream>

/***
 *
 *  MATLAB (mex) gateway function to test ArrayFire's
 *  backends.
 *
 ***/

extern void _main();

void  mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{

  // Check for proper number of arguments

  if (nrhs != 0) {
    mexErrMsgTxt("af_test has no input arguments!");
  }

  std::cout << std::endl << "Number of avialable ArrayFire backends: " << af::getBackendCount() << std::endl << std::endl;

  int backends = af::getAvailableBackends();
  switch(backends) {

  case 0:
    std::cout << "No ArrayFire backends available!" << std::endl;
    break;

  case 1:
    std::cout << "CPU ArrayFire backend is available" << std::endl;
    break;

  case 2:
    std::cout << "CUDA ArrayFire backend is available!" << std::endl;
    break;

  case 3:
    std::cout << "CPU and CUDA ArrayFire backends available!" << std::endl;
    break;

  case 4:
    std::cout << "OpenCL ArrayFire backend is available!" << std::endl;
    break;

  case 5:
    std::cout << "OpenCL and CPU ArrayFire backends available!" << std::endl;
    break;

  case 6:
    std::cout << "CUDA and OpenCL ArrayFire backends available!" << std::endl;
    break;

  case 7:
    std::cout << "CUDA, OpenCL, and CPU ArrayFire backends available!" << std::endl;
    break;

  }
  std::cout << std::endl;

  try {
    std::cout << "Trying CUDA Backend..."  << std::endl;
    af::setBackend(AF_BACKEND_CUDA);
    af::info();
    af_print(af::randu(5, 4));

  } catch (af::exception& e) {
    std::cerr << "Caught an exception when trying the ArrayFire CUDA backend" << std::endl;
    std::cerr <<  e.what() << std::endl;
  }

  try {
    std::cout << "Trying OpenCL Backend..."  << std::endl;
    af::setBackend(AF_BACKEND_OPENCL);
    af::info();
    af_print(af::randu(5, 4));
  } catch (af::exception& e) {
    std::cerr << "Caught an exception when trying the ArrayFire OpenCL backend" << std::endl;
    std::cerr <<  e.what() << std::endl;
  }

  try {
    std::cout << "Trying CPU Backend..." << std::endl;
    af::setBackend(AF_BACKEND_CPU);
    af::info();
    af_print(af::randu(5, 4));
  } catch (af::exception& e) {
    std::cerr << "Caught an exception when trying the ArrayFire CPU backend" << std::endl;
    std::cerr << e.what() << std::endl;
  }

  return;
}
