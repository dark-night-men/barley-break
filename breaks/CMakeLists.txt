cmake_minimum_required (VERSION 2.8)

FIND_PACKAGE ( Threads REQUIRED )

add_executable(brk main.cpp)

target_link_libraries (brk LINK_PUBLIC breaks)
