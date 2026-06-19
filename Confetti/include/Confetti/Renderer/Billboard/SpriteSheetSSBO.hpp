#pragma once

#include "Confetti/Particle/SpriteSheet.hpp"

#include <glm/glm.hpp>
#include <unordered_map>

namespace cft
{
	class SpriteSheetSSBO
	{
	private:
		unsigned int m_id;
		unsigned int m_capacity;

		struct SpriteSheetData
		{
			glm::uvec2 frameSize;
			unsigned int frameCount;
			unsigned int rowFrameCount;
			float animationSpeed;
			glm::vec3 padding;
		};

		void resize(unsigned int capacity);

	public:
		SpriteSheetSSBO();
		~SpriteSheetSSBO();

		void bind() const;
		void setData(const std::vector<std::reference_wrapper<const SpriteSheet>>& spriteSheetData);
	};
}