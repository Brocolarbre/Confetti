#pragma once

#include "Confetti/Rendering/Tool/Framebuffer.hpp"
#include "Confetti/Rendering/Tool/Shader.hpp"

namespace cft
{
	class HdrComposite
	{
	private:
		Framebuffer m_framebuffer;
		Shader m_shader;
		unsigned int m_vertexArray;

		float m_bloomStrength;
		float m_flareStrength;

	public:
		HdrComposite(unsigned int width, unsigned int height, float bloomStrength, float flareStrength);
		~HdrComposite();

		unsigned int getOutputTexture() const;

		void setBloomStrength(float bloomStrength);
		void setFlareStrength(float flareStrength);

		void resize(unsigned int width, unsigned int height);
		void render(unsigned int sourceTexture, unsigned int bloomTexture, unsigned int flareTexture);
	};
}