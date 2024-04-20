set (SOURCES 
        ByteBuffer.cpp

        transcode/Result.cpp
        transcode/TranscodeServer.cpp
        transcode/TranscodeSession.cpp
        transcode/ExecuteList.cpp
        transcode/ExecuteInterface.cpp
        transcode/ExecuteFileUpload.cpp
)



set(UPDATED_SOURCES "")
foreach(SOURCE IN LISTS SOURCES)
    list(APPEND UPDATED_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}")
endforeach()

target_sources (${PROJECT_NAME} PRIVATE ${UPDATED_SOURCES})