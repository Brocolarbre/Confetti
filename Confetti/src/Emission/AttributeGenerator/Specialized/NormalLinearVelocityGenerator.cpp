#include "Confetti/Emission/AttributeGenerator/Specialized/NormalLinearVelocityGenerator.hpp"

namespace cft
{
	LinearVelocity NormalLinearVelocityGenerator::generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const
	{
		return context.position + context.normal * m_strength;
	}

	NormalLinearVelocityGenerator::NormalLinearVelocityGenerator(float strength) :
		m_strength(strength)
	{

	}

	std::unique_ptr<AttributeGenerator<LinearVelocity>> NormalLinearVelocityGenerator::clone() const
	{
		return std::make_unique<NormalLinearVelocityGenerator>(*this);
	}
}