cmake_minimum_required(VERSION 2.8)
project(tests)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" COMPILER_HAS_CXX11_FLAG)
if (CXX11 AND COMPILER_HAS_CXX11_FLAG)
  # Update CMAKE_REQUIRED_FLAGS used by CheckCXXSourceCompiles to include
  # -std=c++11 s/t we will detect the C++11 versions of unordered_map &
  # shared_ptr if they exist.
  set(CMAKE_REQUIRED_FLAGS -std=c++11)
endif (CXX11 AND COMPILER_HAS_CXX11_FLAG)

# To ensure that CXX11 accurately reflects whether we are using C++11,
# check if it is required given where the potentially C++11 features Ceres
# uses were found, and disable it if C++11 is not being used.
if (CXX11)

    message("   ==============================================================")
    message("   Compiling Ceres using C++11.  This will result in a version ")
    message("   of Ceres that will require the use of C++11 in client code.")
    message("   ==============================================================")
    list(APPEND CERES_COMPILE_OPTIONS CERES_USE_CXX11)
    if (COMPILER_HAS_CXX11_FLAG)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
endif(CXX11)

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

add_executable(global_fitting global_fitting.cc)
target_link_libraries(global_fitting ${CERES_LIBRARIES})

add_executable(global_fitting_test global_fitting_test.cc)
target_link_libraries(global_fitting_test ${CERES_LIBRARIES})

install(TARGETS global_fitting RUNTIME DESTINATION bin)
install(TARGETS global_fitting_test RUNTIME DESTINATION bin)
