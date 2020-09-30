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


#ifndef INCLUDED_GNMAX2769_GNMAX_SOURCE_CC_H
#define INCLUDED_GNMAX2769_GNMAX_SOURCE_CC_H

#include <gnMAX2769/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace gnMAX2769 {

    /*!
     * \brief <+description of block+>
     * \ingroup gnMAX2769
     *
     */
    class GNMAX2769_API gnmax_source_cc : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<gnmax_source_cc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of gnMAX2769::gnmax_source_cc.
       *
       * To avoid accidental use of raw pointers, gnMAX2769::gnmax_source_cc's
       * constructor is in a private implementation
       * class. gnMAX2769::gnmax_source_cc::make is the public interface for
       * creating new instances.
       */
      static sptr make(int bias, int ant, float freq, int bw, int zeroif);

      /*!
       * \brief Return active antenna bias state
       */
      virtual int bias() const = 0;

      /*!
       * \brief Set active antenna bias
       */
      virtual void set_bias(int bias) = 0;

      /*!
       * \brief Return antenna selection
       */
      virtual int ant() const = 0;

      /*!
       * \brief Set antenna selection
       */
      virtual void set_ant(int ant) = 0;

      /*!
       * \brief Return RF frequency
       */
      virtual float freq() const = 0;

      /*!
       * \brief Set RF frequency
       */
      virtual void set_freq(float freq) = 0;

      /*!
       * \brief Return IF bandwidth setting
       */
      virtual int bw() const = 0;

      /*!
       * \brief Set IF bandwidth
       */
      virtual void set_bw(int bw) = 0;
    };

  } // namespace gnMAX2769
} // namespace gr

#endif /* INCLUDED_GNMAX2769_GNMAX_SOURCE_CC_H */

