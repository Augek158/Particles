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
    
    GLfloat particleData[] = {
                +0.0, +1.0, -0.0, +1.0, 1.0, 0.0, 0.0,
                -1.0, -1.0, -0.0, +1.0, 0.0, 1.0, 0.0,
                +1.0, -1.0, -0.0, +1.0, 0.0, 0.0, 1.0,
    };
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particleData), particleData, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), 0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)( 4 * sizeof(GL_FLOAT)));
    
    GLuint tbo;
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particleData), nullptr, GL_STATIC_READ);
    
    glEnable(GL_RASTERIZER_DISCARD);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);
    
    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, 21);
    glEndTransformFeedback();
    
    GLfloat feedback[21];
    glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);
    
    for (int i = 0; i < 21; i++) {
        printf("%f\n",feedback[i]);
    }
    
    std::swap(vbo,tbo);
    glDisable(GL_RASTERIZER_DISCARD);
    glUseProgram(RenderProgram->getProgramID());
    
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
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)( 4 * sizeof(GL_FLOAT)));
    
    
    while(!window->shouldClose()){
        glViewport(0, 0, window->getFrameBufferWidth(), window->getFrameBufferHeight());
        glClear(GL_COLOR_BUFFER_BIT);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwPollEvents();
        window->swapBuffers();
    }
    
    delete window;
    delete RenderProgram;
    delete TransformProgram;
    glfwTerminate();
    return 0;
}