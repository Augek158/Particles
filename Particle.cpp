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
    bornTime = glfwGetTime();
    position = glm::vec3(-25.0f + (float)(rand() % 50),
                          30.0f + (float)(rand() % 40),
                         -60.0f + (float)(rand() % 30));
    velocity = glm::vec3(0.0f, (float)(rand() % 10) * getDelta(), 0.0f);
}

void Particle::draw(GLuint vao, GLuint modelLoc){
    glm::mat4 modelMat = glm::mat4();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(NULL);
    
    position -= velocity;
    modelMat = glm::translate(modelMat, position);
    modelMat = glm::rotate(modelMat, 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
}

glm::vec3 Particle::getPosition(){
    return position;
}


double Particle::getDelta(){
    return 1.0f / 60.0f;
}

double Particle::getTimeLived(){
    return glfwGetTime() - bornTime;
}