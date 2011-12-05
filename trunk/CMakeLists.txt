cmake_minimum_required(VERSION 2.6)

# Include NEngine
include_directories(Sources)
include_directories(Sources/game)

# C++ Flags
SET(CMAKE_CXX_FLAGS "-g -Wall -W -pedantic -ansi")

#Déclaration du projet
project(OpenAWars)
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH bin)

# Include SDL
#set(SDL_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/libs/sdl-1.3
#    CACHE STRING "Path to SDL 1.3" FORCE)
find_library(SDL_LIBRARY
    NAMES SDL-1.3.0 SDL
    PATHS ${SDL_FOLDER}
    PATH_SUFFIXES local/lib VisualC/SDL/Release
    NO_DEFAULT_PATH
)

find_library(SDL_image
    NAMES SDL-1.3.0 SDL
    PATHS ${SDL_FOLDER}
    PATH_SUFFIXES local/lib VisualC/SDL/Release
    NO_DEFAULT_PATH
)

find_library(SDLMAIN_LIBRARY
    NAMES SDLmain
    PATHS ${SDL_FOLDER}
    PATH_SUFFIXES local/lib VisualC/SDLmain/Release
    NO_DEFAULT_PATH
)

# Include OpenGL
find_package(OpenGL REQUIRED)

# Include LibXML
FIND_PACKAGE(LibXml2)
INCLUDE_DIRECTORIES (SYSTEM "${LIBXML2_INCLUDE_DIR}")

#Génération de la liste des fichiers sources
file(
	GLOB_RECURSE
	nengine_files
	Sources/NEngine/*
)

file(
	GLOB_RECURSE
	main_files
	Sources/game/*
)

#Déclaration de l'exécutable
add_library(NEngine SHARED ${nengine_files})
TARGET_LINK_LIBRARIES(NEngine SDL SDL_image)

add_executable(OpenAWars ${main_files})
TARGET_LINK_LIBRARIES(OpenAWars NEngine SDL ${LIBXML2_LIBRARIES})

