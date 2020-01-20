# mkdir build
# cd build
# cmake -DPLATFORM=arm

cmake_minimum_required(VERSION 3.5)   # CMake version check.

project(zlog) # project name.

if (PLATFORM MATCHES arm)
	set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR arm)

    set(CMAKE_CXX_COMPILER /opt/arm-2014.05/bin/arm-none-linux-gnueabi-g++)
    set(CMAKE_C_COMPILER   /opt/arm-2014.05/bin/arm-none-linux-gnueabi-gcc)

    set(GNU_FLAGS "-W -fPIC")
    set(CMAKE_CXX_FLAGS "${GNU_FLAGS}")
    set(CMAKE_C_FLAGS   "${GNU_FLAGS}")

    #include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/zlog/include)
    #link_directories(${CMAKE_CURRENT_LIST_DIR}/lib/arm/zlog/lib)

else()
	set(GNU_FLAGS "-DCOM_X64 -g -W -std=c99")
    set(CMAKE_CXX_FLAGS "${GNU_FLAGS}")
    set(CMAKE_C_FLAGS   "${GNU_FLAGS}")

    include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/zlog/include)

    link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/zlog/lib)

endif()

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src ALL_SRC)

add_executable(demo ${ALL_SRC})
target_link_libraries(demo zlog)
