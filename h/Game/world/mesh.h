#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "VertexLayout.h"

class Game;

namespace TinL {
	class Mesh {
	public:
		Mesh(const VertexLayout& layout, const std::vector<float>& vertices, const std::vector<uint32_t> indices);
		Mesh(const VertexLayout& layout, const std::vector<float>& vertices);
		Mesh(const Mesh&) = delete;
		Mesh& operator =(const Mesh&) = delete;

		void Bind();
		void Draw();

		Game * game;
	private:
		VertexLayout m_VertexLayout;
		size_t m_VertexCout = 0;
		size_t m_indexCount = 0;
		GLuint m_VBO = 0;
		GLuint m_EBO = 0;
		GLuint m_VAO = 0;
	};

};