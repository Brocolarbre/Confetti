#pragma once

#include "Confetti/Renderer/Tools/Texture.hpp"

#include <vector>

namespace cft
{
	class MipChainFramebuffer
	{
	private:
		unsigned int m_id;
		std::vector<Texture> m_mips;
		unsigned int m_mipCount;
		unsigned int m_internalFormat;
		unsigned int m_format;
		unsigned int m_type;

	public:
		MipChainFramebuffer(unsigned int width, unsigned int height, unsigned int mipCount, unsigned int internalFormat, unsigned int format, unsigned int type);
		MipChainFramebuffer(const MipChainFramebuffer& mipChainFramebuffer) = delete;
		MipChainFramebuffer(MipChainFramebuffer&& mipChainFramebuffer) noexcept;
		~MipChainFramebuffer();

		MipChainFramebuffer& operator=(const MipChainFramebuffer& mipChainFramebuffer) = delete;
		MipChainFramebuffer& operator=(MipChainFramebuffer&& mipChainFramebuffer) noexcept;

		const std::vector<Texture>& getMips() const;
		unsigned int getOutputTexture() const;

		void bind() const;
		void resize(unsigned int width, unsigned int height);
	};
}