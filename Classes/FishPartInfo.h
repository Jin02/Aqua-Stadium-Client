//
//  FishPart.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 10. 11..
//
//

#pragma once

#include <string>
#include "Utility.h"
#include "CommonInfo.h"

enum FISHPART_TYPE
{
    FISHPART_TYPE_NONE,
    FISHPART_TYPE_EYE,
    FISHPART_TYPE_BODY,
    FISHPART_TYPE_FIN,
    FISHPART_TYPE_MAXNUM = 3
};

struct CommonFishPartInfo
{
    const char      *name;
    COLOR_ARGB      color;
    
    CommonFishPartInfo() :color(255,255,255,255) {}
    CommonFishPartInfo(const char *name, COLOR_ARGB color)
    {
        this->name  = name;
        this->color = color;
    }
};

class FishPartInfo : public CommonInfo
{
protected:
    FISHPART_TYPE   m_type;
    
public:
    COLOR_ARGB  m_color;
    
public:
    FishPartInfo();
    FishPartInfo(FISHPART_TYPE type, int id, const char *pName, std::vector< POINT<float> > &vPhysicsVertex);
    virtual ~FishPartInfo();
    
    inline FISHPART_TYPE GetType()      { return m_type;        }
    
    FishPartInfo Mix(FishPartInfo *pOther);
};

typedef FishPartInfo    EyeInfo;
