//
//  FinInfo.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 10. 17..
//
//

#include "FinsInfo.h"

FinsInfo::FinsInfo() : FishPartInfo()
{
}

FinsInfo::FinsInfo(int id, const char *pName, FinInfo &upFin, FinInfo &downFin, FinInfo &tailFin, POINT<float> &sideFin)
//        : FishPartInfo(FISHPART_TYPE_FIN, id, pName)
{
    m_vUpFin    = upFin;
    m_vDownFin  = downFin;
    m_vTailFin  = tailFin;
    m_type      = FISHPART_TYPE_FIN;
    m_id        = id;
    m_name      = pName;
}

FinsInfo::~FinsInfo()
{
    
}