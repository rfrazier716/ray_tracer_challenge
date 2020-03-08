
cmake_minimum_required (VERSION 3.12)
project ("rayTracer")

# set to cpp 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Optimizations
# string(REPLACE "/O2" "/Od" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

# Variables
set(TEST_BIN_DIR "${CMAKE_BINARY_DIR}/tests")
set(EXAMPLE_BIN_DIR "${CMAKE_BINARY_DIR}/examples")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

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
"src/actors/actors.cpp"
"src/actors/cameras.cpp"
"src/actors/lights.cpp"

"src/renderers.cpp"

)
target_link_libraries(tracerCore tracerGeometry)




#Build example programs
IF(DEFINED BUILD_EXAMPLES)
	INCLUDE("examples")
ENDIF()

#Build Ctests
INCLUDE("tests")