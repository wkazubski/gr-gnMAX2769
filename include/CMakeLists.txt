# Copyright (C) 2012-2019  (see AUTHORS file for a list of contributors)
#
# This file is based on include/CMakeLists.txt file, a part of GN3S
# driver for gnss-sdr project
#
# This file is part of GNSS-SDR.
#
# GNSS-SDR is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# GNSS-SDR is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
#

########################################################################
# Install public header files
########################################################################
install(FILES
    gnmax_api.h
    gnmax_source_cc.h
    gnmax_source.h
    gnmax_defines.h
    gnmax.h
    libusb_types.h
    DESTINATION include/gnMAX2769
)
