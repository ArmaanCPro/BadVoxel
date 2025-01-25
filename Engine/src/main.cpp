#include <iostream>
#include <fstream>
#include <Windows.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "game.h"
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
	BV::game Game;
	
#ifdef BV_DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OGL_DebugMessageCallback, 0);
#endif

	while (!glfwWindowShouldClose(Game.Window.getGLFWwindow()))
	{
		Game.update_model();

		Game.draw_frame();
	}
	return 0;
}