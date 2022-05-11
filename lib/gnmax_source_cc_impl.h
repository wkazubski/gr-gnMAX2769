/* -*- c++ -*- */
/* 
 * Copyright 2019 Wojciech Kazubski.
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

#ifndef INCLUDED_GNMAX2769_GNMAX_SOURCE_CC_IMPL_H
#define INCLUDED_GNMAX2769_GNMAX_SOURCE_CC_IMPL_H

#include <gnMAX2769/gnmax_source_cc.h>

namespace gr {
  namespace gnMAX2769 {

    class gnmax_source_cc_impl : public gnmax_source_cc
    {
     private:
      /* Create the GNMAX object*/
      gnmax_Source *gnmax_drv;
      gnmax_ms_packet packet;
      gnmax_settings settings;

     public:
      gnmax_source_cc_impl(int bias, int ant, float freq, int bw, int zeroif);
      ~gnmax_source_cc_impl();

      // Where all the action really happens
      int work(int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items);

      int bias() const { return settings.bias; };
      void set_bias (int bias);
      int ant () const { return settings.ant; }; 
      void set_ant (int ant);
      float freq () const { return settings.freq; };
      void set_freq (float freq);
      int bw () const { return settings.bw; };
      void set_bw (int bw);
    };

  } // namespace gnMAX2769
} // namespace gr

#endif /* INCLUDED_GNMAX2769_GNMAX_SOURCE_CC_IMPL_H */
