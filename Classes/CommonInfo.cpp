//
//  CommonInfo.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 10. 16..
//
//

#include "CommonInfo.h"

CommonInfo::CommonInfo()
{
    m_id = -1;
}

CommonInfo::CommonInfo(int id, const char *name, std::vector< POINT<float> > vPhysicsVertex)
{
    m_id                = id;
    m_name              = name;
    m_vPhysicsVertex    = vPhysicsVertex;
}

CommonInfo::~CommonInfo()
{
    
}