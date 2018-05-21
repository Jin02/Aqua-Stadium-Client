//
//  InfoMgr.cpp
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#include "InfoMgr.h"
#include <string>
#include <platform/CCFileUtils.h>
#include <fstream>
#include "RapidXML/rapidxml.hpp"

using namespace cocos2d;
using namespace std;
using namespace rapidxml;

InfoMgr::InfoMgr()
{
    
}

InfoMgr::~InfoMgr()
{
    _clearInformation(m_finsInfo);
    _clearInformation(m_eyeInfo);
    _clearInformation(m_bodyInfo);

    _clearInformation(m_coralReefInfo);
    _clearInformation(m_stonInfo);
    _clearInformation(m_seaweedInfo);
    _clearInformation(m_shipInfo);
    _clearInformation(m_gravelInfo);
    
    delete _db;
}

bool InfoMgr::loadData(const char *DBFileName)
{
    _db = new Sqlite3Base;
    _db->Init(DBFileName);
    
    for(int i = 0; i < FISHPART_TYPE_MAXNUM; ++i )
        _loadFishPart(_db, (FISHPART_TYPE)(i+1));
    for(int i = 0; i < DECORATION_TYPE_MAXNUM; ++i)
        _loadDecoration(_db, (DECORATION_TYPE)(i+1));
    
    return true;
}

std::vector< POINT<float> > InfoMgr::_loadPhysicsFile(const char *pXMLFile)
{
    vector< POINT<float> > list;
    std::string pathKey = CCFileUtils::sharedFileUtils()->fullPathForFilename(pXMLFile);

    printf("XML Path : %s\n", pathKey.data());

    basic_ifstream<char> xmlFile(pathKey.data());
    xmlFile.seekg(0, ios::end);
    
    if(xmlFile.good() == false)
    {
        printf("%s\n", pathKey.data());
        return list;
    }

    long long len = xmlFile.tellg();
    xmlFile.seekg(0);
    
    vector<char> xmlData(len+1);
    xmlData[len] = 0;
    xmlFile.read(&xmlData.front(), (streamsize)len);
    
    xml_document<char> xmlDoc;
    xmlDoc.parse<0>( &xmlData.front() );

    xml_node<char>      *pRoot          = xmlDoc.first_node();
    xml_node<char>      *pNode          = pRoot->first_node()->first_node()->first_node();
    xml_attribute<char> *pAttribute     = pNode->first_attribute();

    for(int i=0; i<8; ++i, pAttribute = pAttribute->next_attribute());

    int polygonNum  = atoi(pAttribute->value());
    pNode           = pNode->first_node();

    xml_node<char> *pPolygonRoot = pNode;
    
    for(int i=0; i<polygonNum;  ++i,
                                pPolygonRoot = pPolygonRoot->next_sibling())
    {
        int size = atoi(pPolygonRoot->first_attribute()->value());
        pNode = pPolygonRoot->first_node();
        for(int j=0; j<size;++j, pNode = pNode->next_sibling())
        {
            POINT<float> p;
            
            pAttribute = pNode->first_attribute();
            p.x = atof(pAttribute->value());
            pAttribute = pAttribute->next_attribute();
            p.y = atof(pAttribute->value());
            list.push_back(p);
        }
    }

    return list;
}

int InfoMgr::_getTime(int timeValue)
{
    //hhmmss
    int hour = timeValue/10000;
    int min = (timeValue - hour*10000)/100;
    int sec = timeValue%100;
    
    return sec + (min * 60) + (hour * 3600);
}

BodyInfo* InfoMgr::_loadBodyInfo(Sqlite3Base *pDBBase, std::vector< POINT<float> > &vPhysics, int &id, const char *pName)
{
    POINT<float> pos[2];

    pos[0] = POINT<float>(pDBBase->GetInt(4)/100, pDBBase->GetInt(4)%100);
    pos[1] = POINT<float>(pDBBase->GetInt(5)/100, pDBBase->GetInt(5)%100);
    FishPartPosition upFinPos( pos[0], pos[1] );

    pos[0] = POINT<float>(pDBBase->GetInt(6)/100, pDBBase->GetInt(6)%100);
    pos[1] = POINT<float>(pDBBase->GetInt(7)/100, pDBBase->GetInt(7)%100);
    FishPartPosition downFinPos( pos[0], pos[1] );

    pos[0] = POINT<float>(pDBBase->GetInt(8)/100, pDBBase->GetInt(8)%100);
    pos[1] = POINT<float>(pDBBase->GetInt(9)/100, pDBBase->GetInt(9)%100);
    FishPartPosition sideFinPos( pos[0], pos[1] );

    pos[0] = POINT<float>(pDBBase->GetInt(10)/100, pDBBase->GetInt(10)%100);
    pos[1] = POINT<float>(pDBBase->GetInt(11)/100, pDBBase->GetInt(11)%100);
    FishPartPosition tailFinPos( pos[0], pos[1] );

    POINT<float> eyePos     = POINT<float>(pDBBase->GetInt(2)/100, pDBBase->GetInt(2)%100);
    POINT<float> mouthPos   = POINT<float>(pDBBase->GetInt(3)/100, pDBBase->GetInt(3)%100);

    return new BodyInfo(id, pName, vPhysics, sideFinPos, upFinPos, downFinPos, tailFinPos, eyePos, mouthPos);
}

FinsInfo* InfoMgr::_loadFinsInfo(Sqlite3Base *pDBBase, int id, const char *pName)
{
    //pName = "FishPart/Fin/Test
    char txt[128];

    sprintf(txt, "FishPart/Fin/Up/%s.xml", pName);
    vector< POINT<float> > vUpFin   = _loadPhysicsFile(txt);

    sprintf(txt, "FishPart/Fin/Down/%s.xml", pName);
    vector< POINT<float> > vDownFin = _loadPhysicsFile(txt);

    sprintf(txt, "FishPart/Fin/Tail/%s.xml", pName);
    vector< POINT<float> > vTailFin = _loadPhysicsFile(txt);
    
    POINT<float> leftPos;
    POINT<float> rightPos;
    FishPartPosition partPos;
    
    leftPos     = POINT<float>(pDBBase->GetInt(2)/100, pDBBase->GetInt(2)%100);
    rightPos    = POINT<float>(pDBBase->GetInt(3)/100, pDBBase->GetInt(3)%100);
    partPos     = FishPartPosition(leftPos, rightPos);
    
    FinInfo upFin = FinInfo(vUpFin, partPos);
    
    leftPos     = POINT<float>(pDBBase->GetInt(4)/100, pDBBase->GetInt(4)%100);
    rightPos    = POINT<float>(pDBBase->GetInt(5)/100, pDBBase->GetInt(5)%100);
    partPos     = FishPartPosition(leftPos, rightPos);
    
    FinInfo downFin = FinInfo(vDownFin, partPos);
    
    leftPos     = POINT<float>(pDBBase->GetInt(6)/100, pDBBase->GetInt(6)%100);
    rightPos    = POINT<float>(pDBBase->GetInt(7)/100, pDBBase->GetInt(7)%100);
    partPos     = FishPartPosition(leftPos, rightPos);

    FinInfo tailFin = FinInfo(vTailFin, partPos);
    
    POINT<float> sidePos = POINT<float>(pDBBase->GetInt(8)/100, pDBBase->GetInt(8)%100);
    
    return new FinsInfo(id, pName, upFin, downFin, tailFin, sidePos);
}

bool InfoMgr::_loadFishPart(Sqlite3Base *pDBBase, FISHPART_TYPE type)
{
    std::string fileName = "FishPart/";
    const char *cmd;
    
    switch (type) {
        case FISHPART_TYPE_BODY:
            cmd = "SELECT * FROM Body Order By id";
//            fileName+="Body/";
            break;
        case FISHPART_TYPE_EYE:
            cmd = "SELECT * FROM Eye Order By id";
  //          fileName+="Eye/";
            break;
        case FISHPART_TYPE_FIN:
            cmd = "SELECT * FROM Fin Order By id";
    //         fileName+="Fin/";
            break;
        default: break;
    }
    
    if( pDBBase->ErrorCheck(cmd) == false )
    {
        printf("%s <- Error \n", __FUNCTION__);
        return false;
    }
    do
    {
        int id                = pDBBase->GetInt(0);
        const char *pName     = pDBBase->GetTxt(1);

        switch (type){
            case FISHPART_TYPE_BODY:    fileName += "Body/";    break;
            case FISHPART_TYPE_EYE:     fileName += "Eye/";     break;
            case FISHPART_TYPE_FIN:     fileName += "Fin/";     break;
        }
        
        fileName += pName;

        FishPartInfo *pInfo;
        
        vector< POINT<float> > vPhysics;
        
        if(type == FISHPART_TYPE_FIN)
            pInfo = _loadFinsInfo(pDBBase, id, pName);
        else if(type == FISHPART_TYPE_BODY)
        {
            fileName += ".xml";
            printf("%s\n", fileName.data());
            vPhysics = _loadPhysicsFile(fileName.data());
        }
        else pInfo = new FishPartInfo(type, id, pName, vPhysics);
        
        switch (type) {
            case FISHPART_TYPE_FIN:
                m_finsInfo.add(dynamic_cast<FinsInfo*>(pInfo));
                break;
            case FISHPART_TYPE_BODY:
                pInfo = _loadBodyInfo(pDBBase, vPhysics, id, pName);
                m_bodyInfo.add(dynamic_cast<BodyInfo*>(pInfo));
                break;
            case FISHPART_TYPE_EYE:     m_eyeInfo.add(pInfo);       break;
            default: break;
        }
        
        fileName = "FishPart/";
    }
    while (pDBBase->isNextStep());
    pDBBase->Finalize();
    
    return true;
}

bool InfoMgr::_loadDecoration(Sqlite3Base *pDBBase, DECORATION_TYPE type)
{
    std::string fileName = "Decoration/";
    const char *cmd;
    
    switch (type) {
        case DECORATION_TYPE_CORALREEF:
            cmd = "SELECT * FROM CoralReef Order By id";
//            fileName += "CoralReef/";
            break;
        case DECORATION_TYPE_SEAWEED:
            cmd = "SELECT * FROM Seaweed Order By id";
  //          fileName += "Seaweed/";
            break;
        case DECORATION_TYPE_SHIP:
            cmd = "SELECT * FROM Ship Order By id";
    //        fileName += "Ship/";
            break;
        case DECORATION_TYPE_STON:
            cmd = "SELECT * FROM Ston Order By id";
      //      fileName += "Ston/";
            break;
        case DECORATION_TYPE_GRAVEL:
            cmd = "SELECT * FROM Gravel Order By id";
        //    fileName += "Gravel/";
            break;
        case DECORATION_TYPE_CLAM:
            cmd = "SELECT * FROM Clam Order by id";
            break;
        default: break;
    }
    
    if( pDBBase->ErrorCheck(cmd) == false )
    {
        printf("%s <- Error \n", __FUNCTION__);
        return false;
    }
    do
    {
        int id                = pDBBase->GetInt(0);
        float rate            = pDBBase->GetDouble(1);
        const char *pName     = pDBBase->GetTxt(2);
        
        switch (type)
        {
            case DECORATION_TYPE_CLAM:      fileName += "Clam/";        break;
            case DECORATION_TYPE_CORALREEF: fileName += "CoralReef/";   break;
            case DECORATION_TYPE_STON:      fileName += "Ston/";        break;
            case DECORATION_TYPE_GRAVEL:    fileName += "Gravel/";      break;
            case DECORATION_TYPE_SEAWEED:   fileName += "Seaweed/";     break;
            case DECORATION_TYPE_SHIP:      fileName += "Ship/";        break;
            default: break;
        }
    
        fileName += pName;
        fileName += ".xml";

        vector< POINT<float> > vPhysics = _loadPhysicsFile(fileName.data());
        
        DecorationInfo *pInfo =  new DecorationInfo(id, type, rate, pName, vPhysics);
        
        pair<const char*, DecorationInfo*> pair;
        pair.first  = pInfo->GetName();
        pair.second = pInfo;
        
        switch (type) {
            case DECORATION_TYPE_CORALREEF: m_coralReefInfo.add(pInfo); break;
            case DECORATION_TYPE_SEAWEED:   m_seaweedInfo.add(pInfo);   break;
            case DECORATION_TYPE_SHIP:      m_shipInfo.add(pInfo);      break;
            case DECORATION_TYPE_STON:      m_stonInfo.add(pInfo);      break;
            case DECORATION_TYPE_GRAVEL:    m_gravelInfo.add(pInfo);    break;
            case DECORATION_TYPE_CLAM:      m_clamInfo.add(pInfo);      break;
            default: break;
        }
        
        fileName = "Decoration/";
    }
    while (pDBBase->isNextStep());
    pDBBase->Finalize();
    
    return true;
}

bool InfoMgr::searchInfo(int id, FISHPART_TYPE type, FishPartInfo **ppInfo)
{
    switch (type) {
        case FISHPART_TYPE_BODY:    *ppInfo = m_bodyInfo.find(id);       break;
        case FISHPART_TYPE_EYE:     *ppInfo = m_eyeInfo.find(id);       break;
        case FISHPART_TYPE_FIN:     *ppInfo = m_finsInfo.find(id);       break;
        default: return false;
    }    
    
    return true;
}

bool InfoMgr::searchInfo(const char *name, FISHPART_TYPE type, FishPartInfo **ppInfo)
{
    FishPartInfo *pOut = NULL;
    
    switch (type) {
        case FISHPART_TYPE_BODY:    pOut = m_bodyInfo.find(name);      break;
        case FISHPART_TYPE_EYE:     pOut = m_eyeInfo.find(name);       break;
        case FISHPART_TYPE_FIN:     pOut = m_finsInfo.find(name);       break;
        default: break;
    }
    
    if( pOut == NULL)
        return false;

    *ppInfo = pOut;
    
    return true;
}

bool InfoMgr::searchInfo(int id, DECORATION_TYPE type, DecorationInfo **ppInfo)
{
    switch (type) {
        case DECORATION_TYPE_CORALREEF: *ppInfo = m_coralReefInfo.find(id);  break;
        case DECORATION_TYPE_GRAVEL:    *ppInfo = m_gravelInfo.find(id);     break;
        case DECORATION_TYPE_SEAWEED:   *ppInfo = m_seaweedInfo.find(id);    break;
        case DECORATION_TYPE_SHIP:      *ppInfo = m_shipInfo.find(id);       break;
        case DECORATION_TYPE_STON:      *ppInfo = m_stonInfo.find(id);       break;
        case DECORATION_TYPE_CLAM:      *ppInfo = m_clamInfo.find(id);       break;
        default: return false;
    }

    return true;
}

bool InfoMgr::searchInfo(const char *name, DECORATION_TYPE type, DecorationInfo **ppInfo)
{
    DecorationInfo *pOut = NULL;
    
    switch (type) {
            case DECORATION_TYPE_CORALREEF: pOut = m_coralReefInfo.find(name);  break;
            case DECORATION_TYPE_GRAVEL:    pOut = m_gravelInfo.find(name);     break;
            case DECORATION_TYPE_SEAWEED:   pOut = m_seaweedInfo.find(name);    break;
            case DECORATION_TYPE_SHIP:      pOut = m_shipInfo.find(name);       break;
            case DECORATION_TYPE_STON:      pOut = m_stonInfo.find(name);       break;
        case DECORATION_TYPE_CLAM:      pOut = m_clamInfo.find(name); break;

        default: break;
    }
    
    if( pOut == NULL)
        return false;
    
    *ppInfo = pOut;
    
    return true;

}

std::vector<BodyInfo*> InfoMgr::GetAllBodyInfo()
{
    return m_bodyInfo.infoVector;
}

std::vector<EyeInfo*> InfoMgr::GetAllEyeInfo()
{
    return m_eyeInfo.infoVector;
}

std::vector<FinsInfo*> InfoMgr::GetAllFinsInfo()
{
    return m_finsInfo.infoVector;
}

std::vector<DecorationInfo*> InfoMgr::GetAllDecorationInfo(DECORATION_TYPE type)
{
    switch (type) {
        case DECORATION_TYPE_CORALREEF:     return m_coralReefInfo.infoVector;
        case DECORATION_TYPE_SEAWEED:       return m_seaweedInfo.infoVector;
        case DECORATION_TYPE_SHIP:          return m_shipInfo.infoVector;
        case DECORATION_TYPE_STON :         return m_stonInfo.infoVector;
        case DECORATION_TYPE_CLAM:          return m_clamInfo.infoVector;
        case DECORATION_TYPE_GRAVEL:        return m_gravelInfo.infoVector;
        default: break;
    }
    
    return vector<DecorationInfo*>();
}