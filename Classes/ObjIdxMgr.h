//
//  ObjIdxMgr.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 6..
//
//

#pragma once


#include <vector>

class ObjIdxMgr
{
private:
    bool         *m_pTable;
    
public:
    ObjIdxMgr();
    ~ObjIdxMgr();
    
private:
    int _indexGenerate(bool *pTable,int start = 0, int max = 3000);
    bool _addIndex(bool *pTable, int index);
    
public:
    int FishIndex();
    int DecoIndex();
    int EggIndex();
    
public:
    bool addFishIndex(int idx);
    bool addDecoIndex(int idx);
    bool addEggIndex(int idx);

public:
    bool removeFishIndex(int idx);
    bool removeDecoIndex(int idx);
    bool removeEggIndex(int idx);
    
public:
    std::vector<int> emptyFishElement();
    std::vector<int> emptyDecoElement();
    std::vector<int> emptyEggElement();
};