//
//  Timer.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

class Timer
{
private:
    double                     m_innerTimer;
    double                     m_saveTime;
    bool                       m_isUse;
    double                     m_nowTime;
    
public:
    Timer(double nowTime);
    virtual ~Timer();
    
public:
    bool        CheckTimer(double completeTime);
    
public:
    double      GetTime();
    void        StartTimer();
    bool        GetisUse();
    void        SetTime(double t);
};