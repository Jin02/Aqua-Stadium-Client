//
//  ObjectMgr.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 6..
//
//

#include "ObjectMgr.h"
#include "GameSystem.h"

using namespace cocos2d;

ObjectMgr::ObjectMgr(GameScene *pScene, InfoMgr *pInfoMgr, GameSystem *pSystem)
{
    m_pScene    = pScene;
    m_pIdxMgr   = new ObjIdxMgr;
    m_pInfoMgr  = pInfoMgr;
    m_pSystem   = pSystem;
}

ObjectMgr::~ObjectMgr()
{
    
}

FishObject* ObjectMgr::addFish(FishStatus &status, cocos2d::CCPoint position, CommonFishPartInfo eye, CommonFishPartInfo body, CommonFishPartInfo fin, double completeTime, int id, bool isNew, Tag tag)
{
    b2World *pWorld = m_pSystem->GetWorld();
    int idx = -1;
    
    if(isNew)     idx = m_pIdxMgr->FishIndex();
    else                    idx = id;
    
    BodyInfo *pBodyInfo = NULL;
    m_pInfoMgr->searchInfo(body.name,
                                  FISHPART_TYPE_BODY, reinterpret_cast<FishPartInfo**>(&pBodyInfo));
    pBodyInfo->m_color = body.color;
    
    FinsInfo *pFinsInfo = NULL;
    m_pInfoMgr->searchInfo(fin.name, FISHPART_TYPE_FIN, reinterpret_cast<FishPartInfo**>(&pFinsInfo));
    pFinsInfo->m_color = fin.color;
    
    EyeInfo *pEyeInfo = NULL;
    m_pInfoMgr->searchInfo(eye.name, FISHPART_TYPE_EYE, &pEyeInfo);
    pEyeInfo->m_color = eye.color;
    
    DNA dna(tag, pBodyInfo, pFinsInfo, pEyeInfo, completeTime);
    
    FishObject *pObject = new FishObject(dna, status, m_pSystem);
    pObject->init(pWorld, position);
    
    if(isNew) pObject->m_id = idx;
    else pObject->m_id = id;
    
    m_pIdxMgr->addFishIndex(pObject->m_id);
    m_pScene->addChild(pObject);
    m_vFishObjects.push_back(pObject);
    
    if(isNew)
        pObject->GetBody()->ApplyForceToCenter(b2Vec2(0,10));
    
    return pObject;
}

void ObjectMgr::removeFish(FishObject *pFish)
{
    std::vector<FishObject*>::iterator iter;
    for(iter = m_vFishObjects.begin(); iter != m_vFishObjects.end(); ++iter)
    {
        if( (*iter) == pFish )
        {
            b2World *pWorld = (*iter)->GetBody()->GetWorld();
            pWorld->DestroyBody((*iter)->GetBody());
            m_pScene->removeChild((*iter), true);
            m_pIdxMgr->removeFishIndex((*iter)->m_id);
            m_vFishObjects.erase(iter);
            SAFE_DELETE((*iter));
            return;
        }
    }
}

void ObjectMgr::addEgg(Egg *pEgg, bool isNew, int idx)
{
    int id = m_pIdxMgr->EggIndex();
    
    if(isNew)   pEgg->m_id = idx;
    else        pEgg->m_id = id;
    
    m_pIdxMgr->addEggIndex(pEgg->m_id);
    m_vEggObjects.push_back(pEgg);
    m_pScene->addChild(pEgg);
}

void ObjectMgr::removeEgg(Egg *pEgg)
{
    std::vector<Egg*>::iterator iter;
    for(iter = m_vEggObjects.begin(); iter != m_vEggObjects.end(); ++iter)
    {
        if( (*iter) == pEgg )
        {
            b2World *pWorld = (*iter)->GetBody()->GetWorld();
            pWorld->DestroyBody((*iter)->GetBody());
//            m_pScene->setVisible(false);
            m_pScene->removeChild((*iter), true);
            m_pIdxMgr->removeEggIndex((*iter)->m_id);
            m_vEggObjects.erase(iter);
//            SAFE_DELETE((*iter));
            return;
        }
    }
}

void ObjectMgr::addDecoration(DecorationInfo *pInfo, cocos2d::CCPoint position, int id, bool isNew)
{    
    int idx = -1;
    
    if(isNew)     idx = m_pIdxMgr->DecoIndex();
    else                    idx = id;
    
    std::string path = "Image/Decoration/";
    
    switch (pInfo->GetType()) {
        case DECORATION_TYPE_CORALREEF: path += "CoralReef/";   break;
        case DECORATION_TYPE_GRAVEL:    path += "Gravel/";      break;
        case DECORATION_TYPE_SEAWEED:   path += "Seaweed/";     break;
        case DECORATION_TYPE_SHIP:      path += "Ship/";        break;
        case DECORATION_TYPE_STON:      path += "Ston/";        break;
        case DECORATION_TYPE_CLAM:      path += "Clam/";        break;
        default:break;
    }
    
    path += pInfo->GetName();
    path += ".png";
    
    CCTexture2D *pTex = CCTextureCache::sharedTextureCache()->addImage(path.data());
    
    DecoObject *pObject = new DecoObject;
    pObject->init(pTex, m_pSystem->GetWorld(), position, 1.f, pInfo->GetPhysicsVertex(), ccp(0, 0), (pInfo->GetType() == DECORATION_TYPE_CLAM ? 4 : 1), (pInfo->GetType() == DECORATION_TYPE_CORALREEF));
    
    if(isNew) pObject->m_id = idx;
    else pObject->m_id = id;
    
    m_pIdxMgr->addDecoIndex(pObject->m_id);
    m_vDecoObjects.push_back(pObject);
    m_pScene->addChild(pObject);
    
//    pObject->SetTransForm( ccp(position.x,
//                               position.y ), 0);
}

void ObjectMgr::removeDeco(DecoObject *pObj)
{
    std::vector<DecoObject*>::iterator iter;
    for(iter = m_vDecoObjects.begin(); iter != m_vDecoObjects.end(); ++iter)
    {
        if( (*iter) == pObj )
        {
            b2World *pWorld = (*iter)->GetBody()->GetWorld();
            pWorld->DestroyBody((*iter)->GetBody());
            m_pScene->removeChild((*iter), true);
            m_pIdxMgr->removeDecoIndex((*iter)->m_id);
            m_vDecoObjects.erase(iter);
            SAFE_DELETE((*iter));
            return;
        }
    }
}

FishObject* ObjectMgr::findFish(cocos2d::CCPoint position)
{
    std::vector<FishObject*>::iterator iter;
    for(iter = m_vFishObjects.begin(); iter != m_vFishObjects.end(); ++iter)
    {
        //0번 인덱스는 Body로 고정되어 있음.
        for( b2Fixture *pFixture = (*iter)->GetFixtureList(); pFixture; pFixture = pFixture->GetNext() )
            if(pFixture->TestPoint(b2Vec2(position.x/PTM_RATIO, position.y/PTM_RATIO)))
            return (*iter);
    }
    
    return NULL;
}

FishObject* ObjectMgr::findFish(int id)
{
    std::vector<FishObject*>::iterator iter;
    for(iter = m_vFishObjects.begin(); iter != m_vFishObjects.end(); ++iter)
    {
        if( (*iter)->m_id == id )
            return (*iter);
    }
    
    return NULL;
}

DecoObject* ObjectMgr::findDeco(cocos2d::CCPoint position)
{
    std::vector<DecoObject*>::iterator iter;
    for(iter = m_vDecoObjects.begin(); iter != m_vDecoObjects.end(); ++iter)
    {
        if((*iter)->GetFixtureList()->TestPoint(b2Vec2(position.x/PTM_RATIO, position.y/PTM_RATIO)))
            return (*iter);
    }
    
    return NULL;
}

DecoObject* ObjectMgr::findDeco(int id)
{
    std::vector<DecoObject*>::iterator iter;
    for(iter = m_vDecoObjects.begin(); iter != m_vDecoObjects.end(); ++iter)
    {
        if( (*iter)->m_id == id )
        {
            return (*iter);
        }
    }
    
    return NULL;
}

void ObjectMgr::update(float dt)
{
    std::vector<FishObject*>::iterator iter;
    for(iter = m_vFishObjects.begin(); iter != m_vFishObjects.end(); ++iter)
        (*iter)->update(dt);
    
    int size = m_vFoods.size();
    for(int i=0; i<size; ++i)
    {
        if(m_vFoods[i]->isRemoveOn)
        {
            b2World *pWorld = m_vFoods[i]->GetBody()->GetWorld();
            pWorld->DestroyBody(m_vFoods[i]->GetBody());
            m_pScene->removeChild(m_vFoods[i], true);
            SAFE_DELETE(m_vFoods[i]);
            m_vFoods.erase(m_vFoods.begin() + i);
        }
    }
    
    size = m_vBubbles.size();
    for(int i=0; i<size; ++i)
    {
        if(m_vBubbles[i]->m_isRemove)
        {
            b2World *pWorld = m_vBubbles[i]->GetBody()->GetWorld();
            pWorld->DestroyBody(m_vBubbles[i]->GetBody());
            m_pScene->removeChild(m_vBubbles[i], true);
            SAFE_DELETE(m_vBubbles[i]);
            m_vBubbles.erase(m_vBubbles.begin() + i);
        }
    }
}

void ObjectMgr::addFood(cocos2d::CCPoint position)
{
    Food *pFood = new Food(m_pSystem, m_pScene);
    pFood->init(m_pSystem->GetWorld(), position);
    m_pScene->addChild(pFood);
    m_vFoods.push_back(pFood);
}

void ObjectMgr::addBubble(cocos2d::CCPoint position)
{
    Bubble *pBubble = new Bubble(m_pSystem, m_pScene);
    pBubble->init(m_pSystem->GetWorld(), position);
    m_pScene->addChild(pBubble);
    m_vBubbles.push_back(pBubble);
}

Egg* ObjectMgr::findEgg(cocos2d::CCPoint position)
{
    std::vector<Egg*>::iterator iter;
    for(iter = m_vEggObjects.begin(); iter != m_vEggObjects.end(); ++iter)
    {
        b2Fixture *fix = (*iter)->GetFixtureList();
        if(fix)
        if(fix->TestPoint(b2Vec2(position.x/PTM_RATIO, position.y/PTM_RATIO)))
            return (*iter);
    }
    
    return NULL;
}

Egg* ObjectMgr::findEgg(int id)
{
    std::vector<Egg*>::iterator iter;
    for(iter = m_vEggObjects.begin(); iter != m_vEggObjects.end(); ++iter)
    {
        if( (*iter)->m_id == id )
            return (*iter);
    }
    
    return NULL;
}