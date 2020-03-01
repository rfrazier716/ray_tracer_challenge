
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

# Library for Ray Tracer Geometry
add_library(tracerGeometry STATIC
"src/geometry/transforms.cpp"
"src/geometry/uvsurface.cpp"
"src/geometry/nurbs/nurbc.cpp"
)

# Library for Ray Tracer Core Package
add_library(tracerCore STATIC
"src/canvas.cpp"
"src/actors/lights.cpp"
)
target_link_libraries(tracerCore tracerGeometry)


# ---Building Examples ---

# Projectile motion example
add_executable(projectileMotion "src/examples/projectile_motion.cpp")
target_link_libraries(projectileMotion tracerCore)
set_target_properties(projectileMotion PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${EXAMPLE_BIN_DIRECTORY}")

# Points around a clock face
add_executable(clock "src/examples/clockFace.cpp")
target_link_libraries(clock tracerCore)
set_target_properties(clock PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${EXAMPLE_BIN_DIRECTORY}")

# ---Tests---
enable_testing() # enable testing for ctest integration

# Adding Catch which manages test routines
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "test")
add_library(catch_main "test/catch_main.cpp")

# Tuple/GLM Test
add_executable(testTuple "test/verify_tuple.cpp")
set_target_properties(testTuple PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TEST_BIN_DIRECTORY}")
target_link_libraries(testTuple Catch catch_main)
add_test(NAME Tuples COMMAND tuple_test)

# Canvas Test
add_executable(testCanvas "test/testCanvas.cpp")
set_target_properties(testCanvas PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TEST_BIN_DIRECTORY}")
target_link_libraries(testCanvas Catch catch_main tracerCore)
add_test(NAME Canvas COMMAND testCanvas)

# Matrix Test
add_executable(testMatrix "test/testMatrices.cpp")
target_link_libraries(testMatrix Catch catch_main tracerCore)
add_test(NAME Matrices COMMAND testMatrix)

# NURBS Contour Test
add_executable(testNurbsC "test/geometryTests/testNURBContour.cpp")
target_link_libraries(testNurbsC Catch catch_main tracerCore)
add_test(NAME NurbContour COMMAND testNurbsC)

# Solid Body Test
add_executable(testSolids "test/actorTests/testsolidbodies.cpp")
target_link_libraries(testSolids Catch catch_main tracerCore)
add_test(NAME ObjectClass COMMAND testSolids)

# Sphere Test
add_executable(testSpheres "test/geometryTests/testSphere.cpp")
target_link_libraries(testSpheres Catch catch_main tracerCore)
add_test(NAME sphereClass COMMAND testSpheres )

# Point Surface Test
add_executable(testPointSurface "test/geometryTests/testPointSurface.cpp")
target_link_libraries(testPointSurface Catch catch_main tracerCore)
add_test(NAME pointsurface COMMAND testPointSurface )

# Ray Structure Test
add_executable(testRay "test/geometryTests/testRay.cpp")
target_link_libraries(testRay Catch catch_main)
add_test(NAME rayStruct COMMAND testRay)

# Light Tests
add_executable(testlights "test/actorTests/testlightsources.cpp")
target_link_libraries(testlights Catch catch_main tracerCore)
add_test(NAME lights COMMAND testlights )