//
//  GameSystem.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 6..
//
//

#include "GameSystem.h"
#include "CCDirector.h"
#include "RapidXML/rapidxml.hpp"

using namespace cocos2d;
using namespace rapidxml;

GameSystem::GameSystem(GameScene *pScene, Player *pPlayer)
{
    m_pNetwork  = new Network;
    m_pInfoMgr  = new InfoMgr;
    m_pScene    = pScene;
    m_pWorld    = NULL;
    m_pObjectMgr = new ObjectMgr(pScene, m_pInfoMgr, this);
    m_pGroundBody   = NULL;
    m_pPlayer   = pPlayer;
}

GameSystem::~GameSystem()
{
    SAFE_DELETE(m_pNetwork);
    SAFE_DELETE(m_pInfoMgr);
    
    m_pWorld->DestroyBody(m_pGroundBody);
    SAFE_DELETE(m_pWorld);
}

void GameSystem::_initPhysics()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    b2Vec2 gravity = b2Vec2(0, -10);
    
    m_pWorld = new b2World(gravity);
    m_pWorld->SetAllowSleeping(true);
    m_pWorld->SetContinuousPhysics(true);
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); //bottom-left corner
    
    m_pGroundBody = m_pWorld->CreateBody(&groundBodyDef);
    
    b2EdgeShape groundBox;
    
    groundBox.Set(b2Vec2(0,0), b2Vec2(size.width/PTM_RATIO,0));
    m_pGroundBody->CreateFixture(&groundBox,0);
    
    // top
    groundBox.Set(b2Vec2(0,(size.height)/PTM_RATIO),
                  b2Vec2(size.width/PTM_RATIO, (size.height)/PTM_RATIO));
    m_pGroundBody->CreateFixture(&groundBox,0);
    
    // left
    groundBox.Set(b2Vec2(0,size.height/PTM_RATIO), b2Vec2(0,0));
    m_pGroundBody->CreateFixture(&groundBox,0);
    
    // right
    groundBox.Set(b2Vec2(size.width/PTM_RATIO,size.height/PTM_RATIO), b2Vec2(size.width/PTM_RATIO,0));
    m_pGroundBody->CreateFixture(&groundBox,0);
}

bool GameSystem::init()
{
    m_pInfoMgr->loadData("ObjectDB.sqlite");
    _initPhysics();

    return true;
}

void GameSystem::update(float dt)
{
    int velocityIterations = 8;
    int positionIterations = 1;
    
    m_pObjectMgr->update(dt);
    m_pWorld->Step(dt, velocityIterations, positionIterations);
    
    for (b2Body* b = m_pWorld->GetBodyList(); b; b = b->GetNext())
    {
        if( b->GetUserData() != NULL )
        {
            CCSprite *pSprite = static_cast<CCSprite*>(b->GetUserData());
            pSprite->setPosition(CCPointMake(b->GetPosition().x * PTM_RATIO,
                                             b->GetPosition().y * PTM_RATIO));
            pSprite->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }
}

FishObject* GameSystem::addFish(FishStatus status, cocos2d::CCPoint position, CommonFishPartInfo eye, CommonFishPartInfo body, CommonFishPartInfo fin, double compTime, bool isNew, int id, Tag tag)
{
    return m_pObjectMgr->addFish(status, position, eye, body, fin, compTime, id, isNew, tag);
}

void GameSystem::addDeco(int id, DECORATION_TYPE type, cocos2d::CCPoint position, bool isNew)
{
    DecorationInfo *pInfo = NULL;
    m_pInfoMgr->searchInfo(id, type, &pInfo);
    
    m_pObjectMgr->addDecoration(pInfo, position, 0, isNew);
}

void GameSystem::addDeco(const char *name, DECORATION_TYPE type, cocos2d::CCPoint position, bool isNew)
{
    //일단 스레드 제외하고 하자.
    DecorationInfo *pInfo = NULL;
    m_pInfoMgr->searchInfo(name, type, &pInfo);
    
    m_pObjectMgr->addDecoration(pInfo, position, 0, isNew);
}

bool GameSystem::_removeNetworkObject()
{
    return true;
}

void GameSystem::FishMix(FishObject *pFish1, FishObject *pFish2)
{
    //급하니까 일단 완성은 시켜야할거 같아
    
    const char *bodyName;
    if(rand()%2) bodyName = pFish1->GetDNA()->GetBodyInfo()->GetName();
    else         bodyName = pFish2->GetDNA()->GetBodyInfo()->GetName();
    COLOR_ARGB bodyColor;
    bodyColor.r = (pFish1->GetDNA()->GetBodyInfo()->m_color.r + pFish2->GetDNA()->GetBodyInfo()->m_color.r)/2;
    bodyColor.g = (pFish1->GetDNA()->GetBodyInfo()->m_color.g + pFish2->GetDNA()->GetBodyInfo()->m_color.b)/2;
    bodyColor.b = (pFish1->GetDNA()->GetBodyInfo()->m_color.g + pFish2->GetDNA()->GetBodyInfo()->m_color.b)/2;

    const char *eyeName;
    if(rand()%2) eyeName = pFish1->GetDNA()->GetEyeInfo()->GetName();
    else         eyeName = pFish2->GetDNA()->GetEyeInfo()->GetName();
    COLOR_ARGB eyeColor;
    eyeColor.r = (pFish1->GetDNA()->GetEyeInfo()->m_color.r + pFish2->GetDNA()->GetEyeInfo()->m_color.r)/2;
    eyeColor.g = (pFish1->GetDNA()->GetEyeInfo()->m_color.g + pFish2->GetDNA()->GetEyeInfo()->m_color.b)/2;
    eyeColor.b = (pFish1->GetDNA()->GetEyeInfo()->m_color.g + pFish2->GetDNA()->GetEyeInfo()->m_color.b)/2;

    const char *finsName;
    if(rand()%2) finsName = pFish1->GetDNA()->GetFinsInfo()->GetName();
    else         finsName = pFish2->GetDNA()->GetFinsInfo()->GetName();
    COLOR_ARGB finsColor;
    finsColor.r = (pFish1->GetDNA()->GetFinsInfo()->m_color.r + pFish2->GetDNA()->GetFinsInfo()->m_color.r)/2;
    finsColor.g = (pFish1->GetDNA()->GetFinsInfo()->m_color.g + pFish2->GetDNA()->GetFinsInfo()->m_color.b)/2;
    finsColor.b = (pFish1->GetDNA()->GetFinsInfo()->m_color.g + pFish2->GetDNA()->GetFinsInfo()->m_color.b)/2;

    BodyInfo *pBodyInfo;
    m_pInfoMgr->searchInfo(bodyName, FISHPART_TYPE_BODY, reinterpret_cast<FishPartInfo**>(&pBodyInfo));
    pBodyInfo->m_color = bodyColor;
    
    FinsInfo *pFinsInfo;
    m_pInfoMgr->searchInfo(finsName, FISHPART_TYPE_FIN, reinterpret_cast<FishPartInfo**>(&pFinsInfo));
    pFinsInfo->m_color = finsColor;

    FinsInfo *pEyeInfo;
    m_pInfoMgr->searchInfo(eyeName, FISHPART_TYPE_EYE, reinterpret_cast<FishPartInfo**>(&pEyeInfo));
    pEyeInfo->m_color = eyeColor;
    
    char fish1Name[30];
    char fish2Name[30];
    
    char txt[20];
    
    pFish1->GetName(fish1Name);
    pFish2->GetName(fish2Name);
//    sprintf(txt, "%s와 %s의 아이", fish1Name, fish2Name);
//    Tag tag(m_pPlayer->GetUserInfo()->GetName(), txt);
    Tag tag;
    
    DNA dna(tag, pBodyInfo, pFinsInfo, pEyeInfo, 15.f);
    CCPoint position;
    position.x = (pFish1->getPositon().x + pFish2->getPositon().x) / 2;
    position.y = (pFish1->getPositon().x + pFish2->getPositon().y) / 2;
    _addEgg(dna, 0, position, true);
}

void GameSystem::_addEgg(DNA &dna, float nowTime, cocos2d::CCPoint position, bool isNew, int id)
{
    Egg *pEgg= new Egg(this, dna, nowTime);
    pEgg->init(m_pWorld, position, 1.f, 15.f);
    m_pObjectMgr->addEgg(pEgg, isNew, id);
}

bool GameSystem::Crossbreed(FishObject *pFish1, FishObject *pFish2, float CBTime, float CBComTime)
{
    if(pFish1 == NULL || pFish2 == NULL) return false;
    if(pFish1 == pFish2) return false;
    if(pFish1->isCrossbreed() || pFish2->isCrossbreed()) return false;
    
    b2DistanceJointDef d;
    
    d.bodyA = pFish1->GetBody();
    d.bodyB = pFish2->GetBody();
    d.collideConnected = true;
    d.length = 2.0f;
    
    b2Joint* pJoint =  m_pWorld->CreateJoint(&d);
    if(pFish1->Crossbreed(pFish2, pJoint, CBTime, CBComTime) == false)
        m_pWorld->DestroyJoint(pJoint);
    
    return true;
}

void GameSystem::addFood(cocos2d::CCPoint position)
{
    m_pObjectMgr->addFood(position);
}