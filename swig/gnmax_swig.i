/* -*- c++ -*- */

#define GNMAX_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "gnmax_swig_doc.i"


%{
#include "gnmax_source_cc.h"
%}

GR_SWIG_BLOCK_MAGIC(gnmax,source_cc);
%include "gnmax_source_cc.h"

