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
#include "renderer.h"
#include "Shader.h"
#include "window.h"

void processInput(BV::window* windowIn);

void APIENTRY OGL_DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                 GLsizei length, const GLchar* message, const void* userParam)
{
    std::cerr << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "")
              << " type = " << type << ", severity = " << severity
              << ", message = " << message << std::endl;
}

// screen settings
constexpr unsigned int SCREEN_WIDTH = 800;
constexpr unsigned int SCREEN_HEIGHT = 600;

// camera statics
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

// mouse bullshits
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;


Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float deltaTime = 0.0f; // time between cur frame and last frame
float lastFrame = 0.0f; // time of last frame

float lastMouseX = 0.0f, lastMouseY = 0.0f;

int main()
{

	// window init
	BV::window Window(SCREEN_WIDTH, SCREEN_HEIGHT);

#ifdef BV_DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OGL_DebugMessageCallback, 0);
#endif
	
	
	// renderer & shader initialization bullshits
	Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
	BV::renderer Renderer;
	Renderer.init();
	
	Renderer.set_texture("shaders/mc_grass.jpg", GL_RGB);
	
	Window.AddMouseEvent([&](float xpos, float ypos)
	{
		if (firstMouse)
		{
			lastMouseX = xpos;
			lastMouseY = ypos;
			firstMouse = false;
		}
		float xoffset = xpos - lastMouseX;
		float yoffset = lastMouseY - ypos; // reversed since y-coordinates go from bottom to top
			
		lastMouseX = xpos;
		lastMouseY = ypos;
			
		camera.ProcessMouseMovement(xoffset, yoffset);
	});

	
	float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//Renderer.load_vertices(vertices, 180);
	Renderer.add_cube(glm::vec3{0.0f, 0.0f, -10.0f});
	// TODO: Only the 1 cube out of these two would be drawn, and it is the one called last
	Renderer.add_cube(glm::vec3{0.0f, 5.0f, -10.0f});

	
	// render loop
	while (!glfwWindowShouldClose(Window.getGLFWwindow()))
	{
		// delta time bullshits
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		// input
		processInput(&Window);
		
		// rendering commands here
		auto scrDims = Window.getWindowDimensions();
		Renderer.draw_vertices(camera, (float)scrDims.first, (float)scrDims.second, false);
		
		// check and call events and swap the buffers
		glfwSwapBuffers(Window.getGLFWwindow());
		glfwPollEvents();
	}
	
	
	Renderer.reset();
	
	return 0;
}

void processInput(BV::window* windowIn)
{
	if (windowIn->isKeyPressed(GLFW_KEY_ESCAPE) == true)
		glfwSetWindowShouldClose(windowIn->getGLFWwindow(), true);

	if (windowIn->isKeyPressed(GLFW_KEY_W) == true)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (windowIn->isKeyPressed(GLFW_KEY_S) == true)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (windowIn->isKeyPressed(GLFW_KEY_A) == true)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (windowIn->isKeyPressed(GLFW_KEY_D) == true)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (windowIn->isKeyPressed(GLFW_KEY_SPACE) == true)
		camera.ProcessKeyboard(UP, deltaTime);
	if (windowIn->isKeyPressed(GLFW_KEY_LEFT_CONTROL) == true)
		camera.ProcessKeyboard(DOWN, deltaTime);
}