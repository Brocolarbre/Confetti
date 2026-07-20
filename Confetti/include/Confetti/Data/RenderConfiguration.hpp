#pragma once

#include <optional>
#include <variant>

namespace cft
{
	enum class RenderType
	{
		Billboard,
		Mesh
	};

	struct BillboardRenderConfiguration
	{
		std::optional<unsigned int> spriteSheetId;
	};

	struct MeshRenderConfiguration
	{
		unsigned int modelId;
		std::optional<unsigned int> imageId;
	};

	struct RenderConfiguration
	{
		RenderType renderType;
		std::variant<BillboardRenderConfiguration, MeshRenderConfiguration> configurationData;
	};
}