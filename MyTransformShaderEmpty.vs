#version 330 core

layout(location = 1) in vec4 aPosition;
layout(location = 2) in vec3 aVelocity;

out vec4 vPosition;
out vec3 vVelocity;


void main(){


        vPosition = aPosition;
        vVelocity = aVelocity;
}