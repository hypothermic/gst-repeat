cmake_minimum_required(VERSION 3.15)
project(gst_repeat C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig)

pkg_check_modules(GST REQUIRED gstreamer-1.0>=1.1
                               gstreamer-app-1.0>=1.1)

add_executable(gst_repeat src/main.c src/error.h src/log.c src/log.h)

target_include_directories(gst_repeat PRIVATE ${GST_INCLUDE_DIRS})
target_link_libraries(gst_repeat ${GST_LIBRARIES})