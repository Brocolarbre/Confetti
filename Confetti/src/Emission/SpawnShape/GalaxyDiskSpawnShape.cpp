#include "Confetti/Emission/SpawnShape/GalaxyDiskSpawnShape.hpp"

#include <glm/gtc/constants.hpp>

namespace cft
{
	SpawnContext GalaxyDiskSpawnShape::generateValue(unsigned int count, unsigned int index) const
	{
		if (count == 0)
			return SpawnContext{ glm::vec3(0.0f), m_axis };

		constexpr float goldenAngle = 2.39996323f;
		constexpr float twoPi = glm::two_pi<float>();

		/*
		 * ---------------------------------------------------------
		 * 1. Deterministic pseudo-random values
		 * ---------------------------------------------------------
		 *
		 * We don't want to introduce a random engine into
		 * SpawnShape, so generate deterministic values from index.
		 */

		auto random01 = [](unsigned int value) -> float
			{
				value ^= value >> 16;
				value *= 0x7feb352d;
				value ^= value >> 15;
				value *= 0x846ca68b;
				value ^= value >> 16;

				return static_cast<float>(value)
					/ static_cast<float>(0xFFFFFFFFu);
			};

		float randomRadius = random01(index * 92837111u + 12345u);
		float randomAngle = random01(index * 689287499u + 54321u);
		float randomHeight = random01(index * 283923481u + 98765u);

		/*
		 * ---------------------------------------------------------
		 * 2. Radial distribution
		 * ---------------------------------------------------------
		 *
		 * The exponential falloff makes the galaxy denser
		 * towards its center.
		 *
		 * We also mix in a small amount of uniform distribution
		 * so that the outer arms remain visible.
		 */

		float exponentialRadius = -std::log(glm::max(1.0f - randomRadius, 0.0001f));

		/*
		 * Scale the exponential distribution so that most
		 * particles remain inside m_radius.
		 */
		float scale = m_radius / 4.0f;
		float radius = exponentialRadius * scale;

		/*
		 * Clamp the galaxy radius.
		 */
		radius = glm::min(radius, m_radius);

		/*
		 * ---------------------------------------------------------
		 * 3. Central bulge
		 * ---------------------------------------------------------
		 *
		 * A fraction of particles are concentrated around the
		 * center. The probability decreases as the particle
		 * index progresses.
		 */

		float bulgeProbability = glm::max(1.0f - radius / m_radius, 0.0f);

		if (random01(index * 374761393u + 31u) < bulgeProbability * 0.35f)
		{
			float bulgeRandom = random01(index * 668265263u + 71u);
			radius = m_bulgeRadius * glm::sqrt(bulgeRandom);
		}

		/*
		 * ---------------------------------------------------------
		 * 4. Spiral arms
		 * ---------------------------------------------------------
		 *
		 * Convert radius to normalized [0, 1] range.
		 */
		float normalizedRadius = radius / m_radius;

		/*
		 * Spiral angle increases with distance from the center.
		 */
		float spiralAngle = normalizedRadius * m_turns * twoPi;

		/*
		 * Distribute particles between the spiral arms.
		 */
		unsigned int armIndex = index % m_arms;

		float armAngle = twoPi * (static_cast<float>(armIndex) / static_cast<float>(m_arms));

		/*
		 * Golden-angle distribution prevents particles belonging
		 * to the same arm from forming obvious rings.
		 */
		float baseAngle = static_cast<float>(index) * goldenAngle;

		/*
		 * Arm spread becomes slightly larger towards the outside
		 * of the galaxy.
		 */
		float spread = m_armSpread * (0.25f + normalizedRadius);
		float armOffset = (randomAngle - 0.5f) * spread;

		/*
		 * Small deterministic variation.
		 */
		float noise = glm::sin(static_cast<float>(index) * goldenAngle) * spread * 0.25f;
		float angle = armAngle + spiralAngle + baseAngle * 0.08f + armOffset + noise;

		/*
		 * ---------------------------------------------------------
		 * 5. Build the galaxy plane
		 * ---------------------------------------------------------
		 */

		glm::vec3 tangent = glm::abs(m_axis.y) < 0.999f ? glm::normalize(glm::cross(m_axis, glm::vec3(0.0f, 1.0f, 0.0f))) : glm::normalize(glm::cross(m_axis, glm::vec3(1.0f, 0.0f, 0.0f)));
		glm::vec3 bitangent = glm::cross(m_axis, tangent);

		glm::vec3 radial = glm::cos(angle) * tangent + glm::sin(angle) * bitangent;

		/*
		 * ---------------------------------------------------------
		 * 6. Vertical thickness
		 * ---------------------------------------------------------
		 *
		 * The galaxy is mostly flat, but isn't infinitely thin.
		 *
		 * Use a Gaussian-like distribution around the center
		 * of the disk.
		 */
		float heightRandom = randomHeight * 2.0f - 1.0f;

		float verticalOffset = heightRandom * m_thickness * (0.25f + normalizedRadius * 0.75f);

		/*
		 * ---------------------------------------------------------
		 * 7. Final position
		 * ---------------------------------------------------------
		 */

		glm::vec3 position = radial * radius + m_axis * verticalOffset;

		/*
		 * ---------------------------------------------------------
		 * 8. Normal
		 * ---------------------------------------------------------
		 *
		 * For a galaxy disk, using the galaxy axis as the normal
		 * is generally more useful than using the radial direction.
		 */
		glm::vec3 normal = m_axis;

		return SpawnContext{ position, normal };
	}

	GalaxyDiskSpawnShape::GalaxyDiskSpawnShape(float radius, float bulgeRadius, float thickness, unsigned int arms, float turns, float armSpread, const glm::vec3& axis) :
		m_radius(glm::max(radius, 0.0001f)),
		m_bulgeRadius(glm::max(bulgeRadius, 0.0f)),
		m_thickness(glm::max(thickness, 0.0f)),
		m_turns(glm::max(turns, 0.0f)),
		m_armSpread(glm::max(armSpread, 0.0f)),
		m_arms(glm::max(arms, 1u)),
		m_axis(glm::normalize(axis))
	{

	}
}