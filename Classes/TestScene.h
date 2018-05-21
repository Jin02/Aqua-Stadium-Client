//
//  TestScene.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

#include "GameScene.h"
#include "GameSystem.h"
#include "GameUI.h"
#include "PlayerUI.h"
#include "Shop.h"

#define PTM_RATIO 32

class TestScene : public GameScene
{
private:
    GameSystem              *m_pGameSystem;
    GameUI                  *m_pUI;
    PlayerUI                *m_pPlayerUI;
    Player                  *m_pPlayer;
    Shop                    *m_pShop;
    
private:
    cocos2d::CCSprite       *m_pBackGround;
    FishObject              *m_pFish[2];
    
private:
    bool                    m_isFood;
    bool                    m_isDecoAdd;
    cocos2d::CCSprite       *m_pAddArea;
    int                     m_tap;
    int                     m_addShopIdx;
    
private:
    b2MouseJoint            *m_pJoint;
    cocos2d::CCSprite       *m_pTitle;
    cocos2d::CCSprite       *m_pTmpBack;
    bool                     m_isTitle;
    
public:
    TestScene();
    ~TestScene();
    
public:
    bool init();
    void update(float dt);
    
public:
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

private:
    void _friendUI(cocos2d::CCObject *pSender);
    void _shopUI(cocos2d::CCObject *pSender);
    void _foodUI(cocos2d::CCObject *pSender);
    void _titleOff();
    
private:
    void _addBubble();
    
public:
    void addEgg(int i);
    void addDeco(int tap, int i);
};