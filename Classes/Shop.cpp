//
//  Shop.cpp
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#include "Shop.h"
#include "TestScene.h"

using namespace cocos2d;

Shop::Shop(Player *pPlayer, GameScene *pScene, PlayerUI *pPlayerUI)
{
    m_pPlayer   = pPlayer;
    m_pScene    = pScene;
    m_pPlayerUI = pPlayerUI;

    m_pBackground   = NULL;
    m_pGoldLabel    = NULL;
    m_pCashLabel    = NULL;
    m_phase         = 0;
}

Shop::~Shop()
{
    removeAllChildrenWithCleanup(true);
    
    SAFE_DELETE(m_pBackground);
    SAFE_DELETE(m_pGoldLabel);
    SAFE_DELETE(m_pCashLabel);
    
    m_pMenu->removeAllChildrenWithCleanup(true);
    
    SAFE_DELETE(m_pExit);
    for(int i=0; i<MENU_TAP_NUM; ++i)
    {
        SAFE_DELETE(m_pTap[i]);
        SAFE_DELETE(m_pTapUnLock[i]);
        SAFE_DELETE(m_pTapConponent[i]);
    }
    
    SAFE_DELETE(m_pMenu);
}

bool Shop::init()
{
    if( CCLayer::init() == false ) return false;
    
    m_pBackground = new CCSprite;
    m_pBackground->initWithFile("Shop/navy-bg.png");
    m_pBackground->setAnchorPoint(ccp(0,0));
    m_pBackground->setPosition(ccp(0,0));
    
    char txt[10];
    sprintf(txt, "%d", m_pPlayer->GetMoney());
    m_pGoldLabel = new CCLabelTTF;
    m_pGoldLabel->initWithString(txt, "굴림", 15);
    m_pGoldLabel->setColor(ccc3(0, 0, 0));
    m_pGoldLabel->setAnchorPoint(ccp(0,0));
    m_pGoldLabel->setPosition(ccp(625, 555));
    m_pGoldLabel->setScale(2.0f);
    
    m_pCashLabel = new CCLabelTTF;
    sprintf(txt, "%d", m_pPlayer->GetCash());
    m_pCashLabel->initWithString(txt, "굴림", 15);
    m_pCashLabel->setColor(ccc3(0, 0, 0));
    m_pCashLabel->setAnchorPoint(ccp(0,0));
    m_pCashLabel->setPosition(ccp(790, 555));
    m_pCashLabel->setScale(2.0f);
    
    m_pExit = new CCMenuItemImage;
    m_pExit->initWithNormalImage("Shop/x_button.png", "Shop/x_button.png", NULL, this, menu_selector(Shop::_btExit));
    m_pExit->setPosition(ccp(445, 292));
    
    CCArray *array = CCArray::createWithCapacity(10);
    array->addObject(m_pExit);
    
    for(int i=0; i<MENU_TAP_NUM; ++i)
    {
        m_pTap[i] = new CCMenuItemImage;
        m_pTapConponent[i] = new CCSprite;
        m_pTapUnLock[i] = new CCSprite;
        array->addObject(m_pTap[i]);
    }
    
    m_pTap[MENU_TAP_FISH]->initWithNormalImage("Shop/TapNotClick.png", "Shop/TapNotClick.png", NULL, this, menu_selector(Shop::_tapFish));
    m_pTap[MENU_TAP_FISH]->setPosition(ccp(-375, 153));
    
    m_pTap[MENU_TAP_STONE]->initWithNormalImage("Shop/TapNotClick.png", "Shop/TapNotClick.png", NULL, this, menu_selector(Shop::_tapStone));
    m_pTap[MENU_TAP_STONE]->setPosition(ccp(-255, 153));
    
    m_pTap[MENU_TAP_CORALREEF]->initWithNormalImage("Shop/TapNotClick.png", "Shop/TapNotClick.png", NULL, this, menu_selector(Shop::_tapCoralReef));
    m_pTap[MENU_TAP_CORALREEF]->setPosition(ccp(-135, 153));
    
    m_pTapUnLock[MENU_TAP_FISH]->initWithFile("Shop/TapClick.png");
    m_pTapUnLock[MENU_TAP_FISH]->setPosition(ccp(105, 473));
    
    m_pTapUnLock[MENU_TAP_STONE]->initWithFile("Shop/TapClick.png");
    m_pTapUnLock[MENU_TAP_STONE]->setPosition(ccp(225, 473));

    m_pTapUnLock[MENU_TAP_CORALREEF]->initWithFile("Shop/TapClick.png");
    m_pTapUnLock[MENU_TAP_CORALREEF]->setPosition(ccp(345, 473));

    m_pTapConponent[MENU_TAP_FISH]->initWithFile("Shop/fish-icon.png");
    m_pTapConponent[MENU_TAP_STONE]->initWithFile("Shop/stone-icon.png");
    m_pTapConponent[MENU_TAP_CORALREEF]->initWithFile("Shop/coralreef-icon.png");
    
    for (int i=0; i<MENU_TAP_NUM; ++i)
    {
        CCPoint pos;
        pos.x = m_pTapUnLock[i]->getPosition().x;
        pos.y = m_pTapUnLock[i]->getPosition().y;
        m_pTapConponent[i]->setPosition(pos);

        m_pTapUnLock[i]->setVisible(false);
    }
    
    m_pMenu = new CCMenu;
    m_pMenu->initWithArray(array);
    
    addChild(m_pBackground);
    addChild(m_pGoldLabel);
    addChild(m_pCashLabel);
    
    addChild(m_pMenu);
    
    for (int i=0; i<MENU_TAP_NUM; ++i)
    {
        addChild(m_pTapUnLock[i]);
        addChild(m_pTapConponent[i]);
    }
    
    for(int i=0; i<3; ++i)
    {
        m_pItemLock[i] = new CCSprite;
        m_pItemLock[i]->initWithFile("Shop/locked_gray-box.png");
        m_pItemLock[i]->setAnchorPoint(ccp(0,0));
        m_pItemLock[i]->setPosition(ccp(75 * (i+1) + i * 220, 67));
        addChild(m_pItemLock[i]);
    }

    for(int i=0; i<10; ++i)
        m_pItem[i] = new CCSprite;

    char path[30];
    
    for(int i=0; i<3; ++i)
    {
        sprintf(path, "Shop/FishItem%d.png",i+1);
        m_pItem[i]->initWithFile(path);
        m_pItem[i]->setAnchorPoint(ccp(0,0));
        m_pItem[i]->setPosition(ccp(75 * (i+1) + i * 220 + 50, 260));
        m_pItem[i]->setScale(2.0f);
        m_pItem[i]->setVisible(false);
        addChild(m_pItem[i]);
    }
    
    m_pItem[3]->initWithFile("Image/Decoration/Ston/Normal_1.png");
    m_pItem[4]->initWithFile("Image/Decoration/Ston/Normal_1_Small.png");
    m_pItem[5]->initWithFile("Image/Decoration/Ston/Wood.png");
    for(int i=0; i<3; ++i)
    {
        int idx = i + 3;
        m_pItem[idx]->setAnchorPoint(ccp(0,0));
        m_pItem[idx]->setPosition(ccp(75 * (i+1) + i * 220 + 50, 260));
        m_pItem[idx]->setAnchorPoint(ccp(0,0));
        m_pItem[idx]->setVisible(false);

        addChild(m_pItem[idx]);
    }
    m_pItem[5]->setPosition(m_pItem[5]->getPosition() - ccp(0, 20));
    
    m_pItem[6]->initWithFile("Image/Decoration/CoralReef/Normal_1.png");
    m_pItem[7]->initWithFile("Image/Decoration/CoralReef/Normal_2.png");
    m_pItem[8]->initWithFile("Image/Decoration/CoralReef/Normal_3.png");
    m_pItem[9]->initWithFile("Shop/Clam.png");

    for(int i=0; i<3; ++i)
    {
        int idx = i + 6;
        m_pItem[idx]->setAnchorPoint(ccp(0,0));
        m_pItem[idx]->setPosition(ccp(75 * (i+1) + i * 220 + 60, 260));
        m_pItem[idx]->setVisible(false);
        addChild(m_pItem[idx]);
    }
    
    m_pItem[9]->setAnchorPoint(ccp(0,0));
    m_pItem[9]->setPosition(ccp(75 + 60, 67));
    m_pItem[9]->setVisible(false);
    addChild(m_pItem[9]);
    
    _tapFish();
    setTouchEnabled(true);
    
    return true;
}

void Shop::_btExit()
{
    m_pScene->removeChild(this, true);
}

void Shop::_tapFish()
{
    _tapLock(MENU_TAP_FISH);
    m_pItemLock[0]->setVisible(true);
    m_phase = 0;
    for(int i=0; i<10; ++i)
        m_pItem[i]->setVisible(false);
    for(int i=0; i<3; ++i)
        m_pItem[i]->setVisible(true);
}

void Shop::_tapStone()
{
    _tapLock(MENU_TAP_STONE);
    m_pItemLock[0]->setVisible(true);
    m_phase = 1;
    for(int i=0; i<10; ++i)
        m_pItem[i]->setVisible(false);
    for(int i=3; i<6; ++i)
        m_pItem[i]->setVisible(true);
}

void Shop::_tapCoralReef()
{
    _tapLock(MENU_TAP_CORALREEF);
    m_pItemLock[0]->setVisible(false);
    m_phase = 2;
    for(int i=0; i<10; ++i)
        m_pItem[i]->setVisible(false);
    for(int i=6; i<10; ++i)
        m_pItem[i]->setVisible(true);
}

void Shop::_tapLock(int unlock)
{
    for(int i=0; i<MENU_TAP_NUM; ++i)
    {
        m_pTapUnLock[i]->setVisible(false);
        m_pTapConponent[i]->setOpacity(100);
    }
    
    m_pTapConponent[unlock]->setOpacity(255);
    m_pTapUnLock[unlock]->setVisible(true);
}

void Shop::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch * touch = static_cast<CCTouch *>(*pTouches->begin());
    CCPoint p = touch->getLocationInView();
    p = CCDirector::sharedDirector()->convertToGL(p);
    p.x /= 2;
    p.y += 150;
    printf("%f %f\n", p.x, p.y);
    
    typedef unsigned int uint;
    for(uint i=0; i<4; ++i)
    {
        auto rect = m_pTapUnLock[i]->boundingBox();
        printf("%f %f %f %f\n", rect.getMinX(), rect.getMinY(), rect.getMaxX(), rect.getMaxY());

        if(m_pTapUnLock[i]->boundingBox().containsPoint(p))
        {
            _buyItem(i);
            return;
        }
    }
}

void Shop::_buyFish(int i)
{
    if(i==3) return;
    if( m_pPlayer->GetMoney() - 200 < 0 )
    {
        CCMessageBox("소지금이 부족합니다", "알림");
        m_pScene->removeChild(this, true);
    }
    
    char txt[64];
    sprintf(txt, "%d번 물고기를 구입하셨습니다.\n", i+1);
    CCMessageBox(txt, "알림");
    m_pPlayer->AddMoney(-200);
    m_pPlayerUI->SetMoneyValue(m_pPlayer->GetMoney());
    
    dynamic_cast<TestScene*>(m_pScene)->addEgg(i);
    m_pScene->removeChild(this, true);
}

void Shop::_buyStone(int i)
{
    if(i==3) return;
    if( m_pPlayer->GetMoney() - 200*i < 0 )
    {
        CCMessageBox("소지금이 부족합니다", "알림");
        m_pScene->removeChild(this, true);
    }
    
    char txt[128];
    sprintf(txt, "%d번 바위를 구입하셨습니다. 선택하신곳에 바위가 배치 됩니다.\n", i+1);
    CCMessageBox(txt, "알림");

    dynamic_cast<TestScene*>(m_pScene)->addDeco(1, i);
    m_pScene->removeChild(this, true);
}

void Shop::_buyCoralReef(int i)
{
    char txt[128];
    
    if( m_pPlayer->GetMoney() - 100*2*(i+1) < 0 )
    {
        CCMessageBox("소지금이 부족합니다", "알림");
        m_pScene->removeChild(this, true);
    }
    
    if( i != 3 )
        sprintf(txt, "%d번 해초를 구입하셨습니다. 선택하신곳에 해초가 배치 됩니다.\n", i+1);
    else sprintf(txt, "조개를 구입하셨습니다. 선택하신곳에 조개가 배치 됩니다. \n");

    CCMessageBox(txt, "알림");

    dynamic_cast<TestScene*>(m_pScene)->addDeco(2, i);
    m_pScene->removeChild(this, true);
}

void Shop::_buyItem(int i)
{
    if(m_phase == MENU_TAP_FISH)
        _buyFish(i);
    else if(m_phase == MENU_TAP_STONE)
        _buyStone(i);
    else
        _buyCoralReef(i);
}
