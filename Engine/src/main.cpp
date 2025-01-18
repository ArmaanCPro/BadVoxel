#include <iostream>

#include <Windows.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// screen settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

// vertex shader source code. messy for now
const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

// fragment shader source code
const char* fragmentShaderOrangeSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

const char* fragmentShaderYellowSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
		"FragColor = vec4(0.8f, 0.8f, 0.1f, 1.0f);\n"
	"}\0";

int main()
{
	// initialization
	// --------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef PL_MACOSX
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dangerfield", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// loading glad opengl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);


	// building and compiling shader program
	// -------------------------------------
	// shader initialization bullshits
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int shaderProgramOrange = glCreateProgram();
	unsigned int shaderProgramYellow = glCreateProgram();
	// setting up shader sources
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShaderOrange, 1, &fragmentShaderOrangeSource, nullptr);
	glCompileShader(fragmentShaderOrange);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderYellowSource, nullptr);
	glCompileShader(fragmentShaderYellow);
	// link the first program
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glLinkProgram(shaderProgramOrange);
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	// setting up vertex data (and buffer(s)) and configuring vertex attributes
	// ------------------------------------------------------------------------
	// these are our vertices for a basic rectangle
	float first_triangle[] = {
		// first triangle
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};
	float second_triangle[] = {
		// second triangle
		 0.7f, 0.4f, 0.0f,
		 0.95f, 0.4f, 0.0f,
		 0.8f, 0.8f, 0.0f
	};

	// VAO, VBO, AND EBO bullshits.
	unsigned int VAOs[2], VBOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	
	// bind and setup the first set of vaos and vbos
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(first_triangle), first_triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// second set of VAOs and VBOs
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(second_triangle), second_triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// drawing a triangle
		glUseProgram(shaderProgramOrange);
		glBindVertexArray(VAOs[0]);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// optional. deallocating resources
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shaderProgramYellow);
	glDeleteProgram(shaderProgramOrange);

	glfwTerminate(); // automatically frees up our memory
	window = nullptr;
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}