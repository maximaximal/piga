project(host_pc_keyboard)
cmake_minimum_required(VERSION 2.8)

include(ExternalProject)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/)

SET(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
SET(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(HDRS

)
set(SRCS
    ${SRC}/host.cpp
)

add_library(host_pc_keyboard SHARED ${SRCS} ${HDRS})

find_package(SDL2)
if(${SDL2_FOUND})
    target_link_libraries(host_pc_keyboard ${SDL2_LIBRARY})
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

include_directories(${HDR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libpiga/include/)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lrt ${CMAKE_CXX_FLAGS}")
