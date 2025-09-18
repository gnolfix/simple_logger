cmake_minimum_required (VERSION 3.20)

project ("simple_logger" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCES
            ${SRC_DIR}/Logger.cpp
            ${SRC_DIR}/LogFormat.cpp
            )

add_library(simple_logger STATIC ${SOURCES})

option(ENABLE_TESTS "Enable building tests" ON)

if(ENABLE_TESTS)
    enable_testing()
    add_executable(tests ${SRC_DIR}/logger_tests.cpp)
    target_link_libraries(tests PRIVATE simple_logger)
    add_test(NAME SimpleLoggerTests COMMAND tests)
endif()



