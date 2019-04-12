# Copyright (C) 2012-2019  (see AUTHORS file for a list of contributors)
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
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

add_library(gnuradio-gnmax2769 SHARED gnmax_source_cc.cc gnmax_source.cc gnmax.cc)
target_link_libraries(gnuradio-gnmax2769 ${Boost_LIBRARIES} ${GNURADIO_RUNTIME_LIBRARIES} ${LIBUSB_LIBRARIES})
set_target_properties(gnuradio-gnmax2769 PROPERTIES DEFINE_SYMBOL "gr_gnmax2769_EXPORTS")

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-gnmax2769
    LIBRARY DESTINATION lib${LIB_SUFFIX}
    COMPONENT "gnuradio-gnmax2769"
)

########################################################################
# Build and register unit test
########################################################################
find_package(Boost COMPONENTS unit_test_framework)

include(GrTest)
set(GR_TEST_TARGET_DEPS gnuradio-gnmax2769)
#turn each test cpp file into an executable with an int main() function
add_definitions(-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN)

add_executable(qa_gnmax_source_cc qa_gnmax_source_cc.cc)
target_link_libraries(qa_gnmax_source_cc gnuradio-gnmax2769 ${Boost_LIBRARIES} ${LIBUSB_LIBRARIES})
GR_ADD_TEST(qa_gnmax_source_cc qa_gnmax_source_cc)

