# ---Building Examples ---

# Projectile motion example
add_executable(projectileMotion "src/examples/projectile_motion.cpp")
target_link_libraries(projectileMotion tracerCore)
set_target_properties(projectileMotion PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${EXAMPLE_BIN_DIRECTORY}")

# Points around a clock face
add_executable(clock "src/examples/clockFace.cpp")
target_link_libraries(clock tracerCore)
set_target_properties(clock PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${EXAMPLE_BIN_DIRECTORY}")