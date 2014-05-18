#version 150 core

uniform vec4 color;
uniform sampler2D tex;

in vec2 Texcoord;
out vec4 fragData;

void main(){
    fragData = color * texture(tex, Texcoord);
}