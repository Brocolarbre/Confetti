#pragma once

#include "ParticleConnector.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class RandomParticleConnector : public Cloneable<RandomParticleConnector, ParticleConnector>
	{
	private:
		float m_maximumDistance;
		unsigned int m_connexionsCount;
		RandomNumberGenerator& m_randomNumberGenerator;

	public:
		RandomParticleConnector(float maximumDistance, unsigned int connexionsCount, RandomNumberGenerator& randomNumberGenerator);

		unsigned int createRibbons(RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime);
		void updateRibbon(RibbonView& ribbon, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle);
		bool isRibbonValid(const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const;
	};
}