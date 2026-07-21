#include "Confetti/Simulation/Link/RibbonGenerator/PathRibbonGenerator.hpp"

namespace cft
{
	glm::vec3 PathRibbonGenerator::generateRibbonPoint(float t, float elapsedTime, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const
	{
		glm::vec3 a = fromParticle.postBehaviorPosition;
		glm::vec3 b = toParticle.postBehaviorPosition;

		glm::vec3 center = glm::mix(a, b, t);
		glm::vec3 axis = glm::normalize(b - a);

		glm::vec3 reference = glm::abs(axis.y) < 0.999f ? glm::vec3(0.0f, 1.0f, 0.0f) : glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 right = glm::normalize(glm::cross(axis, reference));
		glm::vec3 up = glm::normalize(glm::cross(right, axis));

		if (m_easing)
			t = (*m_easing)(t);

		lw::Point point = (*m_interpolator)(m_path, t);
		glm::vec3 offset = right * point.x + up * point.y + axis * point.z;

		return center + offset;
	}

	PathRibbonGenerator::PathRibbonGenerator(lw::Curve path, std::unique_ptr<lw::Interpolator> interpolator, std::unique_ptr<lw::Easing> easing) :
		m_path(std::move(path)),
		m_interpolator(std::move(interpolator)),
		m_easing(std::move(easing))
	{

	}

	PathRibbonGenerator::PathRibbonGenerator(const PathRibbonGenerator& pathRibbonGenerator) :
		m_path(pathRibbonGenerator.m_path),
		m_interpolator(pathRibbonGenerator.m_interpolator->clone()),
		m_easing(pathRibbonGenerator.m_easing ? pathRibbonGenerator.m_easing->clone() : nullptr)
	{

	}
}