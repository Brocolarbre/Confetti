#pragma once

#include "Confetti/Particle/Particle.hpp"

#include <memory>

namespace cft
{
	class ParticleBehavior
	{
	public:
		virtual ~ParticleBehavior() = default;

		virtual std::unique_ptr<ParticleBehavior> clone() const = 0;
		virtual void evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle) = 0;
	};

	template <typename Derived>
	class CloneableParticleBehavior : public ParticleBehavior
	{
	public:
		std::unique_ptr<ParticleBehavior> clone() const override;
	};

	template<typename Derived>
	inline std::unique_ptr<ParticleBehavior> CloneableParticleBehavior<Derived>::clone() const
	{
		return std::make_unique<Derived>(static_cast<const Derived&>(*this));
	}
}