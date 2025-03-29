#version 330 core
uniform vec2 iCenter;
uniform float iRadius;
uniform vec2 iResolution;

in vec2 fragCoord;
out vec4 fragColor;

void main() {
    vec2 pixelCoord = (fragCoord * 0.5 + 0.5) * iResolution;

    float l = length(pixelCoord-iCenter);
    if (l < iRadius) {
        fragColor = vec4(1.0, 0.0, 0.0, 1.0);
    } else {
        fragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
}