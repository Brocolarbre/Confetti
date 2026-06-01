#pragma once

#include <glm/glm.hpp>

namespace cft
{
	enum class Falloff
	{
		Constant,
		Linear,
		Quadratic,
		Cubic
	};

	class SpatialInfluence
	{
	private:
		glm::vec3 m_origin;
		float m_radius;
		float m_squaredRadius;
		Falloff m_falloff;
		bool m_infiniteRadius;

	public:
		SpatialInfluence(const glm::vec3& origin, float radius, Falloff falloff, bool infiniteRadius);

		const glm::vec3& getOrigin() const;

		float getStrengthFactor(const glm::vec3& position) const;
	};
}