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

int main()
{
	BV::game Game;

	while (!glfwWindowShouldClose(Game.Window.getGLFWwindow()))
	{
		Game.update_model();

		Game.draw_frame();
	}
	return 0;
}