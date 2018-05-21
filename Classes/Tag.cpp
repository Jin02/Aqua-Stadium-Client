//
//  Tag.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 6..
//
//

#include "Tag.h"

Tag::Tag()
{
    m_userName  = "NONE";
    m_content   = "EMPTY";
}

Tag::Tag(const char *userName, const char *content)
{
    m_userName  = userName;
    m_content   = content;
}

Tag::~Tag()
{
    
}