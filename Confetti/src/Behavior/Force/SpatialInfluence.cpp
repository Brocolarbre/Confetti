#include "Confetti/Behavior/Force/SpatialInfluence.hpp"

namespace cft
{
	SpatialInfluence::SpatialInfluence(const glm::vec3& origin, float radius, Falloff falloff) :
		m_origin(origin),
		m_radius(radius),
		m_squaredRadius(radius * radius),
		m_falloff(falloff)
	{

	}

	const glm::vec3& SpatialInfluence::getOrigin() const
	{
		return m_origin;
	}

	float SpatialInfluence::getStrengthFactor(const glm::vec3& position) const
	{
		glm::vec3 offset = m_origin - position;
		float squaredDistance = glm::dot(offset, offset);

		if (m_radius != 0.0f && squaredDistance > m_squaredRadius)
			return 0.0f;

		if (m_falloff == Falloff::Constant)
			return 1.0f;

		float t = m_radius == 0.0f ? squaredDistance : squaredDistance / m_squaredRadius;
		float factor = glm::max(0.0f, 1.0f - t);

		float influence = 0.0f;

		switch (m_falloff)
		{
		case Falloff::Linear: influence = factor; break;
		case Falloff::Quadratic: influence = factor * factor; break;
		case Falloff::Cubic: influence = factor * factor * factor; break;
		}

		return glm::clamp(influence, 0.0f, 1.0f);
	}
}