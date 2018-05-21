//
//  Tag.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 6..
//
//

#pragma once

#include <string>

class Tag
{
private:
    //일단 cocos는 제외
    //세부 구현
    const char *m_userName;
    const char *m_content;
    
public:
    Tag();
    Tag(const char *userName, const char *content);
    ~Tag();
    
public:
    inline const char* GetContent()     { return m_content;  }
    inline const char* GetPlayer()      { return m_userName;  }
};