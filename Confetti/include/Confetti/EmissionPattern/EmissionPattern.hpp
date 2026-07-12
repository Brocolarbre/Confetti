#pragma once

#include <memory>

namespace cft
{
	class EmissionPattern
	{
	public:
		virtual ~EmissionPattern() = default;

		virtual std::unique_ptr<EmissionPattern> clone() const = 0;
		virtual unsigned int getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const = 0;
		virtual unsigned int emit(float deltaTime) = 0;
	};

	template <typename Derived>
	class CloneableEmissionPattern : public EmissionPattern
	{
	public:
		std::unique_ptr<EmissionPattern> clone() const override;
	};

	template<typename Derived>
	inline std::unique_ptr<EmissionPattern> CloneableEmissionPattern<Derived>::clone() const
	{
		return std::make_unique<Derived>(static_cast<const Derived&>(*this));
	}
}