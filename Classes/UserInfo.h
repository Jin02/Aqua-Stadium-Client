//
//  UserInfo.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

#include <string>

struct UserInfo
{
public:
    std::string     userToken;
    std::string     userDate;
    std::string     userName;
    
public:
    UserInfo(){}
    UserInfo(const char* userToken, const char *userDate, const char *userName)
    {
        this->userToken     = userToken;
        this->userDate      = userDate;
        this->userName      = userName;
    }
    
    ~UserInfo(){}
    
public:
    const char* GetToken() { return userToken.data(); }
    const char* GetDate() { return userDate.data(); }
    const char* GetName() { return userName.data(); }
};
