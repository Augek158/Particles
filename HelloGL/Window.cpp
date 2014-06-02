//
//  Window.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-17.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Window.h"

GLint Window::instanceCount = 0;
GLint Window::frameCount = 0;
GLdouble Window::oldTime = 0.0f;

Window::Window(GLint width, GLint height, std::string title){
    
    if(instanceCount == 0){
        

        ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
        ilEnable(IL_ORIGIN_SET);
        
        GLint glfwStatus = glfwInit();
        if(glfwStatus != GL_TRUE){
            std::cout << "GLFW failed to initalize!" << std::endl;
            glfwTerminate();
        }
        
        //Use latest version of OpenGL
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        
        instanceCount++;
    
        //Setup window
        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if(window == NULL){
            std::cout << "Window failed to create" << std::endl;
            glfwTerminate();
        }
    }
    
}

Window::~Window(){
    glfwDestroyWindow(window);
    instanceCount--;
    if(instanceCount == 0){
        glfwTerminate();
        std::cout << "Window destroyed!" << std::endl;
    }

}

void Window::makeContextCurrent(){
        glfwMakeContextCurrent(window);
}

bool Window::shouldClose(){
    return glfwWindowShouldClose(window);
}

GLint Window::getFrameBufferWidth(){
    GLint width;
    glfwGetFramebufferSize(window, &width, NULL);
    return width;
}

GLint Window::getFrameBufferHeight(){
    GLint height;
    glfwGetFramebufferSize(window, NULL, &height);
    return height;
}

void Window::swapBuffers(){
    glfwPollEvents();
    glfwSwapBuffers(window);
    GLdouble currentTime = glfwGetTime();
    _deltaTime = currentTime - _lastBufferSwapTime;
    _lastBufferSwapTime = currentTime;
    if(!_grabbed &&glfwGetMouseButton(window, 0)){
        _grabbed =true;
        GLdouble x,y;
        glfwGetCursorPos(window, &x, &y);
        _lastMousePos = glm::vec2(-x,-y);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    if(_grabbed && glfwGetKey(window, GLFW_KEY_ESCAPE)){
        _grabbed = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    GLdouble x,y;
    glfwGetCursorPos(window, &x, &y);
    glm::vec2 currentMosPos = glm::vec2(-x,-y);
    _deltaMousePos = currentMosPos - _lastMousePos;
    _lastMousePos= currentMosPos;
}

void Window::setWindowFPS(){
    double currentTime = glfwGetTime();
    frameCount++;
    std::stringstream ss;
    if(frameCount % 30 == 0){
        ss << "FPS: " << round(1.0f / (currentTime - oldTime));
        glfwSetWindowTitle(window, ss.str().c_str());
    }
    oldTime = currentTime;
}
GLFWwindow* Window::getWindow(){
    return window;
}

GLfloat Window::getDeltaTime(){
    return _deltaTime;
}

bool Window::isGrabbed(){
    return _grabbed;
}

glm::vec2 Window::getDeltaMousePosition(){
    return _deltaMousePos;
}