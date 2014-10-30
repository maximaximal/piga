project(libpiga)
cmake_minimum_required(VERSION 2.8)

SET(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
SET(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include/piga/)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

SET(HDRS
    ${HDR}/GameInput.hpp
    ${HDR}/PlayerInput.hpp
    ${HDR}/GameControl.hpp
    ${HDR}/InputMethod.hpp
    ${HDR}/Interface.hpp
    ${HDR}/Host.hpp
    ${HDR}/GameEvent.hpp
)

SET(SRCS
    ${SRC}/GameInput.cpp
    ${SRC}/PlayerInput.cpp
    ${SRC}/InputMethod.cpp
    ${SRC}/Interface.cpp
    ${SRC}/Host.cpp
    ${SRC}/GameEvent.cpp
)

add_library(piga ${SRCS} ${HDRS})

find_package(Boost REQUIRED)

if(${Boost_FOUND})
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    target_link_libraries(piga ${Boost_LIBRARIES})
endif()

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
