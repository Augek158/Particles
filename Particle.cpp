//
//  Particle.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-19.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Particle.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Particle::Particle(){
    
    position = glm::vec3(-20.0f + (float)(rand() % 40),
                          15.0f + (float)(rand() % 15),
                         -35.0f + (float)(rand() % 8));
}

void Particle::draw(GLuint vao, GLuint modelLoc){
    glm::mat4 modelMat = glm::mat4();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    glBindVertexArray(NULL);
    
    position -= glm::vec3(0.0f, 2.5f * getDelta(), 0.0f);
    modelMat = glm::translate(modelMat, position);
    modelMat = glm::rotate(modelMat, 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
}

double Particle::getDelta(){
    return 1.0f / 60.0f;
}