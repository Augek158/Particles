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

#define VIEW_LOC 0
#define TIME_LOC 0
#define MODEL_LOC 4
#define PROJECTION_LOC 8

// Buffer holds maximum 1 million particles.
#define MAX_BUFFER_SIZE 1000000

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
    Camera cam;
    
    GLuint vao;
    GLuint vbo[3];
    GLuint particles;
    GLuint frameCount;
    GLuint batchSize;
    GLuint interval;

    void update();
    void draw();
    void setUniforms();
    void spawnParticles();
public:
    Renderer(GLuint batchSize, GLuint interval);
    ~Renderer();
    void initWindow();
    void initShaderPrograms();
    void initBuffers();
    void initCamera();
    bool render();
};


#endif /* defined(__HelloGL__Renderer__) */
