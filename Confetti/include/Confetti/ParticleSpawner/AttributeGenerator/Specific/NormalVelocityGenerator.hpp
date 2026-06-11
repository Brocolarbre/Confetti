#pragma once

#include "Confetti/ParticleSpawner/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/ParticleSpawner/AttributeGenerator/AttributeTypes.hpp"

namespace cft
{
	class NormalVelocityGenerator : public AttributeGenerator<Velocity>
	{
	private:
		float m_strength;

		Velocity generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const override;

	public:
		NormalVelocityGenerator(float strength);

		std::unique_ptr<AttributeGenerator<Velocity>> clone() const override;
	};
}