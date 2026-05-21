#include "ConfettiEngine/Renderer/Mesh.hpp"

#include <glad/glad.h>

namespace cft
{
	Mesh::Mesh() :
		m_vao(0),
		m_vbo(0)
	{
		float vertexData[] = {
			-0.5f, -0.5f,
			0.5f, -0.5f,
			-0.5f, 0.5f,
			0.5f, 0.5f
		};

		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertexData, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<const void*>(0));

		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
	}

	void Mesh::draw() const
	{
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	void Mesh::drawInstanced(unsigned int instanceCount) const
	{
		glBindVertexArray(m_vao);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, instanceCount);
	}
}