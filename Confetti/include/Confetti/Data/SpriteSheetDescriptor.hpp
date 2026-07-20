#pragma once

namespace cft
{
	struct SpriteSheetDescriptor
	{
		unsigned int imageId;
		unsigned int frameCount;
		unsigned int rowFrameCount;
		unsigned int frameWidth;
		unsigned int frameHeight;
		float animationSpeed;
	};
}