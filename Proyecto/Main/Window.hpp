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

	vec1  SPHERE_RADIUS;
	vec1  SPHERE_DISPLAY_RADIUS;
	uvec2 GRID_SIZE;
	vec1  ITERATIONS;
	vec1  RENDER_SCALE;
	bool OPENMP;

	vector<Particle> point_cloud;

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

	dvec1 sim_delta;
	dvec1 current_time;
	dvec1 window_time;
	dvec1 frame_time;
	dvec1 last_time;

	uint view_layer;

	unordered_map<string, GLuint> buffers;

	Renderer(
		const vec1& SPHERE_RADIUS = 0.01f,
		const vec1& SPHERE_DISPLAY_RADIUS = 0.01 * 0.5f * 1.5f,
		const uvec2& GRID_SIZE = uvec2(192,108),
		const vec1& ITERATIONS = 4.0f,
		const vec1& RENDER_SCALE = 0.125,
		const bool& OPENMP = false
	);
	~Renderer();

	void init();
	void quit();

	void initGlfw();
	void initImGui();
	void systemInfo();

	void f_pipeline();
	void f_tickUpdate();

	void guiLoop();
	void gameLoop();
	void displayLoop();

	void resize();

	static void framebufferSize(GLFWwindow* window, int width, int height);
	static void cursorPos(GLFWwindow* window, dvec1 xpos, dvec1 ypos);
	static void mouseButton(GLFWwindow* window, int button, int action, int mods);
	static void scroll(GLFWwindow* window, dvec1 xoffset, dvec1 yoffset);
	static void key(GLFWwindow* window, int key, int scancode, int action, int mods);
};