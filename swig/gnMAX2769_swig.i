/* -*- c++ -*- */

#define GNMAX2769_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "gnMAX2769_swig_doc.i"

%{
#include "gnMAX2769/gnmax_source_cc.h"
%}


%include "gnMAX2769/gnmax_source_cc.h"
GR_SWIG_BLOCK_MAGIC2(gnMAX2769, gnmax_source_cc);
