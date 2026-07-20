#include "Confetti/Resource/Model.hpp"

#include <tiny_obj_loader.h>
#include <iostream>
#include <unordered_map>

namespace cft
{
	bool VertexKey::operator==(const VertexKey& vertexKey) const
	{
		return position == vertexKey.position && normal == vertexKey.normal && textureCoordinates == vertexKey.textureCoordinates;
	}

	size_t VertexKeyHash::operator()(const VertexKey& key) const
	{
		size_t h1 = std::hash<int>{}(key.position);
		size_t h2 = std::hash<int>{}(key.normal);
		size_t h3 = std::hash<int>{}(key.textureCoordinates);

		return h1 ^ (h2 << 1) ^ (h3 << 2);
	}

	unsigned int Model::getVertexCount() const
	{
		return static_cast<unsigned int>(m_vertexData.size());
	}

	unsigned int Model::getIndexCount() const
	{
		return static_cast<unsigned int>(m_indexData.size());
	}

	const std::vector<Vertex>& Model::getVertexData() const
	{
		return m_vertexData;
	}

	const std::vector<unsigned int>& Model::getIndexData() const
	{
		return m_indexData;
	}

	void Model::loadFromFile(const std::string& path)
	{
		m_vertexData.clear();
		m_indexData.clear();

		tinyobj::ObjReader reader;
		tinyobj::ObjReaderConfig configuration;
		configuration.triangulate = true;

		if (!reader.ParseFromFile(path, configuration))
		{
			std::cerr << "Failed to load model at '" << path << "' : " << reader.Error() << std::endl;
			return;
		}

		if (!reader.Warning().empty())
			std::cout << "Model loading warning : " << reader.Warning();

		const tinyobj::attrib_t& attributes = reader.GetAttrib();
		const std::vector<tinyobj::shape_t>& shapes = reader.GetShapes();

		unsigned int totalVertexCount = 0;

		for (const tinyobj::shape_t& shape : shapes)
		{
			for (unsigned int vertexCount : shape.mesh.num_face_vertices)
				totalVertexCount += vertexCount;
		}

		m_vertexData.reserve(totalVertexCount);
		m_indexData.reserve(totalVertexCount);

		std::unordered_map<VertexKey, unsigned int, VertexKeyHash> vertexMap;

		for (unsigned int shapeIndex = 0; shapeIndex < shapes.size(); ++shapeIndex)
		{
			const tinyobj::shape_t& shape = shapes[shapeIndex];
			unsigned int indexOffset = 0;

			for (unsigned int faceIndex = 0; faceIndex < shape.mesh.num_face_vertices.size(); ++faceIndex)
			{
				unsigned int faceVertexCount = shape.mesh.num_face_vertices[faceIndex];

				for (unsigned int vertexIndex = 0; vertexIndex < faceVertexCount; ++vertexIndex)
				{
					tinyobj::index_t objectIndex = shape.mesh.indices[static_cast<size_t>(indexOffset + vertexIndex)];
					VertexKey key{
						objectIndex.vertex_index,
						objectIndex.normal_index,
						objectIndex.texcoord_index
					};

					auto it = vertexMap.find(key);

					if (it != vertexMap.end())
					{
						m_indexData.push_back(it->second);
						continue;
					}

					size_t colorOffset = static_cast<size_t>(objectIndex.vertex_index * 3);

					bool hasColor = attributes.colors.size() >= colorOffset + 3;
					bool hasNormal = objectIndex.normal_index >= 0;
					bool hasTextureCoordinates = objectIndex.texcoord_index >= 0;					

					Vertex vertex{
						hasColor ?
						glm::vec4(
							attributes.colors[colorOffset + 0],
							attributes.colors[colorOffset + 1],
							attributes.colors[colorOffset + 2],
							1.0f
						) : glm::vec4(1.0f),
						glm::vec3(
							attributes.vertices[static_cast<size_t>(objectIndex.vertex_index * 3 + 0)],
							attributes.vertices[static_cast<size_t>(objectIndex.vertex_index * 3 + 1)],
							attributes.vertices[static_cast<size_t>(objectIndex.vertex_index * 3 + 2)]
						),
						hasNormal ?
						glm::vec3(
							attributes.normals[static_cast<size_t>(objectIndex.normal_index * 3 + 0)],
							attributes.normals[static_cast<size_t>(objectIndex.normal_index * 3 + 1)],
							attributes.normals[static_cast<size_t>(objectIndex.normal_index * 3 + 2)]
						) : glm::vec3(0.0f),
						hasTextureCoordinates ?
						glm::vec2(
							attributes.texcoords[static_cast<size_t>(objectIndex.texcoord_index * 2 + 0)],
							attributes.texcoords[static_cast<size_t>(objectIndex.texcoord_index * 2 + 1)]
						) : glm::vec2(0.0f)
					};

					unsigned int index = static_cast<unsigned int>(m_vertexData.size());
					vertexMap[key] = index;

					m_vertexData.push_back(vertex);
					m_indexData.push_back(index);
				}

				indexOffset += faceVertexCount;
			}
		}
	}

	void Model::loadFromMemory(std::vector<Vertex> vertexData, std::vector<unsigned int> indexData)
	{
		m_vertexData = std::move(vertexData);
		m_indexData = std::move(indexData);
	}
}