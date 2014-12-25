project(pihud)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(FindPkgConfig)
include(FindPackageHandleStandardArgs)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRCS
    ${SRC}/HudContainer.cpp
    ${SRC}/DirectionEvent.cpp
    ${SRC}/InputEvent.cpp
    ${SRC}/Event.cpp
    ${SRC}/Widget.cpp
    ${SRC}/Config.cpp
    ${SRC}/Font.cpp
    ${SRC}/FontManager.cpp
    ${SRC}/Label.cpp
    ${SRC}/pihud.cpp
    ${SRC}/Texture.cpp
    ${SRC}/Image.cpp
    ${SRC}/IconHealthIndicator.cpp
    ${SRC}/HealthAndNameDisplay.cpp
    ${SRC}/Rect.cpp
    ${SRC}/Layout.cpp
    ${SRC}/Layouter.cpp
    ${SRC}/QueueDisplayWidget.cpp
    ${SRC}/Particle.cpp
    ${SRC}/ParticleSource.cpp
    ${SRC}/WeHaveAWinnerWidget.cpp
)

set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include/pihud/)
set(HDRS
    ${HDR}/HudContainer.hpp
    ${HDR}/Widget.hpp
    ${HDR}/Rect.hpp
    ${HDR}/Event.hpp
    ${HDR}/InputEvent.hpp
    ${HDR}/DirectionEvent.hpp
    ${HDR}/Config.hpp
    ${HDR}/pihud.hpp
    ${HDR}/Font.hpp
    ${HDR}/Label.hpp
    ${HDR}/FontManager.hpp
    ${HDR}/Texture.hpp
    ${HDR}/Image.hpp
    ${HDR}/IconHealthIndicator.hpp
    ${HDR}/HealthAndNameDisplay.hpp
    ${HDR}/QueueDisplayWidget.hpp
    ${HDR}/Particle.hpp
    ${HDR}/Layout.hpp
    ${HDR}/Layouter.hpp
    ${HDR}/WeHaveAWinnerWidget.hpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} ${SRCS} ${HDRS})

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# Add SDL2 and SDL_image
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

# Add sigc++2
find_package(SigC++ REQUIRED)
if(${SIGC++_FOUND})
    target_link_libraries(${PROJECT_NAME} ${SIGC++_LIBRARY})
    include_directories(${SIGC++_INCLUDE_DIR})
elseif()
    message(STATUS "Did not find Sigc++2! Please install it before you try to compile again.")
endif()

# Link to libpiga
target_link_libraries(piga)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../libpiga/include)
