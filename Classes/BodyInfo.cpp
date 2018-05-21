//
//  BodyInfo.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 10. 16..
//
//

#include "BodyInfo.h"

BodyInfo::BodyInfo() : FishPartInfo()
{
}

BodyInfo::    BodyInfo(int id, const char *pName,
                       std::vector< POINT<float> > &vPhysicsVertex,
                       FishPartPosition &sideFinPos,
                       FishPartPosition &upFinPos,
                       FishPartPosition &downFinPos,
                       FishPartPosition &tailFinPos,
                       POINT<float> &eyePos,
                       POINT<float> &mouthPos)
: FishPartInfo(FISHPART_TYPE_BODY, id, pName, vPhysicsVertex)
{
    m_bodyPartPos[BODY_PART_TYPE_DOWN_FIN]  = downFinPos;
    m_bodyPartPos[BODY_PART_TYPE_TAIL_FIN]  = tailFinPos;
    m_bodyPartPos[BODY_PART_TYPE_UP_FIN]    = upFinPos;
    m_bodyPartPos[BODY_PART_TYPE_SIDE_FIN]  = sideFinPos;

    m_bodyPartPos[BODY_PART_TYPE_EYE]       = eyePos;
    m_bodyPartPos[BODY_PART_TYPE_MOUTH]     = mouthPos;
}

BodyInfo::~BodyInfo()
{
    
}