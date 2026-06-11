#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "VertexLayout.h"

namespace TinL {
	class Mesh {
	public:
		Mesh(const VertexLayout& layout, const std::vector<float>& vertices, const std::vector<uitn32_t> indices) = delete;
		Mesh(const VertexLayout& layout, const std::vector<float>& vertices) = delete;
		Mesh(const Mesh&) = delete;
		Mesh& operator =(const Mesh&) = delete;

		void Bind();
		void Draw();
	private:
		VertexLayout m_VertexLayout;
		size_t m_VertexCout;
		size_t m_indexCount;
		GLuint m_VBO = 0;
		GLuint m_EBO = 0;
		GLuint m_VAO = 0;
	}

}