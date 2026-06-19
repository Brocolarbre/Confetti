#include "Confetti/Renderer/Mesh/MeshParticleSSBO.hpp"

#include <glad/glad.h>

namespace cft
{
	void MeshParticleSSBO::resize(unsigned int capacity)
	{
		m_capacity = capacity;

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBufferData(GL_SHADER_STORAGE_BUFFER, m_capacity * sizeof(ParticleData), nullptr, GL_DYNAMIC_DRAW);
	}

	MeshParticleSSBO::MeshParticleSSBO() :
		m_id(0),
		m_capacity(0)
	{
		glGenBuffers(1, &m_id);
	}

	MeshParticleSSBO::~MeshParticleSSBO()
	{
		if (m_id != 0)
			glDeleteBuffers(1, &m_id);
	}

	void MeshParticleSSBO::bind() const
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_id);
	}

	void MeshParticleSSBO::setData(const std::vector<MeshParticleSSBO::ParticleData>& data)
	{
		unsigned int particleCount = static_cast<unsigned int>(data.size());

		if (m_capacity < particleCount)
			resize(particleCount);

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, data.size() * sizeof(ParticleData), data.data());
	}
}