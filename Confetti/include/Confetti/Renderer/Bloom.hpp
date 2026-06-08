#pragma once

#include "BloomFramebuffer.hpp"
#include "Framebuffer.hpp"
#include "Shader.hpp"

namespace cft
{
	class Bloom
	{
	private:
		BloomFramebuffer m_bloomFramebuffer;
		Framebuffer m_framebuffer;
		Shader m_downsampleShader;
		Shader m_upsampleShader;
		Shader m_bloomShader;

		unsigned int m_mipCount;
		glm::uvec2 m_viewportSize;

		unsigned int m_vertexArray;

		void renderDownsamples(unsigned int sourceTexture);
		void renderUpsamples(float filterRadius);
		void applyBloom(unsigned int sourceTexture);

	public:
		Bloom(unsigned int width, unsigned int height, unsigned int mipCount);
		~Bloom();

		unsigned int getBloomTexture() const;

		void resize(unsigned int width, unsigned int height);
		void render(unsigned int sourceTexture, float filterRadius);
	};
}