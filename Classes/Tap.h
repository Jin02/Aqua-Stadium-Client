//
//  Tap.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 18..
//
//

#pragma once

#include "cocos2d.h"

class Tap : public cocos2d::CCNode
{
private:
    int m_type;
    cocos2d::CCSprite   *m_pContent;
    cocos2d::CCSprite   *m_pSelectTap;
    cocos2d::CCSprite   *m_pNotSelectTap;
    
public:
    Tap();
    ~Tap();
    
public:
    bool init(cocos2d::CCPoint position, bool isSelect, const char *imgPath, int type);

public:
    void select();
    void notSelect();
    int GetType() { return m_type; }
};