#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace cft
{
	struct VertexKey
	{
		int position;
		int normal;
		int textureCoordinates;

		bool operator==(const VertexKey& vertexKey) const;
	};

	struct VertexKeyHash
	{
		size_t operator()(const VertexKey& key) const;
	};

	struct Vertex
	{
		glm::vec4 color;
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 textureCoordinates;
	};

	class Model
	{
	private:
		std::vector<Vertex> m_vertexData;
		std::vector<unsigned int> m_indexData;

	public:
		unsigned int getVertexCount() const;
		unsigned int getIndexCount() const;

		const std::vector<Vertex>& getVertexData() const;
		const std::vector<unsigned int>& getIndexData() const;

		void loadFromFile(const std::string& path);
		void loadFromMemory(std::vector<Vertex> vertexData, std::vector<unsigned int> indexData);
	};
}