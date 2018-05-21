//
//  Bubble.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 17..
//
//

#include "Bubble.h"
#include "GameScene.h"
#include "GameSystem.h"

using namespace cocos2d;

Bubble::Bubble(GameSystem *pSystem, GameScene *pScene)
{
    m_isRemove  = false;
    m_pSystem   = NULL;
    m_pScene    = NULL;
    m_time = 0;
}

Bubble::~Bubble()
{
    unschedule(schedule_selector(Bubble::_check));
}

bool Bubble::init(b2World *pWorld, cocos2d::CCPoint position)
{
    CCTexture2D *pTex = CCTextureCache::sharedTextureCache()->addImage("Image/Bubble.png");
    if(PhysicsObject::init(pTex, 4.f, pWorld, b2_dynamicBody, position, -0.1f, 0.01f) == false)
        return false;

    m_pSprite->setColor(ccc3(255, 255, 255));
    schedule(schedule_selector(Bubble::_check));
    
    return true;
}

void Bubble::_check(float dt)
{
    if( (this->PhysicsObject::m_pBody->GetPosition().y * PTM_RATIO >= 312*2.5) || (m_time += dt) >= 5.0f)
    {
        m_isRemove = true;
        unschedule(schedule_selector(Bubble::_check));
    }
}
