#include "Confetti/Rendering/Billboard/BillboardParticleSSBO.hpp"

#include <glad/glad.h>

namespace cft
{
	void BillboardParticleSSBO::resize(unsigned int capacity)
	{
		if (m_mappedData != nullptr)
		{
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
			m_mappedData = nullptr;
		}

		if (m_id != 0)
			glDeleteBuffers(1, &m_id);

		glGenBuffers(1, &m_id);
		
		m_capacity = capacity;

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBufferStorage(GL_SHADER_STORAGE_BUFFER, m_capacity * sizeof(ParticleData), nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);

		m_mappedData = static_cast<ParticleData*>(glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, m_capacity * sizeof(ParticleData), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_FLUSH_EXPLICIT_BIT));
	}

	BillboardParticleSSBO::BillboardParticleSSBO() :
		m_id(0),
		m_capacity(0),
		m_particleCount(0),
		m_mappedData(nullptr)
	{

	}

	BillboardParticleSSBO::~BillboardParticleSSBO()
	{
		if (m_mappedData != nullptr)
		{
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
		}

		if (m_id != 0)
			glDeleteBuffers(1, &m_id);
	}

	unsigned int BillboardParticleSSBO::getParticleCount() const
	{
		return m_particleCount;
	}

	void BillboardParticleSSBO::ensureCapaticy(const std::unordered_map<unsigned int, ParticlePool>& particlePools, const ParticleRegistry& particleRegistry)
	{
		unsigned int particleCount = 0;

		for (const auto& [id, pool] : particlePools)
		{
			if (pool.getCount() == 0 || particleRegistry.getEntry(pool.getParticleRegistryId().front()).renderConfiguration.renderType != RenderType::Billboard)
				continue;

			particleCount += pool.getCount();
		}

		m_particleCount = particleCount;

		if (m_capacity < m_particleCount)
			resize(glm::max(m_particleCount, std::max(1u, m_capacity * 2)));
	}

	void BillboardParticleSSBO::bind() const
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_id);
	}

	void BillboardParticleSSBO::setData(const std::unordered_map<unsigned int, ParticlePool>& particlePools, const std::unordered_map<unsigned int, unsigned int>& imageIdToTextureIndex, const std::unordered_map<unsigned int, unsigned int>& spriteSheetIdToSpriteSheetSsboIndexMapping, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry)
	{
		if (m_particleCount == 0)
			return;

		ParticleData* output = m_mappedData;

		for (const auto& [id, pool] : particlePools)
		{
			unsigned int particleCount = pool.getCount();

			const std::vector<unsigned int>& particleRegistryId = pool.getParticleRegistryId();

			if (pool.getCount() == 0 || particleRegistry.getEntry(particleRegistryId.front()).renderConfiguration.renderType != RenderType::Billboard)
				continue;

			const std::vector<glm::vec4>& color = pool.getColor();
			const std::vector<glm::vec3>& position = pool.getPostBehaviorPosition();
			const std::vector<glm::quat>& rotation = pool.getRotation();
			const std::vector<glm::vec3>& scale = pool.getScale();
			const std::vector<float>& phase = pool.getPhase();
			
			for (unsigned int i = 0; i < particleCount; ++i)
			{
				float spriteSheetSsboIndex = -1.0f;
				float textureIndex = -1.0f;

				std::optional<unsigned int> spriteSheet = std::get<BillboardRenderConfiguration>(particleRegistry.getEntry(particleRegistryId[i]).renderConfiguration.configurationData).spriteSheetId;
				if (spriteSheet.has_value())
				{
					spriteSheetSsboIndex = static_cast<float>(spriteSheetIdToSpriteSheetSsboIndexMapping.at(spriteSheet.value()));
					unsigned int imageId = assetRegistry.getSpriteSheetDescriptor(spriteSheet.value()).imageId;
					textureIndex = static_cast<float>(imageIdToTextureIndex.at(imageId));
				}

				float angle = 2.0f * std::atan2(rotation[i].z, rotation[i].w);

				*output = ParticleData{ color[i], glm::vec4(position[i], phase[i]), glm::vec4(scale[i].x, scale[i].y, spriteSheetSsboIndex, textureIndex), glm::vec4(angle, 0.0f, 0.0f, 0.0f) };
				++output;
			}
		}

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glFlushMappedBufferRange(GL_SHADER_STORAGE_BUFFER, 0, m_particleCount * sizeof(ParticleData));
	}
}