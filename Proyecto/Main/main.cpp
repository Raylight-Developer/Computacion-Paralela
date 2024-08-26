#pragma execution_character_set( "utf-8" )

#include "Include.hpp"

#include "Window.hpp"

int main(int argc, char* argv[]) {
	SetConsoleOutputCP(65001);

	vec1  sphereRadius = 0.015f;
	vec1  sphereDisplayRadius = sphereRadius;
	uvec2 gridSize = uvec2(270,150);
	vec1  iterations = 4.0f;
	vec1  renderScale = 0.25f;

	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "--voxel-size") == 0 && i + 1 < argc) {
			sphereRadius = str_to_f(argv[++i]);
		} else if (strcmp(argv[i], "--sphere-display-mult") == 0 && i + 1 < argc) {
			sphereDisplayRadius = sphereRadius * str_to_f(argv[++i]);
		} else if (strcmp(argv[i], "--grid-size") == 0 && i + 2 < argc) {
			uvec2 transposed = str_to_u(argv[++i], argv[++i]);
			gridSize = uvec2(transposed.y, transposed.x);
		} else if (strcmp(argv[i], "--iterations") == 0 && i + 1 < argc) {
			iterations = str_to_f(argv[++i]);
		} else if (strcmp(argv[i], "--render-scale") == 0 && i + 1 < argc) {
			renderScale = str_to_f(argv[++i]);
		} else {
			cerr << "Unknown or incomplete argument: " << argv[i] << endl;
		}
	}

	Renderer renderer(sphereRadius, sphereDisplayRadius, gridSize, iterations, renderScale);
	renderer.init();

	return 1;
}