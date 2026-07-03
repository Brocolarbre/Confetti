#pragma once

namespace cft
{
    constexpr const char* BLOOM_UPSAMPLE_FRAGMENT_SHADER_SOURCE = R"(
		#version 460 core

        uniform sampler2D uTexture;
        uniform float uFilterRadius;

        in vec2 fTextureCoordinates;

        out vec4 upsample;

        void main()
        {
            ivec2 size = textureSize(uTexture, 0);

            float x = uFilterRadius * float(size.y) / float(size.x);
            float y = uFilterRadius;

            vec4 a = texture(uTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y + y)).rgba;
            vec4 b = texture(uTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y + y)).rgba;
            vec4 c = texture(uTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y + y)).rgba;

            vec4 d = texture(uTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y)).rgba;
            vec4 e = texture(uTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y)).rgba;
            vec4 f = texture(uTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y)).rgba;

            vec4 g = texture(uTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y - y)).rgba;
            vec4 h = texture(uTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y - y)).rgba;
            vec4 i = texture(uTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y - y)).rgba;

            upsample = e * 4.0;
            upsample += (b + d + f + h) * 2.0;
            upsample += (a + c + g + i);
            upsample *= 1.0 / 16.0;
        }
	)";
}