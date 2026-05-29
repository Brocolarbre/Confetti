#include "Confetti/ParticleEmitterBehavior/RandomParticleEmitterBehavior.hpp"

namespace cft
{
	std::unique_ptr<ParticleEmitterBehavior> RandomParticleEmitterBehavior::clone() const
	{
		return std::make_unique<RandomParticleEmitterBehavior>(*this);
	}
}