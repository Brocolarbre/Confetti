#pragma once

namespace cft
{
    constexpr const char* FULLSCREEN_VERTEX_SHADER_SOURCE = R"(
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
}