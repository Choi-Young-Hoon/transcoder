set(SOURCES 
        main.cpp

        TranscodeServer.cpp 
)

set(TRANSCODE_NETWORK_TEST transcode_network_test)

enable_testing() # build/test Æú´õ »ý¼ºµÊ

add_executable(${TRANSCODE_NETWORK_TEST} ${SOURCES})

find_package (Boost REQUIRED COMPONENTS system json)
find_package(GTest CONFIG REQUIRED)

target_include_directories (${TRANSCODE_NETWORK_TEST} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${TRANSCODE_NETWORK_TEST} PRIVATE 
											        ${PROJECT_NAME}
                                                    Boost::system
                                                    Boost::json
                                                    GTest::gtest
                                                    GTest::gtest_main
                                                    GTest::gmock
                                                    GTest::gmock_main)
