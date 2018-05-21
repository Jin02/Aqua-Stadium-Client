//
//  User.cpp
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#include "User.h"

User::User()
{
    m_pUserInfo = new UserInfo;
}

User::User(UserInfo &user)
{
    m_pUserInfo = new UserInfo(user);
}

User::~User()
{
    delete m_pUserInfo;
}

void User::setUserInfo(UserInfo user)
{
    *m_pUserInfo = user;
}
