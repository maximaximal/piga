project(ConsoleMGR)
cmake_minimum_required(VERSION 2.8)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(RSC ${CMAKE_CURRENT_SOURCE_DIR}/ressources)
set(FOR ${CMAKE_CURRENT_SOURCE_DIR}/forms)

set(HDRS
    ${HDR}/Client.hpp
    ${HDR}/ClientManager.hpp
)

set(SRCS
    ${SRC}/main.cpp
    ${SRC}/Client.cpp
    ${SRC}/ClientManager.cpp
)

set(RSCS
    ${RSC}/main.qrc    
)

set(FORS
    ${FOR}/MainView.qml
    ${FOR}/NewConnection.qml
)

include_directories(${HDR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(Qt5Qml)
find_package(Qt5Quick)

add_executable(ConsoleMGR ${SRCS} ${HDRS} ${RSCS} ${FORS})

target_link_libraries(ConsoleMGR Qt5::Widgets Qt5::Qml Qt5::Quick)

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lrt ${CMAKE_CXX_FLAGS}")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    list(APPEND ${CMAKE_CXX_FLAGS} "-Wall -std=c++11 -lrt ${CMAKE_CXX_FLAGS}")
endif()

