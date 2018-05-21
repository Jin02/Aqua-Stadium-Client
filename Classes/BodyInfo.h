//
//  BodyInfo.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 10. 16..
//
//

#pragma once

#include "FishPartInfo.h"
#include "Utility.h"
#include "FishPartPosition.h"

enum BODY_PART_TYPE_
{
    BODY_PART_TYPE_UP_FIN,
    BODY_PART_TYPE_DOWN_FIN,
    BODY_PART_TYPE_SIDE_FIN,
    BODY_PART_TYPE_TAIL_FIN,
    BODY_PART_TYPE_EYE,
    BODY_PART_TYPE_MOUTH,
    BODY_PART_TYPE_NUM,
    BODY_PART_TYPE_PHYSICS_NUM = 3
};

class BodyInfo : public FishPartInfo
{
private:
    FishPartPosition              m_bodyPartPos[BODY_PART_TYPE_NUM];
    
public:
    BodyInfo();
    BodyInfo(int id, const char *pName,
             std::vector< POINT<float> > &vPhysicsVertex,
             FishPartPosition &sideFinPos,
             FishPartPosition &upFinPos,
             FishPartPosition &downFinPos,
             FishPartPosition &tailFinPos,
             POINT<float> &eyePos,
             POINT<float> &mouthPos);
    virtual ~BodyInfo();
    
public:
    inline FishPartPosition GetSideFinPos() { return m_bodyPartPos[BODY_PART_TYPE_SIDE_FIN];  }
    inline FishPartPosition GetUpFinPos()   { return m_bodyPartPos[BODY_PART_TYPE_UP_FIN];    }
    inline FishPartPosition GetDownFinPos() { return m_bodyPartPos[BODY_PART_TYPE_DOWN_FIN];  }
    inline FishPartPosition GetTailFinPos() { return m_bodyPartPos[BODY_PART_TYPE_TAIL_FIN];  }
    inline POINT<float> GetEyePos() { return m_bodyPartPos[BODY_PART_TYPE_EYE].GetLeftPos();      }
    inline POINT<float> GetMouthPos() { return m_bodyPartPos[BODY_PART_TYPE_MOUTH].GetLeftPos();    }
};