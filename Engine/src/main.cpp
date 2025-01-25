#include <iostream>
#include <fstream>
#include <filesystem>
#include <Windows.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "game.h"
#include "renderer.h"
#include "Shader.h"
#include "window.h"

#ifdef BV_DEBUG
// OpenGL debug callback
inline void APIENTRY OGL_DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
							 GLsizei length, const GLchar* message, const void* userParam)
{
	std::cerr << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "")
			  << " type = " << type << ", severity = " << severity
			  << ", message = " << message << std::endl;
}
#endif

int main()
{
#ifdef BV_DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OGL_DebugMessageCallback, 0);
#endif
	
	BV::game Game;

	while (!glfwWindowShouldClose(Game.Window.getGLFWwindow()))
	{
		Game.update_model();

		Game.draw_frame();
	}
	return 0;
}