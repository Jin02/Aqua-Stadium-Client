//
//  GameScene.cpp
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#include "GameScene.h"

using namespace cocos2d;

GameScene::GameScene() : m_pScene(NULL)
{
    
}

GameScene::~GameScene()
{
    SAFE_DELETE(m_pScene);
}

bool GameScene::init()
{
    if( CCLayer::init() == false )
        return NULL;
    
    m_pScene = new CCScene;
    
    if(m_pScene->init() == false)
    {
        SAFE_DELETE(m_pScene);
        return NULL;
    }
    
    m_pScene->addChild(this);
    
    return m_pScene;
}