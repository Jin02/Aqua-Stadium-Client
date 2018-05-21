//
//  Sqlite3Base.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

#include "sqlite/sqlite3.h"

class Sqlite3Base
{
protected:
    sqlite3             *m_pDataBase;
    sqlite3_stmt        *m_pStatement;
    
public:
    Sqlite3Base();
    virtual ~Sqlite3Base();
    
public:
    bool ErrorCheck(const char *table, char *whereType, char *whereBind);
    bool ErrorCheck(const char *cmd);
    
    bool isNextStep();
    void Finalize();
    void Init(const char *DBFileName);
    
public:
    int             GetInt(int iCol);
    const char*     GetTxt(int iCol);
    double          GetDouble(int iCol);
};
