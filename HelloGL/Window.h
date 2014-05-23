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
#include <sstream>
#include <iostream>
#include <fstream>

class Window{
private:
    static int instanceCount;
    static int frameCount;
    static double oldTime;
    GLFWwindow* window;
    
    GLdouble _lastBufferSwapTime;
    GLdouble _deltaTime;
    bool _grabbed;
    glm::vec2 _lastMousePos;
    glm::vec2 _deltaMousePos;
public:
    Window(GLint width, GLint height, std::string title);
    void makeContextCurrent();
    virtual ~Window();
    bool shouldClose();
    GLint getFrameBufferWidth();
    GLint getFrameBufferHeight();
    void swapBuffers();
    void setWindowFPS();
    GLfloat getDeltaTime();
    GLFWwindow* getWindow();
    bool isGrabbed();
    glm::vec2 getDeltaMousePosition();
    glm::vec2 getMousePos();
};


#endif /* defined(__HelloGL__Window__) */
