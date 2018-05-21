//
//  FishPart.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 10. 11..
//
//

#include "FishPartInfo.h"

FishPartInfo::FishPartInfo() : CommonInfo()
{
    m_type      = FISHPART_TYPE_NONE;
    m_color     = COLOR_ARGB(255, 255, 255, 255);
}

FishPartInfo::FishPartInfo(FISHPART_TYPE type, int id, const char *pName, std::vector< POINT<float> > &vPhysicsVertex) : CommonInfo(id, pName, vPhysicsVertex)
{
    m_type      = type;
    m_color     = COLOR_ARGB(255, 255, 255, 255);
}

FishPartInfo::~FishPartInfo()
{
    
}