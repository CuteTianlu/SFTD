#pragma once

#include <thread>
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <vector>
#include <string>
#include <iostream>

struct Offsetxyz {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float radx = 0.0f;
	float rady = 0.0f;
	float radz = 0.0f;
	float cenradx = 0.0f;
	float cenrady = 0.0f;
	float cenradz = 0.0f;
};

struct Color {
	float R = 0.0f;
	float G = 0.0f;
	float B = 0.0f;
	float A = 0.0f;
};

struct rerin {
	GLuint vao;
	GLuint ebo;
	GLuint vbo;
	GLuint shaderProgram;
	Offsetxyz offset;
	Color color;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
};

class rering {
public:
	rering();
	~rering();

public:
	void Shader();
	void initrer();
	void rendering(std::vector<float> vertices, std::vector<unsigned int> indices, float xr, float yr, float zr, Color color);

public:
	rerin rer;

};