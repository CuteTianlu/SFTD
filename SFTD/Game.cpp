#include "h/Game.h"

Game::Game() {

}

Game::~Game() {

}

int frame = 0;
int FPS = 16;//0.016秒 = 16毫秒 1 / 60 = 0.01666666秒

void Game::Init() {

}

void Game::drawOpenGL() {
	frame++;
	if (frame >= 60) {
		std::cout << "渲染主线程无问题\nOpenGL\n";
		frame = 0;
	}
	
	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 左下角
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 右下角
		0.5f,  0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f,  // 右上角
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f  // 左上角
	};
	std::vector<unsigned int> indices = {
	0, 1, 2,
	0, 2, 3
	};

	std::vector<float> vertices1 = {
		-0.9f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 左下角
		0.5f, -0.3f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 右下角
		0.3f,  0.5f, 0.0f, 0.8f, 1.0f, 0.5f, 1.0f,  // 右上角
		-0.8f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f  // 左上角
	};
	std::vector<unsigned int> indices1 = {
	0, 1, 2,
	0, 2, 3
	};

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	reng.rendering(vertices, indices, 0, 0, 0, { 1.0f,0.0f,1.0f,1.0f });
	reng.rendering(vertices1, indices1, 0, 0, 0, { 1.0f,0.0f,1.0f,1.0f });
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Game::drawVulkan() {
	frame++;
	if (frame >= 60) {
		std::cout << "渲染主线程无问题\nVulkan\n";
		frame = 0;
	}
}

void Game::draw() {
	if (Game::Renderingapi == Vulkanapi) {
		Game::drawVulkan();
	} else if (Game::Renderingapi == OpenGLapi) {
		Game::drawOpenGL();
	} else {
		Game::drawOpenGL();
	}
}

void Game::update() {
	frame++;
	if (frame >= 60) {
		std::cout << "更新无问题\n";
		frame = 0;
	}
	keyCallback(window);
	if (keW) {
		reng.rer.offset.y += 0.01f;
	}
	if (keA) {
		reng.rer.offset.x -= 0.01f;
	}
	if (keS) {
		reng.rer.offset.y -= 0.01f;
	}
	if (keD) {
		reng.rer.offset.x += 0.01f;
	}
}

void Game::physics() {
	frame++;
	if (frame >= 60) {
		std::cout << "物理无问题\n";
		frame = 0;
	}
}

int Game::GetRenderingapi() {
	return Game::Renderingapi;
}