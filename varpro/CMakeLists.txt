cmake_minimum_required(VERSION 2.8)
project(varpro)

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

find_package(LAPACK REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/MiLi/)

add_executable(varpro main.cpp dataset.cpp lapack.cpp)
target_link_libraries(varpro ${CERES_LIBRARIES})
target_link_libraries(varpro ${LAPACK_LIBRARIES})

set_property(TARGET varpro PROPERTY CXX_STANDARD 11)

install(TARGETS varpro RUNTIME DESTINATION bin)
