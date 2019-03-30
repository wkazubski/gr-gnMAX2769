/*!
 * \file gnmax_source_cc.cc
 * \brief GNU Radio source block to acces to MAX2769 USB sampler.
 * \author Javier Arribas, 2012. jarribas(at)cttc.es
 * \author Wojciech Kazubski, 2019. wk(at)ire.pw.edu.pl
 *
 * This file is based on gn3s_source_cc.c file, a part of GN3S driver for
 * gnss-sdr project
 *
* -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2012  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnmax_source_cc.h>
#include <gnmax_defines.h>
#include <gnuradio/io_signature.h>


/*
 * Create a new instance of howto_square_ff and return
 * a boost shared_ptr.  This is effectively the public constructor.
 */
gnmax_source_cc_sptr
gnmax_make_source_cc (int bias)
{
  return gnuradio::get_initial_sptr(new gnmax_source_cc (bias));
}

/*
 * Specify constraints on number of input and output streams.
 * This info is used to construct the input and output signatures
 * (2nd & 3rd args to gr::block's constructor).  The input and
 * output signatures are used by the runtime system to
 * check that a valid number and type of inputs and outputs
 * are connected to this block.  In this case, we accept
 * only 1 input and 1 output.
 */
static const int MIN_IN = 0;	// mininum number of input streams
static const int MAX_IN = 0;	// maximum number of input streams
static const int MIN_OUT = 1;	// minimum number of output streams
static const int MAX_OUT = 1;	// maximum number of output streams

static int bias_v;

/*
 * The private constructor
 */
gnmax_source_cc::gnmax_source_cc (int bias)
  : gr::block ("gnmax_cc",
              gr::io_signature::make(MIN_IN, MAX_IN, sizeof (gr_complex)),
              gr::io_signature::make(MIN_OUT, MAX_OUT, sizeof (gr_complex)))
{
    // constructor code here
    bias_v = bias;
    gnmax_drv = new gnmax_Source(bias_v);
    fprintf(stdout,"GNMAX Start\n");
}

/*
 * Our virtual destructor.
 */
gnmax_source_cc::~gnmax_source_cc ()
{
    // destructor code here
    if(gnmax_drv != NULL)
    {
        fprintf(stdout,"Destructing MAX2769");
        delete gnmax_drv;
        //delete packet;
    }
}

int 
gnmax_source_cc::general_work (int noutput_items,
                               gr_vector_int &ninput_items,
                               gr_vector_const_void_star &input_items,
                               gr_vector_void_star &output_items)
{
    int n_samples_rx;
    gr_complex *out = (gr_complex *) output_items[0];

    if (noutput_items<=GNMAX_SAMPS_5MS)
    {
        gnmax_drv->Read(&packet,noutput_items);
        n_samples_rx = noutput_items;
    }
    else
    {
        gnmax_drv->Read(&packet,GNMAX_SAMPS_5MS);
        n_samples_rx = GNMAX_SAMPS_5MS;
    }
    for (int i = 0; i < n_samples_rx; i++)
    {
        out[i] = gr_complex(packet.data[i].i, packet.data[i].q);
    }

    // Tell runtime system how many output items we produced.
    return n_samples_rx;
}

int gnmax_source_cc::bias()
{
    return bias_v;
}

void gnmax_source_cc::set_bias(int bias)
{
    gnmax_drv->w_set_bias(bias);
    bias_v = bias;
}
