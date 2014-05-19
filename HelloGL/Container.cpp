//
//  ParticleContainer.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-19.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Container.h"

Container::Container(int size, GLuint vao, GLuint modelLoc){
 
    this->vao = vao;
    this->modelLoc = modelLoc;
    for(int i = 0; i < size; i++){
        Particle p = Particle();
        container.push_back(p);
    }
}

Container::~Container(){
//    delete container;
}

void Container::draw(){
    
    for(std::vector<Particle>::iterator it = container.begin(); it != container.end(); it++){
        it->draw(vao, modelLoc);
    }
}

double Container::getDelta(){
    return 1.0f / 60.0f;
}