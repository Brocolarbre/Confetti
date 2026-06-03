#include "Confetti/ParticleSpawner/AttributeGenerator/Velocity/NormalVelocityGenerator.hpp"

namespace cft
{
	Velocity NormalVelocityGenerator::generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const
	{
		return context.position + context.normal * m_strength;
	}

	NormalVelocityGenerator::NormalVelocityGenerator(float strength) :
		m_strength(strength)
	{

	}

	std::unique_ptr<AttributeGenerator<Velocity>> NormalVelocityGenerator::clone() const
	{
		return std::make_unique<NormalVelocityGenerator>(*this);
	}
}