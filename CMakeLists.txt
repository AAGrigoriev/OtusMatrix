cmake_minimum_required(VERSION 3.10)

SET(SOURCE_WAY src)
SET(TEST_WAY test)

add_executable(matrix ${SOURCE_WAY}/main.cpp)

set (CMAKE_CXX_STANDARD 17)


target_include_directories(matrix PRIVATE 
                                  inc)                



                                  find_package(GTest REQUIRED)
find_package(Threads)

add_executable(g_test_matrix ${TEST_WAY}/main.cpp )

target_link_libraries(g_test_matrix 
                                    PRIVATE 
                                    ${GTEST_LIBRARIES} 
                                    ${GTEST_MAIN_LIBRARIES} 
                                    pthread)

target_include_directories(g_test_matrix 
                                    PRIVATE 
                                    ${GTEST_INCLUDE_DIRS}
                                    inc)

add_test(g_test_matrix g_test_matrix)