#pragma once

#include "Confetti/Particle/ParticlePool.hpp"

namespace cft
{
	class SSBO
	{
	private:
		unsigned int m_id;
		unsigned int m_capacity;

		struct Particle
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
		void setData(const std::vector<std::reference_wrapper<const ParticlePool>>& particlePools, unsigned int totalParticleCount);
	};
}