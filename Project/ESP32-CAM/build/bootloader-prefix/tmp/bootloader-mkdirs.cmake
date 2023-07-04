# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "F:/ESP-IDF/Espressif/frameworks/esp-idf-v4.4.4/components/bootloader/subproject"
  "D:/Desktop/ESP-CMD/esp-who/examples/single_chip/camera_web_server/build/bootloader"
  "D:/Desktop/ESP-CMD/esp-who/examples/single_chip/camera_web_server/build/bootloader-prefix"
  "D:/Desktop/ESP-CMD/esp-who/examples/single_chip/camera_web_server/build/bootloader-prefix/tmp"
  "D:/Desktop/ESP-CMD/esp-who/examples/single_chip/camera_web_server/build/bootloader-prefix/src/bootloader-stamp"
  "D:/Desktop/ESP-CMD/esp-who/examples/single_chip/camera_web_server/build/bootloader-prefix/src"
  "D:/Desktop/ESP-CMD/esp-who/examples/single_chip/camera_web_server/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Desktop/ESP-CMD/esp-who/examples/single_chip/camera_web_server/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
