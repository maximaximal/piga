project(ConsoleMGR)
cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)

include(ExternalProject)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(RSC ${CMAKE_CURRENT_SOURCE_DIR}/ressources)
set(FOR ${CMAKE_CURRENT_SOURCE_DIR}/forms)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../networked_client/include)

set(HDRS
    ${HDR}/Client.hpp
    ${HDR}/ClientManager.hpp
    ${HDR}/Player.hpp
)

set(SRCS
    ${SRC}/main.cpp
    ${SRC}/Client.cpp
    ${SRC}/ClientManager.cpp
    ${SRC}/Player.cpp
)

set(RSCS
    ${RSC}/main.qrc    
)

set(FORS
    ${FOR}/MainView.qml
    ${FOR}/NewConnection.qml
    ${FOR}/ClientView.qml
)

include_directories(${HDR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(Qt5Qml)
find_package(Qt5Quick)

add_executable(ConsoleMGR ${SRCS} ${HDRS} ${RSCS} ${FORS})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../networked_client/ networked_client)
target_link_libraries(ConsoleMGR piga)
target_link_libraries(ConsoleMGR networked_client)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libpiga/include)

target_link_libraries(ConsoleMGR Qt5::Widgets Qt5::Qml Qt5::Quick)

if(${PROTOBUF_FOUND})
    target_link_libraries(ConsoleMGR ${PROTOBUF_LIBRARIES})
    include_directories(${PROTOBUF_INCLUDE_DIRS})
endif()

find_package(Boost REQUIRED COMPONENTS system thread filesystem)

if(${Boost_FOUND})
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    target_link_libraries(ConsoleMGR ${Boost_LIBRARIES})
endif()

target_link_libraries(ConsoleMGR pthread)

# Add sigc++2
find_package(SigC++ REQUIRED)
if(${SIGC++_FOUND})
    target_link_libraries(ConsoleMGR ${SIGC++_LIBRARY})
    include_directories(${SIGC++_INCLUDE_DIR})
elseif()
    message(STATUS "Did not find Sigc++2! Please install it before you try to compile again.")
endif()

add_dependencies(ConsoleMGR GLM_Project)

include_directories(${INCLUDE})
# GLM Headers in the glm/ path.
include_directories(SYSTEM ${CMAKE_CURRENT_BINARY_DIR}/glm/src/GLM_Project/)

# Add yaml-cpp
find_package(YamlCpp REQUIRED)
if(${YAMLCPP_FOUND})
    target_link_libraries(ConsoleMGR ${YAMLCPP_LIBRARY})
    include_directories(${YAMLCPP_INCLUDE_DIR})
elseif()
    message(STATUS "Did not find Yaml-Cpp! Please install it before you try to compile again.")
endif()

# Add enet
find_package(ENet REQUIRED)
if(${ENET_FOUND})
    include_directories(${ENet_INCLUDE_DIRS})
    target_link_libraries(ConsoleMGR ${ENet_LIBRARIES})
endif()

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lrt ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} ${CMAKE_CXX_FLAGS}")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    list(APPEND ${CMAKE_CXX_FLAGS} "-Wall -std=c++11 -lrt ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} ${CMAKE_CXX_FLAGS}")
endif()

