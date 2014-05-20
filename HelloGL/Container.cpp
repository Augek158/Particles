//
//  ParticleContainer.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-19.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Container.h"

Container::Container(int numParticles){
    this->numParticles = numParticles;
    for (int i = 0; i < numParticles; i++) {
        container.push_back(*new Particle());
    }
    frameCount = 0;
}

Container::~Container(){
    //    delete container;
}

GLfloat* Container::getPositionBuffer(){
    
    GLfloat* positionBuffer = new GLfloat[4*numParticles];
    int index = 0;
    for(std::vector<Particle>::iterator it = container.begin(); it != container.end();){
        Particle& p = *it;
        p.update();
        positionBuffer[index] = p.getPosition().x;
        positionBuffer[index + 1] = p.getPosition().y;
        positionBuffer[index + 2] = p.getPosition().z;
        positionBuffer[index + 3] = 1.0f;
        it++;
        index += 4;
    }
    return positionBuffer;
}

double Container::getDelta(){
    return 1.0f / 60.0f;
}

void Container::spawn(){
    
    if(frameCount++ % 60 == 0){
        frameCount = 1;
        int diff = numParticles - (int)container.size();
        (diff < 10) ? diff : diff = 10;
        for (int i = 0; i < diff; i++) {
            Particle p = Particle();
            container.push_back(p);
        }
    }
    
    std::cout<<container.size()<<std::endl;
}