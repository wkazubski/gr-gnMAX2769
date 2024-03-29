/*
 * Copyright 2011 Free Software Foundation, Inc.
 *
 * This file was generated by gr_modtool, a tool from the GNU Radio framework
 * This file is a part of gr-divider
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
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
      typedef std::shared_ptr<gnmax_source_cc> sptr;

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

