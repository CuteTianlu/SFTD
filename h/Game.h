#pragma once

#include <thread>
#include <string>
#include <iostream>
#include "Game/Rendering/Rendering.h"
#include "Game/Key.h"

#include <glfw/glfw3.h>

struct windowInfo {
	int width;
	int height;
	std::string title;
	int Renderingapi = 0;
};

class Game {
public:
	Game();
	~Game();
	int FPS = 16;
	int Renderingapi = 0;
	void Init();
	void draw();
	void drawOpenGL();
	void drawVulkan();
	void physics();
	void update();

	const static int Vulkanapi = 1;
	const static int OpenGLapi = 2;

public:
	GLFWwindow * window;
	rering reng;

	windowInfo w_info;

	int GetRenderingapi();
};