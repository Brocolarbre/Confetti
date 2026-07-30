#include "Confetti/Serialization/JsonTools.hpp"

namespace cft
{
	glm::quat JsonTools::eulerAnglesToQuaternion(const glm::vec3& eulerAngles)
	{
		return glm::quat(glm::vec3(glm::radians(eulerAngles.x), glm::radians(eulerAngles.y), glm::radians(eulerAngles.z)));
	}

	std::vector<glm::quat> JsonTools::eulerAnglesToQuaternion(const std::vector<glm::vec3>& eulerAngles)
	{
		std::vector<glm::quat> rotations;
		rotations.reserve(eulerAngles.size());

		for (const glm::vec3& rotation : eulerAngles)
			rotations.push_back(eulerAnglesToQuaternion(rotation));

		return rotations;
	}

	std::vector<cft::WeightedValue<glm::quat>> JsonTools::eulerAnglesToQuaternion(const std::vector<cft::WeightedValue<glm::vec3>>& eulerAngles)
	{
		std::vector<cft::WeightedValue<glm::quat>> rotations;
		rotations.reserve(eulerAngles.size());

		for (const cft::WeightedValue<glm::vec3>& rotation : eulerAngles)
			rotations.push_back(cft::WeightedValue<glm::quat>{ eulerAnglesToQuaternion(rotation.value), rotation.weight });

		return rotations;
	}
}