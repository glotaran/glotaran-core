cmake_minimum_required(VERSION 2.8)
project(varpro)

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

add_executable(varpro main.cpp)
target_link_libraries(varpro ${CERES_LIBRARIES})

set_property(TARGET varpro PROPERTY CXX_STANDARD 11)

install(TARGETS varpro RUNTIME DESTINATION bin)
