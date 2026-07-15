#include "Confetti/Renderer/Trail/TrailRenderer.hpp"
#include "Confetti/Renderer/ShaderSource/TrailShaderSource.hpp"

#include <glad/glad.h>
#include <iostream>

namespace
{
	glm::vec3 safeNormalize(const glm::vec3& v)
	{
		float l2 = glm::dot(v, v);

		if (l2 < 1e-12f)
			return glm::vec3(0.0f);

		return v / std::sqrt(l2);
	}
}

namespace cft
{
	TrailRenderer::TrailRenderer() :
		m_imageIdToTextureIndex(),
		m_textureArray(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE),
		m_trailMesh(),
		m_shader()
	{
		m_shader.loadFromMemory(std::string(TRAIL_VERTEX_SHADER_SOURCE), std::string(TRAIL_FRAGMENT_SHADER_SOURCE));
	}

	void TrailRenderer::loadTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds, unsigned int width, unsigned int height)
	{
		m_imageIdToTextureIndex.clear();

		std::vector<std::vector<std::byte>> imageData;
		imageData.reserve(imageIds.size());

		for (unsigned int imageId : imageIds)
		{
			const Image& image = assetRegistry.getImage(imageId);
			m_imageIdToTextureIndex[imageId] = static_cast<unsigned int>(imageData.size());
			imageData.push_back(image.getData());

			unsigned int imageWidth = image.getWidth();
			unsigned int imageHeight = image.getHeight();

			if (imageWidth != width || imageHeight != height)
				std::cerr << "Trail renderer texture loading error : size mismatch for image at id " << imageId << " : " << imageWidth << "x" << imageHeight << " instead of " << width << "x" << height << std::endl;
		}

		std::vector<const void*> textureData;
		textureData.reserve(imageData.size());

		for (const std::vector<std::byte>& data : imageData)
			textureData.push_back(data.data());

		//m_textureArray.load(textureData, width, height, GL_NEAREST, GL_CLAMP_TO_EDGE);
		m_textureArray.load(textureData, width, height, GL_NEAREST, GL_REPEAT);
	}

	void TrailRenderer::update(const std::unordered_map<unsigned int, TrailPool>& trailPools, const TrailRegistry& trailRegistry, const View& view)
	{
		size_t totalVertices = 0;
		size_t totalTrails = 0;

		for (const auto& [id, pool] : trailPools)
		{
			const std::vector<std::deque<TrailPoint>>& trailPoints = pool.getTrailPoints();

			for (unsigned int i = 0; i < pool.getCount(); ++i)
			{
				if (trailPoints[i].size() < 2)
					continue;

				++totalTrails;
				totalVertices += trailPoints[i].size() * 2;
			}
		}

		std::vector<TrailMesh::Vertex> vertexData;
		std::vector<int> first;
		std::vector<int> count;

		vertexData.reserve(totalVertices);
		first.reserve(totalTrails);
		count.reserve(totalTrails);

		for (const auto& [id, pool] : trailPools)
		{
			const std::vector<unsigned int>& trailRegistryId = pool.getTrailRegistryId();
			const std::vector<std::deque<TrailPoint>>& trailPoints = pool.getTrailPoints();
			unsigned int poolCount = pool.getCount();

			for (unsigned int i = 0; i < poolCount; ++i)
			{
				const std::deque<TrailPoint>& trail = trailPoints[i];

				if (trail.size() < 2)
					continue;

				first.push_back(static_cast<int>(vertexData.size()));
				count.push_back(static_cast<int>(trail.size() * 2));

				float totalLength = 0.0f;
				for (size_t i = 1; i < trail.size(); ++i)
					totalLength += glm::distance(trail[i - 1].position, trail[i].position);

				float accumulated = 0.0f;

				for (unsigned int pointIndex = 0; pointIndex < trail.size(); ++pointIndex)
				{
					const TrailPoint& previousPoint = pointIndex > 0 ? trail[static_cast<size_t>(pointIndex) - 1] : trail[pointIndex];
					const TrailPoint& currentPoint = trail[pointIndex];
					const TrailPoint& nextPoint = pointIndex < trail.size() - 1 ? trail[static_cast<size_t>(pointIndex) + 1] : trail[pointIndex];

					glm::vec3 tangent;

					if (pointIndex == 0)
					{
						tangent = safeNormalize(nextPoint.position - currentPoint.position);
					}
					else if (pointIndex == trail.size() - 1)
					{
						tangent = safeNormalize(currentPoint.position - previousPoint.position);
					}
					else
					{
						glm::vec3 tangentA = safeNormalize(currentPoint.position - previousPoint.position);
						glm::vec3 tangentB = safeNormalize(nextPoint.position - currentPoint.position);

						tangent = tangentA + tangentB;

						if (tangent.x * tangent.x + tangent.y * tangent.y + tangent.z * tangent.z < 1e-6f)
							tangent = tangentB;

						tangent = safeNormalize(tangent);
					}

					glm::vec3 cameraDirection = safeNormalize(view.position - currentPoint.position);
					glm::vec3 normal = glm::cross(tangent, cameraDirection);

					if (glm::dot(normal, normal) < 1e-8f)
					{
						normal = glm::cross(tangent, glm::vec3(0, 1, 0));

						if (glm::dot(normal, normal) < 1e-8f)
							normal = glm::cross(tangent, glm::vec3(1, 0, 0));
					}

					normal = glm::normalize(normal);

					float halfWidth = currentPoint.thickness * 0.5f;

					TrailMesh::Vertex vertexA;
					TrailMesh::Vertex vertexB;

					vertexA.position = currentPoint.position + normal * halfWidth;
					vertexB.position = currentPoint.position - normal * halfWidth;

					vertexA.color = currentPoint.color;
					vertexB.color = currentPoint.color;

					if (pointIndex > 0)
						accumulated += glm::distance(previousPoint.position, currentPoint.position);

					int textureIndex = -1;

					const TrailRegistryEntry& trailRegistryEntry = trailRegistry.getEntry(trailRegistryId[i]);
					if (trailRegistryEntry.trailConfiguration.pathConfiguration.image.has_value())
					{
						const PathImage& pathImage = trailRegistryEntry.trailConfiguration.pathConfiguration.image.value();
						
						float v = 0.0f;

						if (pathImage.repeatStretch.has_value())
							v = accumulated / (currentPoint.thickness * pathImage.repeatStretch.value());
						else
							v = totalLength > 0.0f ? accumulated / totalLength : 0.0f;

						vertexA.textureCoordinates = glm::vec2(0.0f, v);
						vertexB.textureCoordinates = glm::vec2(1.0f, v);

						textureIndex = static_cast<int>(m_imageIdToTextureIndex.at(pathImage.imageId));
					}
					else
					{
						vertexA.textureCoordinates = glm::vec2(0.0f);
						vertexB.textureCoordinates = glm::vec2(0.0f);
					}

					vertexA.textureIndex = textureIndex;
					vertexB.textureIndex = textureIndex;

					vertexData.push_back(vertexA);
					vertexData.push_back(vertexB);
				}
			}
		}

		m_trailMesh.setVertexData(vertexData, first, count);
	}

	void TrailRenderer::render(const View& view) const
	{
		TextureArray::setActiveSlot(0);
		m_textureArray.bind();

		m_shader.use();
		m_shader.setUniform("uView", view.viewMatrix);
		m_shader.setUniform("uProjection", view.projectionMatrix);

		m_trailMesh.multiDrawArrays();
	}
}