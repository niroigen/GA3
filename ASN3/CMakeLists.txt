project(ASN3)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    sub::lib2
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)