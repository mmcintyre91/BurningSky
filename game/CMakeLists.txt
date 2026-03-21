add_executable(BurningSkyGame
  src/main.cpp
  src/GameLayer.cpp
	src/Scenes/TitleScene.cpp
	src/Scenes/PlayScene.cpp
	src/Scenes/LoseScene.cpp
  ../engine/src/Platform/GLFWWindow.cpp
  ../engine/src/Core/Window.cpp
  ../engine/src/Core/Application.cpp
  ../engine/src/Core/Input.cpp
  ../engine/src/Graphics/Shader.cpp
  ../engine/src/Graphics/VertexBuffer.cpp
  ../engine/src/Graphics/IndexBuffer.cpp
  ../engine/src/Graphics/VertexArray.cpp
  ../engine/src/Graphics/Renderer2D.cpp
  ../engine/src/Graphics/OrthographicCamera.cpp
  ../engine/src/Graphics/Texture2D.cpp
  ../engine/src/Graphics/TextureLibrary.cpp
 )

target_include_directories(BurningSkyGame PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../engine/include
  ${CMAKE_CURRENT_LIST_DIR}/../third_party/stb
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