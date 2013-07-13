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

include_directories(./include)
link_directories(./lib)

# Finding libraries
find_package (SDL)
if (SDL_FOUND)
  include_directories(${SDL_INCLUDE_DIR})
  target_link_libraries (NEngine ${SDL_LIBRARY})
  # MESSAGE("  SDL_INCLUDE_DIR='${SDL_INCLUDE_DIR}'")
endif (SDL_FOUND)

find_package (SDL_image)
if (SDLIMAGE_FOUND)
  include_directories(${SDLIMAGE_INCLUDE_DIR})
  target_link_libraries (NEngine ${SDLIMAGE_LIBRARY})
  # MESSAGE("  SDLIMAGE_INCLUDE_DIR='${SDLIMAGE_INCLUDE_DIR}'")
endif (SDLIMAGE_FOUND)

install(DIRECTORY ./include/NEngine/
        DESTINATION include/NEngine )

install(TARGETS NEngine
		ARCHIVE DESTINATION lib/
        LIBRARY DESTINATION lib/ )
