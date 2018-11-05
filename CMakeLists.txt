cmake_minimum_required(VERSION 3.10)
project(Stage4)
set(Boost_INCLUDE_DIR /usr/include/)
set(Boost_LIBRARY_DIR /usr/lib/)
find_package(Boost REQUIRED COMPONENTS regex filesystem)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

file(GLOB HEADERS "*.h")

SET(GCC_COVERAGE_COMPILE_FLAGS "-rdynamic")

set(
        CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_HOME_DIRECTORY}/build
)

add_executable(Stage4 main.cpp ${HEADERS})
target_link_libraries(Stage4 ${Boost_LIBRARIES})
set_target_properties(Stage4 PROPERTIES OUTPUT_NAME "main")
