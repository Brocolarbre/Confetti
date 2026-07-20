#include "Confetti/Rendering/Tool/Shader.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

namespace cft
{
	std::string Shader::loadShaderSource(const std::string& path) const
	{
		std::ifstream file(path);

		if (!file.is_open())
		{
			std::cerr << "Failed to open shader at '" << path << "'" << std::endl;
			return {};
		}

		std::ostringstream stream;
		stream << file.rdbuf();

		return stream.str();
	}

	unsigned int Shader::createShader(const std::string& source, unsigned int type) const
	{
		unsigned int shader = glCreateShader(type);

		const char* shaderSource = source.c_str();
		glShaderSource(shader, 1, &shaderSource, nullptr);

		glCompileShader(shader);

		int compileStatus = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

		if (!compileStatus)
		{
			int infoLogLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			std::string infoLog(infoLogLength, ' ');
			glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog.data());

			std::string shaderType;
			switch (type)
			{
			case GL_VERTEX_SHADER: shaderType = "vertex"; break;
			case GL_FRAGMENT_SHADER: shaderType = "fragment"; break;
			}

			std::cerr << "Failed to compile " << shaderType << " shader : " << infoLog << std::endl;
			return 0;
		}

		return shader;
	}

	void Shader::bakeUniformLocations()
	{
		int activeUniforms = 0;
		glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &activeUniforms);

		int activeUniformMaxLength = 0;
		glGetProgramiv(m_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &activeUniformMaxLength);

		for (int i = 0; i < activeUniforms; ++i)
		{
			int length = 0;
			int size = 0;
			unsigned int type = 0;
			std::string uniformName(activeUniformMaxLength, ' ');

			glGetActiveUniform(m_id, i, activeUniformMaxLength, &length, &size, &type, uniformName.data());
			uniformName.resize(length);
			m_uniformLocations[uniformName] = glGetUniformLocation(m_id, uniformName.c_str());
		}
	}

	int Shader::getUniformLocation(const std::string& name) const
	{
		std::unordered_map<std::string, int>::const_iterator iterator = m_uniformLocations.find(name);

		if (iterator == m_uniformLocations.end())
			return -1;

		return iterator->second;
	}

	Shader::Shader() :
		m_id(0),
		m_uniformLocations()
	{
		
	}

	Shader::Shader(Shader&& shader) noexcept :
		m_id(shader.m_id),
		m_uniformLocations(std::move(shader.m_uniformLocations))
	{
		shader.m_id = 0;
	}

	Shader::~Shader()
	{
		if (m_id != 0)
			glDeleteProgram(m_id);
	}

	Shader& Shader::operator=(Shader&& shader) noexcept
	{
		if (&shader == this)
			return *this;

		if (m_id != 0)
			glDeleteProgram(m_id);

		m_id = shader.m_id;
		m_uniformLocations = std::move(shader.m_uniformLocations);

		shader.m_id = 0;

		return *this;
	}

	void Shader::loadFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		std::string vertexShaderSource = loadShaderSource(vertexShaderPath);
		std::string fragmentShaderSource = loadShaderSource(fragmentShaderPath);

		loadFromMemory(vertexShaderSource, fragmentShaderSource);
	}

	void Shader::loadFromMemory(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
	{
		unsigned int vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
		unsigned int fragmentShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

		m_id = glCreateProgram();

		glAttachShader(m_id, vertexShader);
		glAttachShader(m_id, fragmentShader);

		glLinkProgram(m_id);

		int linkStatus = 0;
		glGetProgramiv(m_id, GL_LINK_STATUS, &linkStatus);

		if (!linkStatus)
		{
			int infoLogLength = 0;
			glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

			std::string infoLog(infoLogLength, ' ');
			glGetProgramInfoLog(m_id, infoLogLength, nullptr, infoLog.data());

			std::cerr << "Failed to link shader : " << infoLog << std::endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		if (m_id != 0)
			bakeUniformLocations();
	}

	void Shader::setUniform(const std::string& name, bool value) const
	{
		GLint uniformLocation = getUniformLocation(name);

		if (uniformLocation >= 0)
			glUniform1i(m_uniformLocations.at(name), static_cast<int>(value));
	}

	void Shader::setUniform(const std::string& name, int value) const
	{
		GLint uniformLocation = getUniformLocation(name);

		if (uniformLocation >= 0)
			glUniform1i(uniformLocation, value);
	}

	void Shader::setUniform(const std::string& name, unsigned int value) const
	{
		GLint uniformLocation = getUniformLocation(name);

		if (uniformLocation >= 0)
			glUniform1ui(uniformLocation, value);
	}

	void Shader::setUniform(const std::string& name, float value) const
	{
		GLint uniformLocation = getUniformLocation(name);

		if (uniformLocation >= 0)
			glUniform1f(uniformLocation, value);
	}

	void Shader::setUniform(const std::string& name, double value) const
	{
		GLint uniformLocation = getUniformLocation(name);

		if (uniformLocation >= 0)
			glUniform1d(uniformLocation, value);
	}

	void Shader::setUniform(const std::string& name, const glm::vec2& value) const
	{
		GLint uniformLocation = getUniformLocation(name);

		if (uniformLocation >= 0)
			glUniform2f(uniformLocation, value.x, value.y);
	}

	void Shader::setUniform(const std::string& name, const glm::vec3& value) const
	{
		GLint uniformLocation = getUniformLocation(name);

		if (uniformLocation >= 0)
			glUniform3f(uniformLocation, value.x, value.y, value.z);
	}

	void Shader::setUniform(const std::string& name, const glm::vec4& value) const
	{
		GLint uniformLocation = getUniformLocation(name);

		if (uniformLocation >= 0)
			glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
	}

	void Shader::setUniform(const std::string& name, const glm::mat2& value) const
	{
		GLint uniformLocation = getUniformLocation(name);

		if (uniformLocation >= 0)
			glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::setUniform(const std::string& name, const glm::mat3& value) const
	{
		GLint uniformLocation = getUniformLocation(name);

		if (uniformLocation >= 0)
			glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::setUniform(const std::string& name, const glm::mat4& value) const
	{
		GLint uniformLocation = getUniformLocation(name);

		if (uniformLocation >= 0)
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::use() const
	{
		glUseProgram(m_id);
	}
}