//
//  FishStatus.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 6..
//
//

#pragma once

#include <string>
#include "Tag.h"

class FishStatus
{
public:
    int             m_hungry;
    int             m_clean;
    int             m_life;    
    double          m_time;
    
public:
    FishStatus();
    FishStatus(int hungry, int clean, double time, int life);
    ~FishStatus();
    
public:
    inline int      GetHungry()     { return m_hungry;  }
    inline int      GetClean()      { return m_clean;   }
    inline double   GetTime()       { return m_time;    }
    inline int      GetLife()       { return m_life;    }
};