//
//  Renderer.h
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-23.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#ifndef __HelloGL__Renderer__
#define __HelloGL__Renderer__

#define GLFW_INCLUDE_GLCOREARB
#define viewLoc 0
#define modelLoc 4
#define projectionLoc 8

#include <iostream>
#include <cmath>
#include "Shader.h"
#include "ShaderProgram.h"
#include "TextureUtils.h"
#include "Window.h"
#include "Container.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Physics.h"

class Renderer {
enum{
    PROTO_VBO,
    DATA_VBO,
    TRANSFORM_VBO
};
enum{
    VERTEX_LOC,
    POSITION_LOC,
    VELOCITY_LOC
};
    
private:
    Window* window;
    ShaderProgram* renderProgram;
    ShaderProgram* transformProgram;
    Container* container;
    GLuint vao;
    GLuint vbo[3];
    int particles;
    Camera cam;
    
    void update();
    void draw();
    void setUniforms();
public:
    Renderer(int startingParticles);
    ~Renderer();
    void initWindow();
    void initShaderPrograms();
    void initBuffers();
    void initCamera();
    bool render();
};


#endif /* defined(__HelloGL__Renderer__) */
