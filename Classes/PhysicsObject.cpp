//
//  PhysicsObject.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 10. 12..
//
//

#include "PhysicsObject.h"
#include "Utility.h"

using namespace cocos2d;
using namespace std;

PhysicsObject::PhysicsObject()
{
    m_pBody         = NULL;
    m_pSprite       = NULL;
}

PhysicsObject::~PhysicsObject()
{
    removeAllChildrenWithCleanup(true);
    
    if(m_pSprite)
    {
        delete m_pSprite;
        m_pSprite = NULL;
    }
}

bool PhysicsObject::_initSprite(cocos2d::CCTexture2D *pTex)
{
    if( CCLayer::init() == false )
        return false;
    
    m_pSprite = new CCSprite;
    if(pTex)        m_pSprite->initWithTexture(pTex);
    else            m_pSprite->init();
    
    addChild(m_pSprite);

    return true;
}

bool PhysicsObject::_initSprite(cocos2d::CCSpriteFrame *pFrame)
{
    if( CCLayer::init() == false )
        return false;
    
    m_pSprite = new CCSprite;
    
    if(pFrame)      m_pSprite->initWithSpriteFrame(pFrame);
    else            m_pSprite->init();
    
    addChild(m_pSprite);
    
    return true;
}

bool PhysicsObject::_initSprite(cocos2d::CCSprite *pSprite)
{
    if( CCLayer::init() == false )
        return false;
    
    m_pSprite = pSprite;
    addChild(m_pSprite);
    
    return true;    
}

bool PhysicsObject::init(cocos2d::CCTexture2D *pTex, std::vector< POINT<float> > vertices, b2World *pWorld, b2BodyType type, cocos2d::CCPoint position, float gravityScale, float density, float friction)
{
    if(_initSprite(pTex) == false)
        return false;
    
    
    _initShape(pWorld, vertices, position, gravityScale, density, friction, type);
        
    return true;
}

bool PhysicsObject::init(cocos2d::CCTexture2D *pTex, float radius, b2World *pWorld, b2BodyType type, cocos2d::CCPoint position, float gravityScale, float density, float friction)
{
    if(_initSprite(pTex) == false)
        return false;

    m_pSprite->setScale(2.0f);
    _initShape(pWorld, radius, position, gravityScale, density, friction, type);
    
    return true;
}

bool PhysicsObject::init(cocos2d::CCSpriteFrame *pFrame, std::vector< POINT<float> > vertices, b2World *pWorld, b2BodyType type, cocos2d::CCPoint position, float gravityScale, float density, float friction)
{
    if(_initSprite(pFrame) == false) return false;
    

    _initShape(pWorld, vertices, position, gravityScale, density, friction, type);
    
    return true;
}

bool PhysicsObject::init(cocos2d::CCSpriteFrame *pFrame, float radius, b2World *pWorld, b2BodyType type, cocos2d::CCPoint position, float gravityScale , float density, float friction)
{
     if(_initSprite(pFrame) == false) return false;   

    _initShape(pWorld, radius, position, gravityScale, density, friction, type);
    
    return true;
}

bool PhysicsObject::init(cocos2d::CCSprite *pSprite, std::vector< POINT<float> > vertices, b2World *pWorld, b2BodyType type, cocos2d::CCPoint position, float gravityScale, float density, float friction)
{
    if(_initSprite(pSprite) == false ) return false;
    
    _initShape(pWorld, vertices, position, gravityScale, density, friction, type);
    
    return true;
}

bool PhysicsObject::init(cocos2d::CCSprite *pSprite, float radius, b2World *pWorld, b2BodyType type, cocos2d::CCPoint position, float gravityScale, float density, float friction)
{
    if(_initSprite(pSprite) == false ) return false;
    
    _initShape(pWorld, radius, position, gravityScale, density, friction, type);
    
    return true;
}

void PhysicsObject::_initShape(b2World *pWorld, float &radius, cocos2d::CCPoint &position, float &gravityScale, float &density, float &friction, b2BodyType &type)
{
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.position.Set(position.x/PTM_RATIO, position.y/PTM_RATIO);
    bodyDef.gravityScale = gravityScale;
    
    m_pBody = pWorld->CreateBody(&bodyDef);
    
    b2CircleShape circle;
    circle.m_radius = radius*2 / PTM_RATIO;
//    b2PolygonShape circle;
//    circle.SetAsBox(0.5, 0.5);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.restitution = 0.0f;
    
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    
    m_pBody->CreateFixture(&fixtureDef);
    m_pBody->SetUserData(m_pSprite);
}

void PhysicsObject::_initShape(b2World *pWorld, std::vector< POINT<float> > &vertices, cocos2d::CCPoint &position, float &gravityScale, float &density, float &friction, b2BodyType &type)
{    
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.position.Set(position.x/PTM_RATIO, position.y/PTM_RATIO);
    bodyDef.gravityScale = gravityScale;
    
    m_pBody = pWorld->CreateBody(&bodyDef);
    
    b2PolygonShape polygon;
    
    b2Vec2 *pVecAry = _createVertexAry(vertices);
    polygon.Set(pVecAry, vertices.size());

    delete[] pVecAry;

    addShape(&polygon, density, friction);
    m_pBody->SetUserData(m_pSprite);
    SetTransForm(position, 0.f);
}

void PhysicsObject::addShape(b2Shape *pShape, float density, float friction)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = pShape;
    fixtureDef.restitution = 0.0f;
    
    fixtureDef.density  = density;
    fixtureDef.friction = friction;
    
    m_pBody->CreateFixture(&fixtureDef);
}

void PhysicsObject::SetTexture(cocos2d::CCTexture2D *pTex)
{
    m_pSprite->setTexture(pTex);
}

void PhysicsObject::SetSpriteFrame(CCSpriteFrame *pFrame)
{
    m_pSprite->setTexture(pFrame->getTexture());
    m_pSprite->setTextureRect(pFrame->getRect());
}

void PhysicsObject::SetTransForm(cocos2d::CCPoint p, float radian)
{
    b2Vec2  v(p.x/PTM_RATIO, p.y/PTM_RATIO);
    
    m_pBody->SetTransform(v, radian);

    m_pSprite->setPosition(p);
    m_pSprite->setRotation(CC_RADIANS_TO_DEGREES(radian));
}

void PhysicsObject::SetAngle(float radian)
{
    m_pBody->SetTransform(m_pBody->GetTransform().p, radian);
}

void PhysicsObject::SetGravityScale(float f)
{
    m_pBody->SetGravityScale(f);
}

b2Vec2* PhysicsObject::_createVertexAry(std::vector< POINT<float> > &vDBPosition)
{
    b2Vec2 *ary = new b2Vec2[vDBPosition.size()];
    
    vector< POINT<float> >::iterator iter;
    int i = 0;
    for(iter = vDBPosition.begin(); iter != vDBPosition.end(); ++iter, ++i )
        ary[i].Set((*iter).x/PTM_RATIO, (*iter).y/PTM_RATIO);
        
    return ary;
}

cocos2d::CCSize PhysicsObject::getContentSize()
{
    return m_pSprite->getContentSize();
}