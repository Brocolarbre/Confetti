#include "Confetti/Renderer/Trail/TrailMesh.hpp"

#include <glad/glad.h>

namespace cft
{
	TrailMesh::TrailMesh() :
		m_vertexArray(0),
		m_vertexBuffer(0),
		m_first(),
		m_count()
	{
		glGenVertexArrays(1, &m_vertexArray);
		glGenBuffers(1, &m_vertexBuffer);

		glBindVertexArray(m_vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, textureCoordinates)));

		glEnableVertexAttribArray(3);
		glVertexAttribIPointer(3, 1, GL_INT, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, textureIndex)));

		glBindVertexArray(0);
	}

	TrailMesh::TrailMesh(TrailMesh&& trailMesh) noexcept :
		m_vertexArray(trailMesh.m_vertexArray),
		m_vertexBuffer(trailMesh.m_vertexBuffer),
		m_first(std::move(trailMesh.m_first)),
		m_count(std::move(trailMesh.m_count))
	{
		trailMesh.m_vertexArray = 0;
		trailMesh.m_vertexBuffer = 0;
	}

	TrailMesh::~TrailMesh()
	{
		if (m_vertexArray != 0)
			glDeleteVertexArrays(1, &m_vertexArray);

		if (m_vertexBuffer != 0)
			glDeleteBuffers(1, &m_vertexBuffer);
	}

	TrailMesh& TrailMesh::operator=(TrailMesh&& trailMesh) noexcept
	{
		if (&trailMesh == this)
			return *this;

		if (m_vertexArray != 0)
			glDeleteVertexArrays(1, &m_vertexArray);

		if (m_vertexBuffer != 0)
			glDeleteBuffers(1, &m_vertexBuffer);

		m_vertexArray = trailMesh.m_vertexArray;
		m_vertexBuffer = trailMesh.m_vertexBuffer;
		m_first = std::move(trailMesh.m_first);
		m_count = std::move(trailMesh.m_count);

		trailMesh.m_vertexArray = 0;
		trailMesh.m_vertexBuffer = 0;

		return *this;
	}

	void TrailMesh::setVertexData(const std::vector<Vertex>& vertexData, std::vector<int> first, std::vector<int> count)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(Vertex), vertexData.data(), GL_STREAM_DRAW);

		m_first = std::move(first);
		m_count = std::move(count);
	}

	void TrailMesh::multiDrawArrays() const
	{
		if (m_first.empty())
			return;

		glDisable(GL_CULL_FACE);
		glBindVertexArray(m_vertexArray);
		glMultiDrawArrays(GL_TRIANGLE_STRIP, m_first.data(), m_count.data(), static_cast<int>(m_first.size()));
		glEnable(GL_CULL_FACE);
	}
}