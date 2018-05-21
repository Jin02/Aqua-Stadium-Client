//
//  Egg.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

#include "cocos2d.h"
#include "Box2D.h"
#include "PhysicsObject.h"
#include "DNA.h"
#include "Timer.h"
#include "Tag.h"

class GameSystem;

class Egg : public PhysicsObject
{    
private:
    GameSystem      *m_pSystem;
    DNA             *m_pDNA;
    Timer           *m_pTimer;

public:
    int             m_id;
    
public:
    Egg(GameSystem *pSystem, DNA &dna, double nowTime);
    ~Egg();
        
public:
    bool init(b2World *pWorld, cocos2d::CCPoint position, float delay, float radius);
    void Grow(float dt);
    float GetTime();
};