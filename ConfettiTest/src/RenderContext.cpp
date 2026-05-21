#include "RenderContext.hpp"

#include <glad/glad.h>
#include <iostream>

namespace
{
    constexpr const char* VERTEX_SHADER_SOURCE = R"(
        #version 460 core
        
        const vec2 vertexPositions[] = vec2[](
            vec2(-1.0, -1.0),
            vec2(1.0, -1.0),
            vec2(-1.0, 1.0),
            vec2(1.0, 1.0)
        );
        
        out vec2 fTextureCoordinates;
        
        void main()
        {
            vec2 vertexPosition = vertexPositions[gl_VertexID];
            gl_Position = vec4(vertexPosition, 0.0, 1.0);
            fTextureCoordinates = vertexPosition * 0.5 + 0.5;
        }
    )";

    constexpr const char* FRAGMENT_SHADER_SOURCE = R"(
        #version 460 core
        
        in vec2 fTextureCoordinates;
        
        out vec4 color;
        
        uniform sampler2D uTexture;
        
        void main()
        {
            color = vec4(texture(uTexture, fTextureCoordinates).rgb, 1.0);
        }
    )";
}

bool RenderContext::m_initialized = false;

RenderContext::RenderContext(unsigned int width, unsigned int height) :
    m_shader(),
    m_vertexArray(0),
    m_width(width),
    m_height(height)
{
    glGenVertexArrays(1, &m_vertexArray);
    m_shader.loadFromMemory(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
}

RenderContext::~RenderContext()
{
    glDeleteVertexArrays(1, &m_vertexArray);
}

void RenderContext::resize(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;
}

void RenderContext::render(unsigned int outputTextureId) const
{
    while (GLenum error = glGetError())
        std::cerr << "OpenGL error : " << error << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, outputTextureId);

    m_shader.use();
    m_shader.setUniform("uTexture", 0);

    glBindVertexArray(m_vertexArray);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

bool RenderContext::initialize(void* loader)
{
    if (m_initialized)
        return true;

    if (!gladLoadGLLoader(static_cast<GLADloadproc>(loader)))
        m_initialized = true;

    return m_initialized;
}