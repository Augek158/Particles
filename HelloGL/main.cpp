
//  main.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-04.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Renderer.h"

int main(int argc, const char *argv[]){
    
    Renderer render(10000);
    render.initWindow();
    render.initShaderPrograms();
    render.initBuffers();
    render.initCamera();
    render.render();
    
    return 0;
}