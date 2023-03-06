#
# Copyright (C) 2023 Fredrik Lingvall
#

#project (af-mexave CXX CUDA)
project (af-matlab CXX)

cmake_minimum_required(VERSION 3.10)

# Add path to the various cmake files to detect Matlab, Octave, FTTW, etc.
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")


# https://arrayfire.com/building-an-arrayfire-program-with-cmake/

# Add the path to ArrayFire's cmake modules.
#if (UNIX)
#  set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/local/share/ArrayFire/cmake/")
#endif (UNIX)

find_package (ArrayFire REQUIRED)

if (ArrayFire_FOUND)

  message (STATUS "ArrayFire version: ${ArrayFire_VERSION}")
  message (STATUS "ArrayFire include: ${ArrayFire_INCLUDE_DIRS}")
  message (STATUS "ArrayFire default libs: ${ArrayFire_LIBRARIES}")
  message (STATUS "ArrayFire Unified libs: ${ArrayFire_Unified_LIBRARIES}")

  if (ArrayFire_Unified_FOUND) # Prefer the Unified backend
    set (AF_LIBRARIES ${ArrayFire_Unified_LIBRARIES})
  else (ArrayFire_Unified_FOUND)
    set (AF_LIBRARIES ${ArrayFire_LIBRARIES}) # Defaults to CUDA?
  endif (ArrayFire_Unified_FOUND)

  if (ArrayFire_CPU_FOUND)
    message (STATUS "ArrayFire CPU libs: ${ArrayFire_CPU_LIBRARIES}")
  endif (ArrayFire_CPU_FOUND)

  if (ArrayFire_CUDA_FOUND)
    message (STATUS "ArrayFire CUDA libs: ${ArrayFire_CUDA_LIBRARIES}")
  endif (ArrayFire_CUDA_FOUND)

  if (ArrayFire_OpenCL_FOUND)
    message (STATUS "ArrayFire OpenCL libs: ${ArrayFire_OpenCL_LIBRARIES}")
  endif (ArrayFire_OpenCL_FOUND)
endif (ArrayFire_FOUND)

# Or if you intend to use CUDA, you need it as well as NVVM:
#find_package(CUDA 8.0) # See: http://arrayfire.org/docs/releasenotes.htm (this module comes with CMake).
#set (ArrayFire_EXTRA_LIBS ${ARRAYFIRE_EXTRA_LIBS} ${CMAKE_THREAD_LIBS_INIT} ${CUDA_LIBRARIES} ${NVVM_LIB})

find_package (Matlab)

if (Matlab_FOUND)

  # mex libs
  #set (MEX_LD_FLAGS "${CMAKE_LD_FLAGS} ${Matlab_MEX_LIBRARY} ${Matlab_MX_LIBRARY}")
  message (STATUS "Matlab_ROOT_DIR ${Matlab_ROOT_DIR}")
  message (STATUS "Matlab_MAIN_PROGRAM ${Matlab_MAIN_PROGRAM}")
  message (STATUS "Matlab_INCLUDE_DIRS ${Matlab_INCLUDE_DIRS}")
  message (STATUS "Matlab_LIBRARIES  ${Matlab_LIBRARIES}")

  # MATLAB mex flags.
  set (MEX_LD_FLAGS "${CMAKE_LD_FLAGS} ${OCTAVE_LINK_FLAGS}")

  #
  # Include paths
  #

  set (AF_MEX_INCLUDE_DIRS
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${Matlab_INCLUDE_DIRS}
    ${ArrayFire_INCLUDE_DIRS}
  )

  #
  # af_init
  #

  set (mex_af_init_SOURCE_FILES
    mex_af_init.cc
  )

  matlab_add_mex (NAME mex_af_init MODULE
    SRC ${mex_af_init_SOURCE_FILES}
    LINK_TO ${AF_LIBRARIES} ${ArrayFire_EXTRA_LIBS}
    OUTPUT_NAME "af_init"
  )

  set_target_properties (mex_af_init PROPERTIES
    CXX_STANDARD 11
    INCLUDE_DIRECTORIES "${AF_MEX_INCLUDE_DIRS}"
  )

  #
  # af_test
  #

  set (mex_af_test_SOURCE_FILES
    mex_af_test.cc
  )

  matlab_add_mex (NAME mex_af_test MODULE
    SRC ${mex_af_test_SOURCE_FILES}
    LINK_TO ${AF_LIBRARIES} ${ArrayFire_EXTRA_LIBS}
    OUTPUT_NAME "af_test"
  )

  set_target_properties (mex_af_test PROPERTIES
    CXX_STANDARD 11
    INCLUDE_DIRECTORIES "${AF_MEX_INCLUDE_DIRS}"
  )

  #
  # af_conv
  #

  set (mex_af_conv_SOURCE_FILES
    mex_af_conv.cc
  )

  matlab_add_mex (NAME mex_af_conv MODULE
    SRC ${mex_af_conv_SOURCE_FILES}
    LINK_TO ${AF_LIBRARIES} ${ArrayFire_EXTRA_LIBS}
    OUTPUT_NAME "af_conv"
  )

  set_target_properties (mex_af_conv PROPERTIES
    CXX_STANDARD 11
    INCLUDE_DIRECTORIES "${AF_MEX_INCLUDE_DIRS}"
  )

  #
  # af_fftconv
  #

  set (mex_af_fftconv_SOURCE_FILES
    mex_af_fftconv.cc
  )

  matlab_add_mex (NAME mex_af_fftconv MODULE
    SRC ${mex_af_fftconv_SOURCE_FILES}
    LINK_TO ${AF_LIBRARIES} ${ArrayFire_EXTRA_LIBS}
    OUTPUT_NAME "af_fftconv"
  )

  set_target_properties (mex_af_fftconv PROPERTIES
    CXX_STANDARD 11
    INCLUDE_DIRECTORIES "${AF_MEX_INCLUDE_DIRS}"
  )

endif (Matlab_FOUND)
