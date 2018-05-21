//
//  GameUI.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 8..
//
//

#pragma once

#include "cocos2d.h"
#include "GameScene.h"

enum UI
{
    UI_FRIEND,
    UI_SHOP,
    UI_FOODINVEN,
    UI_MAXNUM
};

struct UI_BUTTON
{
    const char *normalImage;
    const char *selectImage;
    cocos2d::CCObject *pTarget;
    cocos2d::SEL_MenuHandler handler;
    cocos2d::CCPoint position;
    
    UI_BUTTON()
    : normalImage(NULL), selectImage(NULL), pTarget(NULL), handler(NULL), position(ccp(0,0)) {}
    UI_BUTTON(const char* normalImg, const char *selectImg, cocos2d::CCObject *pTarget, cocos2d::SEL_MenuHandler handler, cocos2d::CCPoint position)
    {
        this->normalImage = normalImg;
        this->selectImage = selectImg;
        this->pTarget = pTarget;
        this->handler = handler;
        this->position = position;
    }
};

class GameUI : public cocos2d::CCLayer
{
private:
    cocos2d::CCArray            *m_pMenuItemAry;

    cocos2d::CCMenu             *m_pMenu;
    GameScene                   *m_pScene;
    
    cocos2d::CCSprite           *m_pLevel;
    
public:
    GameUI(GameScene *pScene);
    ~GameUI();
    
public:
    bool init(UI_BUTTON btFriend, UI_BUTTON btShop, UI_BUTTON btFoodInven);
    void SetFoodIconColor(cocos2d::ccColor3B color);
};