#pragma once

#include <glm/glm.hpp>

namespace cft
{
	class ParticlePathMesh
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
		ParticlePathMesh();
		ParticlePathMesh(const ParticlePathMesh& particlePathMesh) = delete;
		ParticlePathMesh(ParticlePathMesh&& particlePathMesh) noexcept;
		~ParticlePathMesh();

		ParticlePathMesh& operator=(const ParticlePathMesh& particlePathMesh) = delete;
		ParticlePathMesh& operator=(ParticlePathMesh&& particlePathMesh) noexcept;

		void setVertexData(const std::vector<Vertex>& vertexData, std::vector<int> first, std::vector<int> count);

		void multiDrawArrays() const;
	};
}