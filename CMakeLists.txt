project(pigaco)
cmake_minimum_required(VERSION 2.8)

include(ExternalProject)
include(FindPkgConfig)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

SET(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
SET(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include/pigaco/)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

SET(HDRS
    ${HDR}/App.hpp
    ${HDR}/Window.hpp
    ${HDR}/DirectoryScanner.hpp
)

SET(SRCS
    ${SRC}/App.cpp
    ${SRC}/Window.cpp
    ${SRC}/DirectoryScanner.cpp
)

add_executable(pigaco ${SRCS} ${HDRS})

find_package(SDL2)
if(${SDL2_FOUND})
    target_link_libraries(pigaco ${SDL2_LIBRARY})
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

find_package(SDL2image)
if(${SDL2IMAGE_FOUND})
    target_link_libraries(pigaco ${SDL2IMAGE_LIBRARY})
    include_directories(${SDL2IMAGE_INCLUDE_DIRS})
endif()

find_package(SDL2ttf)
if(${SDL2TTF_FOUND})
    target_link_libraries(pigaco ${SDL2TTF_LIBRARY})
    include_directories(${SDL2TTF_INCLUDE_DIRS})
endif()

find_package(Boost REQUIRED COMPONENTS system thread filesystem)

if(${Boost_FOUND})
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    target_link_libraries(pigaco ${Boost_LIBRARIES})
endif()

target_link_libraries(pigaco pthread)

# Add sigc++2
find_package(SigC++ REQUIRED)
if(${SIGC++_FOUND})
    target_link_libraries(pigaco ${SIGC++_LIBRARY})
    include_directories(${SIGC++_INCLUDE_DIR})
elseif()
    message(STATUS "Did not find Sigc++2! Please install it before you try to compile again.")
endif()

ExternalProject_Add(GLM_Project
    PREFIX glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.5.4
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

add_dependencies(pigaco GLM_Project)

include_directories(${INCLUDE})
# GLM Headers in the glm/ path.
include_directories(SYSTEM ${CMAKE_CURRENT_BINARY_DIR}/glm/src/GLM_Project/)

# Add yaml-cpp
find_package(YamlCpp REQUIRED)
if(${YAMLCPP_FOUND})
    target_link_libraries(pigaco ${YAMLCPP_LIBRARY})
    include_directories(${YAMLCPP_INCLUDE_DIR})
elseif()
    message(STATUS "Did not find Yaml-Cpp! Please install it before you try to compile again.")
endif()
 
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libpiga/ ${CMAKE_CURRENT_BINARY_DIR}/piga/)
add_dependencies(pigaco piga)
include_directories(${LIBPIGA_INCLUDE_DIRECTORIES})
target_link_libraries(pigaco piga)
target_link_libraries(pigaco pihud)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/pihud/include)

add_custom_command(TARGET pigaco
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/distributor.py
                   POST_BUILD
                   COMMAND python
                   ARGS ${CMAKE_CURRENT_SOURCE_DIR}/distributor.py ${CMAKE_CURRENT_BINARY_DIR}/dist)

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lrt ${CMAKE_CXX_FLAGS}")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	list(APPEND ${CMAKE_CXX_FLAGS} "-Wall -std=c++11 -lrt ${CMAKE_CXX_FLAGS}")
endif()
