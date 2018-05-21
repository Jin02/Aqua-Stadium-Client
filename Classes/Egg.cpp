//
//  Egg.cpp
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#include "Egg.h"
#include "Utility.h"
#include <string>
#include "GameSystem.h"

using namespace cocos2d;
using namespace std;

Egg::Egg(GameSystem *pSystem, DNA &dna, double nowTime)
{
    m_pDNA     = new DNA(dna);
    m_pTimer    = new Timer(nowTime);
    m_id        = -1;
    m_pSystem   = pSystem;    
}

Egg::~Egg()
{
    removeAllChildrenWithCleanup(true);
    SAFE_DELETE(m_pDNA);
    SAFE_DELETE(m_pTimer);

    unschedule(schedule_selector(Egg::Grow));
}

bool Egg::init(b2World *pWorld, CCPoint position, float delay, float radius)
{
    CCTexture2D *pTex = CCTextureCache::sharedTextureCache()->addImage("Image/Fish/Egg/BaseEgg.png");
    if(PhysicsObject::init(pTex, radius, pWorld, b2_dynamicBody, position, 1.f, 1.f) == false)
        return false;
    
    m_pSprite->setColor(ccc3(m_pDNA->GetBodyColor().r, m_pDNA->GetBodyColor().g, m_pDNA->GetBodyColor().b));
    
    schedule(schedule_selector(Egg::Grow));
    m_pTimer->StartTimer();
    
    return true;
}

void Egg::Grow(float dt)
{
    if(m_pTimer->CheckTimer(m_pDNA->GetGrowCompTime()) == true)
    {
        CommonFishPartInfo eye(m_pDNA->GetEyeInfo()->GetName(), m_pDNA->GetEyeInfo()->m_color);
        CommonFishPartInfo body(m_pDNA->GetBodyInfo()->GetName(), m_pDNA->GetBodyInfo()->m_color);
        CommonFishPartInfo fins(m_pDNA->GetFinsInfo()->GetName(), m_pDNA->GetFinsInfo()->m_color);
        
        CCPoint position;
        position.x = PhysicsObject::m_pBody->GetPosition().x * PTM_RATIO;
        position.y = PhysicsObject::m_pBody->GetPosition().y * PTM_RATIO + 30;        
        
        m_pSystem->addFish(FishStatus(0, 100, 0, 3),
                           position, eye, body, fins,
                           10+rand()%20, true, 0),
        b2Vec2(position.x/PTM_RATIO, (position.y+20)/PTM_RATIO);
        
        unschedule(schedule_selector(Egg::Grow));
        m_pSystem->GetObjMgr()->removeEgg(this);
    }
}

float Egg::GetTime()
{
    return m_pTimer->GetTime();
}