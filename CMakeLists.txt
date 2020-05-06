cmake_minimum_required (VERSION 2.8)
project (break C CXX)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 17)

set (CMAKE_BUILD_TYPE Debug)
add_definitions( -D_GLIBCXX_DEBUG )
#add_definitions( -D_GLIBCXX_DEBUG MALLOC_CHECK_ )

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-long-long -pedantic")
endif()


add_subdirectory (breaks)
add_subdirectory (libbreaks)
add_subdirectory (tests)
add_subdirectory (guibreak)

FIND_PACKAGE ( Threads REQUIRED )
