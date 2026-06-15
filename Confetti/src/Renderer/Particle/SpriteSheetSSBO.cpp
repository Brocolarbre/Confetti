#include "Confetti/Renderer/Particle/SpriteSheetSSBO.hpp"

#include <glad/glad.h>

namespace cft
{
	void SpriteSheetSSBO::resize(unsigned int capacity)
	{
		m_capacity = capacity;

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBufferData(GL_SHADER_STORAGE_BUFFER, m_capacity * sizeof(SpriteSheetData), nullptr, GL_STATIC_DRAW);
	}

	SpriteSheetSSBO::SpriteSheetSSBO() :
		m_id(0),
		m_capacity(0)
	{
		glGenBuffers(1, &m_id);
	}

	SpriteSheetSSBO::~SpriteSheetSSBO()
	{
		if (m_id != 0)
			glDeleteBuffers(1, &m_id);
	}

	void SpriteSheetSSBO::bind() const
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_id);
	}

	void SpriteSheetSSBO::setData(const std::vector<std::reference_wrapper<const SpriteSheet>>& spriteSheetData)
	{
		unsigned int spriteSheetCount = static_cast<unsigned int>(spriteSheetData.size());

		if (m_capacity < spriteSheetCount)
			resize(spriteSheetCount);

		std::vector<SpriteSheetData> spriteSheetsData;
		spriteSheetsData.reserve(spriteSheetCount);

		for (const SpriteSheet& spriteSheet : spriteSheetData)
		{
			spriteSheetsData.push_back(SpriteSheetData{
				glm::uvec2(spriteSheet.frameWidth, spriteSheet.frameHeight),
				glm::max(spriteSheet.frameCount, 1u),
				glm::max(spriteSheet.rowFrameCount, 1u),
				spriteSheet.animationSpeed,
				glm::vec3(0.0f)
			});
		}

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, spriteSheetsData.size() * sizeof(SpriteSheetData), spriteSheetsData.data());
	}
}