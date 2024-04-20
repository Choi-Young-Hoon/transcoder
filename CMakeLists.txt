cmake_minimum_required (VERSION 3.6)

project (transcoder)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)

elseif (LINUX)
    set (CMAKE_CXX_FLAGS -Wall)
	set (CMAKE_CXX_FLAGS_RELEASE "-O3")
	set (CMAKE_CXX_FLAGS_DEBUG "-g")
endif ()


add_subdirectory(thirdparty/ffmpegpp)
add_subdirectory(libs)
add_subdirectory(transcode_server)
#add_subdirectory(test)