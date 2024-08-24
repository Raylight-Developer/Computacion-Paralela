#pragma execution_character_set( "utf-8" )

#include "Include.hpp"

#include "Window.hpp"

int main(int argc, char* argv[]) {
	SetConsoleOutputCP(65001);

	Renderer renderer = Renderer();
	renderer.init();

	return 0;
}