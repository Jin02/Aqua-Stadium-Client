//
//  ObjIdxMgr.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 6..
//
//

#include "ObjIdxMgr.h"

using namespace std;

ObjIdxMgr::ObjIdxMgr()
{
    m_pTable    = new bool[3000];
    
    memset(m_pTable, 0, sizeof(bool)*3000);
}

ObjIdxMgr::~ObjIdxMgr()
{
    delete[] m_pTable;
    m_pTable = NULL;
}

int ObjIdxMgr::_indexGenerate(bool *pTable, int start, int max)
{
    for(int idx = start; idx < max; ++idx)
    {
        if(pTable[idx] == false)
            return idx;
    }
    
    return -1;
}

bool ObjIdxMgr::_addIndex(bool *pTable, int index)
{
    if( pTable[index] == false )
        pTable[index] = true;
    else return false;
    return true;
}

int ObjIdxMgr::FishIndex()
{
    return _indexGenerate(m_pTable);
}

int ObjIdxMgr::DecoIndex()
{
    return _indexGenerate(m_pTable, 1000, 2000);
}

bool ObjIdxMgr::addDecoIndex(int idx)
{
    if(idx >= 1000) return false;
    return _addIndex(m_pTable, idx);
}

bool ObjIdxMgr::addFishIndex(int idx)
{
    if( idx < 1000 ) return false;
    return _addIndex(m_pTable, idx);
}

bool ObjIdxMgr::removeDecoIndex(int idx)
{
    if( idx >= 1000) return false;
    m_pTable[idx] = false;
    return true;
}

bool ObjIdxMgr::removeFishIndex(int idx)
{
    if( idx < 1000) return false;
    m_pTable[idx] = false;
    return true;
}

std::vector<int> ObjIdxMgr::emptyFishElement()
{
    vector<int> v;
    
    for(int i=0; i<1000; ++i)
    {
        if(m_pTable[i] == false)
            v.push_back(i);
    }
    
    return v;
}

std::vector<int> ObjIdxMgr::emptyDecoElement()
{
    vector<int> v;
    
    for(int i=1000; i<2000; ++i)
    {
        if(m_pTable[i] == false)
            v.push_back(i);
    }
    
    return v;
}

int ObjIdxMgr::EggIndex()
{
    return _indexGenerate(m_pTable, 2000, 3000);
}

bool ObjIdxMgr::addEggIndex(int idx)
{
    if( idx < 2000 ) return false;
    return _addIndex(m_pTable, idx);
}

bool ObjIdxMgr::removeEggIndex(int idx)
{
    if( idx < 2000 ) return false;
    m_pTable[idx] = false;
    return true;
}

std::vector<int> ObjIdxMgr::emptyEggElement()
{
    vector<int> v;
    
    for(int i=2000; i<3000; ++i)
    {
        if(m_pTable[i] == false)
            v.push_back(i);
    }
    
    return v;
}