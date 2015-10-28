cmake_minimum_required(VERSION 2.8)

add_subdirectory("./deps/NEngine")

project(OpenWars)

cmake_policy(SET CMP0015 NEW)

SET(CMAKE_CXX_WARNING_LEVEL 4)
if (DEFINED MSYS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif ()

if (DEFINED CMAKE_COMPILER_IS_GNUCC OR DEFINED CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif ()

link_directories(./lib)

file(
	GLOB_RECURSE
	sources
	src/*.cpp
	src/*.hpp
	src/*.h
)

# Executable
add_executable(
	OpenWars
	${sources}
)

# Finding libraries
find_package (SDL)
if (SDL_FOUND)
  include_directories(${SDL_INCLUDE_DIR})
  target_link_libraries (OpenWars ${SDL_LIBRARY})
  # MESSAGE("  SDL_INCLUDE_DIR='${SDL_INCLUDE_DIR}'")
endif (SDL_FOUND)

find_package (SDL_image)
if (SDLIMAGE_FOUND)
  include_directories(${SDLIMAGE_INCLUDE_DIR})
  target_link_libraries (OpenWars ${SDLIMAGE_LIBRARY})
  # MESSAGE("  SDLIMAGE_INCLUDE_DIR='${SDLIMAGE_INCLUDE_DIR}'")
endif (SDLIMAGE_FOUND)


#Checks for libxml2
find_package (LibXml2 QUIET)
if (NOT LIBXML2_FOUND)
  if (WIN32)
	message(STATUS "Manually set libxml2 configuration")
	set(LIBXML2_INCLUDE_DIR "./deps/libxml2.bin/include/libxml")
	set(LIBXML2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/deps/libxml2.bin/lib/libxml2.lib")
  else ()
    message(FATAL_ERROR "libxml2 not found")
  endif()
endif()
include_directories(${LIBXML2_INCLUDE_DIR})
target_link_libraries (OpenWars ${LIBXML2_LIBRARIES})

include_directories(./src)
include_directories(./include)
include_directories(./deps/NEngine/include) # TODO : should it be done here ?

target_link_libraries (OpenWars NEngine)
