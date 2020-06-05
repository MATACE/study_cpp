cmake_minimum_required(VERSION 3.5)

# set_property(TARGET run_demo PROPERTY C_STANDARD 99)
# set_property(TARGET run_demo PROPERTY C_STANDARD_REQUIRED ON)

# set_property(TARGET run_demo PROPERTY CXX_STANDARD 11)
# set_property(TARGET run_demo PROPERTY CXX_STANDARD_REQUIRED ON)

message(STATUS "Project source path " ${PROJECT_SOURCE_DIR})
message(STATUS "Project Current list dir " ${CMAKE_CURRENT_LIST_DIR})

# Option can use the OFF or ON to build the each mode.
option(BUILD_SWITCH_COROUTINE "Build Switch Coroutine" ON)
option(BUILD_BOOST_ASIO_COROUTINE "Build Boost Asio Coroutine" OFF)
option(BUILD_THREAD_POOL "Build Thread Pool" ON)

# Set output file path.
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
        CACHE PATH
        ""
    )

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        ""
    )

SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
        CACHE PATH
        ""
    )

if(BUILD_SWITCH_COROUTINE)
    message(STATUS "Build Switch Coroutine")
    set(GNU_FLAGS "-DCOM_X64 -g -W")
    set(CMAKE_CXX_FLAGS "${GNU_FLAGS}")
    set(CMAKE_C_FLAGS   "${GNU_FLAGS}")

    # include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/glog/include/)
    # link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/glog/lib)

    # include_directories(${PROJECT_SOURCE_DIR}/include/coroutines)
    # set(coroutine_src
    #     ${PROJECT_SOURCE_DIR}/src/coroutines/example_switch_coroutine.cpp)
    # add_library(switch_coroutine ${coroutine_src})

    # set_property(TARGET switch_coroutine PROPERTY CXX_STANDARD 11)
    # set_property(TARGET switch_coroutine PROPERTY CXX_STANDARD_REQUIRED ON)
    
    add_executable(example_switch_coroutine_app
        ${PROJECT_SOURCE_DIR}/src/coroutines/example_switch_coroutine.c
    )

    set_property(TARGET example_switch_coroutine_app PROPERTY C_STANDARD 99)
    set_property(TARGET example_switch_coroutine_app PROPERTY C_STANDARD_REQUIRED ON)

    # target_link_libraries(example_switch_coroutine_app switch_coroutine)
    target_link_libraries(example_switch_coroutine_app)

endif()

if(BUILD_BOOST_ASIO_COROUTINE)
    message(STATUS "Build Boost Asio Coroutine")
    set(GNU_FLAGS "-DCOM_X64 -g -W")
    set(CMAKE_CXX_FLAGS "${GNU_FLAGS}")
    set(CMAKE_C_FLAGS   "${GNU_FLAGS}")

    # include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/glog/include/)
    # link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/glog/lib)

    # include_directories(${PROJECT_SOURCE_DIR}/include/coroutines)
    # set(coroutine_src
    #     ${PROJECT_SOURCE_DIR}/src/coroutines/example_switch_coroutine.cpp)
    # add_library(switch_coroutine ${coroutine_src})

    # set_property(TARGET switch_coroutine PROPERTY CXX_STANDARD 11)
    # set_property(TARGET switch_coroutine PROPERTY CXX_STANDARD_REQUIRED ON)
    
    add_executable(example_boost_asio_coroutine_app
        ${PROJECT_SOURCE_DIR}/src/coroutines/example_boost_asio_coroutine.cpp
    )

    set_property(TARGET example_boost_asio_coroutine_app PROPERTY CXX_STANDARD 11)
    set_property(TARGET example_boost_asio_coroutine_app PROPERTY CXX_STANDARD_REQUIRED ON)

    # target_link_libraries(example_switch_coroutine_app switch_coroutine)
    target_link_libraries(example_boost_asio_coroutine_app)
endif()

if(BUILD_THREAD_POOL)
    message(STATUS "Build Thread Pool")
    set(GNU_FLAGS "-DCOM_X64 -g -W")
    set(CMAKE_CXX_FLAGS "${GNU_FLAGS}")
    set(CMAKE_C_FLAGS   "${GNU_FLAGS}")

    # include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/glog/include/)
    # link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/glog/lib)

    include_directories(${PROJECT_SOURCE_DIR}/include/thread_pool)
    # set(coroutine_src
    #     ${PROJECT_SOURCE_DIR}/src/coroutines/example_switch_coroutine.cpp)
    # add_library(switch_coroutine ${coroutine_src})

    # set_property(TARGET switch_coroutine PROPERTY CXX_STANDARD 11)
    # set_property(TARGET switch_coroutine PROPERTY CXX_STANDARD_REQUIRED ON)
    
    add_executable(example_thread_pool_app
        ${PROJECT_SOURCE_DIR}/src/thread_pool/example_thread_pool.cpp
    )

    set_property(TARGET example_thread_pool_app PROPERTY CXX_STANDARD 11)
    set_property(TARGET example_thread_pool_app PROPERTY CXX_STANDARD_REQUIRED ON)

    # target_link_libraries(example_switch_coroutine_app switch_coroutine)
    target_link_libraries(example_thread_pool_app pthread)
endif()
