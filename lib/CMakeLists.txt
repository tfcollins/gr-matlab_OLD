# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS} "/home/travis/git/custom-blocks/gr-matlab/so/")

list(APPEND matlab_sources
    fftmat_impl.cc
)

set(matlab_sources "${matlab_sources}" PARENT_SCOPE)
if(NOT matlab_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT matlab_sources)


set(matlablib "/home/travis/git/custom-blocks/gr-matlab/so/libfft_from_matlab.so")

add_library(gnuradio-matlab SHARED ${matlab_sources})

MESSAGE(STATUS "${matlab_sources}")
target_link_libraries(gnuradio-matlab ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES} ${matlablib})
set_target_properties(gnuradio-matlab PROPERTIES DEFINE_SYMBOL "gnuradio_matlab_EXPORTS")
MESSAGE(STATUS "${GNURADIO_ALL_LIBRARIES}")
MESSAGE(STATUS "${Boost_LIBRARIES}")


if(APPLE)
    set_target_properties(gnuradio-matlab PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-matlab
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_matlab_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_matlab.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_matlab.cc
)


#link_directories(/home/travis/git/custom-blocks/gr-matlab/lib)

add_executable(test-matlab ${test_matlab_sources})

target_link_libraries(
  test-matlab
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-matlab
  fft_from_matlab
)

GR_ADD_TEST(test_matlab test-matlab)
