#pragma once

namespace cft
{
	class BillboardParticleMesh
	{
	private:
		unsigned int m_vao;
		unsigned int m_vbo;

	public:
		BillboardParticleMesh();
		~BillboardParticleMesh();

		void draw() const;
		void drawInstanced(unsigned int count) const;
	};
}