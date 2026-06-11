#include "../../h/Game/Rendering/Rendering.h"

rering::rering() {
}

rering::~rering() {
	if (rer.vao != 0) {
		glDeleteVertexArrays(1, &rer.vao);
	}
	if (rer.shaderProgram != 0) {
		glDeleteProgram(rer.shaderProgram);
	}
}

void rering::Shader() {
	std::string vertexShaderSource = R"(
		#version 330 core
		layout (location = 0) in vec3 position;
		layout (location = 1) in vec4 color;

		uniform vec3 uOffset;
		out vec4 vColor;

		void main() {
			vColor = color;
			gl_Position = vec4(position.x + uOffset.x, position.y + uOffset.y, position.z + uOffset.z, 1.0);
		}
	)";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char * vertexShaderSourceCStr = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSourceCStr, nullptr);
	glCompileShader(vertexShader);

	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "错误顶点着色器编译失败\n" << infoLog << std::endl;
		throw std::runtime_error("错误顶点着色器编译失败");
	}

	std::string fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;

		in vec4 vColor;
		uniform vec4 uColor;

		void main() {
			FragColor = vec4(vColor) * uColor;
		}
	)";

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char * fragmentShaderSourceCStr = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "错误片段着色器编译失败\n" << infoLog << std::endl;
		throw std::runtime_error("错误片段着色器编译失败");
	};

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cerr << "错误着色器程序链接失败: " << infoLog << std::endl;
		throw std::runtime_error("错误着色器程序链接失败");
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	rer.shaderProgram = shaderProgram;

}

void rering::initrer() {

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, rer.vertices.size() * sizeof(float), rer.vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, rer.indices.size() * sizeof(unsigned int), rer.indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, false, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);

	GLint uOffsetLoc = glGetUniformLocation(rer.shaderProgram, "uOffset");

	rer.vbo = vbo;
	rer.ebo = ebo;
	rer.vao = vao;
}

void rering::rendering(std::vector<float> vertices, std::vector<unsigned int> indices, float xr, float yr, float zr, Color color) {
	glUseProgram(rer.shaderProgram);
	glBindBuffer(GL_ARRAY_BUFFER, rer.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rer.ebo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
	glUniform4f(glGetUniformLocation(rer.shaderProgram, "uColor"), color.R, color.G, color.B, color.A);
	glUniform3f(glGetUniformLocation(rer.shaderProgram, "uOffset"), rer.offset.x, rer.offset.y, rer.offset.z);
	//glUniform3f(glGetUniformLocation(rer.shaderProgram, "uOffsetrad"), rer.offset.radx, rer.offset.rady, rer.offset.radz);
	//glUniform3f(glGetUniformLocation(rer.shaderProgram, "uOffsetcenrad"), rer.offset.cenradx, rer.offset.cenrady, rer.offset.cenradz);
	glBindVertexArray(rer.vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}