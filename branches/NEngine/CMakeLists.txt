cmake_minimum_required(VERSION 2.8)

project(NEngine)

cmake_policy(SET CMP0015 NEW)

SET(CMAKE_CXX_WARNING_LEVEL 4)
if (DEFINED MSYS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif ()

if (DEFINED CMAKE_COMPILER_IS_GNUCC OR DEFINED CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif ()

include_directories(include/)
include_directories(src/)

file(
	GLOB_RECURSE
    NEngine_sources
	src/*
)

add_library(
    NEngine
	SHARED
	${NEngine_sources}
)

add_library(
    NEngine-static
	STATIC
	${NEngine_sources}
)
# Since the static compilation will have same root name, with have to do some "hacky" thing
# This is coming from CMake FAQ
SET_TARGET_PROPERTIES(NEngine-static PROPERTIES OUTPUT_NAME "NEngine")
# Now the library target "foo-static" will be named "foo.lib" with MS tools.
# This conflicts with the "foo.lib" import library corresponding to "foo.dll",
# so we add a "lib" prefix (which is default on other platforms anyway):
SET_TARGET_PROPERTIES(NEngine-static PROPERTIES PREFIX "lib")

include_directories(./include)
link_directories(./lib)


set(SDL_ROOT "./" CACHE PATH "The location of the SDL install prefix (only used if the SDL is not yet found)")
if(SDL_ROOT)
   set(CMAKE_PREFIX_PATH ${SDL_ROOT})
endif()

# Finding libraries
find_package (SDL)
if (SDL_FOUND)
  include_directories(${SDL_INCLUDE_DIR})
  target_link_libraries (NEngine ${SDL_LIBRARY})
  # MESSAGE("  SDL_INCLUDE_DIR='${SDL_INCLUDE_DIR}'")
else ()
  MESSAGE(FATAL_ERROR "SDL not found")
endif (SDL_FOUND)

find_package (SDL_image)
if (SDLIMAGE_FOUND)
  include_directories(${SDLIMAGE_INCLUDE_DIR})
  target_link_libraries (NEngine ${SDLIMAGE_LIBRARY})
  # MESSAGE("  SDLIMAGE_INCLUDE_DIR='${SDLIMAGE_INCLUDE_DIR}'")
else ()
  # Since the FindSDL_image is a bit incomplete, from my point of view, I will try to specify the directories myself
  if (MSYS OR MINGW)
    MESSAGE(STATUS "Define default paths for SDL on Windows")
	set (SDLIMAGE_INCLUDE_DIR "./include/SDL")
	set (SDLIMAGE_LIBRARY "./include/SDL_image.lib")
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/SDL)
	target_link_libraries (NEngine ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL_image.lib)
  else ()
	MESSAGE(FATAL_ERROR "SDL_image not found")
  endif (MSYS OR MINGW)
endif (SDLIMAGE_FOUND)

install(DIRECTORY ./include/NEngine/
        DESTINATION include/NEngine )

install(TARGETS NEngine NEngine-static
		ARCHIVE DESTINATION lib/
        LIBRARY DESTINATION lib/ )
