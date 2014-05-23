//
//  Physics.h
//  HelloGL
//
//  Created by Oscar Johnson on 2014-05-20.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#ifndef __HelloGL__Physics__
#define __HelloGL__Physics__

#include <iostream>



class Physics {

  
public:

    static constexpr float gravity = 9.82;
    
 
};

const float COR = 0.7;

// Y-axis bounds
const float BoundingSouth = -20.0;
const float BoundingNorth = 20.0;
    
// X-axis bounds
const float BoundingWest = -40.0;
const float BoundingEast = 40.0;

//Z-axis bounds
const float BoundingNearest = 20.0;
const float BoundingFarthest = -20.0;

#endif /* defined(__HelloGL__Physics__) */
