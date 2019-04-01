/*----------------------------------------------------------------------------------------------*/
//
// FILENAME: gps_source.h
//
// DESCRIPTION: Defines the GPS_Source class.
//
// DEVELOPERS: Gregory W. Heckler (2003-2009)
//             Wojciech Kazubski (2019)
//
// LICENSE TERMS: Copyright (c) Gregory W. Heckler 2009
//                Copyright (c) Wojciech Kazubski 2019
//
// This file is based on gn3s_source.h file, a part of GN3S driver for gnss-sdr project
//
// This file is part of the GPS Software Defined Radio (GPS-SDR)
//
// The GPS-SDR is free software; you can redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version. The GPS-SDR is distributed in the hope that
// it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// Note:  Comments within this file follow a syntax that is compatible with
//        DOXYGEN and are utilized for automated document extraction
//
// Reference:
/*----------------------------------------------------------------------------------------------*/

#ifndef GNMAX_SOURCE_H_
#define GNMAX_OURCE_H_

#include "gnmax_defines.h"
#include "gnmax.h"

/*! \ingroup CLASSES
 *
 */
class gnmax_Source
{

	private:

		/* Generic variables */
		int source_type;		//!< Source type
		int sample_mode;		//!< Sample mode
		int leftover;			//!< Leftover bytes for USRP double buffering
		int bwrite;			//!< Bytes somthing something?
		int ms_count;			//!< Count the numbers of ms processed

		bool flag_first_read;
		/* Tag overflows */
		time_t rawtime;
		struct tm * timeinfo;

		/* AGC Values */
		int agc_scale;		//!< To do the AGC
		int overflw;			//!< Overflow counter
		int soverflw;			//!< Overflow counter

		/* Data buffers */
		unsigned char gbuff[GNMAX_SAMPS_5MS*2]; 	//!< Byte buffer for GNMAX
		GNMAX_CPX buff[GNMAX_SAMPS_5MS]; 		//!< Base buffer for GNMAX

		/* SOURCE_GNMAX Handles */
		gnmax *gnmax_a;

	private:

		void Open_GNMAX(gnmax_variables variables);			//!< Open the MAX2769 Sampler
		void Close_GNMAX();			//!< Close the MAX2769 Sampler
		void Read_GNMAX(gnmax_ms_packet *_p,int n_samples);	//!< Read from the MAX2769 Sampler

	public:

		gnmax_Source(gnmax_variables variables);	//!< Create the GPS source with the proper hardware type
		~gnmax_Source();					//!< Kill the object
		void Read(gnmax_ms_packet *_p,int n_samples);		//!< Read in a single ms of data
		int getScale(){return(agc_scale);}
		int getOvrflw(){return(overflw);}
		bool w_set_bias(int bias);
		bool w_set_ant(int ant);
		bool w_set_freq(int freq);
};

#endif /* GNMAX_SOURCE_H_ */
