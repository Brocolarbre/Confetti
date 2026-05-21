#pragma once

namespace cft
{
	class Mesh
	{
	private:
		unsigned int m_vao;
		unsigned int m_vbo;

	public:
		Mesh();
		~Mesh();

		void draw() const;
		void drawInstanced(unsigned int instanceCount) const;
	};
}