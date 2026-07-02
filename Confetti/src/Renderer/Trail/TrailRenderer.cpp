#include "Confetti/Renderer/Trail/TrailRenderer.hpp"
#include "Confetti/Renderer/ShaderSource/TrailShaderSource.hpp"

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
		m_trailMesh(),
		m_shader()
	{
		m_shader.loadFromMemory(std::string(TRAIL_VERTEX_SHADER_SOURCE), std::string(TRAIL_FRAGMENT_SHADER_SOURCE));
	}

	void TrailRenderer::update(const std::unordered_map<unsigned int, TrailPool>& trailPools, const View& view)
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

					vertexA.position = currentPoint.position + normal * halfWidth; // (elapsedTime - currentPoint.spawnTime) * 
					vertexB.position = currentPoint.position - normal * halfWidth;

					vertexA.color = currentPoint.color;
					vertexB.color = currentPoint.color;

					if (pointIndex > 0)
						accumulated += glm::distance(previousPoint.position, currentPoint.position);

					float u = totalLength > 0.0f ? accumulated / totalLength : 0.0f;

					vertexA.textureCoordinates = glm::vec2(u, 0.0f);
					vertexB.textureCoordinates = glm::vec2(u, 1.0f);

					vertexData.push_back(vertexA);
					vertexData.push_back(vertexB);
				}
			}
		}

		m_trailMesh.setVertexData(vertexData, first, count);
	}

	void TrailRenderer::render(const View& view) const
	{
		m_shader.use();
		m_shader.setUniform("uView", view.viewMatrix);
		m_shader.setUniform("uProjection", view.projectionMatrix);

		m_trailMesh.multiDrawArrays();
	}
}