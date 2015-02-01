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
    ${HDR}/GameHost.hpp
    ${HDR}/Status.hpp
    ${HDR}/PlayerManager.hpp
    ${HDR}/SharedLibWrapper.hpp

    ${HDR}/Events/GameInput.hpp
    ${HDR}/Events/TextInput.hpp
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
    ${SRC}/GameHost.cpp
    ${SRC}/Status.cpp
    ${SRC}/PlayerManager.cpp
    ${SRC}/SharedLibWrapper.cpp
    ${SRC}/GameControl.cpp

    ${SRC}/Events/GameInput.cpp
    ${SRC}/Events/TextInput.cpp
)

SET(SCM ${CMAKE_CURRENT_SOURCE_DIR}/../schemas)

SET(SCHEMAS
    ${SCM}/player.proto
    ${SCM}/libpiga_handshake.proto
    ${SCM}/input.proto
    ${SCM}/gamecontrol.proto
)

SET(SCHEMAS ${SCHEMAS} PARENT_SCOPE)

# Add google protocol buffers
find_package(Protobuf REQUIRED)

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${SCHEMAS})

add_library(piga SHARED ${SRCS} ${HDRS} ${PROTO_SRCS} ${PROTO_HDRS})

if(${PROTOBUF_FOUND})
    target_link_libraries(piga ${PROTOBUF_LIBRARIES})
    include_directories(${PROTOBUF_INCLUDE_DIRS})
endif()

find_package(Boost REQUIRED COMPONENTS system thread filesystem)

if(${Boost_FOUND})
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    target_link_libraries(piga ${Boost_LIBRARIES})
endif()

# Add yaml-cpp
find_package(YamlCpp)
if(${YAMLCPP_FOUND})
    target_link_libraries(piga ${YAMLCPP_LIBRARY})
    include_directories(${YAMLCPP_INCLUDE_DIR})
elseif()
    message(STATUS "Did not find Yaml-Cpp! This binary can not be used as server.")
endif()

# Add sigc++2
find_package(SigC++ REQUIRED)
if(${SIGC++_FOUND})
    target_link_libraries(piga ${SIGC++_LIBRARY})
    include_directories(${SIGC++_INCLUDE_DIR})
elseif()
    message(STATUS "Did not find Sigc++2! Please install it before you try to compile again.")
endif()

# Add enet
find_package(ENet REQUIRED)
if(${ENET_FOUND})
    include_directories(${ENet_INCLUDE_DIRS})
    target_link_libraries(piga ${ENet_LIBRARIES})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../hosts/)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
