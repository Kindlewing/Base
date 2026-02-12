cmake_minimum_required(VERSION 3.24)
project(Base C)

option(STANDALONE "Build Base as standalone project" OFF)
if(STANDALONE)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

add_library(Base STATIC)
target_compile_features(Base PUBLIC c_std_99)




target_sources(Base
	PRIVATE
		src/base_math.c
		src/profile.c
		src/string8.c
)

if(WIN32)
	target_sources(Base PRIVATE src/arena_win32.c)
elseif(UNIX AND NOT APPLE)
	target_sources(Base PRIVATE src/arena_linux.c)
endif()

target_include_directories(Base PUBLIC include)

target_compile_options(
	Base
	PRIVATE
	$<$<CONFIG:Debug>:-Wall -Wextra -g -O0>
)

