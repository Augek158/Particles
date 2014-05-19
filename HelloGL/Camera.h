//
//  Camera.h
//  Modern OpenGL
//
//  Created by Oscar Johnson on 2014-05-18.
//  Copyright (c) 2014 Oscar Johnson. All rights reserved.
//

#ifndef __Modern_OpenGL__Camera__
#define __Modern_OpenGL__Camera__

#define GLFW_INCLUDE_GLCOREARB

#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "Window.h"

class Camera {
private:
  glm::vec3 _position;
  glm::vec3 _rotation;
  GLfloat _moveSpeed;
  GLfloat _rotateSpeed;

public:
  Camera();
    void setPosition(glm::vec3 position);//std::cout << 1.0 / window->getDeltaTime() << std::endl;
    void setRotation(glm::vec3 rotation);
    void setMoveSpeed(GLfloat moveSpeed);
    void setRotateSpeed(GLfloat rotateSpeed);
    glm::mat4 getMatrix();
    void pollUserInput(Window* window);
};



#endif /* defined(__Modern_OpenGL__Camera__) */
