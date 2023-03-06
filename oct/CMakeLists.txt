#
# Copyright (C) 2019 Fredrik Lingvall
#

#project (af-octave CXX CUDA)
project (af-octave CXX)

cmake_minimum_required(VERSION 3.10)

# Add path to the various cmake files to detect Matlab, Octave, FTTW, etc.
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# From http://www.coolprop.org/coolprop/wrappers/Octave/index.html
find_package (Octave REQUIRED)

if (Octave_FOUND)

  # Octave oct flags.
  set (OCT_LD_FLAGS "${CMAKE_LD_FLAGS} ${OCTAVE_LINK_FLAGS}")

  #
  # Include paths
  #

  set (AF_MEX_INCLUDE_DIRS
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${OCTAVE_INCLUDE_DIRS}
    ${ArrayFire_INCLUDE_DIRS}
  )

  #
  # af_init
  #

  set (oct_af_init_SOURCE_FILES
    oct_af_init.cc
  )

  add_library (oct_af_init MODULE
    ${oct_af_init_SOURCE_FILES}
  )

  target_link_libraries (oct_af_init
    ${OCTAVE_LIBRARIES}
    ${AF_LIBRARIES}
    ${ArrayFire_EXTRA_LIBS}
  )

  set_target_properties (oct_af_init PROPERTIES
    CXX_STANDARD 11
    COMPILE_FLAGS "${OCT_FLAGS}"
    LINK_FLAGS ${OCT_LD_FLAGS}
    SUFFIX ".oct" PREFIX "" OUTPUT_NAME "af_init")

  #
  # af_test
  #

  set (oct_af_test_SOURCE_FILES
    oct_af_test.cc
  )

  add_library (oct_af_test MODULE
    ${oct_af_test_SOURCE_FILES}
  )

  target_link_libraries (oct_af_test
    ${OCTAVE_LIBRARIES}
    ${AF_LIBRARIES}
    ${ArrayFire_EXTRA_LIBS}
  )

  set_target_properties (oct_af_test PROPERTIES
    CXX_STANDARD 11
    COMPILE_FLAGS "${OCT_FLAGS}"
    LINK_FLAGS ${OCT_LD_FLAGS}
    SUFFIX ".oct" PREFIX "" OUTPUT_NAME "af_test")

  #
  # af_conv
  #

  set (oct_af_conv_SOURCE_FILES
    oct_af_conv.cc
  )

  add_library (oct_af_conv MODULE
    ${oct_af_conv_SOURCE_FILES}
  )

  target_link_libraries (oct_af_conv
    ${OCTAVE_LIBRARIES}
    ${AF_LIBRARIES}
    ${ArrayFire_EXTRA_LIBS}
  )

  set_target_properties (oct_af_conv PROPERTIES
    CXX_STANDARD 11
    COMPILE_FLAGS "${OCT_FLAGS}"
    LINK_FLAGS ${OCT_LD_FLAGS}
    SUFFIX ".oct" PREFIX "" OUTPUT_NAME "af_conv")

  #
  # af_fftconv
  #

  set (oct_af_fftconv_SOURCE_FILES
    oct_af_fftconv.cc
  )

  add_library (oct_af_fftconv MODULE
    ${oct_af_fftconv_SOURCE_FILES}
  )

  target_link_libraries (oct_af_fftconv
    ${OCTAVE_LIBRARIES}
    ${AF_LIBRARIES}
    ${ArrayFire_EXTRA_LIBS}
  )

  set_target_properties (oct_af_fftconv PROPERTIES
    CXX_STANDARD 11
    COMPILE_FLAGS "${OCT_FLAGS}"
    LINK_FLAGS ${OCT_LD_FLAGS}
    SUFFIX ".oct" PREFIX "" OUTPUT_NAME "af_fftconv")

endif (Octave_FOUND)
