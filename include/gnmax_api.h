/*!
 * \file gnmax_api.h
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

#ifndef INCLUDED_GNMAX_API_H
#define INCLUDED_GNMAX_API_H

#include <gnuradio/attributes.h>

#ifdef gr_gnmax_EXPORTS
#  define GNMAX_API __GR_ATTR_EXPORT
#else
#  define GNMAX_API __GR_ATTR_IMPORT
#endif

#endif /* INCLUDED_GNMAX_API_H */
