project(transcoder)


add_library(${PROJECT_NAME})


set(TRANSCODER_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC Drogon::Drogon
                                             ffmpegpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
                                                  )


add_subdirectory(src)
add_subdirectory(test)