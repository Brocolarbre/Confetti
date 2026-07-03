#pragma once

#include "BloomFramebuffer.hpp"
#include "Confetti/Renderer/Tools/Framebuffer.hpp"
#include "Confetti/Renderer/Tools/Shader.hpp"

namespace cft
{
	class Bloom
	{
	private:
		BloomFramebuffer m_bloomFramebuffer; // Second framebuffer for upsampling ?
		Shader m_downsampleShader;
		Shader m_upsampleShader;
		unsigned int m_vertexArray;

		float m_filterRadius;

		void renderDownsamples(unsigned int sourceTexture);
		void renderUpsamples(float filterRadius);

	public:
		Bloom(unsigned int width, unsigned int height, unsigned int mipCount, float filterRadius);
		~Bloom();

		unsigned int getOutputTexture() const;

		void setFilterRadius(float filterRadius);

		void resize(unsigned int width, unsigned int height);
		void render(unsigned int sourceTexture);
	};
}