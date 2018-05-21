//
//  PhysicsObject.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 10. 12..
//
//

#pragma once

#include "Box2D.h"
#include "cocos2d.h"
#include <vector>
#include <list>
#include "Utility.h"

class PhysicsObject : public cocos2d::CCLayer
{
protected:
    b2Body                  *m_pBody;
    cocos2d::CCSprite       *m_pSprite;
    
public:
    PhysicsObject();
    ~PhysicsObject();
    
private:
    bool _initSprite(cocos2d::CCTexture2D *pTex);
    bool _initSprite(cocos2d::CCSpriteFrame *pFrame);
    bool _initSprite(cocos2d::CCSprite *pSprite);
    
    void _initShape(b2World *pWorld, float &radius, cocos2d::CCPoint &position, float &gravityScale, float &density, float &friction, b2BodyType &type);
    void _initShape(b2World *pWorld, std::vector< POINT<float> > &vertices, cocos2d::CCPoint &position, float &gravityScale, float &density, float &friction, b2BodyType &type);

protected:
    b2Vec2* _createVertexAry(std::vector< POINT<float> > &vDBPosition);
    
public:
    bool init(cocos2d::CCTexture2D *pTex, std::vector< POINT<float> > vertices, b2World *pWorld, b2BodyType type, cocos2d::CCPoint position = cocos2d::CCPoint(0,0), float gravityScale = 0.f, float density = 0.f, float friction = 0.f);

    bool init(cocos2d::CCTexture2D *pTex, float radius, b2World *pWorld, b2BodyType type, cocos2d::CCPoint position = cocos2d::CCPoint(0,0), float gravityScale = 0.f, float density = 0.f, float friction = 0.f);

    bool init(cocos2d::CCSpriteFrame *pFrame, std::vector< POINT<float> > vertices, b2World *pWorld, b2BodyType type, cocos2d::CCPoint position = cocos2d::CCPoint(0,0), float gravityScale = 0.f, float density = 0.f, float friction = 0.f);
    
    bool init(cocos2d::CCSpriteFrame *pFrame, float radius, b2World *pWorld, b2BodyType type, cocos2d::CCPoint position = cocos2d::CCPoint(0,0), float gravityScale = 0.f, float density = 0.f, float friction = 0.f);
    
    bool init(cocos2d::CCSprite *pSprite, std::vector< POINT<float> > vertices, b2World *pWorld, b2BodyType type, cocos2d::CCPoint position = cocos2d::CCPoint(0,0), float gravityScale = 0.f, float density = 0.f, float friction = 0.f);
    
    bool init(cocos2d::CCSprite *pSprite, float radius, b2World *pWorld, b2BodyType type, cocos2d::CCPoint position = cocos2d::CCPoint(0,0), float gravityScale = 0.f, float density = 0.f, float friction = 0.f);
    
public:
    void addShape(b2Shape *pShape, float density, float friction);
    
public:
    void SetTexture(cocos2d::CCTexture2D *pTex);
    void SetSpriteFrame(cocos2d::CCSpriteFrame *pFrame);

    void SetTransForm(cocos2d::CCPoint p, float radian);
    void SetAngle(float radian);
    void SetGravityScale(float f);
    
    b2Fixture* GetFixtureList()
    {
        if(m_pBody == NULL) return NULL;
        return m_pBody->GetFixtureList();
    }
    inline b2Body* GetBody() { return m_pBody; }
    cocos2d::CCSize getContentSize();
};