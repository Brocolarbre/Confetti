#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

namespace cft
{
	class Shader
	{
	private:
		unsigned int m_id;
		std::unordered_map<std::string, int> m_uniformLocations;
		
		std::string loadShaderSource(const std::string& path) const;
		unsigned int createShader(const std::string& source, unsigned int type) const;
		void bakeUniformLocations();

	public:
		Shader();
		Shader(const Shader& shader) = delete;
		Shader(Shader&& shader) noexcept;
		~Shader();

		Shader& operator=(const Shader& shader) = delete;
		Shader& operator=(Shader&& shader) noexcept;

		void loadFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		void loadFromMemory(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

		void setUniform(const std::string& name, bool value) const;
		void setUniform(const std::string& name, int value) const;
		void setUniform(const std::string& name, unsigned int value) const;
		void setUniform(const std::string& name, float value) const;
		void setUniform(const std::string& name, double value) const;
		void setUniform(const std::string& name, const glm::vec2& value) const;
		void setUniform(const std::string& name, const glm::vec3& value) const;
		void setUniform(const std::string& name, const glm::vec4& value) const;
		void setUniform(const std::string& name, const glm::mat2& value) const;
		void setUniform(const std::string& name, const glm::mat3& value) const;
		void setUniform(const std::string& name, const glm::mat4& value) const;

		void use() const;
	};
}