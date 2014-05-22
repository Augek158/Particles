//
//  main.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-04.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#define GLFW_INCLUDE_GLCOREARB
#include <iostream>
#include <cmath>
#include "Shader.h"
#include "ShaderProgram.h"
#include "TextureUtils.h"
#include "Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint protoVBO = 0;
GLuint dataVBO = 1;
GLuint transVBO = 2;

void initUniforms(ShaderProgram* RenderProgram, Window* window){
    
    GLint modelLoc = RenderProgram->getUniformLoc("uMMatrix");
    GLint projectionLoc = RenderProgram->getUniformLoc("uPMatrix");
    GLint viewLoc = RenderProgram->getUniformLoc("uVMatrix");
    
    float aspect = (float)window->getFrameBufferWidth()/window->getFrameBufferHeight();
    
    glm::mat4 projectionMat = glm::perspective(60.0f, aspect, 0.01f, 100.0f);
    glm::mat4 viewMat = glm::mat4();
    glm::mat4 modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, -2.0f));
    
    
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    
    
}

int main(int argc, const char *argv[]){
    
    Window* window = new Window(640, 360, "Particles");
    ShaderProgram* RenderProgram;
    ShaderProgram* TransformProgram;
    
    Shader* transformShader;
    Shader* vertexShader;
    Shader* fragmentShader;
    
    window->makeContextCurrent();
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    RenderProgram = new ShaderProgram();
    vertexShader = new Shader("MyVertexShader.vs", GL_VERTEX_SHADER);
    fragmentShader = new Shader("MyFragmentShader.fs", GL_FRAGMENT_SHADER);
    
    RenderProgram->attachShader(vertexShader);
    RenderProgram->attachShader(fragmentShader);
    
    RenderProgram->bindFragDataLocation(0, "fragData");
    RenderProgram->link();
    
    
    
    // Initalizing TransformShader
    TransformProgram = new ShaderProgram();
    transformShader = new Shader("MyTransformShader.vs", GL_VERTEX_SHADER);
    
    TransformProgram->attachShader(transformShader);
    const GLchar* feedbackVaryings[] = {"vPosition", "vVelocity"};
    glTransformFeedbackVaryings(TransformProgram->getProgramID(), 2, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
    
    TransformProgram->link();
    TransformProgram->use();
    
    GLuint myVAO;
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);
    
    
    delete transformShader;
    delete vertexShader;
    delete fragmentShader;
    
    
    std::cout << glGetString(GL_VERSION) << std::endl;
    
    GLuint vbo[3];
    glGenBuffers(3, vbo);
    
    GLfloat prototypeData[] = {
        0.5, 0.5, -0.0
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[protoVBO]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(prototypeData), prototypeData , GL_STATIC_DRAW);
    
    // First 4 values = position, last 3 = velocity
    GLfloat particleData[] = {
        -1.0, +0.5, -0.0, +1.0, 0.0,-1.0, 0.0,
        -0.5, +0.5, -0.0, +1.0, 0.0,-1.0, 0.0,
        +0.0, +0.5, -0.0, +1.0, 0.0,-1.0, 0.0,
        +0.5, +0.5, -0.0, +1.0, 0.0,-1.0, 0.0,
    };
    
    int size = sizeof(particleData)/sizeof(GLfloat);
    int numParticles = size/7;
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[dataVBO]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particleData), particleData, GL_STATIC_DRAW);
    
    glPointSize(3.0f);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[transVBO]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particleData), nullptr, GL_DYNAMIC_COPY);
    
    
    
    while(!window->shouldClose()){
        
        TransformProgram->use();
        
        glEnable(GL_RASTERIZER_DISCARD);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo[dataVBO]);
        glEnableVertexAttribArray(1);
        glVertexAttribDivisor(1, 0);

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), 0);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)( 4 * sizeof(GL_FLOAT)));
        
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo[transVBO]);
        
        glBeginTransformFeedback(GL_POINTS);
        glDrawArrays(GL_POINTS, 0, size);
        glEndTransformFeedback();
        
        std::swap(vbo[dataVBO],vbo[transVBO]);
        
        glDisable(GL_RASTERIZER_DISCARD);
        RenderProgram->use();
        
        initUniforms(RenderProgram, window);
        glViewport(0, 0, window->getFrameBufferWidth(), window->getFrameBufferHeight());
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo[protoVBO]);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo[dataVBO]);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), 0);
        glVertexAttribDivisor(1, 1);
        
        glDrawArraysInstanced(GL_POINTS, 0, 1, numParticles);
        
        glfwPollEvents();
        window->swapBuffers();
    }
    
    delete window;
    delete RenderProgram;
    delete TransformProgram;
    glDeleteBuffers(3, vbo);
    glfwTerminate();
    return 0;
}