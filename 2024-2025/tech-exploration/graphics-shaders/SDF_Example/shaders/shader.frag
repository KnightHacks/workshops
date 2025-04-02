#version 330 core
out vec4 fragColor;
in vec2 fragCoord;

uniform vec2 iResolution;
uniform float iTime;

void main()	{
    vec2 uv = (fragCoord + 1) / 2;
    float pct = 0.0;

    // bottom-left, basically getting the distance to the center from the UV
    pct = distance(uv,vec2(0.5));

    //Black and white, while also creating a gradient
    vec3 color = vec3(pct);

    //output
    fragColor = vec4(color,1.0);
}