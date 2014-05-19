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
#include "Container.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int SIZE = 200;
const int BATCH_SIZE = 200;

GLfloat* getColorData(int size){
    GLfloat* buffer = new GLfloat[4*size];
    int bufferSize = 4*size;
    
    for (int i = 0; i < bufferSize; i+=4){
        
        for (int j = i; j < i+3; j++) {
            buffer[j] = (double)rand() / RAND_MAX;
        }

        if(i+4 <= bufferSize){
            buffer[i+3] = 1.0;
        }
    }
    return buffer;
}

int main(int argc, const char *argv[]){
    
    Window* window = new Window(640, 360, "Modern OpenGL");
    ShaderProgram* program;
    Shader* vertexShader;
    Shader* fragmentShader;
    
    window->makeContextCurrent();
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    program = new ShaderProgram();
    vertexShader = new Shader("MyVertexShader.vs", GL_VERTEX_SHADER);
    fragmentShader = new Shader("MyFragmentShader.fs", GL_FRAGMENT_SHADER);
    
    program->attachShader(vertexShader);
    program->attachShader(fragmentShader);
    
    program->bindFragDataLocation(0, "fragData");
    program->link();
    program->use();
    
    delete vertexShader;
    delete fragmentShader;
    
    
    std::cout << glGetString(GL_VERSION) << std::endl;
    
    //init Buffers
    GLuint myVBO;
    glGenBuffers(1, &myVBO);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    
    GLfloat bufferData[] = {
        +0.3, +0.3, -0.0, +1.0,
        -0.3, +0.3, -0.0, +1.0,
        +0.3, -0.3, -0.0, +1.0,
        -0.3, -0.3, -0.0, +1.0,
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    
    GLuint myVAO;
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);
    
    GLint positionLoc = program->getAttribLoc("aPosition");
    
    glEnableVertexAttribArray(positionLoc);
    
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glVertexAttribPointer(positionLoc, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat),(GLvoid*) (0*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    glBindVertexArray(NULL);
    
    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, SIZE * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
//    glBufferData(GL_ARRAY_BUFFER, SIZE * 4 * sizeof(GLubyte), , GL_STREAM_DRAW);
    
    
    GLint modelLoc = program->getUniformLoc("uMMatrix");
    GLint projectionLoc = program->getUniformLoc("uPMatrix");
    GLint viewLoc = program->getUniformLoc("uVMatrix");

    
    float aspect = (float)window->getFrameBufferWidth()/(float)window->getFrameBufferHeight();
    glm::mat4 projectionMat = glm::perspective(45.0f, aspect, 0.01f, 100.0f);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));

    glm::mat4 viewMat = glm::mat4();
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    
    Container* container = new Container(SIZE, BATCH_SIZE, myVAO, modelLoc);

    //drawloop
    while(!window->shouldClose()){
        window->setWindowFPS();
        glViewport(0, 0, window->getFrameBufferWidth(), window->getFrameBufferHeight());
        glClear(GL_COLOR_BUFFER_BIT);
        container->spawn();
        container->draw();

        glfwPollEvents();
        window->swapBuffers();
    }
    
    glDeleteBuffers(1, &myVBO);
    delete window;
    delete program;
    glfwTerminate();
    return 0;
}