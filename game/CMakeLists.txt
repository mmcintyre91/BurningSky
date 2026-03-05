add_executable(BurningSkyGame
  src/main.cpp
)

target_link_libraries(BurningSkyGame PRIVATE
  glfw
  glad
  glm
  OpenGL::GL
)


if (WIN32)
  target_link_libraries(BurningSkyGame PRIVATE opengl32)
endif()