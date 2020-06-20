#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 normal;
out vec3 fragPos;


void main() {
    // 注意乘法要从右向左读
    gl_Position = u_projection * u_view * u_model * vec4(a_pos, 1.0f);
    normal = mat3(transpose(inverse(u_model))) * a_normal;
    fragPos = a_pos;
}

