#pragma once

#include "MeshParticleBatch.hpp"
#include "Confetti/Simulation/Pool/ParticlePool.hpp"
#include "Confetti/Simulation/Registry/AssetRegistry.hpp"
#include "Confetti/Simulation/Registry/ParticleRegistry.hpp"

namespace cft
{
	class CONFETTI_API MeshParticleSSBO
	{
	public:
		struct ParticleData
		{
			glm::mat4 modelMatrix;
			glm::vec4 color;
		};

	private:
		unsigned int m_id;
		unsigned int m_capacity;

		ParticleData* m_mappedData;

		void resize(unsigned int capacity);

	public:
		MeshParticleSSBO();
		~MeshParticleSSBO();

		void bind() const;
		void setData(const std::vector<MeshParticleSSBO::ParticleData>& data);
	};
}