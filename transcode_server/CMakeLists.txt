cmake_minimum_required (VERSION 3.6)

project (transcode_server)

set (TRANSCODER_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/${PROJECT_NAME})
set (TRANSCODER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable (${PROJECT_NAME} main.cpp)

find_package (Boost REQUIRED COMPONENTS system json)
target_include_directories (${PROJECT_NAME} PUBLIC 
												${TRANSCODER_INCLUDE_DIR}
												${Boost_INCLUDE_DIRS})

target_link_libraries (${PROJECT_NAME} PUBLIC 
											Boost::system 
											Boost::json
											ffmpegpp)

add_subdirectory (src)

											   