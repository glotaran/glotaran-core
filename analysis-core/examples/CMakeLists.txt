cmake_policy(SET CMP0063 OLD)

add_executable(large_example large_example.cpp)

target_link_libraries(large_example analysis-core)
set_property(TARGET large_example PROPERTY CXX_STANDARD 11)