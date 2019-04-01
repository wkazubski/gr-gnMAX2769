/*----------------------------------------------------------------------------------------------*/
/*! \file gnmax.cpp
//
// FILENAME: gnmax.cpp
//
// DESCRIPTION: Impelements the GNMAX class.
//
// DEVELOPERS: Gregory W. Heckler (2003-2009)
//             Wojciech Kazubski (2019)
//
// LICENSE TERMS: Copyright (c) Gregory W. Heckler 2009
//                Copyright (c) Wojciech Kazubski 2019
//
// This file is based on gn3s.c file, a part of GN3S driver for gnss-sdr project
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

#define ISO_TRANSFER 0

#include "gnmax.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <libusb.h>
#include <time.h>

static char debug = 1; //!< 1 = Verbose

static unsigned char reg0[] = {0xA2,0x91,0x9A,0x30};
static unsigned char reg1[] = {0x85,0x50,0x08,0x81};
static unsigned char reg2[] = {0xEA,0xFF,0x1D,0xC2};
static unsigned char reg3[] = {0x9E,0xC0,0x00,0x83};

static unsigned char buffer[USB_NTRANSFERS][USB_BUFFER_SIZE];
static int bcount;
static int bufptr;

/*----------------------------------------------------------------------------------------------*/
/*!
 * All libusb callback functions should be marked with the LIBUSB_CALL macro
 * to ensure that they are compiled with the same calling convention as libusb.
 */

//libusb_transfer_cb_fn 
static void LIBUSB_CALL callback(libusb_transfer *transfer)
{
    bcount += transfer->actual_length;
    if (bcount > sizeof(buffer))
        bcount -= sizeof(buffer);
    libusb_submit_transfer(transfer);
}
/*----------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------*/
gnmax::gnmax(int _which, int bias, int ant)
{

    bool ret = 0;
    int r;
    which = _which;

    fx2_device  = nullptr;
    fx2_handle  = nullptr;

    r = libusb_init(&ctx);
    if (r < 0)
    {
        printf("Libusb init error: %s\n", libusb_error_name(ret));
        throw (1);
    }

#if defined(LIBUSB_API_VERSION) && (LIBUSB_API_VERSION >=  0x01000106)
    r = libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, 3);
#else
    libusb_set_debug(ctx, 3);
#endif

    fx2_device = usb_fx2_find(GN3S_VID, GN3S_PID);
    if (fx2_device)
    {
        printf("Found MAX2769 Device\n");
    }
    else
    {
        printf("Could not find MAX2769 Device\n");
        throw(1);
    }

    /* Open and configure FX2 device if found... */
    ret = usb_fx2_configure();
    if(ret)
    {
        printf("Could not obtain a handle to the MAX2769 device\n");
        throw(1);
    }

    ret = max2769_configure(bias, ant);
    if(!ret)
    {
        printf("Could not write to MAX2769\n");
        throw(1);
    }

    ret = usb_fx2_start_transfers();
    if(!ret)
    {
        printf("Could not start USB transfers\n");
        throw(1);
    }

}
/*----------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------*/
gnmax::~gnmax()
{
    usrp_xfer(VRQ_XFER, 0);
    usrp_xfer(VRQ_ENABLE, 0);

    libusb_release_interface(fx2_handle, RX_INTERFACE);
    libusb_close(fx2_handle);
    libusb_exit(ctx);

}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
struct libusb_device* gnmax::usb_fx2_find(int vid, int pid)
{
    libusb_device **devs;
    struct libusb_device *fx2 = nullptr;
    long count = 0;
    int ret;

    count = libusb_get_device_list(ctx, &devs);
    if (count < 0)
    {
        printf("Unable to list devices\n");;
    }
    else
    {
        for (int idx = 0; idx < count; ++idx)
        {
            libusb_device *dev = devs[idx];
            libusb_device_descriptor desc = {0};

            ret = libusb_get_device_descriptor (dev, &desc);
            if ((desc.idVendor == vid) && (desc.idProduct == pid))
                 fx2 = dev;
        }
    }

    libusb_free_device_list(devs, 1);
    return fx2;
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
bool gnmax::usb_fx2_configure()
{

    char status = 0;
    int ret;

    ret = libusb_open(fx2_device, &fx2_handle);

    if(ret != 0)
    {
        printf("Could not obtain a handle to MAX2769 Front-End device \n");
        return -1;
    }
    else
    {
        if(debug)
            printf("Received handle for MAX2769 Front-End device \n");

        ret = libusb_set_configuration (fx2_handle, 1);
        if(ret != 0)
        {
            printf("FX2 configure error: %s\n", libusb_error_name(ret));
            libusb_close (fx2_handle);
            status = -1;
        }

        ret = libusb_claim_interface (fx2_handle, RX_INTERFACE);
        if (ret < 0)
        {
            printf("Interface claim error: %s\n", libusb_error_name(ret));
            printf ("\nDevice not programmed? \n");
            libusb_close (fx2_handle);
            status = -1;
       }
        else
            printf("Claimed interface\n");

        ret = libusb_set_interface_alt_setting(fx2_handle, RX_INTERFACE, RX_ALTINTERFACE);
        if (ret !=0)
        {
            printf ("Failed to start alternate setting:%s", libusb_error_name(ret));
            libusb_release_interface (fx2_handle, RX_INTERFACE);
            libusb_close (fx2_handle);
            status = -1;
        }

//        usrp_xfer(VRQ_ENABLE, 1);
        usleep(100);

        return status;
    }
}

/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
bool gnmax::max2769_configure(int bias, int ant)
{
    set_bias_bit(bias);
    set_ant_bit(ant);

    if(write_cmd(VRQ_WRITE_CMD, 0, 0, reg0, sizeof(reg0)) != sizeof (reg0))
        return false;
    if(write_cmd(VRQ_WRITE_CMD, 0, 0, reg1, sizeof(reg1)) != sizeof (reg1))
        return false;
    if(write_cmd(VRQ_WRITE_CMD, 0, 0, reg2, sizeof(reg2)) != sizeof (reg2))
        return false;
    if(write_cmd(VRQ_WRITE_CMD, 0, 0, reg3, sizeof(reg3)) != sizeof (reg3))
        return false;
    return true;
}

/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
bool gnmax::usb_fx2_start_transfers()
{
    int ret;
    bool success = true;
    bufptr = 0;
    bcount = 0;

    for (int i = 0; i < USB_NTRANSFERS; i++)
    {
        transfer[i] = libusb_alloc_transfer(0);
        libusb_fill_bulk_transfer(transfer[i], fx2_handle, RX_ENDPOINT, buffer[i], 
                USB_BUFFER_SIZE, libusb_transfer_cb_fn(&callback), nullptr, USB_TIMEOUT);
        ret = libusb_submit_transfer(transfer[i]);
        if (ret != 0)
        {
            printf ("Failed to start endpoint streaming:%s", libusb_error_name(ret));
            success = false;
        }
    }
    return (success);
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
int gnmax::read(unsigned char *buff, int bytes)
{
    int n;
    if (bcount < bytes)
        n = bcount;
    else
        n = bytes;
    for (int i=0; i<n; i++)
    {
        buff[i] = buffer[0][bufptr++];
        if (bufptr == sizeof(buffer))
            bufptr = 0;
    } 
    return(n);
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
bool gnmax::check_rx_overrun()
{
    bool overrun;

    _get_status(GS_RX_OVERRUN, &overrun);

    return(overrun);
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
bool gnmax::_get_status(int command, bool *trouble)
{
    unsigned char status;

    if(write_cmd(VRQ_GET_STATUS, 0, command, &status, sizeof(status)) != sizeof (status))
        return false;

    *trouble = status;
    return true;
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
bool gnmax::usrp_xfer(char VRQ_TYPE, int start)
{
    int r;

    r = write_cmd(VRQ_TYPE, start, 0, nullptr, 0);

    return(r == 0);
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
int gnmax::write_cmd(int request, int value, int index, unsigned char *bytes, int len)
{
    int requesttype;
    int r;

    requesttype = (request & 0x80) ? VRT_VENDOR_IN : VRT_VENDOR_OUT;
    r = libusb_control_transfer (fx2_handle, requesttype, request, value, index, bytes, len, USB_TIMEOUT);
    if(r < 0)
    {
        /* We get EPIPE if the firmware stalls the endpoint. */
        if(errno != EPIPE)
            printf("usb_control_msg failed: %s\n", libusb_error_name(r));
    }
    return r;
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
void gnmax::set_bias_bit(int bias)
{
    if (bias == 0)
        reg0[2] &= 0x7F;
    else
        reg0[2] |= 0x80;
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
bool gnmax::set_bias(int bias)
{
    set_bias_bit(bias);
    if(write_cmd(VRQ_WRITE_CMD, 0, 0, reg0, sizeof(reg0)) != sizeof (reg0))
        return false;
    return true;
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
void gnmax::set_ant_bit(int ant)
{
    reg0[1] &= 0xF9;
    reg0[1] |= (ant << 1);
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
bool gnmax::set_ant(int ant)
{
    set_ant_bit(ant);
    if(write_cmd(VRQ_WRITE_CMD, 0, 0, reg0, sizeof(reg0)) != sizeof (reg0))
        return false;
    return true;
}
/*----------------------------------------------------------------------------------------------*/
