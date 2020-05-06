cmake_minimum_required (VERSION 2.8)
FIND_PACKAGE ( Threads REQUIRED )

add_executable(rnt 
    tests_main.cpp
    tests_cell.cpp
)

target_link_libraries (rnt LINK_PUBLIC breaks)
