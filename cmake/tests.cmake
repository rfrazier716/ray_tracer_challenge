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
add_test(NAME Tuples COMMAND testTuple)

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
target_link_libraries(testRay Catch catch_main tracerCore)
add_test(NAME rayStruct COMMAND testRay)


### Actor Tests ###
# Generic Actor Test
add_executable(testactor "test/actorTests/testactor.cpp")
target_link_libraries(testactor Catch catch_main tracerCore)
add_test(NAME genericActors COMMAND testactor)

# Light Tests
add_executable(testlights "test/actorTests/testlightsources.cpp")
target_link_libraries(testlights Catch catch_main tracerCore)
add_test(NAME lights COMMAND testlights )

# Camera Tests
add_executable(testcameras "test/actorTests/testcameras.cpp")
target_link_libraries(testcameras Catch catch_main tracerCore)
add_test(NAME cameras COMMAND testcameras )

# Solid Body Test
add_executable(testSolids "test/actorTests/testsolidbodies.cpp")
target_link_libraries(testSolids Catch catch_main tracerCore)
add_test(NAME solidObjects COMMAND testSolids)

### Renderer Tests
#Generic Renderer Test
add_executable(testGenericRenderer "test/testRenderers.cpp")
target_link_libraries(testGenericRenderer Catch catch_main tracerCore)
add_test(NAME genericRenderer COMMAND testGenericRenderer)