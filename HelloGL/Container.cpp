//
//  ParticleContainer.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-19.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Container.h"

Container::Container(int size){
 
    for(int i = 0; i < size; i++){
        glm::vec3 pos = glm::vec3(-15.0f + (float)(rand() % 30),
                                   15.0f + (float)(rand() % 15),
                                  -35.0f + (float)(rand() % 8));
        container.push_back(pos);
    }
}

Container::~Container(){
//    delete container;
}

void Container::draw(GLuint vao, GLuint modelLoc){
    
    for(std::vector<glm::vec3>::iterator it = container.begin(); it != container.end(); it++){
        glm::mat4 modelMat = glm::mat4();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(NULL);
        glm::vec3 position = *it;
        position -= glm::vec3(0.0f, 2.5f * getDelta(), 0.0f);
        *it = position;
        modelMat = glm::translate(modelMat, position);
        modelMat = glm::rotate(modelMat, 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    }
}

double Container::getDelta(){
    return 1.0f / 60.0f;
}