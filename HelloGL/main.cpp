
//  main.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-04.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Renderer.h"
#include "Container.h"
#include <IL/il.h>

int main(int argc, const char *argv[]){

    ilInit();
    Renderer renderer(3644,5);
    renderer.initWindow();
    renderer.initShaderPrograms();
    renderer.initBuffers();
    renderer.initCamera();
    renderer.initTextParticles();
    renderer.render();
    
    return 0;
}