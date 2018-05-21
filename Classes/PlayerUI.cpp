//
//  PlayerUI.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 16..
//
//

#include "PlayerUI.h"

using namespace cocos2d;

PlayerUI::PlayerUI()
{
    m_pGoldLabel = NULL;
    m_pGoldSprite = NULL;
    m_pCashLabel = NULL;
    m_pCashSprite = NULL;
}

PlayerUI::~PlayerUI()
{
    
}

bool PlayerUI::init(int fontSize, cocos2d::CCPoint goldPos, cocos2d::CCPoint cashPos)
{
    CCLayer::init();
    m_pGoldLabel = new CCLabelTTF;
    m_pGoldSprite = new CCSprite;
    m_pCashLabel = new CCLabelTTF;
    m_pCashSprite = new CCSprite;
    
    m_pGoldSprite->initWithFile("Common/Money.png");
    m_pGoldSprite->setPosition(goldPos);
    m_pGoldSprite->setAnchorPoint(ccp(0,0));
    m_pGoldSprite->setScale(0.7);
    
    m_pCashSprite->initWithFile("Common/cash.png");
    m_pCashSprite->setPosition(cashPos);
    m_pCashSprite->setAnchorPoint(ccp(0,0));
    m_pCashSprite->setScale(0.7);
    
    m_pGoldLabel->initWithString("0", "굴림", fontSize);
    m_pCashLabel->initWithString("0", "굴림", fontSize);
    m_pGoldLabel->setAnchorPoint(ccp(0,0));
    m_pCashLabel->setAnchorPoint(ccp(0,0));
    m_pGoldLabel->setPosition(ccp(goldPos.x + 50, goldPos.y));
    m_pCashLabel->setPosition(ccp(cashPos.x + 50, cashPos.y));
    m_pGoldLabel->setColor(ccc3(0, 0, 0));
    m_pCashLabel->setColor(ccc3(0, 0, 0));

    addChild(m_pGoldLabel);
    addChild(m_pGoldSprite);
    addChild(m_pCashLabel);
    addChild(m_pCashSprite);
    
    setScale(2.0f);
    
    return true;
}

void PlayerUI::SetCashValue(int n)
{
    char txt[10];
    sprintf(txt, "%d", n);
    m_pCashLabel->setString(txt);
}

void PlayerUI::SetMoneyValue(int n)
{
    char txt[10];
    sprintf(txt, "%d", n);
    m_pGoldLabel->setString(txt);
}