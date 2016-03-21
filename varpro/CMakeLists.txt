cmake_minimum_required(VERSION 2.8)
project(varpro)

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

find_package(LAPACK REQUIRED)

#add_executable(varpro main.cpp dataset.cpp lapack.cpp ntr.c)

file(GLOB srcs src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${srcs})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} ${CERES_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LAPACK_LIBRARIES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
add_subdirectory(examples)