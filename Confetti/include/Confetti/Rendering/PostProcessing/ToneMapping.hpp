#pragma once

#include "Confetti/Rendering/Tool/Framebuffer.hpp"
#include "Confetti/Rendering/Tool/Shader.hpp"

namespace cft
{
	class ToneMapping
	{
	private:
		Framebuffer m_framebuffer;
		Shader m_shader;
		unsigned int m_vertexArray;

		float m_exposure;
		float m_gamma;

	public:
		ToneMapping(unsigned int width, unsigned int height, float exposure, float gamma);
		~ToneMapping();

		unsigned int getOutputTexture() const;

		void setExposure(float exposure);
		void setGamma(float gamma);

		void resize(unsigned int width, unsigned int height);
		void render(unsigned int texture);
	};
}