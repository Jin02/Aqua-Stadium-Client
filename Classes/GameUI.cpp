//
//  GameUI.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 8..
//
//

#include "GameUI.h"
#include "Utility.h"

using namespace cocos2d;

GameUI::GameUI(GameScene *pScene)
{
    m_pScene = pScene;    
    m_pMenu = NULL;
}

GameUI::~GameUI()
{
    m_pMenu->removeAllChildrenWithCleanup(true);
    removeAllChildrenWithCleanup(true);
    
    for(int i=0; i<UI_MAXNUM; ++i)
        delete m_pMenuItemAry->objectAtIndex(i);
    
    SAFE_DELETE(m_pMenuItemAry);
}

bool GameUI::init(UI_BUTTON btFriend, UI_BUTTON btShop, UI_BUTTON btFoodInven)
{
    CCLayer::init();
    m_pMenuItemAry = new CCArray(UI_MAXNUM);
    CCMenuItemImage *pMenuItem[UI_MAXNUM];
    
    for(int i=0; i<UI_MAXNUM; ++i) pMenuItem[i] = new CCMenuItemImage;

    pMenuItem[UI_FRIEND]->initWithNormalImage(btFriend.normalImage, btFriend.selectImage, NULL, btFriend.pTarget, btFriend.handler);
    pMenuItem[UI_SHOP]->initWithNormalImage(btShop.normalImage, btShop.selectImage, NULL, btShop.pTarget, btShop.handler);
    pMenuItem[UI_FOODINVEN]->initWithNormalImage(btFoodInven.normalImage, btFoodInven.selectImage, NULL, btFoodInven.pTarget, btFoodInven.handler);
    
    pMenuItem[UI_FRIEND]->setPosition(btFriend.position);
    pMenuItem[UI_SHOP]->setPosition(btShop.position);
    pMenuItem[UI_FOODINVEN]->setPosition(btFoodInven.position);
    
    for(int i=0; i<UI_MAXNUM; ++i)
    {
        //pMenuItem[i]->setScale(0.7f);
        m_pMenuItemAry->addObject(pMenuItem[i]);
    }
    m_pMenu = new CCMenu;
    m_pMenu->initWithArray(m_pMenuItemAry);
    
    addChild(m_pMenu);
    
    m_pLevel = new CCSprite;
    m_pLevel->initWithFile("Image/level.png");
    m_pLevel->setAnchorPoint(ccp(0,0));
    m_pLevel->setPosition(ccp(10, 550));
//    m_pLevel->setScale(0.5);
    addChild(m_pLevel);
    
    return true;
}

void GameUI::SetFoodIconColor(cocos2d::ccColor3B color)
{
    ((CCMenuItemImage*)m_pMenuItemAry->objectAtIndex(UI_FOODINVEN))->setColor(color);
}
