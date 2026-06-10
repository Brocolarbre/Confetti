#pragma once

namespace cft
{
	class ParticleMesh
	{
	private:
		unsigned int m_vao;
		unsigned int m_vbo;

	public:
		ParticleMesh();
		~ParticleMesh();

		void draw() const;
		void drawInstanced(unsigned int instanceCount) const;
	};
}