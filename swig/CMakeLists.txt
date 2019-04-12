# Copyright (C) 2012-2015  (see AUTHORS file for a list of contributors)
#
# This file is a part of gr-gnMAX2769 projest and is based on 
# docs/CMakeLists.txt file, a part of GN3S driver for gnss-sdr project
#
# gr-gnMAX2769 is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# gr-gnMAX2769 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with gr-gnMAX2769; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Include swig generation macros
########################################################################
find_package(SWIG)
find_package(PythonLibs)
if(NOT SWIG_FOUND OR NOT PYTHONLIBS_FOUND)
    return()
endif()
include(GrSwig)
include(GrPython)

########################################################################
# Setup swig generation
########################################################################
set(GNURADIO_RUNTIME_SWIG_INCLUDE_DIRS ${GNURADIO_RUNTIME_INCLUDE_DIRS}/gnuradio/swig)

set(GR_SWIG_INCLUDE_DIRS
    ${GR_GNMAX_INCLUDE_DIRS}
    ${GNURADIO_RUNTIME_SWIG_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

set(GR_SWIG_LIBRARIES gnuradio-gnmax2769 gnuradio-runtime)
set(GR_SWIG_DOC_FILE ${CMAKE_CURRENT_BINARY_DIR}/gnmax_swig_doc.i)
set(GR_SWIG_DOC_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include)

GR_SWIG_MAKE(gnmax_swig gnmax_swig.i)

########################################################################
# Install the build swig module
########################################################################
GR_SWIG_INSTALL(TARGETS gnmax_swig DESTINATION ${GR_PYTHON_DIR}/gnMAX2769)

########################################################################
# Install swig .i files for development
########################################################################
install(
    FILES
    gnmax_swig.i
    ${CMAKE_CURRENT_BINARY_DIR}/gnmax_swig_doc.i
    DESTINATION ${GR_INCLUDE_DIR}/gnMAX2769/swig
)
