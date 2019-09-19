cmake_minimum_required(VERSION 3.0)
project(mc-pricer CXX)

# Prefix
if (NOT PREFIX)
    set(PREFIX ${CMAKE_CURRENT_BINARY_DIR})
endif (NOT PREFIX)
set(CMAKE_INSTALL_PREFIX ${PREFIX} CACHE STRING "Installation prefix." FORCE)

if (CXX)
    set(CMAKE_CXX_COMPILER ${CXX})
endif (CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Release or Debug
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif ()


# Detect PNL
find_package(Pnl REQUIRED)
set(LIBS ${LIBS} ${PNL_LIBRARIES})
include_directories(${PNL_INCLUDE_DIRS})
if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_definitions(-DPNL_RANGE_CHECK_OFF)
endif()

# Detect Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} "doc/doxygen.cfg"
            WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
            COMMENT "Building user's documentation into doc build dir..."
            )
endif()

# Add math lib
set(LIBS ${LIBS} m)
file(GLOB SRC
        "src/*.hpp"
        "src/*.cpp")

file(GLOB SRC
        "src/*.hpp"
        "src/*.cpp"
    )

# Add jlparser
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if (WIN32)
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()
add_subdirectory(src/3rdparty/jlparser)


# Test the parser
add_executable(test-parser tests/test_parser.cpp ${SRC})
target_link_libraries(test-parser jl_parser ${LIBS})

add_executable(mc-example tests/mc_example.cpp ${SRC})
target_link_libraries(mc-example jl_parser ${LIBS})

# Tests Pricer
add_executable(test-payoff tests/testPayoff.cpp ${SRC})
target_link_libraries(test-payoff jl_parser ${LIBS})

add_executable(test-asset tests/testAsset.cpp ${SRC})
target_link_libraries(test-asset jl_parser ${LIBS})

add_executable(test-pricer0 tests/testPrice0.cpp ${SRC})
target_link_libraries(test-pricer0 jl_parser ${LIBS})

add_executable(test-pricert tests/testPriceT.cpp ${SRC})
target_link_libraries(test-pricert jl_parser ${LIBS})

add_executable(test-shift tests/testShiftAsset.cpp ${SRC})
target_link_libraries(test-shift jl_parser ${LIBS})

add_executable(test-deltas tests/testDeltas.cpp ${SRC})
target_link_libraries(test-deltas jl_parser ${LIBS})


# Applications finales
add_executable(price0 tests/price0.cpp ${SRC})
target_link_libraries(price0 jl_parser ${LIBS})

add_executable(hedge tests/hedge.cpp ${SRC})
target_link_libraries(hedge jl_parser ${LIBS})

# Print compiler flags
get_directory_property(DirDefs COMPILE_DEFINITIONS)
message(STATUS "COMPILE_DEFINITIONS = ${DirDefs}")
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "C++ Flags: ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} ${CMAKE_LINKER_EXE_FLAGS}" )
else()
    message(STATUS "C++ Flags: ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_LINKER_EXE_FLAGS}" )
endif()


# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(Google_Tests_run tests/test1.cpp src/Basket.hpp src/BlackScholesModel.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main jl_parser ${LIBS})
