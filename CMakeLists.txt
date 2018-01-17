cmake_minimum_required(VERSION 2.8.9)
project(Project_Creator)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

link_directories(link)

if(WIN32)
	include_directories(include_win32)
	link_directories(link_win32)
endif(WIN32)

file(GLOB SOURCES "src/*.cpp" "include/*.hpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../run)

add_executable(Project_Creator ${SOURCES})

if(WIN32)
	target_link_libraries(Project_Creator )
elseif(UNIX)
	target_link_libraries(Project_Creator )
endif(WIN32)
