#pragma once

#include "Shared.hpp"

#include "GLFW/glfw3.h"
#include "imgui-1.90/imgui.h"
#include "imgui-1.90/backends/imgui_impl_glfw.h"
#include "imgui-1.90/backends/imgui_impl_opengl3.h"

#include "OpenGL.hpp"
#include "Kernel.hpp"

struct Renderer {
	GLFWwindow* window;

	Transform camera_transform;

	dvec1 display_aspect_ratio;
	dvec1 render_aspect_ratio;
	uvec2 display_resolution;
	uvec2 render_resolution;

	uint   frame_counter;
	uint   frame_count;
	uint64 runframe;

	bool recompile;
	bool reset;
	bool debug;

	dvec1 camera_move_sensitivity;
	dvec1 camera_view_sensitivity;
	vector<bool> keys;

	dvec2 current_mouse;
	dvec2 last_mouse;

	dvec1 current_time;
	dvec1 window_time;
	dvec1 frame_time;
	dvec1 last_time;

	uint view_layer;

	Renderer();

	void init();
	void exit();

	void initGlfw();
	void initImGui();
	void systemInfo();

	void f_pipeline();
	void f_tickUpdate();

	void guiLoop();
	void gameLoop();
	void displayLoop();

	static void framebufferSize(GLFWwindow* window, int width, int height);
	static void cursorPos(GLFWwindow* window, dvec1 xpos, dvec1 ypos);
	static void mouseButton(GLFWwindow* window, int button, int action, int mods);
	static void scroll(GLFWwindow* window, dvec1 xoffset, dvec1 yoffset);
	static void key(GLFWwindow* window, int key, int scancode, int action, int mods);
};