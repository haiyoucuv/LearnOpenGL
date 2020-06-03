#version 330 core

out vec4 FragColor;

in vec3 o_color;

uniform float u_ourColor;

void main(){
    // FragColor = vec4(o_color.x, o_color.y, o_color.z, 1.0f);
    FragColor = vec4(o_color.x, u_ourColor, o_color.z, 1.0f);
}
