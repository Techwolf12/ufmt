cmake_minimum_required(VERSION 2.8.9)
project(ufmt)

if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

add_executable(ufmt
	src/ufmt/LanguageDefinition.h
	
	src/ufmt/Formatter.cpp
	src/ufmt/Formatter.h
	
	src/ufmt/UFMT.cpp
	src/ufmt/UFMT.h
	
	src/ufmt/main.cpp
	
	src/ufmt/Formatters/Html.cpp
	src/ufmt/Formatters/Html.h
)

add_subdirectory(src/Scratch)
include_directories(src/Scratch/src)
target_link_libraries(ufmt Scratch)