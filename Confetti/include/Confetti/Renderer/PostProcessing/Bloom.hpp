#pragma once

#include "BloomFramebuffer.hpp"
#include "Confetti/Renderer/Tools/Framebuffer.hpp"
#include "Confetti/Renderer/Tools/Shader.hpp"

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

		const Texture& getBloomTexture() const;

		void resize(unsigned int width, unsigned int height);
		void render(unsigned int sourceTexture, float filterRadius);
	};
}