#pragma once

#include <functional>
#include <vector>
#include <GLFW/glfw3.h>

namespace BV
{
	class window;	
}

class BV::window
{
public:
	window(int scr_width = 600, int scr_height = 800);
	~window();
	window(const window&) = delete;
	window& operator=(const window&) = delete;

	GLFWwindow* getGLFWwindow() const { return m_window; }

	bool isKeyPressed(int keycode) { return glfwGetKey(m_window, keycode) == GLFW_PRESS; }

	// TODO: add callbacks for keyboard events

	// add callbacks for mouse events
	void AddMouseEvent(std::function<void(float, float)> callback) { m_mouse_callbacks.push_back(std::move(callback)); }
	std::vector<std::function<void(float, float)>> GetMouseCallbacks() { return m_mouse_callbacks; }
	
	float last_mouseX = 0.0f;
	float last_mouseY = 0.0f;
	float mouseX = 0.0f;
	float mouseY = 0.0f;
	
	void setScrollOffset(float yoffset) { scroll_offset_y = yoffset; }
	float getScrollOffset() const { return scroll_offset_y; }
	
private:
	GLFWwindow* m_window = nullptr;

	std::vector<std::function<void(float, float)>> m_mouse_callbacks;
	
	float scroll_offset_y = 0.0f;
};