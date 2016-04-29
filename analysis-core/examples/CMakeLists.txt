if(POLICY CMP0063)
  cmake_policy(SET CMP0063 OLD)
endif()

add_executable(large_example_cpp large_example.cpp)

target_link_libraries(large_example_cpp analysis-core)
set_property(TARGET large_example_cpp PROPERTY CXX_STANDARD 11)

add_executable(large_example_c large_example.c)

target_link_libraries(large_example_c analysis-core)