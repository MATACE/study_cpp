set(CMAKE_SYSTEM_NAME Linux)    
set(CMAKE_SYSTEM_PROCESSOR arm) 

set(CMAKE_C_COMPILER /opt/arm-2014.05/bin/arm-none-linux-gnueabi-gcc)   
set(CMAKE_CXX_COMPILER /opt/arm-2014.05/bin/arm-none-linux-gnueabi-g++) 


set(GNU_CXX_FLAGS "-mfpu=vfp -std=c++11 -fPIC -g -W -O2 -DBOOST_ASIO_DISABLE_STD_FUTURE")
set(GNU_C_FLAGS "-mfpu=vfp -fPIC -g -W -O2 -std=c99")
set(CMAKE_CXX_FLAGS "${GNU_CXX_FLAGS}")
set(CMAKE_C_FLAGS   "${GNU_C_FLAGS}")