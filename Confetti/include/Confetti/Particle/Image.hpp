#pragma once

#include <string>
#include <vector>

namespace cft
{
	class Image
	{
	private:
		unsigned int m_width = 0;
		unsigned int m_height = 0;

		std::vector<std::byte> m_data;

	public:
		unsigned int getWidth() const;
		unsigned int getHeight() const;

		const std::vector<std::byte>& getData() const;

		void loadFromFile(const std::string& path);
		void loadFromMemory(unsigned int width, unsigned int height, std::vector<std::byte> data);
	};
}