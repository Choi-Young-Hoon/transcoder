set(SOURCES 
        main.cpp
)

set(UTILS_TEST utils_test)

enable_testing() # build/test Æú´õ »ý¼ºµÊ

add_executable(${UTILS_TEST} ${SOURCES})

find_package(GTest CONFIG REQUIRED)
target_link_libraries(${UTILS_TEST} PRIVATE 
											${PROJECT_NAME}
                                            GTest::gtest
                                            GTest::gtest_main
                                            GTest::gmock
                                            GTest::gmock_main)