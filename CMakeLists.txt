cmake_minimum_required(VERSION 3.0.0)

set(TARGET_PLATFORM linux_x86_64 CACHE STRING "android_aarch64/linux_x86_64")

message(STATUS "TARGET_PLATFORM: ${TARGET_PLATFORM}")

#set(CMAKE_BUILD_TYPE "Release")
#set(CMAKE_BUILD_TYPE "Debug")

set(PROJECT_NAME easy_test)
project(${PROJECT_NAME})

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_options("-std=c++11" "-g" "-O0")
else()
    add_compile_options("-std=c++11" "-O3")
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/MNN/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/easy_timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
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
)
