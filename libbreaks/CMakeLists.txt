cmake_minimum_required (VERSION 2.8)

FIND_PACKAGE ( Threads REQUIRED )


add_library ( 
    breaks
    cell.h
    cell.cpp
)

target_include_directories (breaks PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
