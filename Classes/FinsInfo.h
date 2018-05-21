//
//  FinInfo.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 10. 17..
//
//

#pragma once

#include "Utility.h"
#include "FishPartInfo.h"
#include "FinInfo.h"

enum FIN_TYPE
{
    FIN_TYPE_UP,
    FIN_TYPE_DOWN,
    FIN_TYPE_TAIL,
    FIN_TYPE_SIDE,
    FIN_TYPE_NUM
};

class FinsInfo : public FishPartInfo
{
private:
    FinInfo         m_vUpFin;
    FinInfo         m_vDownFin;
    FinInfo         m_vTailFin;

public:
    FinsInfo();
    FinsInfo(int id, const char *pName, FinInfo &upFin, FinInfo &downFin, FinInfo &tailFin, POINT<float> &sideFin);
    ~FinsInfo();
    
public:
    inline FinInfo GetUpFin()   { return m_vUpFin;      }
    inline FinInfo GetDownFin() { return m_vDownFin;    }
    inline FinInfo GetTailFin() { return m_vTailFin;    }
};