#include "game.h"

// screen settings
constexpr unsigned int SCREEN_WIDTH = 800;
constexpr unsigned int SCREEN_HEIGHT = 600;

BV::game::game()
    :
    Window(SCREEN_WIDTH, SCREEN_HEIGHT),
    camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
    
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

    Renderer.add_cube(glm::vec3{0.0f, 0.0f, -10.0f});
    Renderer.add_cube(glm::vec3{0.0f, 5.0f, -10.0f});

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Renderer.add_cube(glm::vec3{i * 3, 0.0f, j});
        }
    }
}

BV::game::~game()
{
    Renderer.reset();
}

void BV::game::update_model()
{
    // delta time bullshits
    float currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    // input
    processInput(Window);
}

void BV::game::draw_frame()
{
    // rendering commands here
    auto scrDims = Window.getWindowDimensions();
    Renderer.draw_vertices(camera, (float)scrDims.first, (float)scrDims.second, false);
		
    // check and call events and swap the buffers
    glfwSwapBuffers(Window.getGLFWwindow());
    glfwPollEvents();
}


void BV::game::processInput(const BV::window& windowIn)
{
    if (windowIn.isKeyPressed(GLFW_KEY_ESCAPE) == true)
        glfwSetWindowShouldClose(windowIn.getGLFWwindow(), true);

    if (windowIn.isKeyPressed(GLFW_KEY_W) == true)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (windowIn.isKeyPressed(GLFW_KEY_S) == true)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (windowIn.isKeyPressed(GLFW_KEY_A) == true)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (windowIn.isKeyPressed(GLFW_KEY_D) == true)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (windowIn.isKeyPressed(GLFW_KEY_SPACE) == true)
        camera.ProcessKeyboard(UP, deltaTime);
    if (windowIn.isKeyPressed(GLFW_KEY_LEFT_CONTROL) == true)
        camera.ProcessKeyboard(DOWN, deltaTime);
}
