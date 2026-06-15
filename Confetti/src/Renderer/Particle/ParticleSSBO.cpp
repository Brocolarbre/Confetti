#include "Confetti/Renderer/Particle/ParticleSSBO.hpp"

#include <glad/glad.h>

namespace cft
{
	void ParticleSSBO::resize(unsigned int capacity)
	{
		m_capacity = capacity;

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBufferData(GL_SHADER_STORAGE_BUFFER, m_capacity * sizeof(ParticleData), nullptr, GL_DYNAMIC_DRAW);
	}

	ParticleSSBO::ParticleSSBO() :
		m_id(0),
		m_capacity(0),
		m_particleCount(0)
	{
		glGenBuffers(1, &m_id);
	}

	ParticleSSBO::~ParticleSSBO()
	{
		if (m_id != 0)
			glDeleteBuffers(1, &m_id);
	}

	unsigned int ParticleSSBO::getParticleCount() const
	{
		return m_particleCount;
	}

	void ParticleSSBO::bind() const
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_id);
	}

	void ParticleSSBO::setData(const std::unordered_map<unsigned int, ParticlePool>& particlePools, const std::unordered_map<unsigned int, unsigned int>& imageTextureIdMapping, const std::unordered_map<unsigned int, unsigned int>& spriteSheetSpriteSheetIdMapping, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry)
	{
		std::vector<std::reference_wrapper<const cft::ParticlePool>> pools;
		pools.reserve(particlePools.size());

		for (const auto& [id, pool] : particlePools)
			pools.push_back(pool);

		m_particleCount = 0;
		for (const auto& pool : pools)
			m_particleCount += pool.get().getCount();

		if (m_capacity < m_particleCount)
			resize(m_particleCount);

		std::vector<ParticleData> particlesData;
		particlesData.reserve(m_particleCount);

		for (const auto& particlePool : pools)
		{
			const ParticlePool& pool = particlePool.get();
			unsigned int particleCount = pool.getCount();

			const std::vector<glm::vec4>& color = pool.getColor();
			const std::vector<glm::vec3>& position = pool.getPosition();
			const std::vector<glm::vec2>& scale = pool.getScale();
			const std::vector<float>& phase = pool.getPhase();
			const std::vector<unsigned int>& id = pool.getId();

			for (unsigned int i = 0; i < particleCount; ++i)
			{
				float spriteSheetId = -1.0f;
				float textureId = -1.0f;

				std::optional<unsigned int> spriteSheet = particleRegistry.getEntry(id[i]).spriteSheet;
				if (spriteSheet.has_value())
				{
					spriteSheetId = static_cast<float>(spriteSheetSpriteSheetIdMapping.at(spriteSheet.value()));
					unsigned int imageId = assetRegistry.getSpriteSheet(spriteSheet.value()).imageId;
					textureId = static_cast<float>(imageTextureIdMapping.at(imageId));
				}

				ParticleData particleData{ color[i], glm::vec4(position[i], phase[i]), glm::vec4(scale[i], spriteSheetId, textureId)};
				particlesData.push_back(particleData);
			}
		}

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, particlesData.size() * sizeof(ParticleData), particlesData.data());
	}
}