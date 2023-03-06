#include <octave/oct.h>
#include <arrayfire.h>

/***
 *
 *  Octave (oct) gateway function for af::fftConvolve
 *
 ***/

DEFUN_DLD (af_fftconv, args, nlhs,
           "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} [Y] = af_fftconv(A,B)\n\
\n\
AF_FFTCONV - Computes fftconvolutions of the columns of two matricies\n\
A and B using the ArrayFire general purpose GPU library.\n\
\n\
Input parameters:\n\
\n\
@table @code\n\
@item A\n\
An M_A x N matrix.\n\
@item B\n\
An M_B x N matrix or and M_B x 1 vector.\n\
@end table\n\
\n\
af_fftconv is an oct-function that is a part of ...\n\
@url{https://github.com/frli8848/af_octave}.\n\
\n\
Copyright @copyright{} 2019 Fredrik Lingvall.\n\
@seealso {af_conv}\n\
@end deftypefn")
{
  octave_value_list oct_retval;

  int nrhs = args.length ();

  // Check for proper number of arguments

  if (nrhs != 2) {
    error("af_fftconv requires 2 input arguments!");
    return oct_retval;
  }

  const Matrix tmp0 = args(0).matrix_value();
  double *A = (double*) tmp0.data();
  octave_idx_type M_A = args(0).matrix_value().rows();
  octave_idx_type N_A = args(0).matrix_value().cols();

  const Matrix tmp1 = args(1).matrix_value();
  double *B = (double*) tmp1.data();
  octave_idx_type M_B = args(1).matrix_value().rows();
  octave_idx_type N_B = args(1).matrix_value().cols();

  // Check filter dim.
  if ( (N_B != N_A) && (N_B != 1) ) {
    error("Wrong dim of 2nd argument. The number of columns in arg 2 must be 1 or must match the number of columns in 1st arg!");
  }

  // Create device arrays and copy host data.
  af::array af_A(M_A, N_A, A);
  af::array af_B(M_B, N_B, B);

  // AF_CONV_DEFAULT Output of the convolution is the same size as input.
  // AF_CONV_EXPAND  Output of the convolution is signal_len + filter_len - 1.
  af::array af_Y = af::fftConvolve1(af_A, af_B, AF_CONV_EXPAND);

  // Create an output matrix for the impulse response
  Matrix Ymat(M_A+M_B-1, N_A);
  double *Y = (double*) Ymat.data();

  // Copy data back to the host.
  af_Y.host(Y);

  oct_retval.append(Ymat);

  return oct_retval;
}
