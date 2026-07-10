#pragma once

#include <glm/glm.hpp>

namespace cft
{
	class TrailMesh
	{
	public:
		struct Vertex
		{
			glm::vec3 position;
			glm::vec4 color;
			glm::vec2 textureCoordinates;
			int textureIndex;
		};

	private:
		unsigned int m_vertexArray;
		unsigned int m_vertexBuffer;

		std::vector<int> m_first;
		std::vector<int> m_count;

	public:
		TrailMesh();
		TrailMesh(const TrailMesh& trailMesh) = delete;
		TrailMesh(TrailMesh&& trailMesh) noexcept;
		~TrailMesh();

		TrailMesh& operator=(const TrailMesh& trailMesh) = delete;
		TrailMesh& operator=(TrailMesh&& trailMesh) noexcept;

		void setVertexData(const std::vector<Vertex>& vertexData, std::vector<int> first, std::vector<int> count);

		void multiDrawArrays() const;
	};
}