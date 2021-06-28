cmake_minimum_required(VERSION 3.16.3)

project(Ges_Project VERSION 1.0)

add_subdirectory(Application/my_table)


add_executable(ges
main.cpp
)

target_link_libraries(ges PUBLIC my_table)

