//
//  TextureUtils.h
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-09.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#ifndef __HelloGL__TextureUtils__
#define __HelloGL__TextureUtils__

#define GLFW_INCLUDE_GLCOREARB
#include <iostream>
#include <GLFW/glfw3.h>
#include <IL/il.h>
#include <iostream>
#include <fstream>

#endif /* defined(__HelloGL__TextureUtils__) */

class TextureUtils
{
public:
    static GLuint createTexture(const GLchar* path);
};