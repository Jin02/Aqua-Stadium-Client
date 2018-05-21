//
//  FinsInfo.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 10. 20..
//
//

#pragma once

#include "FinInfo.h"
#include "Utility.h"
#include <list>
#include "FishPartPosition.h"

class FinInfo
{
private:
    std::vector< POINT<float> >         m_vPhysicsVertex;
    FishPartPosition                    m_position;
    
public:
    FinInfo();
    FinInfo(std::vector< POINT<float> > &vertex, FishPartPosition &pos);
    ~FinInfo();
    
public:
    inline std::vector< POINT<float> > GetPhysicsVertex() { return m_vPhysicsVertex; }
    inline FishPartPosition GetPosition() { return m_position; }
};