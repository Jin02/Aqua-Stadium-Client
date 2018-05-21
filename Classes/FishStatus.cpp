//
//  FishStatus.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 6..
//
//

#include "FishStatus.h"
#include "Utility.h"

FishStatus::FishStatus()
{
    m_time = 0;
    m_clean = 0;
    m_hungry = 0;
    m_life  = 0;
}

FishStatus::FishStatus(int hungry, int clean, double time, int life)
{
    m_hungry    = hungry;
    m_clean     = clean;
    m_time      = time;
    m_life      = life;
}

FishStatus::~FishStatus()
{
}