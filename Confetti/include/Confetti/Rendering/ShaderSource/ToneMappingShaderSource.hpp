#pragma once

namespace cft
{
    constexpr const char* TONEMAPPING_FRAGMENT_SHADER_SOURCE = R"(
        #version 330 core
        
        uniform sampler2D uTexture;
        uniform float uExposure;
        uniform float uGamma;
        
        in vec2 fTextureCoordinates;
        
        out vec4 color;
        
        void main()
        {
            vec3 textureColor = texture(uTexture, fTextureCoordinates).rgb;
            vec3 mappedColor = vec3(1.0) - exp(-textureColor * uExposure);
            mappedColor = pow(mappedColor, vec3(1.0 / uGamma));
            color = vec4(mappedColor, 1.0);
        }
    )";
}