add_executable(firing-projectiles FiringProjectiles.cpp)
target_link_libraries(
  firing-projectiles PRIVATE project_options project_warnings)