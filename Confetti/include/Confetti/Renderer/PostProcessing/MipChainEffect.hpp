#pragma once

#include "MipChainFramebuffer.hpp"
#include "Confetti/Renderer/Tools/Shader.hpp"

namespace cft
{
	class MipChainEffect
	{
	protected:
		MipChainFramebuffer m_framebuffer;
		Shader m_downsampleShader;
		unsigned int m_vertexArray;

		virtual void setupUpsampleShader() const = 0;

		void renderDownsamples(unsigned int sourceTexture) const;
		void renderUpsamples() const;

	public:
		MipChainEffect(unsigned int width, unsigned int height, unsigned int mipCount);
		virtual ~MipChainEffect();

		unsigned int getOutputTexture() const;

		void resize(unsigned int width, unsigned int height);
		void render(unsigned int sourceTexture) const;
	};
}