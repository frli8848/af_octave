#include <octave/oct.h>
#include <arrayfire.h>
#include <iostream>

#include <iostream>

/***
 *
 *  Octave (oct) gateway function to initialze ArrayFire
 *
 ***/

DEFUN_DLD (af_init, args, nlhs,
           "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} [Y] = af_init()\n\
\n\
AF_INIT - Initialize ArrayFire backend\n\
\n\
af_init is an oct-function that is a part of ...\n\
@url{https://github.com/frli8848/af_octave}.\n\
\n\
Copyright @copyright{} 2019 Fredrik Lingvall.\n\
@seealso {af_fftinit}\n\
@end deftypefn")
{
  octave_value_list oct_retval;

  int nrhs = args.length ();

  // Check for proper number of arguments

  if (nrhs != 0) {
    error("af_init has no input arguments!");
    return oct_retval;
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

  return oct_retval;
}
