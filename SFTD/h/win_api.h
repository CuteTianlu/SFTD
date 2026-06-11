#pragma once

#include <iostream>
#include <string>

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <glfw/glfw3.h>

#include <glad/glad.h>
#include "Game/Rendering/Rendering.h"
#include "Game.h"
#include <thread>

class Game;

struct windowInfo {
	int width;
	int height;
	std::string title;
	int Renderingapi = 0;
};

class win_OpVk {
public:
	win_OpVk();
	win_OpVk(std::string title);
	win_OpVk(windowInfo window_info);
	~win_OpVk();

public:
	void Rendering();
	void Update();
	void Physics();

public:
	bool Switch = true;
	Game * game;
	
private:
	void initwindow();

	void initRenderingapi();

	void initvulkan();
	void initOpenGL();

	void pickupPhysicalDevice();

private:
	void cleanupwindow();
	void cleanupAll();

private:
	windowInfo w_info;
	GLFWwindow * window;
	VkInstance instance;
	VkPhysicalDevice Device;

};