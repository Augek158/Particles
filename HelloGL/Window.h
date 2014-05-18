//
//  Window.h
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-17.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#ifndef __HelloGL__Window__
#define __HelloGL__Window__

#define GLFW_INCLUDE_GLCOREARB
#include <iostream>
#include <GLFW/glfw3.h>
#include <IL/il.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>

class Window{
private:
    static int instanceCount;
    GLFWwindow* window;
public:
    Window(GLint width, GLint height, std::string title);
    void makeContextCurrent();
    virtual ~Window();
    bool shouldClose();
    GLint getFrameBufferWidth();
    GLint getFrameBufferHeight();
    void swapBuffers();
};


#endif /* defined(__HelloGL__Window__) */
