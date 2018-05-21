//
//  InfoMgr.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

#include <vector>
#include <map>
#include "Sqlite3Base.h"
#include "FishPartInfo.h"
#include "DecorationInfo.h"
#include "BodyInfo.h"
#include "FinsInfo.h"

template<typename TYPE>
struct INFORMATION
{
    std::vector<TYPE>               infoVector;
    
    void add(TYPE t)
    {
        infoVector.push_back(t);
    }
    
    TYPE find(const char *name)
    {
        typename std::vector<TYPE>::iterator iter;
        for(iter = infoVector.begin(); iter != infoVector.end(); ++iter)
            if( strcmp((*iter)->GetName(), name) == 0)
                return (*iter);
        
        return NULL;
    }
    
    TYPE find(int id)
    {
        typename std::vector<TYPE>::iterator iter;
        for(iter = infoVector.begin(); iter != infoVector.end(); ++iter)
            if( (*iter)->GetID() == id)
                return (*iter);
        
        return NULL;        
    }
};

class InfoMgr
{
private:
    INFORMATION<FinsInfo*>      m_finsInfo;
    INFORMATION<EyeInfo*>       m_eyeInfo;
    INFORMATION<BodyInfo*>      m_bodyInfo;
    
    INFORMATION<CoralReefInfo*> m_coralReefInfo;
    INFORMATION<StonInfo*>      m_stonInfo;
    INFORMATION<SeaweedInfo*>   m_seaweedInfo;
    INFORMATION<ShipInfo*>      m_shipInfo;
    INFORMATION<GravelInfo*>    m_gravelInfo;
    INFORMATION<ClamInfo*>      m_clamInfo;
    
    Sqlite3Base* _db;
    
public:
    InfoMgr();
    ~InfoMgr();
    
public:
    bool        loadData(const char *DBFileName);
    
private:
    int         _getTime(int timeValue);

private:
    std::vector< POINT<float> > _loadPhysicsFile(const char *pXMLFile);
    FinsInfo*         _loadFinsInfo(Sqlite3Base *pDBBase, int id, const char *pName);
    BodyInfo*        _loadBodyInfo(Sqlite3Base *pDBBase, std::vector< POINT<float> > &vPhysics, int &id, const char *pName);
    
private:
    bool        _loadFishPart(Sqlite3Base *pDBBase, FISHPART_TYPE type);
    bool        _loadDecoration(Sqlite3Base *pDBBase, DECORATION_TYPE type);
    
public:
    bool        searchInfo(int id, FISHPART_TYPE type, FishPartInfo **ppInfo);
    bool        searchInfo(const char *name, FISHPART_TYPE type, FishPartInfo **ppInfo);
    bool        searchInfo(int id, DECORATION_TYPE type, DecorationInfo **ppInfo);
    bool        searchInfo(const char *name, DECORATION_TYPE type, DecorationInfo **ppInfo);

public:
    std::vector<BodyInfo*>      GetAllBodyInfo();
    std::vector<EyeInfo*>       GetAllEyeInfo();
    std::vector<FinsInfo*>      GetAllFinsInfo();
    
    std::vector<DecorationInfo*>    GetAllDecorationInfo(DECORATION_TYPE type);
    
public:
    template <typename TYPE>
    void        _clearInformation(INFORMATION<TYPE> &info)
    {
        int size = info.infoVector.size();
        for(int i=0; i<size; ++i)
            delete info.infoVector[i];
        info.infoVector.clear();
    }
};