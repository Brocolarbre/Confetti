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

	struct BillboardRenderDescriptor
	{
		std::optional<unsigned int> spriteSheetId;
	};

	struct MeshRenderDescriptor
	{
		unsigned int modelId;
		std::optional<unsigned int> imageId;
	};

	struct RenderDescriptor
	{
		RenderType renderType;
		std::variant<BillboardRenderDescriptor, MeshRenderDescriptor> descriptorData;
	};
}