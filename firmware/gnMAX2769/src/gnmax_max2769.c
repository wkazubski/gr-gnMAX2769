/* 
 * Code from: USRP - Universal Software Radio Peripheral (GNU Radio) 
 * 
 * Initial modifications by: 
 * 
 * Stephan Esterhuizen, Aerospace Engineering Sciences 
 * University of Colorado at Boulder 
 * Boulder CO, USA 
 *  
 * Further modifications for use with the SiGe USB module to accompany 
 * the textbook: "A Software-Defined GPS and Galileo Receiver: A 
 * Single-Frequency Approach" by Kai Borre, Dennis Akos, et.al. by: 
 * 
 * Marcus Junered, GNSS Research Group 
 * Lulea University of Technology 
 * Lulea, Sweden  
 * junered@ltu.se 
 * 
 *Futher modified for usage with a new frontend PCB 
 * by Oscar Isoz GNSS Research Group 
 * Lulea University of Technology 
 * Lulea, Sweden 
 * --------------------------------------------------------------------- 
 * 
 * GN3S - GNSS IF Streamer for Windows 
 * Copyright (C) 2006 Marcus Junered 
 * 
 * ---------------------------------------------------------------------
 *
 * GNMAX - Modified for MAX2769 chip
 * Copyright (C) 2017 Wojciech Kazubski
 *
 * ---------------------------------------------------------------------
 *
 * This program is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */ 
 
 
#include "gnmax_max2769.h"
#include "syncdelay.h"

#define SPI_CS     0x80 //CS: set low to write data, high after finishing
#define SPI_SCK    0x08 //SDK serial clock
#define SHDN       0x02 //SHDN pin, device active when high
#define SPI_SDATA  0x01 //SDATA serial data
#define LEN        4    //message lenght in bytes

static unsigned short idx = 0;


char init_max2769(void)
{
  IOA |= SPI_CS|SHDN|SPI_SDATA;
  OEA |= SPI_CS|SPI_SCK|SHDN|SPI_SDATA;
  OED = 0x00;

  SYNCDELAY;

  IOA |= SPI_SCK; // SCK: _/
  SYNCDELAY;

  IOA &= ~SPI_SCK; // SCK: \_
  SYNCDELAY;
  return 0;
}

char enable_max2769(void)
{
  IOA |= SHDN;
  return 0;
}

char disable_max2769(void)
{
  IOA &= ~SHDN;
  return 0;
}

void spi_write_byte(unsigned char byte)
{
  unsigned char mask = 0x80;
  do {
    if(byte & mask)
      IOA |= SPI_SDATA;
    else
      IOA &= ~SPI_SDATA;
    SYNCDELAY;

    IOA |= SPI_SCK; // SCK: _/
    SYNCDELAY;

    IOA &= ~SPI_SCK; // SCK: \_
    SYNCDELAY;

    IOA |= SPI_SCK; // SCK: _/
    SYNCDELAY;

    mask = mask >> 1;
  } while(mask != 0);
}

char write_max2769(__xdata unsigned char *buf)
{
  int i;
  IOA &= ~SPI_SCK; // SCK: \_
  SYNCDELAY;

  IOA &= ~SPI_CS;
  SYNCDELAY;
  SYNCDELAY;

  for(i = 0; i < LEN; i++)
    spi_write_byte(buf[i]);

  IOA |= SPI_CS;
  SYNCDELAY;
  SYNCDELAY;

  IOA |= SPI_SDATA;

  IOA |= SPI_SCK; // SCK: _/
  SYNCDELAY;

  IOA &= ~SPI_SCK; // SCK: \_
  SYNCDELAY;

  IOA |= SPI_SCK;  // SCK: _/
  SYNCDELAY;

  return 0;
}

char status_max2769(void)
{
  return IOD;
}

short fifo_status() {
  return idx;
}


