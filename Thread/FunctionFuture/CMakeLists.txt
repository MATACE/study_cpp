#
# x86 platform build
# cmake .. 

cmake_minimum_required(VERSION 3.5)

project(boostsignal2)

set(GNU_CXX_FLAGS "-DCOM_X64 -g -W -std=c++11")
set(GUN_C_FLAGS "-DCOM_X64 -g -W")

set(CMAKE_CXX_FLAGS "${GNU_CXX_FLAGS}")
set(CMAKE_C_FLAGS   "${GUN_C_FLAGS}")

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src ALL_SRC)

add_executable(demo ${ALL_SRC})
target_link_libraries(demo pthread)