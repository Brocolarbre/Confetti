#pragma once

#include "MeshParticleBatch.hpp"
#include "Confetti/ParticleSimulation/ParticlePool.hpp"
#include "Confetti/ParticleSimulation/AssetRegistry.hpp"
#include "Confetti/ParticleSimulation/ParticleRegistry.hpp"

namespace cft
{
	class MeshParticleSSBO
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

		void resize(unsigned int capacity);

	public:
		MeshParticleSSBO();
		~MeshParticleSSBO();

		void bind() const;
		void setData(const std::vector<MeshParticleSSBO::ParticleData>& data);
	};
}