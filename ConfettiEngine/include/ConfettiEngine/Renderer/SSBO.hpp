#pragma once

#include "ConfettiEngine/Particle/ParticleData.hpp"

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

	public:
		SSBO(unsigned int particleCount);
		~SSBO();

		void bind() const;
		void setData(const ParticleData& data) const;
	};
}