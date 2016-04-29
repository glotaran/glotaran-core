cmake_minimum_required(VERSION 2.8)
project(analysis-core)

include(GenerateExportHeader)

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

find_package(LAPACK REQUIRED)

find_package(Armadillo 6.700 REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

find_package(Boost 1.58.0 REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(include
                    external/Boost.DLL/include)

set(internal
    src/internal/pluginmanager
    src/internal/solver
    src/internal/simulator
    )

set(srcs
    src/api
    src/dataset
    src/options
    src/core
    )

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library(${PROJECT_NAME} SHARED ${internal} ${srcs})

generate_export_header(${PROJECT_NAME} BASE_NAME ${PROJECT_NAME} EXPORT_MACRO_NAME ANALYSIS_CORE_EXPORT EXPORT_FILE_NAME analysis-core_export.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})


target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${CERES_LIBRARIES} ${ARMADILLO_LIBRARIES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

add_subdirectory(plugins)
add_subdirectory(examples)