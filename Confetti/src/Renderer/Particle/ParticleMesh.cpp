#include "Confetti/Renderer/Particle/ParticleMesh.hpp"

#include <glad/glad.h>

namespace cft
{
	ParticleMesh::ParticleMesh() :
		m_vao(0),
		m_vbo(0)
	{
		float vertexData[] = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, 1.0f, 0.0f,
			-0.5f, 0.5f, 0.0f, 1.0f,
			0.5f, 0.5f, 1.0f, 1.0f
		};

		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertexData, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<const void*>(0));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<const void*>(2 * sizeof(float)));

		glBindVertexArray(0);
	}

	ParticleMesh::~ParticleMesh()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
	}

	void ParticleMesh::draw() const
	{
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	void ParticleMesh::drawInstanced(unsigned int instanceCount) const
	{
		glBindVertexArray(m_vao);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, instanceCount);
	}
}