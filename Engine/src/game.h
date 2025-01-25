#pragma once
#include "Camera.h"
#include "renderer.h"
#include "window.h"

namespace BV
{
    class game;
}

class BV::game
{
public:
    game();
    ~game();
    void update_model();
    void draw_frame();

    window Window;
    renderer Renderer;
    Camera camera;
private:
    

    // mouse bullshits
    bool firstMouse = true;
    float lastMouseX = 0.0f, lastMouseY = 0.0f;

    // deltatime bullshits
    float deltaTime = 0.0f; // time between cur frame and last frame
    float lastFrame = 0.0f; // time of last frame

protected:

    void processInput(const BV::window& window);
};
