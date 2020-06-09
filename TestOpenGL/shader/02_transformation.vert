#version 330 core

layout (location = 0) in vec3 a_pos;
// layout (location = 1) in vec3 a_color;
layout (location = 1) in vec2 a_texCoord;

// out vec3 o_color;
out vec2 o_texCoord;

uniform mat4 u_transform;

void main() {
    gl_Position = u_transform * vec4(a_pos, 1.0f);
    // gl_PointSize = 10.0f;
    // o_color = a_color;
    o_texCoord = a_texCoord;
}

