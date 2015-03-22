cmake_minimum_required(VERSION 2.8)

include(ExternalProject)
ExternalProject_Add(
    NEngine_lib
    GIT_REPOSITORY https://github.com/LittleWhite-tb/NEngine.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/
    INSTALL_DIR ./
)

project(OpenAWars)

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
)

# Executable
add_executable(
	OpenAWars
	${sources}
)

# Finding libraries
find_package (SDL)
if (SDL_FOUND)
  include_directories(${SDL_INCLUDE_DIR})
  target_link_libraries (OpenAWars ${SDL_LIBRARY})
  # MESSAGE("  SDL_INCLUDE_DIR='${SDL_INCLUDE_DIR}'")
endif (SDL_FOUND)

find_package (SDL_image)
if (SDLIMAGE_FOUND)
  include_directories(${SDLIMAGE_INCLUDE_DIR})
  target_link_libraries (OpenAWars ${SDLIMAGE_LIBRARY})
  # MESSAGE("  SDLIMAGE_INCLUDE_DIR='${SDLIMAGE_INCLUDE_DIR}'")
endif (SDLIMAGE_FOUND)


#Checks for libxml2
find_package (LibXml2)
if (LIBXML2_FOUND)
  include_directories(${LIBXML2_INCLUDE_DIR})
  target_link_libraries (OpenAWars ${LIBXML2_LIBRARIES})
  # MESSAGE("  LIBXML2_INCLUDE_DIR='${LIBXML2_INCLUDE_DIR}'")
endif (LIBXML2_FOUND)

include_directories(./src)
include_directories(./include)

target_link_libraries (OpenAWars NEngine)
