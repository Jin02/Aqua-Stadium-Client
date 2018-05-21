//
//  Player.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

#include "User.h"
#include "Utility.h"
#include "Network.h"

#define PLAYER_FILE_NAME "Player.info"

class Player : public User
{
private:
    std::string     m_strFilePath;
    
private:
    int             m_level;
    int             m_money;
    int             m_cash;
    int             m_exp;
    
public:
    Player();
    ~Player();
    
public:
    void Init();
    
    bool AddMoney(int n);
    void AddCash(int n);
    void AddExp(int n);
    
public:
    inline int GetLevel()       { return m_level;           }
    inline int GetMoney()       { return m_money;           }
    inline int GetCash()        { return m_cash;            }
    inline int GetExp()         { return m_exp;             }
    inline int GetMaxinumExp()  { return m_exp * m_level;   }
    
public:
    static bool hasFile();
    static void newPlayer(const char *PlayerToken, char *PlayerDate);
    static void GetInfo(char *pOutToken, char *pOutDate);
};