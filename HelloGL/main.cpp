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

const int SIZE = 100;
const int BATCH_SIZE = 20;

GLfloat* getColorData(int size){

    int bufferSize = 4*4*size;
    GLfloat* buffer = new GLfloat[bufferSize];
    
    for(int i = 0; i < bufferSize; i+=16){
        for(int j = i; j < i+15; j+=4){
            double color = (double)rand()/ RAND_MAX;
            buffer[j] = color;
            buffer[j + 1] = color;
            buffer[j + 2] = color;
            buffer[j + 3] = 1.0f;
        }
    }
    return buffer;
}

GLfloat* getPositionData(int size){
    
    int bufferSize = 4*size;
    GLfloat* buffer = new GLfloat[bufferSize];
    for(int i = 0; i < bufferSize; i+=4){
        buffer[i] =  -10 + (float)(rand() % 10);
        buffer[i+1] = -10 + (float)(rand() % 10);
        buffer[i+2] = -10 + (float)(rand() % 5);
        buffer[i+3] = 1.0f;
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
    
    GLuint myVAO;
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);
    
    // init Vertices
    GLuint myVBO[3];
    glGenBuffers(3, myVBO);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[0]);
    
    GLfloat vertexData[] = {
        +0.3, +0.3, -0.0, +1.0,
        -0.3, +0.3, -0.0, +1.0,
        +0.3, -0.3, -0.0, +1.0,
        -0.3, -0.3, -0.0, +1.0,
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    
    GLint vertexLoc = program->getAttribLoc("aVertex");
    
    // init Colors
    
    GLfloat colorData[] = {
        +1.0, +0.0, +0.0, +1.0,
        +1.0, +0.0, +0.0, +1.0,
        +1.0, +0.0, +0.0, +1.0,
        +1.0, +0.0, +0.0, +1.0,
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
    GLint colorLoc = program->getAttribLoc("aColor");
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);
    
    GLfloat* positionData = getPositionData(SIZE);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[2]);
    glBufferData(GL_ARRAY_BUFFER, 4 * SIZE * sizeof(GL_FLOAT), positionData, GL_STATIC_DRAW);
    GLint positionLoc = program->getAttribLoc("aPosition");
    glVertexAttribPointer(positionLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionLoc);
    glVertexAttribDivisor(positionLoc, 1);
    
    
//    std::cout<<myVAO<<std::endl;
    
    

    
    
    /*
    GLuint colorBuffer;
    GLfloat* colorData = getColorData(10);
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, SIZE * 4 * sizeof(GLfloat), colorData, GL_STREAM_DRAW);
    
    
    glEnableVertexAttribArray(colorLoc);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
      */
    
    
    GLint modelLoc = program->getUniformLoc("uMMatrix");
    GLint projectionLoc = program->getUniformLoc("uPMatrix");
    GLint viewLoc = program->getUniformLoc("uVMatrix");

    
    float aspect = (float)window->getFrameBufferWidth()/(float)window->getFrameBufferHeight();
    glm::mat4 projectionMat = glm::perspective(45.0f, aspect, 0.01f, 100.0f);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));

    glm::mat4 viewMat = glm::mat4();
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    
    glm::mat4 modelMat = glm::mat4();
    
    //drawloop
        modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, -10.0f));
    while(!window->shouldClose()){
        window->setWindowFPS();
        glViewport(0, 0, window->getFrameBufferWidth(), window->getFrameBufferHeight());
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Send Positions
        glEnableVertexAttribArray(vertexLoc);
        glBindBuffer(GL_ARRAY_BUFFER, myVBO[0]);
        glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat),(GLvoid*) (0*sizeof(GLfloat)));
        
        // Send Colors
        glEnableVertexAttribArray(colorLoc);
        glBindBuffer(GL_ARRAY_BUFFER, myVBO[1]);
        glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);

        glEnableVertexAttribArray(positionLoc);
        glBindBuffer(GL_ARRAY_BUFFER, myVBO[2]);
        glVertexAttribPointer(positionLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, SIZE);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));


        
//        container->spawn();
//        container->draw();

        glfwPollEvents();
        window->swapBuffers();
    }
    
    glDeleteBuffers(2, myVBO);
    glDeleteVertexArrays(1, &myVAO);
    delete window;
    delete program;
    glfwTerminate();
    return 0;
}