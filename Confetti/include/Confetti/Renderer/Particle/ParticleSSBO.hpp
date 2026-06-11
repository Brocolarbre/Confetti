#pragma once

#include "Confetti/ParticleSimulation/ParticlePool.hpp"
#include "Confetti/ParticleSimulation/ParticleRegistry.hpp"

namespace cft
{
	class SSBO
	{
	private:
		unsigned int m_id;
		unsigned int m_capacity;

		struct ParticleData
		{
			glm::vec4 color;
			glm::vec4 position;
			glm::vec4 size;
		};

		void resize(unsigned int capacity);

	public:
		SSBO();
		~SSBO();

		void bind() const;
		void setData(const std::vector<std::reference_wrapper<const ParticlePool>>& particlePools, unsigned int totalParticleCount, const std::unordered_map<unsigned int, unsigned int>& imageTextureIdMapping, const ParticleRegistry& particleRegistry);
	};
}