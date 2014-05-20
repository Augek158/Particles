
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
#include "Camera.h"

int size = 10;
const int BATCH_SIZE = 10;

int main(int argc, const char *argv[]){
    Window* window = new Window(640, 360, "Modern OpenGL");
    ShaderProgram* program;
    Shader* vertexShader;
    Shader* fragmentShader;
//    for (int i = 0; i < 10 ; i++) {
//  std::cout<<((double) rand() / (RAND_MAX)) + 1<<std::endl;
//    }
    
    
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
    
    // Initalize Vertices
    GLuint myVBO[4];
    glGenBuffers(4, myVBO);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[0]);
    
    GLfloat vertexData[] = {
        +1.0, +1.0, -0.0, +1.0,
//        -1.0, +1.0, -0.0, +1.0,
//        +1.0, -1.0, -0.0, +1.0,
//        -1.0, -1.0, -0.0, +1.0,
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    
    GLint vertexLoc = program->getAttribLoc("aVertex");
    
    // Initalize Colors
    GLfloat colorData[] = {
        +0.35, +0.0, +0.0, +1.0,
//        +1.0, +0.0, +0.0, +1.0,
//        +0.0, +1.0, +1.0, +1.0,
//        +0.0, +1.0, +1.0, +1.0,
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
    GLint colorLoc = program->getAttribLoc("aColor");
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);
    
    // Initalize instancied positions
    Container* container = new Container(size, BATCH_SIZE);
    GLint positionLoc = program->getAttribLoc("aPosition");
    glVertexAttribPointer(positionLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionLoc);
    glVertexAttribDivisor(positionLoc, 1);
    
    // Initalize Elements
    
    GLuint elementData[] = {
        0, //1, 3, 0, 3, 2,
    };
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myVBO[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementData), elementData, GL_STATIC_DRAW);
    
    GLint modelLoc = program->getUniformLoc("uMMatrix");
    GLint projectionLoc = program->getUniformLoc("uPMatrix");
    GLint viewLoc = program->getUniformLoc("uVMatrix");

    
    float aspect = (float)window->getFrameBufferWidth()/(float)window->getFrameBufferHeight();
    glm::mat4 projectionMat = glm::perspective(45.0f, aspect, 0.01f, 100.0f);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));
    
    glPointSize(2.0f);
    Camera cam = Camera();
    cam.setPosition(glm::vec3(0.0,0.0, 0.0));
    cam.setRotation(glm::vec3(0, 0, 0));
    
    glm::mat4 modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, -10.0f));
    
    while(!window->shouldClose()){
        
        cam.pollUserInput(window);
        window->setWindowFPS();
        glViewport(0, 0, window->getFrameBufferWidth(), window->getFrameBufferHeight());
        glClear(GL_COLOR_BUFFER_BIT);
        
        // TODO: Improve blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        
        // Send Vertices
        glEnableVertexAttribArray(vertexLoc);
        glBindBuffer(GL_ARRAY_BUFFER, myVBO[0]);
        glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat),(GLvoid*) (0*sizeof(GLfloat)));
        
        // Send Colors
        glEnableVertexAttribArray(colorLoc);
        glBindBuffer(GL_ARRAY_BUFFER, myVBO[1]);
        glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);
        
        // Send Positions
        glEnableVertexAttribArray(positionLoc);
        size = container->update();
        GLfloat* positionData = container->getPositionBuffer();
        glBindBuffer(GL_ARRAY_BUFFER, myVBO[2]);
        glBufferData(GL_ARRAY_BUFFER, 4 * size * sizeof(GL_FLOAT), NULL, GL_STREAM_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size * 4 * sizeof(GLfloat), positionData);
        glVertexAttribPointer(positionLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myVBO[3]);
        glDrawElementsInstanced(GL_POINTS, 1, GL_UNSIGNED_INT, 0, size);
        
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cam.getMatrix()));


        glfwPollEvents();
        window->swapBuffers();
    }
    
    glDeleteBuffers(4, myVBO);
    glDeleteVertexArrays(1, &myVAO);
    delete window;
    delete program;
    glfwTerminate();
    return 0;
}