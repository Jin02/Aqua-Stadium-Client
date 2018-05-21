//
//  FishPartPosition.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 2..
//
//

#pragma once

#include "Utility.h"

class FishPartPosition
{
private:
    #define LEFT    0
    #define RIGHT   1
    
private:
    POINT<float> m_position[2];
    
public:
    FishPartPosition();
    FishPartPosition(POINT<float> &left, POINT<float> &right);
    FishPartPosition(POINT<float> &position);
    ~FishPartPosition();
    
public:
    inline POINT<float> GetLeftPos()    { return m_position[LEFT];  }
    inline POINT<float> GetRightPos()   { return m_position[RIGHT]; }
    inline POINT<float> GetPos(bool isLeft) { return m_position[!isLeft]; }
    POINT<float> GetAveragePos();
};