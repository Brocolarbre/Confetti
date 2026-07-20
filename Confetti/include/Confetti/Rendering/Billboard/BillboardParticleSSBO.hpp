#pragma once

#include "Confetti/Simulation/Pool/ParticlePool.hpp"
#include "Confetti/Simulation/Registry/AssetRegistry.hpp"
#include "Confetti/Simulation/Registry/ParticleRegistry.hpp"

namespace cft
{
	class BillboardParticleSSBO
	{
	private:
		struct ParticleData
		{
			glm::vec4 color;
			glm::vec4 positionPhase;
			glm::vec4 sizeSpriteSheetIdTextureId;
			glm::vec4 rotation;
		};

	private:
		unsigned int m_id;
		unsigned int m_capacity;
		unsigned int m_particleCount;

		void resize(unsigned int capacity);

	public:
		BillboardParticleSSBO();
		~BillboardParticleSSBO();

		unsigned int getParticleCount() const;

		void bind() const;
		void setData(const std::unordered_map<unsigned int, ParticlePool>& particlePools, const std::unordered_map<unsigned int, unsigned int>& imageIdToTextureIndex, const std::unordered_map<unsigned int, unsigned int>& spriteSheetIdToSpriteSheetSsboIndexMapping, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry);
	};
}