
cmake_minimum_required (VERSION 3.12)
project ("rayTracer")

# Add include directories
include_directories ("include")	# standard include directory
include_directories ("include/glm-0.9.9.7/glm") # Directory for opengl Math library


# GLFW Library
include_directories ("lib/GLFW-3.3.1/Include") # directory for GLFW precompiled library
find_library(LIB_GLFW glfw3 HINTS "lib/GLFW-3.3.1/")


# GLEW Library
add_compile_definitions(GLEW_STATIC)
include_directories ("lib/GLEW-2.1.0/Include") # directory for GLFW precompiled library
find_library(LIB_GLEW glew32s HINTS "lib/GLEW-2.1.0/")


#OPENGL Library
find_library(LIB_OPENGL opengl32)

# Add source to this project's executable.
add_executable (tracer "src/tracer.cpp")

# Adding Libraries
add_library(logger "src/log.cpp")
add_library(geometry "src/geometry.cpp")

# Linking Libraries
target_link_libraries(tracer logger)


# test file for OpenGL
add_executable(opengl_test "test/openGL_test.cpp")
target_link_libraries(opengl_test ${LIB_GLFW} ${LIB_OPENGL} ${LIB_GLEW})

# test settings
enable_testing()

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "test")
add_library(catch_main "test/catch_main.cpp")


add_executable(tuple_test "test/verify_tuple.cpp")
target_link_libraries(tuple_test Catch catch_main)



enable_testing()
add_test(NAME Tuples COMMAND tuple_test)
