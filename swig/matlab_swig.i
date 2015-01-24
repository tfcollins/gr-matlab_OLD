/* -*- c++ -*- */

#define MATLAB_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "matlab_swig_doc.i"

%{
#include "matlab/fftmat.h"
%}


%include "matlab/fftmat.h"
GR_SWIG_BLOCK_MAGIC2(matlab, fftmat);
