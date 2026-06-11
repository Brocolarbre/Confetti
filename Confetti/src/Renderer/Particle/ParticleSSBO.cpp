#include "Confetti/Renderer/Particle/ParticleSSBO.hpp"

#include <glad/glad.h>

namespace cft
{
	void SSBO::resize(unsigned int capacity)
	{
		m_capacity = capacity;

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBufferData(GL_SHADER_STORAGE_BUFFER, m_capacity * sizeof(ParticleData), nullptr, GL_DYNAMIC_DRAW);
	}

	SSBO::SSBO() :
		m_id(0),
		m_capacity()
	{
		glGenBuffers(1, &m_id);
	}

	SSBO::~SSBO()
	{
		glDeleteBuffers(1, &m_id);
	}

	void SSBO::bind() const
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_id);
	}

	void SSBO::setData(const std::vector<std::reference_wrapper<const ParticlePool>>& particlePools, unsigned int totalParticleCount, const std::unordered_map<unsigned int, unsigned int>& imageTextureIdMapping, const ParticleRegistry& particleRegistry)
	{
		if (m_capacity < totalParticleCount)
			resize(totalParticleCount);

		std::vector<ParticleData> particles;
		particles.reserve(totalParticleCount);

		for (const auto& particlePool : particlePools)
		{
			const ParticlePool& pool = particlePool.get();
			unsigned int particleCount = pool.getCount();

			const std::vector<glm::vec4>& color = pool.getColor();
			const std::vector<glm::vec3>& position = pool.getPosition();
			const std::vector<glm::vec2>& scale = pool.getScale();
			const std::vector<unsigned int>& id = pool.getId();

			for (unsigned int i = 0; i < particleCount; ++i)
			{
				std::optional<unsigned int> imageId = particleRegistry.getEntry(id[i]).image;
				float textureId = -1.0f;
				if (imageId.has_value())
					textureId = static_cast<float>(imageTextureIdMapping.at(imageId.value()));

				ParticleData particleData{ color[i], glm::vec4(position[i], 0.0f), glm::vec4(scale[i], textureId, 0.0f) };
				particles.push_back(particleData);
			}
		}

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, particles.size() * sizeof(ParticleData), particles.data());
	}
}