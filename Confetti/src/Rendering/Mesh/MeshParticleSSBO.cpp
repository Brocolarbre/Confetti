#include "Confetti/Rendering/Mesh/MeshParticleSSBO.hpp"

#include <glad/glad.h>
#include <cstring>

namespace cft
{
	void MeshParticleSSBO::resize(unsigned int capacity)
	{
		if (m_mappedData != nullptr)
		{
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
			m_mappedData = nullptr;
		}

		m_capacity = capacity;

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBufferStorage(GL_SHADER_STORAGE_BUFFER, m_capacity * sizeof(ParticleData), nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);

		m_mappedData = static_cast<ParticleData*>(glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, m_capacity * sizeof(ParticleData), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_FLUSH_EXPLICIT_BIT));
	}

	MeshParticleSSBO::MeshParticleSSBO() :
		m_id(0),
		m_capacity(0),
		m_mappedData(nullptr)
	{
		glGenBuffers(1, &m_id);
	}

	MeshParticleSSBO::~MeshParticleSSBO()
	{
		if (m_mappedData != nullptr)
		{
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
		}

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
			resize(std::max(particleCount, std::max(1u, m_capacity * 2)));

		if (particleCount == 0)
			return;

		std::memcpy(m_mappedData, data.data(), data.size() * sizeof(ParticleData));

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glFlushMappedBufferRange(GL_SHADER_STORAGE_BUFFER, 0, data.size() * sizeof(ParticleData));
	}
}