#version 330 core

out vec4 FragColor;

//in vec3 o_color;
in vec2 o_texCoord;

uniform sampler2D ourTexture;

void main(){
    // FragColor = vec4(o_color, 1.0f);
    FragColor = texture(ourTexture, o_texCoord);
}
