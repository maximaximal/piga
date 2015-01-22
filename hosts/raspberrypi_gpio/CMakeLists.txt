project(host_raspberrypi_gpio)
cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

SET(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
SET(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(HDRS

)
set(SRCS
    ${SRC}/host.cpp
)

add_library(host_raspberrypi_gpio SHARED ${SRCS} ${HDRS})

# Add wiringpi
ExternalProject_Add(wiringpi_project
    PREFIX wiringpi
    GIT_REPOSITORY git://git.drogon.net/wiringPi
    UPDATE_COMMAND git pull origin master
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
)

add_dependencies(host_raspberrypi_gpio wiringpi_project)

find_library(wiringpi_library
    NAMES wiringpi libwiringpi libwiringpi.a libwiringpi.so
    HINTS ${CMAKE_CURRENT_BINARY_DIR}/wiringpi/
)

include_directories(${HDR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libpiga/include/)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/wiringpi/src/wiringpi_project/wiringPi/)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lrt ${CMAKE_CXX_FLAGS}")
