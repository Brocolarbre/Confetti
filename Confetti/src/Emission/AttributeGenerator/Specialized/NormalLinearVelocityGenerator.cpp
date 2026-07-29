#include "Confetti/Emission/AttributeGenerator/Specialized/NormalLinearVelocityGenerator.hpp"

namespace cft
{
	LinearVelocity NormalLinearVelocityGenerator::generateValue(unsigned int count, unsigned int index, const SpawnContext& context)
	{
		return context.position + context.normal * m_strength;
	}

	NormalLinearVelocityGenerator::NormalLinearVelocityGenerator(float strength) :
		m_strength(strength)
	{

	}
}