//
//  CommonInfo.h
//  SeaSocialGame
//
//  Created by 박 진 on 12. 10. 16..
//
//

#pragma once

#include <string>
#include <list>
#include "Utility.h"

class CommonInfo
{
protected:
    int                 m_id;
    std::string         m_name;
    std::vector< POINT<float> >  m_vPhysicsVertex;
    
    
public:
    CommonInfo();
    CommonInfo(int id, const char *name, std::vector< POINT<float> > vPhysicsVertex);
    ~CommonInfo();
    
public:
    inline int GetID() { return m_id; }
    inline const char* GetName() { return m_name.data(); }
    std::vector< POINT<float> > GetPhysicsVertex() { return m_vPhysicsVertex; }
};