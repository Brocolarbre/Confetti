#pragma once

#include "MipChainEffect.hpp"

namespace cft
{
	class Flare : public MipChainEffect
	{
	private:
		Shader m_downsampleShader;
		Shader m_upsampleShader;

		glm::vec2 m_direction;
		float m_radius;
		float m_chromaticAberrationStrength;

		void setupDownsampleShader(unsigned int mipLevel) const override;
		void setupUpsampleShader(unsigned int mipLevel) const override;

	public:
		Flare(unsigned int width, unsigned int height, unsigned int mipCount, const glm::vec2& direction, float radius, float chromaticAberrationStrength);

		void setDirection(const glm::vec2& direction);
		void setRadius(float radius);
		void setChromaticAberrationStength(float chromaticAberrationStrength);
	};
}