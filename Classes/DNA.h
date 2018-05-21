//
//  DNA.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

#include "Utility.h"
#include "BodyInfo.h"
#include "FinsInfo.h"
#include "Tag.h"

class DNA
{
private:
    Tag             m_tag;
    
private:
    BodyInfo        *m_pBodyInfo;
    FinsInfo        *m_pFinsInfo;
    EyeInfo         *m_pEyeInfo;
    
    double    m_growCompTime;
    
public:
    DNA();
    DNA(Tag &tag, BodyInfo *pBodyInfo, FinsInfo *pFinsInfo, EyeInfo *pEyeInfo, double growCompTime);
    DNA(const DNA &dna);
    ~DNA();
    
public:
    inline BodyInfo    *GetBodyInfo()        { return m_pBodyInfo;    }
    inline FinsInfo    *GetFinsInfo()        { return m_pFinsInfo;    }
    inline EyeInfo     *GetEyeInfo()         { return m_pEyeInfo;     }
    inline double      GetGrowCompTime()     { return m_growCompTime; }
    inline Tag         GetTag()              { return m_tag;          }
    
public:
    COLOR_ARGB  GetBodyColor();
    COLOR_ARGB  GetFinsColor();
    COLOR_ARGB  GetEyeColor();
};
