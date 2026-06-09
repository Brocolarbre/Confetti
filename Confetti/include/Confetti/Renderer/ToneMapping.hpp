#pragma once

#include "Shader.hpp"

namespace cft
{
	class ToneMapping
	{
	private:
		Shader m_shader;
		unsigned int m_vertexArray;

		float m_exposure;
		float m_gamma;

	public:
		ToneMapping(float exposure, float gamma);
		~ToneMapping();

		void setExposure(float exposure);
		void setGamme(float gamma);

		void render(unsigned int texture);
	};
}