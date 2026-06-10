#pragma once

#include "Confetti/Renderer/Tools/Texture.hpp"

#include <glm/glm.hpp>

namespace cft
{
	class BloomFramebuffer
	{
	private:
		unsigned int m_id;
		unsigned int m_mipCount;
		std::vector<Texture> m_mips;

	public:
		BloomFramebuffer(unsigned int width, unsigned int height, unsigned int mipCount);
		~BloomFramebuffer();

		const std::vector<Texture>& getMips() const;

		void resize(unsigned int width, unsigned int height);

		void bind() const;
	};
}