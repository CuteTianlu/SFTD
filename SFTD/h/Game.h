#pragma once

#include <thread>
#include <string>
#include <iostream>
#include "Game/Rendering/Rendering.h"
#include "Game/Key.h"

#include <glfw/glfw3.h>

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

	int GetRenderingapi();
};