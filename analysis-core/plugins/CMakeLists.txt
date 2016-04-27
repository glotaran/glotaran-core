set(plugins
    kin_sim
    kin_sol
    )
    
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library(kin_sim SHARED kin_sim)

add_library(kin_sol SHARED kin_sol internal/lapack)
target_link_libraries(kin_sol ${LAPACK_LIBRARIES})

foreach(plugin ${plugins})
  target_include_directories(${plugin} PRIVATE "include")
  target_link_libraries(${plugin} analysis-core)
  set_property(TARGET ${plugin} PROPERTY CXX_STANDARD 11)
  set_target_properties(${plugin} PROPERTIES PREFIX "")
endforeach(plugin)
