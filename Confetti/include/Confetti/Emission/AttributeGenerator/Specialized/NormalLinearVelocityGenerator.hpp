#pragma once

#include "Confetti/Export.hpp"
#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/Emission/AttributeGenerator/AttributeTypes.hpp"

namespace cft
{
	class CONFETTI_API NormalLinearVelocityGenerator : public AttributeGenerator<LinearVelocity>
	{
	private:
		float m_strength;

		LinearVelocity generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const override;

	public:
		NormalLinearVelocityGenerator(float strength);

		std::unique_ptr<AttributeGenerator<LinearVelocity>> clone() const override;
	};
}