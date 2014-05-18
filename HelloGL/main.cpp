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
        +1.0, +1.0, -0.0, +1.0, +1.0, +1.0,
        -1.0, +1.0, -0.0, +1.0, +0.0, +1.0,
        -1.0, -1.0, -0.0, +1.0, +0.0, +0.0,
        +1.0, -1.0, -0.0, +1.0, +1.0, +0.0
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    
    GLuint myEBO;
    glGenBuffers(1, &myEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO);
    
    GLushort indexData[] = {
        0, 1, 2,
        0, 2, 3,
    };
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
    
    GLuint myVAO;
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);
    
    GLint positionLoc = program->getAttribLoc("position");
    GLint texcoordLoc = program->getAttribLoc("texcoord");
    
    glEnableVertexAttribArray(positionLoc);
    glEnableVertexAttribArray(texcoordLoc);
    
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glVertexAttribPointer(positionLoc, 4, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat),(GLvoid*) (0*sizeof(GLfloat)));
    glVertexAttribPointer(texcoordLoc, 2, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat),(GLvoid*) (4*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    glBindVertexArray(NULL);
    
    GLint colorLoc = program->getUniformLoc("color");
    GLint texLoc = program->getUniformLoc("tex");
    
    GLint modelLoc = program->getUniformLoc("uMMatrix");
    GLint projectionLoc = program->getUniformLoc("uPMatrix");
    GLint viewLoc = program->getUniformLoc("uVMatrix");
    
    GLuint texture = TextureUtils::createTexture("texture.jpg");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glUniform1i(texLoc,0);
    glUniform4f(colorLoc, 1.0, 1.0, 1.0, 1.0);
    

    //drawloop
    while(!window->shouldClose()){
        glViewport(0, 0, window->getFrameBufferWidth(), window->getFrameBufferHeight());
        glClear(GL_COLOR_BUFFER_BIT);
        
        float aspect = (float)window->getFrameBufferHeight()/window->getFrameBufferHeight();
        
        
        glm::mat4 projectionMat = glm::perspective(60.0f, aspect, 0.01f, 100.0f);
        glm::mat4 viewMat = glm::mat4();
        glm::mat4 modelMat = glm::mat4();
        modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, -2.0f));
        
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
        
        glBindVertexArray(myVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
        glBindVertexArray(NULL);
        
        glfwPollEvents();
        window->swapBuffers();
    }
    
    glDeleteBuffers(1, &myEBO);
    glDeleteBuffers(1, &myVBO);
    delete window;
    delete program;
    glfwTerminate();
    return 0;
}