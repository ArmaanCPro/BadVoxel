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

	// for debug purposes, until all GLFW window functions can be abstracted
	GLFWwindow* getGLFWwindow() const { return m_window; }

	bool isKeyPressed(int keycode) { return glfwGetKey(m_window, keycode) == GLFW_PRESS; }

	// add callbacks for keyboard events
	void AddKeyEvent(std::function<void(int, int, int, int)> callback) { m_key_callbacks.push_back(callback); }
	const std::vector<std::function<void(int, int, int, int)>>& GetKeyCallbacks() const { return m_key_callbacks; }
	//bool isKeyDown(int keycode) { return key_states[keycode] == true; } 
	
	// add callbacks for mouse events
	void AddMouseEvent(std::function<void(float, float)> callback) { m_mouse_callbacks.push_back(std::move(callback)); }
	const std::vector<std::function<void(float, float)>>& GetMouseCallbacks() const { return m_mouse_callbacks; }
	
	float last_mouseX = 0.0f;
	float last_mouseY = 0.0f;
	float mouseX = 0.0f;
	float mouseY = 0.0f;
	
	void setScrollOffset(float yoffset) { m_scroll_offset_y = yoffset; }
	float getScrollOffset() const { return m_scroll_offset_y; }

	
	std::unordered_map<int, bool> key_states;
	
private:
	GLFWwindow* m_window = nullptr;

	std::vector<std::function<void(float, float)>> m_mouse_callbacks;
	/* @params
	 * key - the GLFW keycode
	 * scancode - the os mapped hardware code
	 * action - the type of action, i.e. GLFW_PRESS
	 * mods - i.e. GLFW_MOD_SHIFT
	 */
	std::vector<std::function<void(int key, int scancode, int action, int mods)>> m_key_callbacks;
	// tracks keys being pressed or released
	
	float m_scroll_offset_y = 0.0f;
};