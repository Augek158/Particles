
//  main.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-04.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Renderer.h"
#include "Container.h"

int main(int argc, const char *argv[]){
    
    Renderer render(5);
    render.initWindow();
    render.initShaderPrograms();
    render.initBuffers();
    render.initCamera();
    render.render();
//    
//    Container* cont = new Container();
//    
//    for(int i  = 0; i < 10000; i++){
//        cont->getNewParticleData(20);
//    }

//    printf("\n\n");
//    cont->spawnParticles(1);
//    cont->print(cont->getPositionBuffer());
    
    return 0;
}