project(libpiga)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)

SET(LIBPIGA_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/ PARENT_SCOPE)

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
    ${HDR}/Player.hpp
    ${HDR}/GameEvent.hpp
    ${HDR}/Definitions.hpp
    ${HDR}/GameEventHandler.hpp
    ${HDR}/Renderer.hpp
)

SET(SRCS
    ${SRC}/GameInput.cpp
    ${SRC}/PlayerInput.cpp
    ${SRC}/InputMethod.cpp
    ${SRC}/Interface.cpp
    ${SRC}/Host.cpp
    ${SRC}/Player.cpp
    ${SRC}/GameEvent.cpp
    ${SRC}/GameEventHandler.cpp
    ${SRC}/Renderer.cpp
)

add_library(piga ${SRCS} ${HDRS})

find_package(Boost REQUIRED COMPONENTS system thread)

if(${Boost_FOUND})
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    target_link_libraries(piga ${Boost_LIBRARIES})
endif()

# Add sigc++2
find_package(SigC++ REQUIRED)
if(${SIGC++_FOUND})
    target_link_libraries(piga ${SIGC++_LIBRARY})
    include_directories(${SIGC++_INCLUDE_DIR})
elseif()
    message(STATUS "Did not find Sigc++2! Please install it before you try to compile again.")
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../pihud pihud)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../pihud/include)

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
