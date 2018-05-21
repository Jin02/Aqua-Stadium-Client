//
//  TestScene.cpp
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#include "TestScene.h"
#include "InfoMgr.h"

using namespace cocos2d;

TestScene::TestScene()
{
    m_pBackGround   = NULL;
    m_pUI           = NULL;
    m_pPlayerUI     = NULL;
    m_isFood        = false;
    m_pJoint        = NULL;
    m_pPlayer       = NULL;
    m_pShop         = NULL;
    m_isDecoAdd     = false;
    m_isTitle       = true;
}

TestScene::~TestScene()
{
    removeAllChildrenWithCleanup(true);    
    SAFE_DELETE(m_pBackGround);
    SAFE_DELETE(m_pUI);
    SAFE_DELETE(m_pPlayerUI);
    SAFE_DELETE(m_pPlayer);
    SAFE_DELETE(m_pShop);
}

bool TestScene::init()
{
    if( GameScene::init() == false )
        return false;
    
    m_pBackGround = new CCSprite;
    m_pBackGround->initWithFile("Image/BackGround_3-hd.jpg");
//    m_pBackGround->setScale(0.5f);
    m_pBackGround->setPosition(ccp(0,0));
    m_pBackGround->setAnchorPoint(ccp(0.0,0.0));
    
    addChild(m_pBackGround);
    scheduleUpdate();
    
    setTouchEnabled(true);

    m_pPlayer = new Player;
    m_pPlayer->Init();
    m_pPlayer->AddCash(100);
    m_pPlayer->AddMoney(5000);    
    
    m_pGameSystem = new GameSystem(this, m_pPlayer);
    m_pGameSystem->init();

    CommonFishPartInfo body("Body2", COLOR_ARGB(255, 255, 255, 255));
    CommonFishPartInfo eye("Eye2", COLOR_ARGB(255, 255, 255, 255));
    CommonFishPartInfo fin("Fin1", COLOR_ARGB(255, 255, 255, 255));

    m_pGameSystem->addFish(FishStatus(0, 100, 0, 3), ccp(240, 200), eye, body, fin, 15, true, 0);    
    
    m_pUI = new GameUI(this);
    UI_BUTTON btFriend("GameUI/FriendButton.png", "GameUI/FriendButton.png", this, menu_selector(TestScene::_friendUI), ccp(400,-100));
    UI_BUTTON btShop("GameUI/ShopButton.png", "GameUI/ShopButton.png", this, menu_selector(TestScene::_shopUI), ccp(400,0));
    UI_BUTTON btFoodInven("GameUI/FoodInven.png", "GameUI/FoodInven.png", this, menu_selector(TestScene::_foodUI), ccp(400,100));
    
    m_pUI->init(btFriend, btShop, btFoodInven);
    addChild(m_pUI, 10);
    
    m_pPlayerUI = new PlayerUI;
    m_pPlayerUI->init(15, ccp(630, 450), ccp(630, 420));
    addChild(m_pPlayerUI, 10);
    
    m_pPlayerUI->SetMoneyValue(5000);
    m_pPlayerUI->SetCashValue(100);
    
    m_pShop = new Shop(m_pPlayer, this, m_pPlayerUI);
    m_pShop->init();
    
    m_pAddArea = new CCSprite;
    m_pAddArea->initWithFile("Image/area.png");
    m_pAddArea->setAnchorPoint(ccp(0,0));
    m_pAddArea->setPosition(ccp(0,0));
    m_pAddArea->setVisible(false);
    addChild(m_pAddArea);
    
    
    schedule(schedule_selector(TestScene::_addBubble), 0.5);
    
    m_pTmpBack = new CCSprite;
    m_pTmpBack->initWithFile("Image/BackGround_3-hd.jpg");
    m_pTmpBack->setPosition(ccp(0,0));
//    m_pTmpBack->setScale(0.5);
    m_pTmpBack->setAnchorPoint(ccp(0,0));
    addChild(m_pTmpBack,50);
    
    m_pTitle = new CCSprite;
    m_pTitle->initWithFile("Image/aquastadium_title.png");
    m_pTitle->setPosition(CCDirector::sharedDirector()->getWinSize()/2);
    
//    m_pTitle->setScale(0.5);
    addChild(m_pTitle,50);
    
    return true;
}

void TestScene::update(float dt)
{
    m_pGameSystem->update(dt);
}

void TestScene::_titleOff()
{
    removeChild(m_pTitle, true);
    removeChild(m_pTmpBack, true);
    
    SAFE_DELETE(m_pTmpBack);
    SAFE_DELETE(m_pTitle);
}

void TestScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch * touch = static_cast<CCTouch *>(*pTouches->begin());
    CCPoint p = touch->getLocationInView();
    p = CCDirector::sharedDirector()->convertToGL(p);
    
    if(m_isTitle)
    {
        CCFadeOut *fadeOut = CCFadeOut::create(1.f);
        CCMoveBy  *move = CCMoveBy::create(1.f, ccp(0, - 300));
        CCDelayTime *delay = CCDelayTime::create(1.f);
        CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(TestScene::_titleOff));
        CCSequence *seq = CCSequence::create(delay, func);
        
        m_pTitle->runAction(move);
        m_pTmpBack->runAction(fadeOut);
        this->runAction(seq);
        
        m_isTitle = false;
    }
    if(m_isDecoAdd)
    {
        if(intersectBoxWithPoint(POINT<float>(0, 0), SIZE<float>(480, 35), POINT<float>(p.x, p.y)))
        {
            int id;
            DECORATION_TYPE type;
            cocos2d::CCPoint position;
            
            if( m_tap == 1 )
            {
                id = m_addShopIdx;
                type = DECORATION_TYPE_STON;
            }
            else
            {
                id = m_addShopIdx;
                type = DECORATION_TYPE_CORALREEF;
            
                if( id == 3 )
                {
                    id = 0;
                    type = DECORATION_TYPE_CLAM;
                }
            }
            
            position = ccp(p.x, p.y);
            m_pGameSystem->addDeco(id, type, position, true);
            m_pPlayer->AddMoney(-100*m_tap*(id+1));
            m_pPlayerUI->SetMoneyValue(m_pPlayer->GetMoney());
            
            m_isDecoAdd = false;
            m_pAddArea->setVisible(false);
        }
 
        return;
    }
    

    b2MouseJointDef def;
    
    m_pFish[0] = m_pFish[1] = NULL;
    m_pFish[1] = m_pGameSystem->GetObjMgr()->findFish(p);

    def.target = b2Vec2(p.x/PTM_RATIO, p.y/PTM_RATIO);
    def.collideConnected = true;
    def.dampingRatio = 1.f;
    def.frequencyHz = 1.f;
    def.maxForce = 25.f;
    def.bodyA = m_pGameSystem->GetGroundBody();

    if(m_pFish[1])
        def.bodyB = m_pFish[1]->GetBody();
    else
    {
        Egg *pEgg = m_pGameSystem->GetObjMgr()->findEgg(p);
        if(pEgg)
        {
            if(pEgg->GetTime() < 10.f)
                def.bodyB = pEgg->GetBody();
        }
    }

    if(def.bodyB)
        m_pJoint = (b2MouseJoint*)m_pGameSystem->GetWorld()->CreateJoint(&def);
    
    if(m_isFood && m_pPlayer->GetMoney()-5 > 0)
    {
        m_pGameSystem->addFood(p);
        m_pPlayer->AddMoney(-5);
        m_pPlayerUI->SetMoneyValue(m_pPlayer->GetMoney());
    }
}

void TestScene::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch * touch = static_cast<CCTouch *>(*pTouches->begin());
    CCPoint p = touch->getLocationInView();
    p = CCDirector::sharedDirector()->convertToGL(p);

    if(m_pJoint)
        m_pJoint->SetTarget(b2Vec2(p.x/PTM_RATIO, p.y/PTM_RATIO));
}

void TestScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch * touch = static_cast<CCTouch *>(*pTouches->begin());
    CCPoint p = touch->getLocationInView();
    p = CCDirector::sharedDirector()->convertToGL(p);

    m_pFish[0] = m_pGameSystem->GetObjMgr()->findFish(p);
    m_pGameSystem->Crossbreed(m_pFish[0], m_pFish[1]);
    
    if(m_pJoint)
    {
        m_pGameSystem->GetWorld()->DestroyJoint(m_pJoint);
        m_pJoint = NULL;
    }
}

void TestScene::_friendUI(cocos2d::CCObject *pSender)
{
    printf("friendUI\n");
}

void TestScene::_shopUI(cocos2d::CCObject *pSender)
{
    removeChild(m_pShop, true);
    printf("shopUI\n");
    addChild(m_pShop,20);
}

void TestScene::_foodUI(cocos2d::CCObject *pSender)
{
    printf("foodUI\n");

    if((m_isFood = !m_isFood))
        m_pUI->SetFoodIconColor(ccc3(128, 128, 128));
    else
        m_pUI->SetFoodIconColor(ccc3(255, 255, 255));
}

void TestScene::_addBubble()
{
    
    float x = rand() % (uint)(CCDirector::sharedDirector()->getWinSize().width);
    m_pGameSystem->GetObjMgr()->addBubble(ccp(x, 10));
}

void TestScene::addEgg(int i)
{
    CommonFishPartInfo body;//
    CommonFishPartInfo eye;//("Eye1", COLOR_ARGB(255, 255, 255, 255));
    CommonFishPartInfo fin;//("Fin1", COLOR_ARGB(255, 255, 255, 0));

    if( i == 0 )
    {
        body    = CommonFishPartInfo("Body1", COLOR_ARGB(255, 0, 168, 144));
        eye     = CommonFishPartInfo("Eye1", COLOR_ARGB(255, 255, 255, 255));
        fin     = CommonFishPartInfo("Fin1", COLOR_ARGB(255, 255, 209, 123));
    }
    else if( i == 1 )
    {
        body    = CommonFishPartInfo("Body1", COLOR_ARGB(255, 255, 242, 218));
        eye     = CommonFishPartInfo("Eye1", COLOR_ARGB(255, 255, 255, 255));
        fin     = CommonFishPartInfo("Fin2", COLOR_ARGB(255, 232, 61, 54));
    }
    else
    {
        body    = CommonFishPartInfo("Body2", COLOR_ARGB(255, 250, 248, 186));
        eye     = CommonFishPartInfo("Eye2", COLOR_ARGB(255, 255, 255, 255));
        fin     = CommonFishPartInfo("Fin3", COLOR_ARGB(255, 244, 108, 97));
    }
    
//    DNA(Tag(), <#BodyInfo *pBodyInfo#>, <#FinsInfo *pFinsInfo#>, <#EyeInfo *pEyeInfo#>, <#double growCompTime#>)
    
    BodyInfo *pBody = NULL;
    m_pGameSystem->GetInfoMgr()->searchInfo(body.name, FISHPART_TYPE_BODY, reinterpret_cast<FishPartInfo**>(&pBody));
    ((BodyInfo*)pBody)->m_color = body.color;
    
    FinsInfo *pFins = NULL;
    m_pGameSystem->GetInfoMgr()->searchInfo(fin.name, FISHPART_TYPE_FIN, reinterpret_cast<FishPartInfo**>(&pFins));
    pFins->m_color = fin.color;

    EyeInfo *pEye = NULL;
    m_pGameSystem->GetInfoMgr()->searchInfo(eye.name, FISHPART_TYPE_EYE, reinterpret_cast<FishPartInfo**>(&pEye));
    pEye->m_color = eye.color;

    Tag tag;
    DNA dna(tag, pBody, pFins, pEye, 15.f);
    
    Egg *pEgg = new Egg(m_pGameSystem, dna, 0);
    pEgg->init(m_pGameSystem->GetWorld(), ccp(rand()%480, 280), 15, 15);
    m_pGameSystem->GetObjMgr()->addEgg(pEgg, true, 0);
}

void TestScene::addDeco(int tap, int i)
{
    m_isDecoAdd = true;
    m_pAddArea->setVisible(true);
    m_tap =tap;
    m_addShopIdx = i;
}
