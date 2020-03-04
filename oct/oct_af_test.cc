#include <octave/oct.h>
#include <arrayfire.h>
#include <iostream>

/***
 *
 *  Octave (oct) gateway function to test ArrayFire's
 *  backends.
 *
 ***/

DEFUN_DLD (af_test, args, nlhs,
           "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} [Y] = af_test()\n\
\n\
AF_TEST - Test run ArrayFire's detected backends\n\
\n\
af_test is an oct-function that is a part of ...\n\
@url{https://github.com/frli8848/af_octave}.\n\
\n\
Copyright @copyright{} 2019 Fredrik Lingvall.\n\
@seealso {af_init}\n\
@end deftypefn")
{
  octave_value_list oct_retval;

  int nrhs = args.length ();

  // Check for proper number of arguments

  if (nrhs != 0) {
    error("af_test has no input arguments!");
    return oct_retval;
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
    std::cerr <<  e.what() << std::endl;
  }

  return oct_retval;
}
