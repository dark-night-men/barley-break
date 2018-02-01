cmake_minimum_required (VERSION 2.8)
project (break C CXX)

add_subdirectory (breaks)
add_subdirectory (libbreaks)
add_subdirectory (tests)

FIND_PACKAGE ( Threads REQUIRED )

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_BUILD_TYPE Debug)
add_definitions( -D_GLIBCXX_DEBUG )
#add_definitions( -D_GLIBCXX_DEBUG MALLOC_CHECK_ )

