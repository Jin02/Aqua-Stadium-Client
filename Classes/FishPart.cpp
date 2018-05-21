//
//  FishPart.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 10. 18..
//
//

#include "FishPart.h"
#include "Utility.h"

using namespace cocos2d;

FishPart::FishPart()
{
    m_pAnimation    = NULL;
    m_pAnimate      = NULL;
    memset(m_pSpriteFrame, 0, sizeof(CCSpriteFrame*)
                                        * FISH_ANIMATION_FRAME_NUM);
}

FishPart::~FishPart()
{
    stopAllActions();
    removeAllChildrenWithCleanup(true);
    
    SAFE_DELETE(m_pAnimate);
    SAFE_DELETE(m_pAnimation);
    for(int i=0; i<FISH_ANIMATION_TYPE_NUM; ++i)
        SAFE_DELETE(m_pSpriteFrame[i]);
}

bool FishPart::init(cocos2d::CCTexture2D *pTex, float delay, FISHPART_TYPE type)
{
    if(CCSprite::initWithTexture(pTex) == false)
        return false;

    if( type == FISHPART_TYPE_BODY || type == FISHPART_TYPE_EYE)
        return true;
    
    m_pAnimation = new CCAnimation;
    m_pAnimation->init();
    m_pAnimation->setDelayPerUnit(delay);
    m_pAnimation->setRestoreOriginalFrame(true);
    m_pAnimation->setLoops(-1);
    
    float witdh         = pTex->getContentSize().width;
    float height        = pTex->getContentSize().height;
    float frameSize     = witdh / FISH_ANIMATION_FRAME_NUM;
    
    for(int i=0; i<FISH_ANIMATION_FRAME_NUM; ++i)
    {
        CCSpriteFrame *pFrame = new CCSpriteFrame;
        pFrame->initWithTexture(pTex, CCRectMake(i*frameSize, 0, frameSize, height));
        
        m_pAnimation->addSpriteFrame(pFrame);
        m_pSpriteFrame[i] = pFrame;
    }
    
    m_pAnimate = new CCAnimate;
    m_pAnimate->initWithAnimation(m_pAnimation);
    
    setTexture(m_pSpriteFrame[0]->getTexture());
    setTextureRect(m_pSpriteFrame[0]->getRect());
    this->runAction(m_pAnimate);
    
    return true;
}