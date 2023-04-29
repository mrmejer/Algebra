# 'Google_test' is the subproject name
cmake_minimum_required(VERSION 3.24)
project(GoogleTest)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(general_test general_test.cpp)
target_link_libraries(general_test gtest gtest_main)

add_executable(logical_operators_test logical_operators_test.cpp)
target_link_libraries(logical_operators_test gtest gtest_main)

add_executable(arithmetic_operators_test arithmetic_operators_test.cpp)
target_link_libraries(arithmetic_operators_test gtest gtest_main)

add_executable(bin-arithmetic_operators_test bin-arithmetic_operators_test.cpp)
target_link_libraries(bin-arithmetic_operators_test gtest gtest_main)

add_executable(barret_reducer_test barret_reducer_test.cpp)
target_link_libraries(barret_reducer_test gtest gtest_main)

add_executable(non_member_bignum_functions_test non_member_bignum_functions_test.cpp)
target_link_libraries(non_member_bignum_functions_test gtest gtest_main)

add_executable(all_tests
        ../lib/BigNum.h ../lib/BigNum.cpp
        ../lib/BarretReducer.h ../lib/BarretReducer.cpp
        ../lib/miller_rabin_test.h ../lib/miller_rabin_test.cpp
        ../lib/pollards_rho.h ../lib/pollards_rho.cpp
        logical_operators_test.cpp
        arithmetic_operators_test.cpp
        general_test.cpp
        bin-arithmetic_operators_test.cpp
        barret_reducer_test.cpp
        non_member_bignum_functions_test.cpp rho_test.cpp)
target_link_libraries(all_tests gtest gtest_main)