/* -*- c++ -*- */
/*
 * Copyright 2020 Wojciech Kazubski.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "gnmax_source_cc_impl.h"

namespace gr {
  namespace gnMAX2769 {

    gnmax_source_cc::sptr
    gnmax_source_cc::make(int bias, int ant, float freq, int bw, int zeroif)
    {
      return gnuradio::get_initial_sptr
        (new gnmax_source_cc_impl(bias, ant, freq, bw, zeroif));
    }


    /*
     * The private constructor
     */
    gnmax_source_cc_impl::gnmax_source_cc_impl(int bias, int ant, float freq, int bw, int zeroif)
      : gr::sync_block("gnmax_source_cc",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      settings.bias = bias;
      settings.ant = ant;
      if (zeroif != 0)
        settings.zeroif = 4;
      else
        settings.zeroif = 0;
      settings.freq = static_cast<int>(freq / 1023000 + 0.5) - 4 + settings.zeroif;
      settings.bw = bw;
      gnmax_drv = new gnmax_Source(settings);
      fprintf(stdout,"GNMAX Start\n");
    }

    /*
     * Our virtual destructor.
     */
    gnmax_source_cc_impl::~gnmax_source_cc_impl()
    {
      if(gnmax_drv != NULL)
      {
        fprintf(stdout,"Destructing MAX2769\n");
        delete gnmax_drv;
      }
    }

    int
    gnmax_source_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      gr_complex *out = (gr_complex *) output_items[0];

      // Do <+signal processing+>
      int n_samples_rx;
      unsigned char bbuf[GNMAX_SAMPS_5MS];

      if (noutput_items<=GNMAX_SAMPS_5MS)
      {
        n_samples_rx = gnmax_drv->Read(bbuf,noutput_items);
      }
      else
      {
        n_samples_rx = gnmax_drv->Read(bbuf,GNMAX_SAMPS_5MS);
      }
      for (int i = 0; i < n_samples_rx; i++)
      {
        out[i] = gr_complex((((bbuf[i] & 0x03) << 1) - 3), (((bbuf[i] & 0x0C) >> 1) - 3));
/*
       // use higher nibble
        out[i] = gr_complex((((bbuf[i] & 0x30) >> 3) - 3), (((bbuf[i] & 0xC0) >> 5) - 3));
*/
      }

      // Tell runtime system how many output items we produced.
      return n_samples_rx;
    }

    void gnmax_source_cc_impl::set_bias(int bias)
    {
      gnmax_drv->w_set_bias(bias);
      settings.bias = bias;
    }

    void gnmax_source_cc_impl::set_ant(int ant)
    {
      gnmax_drv->w_set_ant(ant);
      settings.ant = ant;
    }

    void gnmax_source_cc_impl::set_freq(float freq)
    {
      int f = static_cast<int>(freq / 1023000 + 0.5) - 4 + settings.zeroif;
      gnmax_drv->w_set_freq(f);
      settings.freq = f;
    }

    void gnmax_source_cc_impl::set_bw(int bw)
    {
      gnmax_drv->w_set_bw(bw, settings.zeroif);
      settings.bw = bw;
    }


  } /* namespace gnMAX2769 */
} /* namespace gr */

