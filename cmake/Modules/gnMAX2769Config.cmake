INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_GNMAX2769 gnMAX2769)

FIND_PATH(
    GNMAX2769_INCLUDE_DIRS
    NAMES gnMAX2769/api.h
    HINTS $ENV{GNMAX2769_DIR}/include
        ${PC_GNMAX2769_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GNMAX2769_LIBRARIES
    NAMES gnuradio-gnMAX2769
    HINTS $ENV{GNMAX2769_DIR}/lib
        ${PC_GNMAX2769_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnMAX2769Target.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GNMAX2769 DEFAULT_MSG GNMAX2769_LIBRARIES GNMAX2769_INCLUDE_DIRS)
MARK_AS_ADVANCED(GNMAX2769_LIBRARIES GNMAX2769_INCLUDE_DIRS)
