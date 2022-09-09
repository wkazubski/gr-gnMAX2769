/*----------------------------------------------------------------------------------------------*/
/*! \file gnmax_source.cpp
//
// FILENAME: gnmax_source.cpp
//
// DESCRIPTION: Implements member functions of the GPS_Source class.
//
// DEVELOPERS: Gregory W. Heckler (2003-2009), Javier Arribas (2012)
//             Wojciech Kazubski (2019)
//
// LICENSE TERMS: Copyright (c) Gregory W. Heckler 2009
//                Copyright (c) Wojciech Kazubski 2019
//
// This file is based on gn3s_source.c file, a part of GN3S driver for gnss-sdr project
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
*/
/*----------------------------------------------------------------------------------------------*/


#include "gnmax_source.h"
#include <time.h>


/*----------------------------------------------------------------------------------------------*/
gnmax_Source::gnmax_Source(gnmax_settings settings)
{

    Open_GNMAX(settings);

    /* Assign to base */
    ms_count = 0;
    flag_first_read = true;
#if DEBUG
    fprintf(stdout, "Creating GPS Source\n");
#endif
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
gnmax_Source::~gnmax_Source()
{

    Close_GNMAX();
#if DEBUG
    fprintf(stdout, "Destructing GPS Source\n");
#endif
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
int gnmax_Source::Read(unsigned char *bbuf, int n_samples)
{

    int n = Read_GNMAX(bbuf, n_samples);
    ms_count++;
    return n;
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
void gnmax_Source::Open_GNMAX(gnmax_settings settings)
{


    /* Create the object */
    gnmax_a = new gnmax(0, settings);


    /* Everything is super! */
    //fprintf(stdout,"GNMAX Start\n");

}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
void gnmax_Source::Close_GNMAX()
{

    if(gnmax_a != NULL) delete gnmax_a;
    //fprintf(stdout,"Destructing GNMAX\n");

}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
int gnmax_Source::Read_GNMAX(unsigned char *bbuf, int n_samples)
{

    int bread;
    int started = 0;
    int check;
    bool overrun;

    short int *pbuff;

    if (flag_first_read == true)
    {
        /* Start transfer */
        while(!started)
        {
            usleep(100);
            started = gnmax_a->start_xfer();
        }
        printf("Started RX signal transfer\n");
        flag_first_read = false;
    }

    /* Check the overrun */
    overrun = gnmax_a->check_rx_overrun();
    if(overrun)
    {
#if defined(VERBOSE_OVERFLOW) && (VERBOSE_OVERFLOW >=  1)
        time(&rawtime);
        timeinfo = localtime (&rawtime);
        fprintf(stdout, "MAX2769 overflow at time %s\n", asctime(timeinfo));
        fflush(stdout);
#else
        fprintf(stdout, "O");
#endif
    }

    /* Read 5 ms */
    bread = gnmax_a->read(bbuf, n_samples);

    if (bread != n_samples)
    {
        n_samples = bread;
//        fprintf (stderr, "usb_read: ret = %d (bufsize: %d) \n", bread, n_samples);
    }
    return n_samples;
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
bool gnmax_Source::w_set_bias(int bias)
{
    return gnmax_a->set_bias(bias);
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
bool gnmax_Source::w_set_ant(int ant)
{
    return gnmax_a->set_ant(ant);
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
bool gnmax_Source::w_set_freq(int freq)
{
    return gnmax_a->set_freq(freq);
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
bool gnmax_Source::w_set_bw(int bw, int zeroif)
{
    return gnmax_a->set_bw(bw, zeroif);
}
/*----------------------------------------------------------------------------------------------*/

