//
//  GameScene.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

#include "cocos2d.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) if(p){ delete p; p = NULL; }
#endif

class GameScene : public cocos2d::CCLayer
{
private:
    cocos2d::CCScene            *m_pScene;
    
public:
    GameScene();
    ~GameScene();
    
public:
    virtual bool init();
    
public:
    inline cocos2d::CCScene* GetScene() { return m_pScene; }
};