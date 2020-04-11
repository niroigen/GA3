cmake_minimum_required(VERSION 3.5.1)
project(GA)

add_library(${PROJECT_NAME} src/individual.cpp src/helper.cpp src/crossover.cpp src/mutation.cpp src/fitness.cpp
            src/parent.cpp src/survivor.cpp src/ga.cpp)
add_library(sub::lib2 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    sub::lib1
    jsoncpp
    pthread
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)