
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
#include "Physics.h"


int size = 10;
const int BATCH_SIZE = 10;

enum{
    PROTO_VBO,
    DATA_VBO,
    TRANSFORM_VBO
};

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

void renderScene(){
    
}

int main(int argc, const char *argv[]){

    
    Window* window = new Window(640, 360, "Particles");
    ShaderProgram* RenderProgram;
    ShaderProgram* TransformProgram;
    
    Shader* transformShader;

    Shader* vertexShader;
    Shader* fragmentShader;
//    for (int i = 0; i < 10 ; i++) {
//  std::cout<<((double) rand() / (RAND_MAX)) + 1<<std::endl;
//    }
    
    
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
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[PROTO_VBO]);
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
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[DATA_VBO]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particleData), particleData, GL_STATIC_DRAW);
    
    glPointSize(3.0f);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[TRANSFORM_VBO]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particleData), nullptr, GL_DYNAMIC_COPY);
   
    
    glPointSize(2.0f);
    Camera cam = Camera();
    cam.setPosition(glm::vec3(0.0,0.0, 20.0));
    cam.setRotation(glm::vec3(0, 0, 0));
    
    glm::mat4 modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, -10.0f));
    

    
    GLuint modelLoc = RenderProgram->getUniformLoc("uMMatrix");
    GLuint viewLoc = RenderProgram->getUniformLoc("uVMatrix");
    GLuint projectionLoc  = RenderProgram->getUniformLoc("uPMatrix");
    
    float aspect = (float)window->getFrameBufferWidth()/(float)window->getFrameBufferHeight();
    glm::mat4 projectionMat = glm::perspective(45.0f, aspect, 0.01f, 100.0f);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));
    
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

//    Container container = Container(10, 2);
//    container.getPositionBuffer();
    glm::vec3 vec = glm::vec3(1.0, 2.0, 3.0);
    printf("%f\n",vec[1]);
    
    while(!window->shouldClose()){
        cam.pollUserInput(window);
        window->setWindowFPS();
        
        // Transform shader calculates the new positions/velocities
        TransformProgram->use();
        
        glEnable(GL_RASTERIZER_DISCARD);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo[DATA_VBO]);
        glEnableVertexAttribArray(1);
        glVertexAttribDivisor(1, 0);

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), 0);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)( 4 * sizeof(GL_FLOAT)));
        
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo[TRANSFORM_VBO]);
        
        glBeginTransformFeedback(GL_POINTS);
        glDrawArrays(GL_POINTS, 0, size);
        glEndTransformFeedback();
        
        std::swap(vbo[DATA_VBO],vbo[TRANSFORM_VBO]);
        
        // Vertex shader picks up the generated VBO and uses this for drawing

        RenderProgram->use();
        glDisable(GL_RASTERIZER_DISCARD);
        
        // TODO: Improve blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        
        initUniforms(RenderProgram, window);
        glViewport(0, 0, window->getFrameBufferWidth(), window->getFrameBufferHeight());
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo[PROTO_VBO]);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo[DATA_VBO]);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), 0);
        glVertexAttribDivisor(1, 1);
        
        glDrawArraysInstanced(GL_POINTS, 0, 1, numParticles);

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cam.getMatrix()));


        glfwPollEvents();
        window->swapBuffers();
    }
    


    delete window;
    delete RenderProgram;
    delete TransformProgram;
    glDeleteVertexArrays(1, &myVAO);
    glDeleteBuffers(3, vbo);
    glfwTerminate();
    return 0;
}