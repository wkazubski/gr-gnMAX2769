# gr-gnMAX2769

gr-gnMAX2769 is a GNU Radio module intended to be used either with GNSS-SDR as a signal source (in future), or as standalone signal source block instantiated from a GNU Radio flow graph from C++ or using Python (also includes a gnuradio-companion interface).

This document describes how to build the MAX2769 GNU Radio Source USB 2.0 driver.

The driver core is based on GN3S driver available at https://github.com/gnss-sdr/gr-gn3s, which is based on a Gregory W. Hecker driver available at http://github.com/gps-sdr/gps-sdr.


## Install GNU Radio:

You can install GNU Radio through a distribution packages provided by your favorite Linux distribution or by using PyBOMBS. In this case follow the instructions provided by GNU Radio.

## Get the latest version of gr-gnMAX2769:

~~~~~~
$ git clone https://github.com/wkazubski/gr-gnMAX2769
~~~~~~

## Build gr-gnMAX2769:

- Go to gr-gnMAX2769 root directory and compile the driver:

~~~~~~
$ mkdir -p gr-gnMAX2769/build
$ cd gr-gnMAX2769/build
$ cmake ../
$ make
~~~~~~

NOTE: If you have installed GNU Radio via the repository packages, you might need to use ```cmake -DCMAKE_INSTALL_PREFIX=/usr ../``` instead of ```cmake ../``` in order to make the module visible from gnuradio-companion once installed.

- If everything went fine, install the driver as root

~~~~~~
$ sudo make install
~~~~~~

When using Ubuntu, you might need to type this line when the installation is finished:

~~~~~~
$ sudo ldconfig
~~~~~~

## Check that the module is usable by gnuradio-companion
 
Open gnuradio-companion and check the MAX2769 Source module under the MAX2769 tab. In order to gain access to USB ports, gnuradio-companion should be used as root or MAX2769 udev module has to be installed.

## Build gnss-sdr with the gnmax option enabled:

TBA




