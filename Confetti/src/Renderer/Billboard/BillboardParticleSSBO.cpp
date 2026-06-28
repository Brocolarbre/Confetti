#include "Confetti/Renderer/Billboard/BillboardParticleSSBO.hpp"

#include <glad/glad.h>

namespace cft
{
	void BillboardParticleSSBO::resize(unsigned int capacity)
	{
		m_capacity = capacity;

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBufferData(GL_SHADER_STORAGE_BUFFER, m_capacity * sizeof(ParticleData), nullptr, GL_DYNAMIC_DRAW);
	}

	BillboardParticleSSBO::BillboardParticleSSBO() :
		m_id(0),
		m_capacity(0),
		m_particleCount(0)
	{
		glGenBuffers(1, &m_id);
	}

	BillboardParticleSSBO::~BillboardParticleSSBO()
	{
		if (m_id != 0)
			glDeleteBuffers(1, &m_id);
	}

	unsigned int BillboardParticleSSBO::getParticleCount() const
	{
		return m_particleCount;
	}

	void BillboardParticleSSBO::bind() const
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_id);
	}

	void BillboardParticleSSBO::setData(const std::unordered_map<unsigned int, ParticlePool>& particlePools, const std::unordered_map<unsigned int, unsigned int>& imageTextureIdMapping, const std::unordered_map<unsigned int, unsigned int>& spriteSheetSpriteSheetIdMapping, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry)
	{
		std::vector<std::reference_wrapper<const cft::ParticlePool>> pools;
		pools.reserve(particlePools.size());

		for (const auto& [id, pool] : particlePools)
			pools.push_back(pool);

		m_particleCount = 0;

		std::vector<ParticleData> particlesData;

		for (const auto& particlePool : pools)
		{
			const ParticlePool& pool = particlePool.get();
			unsigned int particleCount = pool.getCount();

			const std::vector<glm::vec4>& color = pool.getColor();
			const std::vector<glm::vec3>& position = pool.getPosition();
			const std::vector<glm::quat>& rotation = pool.getRotation();
			const std::vector<glm::vec3>& scale = pool.getScale();
			const std::vector<float>& phase = pool.getPhase();
			const std::vector<unsigned int>& id = pool.getParticleRegistryId();

			if (particleCount == 0 || particleRegistry.getEntry(id.front()).renderDescriptor.renderType != RenderType::Billboard)
				continue;

			particlesData.reserve(particlesData.size() + id.size());

			for (unsigned int i = 0; i < particleCount; ++i)
			{
				float spriteSheetId = -1.0f;
				float textureId = -1.0f;

				std::optional<unsigned int> spriteSheet = std::get<BillboardRenderDescriptor>(particleRegistry.getEntry(id[i]).renderDescriptor.descriptorData).spriteSheetId;
				if (spriteSheet.has_value())
				{
					spriteSheetId = static_cast<float>(spriteSheetSpriteSheetIdMapping.at(spriteSheet.value()));
					unsigned int imageId = assetRegistry.getSpriteSheet(spriteSheet.value()).imageId;
					textureId = static_cast<float>(imageTextureIdMapping.at(imageId));
				}

				float angle = 2.0f * std::atan2(rotation[i].z, rotation[i].w);

				ParticleData particleData{ color[i], glm::vec4(position[i], phase[i]), glm::vec4(scale[i].x, scale[i].y, spriteSheetId, textureId), glm::vec4(angle, 0.0f, 0.0f, 0.0f) };
				particlesData.push_back(particleData);
			}

			m_particleCount += pool.getCount();
		}

		if (m_capacity < m_particleCount)
			resize(m_particleCount);

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, particlesData.size() * sizeof(ParticleData), particlesData.data());
	}
}