#include "Confetti/ParticleEmitterBehavior/RandomParticleEmitterBehavior.hpp"

namespace cft
{
	std::unique_ptr<ParticleEmitterBehavior> RandomParticleEmitterBehavior::clone() const
	{
		return std::make_unique<RandomParticleEmitterBehavior>(*this);
	}

	void RandomParticleEmitterBehavior::update(float elapsedTime, float deltaTime, ParticleEmitterView& particleEmitter)
	{
		float radius = 10.0f;
		float progress = elapsedTime * 2.0f;
		particleEmitter.position = glm::vec3(glm::cos(progress), glm::sin(progress), 0.0f) * radius;
	}
}