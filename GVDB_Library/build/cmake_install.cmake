# Install script for directory: C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/lutca/source/repos/GVDB_Project/_output")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/lutca/source/repos/GVDB_Project/_output/bin/")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "C:/Users/lutca/source/repos/GVDB_Project/_output/bin" TYPE DIRECTORY FILES "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/build/Debug/" FILES_MATCHING REGEX "/[^/]*\\.dll$" REGEX "/[^/]*\\.glsl$" REGEX "/[^/]*\\.ptx$" REGEX "/[^/]*\\.so$")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/lutca/source/repos/GVDB_Project/_output/bin/")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "C:/Users/lutca/source/repos/GVDB_Project/_output/bin" TYPE DIRECTORY FILES "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/build/Release/" FILES_MATCHING REGEX "/[^/]*\\.dll$" REGEX "/[^/]*\\.glsl$" REGEX "/[^/]*\\.ptx$" REGEX "/[^/]*\\.so$")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/lutca/source/repos/GVDB_Project/_output/bin/")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "C:/Users/lutca/source/repos/GVDB_Project/_output/bin" TYPE DIRECTORY FILES "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/build/MinSizeRel/" FILES_MATCHING REGEX "/[^/]*\\.dll$" REGEX "/[^/]*\\.glsl$" REGEX "/[^/]*\\.ptx$" REGEX "/[^/]*\\.so$")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/lutca/source/repos/GVDB_Project/_output/bin/")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "C:/Users/lutca/source/repos/GVDB_Project/_output/bin" TYPE DIRECTORY FILES "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/build/RelWithDebInfo/" FILES_MATCHING REGEX "/[^/]*\\.dll$" REGEX "/[^/]*\\.glsl$" REGEX "/[^/]*\\.ptx$" REGEX "/[^/]*\\.so$")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/lutca/source/repos/GVDB_Project/_output/lib/")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "C:/Users/lutca/source/repos/GVDB_Project/_output/lib" TYPE DIRECTORY FILES "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/build/Debug/" FILES_MATCHING REGEX "/[^/]*\\.lib$" REGEX "/[^/]*\\.exp$" REGEX "/[^/]*\\.ilk$" REGEX "/[^/]*\\.pdb$")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/lutca/source/repos/GVDB_Project/_output/lib/")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "C:/Users/lutca/source/repos/GVDB_Project/_output/lib" TYPE DIRECTORY FILES "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/build/Release/" FILES_MATCHING REGEX "/[^/]*\\.lib$" REGEX "/[^/]*\\.exp$" REGEX "/[^/]*\\.ilk$" REGEX "/[^/]*\\.pdb$")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/lutca/source/repos/GVDB_Project/_output/lib/")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "C:/Users/lutca/source/repos/GVDB_Project/_output/lib" TYPE DIRECTORY FILES "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/build/MinSizeRel/" FILES_MATCHING REGEX "/[^/]*\\.lib$" REGEX "/[^/]*\\.exp$" REGEX "/[^/]*\\.ilk$" REGEX "/[^/]*\\.pdb$")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/lutca/source/repos/GVDB_Project/_output/lib/")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "C:/Users/lutca/source/repos/GVDB_Project/_output/lib" TYPE DIRECTORY FILES "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/build/RelWithDebInfo/" FILES_MATCHING REGEX "/[^/]*\\.lib$" REGEX "/[^/]*\\.exp$" REGEX "/[^/]*\\.ilk$" REGEX "/[^/]*\\.pdb$")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/lutca/source/repos/GVDB_Project/_output/include/app_perf.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/gvdb.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/gvdb_allocator.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/gvdb_camera.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/gvdb_cutils.cuh;C:/Users/lutca/source/repos/GVDB_Project/_output/include/gvdb_model.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/gvdb_node.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/gvdb_render.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/gvdb_scene.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/gvdb_types.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/gvdb_vec.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/gvdb_volume_3D.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/gvdb_volume_base.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/gvdb_volume_gvdb.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/loader_ObjarReader.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/loader_OBJReader.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/loader_Parser.h;C:/Users/lutca/source/repos/GVDB_Project/_output/include/string_helper.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Users/lutca/source/repos/GVDB_Project/_output/include" TYPE FILE FILES
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/app_perf.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/gvdb.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/gvdb_allocator.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/gvdb_camera.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/gvdb_cutils.cuh"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/gvdb_model.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/gvdb_node.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/gvdb_render.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/gvdb_scene.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/gvdb_types.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/gvdb_vec.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/gvdb_volume_3D.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/gvdb_volume_base.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/gvdb_volume_gvdb.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/loader_ObjarReader.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/loader_OBJReader.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/loader_Parser.h"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/src/string_helper.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/lutca/source/repos/GVDB_Project/_output/include/cuda_gvdb.cuh;C:/Users/lutca/source/repos/GVDB_Project/_output/include/cuda_gvdb_dda.cuh;C:/Users/lutca/source/repos/GVDB_Project/_output/include/cuda_gvdb_geom.cuh;C:/Users/lutca/source/repos/GVDB_Project/_output/include/cuda_gvdb_nodes.cuh;C:/Users/lutca/source/repos/GVDB_Project/_output/include/cuda_gvdb_operators.cuh;C:/Users/lutca/source/repos/GVDB_Project/_output/include/cuda_gvdb_particles.cuh;C:/Users/lutca/source/repos/GVDB_Project/_output/include/cuda_gvdb_raycast.cuh;C:/Users/lutca/source/repos/GVDB_Project/_output/include/cuda_gvdb_scene.cuh;C:/Users/lutca/source/repos/GVDB_Project/_output/include/cuda_math.cuh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Users/lutca/source/repos/GVDB_Project/_output/include" TYPE FILE FILES
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/kernels/cuda_gvdb.cuh"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/kernels/cuda_gvdb_dda.cuh"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/kernels/cuda_gvdb_geom.cuh"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/kernels/cuda_gvdb_nodes.cuh"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/kernels/cuda_gvdb_operators.cuh"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/kernels/cuda_gvdb_particles.cuh"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/kernels/cuda_gvdb_raycast.cuh"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/kernels/cuda_gvdb_scene.cuh"
    "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/kernels/cuda_math.cuh"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/lutca/source/repos/GVDB_Project/UE_GVDB/GVDB_Library/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
