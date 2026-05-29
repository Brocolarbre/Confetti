#include "Confetti/ParticleBehavior/RandomParticleBehavior.hpp"

namespace cft
{
	RandomParticleBehavior::RandomParticleBehavior(RandomNumberGenerator& randomNumberGenerator) :
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	std::unique_ptr<ParticleBehavior> RandomParticleBehavior::clone() const
	{
		return std::make_unique<RandomParticleBehavior>(*this);
	}

	void RandomParticleBehavior::update(float elapsedTime, float deltaTime, ParticleView& particle)
	{
		particle.position += m_randomNumberGenerator.generate(glm::vec3(-0.1f), glm::vec3(0.1f)) * deltaTime;
	}
}