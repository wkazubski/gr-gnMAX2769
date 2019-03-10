# gr-gnMAX2769

gr-gnMAX2769 is a GNU Radio module intended to be used either with GNSS-SDR as a signal source (in future), or as standalone signal source block instantiated from a GNU Radio flow graph from C++ or using Python (also includes a gnuradio-companion interface).

This document describes how to build the MAX2769 GNU Radio Source USB 2.0 driver.

The driver core is based on GN3S driver available at https://github.com/gnss-sdr/gr-gn3s, which is based on a Gregory W. Hecker driver available at http://github.com/gps-sdr/gps-sdr.


## Install GNU Radio:

You can install GNU Radio through a .deb package or by using PyBOMBS. Please choose only **one** of these two procedures.

### In Ubuntu 12.10 and later, or Debian Jessie or later, install GNU Radio and other dependencies through a .deb package:

~~~~~~ 
$ sudo apt-get install gnuradio-dev libusb-dev libusb-1.0.0-dev
~~~~~~


### Semi-automatic installation of GNU Radio using PyBOMBS:

Downloading, building and installing [GNU Radio](http://gnuradio.org "GNU Radio's Homepage") and all its dependencies is not a simple task. We recommend to use [PyBOMBS](http://gnuradio.org/redmine/projects/pybombs/wiki "Python Build Overlay Managed Bundle System wiki") (Python Build Overlay Managed Bundle System), the GNU Radio install management system that automatically does all the work for you. In a terminal, type:

First of all, install some basic packages:

~~~~~~ 
$ sudo apt-get install git python-pip
~~~~~~ 

Download, build and install PyBOMBS:

~~~~~~ 
$ sudo pip install git+https://github.com/gnuradio/pybombs.git
~~~~~~ 

Add some software recipes (i.e., instructions on how to install software dependencies):

~~~~~~ 
$ pybombs recipes add gr-recipes git+https://github.com/gnuradio/gr-recipes.git
$ pybombs recipes add gr-etcetera git+https://github.com/gnuradio/gr-etcetera.git
~~~~~~ 

Download, build and install GNU Radio, related drivers and some other extra modules into the directory ```/path/to/prefix``` (replace this path by your preferred one, for instance ```$HOME/sdr```):

~~~~~~ 
$ pybombs prefix init /path/to/prefix -a myprefix -R gnuradio-default
~~~~~~ 

This will perform a local installation of the dependencies under ```/path/to/prefix```, so they will not be visible when opening a new terminal. In order to make them available, you will need to set up the adequate environment variables:

~~~~~~ 
$ cd /path/to/prefix
$ . ./setup_env.sh
~~~~~~ 

In case you do not want to use PyBOMBS and prefer to build and install GNU Radio step by step, follow instructions at the [GNU Radio Build Guide](http://gnuradio.org/redmine/projects/gnuradio/wiki/BuildGuide).


## Get the latest version of gr-gnMAX2769:

~~~~~~
$ git clone https://github.com/wkazubski/gr-gnMAX2769
~~~~~~

## Build GR-GN3S:

- Go to gr-gnMAX2769 root directory and compile the driver:

~~~~~~
$ cd gr-gn3s/build
$ cmake ../
$ make
~~~~~~

NOTE: If you have installed GNU Radio via the gnuradio-dev package, you might need to use ```cmake -DCMAKE_INSTALL_PREFIX=/usr ../``` instead of ```cmake ../``` in order to make the module visible from gnuradio-companion once installed.


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

## Build gnss-sdr with the GN3S option enabled:

TBA




