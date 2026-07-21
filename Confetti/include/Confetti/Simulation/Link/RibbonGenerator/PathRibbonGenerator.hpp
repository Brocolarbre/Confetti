#pragma once

#include "RibbonGenerator.hpp"

#include <LineWeaver/Interpolation/Interpolator.hpp>
#include <LineWeaver/Easing/Easing.hpp>

namespace cft
{
	class PathRibbonGenerator : public Cloneable<PathRibbonGenerator, RibbonGenerator>
	{
	private:
		lw::Curve m_path;
		std::unique_ptr<lw::Interpolator> m_interpolator;
		std::unique_ptr<lw::Easing> m_easing;

		glm::vec3 generateRibbonPoint(float t, float elapsedTime, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const;

	public:
		PathRibbonGenerator(lw::Curve path, std::unique_ptr<lw::Interpolator> interpolator, std::unique_ptr<lw::Easing> easing);
		PathRibbonGenerator(const PathRibbonGenerator& pathRibbonGenerator);
	};
}