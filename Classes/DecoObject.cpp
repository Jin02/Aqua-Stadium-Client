//
//  DecoObject.cpp
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#include "DecoObject.h"
#include "Utility.h"

using namespace cocos2d;
using namespace std;

DecoObject::DecoObject()
{
}

DecoObject::~DecoObject()
{    
    for(int i=0; i<4; ++i)
        delete m_pSpriteFrame[i];
        
    if(m_pAnimation)
    {
        delete m_pAnimation;
        m_pAnimation = NULL;
    }
}

bool DecoObject::init(cocos2d::CCTexture2D *pTex, b2World *pWorld, CCPoint position, float delay, std::vector< POINT<float> > vertices, CCPoint anchorPoint, int animationNum, bool isEffect)
{
    if(PhysicsObject::init(static_cast<CCSpriteFrame*>(NULL), vertices, pWorld, b2_staticBody, position, 50.f) == false)
        return false;
    
    float witdh         = pTex->getContentSize().width;
    float height        = pTex->getContentSize().height;
    float frameSize     = witdh / animationNum;
    
    m_pAnimation        = new CCAnimation;
    m_pAnimation->init();
    m_pAnimation->setDelayPerUnit(delay);
    m_pAnimation->setRestoreOriginalFrame(true);
    m_pAnimation->setLoops(-1);
    
    for(int i=0; i<animationNum; ++i)
    {
        CCSpriteFrame *pFrame = new CCSpriteFrame;
        pFrame->initWithTexture(pTex, CCRectMake(i*frameSize, 0, frameSize, height));
        
        m_pAnimation->addSpriteFrame(pFrame);
        m_pSpriteFrame[i] = pFrame;
    }
    
    m_pAnimate = new CCAnimate;
    m_pAnimate->initWithAnimation(m_pAnimation);
    
    SetSpriteFrame(m_pSpriteFrame[0]);
    m_pSprite->runAction(m_pAnimate);

    float d = 0.f;
    if(animationNum == 4) d = -30;
    
    SetTransForm(ccp(position.x, m_pSprite->getContentSize().height/2 + d), 0);
//    m_pSprite->setScale(0.5f);

    return true;
}

void DecoObject::SetBody(b2Body *pBody)
{
    m_pBody = pBody;
}
