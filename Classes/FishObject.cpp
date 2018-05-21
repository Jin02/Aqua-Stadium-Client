//
//  FishObject.cpp
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#include "FishObject.h"
#include "GameSystem.h"

using namespace cocos2d;
using namespace std;

FishObject::FishObject(DNA &dna, FishStatus &status, GameSystem *pSystem)
{
    m_pEye          = NULL;
    memset(m_pFin, 0, sizeof(FishPart*) * FIN_TYPE_NUM);
    m_pBody         = NULL;
    m_pDNA          = new DNA(dna);
    m_isGrowEnd     = false;
    m_pStatus       = new FishStatus(status);
    m_isLeft        = true;
    m_pFlipAction        = NULL;
    m_pJoint        = NULL;
    m_pOtherFish    = NULL;
    m_cbNowTime    = 0;
    m_cbCompleteTime = 0;
    m_pSystem       = pSystem;
    m_isSchedule    = true;
}

FishObject::~FishObject()
{
    SAFE_DELETE(m_pStatus);
    SAFE_DELETE(m_pFlipAction);
    SAFE_DELETE(m_pEye);
    SAFE_DELETE(m_pBody);
    SAFE_DELETE(m_pPattern);
    SAFE_DELETE(m_pDNA);
    for(int i=0; i<FIN_TYPE_NUM; ++i) SAFE_DELETE(m_pFin[i]);
    
    unschedule(schedule_selector(FishObject::testMovePattern));
    unschedule(schedule_selector(FishObject::_fishStatusUpdate));
}

void FishObject::_calcPhysicsVertex(POINT<float> *pPos, cocos2d::CCSize &size)
{
    pPos->x -= size.width/2.f;
    pPos->y -= size.height/2.f;
}

void FishObject::_rotatePhysicsVertex(std::vector< POINT<float> > &vertex, float degree)
{
    std::vector< POINT<float> >::iterator iter;
    for(iter = vertex.begin(); iter != vertex.end(); ++iter)
    {
        POINT<float> p;
        p.x = (*iter).x * cos(degree) - (*iter).y * sin(degree);
        p.y = (*iter).x * sin(degree) + (*iter).y * cos(degree);
        
        (*iter).x = p.x;
        (*iter).y = p.y;
    }
}

void FishObject::_calcFinVertex(std::vector< POINT<float> > &finVertex, cocos2d::CCSize &bodySize, POINT<float> bodyFinAveragePos )
{
    std::vector< POINT<float> >::iterator iter;
    for(iter = finVertex.begin(); iter != finVertex.end(); ++iter)
    {
        (*iter).x += (bodyFinAveragePos.x - (bodySize.width  / 2.f));
        (*iter).y += (bodyFinAveragePos.y - (bodySize.height / 2.f));
    }
}

void FishObject::_initFinPhysics(cocos2d::CCSize bodySize, float density, float friction, float *pGetFinAngleAry)
{
#define UP_FIN      0
#define DOWN_FIN    1
#define TAIL_FIN    2
#define FIN_NUM     3

    bool fins[3];
    vector< POINT<float> >  finVertex[FIN_NUM];
    finVertex[FIN_TYPE_UP]      = m_pDNA->GetFinsInfo()->GetUpFin().GetPhysicsVertex();
    finVertex[FIN_TYPE_DOWN]    = m_pDNA->GetFinsInfo()->GetDownFin().GetPhysicsVertex();
    finVertex[FIN_TYPE_TAIL]    = m_pDNA->GetFinsInfo()->GetTailFin().GetPhysicsVertex();
    
    for(int i=0; i<3; ++i) fins[i] = finVertex[i].size();
    
    float bodyAngle[FIN_NUM] = {0, };

    bodyAngle[UP_FIN]    = calcDegreeBetweenTwoPoint(m_pDNA->GetBodyInfo()->GetUpFinPos().GetLeftPos(), m_pDNA->GetBodyInfo()->GetUpFinPos().GetRightPos());
    bodyAngle[DOWN_FIN]  = calcDegreeBetweenTwoPoint(m_pDNA->GetBodyInfo()->GetDownFinPos().GetLeftPos(), m_pDNA->GetBodyInfo()->GetDownFinPos().GetRightPos());
    bodyAngle[TAIL_FIN]  = calcDegreeBetweenTwoPoint(m_pDNA->GetBodyInfo()->GetTailFinPos().GetLeftPos(), m_pDNA->GetBodyInfo()->GetTailFinPos().GetRightPos());

    float finAngle[FIN_NUM];

    finAngle[UP_FIN]    = calcDegreeBetweenTwoPoint(m_pDNA->GetFinsInfo()->GetUpFin().GetPosition().GetLeftPos(), m_pDNA->GetFinsInfo()->GetUpFin().GetPosition().GetRightPos());
    finAngle[DOWN_FIN]  = calcDegreeBetweenTwoPoint(m_pDNA->GetFinsInfo()->GetDownFin().GetPosition().GetLeftPos(), m_pDNA->GetFinsInfo()->GetDownFin().GetPosition().GetRightPos());
    finAngle[TAIL_FIN]  = calcDegreeBetweenTwoPoint(m_pDNA->GetFinsInfo()->GetTailFin().GetPosition().GetLeftPos(), m_pDNA->GetFinsInfo()->GetTailFin().GetPosition().GetRightPos());

    float applyAngle[FIN_NUM]  = {0, };
    applyAngle[UP_FIN]      = bodyAngle[UP_FIN]     - finAngle[UP_FIN];
    applyAngle[DOWN_FIN]    = bodyAngle[DOWN_FIN]   - finAngle[DOWN_FIN];
    applyAngle[TAIL_FIN]    = bodyAngle[TAIL_FIN]   - finAngle[TAIL_FIN];

    _rotatePhysicsVertex(finVertex[UP_FIN] ,applyAngle[UP_FIN]);
    _rotatePhysicsVertex(finVertex[DOWN_FIN] ,applyAngle[DOWN_FIN]);
    _rotatePhysicsVertex(finVertex[TAIL_FIN] ,applyAngle[TAIL_FIN]);
    
    _calcFinVertex(finVertex[UP_FIN], bodySize,     m_pDNA->GetBodyInfo()->GetUpFinPos().GetAveragePos());
    _calcFinVertex(finVertex[DOWN_FIN], bodySize,   m_pDNA->GetBodyInfo()->GetDownFinPos().GetAveragePos());
    _calcFinVertex(finVertex[TAIL_FIN], bodySize,   m_pDNA->GetBodyInfo()->GetTailFinPos().GetAveragePos());
    
    for(int i=0; i<FIN_NUM; ++i)
    {
        if(fins[i] == false) continue;
        
        b2Vec2 *pVecAry = _createVertexAry(finVertex[i]);
        b2PolygonShape polygon;
        polygon.Set(pVecAry, finVertex[i].size());
        addShape(&polygon, 0, friction);
        
        delete[] pVecAry;
    }
    
    if(pGetFinAngleAry == NULL) return;
    
    pGetFinAngleAry[UP_FIN]     = applyAngle[UP_FIN];
    pGetFinAngleAry[DOWN_FIN]   = applyAngle[DOWN_FIN];
    pGetFinAngleAry[TAIL_FIN]   = applyAngle[TAIL_FIN];
}

void FishObject::_loadPart(const char *name, FISHPART_TYPE type, float delay, FishPart *pPart)
{
    std::string path = "Image/Fish/";
    
    switch (type)
    {
        case FISHPART_TYPE_BODY:    path += "Body/";     break;
        case FISHPART_TYPE_EYE:     path += "Eye/";      break;
        case FISHPART_TYPE_FIN:     path += "Fins/";      break;
        default: break;
    }
    
    path += name;
    path += ".png";

    CCTexture2D *pTex = CCTextureCache::sharedTextureCache()->addImage(path.data());
    pPart->init(pTex, delay, type);
}

void FishObject::_initSprite()
{
#define Z_ORDER_BODY    0
#define Z_ORDER_EYE     1
#define Z_ORDER_MOUTH   1
#define Z_ORDER_FIN     -1
    
    m_pEye = new FishPart;
    _loadPart(m_pDNA->GetEyeInfo()->GetName(), FISHPART_TYPE_EYE, 1.f, m_pEye);
    m_pEye->setAnchorPoint(ccp(0.5, 0.5));
    m_pEye->setColor(ccc3(m_pDNA->GetEyeInfo()->m_color.r, m_pDNA->GetEyeInfo()->m_color.g, m_pDNA->GetEyeInfo()->m_color.b));
    
    m_pBody = new FishPart;
    _loadPart(m_pDNA->GetBodyInfo()->GetName(), FISHPART_TYPE_BODY, 1.f, m_pBody);
    m_pBody->setAnchorPoint(ccp(0.5f, 0.5f));
    m_pBody->setColor(ccc3(m_pDNA->GetBodyInfo()->m_color.r, m_pDNA->GetBodyInfo()->m_color.g, m_pDNA->GetBodyInfo()->m_color.b));
    
    m_pBody->setPosition( ccp(0, 0) );
    m_pEye->setPosition(ccp(m_pDNA->GetBodyInfo()->GetEyePos().x, m_pBody->getContentSize().height - m_pDNA->GetBodyInfo()->GetEyePos().y));
    
    for(int i=0; i<FIN_TYPE_NUM; ++i)
    {
        CCPoint pos;
        std::string name;
        if(i == FIN_TYPE_UP)
        {
            if(m_pDNA->GetBodyInfo()->GetUpFinPos().GetAveragePos().x == 0)
                continue;
            
            name    = "Up/";
            pos     = ccp(m_pDNA->GetBodyInfo()->GetUpFinPos().GetAveragePos().x, m_pDNA->GetBodyInfo()->GetUpFinPos().GetAveragePos().y + 42);
        }
        else if( i == FIN_TYPE_DOWN )
        {
            if(m_pDNA->GetBodyInfo()->GetDownFinPos().GetAveragePos().x == 0)
                continue;

            name    = "Down/";
            pos     = ccp(m_pDNA->GetBodyInfo()->GetDownFinPos().GetAveragePos().x, m_pDNA->GetBodyInfo()->GetDownFinPos().GetAveragePos().y - 40);
        }
        else if( i == FIN_TYPE_SIDE )
        {
            if(m_pDNA->GetBodyInfo()->GetSideFinPos().GetAveragePos().x == 0)
                continue;

            name    = "Side/";
            pos     = ccp(m_pDNA->GetBodyInfo()->GetSideFinPos().GetAveragePos().x, m_pDNA->GetBodyInfo()->GetSideFinPos().GetAveragePos().y);
        }
        else if( i == FIN_TYPE_TAIL )
        {
            if(m_pDNA->GetBodyInfo()->GetTailFinPos().GetAveragePos().x == 0)
                continue;

            name    = "Tail/";
            pos     = ccp(m_pDNA->GetBodyInfo()->GetTailFinPos().GetAveragePos().x, m_pBody->getContentSize().height
                                                                                        - m_pDNA->GetBodyInfo()->GetTailFinPos().GetAveragePos().y);
        }

        name += m_pDNA->GetFinsInfo()->GetName();
        
        m_pFin[i] = new FishPart;
        _loadPart(name.data(), FISHPART_TYPE_FIN, 1.f, m_pFin[i]);
        if(FIN_TYPE_SIDE != i)
            m_pBody->addChild(m_pFin[i], Z_ORDER_FIN);
        else m_pBody->addChild(m_pFin[i], 1);
        m_pFin[i]->setAnchorPoint(ccp(0.5, 0.5));
        m_pFin[i]->setPosition(pos);
        m_pFin[i]->setColor(ccc3(m_pDNA->GetFinsInfo()->m_color.r, m_pDNA->GetFinsInfo()->m_color.g, m_pDNA->GetFinsInfo()->m_color.b));
    }
    
    m_pBody->addChild(m_pEye, Z_ORDER_EYE);
    
//    m_pFin[FIN_TYPE_TAIL]->setVisible(false);
}

bool FishObject::init(b2World *pWorld, cocos2d::CCPoint position)
{
    _initSprite();
    
    if( PhysicsObject::init( m_pBody, m_pDNA->GetBodyInfo()->GetPhysicsVertex(), pWorld, b2_dynamicBody, position, FISH_GRAVITYSCALE, BADY_DENSITY, BADY_FRICTION) == false )
        return false;

    float finAngle[3];

    _initFinPhysics(m_pBody->getContentSize(), FIN_DENSITY, FIN_FRICTION, finAngle);

    if(m_pFin[FIN_TYPE_UP])
    m_pFin[FIN_TYPE_UP]->setRotation(finAngle[0]);

    if(m_pFin[FIN_TYPE_DOWN])
    m_pFin[FIN_TYPE_DOWN]->setRotation(finAngle[1]);
    
    if(m_pFin[FIN_TYPE_TAIL])
    m_pFin[FIN_TYPE_TAIL]->setRotation(finAngle[2]);
    
    b2Fixture *pFixture = PhysicsObject::m_pBody->GetFixtureList();
    for(int i = 0; pFixture; pFixture = pFixture->GetNext(), ++i)
    {
        b2PolygonShape *pPolygonShape = dynamic_cast<b2PolygonShape*>(pFixture->GetShape());
        
        int vertexCount = pPolygonShape->GetVertexCount();
        
        for(int j=0; j<vertexCount; ++j)
            m_vOriginvertex[i].push_back(pPolygonShape->m_vertices[j]);
    }
    
//    m_pFilpX->initWithSize(ccg(m_pBody->getContentSize().width, m_pBody->getContentSize().height), 0.5);
    schedule(schedule_selector(FishObject::testMovePattern), 1.f);
    schedule(schedule_selector(FishObject::_fishStatusUpdate), 2.f);
    m_isSchedule = true;
    
    if(m_pStatus->GetTime() == 0)
        _growCompleteEffect();
    
    return true;
}

void FishObject::_fishStatusUpdate()
{
    if(m_pStatus->m_hungry >= 0) m_pStatus->m_hungry--;
    if(m_pStatus->m_clean >= 0) m_pStatus->m_clean--;
}

void FishObject::update(float dt)
{
    float   angle = RADIAN_TO_DEGREE(PhysicsObject::m_pBody->GetTransform().q.GetAngle());
    
    if(angle >= 30)         angle = 30.f;
    else if(angle <= -30)   angle = -30.f;
    
    if(m_isGrowEnd == false) m_pStatus->m_time += dt;
    
    float growRatio = m_pStatus->m_time / m_pDNA->GetGrowCompTime() + 0.5;
    float rate = growRatio >= 1.f ? 1.f : 0.3f;

    //이 값은, 아마 0~1 사이 일거야 기본 오프셋은 30%로 두자
    if(growRatio>=1.0f && m_isGrowEnd == false)
    {
        growRatio = 1.f;
        m_isGrowEnd = true;
        _growCompleteEffect();
    }

    b2Fixture *pFixture = PhysicsObject::m_pBody->GetFixtureList();
    for(int i = 0; pFixture; pFixture = pFixture->GetNext(), ++i)
    {
        b2PolygonShape *pPolygonShape = dynamic_cast<b2PolygonShape*>(pFixture->GetShape());

        int vertexCount = pPolygonShape->GetVertexCount();

        for(int j=0; j<vertexCount; ++j)
        {
            pPolygonShape->m_vertices[j].x = (((m_vOriginvertex[i][j].x * PTM_RATIO) * rate) / PTM_RATIO);
            pPolygonShape->m_vertices[j].y = (((m_vOriginvertex[i][j].y * PTM_RATIO) * rate) / PTM_RATIO);
        }
    }
    
    m_pSprite->setScale(rate);
    SetAngle(DEGREE_TO_RADIAN(angle));
    
    //교배 관한걸 켜야할거 같은데?
    //그 다음에 OtherFish 끄고 Joint해제해

    if( m_pOtherFish == NULL ) return;
    if( (m_cbNowTime += dt) >= m_cbCompleteTime )
    {
        m_pSystem->FishMix(this, m_pOtherFish);
        crossbreedOff();
    }
}

void FishObject::crossbreedOff()
{
    if(m_pJoint == false) return;

    PhysicsObject::m_pBody->GetWorld()->DestroyJoint(m_pJoint);
    m_pOtherFish->MoveOn();
    m_pOtherFish = NULL;
    m_cbCompleteTime = 0;
    m_cbNowTime = 0;
    m_pJoint = NULL;
    m_pStatus->m_life--;
}

bool FishObject::isGrowEnd()
{
    return m_isGrowEnd;
}

void FishObject::_flipBodySprite()
{
    if(m_pBody->isRunning())
        m_pBody->stopAllActions();
    
    SAFE_DELETE(m_pFlipAction);
    m_pFlipAction = new cocos2d::CCOrbitCamera;
    
    float startAngle = 0;
    float delatAngle = 180.f;
    
    if( !m_isLeft )
    {
        startAngle = 180;
        delatAngle = -180;
    }
    
    m_pFlipAction->initWithDuration(0.5f, 1, 1,
                                    startAngle,
                                    delatAngle, 0, 0);
    m_pBody->runAction(m_pFlipAction);
    m_isLeft = !m_isLeft;
}

void FishObject::flipFish()
{
    _flipXVertex();
    _flipBodySprite();

    if(m_pOtherFish)
    {
        if(m_pOtherFish->m_isLeft != m_isLeft)
            m_pOtherFish->flipFish();
    }
}

void FishObject::testMovePattern(float t)
{
    if(rand()%2)    flipFish();
    
    int force = rand()%50+30;
    float degree = rand()%60 - 30;

    float x =force*(cos(DEGREE_TO_RADIAN(degree))-sin(DEGREE_TO_RADIAN(degree)));
    float y =force*(cos(DEGREE_TO_RADIAN(degree))+sin(DEGREE_TO_RADIAN(degree)));
    
    if(degree <= 0) y = -y;
    if(!m_isLeft)
    {
        x = -x;
        y = -y;
    }

    PhysicsObject::m_pBody->SetType(b2_staticBody);
    PhysicsObject::m_pBody->SetType(b2_dynamicBody);
    PhysicsObject::m_pBody->ApplyForce(b2Vec2(-x, -y), PhysicsObject::m_pBody->GetPosition());
    SetAngle(DEGREE_TO_RADIAN(degree));
    
    if(m_pOtherFish)
        m_pOtherFish->SetAngle(DEGREE_TO_RADIAN(degree));
}

void FishObject::_flipXVertex()
{
    b2Fixture *pFixture = PhysicsObject::m_pBody->GetFixtureList();
    for(int i = 0; pFixture; pFixture = pFixture->GetNext(), ++i)
    {
        b2PolygonShape *pPolygonShape = dynamic_cast<b2PolygonShape*>(pFixture->GetShape());
        
        int vertexCount = pPolygonShape->GetVertexCount();
        
        for(int j=0; j<vertexCount; ++j)
        {
            pPolygonShape->m_vertices[j].x = -pPolygonShape->m_vertices[j].x;
            pPolygonShape->m_vertices[j].y = -pPolygonShape->m_vertices[j].y;
        }
    }
}

void FishObject::MoveOn()
{
    schedule(schedule_selector(FishObject::testMovePattern), 1.f);
    m_isSchedule = true;
}

void FishObject::MoveOff()
{
    unschedule(schedule_selector(FishObject::testMovePattern));
    m_isSchedule = false;
}

bool FishObject::Crossbreed(FishObject *pOtherFish, b2Joint *pJoint, float CBTime, float CBComTime)
{
    if(m_isGrowEnd == false) return false;
    
    m_pOtherFish = pOtherFish;
//    pOtherFish->m_pOtherFish = this;
    m_pJoint = pJoint;
    m_pOtherFish->MoveOff();
    m_cbCompleteTime = CBComTime;
    m_cbNowTime = CBTime;
    
    return true;
}

void FishObject::eat(FOOD_TYPE t)
{
    if( t == FOOD_TYPE_NORMAL ) m_pStatus->m_hungry += 30;
    else                        m_pStatus->m_hungry += 70;
}

bool FishObject::isCrossbreed()
{
    return (m_pOtherFish || !m_isSchedule);
}

bool FishObject::isJointOn()
{
    return PhysicsObject::m_pBody->GetJointList();
}

void FishObject::_growCompleteEffect()
{
    if( getChildByTag(10) )
        removeChildByTag(10, true);
    
    m_pFlower = CCParticleFlower::create();
    m_pFlower->setPosition(ccp(GetBody()->GetPosition().x * PTM_RATIO, GetBody()->GetPosition().y * PTM_RATIO));
    m_pFlower->setAnchorPoint(ccp(0.5, 0.5));
    
    m_pFlower->setScale(0.4f);
    m_pFlower->setLifeVar(0);
    m_pFlower->setLife(5);      
    m_pFlower->setSpeed(100);
    m_pFlower->setSpeedVar(10);
    m_pFlower->setEmissionRate(250);

    addChild(m_pFlower, 5, 10);
    m_pFlower->setTexture( CCTextureCache::sharedTextureCache()->addImage("Image/Bubble.png"));
    
    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(FishObject::_particleEnd));
    CCDelayTime *delay = CCDelayTime::create(0.1f);
    CCSequence *sequence = CCSequence::create(delay, call);
    runAction(sequence);
}

void FishObject::_particleEnd()
{
    m_pFlower->stopSystem();
}

void FishObject::GetName(char *pTxt)
{
    sprintf(pTxt, "%s/%d", m_pDNA->GetTag().GetPlayer(), m_id);
}