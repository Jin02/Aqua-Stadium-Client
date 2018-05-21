//
//  FinsInfo.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 10. 20..
//
//

#include "FinInfo.h"

FinInfo::FinInfo()
{
    
}

FinInfo::FinInfo(std::vector< POINT<float> > &vertex, FishPartPosition &pos)
{
    m_vPhysicsVertex    = vertex;
    m_position          = pos;
}

FinInfo::~FinInfo()
{
    
}