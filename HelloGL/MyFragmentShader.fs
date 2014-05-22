#version 150 core

in vec3 vColor;

out vec4 fragData;

void main(){
    fragData = vec4(vColor, 1.0);
}