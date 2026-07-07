#pragma once

namespace cft
{
    constexpr const char* BLOOM_DOWNSAMPLE_FRAGMENT_SHADER_SOURCE = R"(
		#version 460 core

        uniform sampler2D uTexture;

        in vec2 fTextureCoordinates;

        out vec4 downsample;

        void main()
        {
            vec2 texelSize = 1.0 / textureSize(uTexture, 0);
            float x = texelSize.x;
            float y = texelSize.y;

            vec4 a = texture(uTexture, vec2(fTextureCoordinates.x - 2 * x, fTextureCoordinates.y + 2 * y)).rgba;
            vec4 b = texture(uTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y + 2 * y)).rgba;
            vec4 c = texture(uTexture, vec2(fTextureCoordinates.x + 2 * x, fTextureCoordinates.y + 2 * y)).rgba;

            vec4 d = texture(uTexture, vec2(fTextureCoordinates.x - 2 * x, fTextureCoordinates.y)).rgba;
            vec4 e = texture(uTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y)).rgba;
            vec4 f = texture(uTexture, vec2(fTextureCoordinates.x + 2 * x, fTextureCoordinates.y)).rgba;

            vec4 g = texture(uTexture, vec2(fTextureCoordinates.x - 2 * x, fTextureCoordinates.y - 2 * y)).rgba;
            vec4 h = texture(uTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y - 2 * y)).rgba;
            vec4 i = texture(uTexture, vec2(fTextureCoordinates.x + 2 * x, fTextureCoordinates.y - 2 * y)).rgba;

            vec4 j = texture(uTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y + y)).rgba;
            vec4 k = texture(uTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y + y)).rgba;
            vec4 l = texture(uTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y - y)).rgba;
            vec4 m = texture(uTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y - y)).rgba;

            downsample = e * 0.125;
            downsample += (a + c + g + i) * 0.03125;
            downsample += (b + d + f + h) * 0.0625;
            downsample += (j + k + l + m) * 0.125;
        }
	)";

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