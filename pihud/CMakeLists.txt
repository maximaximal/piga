project(pihud)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(FindPkgConfig)
include(FindPackageHandleStandardArgs)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRCS
    ${SRC}/HudContainer.cpp
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
    ${SRC}/HorizontalListLayout.cpp
    ${SRC}/VerticalListLayout.cpp
    ${SRC}/FocusManager.cpp
    ${SRC}/FocusEvent.cpp
    ${SRC}/QueueDisplayWidget.cpp
    ${SRC}/Particle.cpp
    ${SRC}/ParticleSource.cpp
    ${SRC}/WeHaveAWinnerWidget.cpp
    ${SRC}/PigaEvent.cpp
    ${SRC}/TextureManager.cpp
    ${SRC}/MenuContainer.cpp
)

set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include/pihud/)
set(HDRS
    ${HDR}/HudContainer.hpp
    ${HDR}/Widget.hpp
    ${HDR}/Rect.hpp
    ${HDR}/Event.hpp
    ${HDR}/InputEvent.hpp
    ${HDR}/Direction.hpp
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
    ${HDR}/HorizontalListLayout.hpp
    ${HDR}/VerticalListLayout.hpp
    ${HDR}/FocusManager.hpp
    ${HDR}/FocusEvent.hpp
    ${HDR}/WeHaveAWinnerWidget.hpp
    ${HDR}/PigaEvent.hpp
    ${HDR}/TextureManager.hpp
    ${HDR}/MenuContainer.hpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} SHARED ${SRCS} ${HDRS})

find_package(SDL2)
if(${SDL2_FOUND})
    target_link_libraries(pihud ${SDL2_LIBRARY})
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

find_package(SDL2image)
if(${SDL2IMAGE_FOUND})
    target_link_libraries(pihud ${SDL2IMAGE_LIBRARY})
    include_directories(${SDL2IMAGE_INCLUDE_DIRS})
endif()

find_package(SDL2ttf)
if(${SDL2TTF_FOUND})
    target_link_libraries(pihud ${SDL2TTF_LIBRARY})
    include_directories(${SDL2TTF_INCLUDE_DIRS})
endif()

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
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libpiga/include)

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
