#pragma once

#include "Confetti/Export.hpp"
#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/Emission/AttributeGenerator/AttributeTypes.hpp"

namespace cft
{
	class CONFETTI_API NormalLinearVelocityGenerator : public Cloneable<NormalLinearVelocityGenerator, AttributeGenerator<LinearVelocity>>
	{
	private:
		float m_strength;

		LinearVelocity generateValue(unsigned int count, unsigned int index, const SpawnContext& context) override;

	public:
		NormalLinearVelocityGenerator(float strength);
	};
}