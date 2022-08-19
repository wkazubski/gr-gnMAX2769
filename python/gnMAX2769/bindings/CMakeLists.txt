# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT gnMAX2769_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT gnMAX2769_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND gnMAX2769_python_files
    gnmax_source_cc_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(gnMAX2769
   ../../..
   gr::gnMAX2769
   "${gnMAX2769_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(TARGET gnMAX2769_python POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:gnMAX2769_python>
    ${CMAKE_BINARY_DIR}/test_modules/gnuradio/gnMAX2769/
)

install(TARGETS gnMAX2769_python DESTINATION ${GR_PYTHON_DIR}/gnMAX2769 COMPONENT pythonapi)
