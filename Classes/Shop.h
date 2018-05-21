//
//  Shop.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "PlayerUI.h"

class GameScene;

enum MENU_TAP
{
    MENU_TAP_FISH,
    MENU_TAP_STONE,
    MENU_TAP_CORALREEF,
    MENU_TAP_NUM
};

class Shop : public cocos2d::CCLayer
{
private:
    GameScene   *m_pScene;
    Player      *m_pPlayer;
    PlayerUI    *m_pPlayerUI;
    
    int          m_phase;
    
private:
    cocos2d::CCSprite       *m_pBackground;
    cocos2d::CCLabelTTF     *m_pGoldLabel;
    cocos2d::CCLabelTTF     *m_pCashLabel;
    
    cocos2d::CCMenu             *m_pMenu;
    cocos2d::CCMenuItemImage    *m_pExit;
    cocos2d::CCMenuItemImage    *m_pTap[MENU_TAP_NUM];
    cocos2d::CCSprite           *m_pTapUnLock[MENU_TAP_NUM];
    cocos2d::CCSprite           *m_pTapConponent[MENU_TAP_NUM];
    
    cocos2d::CCSprite           *m_pItemLock[3];
    cocos2d::CCSprite           *m_pItem[10];
    
public:
    Shop(Player *pPlayer, GameScene *pScene, PlayerUI *pPlayerUI);
    ~Shop();
    
public:
    bool init();
    
private:
    void _tapLock(int unlock);
    
    void _btExit();
    void _tapFish();
    void _tapStone();
    void _tapCoralReef();
    
    void _buyCoralReef(int i);
    void _buyFish(int i);
    void _buyStone(int i);
    
    void _buyItem(int i);
    
public:
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
};