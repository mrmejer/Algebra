cmake_minimum_required(VERSION 3.24)
project(Raspberry-Maths)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)

add_executable(Main main.cpp
        lib/BigNum.h lib/BigNum.cpp
        lib/BarretReducer.h lib/BarretReducer.cpp
        lib/miller_rabin_test.h lib/miller_rabin_test.cpp
        lib/pollards_rho.h lib/pollards_rho.cpp
)

add_executable(Integer_factorization-pollards_rho integer_factorization-pollards_rho.cpp
        lib/BigNum.h lib/BigNum.cpp
        lib/BarretReducer.h lib/BarretReducer.cpp
        lib/miller_rabin_test.h lib/miller_rabin_test.cpp
        lib/pollards_rho.h lib/pollards_rho.cpp
)

add_executable(Primality_test-miller_rabin primality_test-miller_rabin.cpp
        lib/BigNum.h lib/BigNum.cpp
        lib/BarretReducer.h lib/BarretReducer.cpp
        lib/miller_rabin_test.h lib/miller_rabin_test.cpp
        lib/pollards_rho.h lib/pollards_rho.cpp
)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)