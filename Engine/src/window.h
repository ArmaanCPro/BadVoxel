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
	window(int scr_width, int scr_height);
	~window();
	window(const window&) = delete;
	window& operator=(const window&) = delete;

	// for debug purposes, until all needed GLFW window functions can be abstracted
	GLFWwindow* getGLFWwindow() const { return m_window; }

	// returns if a key is pressed. should be used for input processing.
	bool isKeyPressed(int keycode) const { return glfwGetKey(m_window, keycode) == GLFW_PRESS; }
	// width, height
	std::pair<int, int> getWindowDimensions() { std::pair<int, int> dims; glfwGetWindowSize(m_window, &dims.first, &dims.second); return dims; }
	
	// add callbacks for mouse events. we don't have these for keyboard events because keyboard steps, mouse doesn't step. mouse isn't analogue like a keyboard.
	void AddMouseEvent(std::function<void(float, float)> callback) { m_mouse_callbacks.push_back(std::move(callback)); }
	// helper function to get all the callbacks for when the mouse moves.
	const std::vector<std::function<void(float, float)>>& GetMouseCallbacks() const { return m_mouse_callbacks; }

	// get the scroll offset from the last frame. useful for reading mouse scrolling.
	void setScrollOffset(float yoffset) { m_scroll_offset_y = yoffset; }
	float getScrollOffset() const { return m_scroll_offset_y; }
	
private:
	// the actual GLFW window.
	GLFWwindow* m_window = nullptr;

	// array of callbacks that are executed when GLFW registers a mouse event.
	std::vector<std::function<void(float, float)>> m_mouse_callbacks;
	/* @params
	 * key - the GLFW keycode
	 * scancode - the os mapped hardware code
	 * action - the type of action, i.e. GLFW_PRESS
	 * mods - i.e. GLFW_MOD_SHIFT
	 */
	std::vector<std::function<void(int key, int scancode, int action, int mods)>> m_key_callbacks;
	
	float m_scroll_offset_y = 0.0f;
};