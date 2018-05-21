//
//  Food.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 13..
//
//

#pragma once

#include "PhysicsObject.h"
#include <vector>
#include "FishObject.h"

class GameSystem;
class GameScene;

#define MAX_FOOD_JOINT      3


class Food : public PhysicsObject
{
public:
    bool isRemoveOn;
    
private:
    GameSystem                      *m_pSystem;
    GameScene                       *m_pScene;
    std::vector<b2DistanceJoint*>    m_vJoints;

public:
    Food(GameSystem *pSystem, GameScene *pScene);
    ~Food();
    
private:
    bool _checkOverlapJoint(b2Body *pBody);
    FishObject* _findFish(b2Body *pBody);
    void _removeJoint();

    void _rotateFish(b2Body *pBody);
    
public:
    bool init(b2World *pWorld, cocos2d::CCPoint position);
    void update(float dt);
    void _eat(b2Body *pBody, int jointIndex);
    void findFish(float dt);
};