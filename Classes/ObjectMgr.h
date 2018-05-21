//
//  ObjectMgr.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 6..
//
//

#pragma once

#include "ObjIdxMgr.h"
#include "cocos2d.h"
#include "DecorationInfo.h"
#include "FishPartInfo.h"
#include "FishStatus.h"
#include "FishObject.h"
#include "DecoObject.h"
#include "GameScene.h"
#include "InfoMgr.h"
#include "Egg.h"
#include "Food.h"
#include "Bubble.h"

class GameSystem;

class ObjectMgr
{
private:
    GameSystem      *m_pSystem;
    GameScene       *m_pScene;
    ObjIdxMgr       *m_pIdxMgr;
    InfoMgr         *m_pInfoMgr;
    
    std::vector<DecoObject*>    m_vDecoObjects;
    std::vector<FishObject*>    m_vFishObjects;
    std::vector<Egg*>           m_vEggObjects;
    std::vector<Food*>          m_vFoods;
    std::vector<Bubble*>        m_vBubbles;
    
public:
    ObjectMgr(GameScene *pScene, InfoMgr *pInfoMgr, GameSystem *pSystem);
    ~ObjectMgr();
    
public:
    FishObject* addFish(FishStatus &status, cocos2d::CCPoint position, CommonFishPartInfo eye, CommonFishPartInfo body, CommonFishPartInfo fin, double completeTime, int id, bool isNew, Tag tag);
  
    void removeFish(FishObject *pFish);
    
    void addDecoration(DecorationInfo *pInfo, cocos2d::CCPoint position, int id, bool isNew);
    void removeDeco(DecoObject *pObj);
    
    void addEgg(Egg *pEgg, bool isNew, int id);
    void removeEgg(Egg *pEgg);
    
    void addFood(cocos2d::CCPoint position);
    void addBubble(cocos2d::CCPoint position);
    
public:
    void update(float dt);

public:
    FishObject* findFish(cocos2d::CCPoint position);
    FishObject* findFish(int id);
    
    DecoObject* findDeco(cocos2d::CCPoint position);
    DecoObject* findDeco(int id);
    
    Egg* findEgg(cocos2d::CCPoint position);
    Egg* findEgg(int id);
    
public:
    inline std::vector<FishObject*> GetFishObjects() { return m_vFishObjects; }
};