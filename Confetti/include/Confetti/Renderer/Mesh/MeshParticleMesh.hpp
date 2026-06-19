#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace cft
{
	class MeshParticleMesh
	{
	public:
		struct Vertex
		{
			glm::vec3 position;
			glm::vec4 color;
			glm::vec2 textureCoordinates;
		};

	private:
		unsigned int m_vao;
		unsigned int m_vbo;
		unsigned int m_ebo;
		unsigned int m_indexCount;

	public:
		MeshParticleMesh();
		~MeshParticleMesh();

		void load(const std::vector<Vertex>& vertexData, const std::vector<unsigned int>& indexData);

		void draw() const;
		void drawInstanced(unsigned int count) const;
		void drawInstancedBaseInstance(unsigned int firstInstance, unsigned int instanceCount) const;
	};
}