# Examples

file(GLOB EXAMPLES_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(examples 
    COMMENT "This is the examples meta-target which builds all examples of the piga library.")

foreach(sourcefile ${EXAMPLES_SOURCES})
    string(REPLACE ".cpp" "" exampleName ${sourcefile})
    add_executable(example_${exampleName} ${sourcefile})
    target_link_libraries(example_${exampleName} piga)
    set_target_properties(example_${exampleName} PROPERTIES EXCLUDE_FROM_ALL TRUE)
    add_dependencies(examples example_${exampleName})
endforeach()

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
