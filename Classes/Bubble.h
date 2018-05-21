//
//  Bubble.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 17..
//
//

#pragma once

#include "PhysicsObject.h"
#include "Timer.h"

class GameSystem;
class GameScene;

class Bubble : public PhysicsObject
{
public:
    bool            m_isRemove;
    float           m_time;
    
private:
    GameSystem      *m_pSystem;
    GameScene       *m_pScene;
    
public:
    Bubble(GameSystem *pSystem, GameScene *pScene);
    ~Bubble();
    
public:
    void _check(float dt);
    
public:
    bool init(b2World *pWorld, cocos2d::CCPoint position);
    bool isRemoveOn() { return m_isRemove; }
};