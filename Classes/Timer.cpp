//
//  Timer.cpp
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#include "Timer.h"
#include <ctime>

Timer::Timer(double nowTime)
{
    m_innerTimer = 0;
    m_saveTime   = nowTime;
    m_nowTime    = nowTime;
    m_isUse      = false;
}

Timer::~Timer()
{
    
}

bool Timer::CheckTimer(double completeTime)
{
    if( m_isUse == false )
        return false;
    
    int elapse = time(NULL) - m_innerTimer;
    m_nowTime  = elapse + m_saveTime;
    
    if( completeTime == -1 )
        return false;
    
    if( m_nowTime > completeTime )
    {
        m_nowTime = 0;
        m_saveTime = 0;
        m_innerTimer = time(NULL);
        m_isUse = false;
        
        return true;
    }
    
    return false;
}

void Timer::StartTimer()
{
    m_innerTimer    = time(NULL);
    m_isUse         = true;
}

double Timer::GetTime()
{
    return m_nowTime;
}

bool Timer::GetisUse()
{
    return m_isUse;
}

void Timer::SetTime(double t)
{
    m_nowTime = t;
}
