/*----------------------------------------------------------------------------------------------*/
/*! \file gn3s.h
//
// FILENAME: gn3s.h
//
// DESCRIPTION: Defines the GN3S class.
//
// DEVELOPERS: Gregory W. Heckler (2003-2009)
//             Wojciech Kazubski (2019)
//
// LICENSE TERMS: Copyright (c) Gregory W. Heckler 2009
//                Copyright (c) Wojciech Kazubski 2019
//
// This file is based on gn3s.h file, a part of GN3S driver for gnss-sdr project
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


#ifndef GNMAX_H_
#define GNMAX_H_


/* Includes */
/*--------------------------------------------------------------*/
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <libusb.h>
/*--------------------------------------------------------------*/


/* FX2 Configuration Structure */
/*--------------------------------------------------------------*/
struct fx2Config
{
    int interface;
    int altinterface;
    libusb_device_handle *udev;
};
/*--------------------------------------------------------------*/


/* FX2 Stuff */
/*--------------------------------------------------------------*/
#define RX_ENDPOINT      (0x86)
#define VRT_VENDOR_IN    (0xC0)
#define VRT_VENDOR_OUT   (0x40)
#define RX_INTERFACE     (2)
#define RX_ALTINTERFACE  (0)
#define VRQ_XFER         (0x01)
#define VRQ_ENABLE       (0x10)
#define VRQ_WRITE_CMD    (0x20)
#define VRQ_GET_STATUS   (0x80)
#define GS_RX_OVERRUN    (1)  //!< Returns 1 byte
/*--------------------------------------------------------------*/


/* GN3S Stuff */
/*--------------------------------------------------------------*/
#define GN3S_VID         (0x1781)
#define GN3S_PID         (0x0B3C)
#define PROG_SET_CMD     (0xE600)
#define USB_BUFFER_SIZE  (16384)           //!< 8 MB
#define USB_BLOCK_SIZE   (512)             //!< 16KB is hard limit
#define USB_NBLOCKS      (USB_BUFFER_SIZE / USB_BLOCK_SIZE)
#define USB_NTRANSFERS   (16)
#define USB_TIMEOUT      (1000)
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*! \ingroup CLASSES
 *
 */
class gnmax
{

    private:

        /* First or second board */
        int which;

        /* GN3S FX2 Stuff */
        struct fx2Config fx2_config;
        struct libusb_device *fx2_device;
        struct libusb_device_handle *fx2_handle;
        struct libusb_transfer *transfer[USB_NTRANSFERS];

        /* USB Stuff */
        libusb_context *ctx = nullptr;

        void set_bias_bit(int bias);
        void set_ant_bit(int ant);

    public:

        gnmax(int _which, int bias, int ant);   //!< Constructor
        ~gnmax();            //!< Destructor

        /* FX2 functions */
        struct libusb_device* usb_fx2_find(int vid, int pid);
        bool usb_fx2_configure();
        bool max2769_configure(int bias, int ant);
        bool usb_fx2_start_transfers();
        int read(unsigned char *buff, int bytes);
//        int read(void *buff, int bytes);
        int write_cmd(int request, int value, int index, unsigned char *bytes, int len);
        bool _get_status(int which, bool *trouble);
        bool check_rx_overrun();
        bool usrp_xfer(char VRQ_TYPE, int start);
//        static void LIBUSB_CALL iso_callback(libusb_transfer *transfer);
        bool set_bias(int bias);
        bool set_ant(int ant);

};
/*--------------------------------------------------------------*/


#endif /*GNMAX_H_ */
