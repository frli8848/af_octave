#
# Copyright (C) 2019 Fredrik Lingvall
#

project (af-octave)

cmake_minimum_required(VERSION 3.8)

# Add path to the various cmake files to detect Matlab, Octave, FTTW, etc.
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# From http://www.coolprop.org/coolprop/wrappers/Octave/index.html
find_package (Octave REQUIRED)

# https://arrayfire.com/building-an-arrayfire-program-with-cmake/

# Add the path to ArrayFire's cmake modules.
if (UNIX)
  set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/local/share/ArrayFire/cmake/")
endif (UNIX)

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
#find_package(CUDA 7.0) # See: http://arrayfire.org/docs/releasenotes.htm (this module comes with CMake).
#set (ArrayFire_EXTRA_LIBS ${ARRAYFIRE_EXTRA_LIBS} ${CMAKE_THREAD_LIBS_INIT} ${CUDA_LIBRARIES} ${NVVM_LIB})

# Octave oct flags.
set (OCT_LD_FLAGS "${CMAKE_LD_FLAGS} ${OCTAVE_LINK_FLAGS}")

#
# Include paths
#

include_directories (
  ${PROJECT_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}/include
  ${OCTAVE_INCLUDE_DIRS}
  ${ArrayFire_INCLUDE_DIRS}
  )

#
# af_conv
#

set (oct_af_conv_SOURCE_FILES
  oct/oct_af_conv.cc
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
  C_STANDARD 99
  CXX_STANDARD 11
  COMPILE_FLAGS "${OCT_FLAGS}"
  LINK_FLAGS ${OCT_LD_FLAGS}
  SUFFIX ".oct" PREFIX "" OUTPUT_NAME "af_conv")

#
# af_fftconv
#

set (oct_af_fftconv_SOURCE_FILES
  oct/oct_af_fftconv.cc
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
  C_STANDARD 99
  CXX_STANDARD 11
  COMPILE_FLAGS "${OCT_FLAGS}"
  LINK_FLAGS ${OCT_LD_FLAGS}
  SUFFIX ".oct" PREFIX "" OUTPUT_NAME "af_fftconv")
