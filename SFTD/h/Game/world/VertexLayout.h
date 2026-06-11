#pragma once
#include <glfw/glfw3.h>
#include <vector>

namespace TinL {

	struct VertexElement {
		GLuint index;
		GLuint size;
		GLuint type;
		uint32_t offset;
	};

	struct VertexLayout {
		std::vector<VertexElement> elements;
		uint32_t stride = 0;
	};

};