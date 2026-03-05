# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.20)
project(BurningSky LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ---- third_party ----
# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/glfw)

# GLAD (we build glad.c into a static lib)
add_library(glad STATIC
  third_party/glad/src/glad.c
)
target_include_directories(glad PUBLIC
  third_party/glad/include
)
target_compile_definitions(glad PUBLIC GLFW_INCLUDE_NONE)

# GLM (header-only)
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE
  third_party/glm
)

# OpenGL
find_package(OpenGL REQUIRED)

add_subdirectory(game)