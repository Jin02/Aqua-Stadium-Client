//
//  FishObject.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

#include "cocos2d.h"
#include "Box2D.h"
#include "PhysicsObject.h"
#include <vector>
#include "FishPart.h"
#include "FinsInfo.h"
#include "BodyInfo.h"
#include "FishPartInfo.h"
#include "Mouth.h"
#include "Timer.h"
#include "DNA.h"
#include "FishStatus.h"

class GameSystem;

#define FISH_GRAVITYSCALE 0
#define BADY_DENSITY    0.f
#define BADY_FRICTION   0.2f
#define FIN_DENSITY     0.f
#define FIN_FRICTION    0.2f

enum FOOD_TYPE
{
    FOOD_TYPE_NORMAL,
    FOOD_TYPE_EGG
};

//바디_이름_num
//핀_위치_이름_num
//눈_이름_num
//입_이름_num

class FishObject : public PhysicsObject
{
private:
    GameSystem          *m_pSystem;
    
private:
    FishPart            *m_pEye;
    FishPart            *m_pFin[FIN_TYPE_NUM];
    FishPart            *m_pBody;
    FishPart            *m_pPattern;

    DNA                 *m_pDNA;
    FishStatus          *m_pStatus;

    std::vector< b2Vec2 > m_vOriginvertex[4];
    bool                m_isGrowEnd;
    
    cocos2d::CCOrbitCamera *m_pFlipAction;
    bool                    m_isLeft;
    b2Joint             *m_pJoint;
    FishObject          *m_pOtherFish;
    
    bool                m_isSchedule;
    
public:
    int                 m_id;
    
private:
    /*
     성장에 필요한 데이터들을 담아와야해
     */
    
private:
    float               m_cbCompleteTime;
    float               m_cbNowTime;
    
private:
    cocos2d::CCParticleFlower*    m_pFlower;
    
public:
    FishObject(DNA &dna, FishStatus &status, GameSystem *pSystem);
    ~FishObject();
    
private:
    void _calcPhysicsVertex(POINT<float> *pPos, cocos2d::CCSize &size);
    void _calcFinVertex(std::vector< POINT<float> > &finVertex, cocos2d::CCSize &bodySize, POINT<float> bodyFinAveragePos );
    void _rotatePhysicsVertex(std::vector< POINT<float> > &vertex, float degree);
    
private:
    void _initFinPhysics(cocos2d::CCSize bodySize, float density, float friction, float *pGetFinAngleAry);
    void _loadPart(const char *name, FISHPART_TYPE type, float delay, FishPart *pPart);
    void _initSprite();
    
private:
    void _fishStatusUpdate();
    
public:
    void crossbreedOff();
    
private:
    void _flipXVertex();
    void _flipBodySprite();
    void _growCompleteEffect();
    void _particleEnd();

public:
    bool init(b2World *pWorld, cocos2d::CCPoint position);
    void update(float dt);
    bool isGrowEnd();
    
    void flipFish();
    void testMovePattern(float t);
    void MoveOn();
    void MoveOff();
    
    bool Crossbreed(FishObject *pOtherFish, b2Joint *pJoint, float CBTime, float CBComTime);
    
    void eat(FOOD_TYPE t);
    
    
public:
    inline FishStatus* GetStatus() { return m_pStatus; }
    inline const cocos2d::CCPoint &getPositon() { return m_pSprite->getPosition(); }
    inline b2Body* GetBody() { return PhysicsObject::m_pBody; }
    inline DNA* GetDNA() { return m_pDNA; }
    bool isCrossbreed();
    inline bool isLeft() { return m_isLeft; }
    bool isJointOn();
    
    void GetName(char *pTxt);
};