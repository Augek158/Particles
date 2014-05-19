//
//  ParticleContainer.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-18.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "ParticleContainer.h"

ParticleContainer::ParticleContainer(int size){
    
    container = new std::vector<Particle>;
    
    for(int i = 0; i < size; i++){
        glm::vec3 pos = glm::vec3(-5.0f + (float)(rand() % 10),
                                   10.0f,
                                  -35.0f);
        Particle p = Particle(pos);
        container->push_back(p);
    }
}

void ParticleContainer::draw(GLuint  VAO){
    
    std::vector<Particle>::iterator it;
    for(it = container->begin(); it < container->end(); it++){
        it->draw(VAO);
    }
    
}

void ParticleContainer::update(GLuint modelLoc){
    
    std::vector<Particle>::iterator it;
    for(it = container->begin(); it < container->end(); it++){
        it->update(modelLoc);

    }
    
}

std::string ParticleContainer::toString(){
    
    std::vector<Particle>::iterator it;
    std::ostringstream ss;
    
    for(it = container->begin(); it < container->end(); it++){
        ss << it->toString() << std::endl;
    }
    
    return ss.str();
}

unsigned long ParticleContainer::getSize(){
    return container->size();
}