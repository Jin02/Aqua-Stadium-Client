//
//  DNA.cpp
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#include "DNA.h"

DNA::DNA()
{
    m_pBodyInfo     = NULL;
    m_pFinsInfo     = NULL;
    m_pEyeInfo      = NULL;
    m_growCompTime  = NULL;
}

DNA::DNA(Tag &tag, BodyInfo *pBodyInfo, FinsInfo *pFinsInfo, EyeInfo *pEyeInfo, double growCompTime)
{
    m_pBodyInfo     = new BodyInfo(*pBodyInfo);
    m_pFinsInfo     = new FinsInfo(*pFinsInfo);
    m_pEyeInfo      = new EyeInfo(*pEyeInfo);
    
    m_growCompTime  = growCompTime;
    
    m_tag = tag;
}

DNA::DNA(const DNA &dna)
{
    m_pBodyInfo     = new BodyInfo(*dna.m_pBodyInfo);
    m_pFinsInfo     = new FinsInfo(*dna.m_pFinsInfo);
    m_pEyeInfo      = new EyeInfo(*dna.m_pEyeInfo);
    
    m_growCompTime  = dna.m_growCompTime;
}



COLOR_ARGB DNA::GetBodyColor()
{
    return m_pBodyInfo->m_color;
}

COLOR_ARGB DNA::GetFinsColor()
{
    return m_pFinsInfo->m_color;
}

COLOR_ARGB DNA::GetEyeColor()
{
    return m_pEyeInfo->m_color;
}

DNA::~DNA()
{
    SAFE_DELETE(m_pBodyInfo);
    SAFE_DELETE(m_pFinsInfo);
    SAFE_DELETE(m_pEyeInfo);
}
