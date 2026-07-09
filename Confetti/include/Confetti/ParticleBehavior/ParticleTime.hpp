#pragma once

namespace cft
{
	struct ParticleTime
	{
		enum class Space
		{
			Absolute,
			Normalized
		};

		float value;
		Space space;

		float normalize(float lifetime) const;

		static ParticleTime absolute(float value);
		static ParticleTime normalized(float value);
	};
}