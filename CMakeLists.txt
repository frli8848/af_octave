#
# Copyright (C) 2019,2023 Fredrik Lingvall
#

#project (af-octave CXX CUDA)
project (af CXX)

cmake_minimum_required(VERSION 3.10)

# Add path to the various cmake files to detect Matlab, Octave, FTTW, etc.
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# https://arrayfire.com/building-an-arrayfire-program-with-cmake/
#
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

add_subdirectory(oct)
add_subdirectory(mex)
