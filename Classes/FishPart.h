//
//  FishPart.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 10. 18..
//
//

#pragma once

#include "cocos2d.h"
#include "PhysicsObject.h"
#include "FishPartInfo.h"

enum FISH_ANIMATION_TYPE
{
    FISH_ANIMATION_TYPE_NORMAL,
    FISH_ANIMATION_TYPE_EAT,
    FISH_ANIMATION_TYPE_NUM
};

#define FISH_ANIMATION_FRAME_NUM 3

class FishPart : public cocos2d::CCSprite
{
protected:
    cocos2d::CCAnimate      *m_pAnimate;
    cocos2d::CCAnimation    *m_pAnimation;
    cocos2d::CCSpriteFrame  *m_pSpriteFrame[FISH_ANIMATION_FRAME_NUM];
    
public:
    FishPart();
    ~FishPart();
    
public:
    bool init(cocos2d::CCTexture2D *pTex, float delay, FISHPART_TYPE type);
};