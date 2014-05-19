//
//  Particle.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-18.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Particle.h"

Particle::Particle(glm::vec3 _position){
    position = _position;
}

glm::vec3 Particle::getPosition(){
    return position;
}

void Particle::draw(GLuint VAO){
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(NULL);
}

void Particle::update(GLuint modelLoc){
    glm::mat4 modelMat = glm::mat4();
    position -= glm::vec3(0.0f, 2.0f*getDelta(), 0.0f);
    modelMat = glm::translate(modelMat, position);
    modelMat = glm::rotate(modelMat, 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
}

std::string Particle::toString(){
    std::ostringstream ss;
    ss << "[ " << position.x << " " << position.y << " " << position.z << " ]";
    return ss.str();
}

double Particle::getDelta(){
    return 1.0 / 60.0f;
}