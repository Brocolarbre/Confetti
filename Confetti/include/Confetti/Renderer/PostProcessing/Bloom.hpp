#pragma once

#include "MipChainEffect.hpp"

namespace cft
{
	class Bloom : public MipChainEffect
	{
	private:
		Shader m_downsampleShader;
		Shader m_upsampleShader;
		float m_filterRadius;

		void setupDownsampleShader(unsigned int mipLevel) const override;
		void setupUpsampleShader(unsigned int mipLevel) const override;

	public:
		Bloom(unsigned int width, unsigned int height, unsigned int mipCount, float filterRadius);

		void setFilterRadius(float filterRadius);
	};
}