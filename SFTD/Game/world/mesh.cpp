#include "../../h/Game/world/mesh.h"
#include "../../h/Game.h"

namespace TinL {

	Mesh::Mesh(const VertexLayout& layout, const std::vector<float>& vertices, const std::vector<uint32_t> indices) {

		auto& graphicsAPI = Game::GetRenderingapi();
	}
	Mesh::Mesh(const VertexLayout& layout, const std::vector<float>& vertices) {

	}

	void Mesh::Bind() {
		glBindVertexArray(m_VAO);
	}

	void Mesh::Draw() {
		if (m_indexCount > 0) {
			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, m_VertexCout);
		}
	}
}