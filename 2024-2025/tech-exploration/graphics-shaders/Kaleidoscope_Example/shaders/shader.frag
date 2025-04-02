#version 330 core
uniform float iTime;  // Time passed since the start of the program
in vec2 fragCoord;  // The coordinates from the vertex shader
out vec4 fragColor;

vec3 palette(float t){
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263, 0.416, 0.557);
    return a + b*cos( 6.28318*(c*t+d) );
}

void main() {
    // Normalize the frag coordinates to [0, 1] range
    vec2 uv = fragCoord;  // [0, 1] coordinate system
    vec3 finalColor = vec3(0.0);

    for (float i = 0.0; i < 4.0; i++) {
        uv = fract(uv * 1.5) - 0.5;
        
        float d = length(uv) * exp(-length(fragCoord));

        vec3 col = palette(length(fragCoord) + iTime*.4);

        d = sin(d*8. + iTime) / 8.;
        d = abs(d);

        d = pow(0.01 / d, 1.2);

        finalColor += col*d;
    }
    // Set the fragment color based on the normalized uv
    fragColor = vec4(finalColor, 1.0);  // Just use uv.x and uv.y to affect the color
}
