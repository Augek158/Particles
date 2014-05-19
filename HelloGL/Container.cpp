//
//  ParticleContainer.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-19.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Container.h"

Container::Container(int max, int batchSize, GLuint vao, GLuint modelLoc){
    this->batchSize = batchSize;
    this->max = max;
    this->vao = vao;
    this->modelLoc = modelLoc;
    frameCount = 0;
}

Container::~Container(){
//    delete container;
}

void Container::draw(){
    
    for(std::vector<Particle>::iterator it = container.begin(); it != container.end();){
        if(it->getPosition().y < -30.0f){
            it = container.erase(it);
        }else{
            it->draw(vao, modelLoc);
            it++;
        }
    }
}

double Container::getDelta(){
    return 1.0f / 60.0f;
}

void Container::spawn(){
    
    if(frameCount++ % 60 == 0){
        frameCount = 1;
        int diff = max - (int)container.size();
        (diff < batchSize) ? diff : diff = batchSize;
                for (int i = 0; i < diff; i++) {
                    Particle p = Particle();
                    container.push_back(p);
                }
    }
}