
cmake_minimum_required (VERSION 3.12)
project ("rayTracer")

# set to cpp 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Optimizations
string(REPLACE "/O2" "/Od" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

# Variables
set(TEST_BIN_DIR "${CMAKE_BINARY_DIR}/tests")
set(EXAMPLE_BIN_DIR "${CMAKE_BINARY_DIR}/examples")

# Put executables in the bin subdirectory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Add include directories
include_directories ("include")	# standard include directory
include_directories ("include/glm-0.9.9.7/glm") # Directory for opengl Math library


# Add source to this project's executable.

# Adding Libraries
add_library(canvas "src/canvas.cpp")
add_library(transforms "src/geometry/transforms.cpp")
add_library(primitives "src/geometry/primitives.cpp")
## nurbs
add_library(nurbc "src/geometry/nurbs/nurbc.cpp")


# ---Building Examples ---

# Projectile motion example
add_executable(projectileMotion "src/examples/projectile_motion.cpp")
target_link_libraries(projectileMotion canvas primitives)
set_target_properties(projectileMotion PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${EXAMPLE_BIN_DIRECTORY}")

# Points around a clock face
add_executable(clock "src/examples/clockFace.cpp")
target_link_libraries(clock canvas primitives transforms)
set_target_properties(clock PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${EXAMPLE_BIN_DIRECTORY}")

# ---Tests---
enable_testing()

# Adding Catch which manages test routines
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "test")
add_library(catch_main "test/catch_main.cpp")

# Tuple/GLM Test
add_executable(testTuple "test/verify_tuple.cpp")
set_target_properties(testTuple PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TEST_BIN_DIRECTORY}")
target_link_libraries(testTuple Catch catch_main primitives)

# Canvas Test
add_executable(testCanvas "test/testCanvas.cpp")
set_target_properties(testCanvas PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TEST_BIN_DIRECTORY}")
target_link_libraries(testCanvas Catch catch_main canvas primitives)

# Matrix Test
add_executable(testMatrix "test/testMatrices.cpp")
target_link_libraries(testMatrix Catch catch_main transforms primitives)

# NURBS Contour Test
add_executable(testNurbsC "test/geometryTests/testNURBContour.cpp")
target_link_libraries(testNurbsC Catch catch_main nurbc primitives)



enable_testing()
add_test(NAME Tuples COMMAND tuple_test)
add_test(NAME Canvas COMMAND testCanvas)
add_test(NAME Matrices COMMAND testMatrix)
