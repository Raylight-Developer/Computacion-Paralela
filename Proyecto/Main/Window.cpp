#include "Window.hpp"


Renderer::Renderer(
	const vec1& SPHERE_RADIUS,
	const vec1& SPHERE_DISPLAY_RADIUS,
	const uvec2& GRID_SIZE,
	const vec1& ITERATIONS,
	const vec1& RENDER_SCALE,
	const bool& OPENMP
) :
	SPHERE_RADIUS(SPHERE_RADIUS),
	SPHERE_DISPLAY_RADIUS(SPHERE_DISPLAY_RADIUS),
	GRID_SIZE(GRID_SIZE),
	ITERATIONS(ITERATIONS),
	RENDER_SCALE(RENDER_SCALE),
	OPENMP(OPENMP)
{
	window = nullptr;

	camera_transform = Transform(dvec3(0, 0, 5.5));

	frame_counter = 0;
	frame_count = 0;
	runframe = 0;

	display_resolution = uvec2(3840U, 2160U);
	display_aspect_ratio = u_to_d(display_resolution.x) / u_to_d(display_resolution.y);

	render_resolution = d_to_u(u_to_d(display_resolution) * f_to_d(RENDER_SCALE));
	render_aspect_ratio = u_to_d(render_resolution.x) / u_to_d(render_resolution.y);

	recompile = false;
	reset = false;
	debug = false;

	camera_move_sensitivity = 1.5;
	camera_view_sensitivity = 2.5;
	keys = vector(348, false);
	current_mouse = dvec2(display_resolution) / 2.0;
	last_mouse = dvec2(display_resolution) / 2.0;

	current_time = 0.0;
	window_time = 0.0;
	frame_time = FPS_60;
	last_time = 0.0;

	view_layer = 0;
}

Renderer::~Renderer() {
	delete window;
}

void Renderer::init() {
	initGlfw();
	initImGui();
	systemInfo();

	f_pipeline();
	displayLoop();
}

void Renderer::quit() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(0);
}

void Renderer::initGlfw() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	display_resolution = uvec2(mode->width, mode->height);
	display_aspect_ratio = u_to_d(display_resolution.x) / u_to_d(display_resolution.y);
	last_mouse = glm::dvec2(display_resolution) / 2.0;

	window = glfwCreateWindow(display_resolution.x, display_resolution.y, "Proyect", NULL, NULL);

	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(false); // V-Sync
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSetWindowUserPointer(window, this);

	glfwSetFramebufferSizeCallback(window, framebufferSize);
	glfwSetMouseButtonCallback(window, mouseButton);
	glfwSetCursorPosCallback(window, cursorPos);
	glfwSetScrollCallback(window, scroll);
	glfwSetKeyCallback(window, key);
}

void Renderer::initImGui() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.FontGlobalScale = 1.75f;
	io.IniFilename = nullptr;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void Renderer::systemInfo() {
	GLint work_grp_cnt[3];
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_cnt[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_cnt[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_cnt[2]);
	LOG << "Max work groups per compute shader" <<
		" x:" << work_grp_cnt[0] <<
		" y:" << work_grp_cnt[1] <<
		" z:" << work_grp_cnt[2];

	GLint work_grp_size[3];
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);
	LOG ENDL << "Max work group sizes" <<
		" x:" << work_grp_size[0] <<
		" y:" << work_grp_size[1] <<
		" z:" << work_grp_size[2];

	GLint work_grp_inv;
	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_grp_inv);
	LOG ENDL << "Max invocations count per work group: " << work_grp_inv;

	GLint uboMaxSize;
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE , &uboMaxSize);
	LOG ENDL << "Maximum UBO size: " << d_to_ul(round(i_to_d(uboMaxSize) / (1024.0 * 1024.0))) << " Mb";

	GLint ssboMaxSize;
	glGetIntegerv(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, &ssboMaxSize);
	LOG ENDL << "Maximum SSBO size per binding: " << d_to_ul(round(i_to_d(ssboMaxSize) / (1024.0 * 1024.0))) << " Mb";

	GLint maxSSBOBindings;
	glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &maxSSBOBindings);
	LOG ENDL << "Maximum SSBO bindings: " << maxSSBOBindings;

	GLint uniformBufferOffsetAlignment;
	glGetIntegerv(GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT, &uniformBufferOffsetAlignment);
	LOG ENDL << "SSBO struct alignment multiplier: " << uniformBufferOffsetAlignment;
	LOG ENDL;
	FLUSH;
}

void Renderer::f_pipeline() {
	glViewport(0, 0, display_resolution.x , display_resolution.y);
	
	const GLfloat vertices[16] = {
		-1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
	};
	const GLuint indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	// Display Quad
	GLuint VAO, VBO, EBO;
	glCreateVertexArrays(1, &VAO);
	glCreateBuffers(1, &VBO);
	glCreateBuffers(1, &EBO);

	glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glNamedBufferData(EBO, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexArrayAttrib (VAO, 0);
	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribFormat (VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);

	glEnableVertexArrayAttrib (VAO, 1);
	glVertexArrayAttribBinding(VAO, 1, 0);
	glVertexArrayAttribFormat (VAO, 1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat));

	glVertexArrayVertexBuffer (VAO, 0, VBO, 0, 4 * sizeof(GLfloat));
	glVertexArrayElementBuffer(VAO, EBO);

	buffers["compute"] = computeShaderProgram("Render");
	buffers["display"] = fragmentShaderProgram("Display");


	// Compute Output
	buffers["raw"] = renderLayer(render_resolution);

	glBindVertexArray(VAO);
	point_cloud = vector(4 * GRID_SIZE.x * GRID_SIZE.y, Particle());
}

void Renderer::f_tickUpdate() {
	glDeleteBuffers(1, &buffers["ssbo"]);

	generatePattern(point_cloud, GRID_SIZE, SPHERE_RADIUS, ITERATIONS, d_to_f(current_time), OPENMP);
	buffers["ssbo"] = ssboBinding(1, ul_to_u(point_cloud.size() * sizeof(Particle)), point_cloud.data());
}

void Renderer::guiLoop() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::Begin("Info");
	ImGui::Text(("Frame Delta: " + to_string(frame_time) + "ms").c_str());
	if (OPENMP)
		ImGui::Text(("OpenMp Delta: " + to_string(sim_delta) + "ms").c_str());
	else
		ImGui::Text(("NON-OpenMp Delta: " + to_string(sim_delta) + "ms").c_str());
	ImGui::Text((to_string(frame_count) + "fps").c_str());
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::gameLoop() {
	if (keys[GLFW_KEY_D]) {
		camera_transform.moveLocal(dvec3(1.0, 0.0, 0.0)* camera_move_sensitivity * frame_time);
		reset = true;
		runframe = 0;
	}
	if (keys[GLFW_KEY_A]) {
		camera_transform.moveLocal(dvec3(-1.0, 0.0, 0.0)* camera_move_sensitivity * frame_time);
		reset = true;
		runframe = 0;
	}
	if (keys[GLFW_KEY_E] || keys[GLFW_KEY_SPACE]) {
		camera_transform.moveLocal(dvec3(0.0, 1.0, 0.0)* camera_move_sensitivity * frame_time);
		reset = true;
		runframe = 0;
	}
	if (keys[GLFW_KEY_Q] || keys[GLFW_KEY_LEFT_CONTROL]) {
		camera_transform.moveLocal(dvec3(0.0, -1.0, 0.0)* camera_move_sensitivity * frame_time);
		reset = true;
		runframe = 0;
	}
	if (keys[GLFW_KEY_W]) {
		camera_transform.moveLocal(dvec3(0.0, 0.0, -1.0)* camera_move_sensitivity * frame_time);
		reset = true;
		runframe = 0;
	}
	if (keys[GLFW_KEY_S]) {
		camera_transform.moveLocal(dvec3(0.0, 0.0, 1.0)* camera_move_sensitivity * frame_time);
		reset = true;
		runframe = 0;
	}
	if (keys[GLFW_MOUSE_BUTTON_RIGHT]) {
		const dvec1 xoffset = (last_mouse.x - current_mouse.x) * frame_time * camera_view_sensitivity;
		const dvec1 yoffset = (last_mouse.y - current_mouse.y) * frame_time * camera_view_sensitivity;

		camera_transform.rotate(dvec3(yoffset, xoffset, 0.0));
		reset = true;
		runframe = 0;

		last_mouse = current_mouse;
	}
}

void Renderer::displayLoop() {
	const uvec3 compute_layout = uvec3(
		d_to_u(ceil(u_to_d(render_resolution.x) / 32.0)),
		d_to_u(ceil(u_to_d(render_resolution.y) / 32.0)),
		1
	);

	while (!glfwWindowShouldClose(window)) {
		current_time = glfwGetTime();
		frame_time = current_time - last_time;
		last_time = current_time;
		window_time += frame_time;

		gameLoop();
		const mat4 matrix = d_to_f(glm::yawPitchRoll(camera_transform.euler_rotation.y * DEG_RAD, camera_transform.euler_rotation.x * DEG_RAD, camera_transform.euler_rotation.z * DEG_RAD));
		const vec3 y_vector = matrix[1];
		const vec3 z_vector = -matrix[2];

		const vec1 focal_length = 0.05f;
		const vec1 sensor_size  = 0.036f;

		const vec3 projection_center = d_to_f(camera_transform.position) + focal_length * z_vector;
		const vec3 projection_u = normalize(cross(z_vector, y_vector)) * sensor_size;
		const vec3 projection_v = normalize(cross(projection_u, z_vector)) * sensor_size;

		const dvec1 current_omp_time = glfwGetTime();
		f_tickUpdate();
		sim_delta = glfwGetTime() - current_omp_time;

		GLuint compute_program = buffers["compute"];

		glUseProgram(compute_program);
		glUniform1ui(glGetUniformLocation(compute_program, "frame_count"), ul_to_u(runframe));
		glUniform1f (glGetUniformLocation(compute_program, "aspect_ratio"), d_to_f(render_aspect_ratio));
		glUniform1f (glGetUniformLocation(compute_program, "current_time"), d_to_f(current_time));
		glUniform2ui(glGetUniformLocation(compute_program, "resolution"), render_resolution.x, render_resolution.y);
		glUniform1ui(glGetUniformLocation(compute_program, "reset"), static_cast<GLuint>(reset));
		glUniform1ui(glGetUniformLocation(compute_program, "debug"), static_cast<GLuint>(debug));

		glUniform3fv(glGetUniformLocation(compute_program, "camera_pos"),  1, value_ptr(d_to_f(camera_transform.position)));
		glUniform3fv(glGetUniformLocation(compute_program, "camera_p_uv"), 1, value_ptr(projection_center));
		glUniform3fv(glGetUniformLocation(compute_program, "camera_p_u"),  1, value_ptr(projection_u));
		glUniform3fv(glGetUniformLocation(compute_program, "camera_p_v"),  1, value_ptr(projection_v));

		glUniform2i(glGetUniformLocation(compute_program, "grid_size"), GRID_SIZE.x, GRID_SIZE.y);
		glUniform1f(glGetUniformLocation(compute_program, "sphere_radius"), SPHERE_RADIUS);
		glUniform1f(glGetUniformLocation(compute_program, "sphere_display_radius"), SPHERE_DISPLAY_RADIUS);

		glBindImageTexture(0, buffers["raw"], 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

		glDispatchCompute(compute_layout.x, compute_layout.y, compute_layout.z);
		
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		GLuint display_program = buffers["display"];

		glUseProgram(display_program);
		glClear(GL_COLOR_BUFFER_BIT);
		glUniform1f (glGetUniformLocation(display_program, "display_aspect_ratio"), d_to_f(display_aspect_ratio));
		glUniform1f (glGetUniformLocation(display_program, "render_aspect_ratio") , d_to_f(render_aspect_ratio));
		glUniform1ui(glGetUniformLocation(display_program, "view_layer"), view_layer);
		glUniform1ui(glGetUniformLocation(display_program, "debug"), static_cast<GLuint>(debug));
		bindRenderLayer(display_program, 0, buffers["raw"], "raw_render_layer");
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		frame_counter++;
		runframe++;
		if (reset) reset = false;
		if (recompile) {
			compute_program = computeShaderProgram("Render");
			display_program = fragmentShaderProgram("Post");
			recompile = false;
		}

		if (window_time > 1.0) {
			frame_count = frame_counter;
			window_time -= 1.0;
			frame_counter = 0;
		}

		guiLoop();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Renderer::resize() {
	display_aspect_ratio = u_to_d(display_resolution.x) / u_to_d(display_resolution.y);


	point_cloud = vector(4 * GRID_SIZE.x * GRID_SIZE.y, Particle());

	current_mouse = dvec2(display_resolution) / 2.0;
	last_mouse = current_mouse;
	runframe = 0;
}

void Renderer::framebufferSize(GLFWwindow* window, int width, int height) {
	Renderer* instance = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
	glViewport(0, 0, width, height);
	instance->display_resolution.x = width;
	instance->display_resolution.y = height;
	instance->resize();
}

void Renderer::cursorPos(GLFWwindow* window, double xpos, double ypos) {
	Renderer* instance = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
	instance->current_mouse = dvec2(xpos, ypos);
}

void Renderer::mouseButton(GLFWwindow* window, int button, int action, int mods) {
	Renderer* instance = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
	if (action == GLFW_PRESS) {
		instance->keys[button] = true;
		if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			instance->last_mouse = dvec2(xpos, ypos);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
	else if (action == GLFW_RELEASE) {
		instance->keys[button] = false;
		if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			instance->last_mouse = dvec2(xpos, ypos);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
}

void Renderer::scroll(GLFWwindow* window, double xoffset, double yoffset) {
	Renderer* instance = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
	if (yoffset < 0) {
		instance->reset = true;
		instance->runframe = 0;
		instance->camera_move_sensitivity /= 1.05;
	}
	if (yoffset > 0) {
		instance->reset = true;
		instance->runframe = 0;
		instance->camera_move_sensitivity *= 1.05;
	}
}

void Renderer::key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Renderer* instance = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
	// Input Handling
	if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
		instance->recompile = true;
	}
	if (key == GLFW_KEY_V  && action == GLFW_PRESS) {
		instance->debug = !instance->debug;
	}
	if (key == GLFW_KEY_RIGHT  && action == GLFW_PRESS) {
		if (instance->view_layer < 3)
			instance->view_layer++;
		else
			instance->view_layer = 0;
	}
	if (key == GLFW_KEY_LEFT  && action == GLFW_PRESS) {
		if (instance->view_layer > 0)
			instance->view_layer--;
		else
			instance->view_layer = 3;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		instance->reset = true;
		instance->runframe = 0;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (action == GLFW_PRESS) {
		instance->keys[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		instance->keys[key] = false;
	}
}