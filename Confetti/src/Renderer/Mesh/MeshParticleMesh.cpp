#include "Confetti/Renderer/Mesh/MeshParticleMesh.hpp"

#include <glad/glad.h>

namespace cft
{
	MeshParticleMesh::MeshParticleMesh() :
		m_vao(0),
		m_vbo(0),
		m_ebo(0),
		m_indexCount(0)
	{
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);
	}

	MeshParticleMesh::~MeshParticleMesh()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ebo);
	}

	void MeshParticleMesh::load(const std::vector<Vertex>& vertexData, const std::vector<unsigned int>& indexData)
	{
		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(Vertex), vertexData.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(unsigned int), indexData.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, position)));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, color)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, textureCoordinates)));

		glBindVertexArray(0);

		m_indexCount = static_cast<unsigned int>(indexData.size());
	}

	void MeshParticleMesh::draw() const
	{
		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
	}

	void MeshParticleMesh::drawInstanced(unsigned int count) const
	{
		glBindVertexArray(m_vao);
		glDrawElementsInstanced(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr, count);
	}

	void MeshParticleMesh::drawInstancedBaseInstance(unsigned int firstInstance, unsigned int instanceCount) const
	{
		glBindVertexArray(m_vao);
		glDrawElementsInstancedBaseInstance(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr, instanceCount, firstInstance);
	}
}