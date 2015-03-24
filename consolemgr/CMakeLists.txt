project(ConsoleMGR)
cmake_minimum_required(VERSION 2.8)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(RSC ${CMAKE_CURRENT_SOURCE_DIR}/ressources)
set(FOR ${CMAKE_CURRENT_SOURCE_DIR}/forms)

set(HDRS

)

set(SRCS
    ${SRC}/main.cpp    
)

set(RSCS
    ${RSC}/main.qrc    
)

set(FORS
    ${FOR}/MainView.qml
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(Qt5Qml)
find_package(Qt5Quick)

add_executable(ConsoleMGR ${SRCS} ${HDRS} ${RSCS} ${FORS})

target_link_libraries(ConsoleMGR Qt5::Widgets Qt5::Qml Qt5::Quick)
