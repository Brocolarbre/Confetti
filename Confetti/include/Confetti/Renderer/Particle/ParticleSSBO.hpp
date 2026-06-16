#pragma once

#include "Confetti/ParticleSimulation/ParticlePool.hpp"
#include "Confetti/ParticleSimulation/AssetRegistry.hpp"
#include "Confetti/ParticleSimulation/ParticleRegistry.hpp"

namespace cft
{
	class ParticleSSBO
	{
	private:
		unsigned int m_id;
		unsigned int m_capacity;
		unsigned int m_particleCount;

		struct ParticleData
		{
			glm::vec4 color;
			glm::vec4 positionPhase;
			glm::vec4 sizeSpriteSheetIdTextureId;
			glm::vec4 rotation;
		};

		void resize(unsigned int capacity);

	public:
		ParticleSSBO();
		~ParticleSSBO();

		unsigned int getParticleCount() const;

		void bind() const;
		void setData(const std::unordered_map<unsigned int, ParticlePool>& particlePools, const std::unordered_map<unsigned int, unsigned int>& imageTextureIdMapping, const std::unordered_map<unsigned int, unsigned int>& spriteSheetSpriteSheetIdMapping, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry);
	};
}