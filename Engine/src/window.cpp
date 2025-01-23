#include "window.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace BV;

namespace glfw_callbacks
{
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{ glViewport(0, 0, width, height); }

	static void mouse_callback(GLFWwindow* windowIn, double xposIn, double yposIn)
	{
		window* win_instance = static_cast<window*>(glfwGetWindowUserPointer(windowIn));
		if (win_instance)
		{
			for (auto& m : win_instance->GetMouseCallbacks())
				m((float)xposIn, (float)yposIn);
		}
	}
	
	static void scroll_callback(GLFWwindow* windowIn, double xoffset, double yoffset)
	{
		window* win_instance = static_cast<window*>(glfwGetWindowUserPointer(windowIn));
		if (win_instance)
			win_instance->setScrollOffset((float)yoffset);
	}

	static void key_callback(GLFWwindow* windowIn, int key, int scancode, int action, int mods)
	{
		window* win_instance = static_cast<window*>(glfwGetWindowUserPointer(windowIn));
		if (win_instance)
		{
			for (const auto& m : win_instance->GetKeyCallbacks())
			{
				m(key, scancode, action, mods);
			}
		}
	}
}

window::window(int scr_width, int scr_height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef PL_MACOSX
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	m_window = glfwCreateWindow(scr_width, scr_height, "Bad Voxel", nullptr, nullptr);
	if (m_window == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(m_window, glfw_callbacks::framebuffer_size_callback);
	glfwSetCursorPosCallback(m_window, glfw_callbacks::mouse_callback);
	glfwSetScrollCallback(m_window, glfw_callbacks::scroll_callback);
	glfwSetKeyCallback(m_window, glfw_callbacks::key_callback);

	// loading glad opengl func pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glViewport(0, 0, scr_width, scr_height);
	glEnable(GL_DEPTH_TEST);
}

window::~window()
{
	glfwTerminate(); // automatically frees up memory from variables such as m_window
	m_window = nullptr;
}