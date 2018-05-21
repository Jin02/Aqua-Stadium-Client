//
//  DecorationInfo.cpp
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#include "DecorationInfo.h"

DecorationInfo::DecorationInfo() : CommonInfo()
{
    m_type          = DECORATION_TYPE_NONE;
    m_effectRate    = 0.f;
}

DecorationInfo::DecorationInfo(int id, DECORATION_TYPE type, float rate, const char *pName, std::vector< POINT<float> > &vPhysicsVertex)
            : CommonInfo(id, pName, vPhysicsVertex)
{
    m_type          = type;
    m_effectRate    = rate;
}

DecorationInfo::~DecorationInfo()
{
    
}