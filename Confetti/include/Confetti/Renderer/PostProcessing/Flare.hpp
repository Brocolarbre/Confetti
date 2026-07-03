#pragma once

#include "Confetti/Renderer/Tools/Framebuffer.hpp"
#include "Confetti/Renderer/Tools/Shader.hpp"

namespace cft
{
	class Flare
	{
	private:
		Framebuffer m_brightPassFramebuffer;
		Framebuffer m_flareFramebuffer;
		Shader m_brightPassShader;
		Shader m_flareShader;
		unsigned int m_vertexArray;

		float m_threshold;
		glm::vec2 m_direction;
		int m_radius;
		float m_chromaticSeparationStrength;

	public:
		Flare(unsigned int width, unsigned int height, float threshold, const glm::vec2& direction, int radius, float chromaticSeparationStrength);
		~Flare();

		unsigned int getOutputTexture() const;

		void setThreshold(float threshold);
		void setDirection(const glm::vec2& direction);
		void setRadius(int radius);
		void setChromaticSeparationStength(float chromaticSeparationStrength);

		void resize(unsigned int width, unsigned int height);
		void render(unsigned int texture);
	};
}