//
//  Player.cpp
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#include "Player.h"
#include "cocos2d.h"

using namespace cocos2d;

Player::Player()
{
}

void Player::Init()
{
    m_strFilePath = CCFileUtils::sharedFileUtils()->getWritablePath().append(PLAYER_FILE_NAME);
    
    FILE *pFile = fopen(m_strFilePath.data(), "rb");
    
    m_pUserInfo         = new UserInfo;
    
    char token[32], date[30];
    
    if(pFile != NULL)
    {
        fscanf(pFile, "%s", token);
        fscanf(pFile, "%s", date);
        
        m_pUserInfo->userToken = token;
        m_pUserInfo->userDate = date;

        fclose(pFile);
    }
    else{
        m_pUserInfo->userToken = "default";
        m_pUserInfo->userDate = "";
    }
    
    m_level = 0;
    m_money = 0;
    m_cash = 0;
    m_exp = 0;    
}

Player::~Player()
{
    FILE *pFile = fopen(m_strFilePath.data(), "wb");
    
    fprintf(pFile, "%s\n",m_pUserInfo->userToken.data());
    fprintf(pFile, "%s\n",m_pUserInfo->userDate.data());
    
    fclose(pFile);
}

bool Player::AddMoney(int n)
{
    m_money += n;
    return true;
}

void Player::AddCash(int n)
{
    m_cash += n;
}

void Player::AddExp(int n)
{
    m_exp+=n;
    if( m_exp >= GetMaxinumExp() )
    {
        m_level++;
        m_exp = 0;
    }
}

bool Player::hasFile()
{
    return isExistFile(CCFileUtils::sharedFileUtils()->getWritablePath().append(PLAYER_FILE_NAME).data());
}

void Player::newPlayer(const char *PlayerToken, char *PlayerDate)
{
    std::string path = CCFileUtils::sharedFileUtils()->getWritablePath().append(PLAYER_FILE_NAME);
    FILE *pFile = fopen(path.data(), "wb");
    
    fprintf(pFile, "%s\n",PlayerToken);
    fprintf(pFile, "%s", PlayerDate);
    
    fclose(pFile);
}

void Player::GetInfo(char *pOutToken, char *pOutDate)
{
    std::string path = CCFileUtils::sharedFileUtils()->getWritablePath().append(PLAYER_FILE_NAME);
    FILE *pFile = fopen(path.data(), "rb");
    
    if(pOutToken)   fscanf(pFile, "%s", pOutToken);
    if(pOutDate)    fscanf(pFile, "%s", pOutDate);
    
    fclose(pFile);
}
