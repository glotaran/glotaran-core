cmake_minimum_required(VERSION 2.8)
project(analysis-core)

include(GenerateExportHeader)

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

find_package(LAPACK REQUIRED)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_program(COG cog.py)
mark_as_advanced(FORCE COG)

if(COG)
  set(gen
        dataset
      )
  foreach(g ${gen})
    execute_process(COMMAND ${COG} -d -o "${CMAKE_CURRENT_SOURCE_DIR}/include/analysis-core/${g}.h" "${CMAKE_CURRENT_SOURCE_DIR}/codegen/${g}.h")
    execute_process(COMMAND ${COG} -d -o "${CMAKE_CURRENT_SOURCE_DIR}/src/${g}.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/codegen/${g}.cpp")
  endforeach(g)
else()
  message(FATAL_ERROR "cog.py not found")
endif(COG)

set(srcs
    src/dataset
    )

add_library(${PROJECT_NAME} SHARED ${srcs})

generate_export_header(${PROJECT_NAME} BASE_NAME ${PROJECT_NAME} EXPORT_MACRO_NAME ANALYSIS_CORE_EXPORT EXPORT_FILE_NAME analysis-core_export.h)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)