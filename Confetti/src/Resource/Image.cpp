#include "Confetti/Resource/Image.hpp"

#include <stb_image.h>
#include <iostream>

namespace cft
{
	unsigned int Image::getWidth() const
	{
		return m_width;
	}

	unsigned int Image::getHeight() const
	{
		return m_height;
	}

	unsigned int Image::getChannelCount() const
	{
		return m_channelCount;
	}

	const std::vector<std::byte>& Image::getData() const
	{
		return m_data;
	}

	void Image::loadFromFile(const std::string& path)
	{
		const std::string suffix(".png");
		if (path.size() >= suffix.size() && path.compare(path.size() - suffix.size(), suffix.size(), suffix) == 0)
			stbi_set_flip_vertically_on_load(true);

		int width, height, channelCount;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channelCount, 0);
		if (data == nullptr)
		{
			std::cerr << "Failed to load image at '" << path << "'" << std::endl;
			return;
		}

		m_data = std::vector<std::byte>(reinterpret_cast<std::byte*>(data), reinterpret_cast<std::byte*>(data + width * height * channelCount));
		m_width = static_cast<unsigned int>(width);
		m_height = static_cast<unsigned int>(height);
		m_channelCount = static_cast<unsigned int>(channelCount);

		stbi_image_free(data);
		stbi_set_flip_vertically_on_load(false);
	}

	void Image::loadFromMemory(unsigned int width, unsigned int height, unsigned int channelCount, std::vector<std::byte> data)
	{
		m_width = width;
		m_height = height;
		m_channelCount = channelCount;

		m_data = std::move(data);
	}
}