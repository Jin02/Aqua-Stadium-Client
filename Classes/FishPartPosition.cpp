//
//  FishPartPosition.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 2..
//
//

#include "FishPartPosition.h"

FishPartPosition::FishPartPosition()
{
}

FishPartPosition::FishPartPosition(POINT<float> &left, POINT<float> &right)
{
    m_position[LEFT]    = left;
    m_position[RIGHT]   = right;
}

FishPartPosition::FishPartPosition(POINT<float> &position)
{
    for(int i=0; i<2; ++i) m_position[i] = position;
}

FishPartPosition::~FishPartPosition()
{
    
}

POINT<float> FishPartPosition::GetAveragePos()
{
    POINT<float> averagePos;

    averagePos.x = m_position[0].x + (m_position[1].x - m_position[0].x);
    averagePos.y = m_position[0].y + (m_position[1].y - m_position[0].y);
    
    return averagePos;
}