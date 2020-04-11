cmake_minimum_required(VERSION 3.5.1)
project(Json)

add_library(${PROJECT_NAME} src/jsonReader.cpp src/jsonWriter.cpp)
add_library(sub::lib1 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/../GA/include
)

target_link_libraries(${PROJECT_NAME}
    sub::lib2
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)