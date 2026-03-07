add_executable(BurningSkyGame
  src/main.cpp
  ../engine/src/Platform/GLFWWindow.cpp
  ../engine/src/Core/Window.cpp
  ../engine/src/Graphics/Shader.cpp
)

target_include_directories(BurningSkyGame PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../engine/include
)

message(STATUS "BurningSkyGame include dirs: ${CMAKE_CURRENT_LIST_DIR}/../engine/include")

target_link_libraries(BurningSkyGame PRIVATE
  glfw
  glad
  glm
  OpenGL::GL
)


if (WIN32)
  target_link_libraries(BurningSkyGame PRIVATE opengl32)
endif()