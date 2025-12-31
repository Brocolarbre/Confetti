#include "ConfettiEngine/Renderer/SSBO.hpp"

#include <glad/glad.h>

namespace cft
{
	SSBO::SSBO(unsigned int particleCount) :
		m_id(0),
		m_capacity(particleCount * sizeof(Particle))
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBufferData(GL_SHADER_STORAGE_BUFFER, m_capacity, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_id);
	}

	SSBO::~SSBO()
	{
		glDeleteBuffers(1, &m_id);
	}

	void SSBO::bind() const
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_id);
	}

	void SSBO::setData(const ParticlePool& data) const
	{
		unsigned int dataCount = data.getCount();
		const std::vector<glm::vec4>& color = data.getColor();
		const std::vector<glm::vec3>& position = data.getPosition();
		const std::vector<glm::vec2>& scale = data.getScale();

		std::vector<Particle> particles;
		particles.reserve(dataCount);

		for (unsigned int i = 0; i < dataCount; ++i)
		{
			Particle particle{ color[i], glm::vec4(position[i], 0.0f), glm::vec4(scale[i], 0.0f, 0.0f) };
			particles.push_back(particle);
		}

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, particles.size() * sizeof(Particle), particles.data());
	}
}