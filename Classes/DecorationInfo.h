//
//  DecorationInfo.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

#include <string>
#include "CommonInfo.h"

enum DECORATION_TYPE
{
    DECORATION_TYPE_NONE,
    DECORATION_TYPE_CORALREEF,
    DECORATION_TYPE_STON,
    DECORATION_TYPE_SEAWEED,
    DECORATION_TYPE_SHIP,
    DECORATION_TYPE_GRAVEL,
    DECORATION_TYPE_CLAM,
    DECORATION_TYPE_MAXNUM = 6
};

struct CommonDecoInfo
{
    std::string name;
    int id;
    
    CommonDecoInfo() : id(-1) {}
    CommonDecoInfo(const char *name, int id) { this->name = name, this->id = id; }
};

class DecorationInfo : public CommonInfo
{
protected:
    float               m_effectRate;
    DECORATION_TYPE     m_type;
    
public:
    DecorationInfo();
    DecorationInfo(int id, DECORATION_TYPE type, float rate, const char *pName, std::vector< POINT<float> > &vPhysicsVertex);
    ~DecorationInfo();
    
public:
    inline float            GetEffectRate()     { return m_effectRate;    }
    inline DECORATION_TYPE  GetType()           { return m_type;    }
};

typedef DecorationInfo CoralReefInfo;
typedef DecorationInfo StonInfo;
typedef DecorationInfo ShipInfo;
typedef DecorationInfo SeaweedInfo;
typedef DecorationInfo GravelInfo;
typedef DecorationInfo ClamInfo;
