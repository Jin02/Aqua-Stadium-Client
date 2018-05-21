//
//  PlayerUI.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 16..
//
//

#pragma once

#include "cocos2d.h"

class PlayerUI : public cocos2d::CCLayer
{
private:
    cocos2d::CCSprite           *m_pGoldSprite;
    cocos2d::CCLabelTTF         *m_pGoldLabel;
    
    cocos2d::CCSprite           *m_pCashSprite;
    cocos2d::CCLabelTTF         *m_pCashLabel;
    
public:
    PlayerUI();
    ~PlayerUI();
    
public:
    bool init(int fontSize, cocos2d::CCPoint goldPos, cocos2d::CCPoint cashPos);

public:
    void SetCashValue(int n);
    void SetMoneyValue(int n);
};