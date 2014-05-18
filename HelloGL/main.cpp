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

void initTriangleParemeters(GLuint VAO){
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(NULL);
    
}

GLfloat getPosY(){
    return fmod(glfwGetTime(), 11.0f);
}


const int SIZE = 30;

glm::vec3* initPosArray(const int size){
    
    glm::vec3* arr = new glm::vec3[size];
    for(int i = 0; i < size; i++){
        arr[i] = glm::vec3((float)(rand() % 10), 13.0f, 1.0f);
    }
    return arr;
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
        +0.0, +1.0, -0.0, +1.0,
        -1.0, -1.0, -0.0, +1.0,
        +1.0, -1.0, -0.0, +1.0,
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    
    GLuint myVAO;
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);
    
    GLint positionLoc = program->getAttribLoc("position");
    
    glEnableVertexAttribArray(positionLoc);
    
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat),(GLvoid*) (0*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    glBindVertexArray(NULL);
    
    GLint colorLoc = program->getUniformLoc("color");
    
    GLint modelLoc = program->getUniformLoc("uMMatrix");
    GLint projectionLoc = program->getUniformLoc("uPMatrix");
    GLint viewLoc = program->getUniformLoc("uVMatrix");
    
    glUniform4f(colorLoc, 1.0, 1.0, 1.0, 1.0);
    
    float aspect = (float)window->getFrameBufferHeight()/window->getFrameBufferHeight();
    glm::mat4 projectionMat = glm::perspective(60.0f, aspect, 0.01f, 100.0f);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));

    glm::mat4 viewMat = glm::mat4();
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    
    glm::vec3* startingPositions = initPosArray(SIZE);
    
    for (int i = 0; i < SIZE; i++) {
        std::cout << startingPositions[i].x << " " << startingPositions[i].y << std::endl;
    }

    //drawloop
    while(!window->shouldClose()){
        glViewport(0, 0, window->getFrameBufferWidth(), window->getFrameBufferHeight());
        glClear(GL_COLOR_BUFFER_BIT);
        
        glm::mat4 modelMat = glm::mat4();
        
        modelMat = glm::mat4();
        initTriangleParemeters(myVAO);
        modelMat = glm::translate(modelMat, glm::vec3(0.0, 13.0f - 2.5*getPosY(), -20.0f));
        modelMat = glm::rotate(modelMat, 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
        
        
        glfwPollEvents();
        window->swapBuffers();
    }
    
    glDeleteBuffers(1, &myVBO);
    delete window;
    delete program;
    glfwTerminate();
    return 0;
}