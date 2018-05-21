//
//  User.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

#include "UserInfo.h"
//서버 나오면 그때가서 마저 추가

class User
{
protected:
    UserInfo       *m_pUserInfo;
    
public:
    User();
    User(UserInfo &user);
    ~User();
    
protected:
    void setUserInfo(UserInfo user);
    
public:
    inline UserInfo * GetUserInfo() { return m_pUserInfo; }    
};