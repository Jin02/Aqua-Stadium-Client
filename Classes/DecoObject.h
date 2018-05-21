//
//  DecoObject.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

#include "cocos2d.h"
#include "Box2D.h"
#include "PhysicsObject.h"

class DecoObject : public PhysicsObject
{
private:
    cocos2d::CCAnimation                    *m_pAnimation;
    cocos2d::CCAnimate                      *m_pAnimate;
    cocos2d::CCSpriteFrame                  *m_pSpriteFrame[10];
    
public:
    int                                     m_id;

public:
    DecoObject();
    ~DecoObject();
    
public:
    bool init(cocos2d::CCTexture2D *pTex, b2World *pWorld, cocos2d::CCPoint position, float delay, std::vector< POINT<float> > vertices, cocos2d::CCPoint anchorPoint, int animationNum, bool isEffect);
    
   inline void SetBody(b2Body *pBody);
};