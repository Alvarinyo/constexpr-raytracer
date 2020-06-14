add_executable(firing-projectiles FiringProjectiles.cpp)
target_link_libraries(
  firing-projectiles PRIVATE project_options project_warnings)

add_executable(clock Clock.cpp)
target_link_libraries(
  clock PRIVATE project_options project_warnings)

add_executable(sphere-silhouette SphereSilhouette.cpp)
target_link_libraries(
  sphere-silhouette PRIVATE project_options project_warnings)