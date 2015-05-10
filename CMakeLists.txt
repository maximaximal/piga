project(pigaco)
cmake_minimum_required(VERSION 2.8)

include(ExternalProject)
include(FindPkgConfig)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

SET(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
SET(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include/pigaco/)
set(RSC ${CMAKE_CURRENT_SOURCE_DIR}/Data/ressources)
set(FOR ${CMAKE_CURRENT_SOURCE_DIR}/Data/forms)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

SET(HDRS
    ${HDR}/App.hpp
    ${HDR}/DirectoryScanner.hpp
    ${HDR}/Players.hpp
    ${HDR}/GameHostStarter.hpp

    ${HDR}/Game.hpp
)

SET(SRCS
    ${SRC}/App.cpp
    ${SRC}/DirectoryScanner.cpp
    ${SRC}/Players.cpp
    ${SRC}/GameHostStarter.cpp

    ${SRC}/Game.cpp
)

set(RSCS
    ${RSC}/main.qrc
)

set(FORS
    ${FOR}/MainMenu.qml
    ${FOR}/MainMenuHeader.qml
    ${FOR}/GameBox.qml

    ${FOR}/Pages/Store/Main.qml
    ${FOR}/Pages/Settings/Main.qml
    ${FOR}/Pages/Settings/Players.qml
    ${FOR}/Pages/Settings/PlayerDelegate.qml
)

# Find Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(Qt5Qml)
find_package(Qt5Quick)

add_executable(pigaco ${SRCS} ${HDRS} ${RSCS} ${FORS})

target_link_libraries(pigaco Qt5::Widgets Qt5::Qml Qt5::Quick)

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
    CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
)

add_dependencies(pigaco GLM_Project)

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
 
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libpiga/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pihud/)
add_dependencies(pigaco piga)
target_link_libraries(pigaco piga)
target_link_libraries(pigaco pihud)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/pihud/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libpiga/include)

add_custom_command(TARGET pigaco
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/distributor.py
                   COMMAND python
                   ARGS ${CMAKE_CURRENT_SOURCE_DIR}/distributor.py ${CMAKE_CURRENT_BINARY_DIR}/dist)

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lrt ${CMAKE_CXX_FLAGS}")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	list(APPEND ${CMAKE_CXX_FLAGS} "-Wall -std=c++11 -lrt ${CMAKE_CXX_FLAGS}")
endif()
