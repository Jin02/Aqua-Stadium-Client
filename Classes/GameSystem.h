//
//  GameSystem.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 6..
//
//

#pragma once

#include "Thread.h"
#include "cocos2d.h"
#include "Player.h"
#include "Network.h"
#include <vector>
#include "FishObject.h"
#include "DecoObject.h"
#include "InfoMgr.h"
#include <string>
#include "GameScene.h"
#include "Box2D.h"
#include "ObjectMgr.h"
#include "Food.h"

struct ADDFISH
{
    FishStatus status;
    CommonFishPartInfo eye, body, mouth, fins, pattern;
    double completeTime;
    int id;
    bool isNew;
};

struct ADDDECO
{
    DecorationInfo *pInfo;
    cocos2d::CCPoint position;
    int id;
    bool isNew;
};

class GameSystem : public Thread
{
private:
    GameScene       *m_pScene;
    Network         *m_pNetwork;
    InfoMgr         *m_pInfoMgr;
    b2World         *m_pWorld;
    b2Body          *m_pGroundBody;
    ObjectMgr       *m_pObjectMgr;
    Player          *m_pPlayer;
    
public:
    GameSystem(GameScene *pScene, Player *pPlayer);
    ~GameSystem();
    
private:
     void _initPhysics();
    
public:
    bool init();

public:
    FishObject* addFish(FishStatus status, cocos2d::CCPoint position, CommonFishPartInfo eye, CommonFishPartInfo body, CommonFishPartInfo fin, double compTime, bool isNew, int id, Tag tag = Tag());
    
    void addDeco(int id, DECORATION_TYPE type, cocos2d::CCPoint position, bool isNew);
    void addDeco(const char *name, DECORATION_TYPE type, cocos2d::CCPoint position, bool isNew);

    bool Crossbreed(FishObject *pFish1, FishObject *pFish2, float CBTime = 0, float CBComTime = 30.f);
    void FishMix(FishObject *pFish1, FishObject *pFish2);
    
    void addFood(cocos2d::CCPoint position);

private:
    bool _removeNetworkObject();    
    void _fail(Thread *pThread, void *parameter);
    void _addEgg(DNA &dna, float nowTime, cocos2d::CCPoint position, bool isNew, int id = -1);
    
public:
    void update(float dt);
    inline ObjectMgr *GetObjMgr() { return m_pObjectMgr; }
    inline b2Body* GetGroundBody() { return m_pGroundBody; }
    inline b2World* GetWorld() { return m_pWorld; }
    inline InfoMgr* GetInfoMgr() { return m_pInfoMgr;}
};