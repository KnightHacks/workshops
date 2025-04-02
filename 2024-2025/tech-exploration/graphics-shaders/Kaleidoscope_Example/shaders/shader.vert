#version 330 core
layout(location = 0) in vec3 aPos; //Take position given from VBO
out vec2 fragCoord;

void main() {
    gl_Position = vec4(aPos, 1.0); //Set position
    fragCoord = aPos.xy;
}