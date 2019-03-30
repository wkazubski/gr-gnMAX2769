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
gnmax_Source::gnmax_Source()
{

    Open_GNMAX();

    overflw = soverflw = 0;
    agc_scale = 1;

    /* Assign to base */
    ms_count = 0;
    flag_first_read=true;
    fprintf(stdout, "Creating GPS Source\n");

}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
gnmax_Source::~gnmax_Source()
{

    Close_GNMAX();
    fprintf(stdout, "Destructing GPS Source\n");
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
void gnmax_Source::Read(gnmax_ms_packet *_p, int n_samples)
{

    Read_GNMAX(_p, n_samples);
    ms_count++;
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
void gnmax_Source::Open_GNMAX()
{


    /* Create the object */
    gnmax_a = new gnmax(0);


    /* Everything is super! */
    //fprintf(stdout,"GNMAX Start\n");

}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
void gnmax_Source::Close_GNMAX()
{

    if(gnmax_a != NULL) delete gnmax_a;
    //fprintf(stdout,"Destructing GN3S\n");

}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
void gnmax_Source::Read_GNMAX(gnmax_ms_packet *_p, int n_samples)
{

    int bread;
    int started=0;
    int check;
    bool overrun;

    short int *pbuff;

    int BUFSIZE=n_samples*2;
    if (flag_first_read==true)
    {
        /* Start transfer */
        while(!started)
        {
            usleep(100);
            started = gnmax_a->usrp_xfer(VRQ_XFER, 1);
        }
        printf("started TX\n");
        flag_first_read=false;
    }

    /* Check the overrun */
    overrun = gnmax_a->check_rx_overrun();
    if(overrun)
    {
        time(&rawtime);
        timeinfo = localtime (&rawtime);
        fprintf(stdout, "MAX2769 overflow at time %s\n", asctime(timeinfo));
        fflush(stdout);
    }

    /* Read 5 ms */
    bread = gnmax_a->read(gbuff, n_samples);

    if (bread != n_samples)
    {
        fprintf (stderr, "usb_read: ret = %d (bufsize: %d) \n", bread, n_samples);
//WK         fprintf (stderr, "%s\n", libusb_error_name(libusb_error));
    }

// Store IF data as 8bit signed values
    pbuff = (short int *)&buff[0];

   int i = 0;
   for (int j=0;j<n_samples;j++)
   {
       pbuff[i++] = (short int)((gbuff[j] & 0x30) >> 3) - 3;
       pbuff[i++] = (short int)((gbuff[j] & 0xC0) >> 5) - 3;
   }

/* Copy to destination */
    memcpy(_p->data, pbuff, n_samples*sizeof(GNMAX_CPX));
}

