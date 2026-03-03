# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/ric/Scrivania/PicoW-Robotic-Arm/src/_deps/picotool-src"
  "/home/ric/Scrivania/PicoW-Robotic-Arm/src/_deps/picotool-build"
  "/home/ric/Scrivania/PicoW-Robotic-Arm/src/_deps"
  "/home/ric/Scrivania/PicoW-Robotic-Arm/src/src/picotool/tmp"
  "/home/ric/Scrivania/PicoW-Robotic-Arm/src/src/picotool/src/picotoolBuild-stamp"
  "/home/ric/Scrivania/PicoW-Robotic-Arm/src/src/picotool/src"
  "/home/ric/Scrivania/PicoW-Robotic-Arm/src/src/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/ric/Scrivania/PicoW-Robotic-Arm/src/src/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/ric/Scrivania/PicoW-Robotic-Arm/src/src/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
