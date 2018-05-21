//
//  Tap.cpp
//  SeaSocialGame
//
//  Created by 박 진 on 12. 11. 18..
//
//

#include "Tap.h"
#include "Utility.h"

using namespace cocos2d;

Tap::Tap()
{
    
}

Tap::~Tap()
{
    removeAllChildrenWithCleanup(true);
    
    SAFE_DELETE(m_pContent);
    SAFE_DELETE(m_pSelectTap);
    SAFE_DELETE(m_pNotSelectTap);
}

bool Tap::init(cocos2d::CCPoint position, bool isSelect, const char *imgPath, int type)
{
    m_pSelectTap = new CCSprite;
    m_pSelectTap->initWithFile("");
    m_pSelectTap->setAnchorPoint(ccp(0,0));
    m_pSelectTap->setPosition(position);
    
    m_pNotSelectTap = new CCSprite;
    m_pNotSelectTap->initWithFile("");
    m_pNotSelectTap->setAnchorPoint(ccp(0,0));
    m_pNotSelectTap->setPosition(position);
    
    m_pContent = new CCSprite;
    m_pContent->initWithFile(imgPath);
    m_pContent->setPosition(ccp(position.x + m_pSelectTap->getContentSize().width/2,
                                position.y + m_pSelectTap->getContentSize().height/2));
    
    if(isSelect)
    {
        m_pNotSelectTap->setVisible(false);
    }
    else
    {
        m_pSelectTap->setVisible(false);
        m_pContent->setOpacity(100);
    }
    
    m_type = type;
    
    return true;
}

void Tap::select()
{
    m_pNotSelectTap->setVisible(false);
    m_pSelectTap->setVisible(true);
    m_pContent->setOpacity(255);
}

void Tap::notSelect()
{
    m_pSelectTap->setVisible(false);
    m_pNotSelectTap->setVisible(true);
    m_pContent->setOpacity(100);
}