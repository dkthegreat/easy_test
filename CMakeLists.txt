cmake_minimum_required(VERSION 3.0.0)

set(TARGET_PLATFORM linux_x86_64 CACHE STRING "android_aarch64/linux_x86_64")

message(STATUS "TARGET_PLATFORM: ${TARGET_PLATFORM}")

#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "Debug")

set(PROJECT_NAME easy_test)
project(${PROJECT_NAME})

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    #add_compile_options("-std=c++11" "-g" "-O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGES} -std=c++11 -g -O0")
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGES} -std=c99 -g -O0")
else()
    #add_compile_options("-std=c++11" "-O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGES} -std=c++11 -O3")
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGES} -std=c99 -O3")
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/MNN/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nv12_jpeg_convert/
)

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/easy_timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/easy_auto_file_io.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/nv12_jpeg_convert/ErrorDefine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nv12_jpeg_convert/JpegToYUV.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nv12_jpeg_convert/YUVToJpeg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nv12_jpeg_convert/nv12_jpeg_convert_test.cpp
)

if ("${TARGET_PLATFORM}" STREQUAL "linux_x86_64")
    set(LIBMNN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/MNN/libs/linux_x86_64)
    set(DEPENS_LIBS pthread)
endif()

if ("${TARGET_PLATFORM}" STREQUAL "android_aarch64")
    set(LIBMNN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/MNN/libs/android_aarch64)
    set(DEPENS_LIBS log)
endif()

target_link_libraries(
    ${PROJECT_NAME}
    ${LIBMNN_DIR}/libMNN.so
    ${DEPENS_LIBS}
    -lturbojpeg
)
