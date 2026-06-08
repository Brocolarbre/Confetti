#pragma once

#include <glm/glm.hpp>

namespace cft
{
	struct BloomMip
	{
		glm::uvec2 size;
		unsigned int texture;
	};

	class BloomFramebuffer
	{
	private:
		unsigned int m_id;
		unsigned int m_mipCount;
		std::vector<BloomMip> m_mips;

	public:
		BloomFramebuffer(unsigned int width, unsigned int height, unsigned int mipCount);
		~BloomFramebuffer();

		const std::vector<BloomMip>& getMips() const;

		void resize(unsigned int width, unsigned int height);

		void bind() const;
	};
}