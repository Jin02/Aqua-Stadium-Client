//
//  Food.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 13..
//
//

#include "Food.h"
#include "GameSystem.h"
#include "GameScene.h"

using namespace cocos2d;
using namespace std;

Food::Food(GameSystem *pSystem, GameScene *pScene)
{
    m_pSystem   = pSystem;
    m_pScene    = pScene;
    isRemoveOn  = false;
}

Food::~Food()
{
    std::vector<b2DistanceJoint*>::iterator iter;
    for(iter = m_vJoints.begin(); iter != m_vJoints.end(); ++iter)
        (*iter)->GetBodyA()->GetWorld()->DestroyJoint((*iter));
}

bool Food::init(b2World *pWorld, CCPoint position)
{
    CCTexture2D *pTex = CCTextureCache::sharedTextureCache()->addImage("Image/Food.png");
    if(PhysicsObject::init(pTex, 8.f, pWorld, b2_dynamicBody, position, 0.6f, 20.f) == false)
        return false;
    
    m_pSprite->setColor(ccc3(255, 255, 255));
    findFish(0);
    schedule(schedule_selector(Food::update));
    return true;
}

FishObject* Food::_findFish(b2Body *pBody)
{
    std::vector<FishObject*> vFishs = m_pSystem->GetObjMgr()->GetFishObjects();
    std::vector<FishObject*>::iterator iter;
    for(iter = vFishs.begin(); iter != vFishs.end(); ++iter)
    {
        if((*iter)->GetBody() == pBody)
            return (*iter);
    }
    
    return NULL;
}

void Food::_removeJoint()
{
    std::vector<b2DistanceJoint*>::iterator iter;
    for(iter = m_vJoints.begin(); iter != m_vJoints.end(); ++iter)
    {
        b2World *pWorld = (*iter)->GetBodyA()->GetWorld();
        _findFish((*iter)->GetBodyA())->MoveOn();
        pWorld->DestroyJoint((*iter));
    }
    
    m_vJoints.clear();
}

void Food::update(float dt)
{
    float posY = 320 - this->GetBody()->GetPosition().y * PTM_RATIO;
    
    if( posY >= 310 )
    {
//        isRemoveOn = true;
//        _removeJoint();
//        unschedule(schedule_selector(Food::update));
//        return;
    }
    
    int i = 0;
    std::vector<b2DistanceJoint*>::iterator iter;
    for(iter = m_vJoints.begin(); iter != m_vJoints.end(); ++iter, ++i)
    {
        float length = (*iter)->GetLength();
        (*iter)->SetLength(length-0.1);
        _rotateFish((*iter)->GetBodyA());
        
        if( (320 - (*iter)->GetBodyA()->GetPosition().y * PTM_RATIO) >= 310 )
        {
            isRemoveOn = true;
            _removeJoint();
            //현재 모든 조인트 해제
            unschedule(schedule_selector(Food::update));
            return;
        }
        
        if( length <= 0.5 )
        {
            _eat((*iter)->GetBodyA(), i);
            _removeJoint();
            return;
        }
    }
}
void Food::_rotateFish(b2Body *pBody)
{
    std::vector<FishObject*> vFishs = m_pSystem->GetObjMgr()->GetFishObjects();
    std::vector<FishObject*>::iterator iter;
    for(iter = vFishs.begin(); iter != vFishs.end(); ++iter)
    {
        FishObject *pFish = (*iter);
        if( (*iter)->GetBody() == pBody )
        {
            if( (pFish->GetBody()->GetPosition().x * PTM_RATIO
               > m_pBody->GetPosition().x * PTM_RATIO) && pFish->isLeft() == false)
                 pFish->flipFish();
            
            float degree = calcDegreeBetweenTwoPoint(POINT<float>(m_pBody->GetPosition().x, m_pBody->GetPosition().y), POINT<float>(pFish->GetBody()->GetPosition().x, pFish->GetBody()->GetPosition().y) );
            
            pFish->SetAngle(DEGREE_TO_RADIAN(degree));
        }
    }
}

void Food::_eat(b2Body *pBody, int jointIndex)
{
    std::vector<FishObject*> vFishs = m_pSystem->GetObjMgr()->GetFishObjects();
    std::vector<FishObject*>::iterator iter;
    for(iter = vFishs.begin(); iter != vFishs.end(); ++iter)
    {
        if( (*iter)->GetBody() == pBody )
        {
            unschedule(schedule_selector(Food::update));
            (*iter)->eat(FOOD_TYPE_NORMAL);
            (*iter)->MoveOn();
            isRemoveOn = true;
            return;
        }
    }
}

bool Food::_checkOverlapJoint(b2Body *pBody)
{
    std::vector<b2DistanceJoint*>::iterator iter;
    
    for(iter = m_vJoints.begin(); iter != m_vJoints.end(); ++iter)
    {
        if((*iter)->GetBodyA() == pBody)
            return true;
    }
    
    return false;
}

void Food::findFish(float dt)
{
    printf("on");
    
    b2World *pWorld = this->GetBody()->GetWorld();
    std::vector<FishObject*> vFishs = m_pSystem->GetObjMgr()->GetFishObjects();

    std::vector<FishObject*>::iterator iter;
    for(iter = vFishs.begin(); iter != vFishs.end(); ++iter)
    {
        if( (*iter)->isCrossbreed() )   continue;
        if( _checkOverlapJoint((*iter)->GetBody()) ) continue;
        if((*iter)->GetStatus()->GetHungry() <= 30 && m_vJoints.size() < 3)
        {
            b2DistanceJointDef line;
            line.bodyA = (*iter)->GetBody();
            line.bodyB = this->GetBody();
            line.collideConnected = false;
            (*iter)->MoveOff();

            float t = calcDistance(line.bodyA->GetPosition().x, line.bodyB->GetPosition().x, line.bodyA->GetPosition().y, line.bodyB->GetPosition().y);
            
            line.length = t;

            b2Joint *pJoint = pWorld->CreateJoint(&line);
            m_vJoints.push_back(dynamic_cast<b2DistanceJoint*>(pJoint));
        }
    }
}
