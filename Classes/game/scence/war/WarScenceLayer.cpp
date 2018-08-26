			//
//  WarScenceLayer.cpp
//  game1
//
//  Created by 俊盟科技1 on 8/22/14.
//
//

#include "WarScenceLayer.h"
#include "GameViewConfig.h"
#include "Box2dWordManger.h"
#include "MainCityScence.h"
#include "TimeUtil.h"
#include "WinDialog.h"
#include "LossDialog.h"
#include "SkillActionManger.h"
#include "StrSplit.h"
#include "DrawSolidRectClass.h"
#include "SimpleAudioEngine.h"
#include "AStarMap6SideManger.h"
#include "SkillEffectAction.h"
#include "WarNetDataManger.h"
#define kupDataZodertimer      0.3f       //z坐标刷新时间
#define kupDataJinDu            10       //z坐标显示精度
#define kBoxLayerCount         1300         //获利物品所在层数
#define kSkillLayercount       1400         //技能所在层数
#define kUILayercount          2000         //用户界面所在层数
#define kRewardMoveSpeed       400          //获利宝箱移动速度
#define kEveryWarTime          180          //每场战斗用时180秒
#define kSkillActionOffSet (Vec2(-2.0f,-2.0f))

#define KActionMoveTo   "tx_dianjizhou"



WarScenceLayer* WarScenceLayer::createWarWithMapID(int ID)
{
    WarScenceLayer* tmp = new WarScenceLayer();
    tmp->autorelease();
    tmp->m_ID = ID;
    tmp->init();
    return tmp;
}

// on "init" you need to initialize your instance
void WarScenceLayer::initMapBG()
{
    std::string tmpefid = m_mapDataST.checkpoint_resource;
    std::vector<std::string> tmpx = StrSplit::split(tmpefid, ",");
    
    m_mapNumber = (int)tmpx.size();
    
    switch (m_mapNumber) {
        case 1:
        {
            m_mapBG[0] = tmpx[0];
            m_mapBG[1] = "";
            m_mapBG[2] = "";
        }
            break;
        case 2:
        {
            m_mapBG[0] = tmpx[0];
            m_mapBG[1] = tmpx[1];
            m_mapBG[2] = "";
        }
            break;
        case 3:
        {
            m_mapBG[0] = tmpx[0];
            m_mapBG[1] = tmpx[1];
            m_mapBG[2] = tmpx[2];
        }
            break;
        default:
            break;
    }
}
bool WarScenceLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    m_isWarEnd = true;
    m_isSetWarEnd = 0;
    AStarMap6SideManger::sharedAStarMap6SideManger()->initMapArrWithMapID(m_ID);
    //通过战场编号从本地或网络取得战场信息
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/warBgmusic.mp3");
    //胜利
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/Battle_Win.mp3");
    //失败
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/Battle_Lose.mp3");
    
    //通过副本ID得到副本数据
    m_mapDataST = LocalDataManger::sharedLocalDataManger()->getConfigtab_checkpoints_sysDataST(m_ID);
    
    
    this->initMapBG();
    
    
    //头像框能量满动画
    string actionID = "tx_faguang";
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("ui/tx/"+actionID+"/" + actionID +"0.png","ui/tx/"+actionID+"/" + actionID + "0.plist","ui/tx/"+actionID+"/" +actionID + ".ExportJson");
    
    
    //加载战斗选择动画
    SkillActionManger::sharedSkillActionManger()->loadEffectWhenWarStart();
    

    s_skillMaskBG = LayerColor::create(Color4B(0,0,0,170), kWidthWindow, kHeightWindow);
    s_skillMaskBG->setVisible(false);
    this->addChild(s_skillMaskBG,1);
    showMaskCount = 0;

//-test----------------
    std::string mappath = "map/" + m_mapBG[0];
    s_MapBG = Sprite::create(mappath);
    s_MapBG->setPosition(Vec2(kWidthWindow/2.0f,kHeightWindow/2.0f));
    this->addChild(s_MapBG,-1);
    
    //加载战斗子子弹图片
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("skill/skillPlist.plist");
    
    //加载战斗头像图片
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite/touxiang/warheroicon.plist");
    
    _layout = dynamic_cast<ui::Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/WarUI/WarUI_1.ExportJson"));

    _layout->setTouchEnabled(false);
    this->addChild(_layout,kUILayercount);

    ourSpCount = 0;
    enemyCount = 0;
    
    
    //战斗场数
    m_warCount = 0;
    
    
//精灵站位初始化坐标
//我方
    ui::Layout* spo1 = dynamic_cast<ui::Layout*>(_layout->getChildByName("sprite1"));
    ui::Layout* spo2 = dynamic_cast<ui::Layout*>(_layout->getChildByName("sprite2"));
    ui::Layout* spo3 = dynamic_cast<ui::Layout*>(_layout->getChildByName("sprite3"));
    ui::Layout* spo4 = dynamic_cast<ui::Layout*>(_layout->getChildByName("sprite4"));
    ui::Layout* spo5 = dynamic_cast<ui::Layout*>(_layout->getChildByName("sprite5"));
    ui::Layout* spo6 = dynamic_cast<ui::Layout*>(_layout->getChildByName("sprite6"));
    
    m_ourStartPointVecotr.push_back(spo1->getPosition());
    m_ourStartPointVecotr.push_back(spo2->getPosition());
    m_ourStartPointVecotr.push_back(spo3->getPosition());
    m_ourStartPointVecotr.push_back(spo4->getPosition());
    m_ourStartPointVecotr.push_back(spo5->getPosition());
    m_ourStartPointVecotr.push_back(spo6->getPosition());
    
//敌方
    ui::Layout* epo1 = dynamic_cast<ui::Layout*>(_layout->getChildByName("enemy1"));
    ui::Layout* epo2 = dynamic_cast<ui::Layout*>(_layout->getChildByName("enemy2"));
    ui::Layout* epo3 = dynamic_cast<ui::Layout*>(_layout->getChildByName("enemy3"));
    ui::Layout* epo4 = dynamic_cast<ui::Layout*>(_layout->getChildByName("enemy4"));
    ui::Layout* epo5 = dynamic_cast<ui::Layout*>(_layout->getChildByName("enemy5"));
    ui::Layout* epo6 = dynamic_cast<ui::Layout*>(_layout->getChildByName("enemy6"));
    m_backBtn = static_cast<ui::Button*>(_layout->getChildByName("play_button"));
    m_backBtn->setTag(10);
    m_backBtn->addTouchEventListener(CC_CALLBACK_2(WarScenceLayer::buttonHeroEvent, this));
    
//    m_goOnBtn = static_cast<ui::Button*>(_layout->getChildByName("play_button"));
//    m_goOnBtn->setTag(11);
//    m_goOnBtn->addTouchEventListener(CC_CALLBACK_2(WarScenceLayer::buttonHeroEvent, this));
    
    
    s_box = static_cast<ui::ImageView*>(_layout->getChildByName("box"));
    
    s_textBoxCount = static_cast<ui::TextBMFont*>(s_box->getChildByName("BitmapLabel_286"));
    s_boxNumber = 0;
    s_textBoxCount->setString("0");
    
    s_time = kEveryWarTime;
    auto tmpTime = static_cast<ui::ImageView*>(_layout->getChildByName("time"));
    s_timeText = static_cast<ui::TextBMFont*>(tmpTime->getChildByName("BitmapLabel_291"));
    s_timeText->setString(TimeUtil::secendToString_M_S(s_time));
    
    m_enemyStartPointVector.push_back(epo1->getPosition());
    m_enemyStartPointVector.push_back(epo2->getPosition());
    m_enemyStartPointVector.push_back(epo3->getPosition());
    m_enemyStartPointVector.push_back(epo4->getPosition());
    m_enemyStartPointVector.push_back(epo5->getPosition());
    m_enemyStartPointVector.push_back(epo6->getPosition());

    DropItemsST st;
    m_enamyDropItemVector.push_back(st);
    m_enamyDropItemVector.clear();
    
    hero1Layout = static_cast<ui::Layout*>(_layout->getChildByName("hearhand1_space"));
    hero1Layout->setVisible(false);
    
    hero2Layout = static_cast<ui::Layout*>(_layout->getChildByName("hearhand2_space"));
    hero2Layout->setVisible(false);
    
    hero3Layout = static_cast<ui::Layout*>(_layout->getChildByName("hearhand3_space"));
    hero3Layout->setVisible(false);
    
    hero4Layout = static_cast<ui::Layout*>(_layout->getChildByName("hearhand4_space"));
    hero4Layout->setVisible(false);
    
    hero5Layout = static_cast<ui::Layout*>(_layout->getChildByName("hearhand5_space"));
    hero5Layout->setVisible(false);
    
    //hero1
    heroicon1 = static_cast<ui::ImageView*>(hero1Layout->getChildByName("hand1_image"));
    heroBtn1 = static_cast<ui::Button*>(hero1Layout->getChildByName("Button_tx"));
    heroBtn1->setTouchEnabled(false);
    for (int i = 0; i < 5; i++) {
        string tmpname = "Image_star" + to_string(i+1);
        hero1StarVector[i] = static_cast<ui::ImageView*>(Helper::seekWidgetByName(hero1Layout,tmpname));
        hero1StarVector[i]->setVisible(false);
    }
    hero1skill = cocostudio::Armature::create("tx_faguang");
    Point tmppo = heroicon1->getWorldPosition();
    tmppo.add(kSkillActionOffSet);
    hero1skill->setPosition(tmppo);
    this->addChild(hero1skill,kUILayercount+1);
    hero1skill->setVisible(false);
    
    
    //hero2
    heroicon2 = static_cast<ui::ImageView*>(hero2Layout->getChildByName("hand1_image"));
    heroBtn2 = static_cast<ui::Button*>(hero2Layout->getChildByName("Button_tx"));
    heroBtn2->setTouchEnabled(false);
    for (int i = 0; i < 5; i++) {
        string tmpname = "Image_star" + to_string(i+1);
        hero2StarVector[i] = static_cast<ui::ImageView*>(hero2Layout->getChildByName(tmpname));
        hero2StarVector[i]->setVisible(false);
    }
    hero2skill = cocostudio::Armature::create("tx_faguang");
    tmppo = heroicon2->getWorldPosition();
    tmppo.add(kSkillActionOffSet);
    hero2skill->setPosition(tmppo);
    this->addChild(hero2skill,kUILayercount+1);
    hero2skill->setVisible(false);
    
    //hero3
    heroicon3 = static_cast<ui::ImageView*>(hero3Layout->getChildByName("hand1_image"));
    heroBtn3 = static_cast<ui::Button*>(hero3Layout->getChildByName("Button_tx"));
    heroBtn3->setTouchEnabled(false);
    for (int i = 0; i < 5; i++) {
        string tmpname = "Image_star" + to_string(i+1);
        hero3StarVector[i] = static_cast<ui::ImageView*>(hero3Layout->getChildByName(tmpname));
        hero3StarVector[i]->setVisible(false);
    }
    hero3skill = cocostudio::Armature::create("tx_faguang");
    tmppo = heroicon3->getWorldPosition();
    tmppo.add(kSkillActionOffSet);
    hero3skill->setPosition(tmppo);
    this->addChild(hero3skill,kUILayercount+1);
    hero3skill->setVisible(false);
    
    //hero4
    heroicon4 = static_cast<ui::ImageView*>(hero4Layout->getChildByName("hand1_image"));
    heroBtn4 = static_cast<ui::Button*>(hero4Layout->getChildByName("Button_tx"));
    heroBtn4->setTouchEnabled(false);
    for (int i = 0; i < 5; i++) {
        string tmpname = "Image_star" + to_string(i+1);
        hero4StarVector[i] = static_cast<ui::ImageView*>(hero4Layout->getChildByName(tmpname));
        hero4StarVector[i]->setVisible(false);
    }
    hero4skill = cocostudio::Armature::create("tx_faguang");
    tmppo = heroicon4->getWorldPosition();
    tmppo.add(kSkillActionOffSet);
    hero4skill->setPosition(tmppo);
    this->addChild(hero4skill,kUILayercount+1);
    hero4skill->setVisible(false);

    //hero5
    heroicon5 = static_cast<ui::ImageView*>(hero5Layout->getChildByName("hand1_image"));
    heroBtn5 = static_cast<ui::Button*>(hero5Layout->getChildByName("Button_tx"));
    heroBtn5->setTouchEnabled(false);
    for (int i = 0; i < 5; i++) {
        string tmpname = "Image_star" + to_string(i+1);
        hero5StarVector[i] = static_cast<ui::ImageView*>(hero5Layout->getChildByName(tmpname));
        hero1StarVector[i]->setVisible(false);
    }
    hero5skill = cocostudio::Armature::create("tx_faguang");
    tmppo = heroicon5->getWorldPosition();
    tmppo.add(kSkillActionOffSet);
    hero5skill->setPosition(tmppo);
    this->addChild(hero5skill,kUILayercount+1);
    hero5skill->setVisible(false);
    
#if 1
    this->setEnamyDataWithSplitString(m_mapDataST.checkpoint_monsters);
    this->setEnamyDropItemsDataWithSplitString(m_mapDataST.drop_items);
    this->setDropShowItemsIDWithSplitString(m_mapDataST.drop_show);
//    //我方英雄初始化
    std::vector<string> mainCamp = Account::sharedAccount()->m_campST.m_mainCamp;
    std::vector<int> ourheroVector;
    
//    ourheroVector.push_back(1008);
//    ourheroVector.push_back(1002);
//    ourheroVector.push_back(1012);
//    ourheroVector.push_back(1015);
//    ourheroVector.push_back(1029);
//    ourheroVector.push_back(0);
    
    int sizev = (int)mainCamp.size();
    for (int i = 0; i < 6; i++) {
        if (i < sizev) {
            ourheroVector.push_back(atoi(mainCamp[i].c_str()));
        } else {
            ourheroVector.push_back(0);
        }
    }
//    //敌方英雄初始化
    std::vector<int> enamyHeroVector;
    enamyHeroVector.push_back(m_enamyDataST[0].ID);
    enamyHeroVector.push_back(m_enamyDataST[1].ID);
    enamyHeroVector.push_back(m_enamyDataST[2].ID);
    enamyHeroVector.push_back(m_enamyDataST[3].ID);
    enamyHeroVector.push_back(m_enamyDataST[4].ID);
    enamyHeroVector.push_back(0);
#else
    //我方英雄初始化
    std::vector<int> ourheroVector;
    ourheroVector.push_back(0);
    ourheroVector.push_back(0);
    ourheroVector.push_back(1008);
    ourheroVector.push_back(0);
    ourheroVector.push_back(0);
    ourheroVector.push_back(0);
    //敌方英雄初始化
    std::vector<int> enamyHeroVector;
    enamyHeroVector.push_back(1504);
    enamyHeroVector.push_back(0);
    enamyHeroVector.push_back(0);
    enamyHeroVector.push_back(0);
    enamyHeroVector.push_back(0);
    enamyHeroVector.push_back(0);
#endif
    this->initSpriteHero(ourheroVector, enamyHeroVector);
    this->setAllHeroButton();
    gameWarStart();
    
    
    if (Director::getInstance()->getScheduler()->isScheduled(schedule_selector(WarScenceLayer::warEndUpdataZoder), this)) {
        //刷新精灵z坐标,判断战斗是否结束,每0.5秒进行一次
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(WarScenceLayer::warEndUpdataZoder), this);
    }
    
    
    //刷新精灵z坐标,判断战斗是否结束,每0.5秒进行一次
    Director::getInstance()->getScheduler()->schedule(schedule_selector(WarScenceLayer::warUpdataZoder), this, 0.3f, false);

    
    
    //战斗倒计时时间显示
    Director::getInstance()->getScheduler()->schedule(schedule_selector(WarScenceLayer::showTimeUpdate), this, 1.0f, false);
    
    s_box2dWord = Box2dWordManger::sharedBox2dWordManger();

    
    // 创建一个事件监听器 OneByOne 为单点触摸
    auto listener1 = EventListenerTouchOneByOne::create();

    // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    listener1->onTouchBegan = CC_CALLBACK_2(WarScenceLayer::onTouchBegan, this);
    listener1->onTouchMoved = CC_CALLBACK_2(WarScenceLayer::onTouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(WarScenceLayer::onTouchEnded, this);
    listener1->onTouchEnded = CC_CALLBACK_2(WarScenceLayer::onTouchEnded, this);
    listener1->setSwallowTouches(true);
    // _eventDispatcher = director->getEventDispatcher();
    //由于Director是单例，所以_eventDispatcher
    // 获得的就相当于单例对象
    
    
    m_touchSprite = nullptr;
    m_touchAttackSprite = nullptr;
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    m_MoveToAction = cocostudio::Armature::create("tx_dianjizhou");
    m_MoveToAction->setVisible(false);

    this->addChild(m_MoveToAction);
    
    
    m_skillEAction = SkillEffectAction::createForScence(this);
    m_skillEAction->setVisible(false);
    m_skillEAction->setPosition(Point(kWidthWindow/2,kHeightWindow*3/5));
    this->addChild(m_skillEAction,kUILayercount+2);

//---------------显示地图格子
    //AStarMap6SideManger::sharedAStarMap6SideManger()->showTiledBox(this);
//--------------
    return true;
}
void WarScenceLayer::initWarEnemyData()
{
    s_box2dWord = Box2dWordManger::sharedBox2dWordManger();
    
    switch (m_warCount) {
        case 0:
        {
            this->setEnamyDataWithSplitString(m_mapDataST.checkpoint_monsters);
            this->setEnamyDropItemsDataWithSplitString(m_mapDataST.drop_items);
            this->setDropShowItemsIDWithSplitString(m_mapDataST.drop_show);
            std::string mappath = "map/" + m_mapBG[0];
            s_MapBG->setTexture(mappath);
        }
            break;
        case 1:
        {
            this->setEnamyDataWithSplitString(m_mapDataST.checkpoint_monsters2);
            this->setEnamyDropItemsDataWithSplitString(m_mapDataST.drop_items);
            this->setDropShowItemsIDWithSplitString(m_mapDataST.drop_show);
            std::string mappath = "map/" + m_mapBG[1];
            s_MapBG->setTexture(mappath);
        }
            break;
        case 2:
        {
            this->setEnamyDataWithSplitString(m_mapDataST.checkpoint_monsters3);
            this->setEnamyDropItemsDataWithSplitString(m_mapDataST.drop_items);
            this->setDropShowItemsIDWithSplitString(m_mapDataST.drop_show);
            std::string mappath = "map/" + m_mapBG[2];
            s_MapBG->setTexture(mappath);
        }
            break;
        default:
            break;
    }

    
    //先清空原来的敌人
    while(!m_enemyHeroVector.empty()) {
        BaseSprite* enemytmp = m_enemyHeroVector.back();
        m_enemyHeroVector.pop_back();
        this->removeChild(enemytmp,true);
    }
    
    //    //敌方英雄初始化
    std::vector<int> enamyHeroVector;
    enamyHeroVector.push_back(m_enamyDataST[0].ID);
    enamyHeroVector.push_back(m_enamyDataST[1].ID);
    enamyHeroVector.push_back(m_enamyDataST[2].ID);
    enamyHeroVector.push_back(m_enamyDataST[3].ID);
    enamyHeroVector.push_back(m_enamyDataST[4].ID);
    enamyHeroVector.push_back(0);
    
    
    this->initSpriteHeroNext(enamyHeroVector);
    this->nextWarStart();
}
void WarScenceLayer::initSpriteHeroNext(vector<int> &enamyHeroVect)
{
    ourSpCount = 0;
    enemyCount = 0;
    int countx = (int)m_ourHeroVector.size();
    for (int i = 0; i < countx; i++) {
        if (m_ourHeroVector[i]) {
            BaseSprite* m_ourHero1 = m_ourHeroVector[i];
            m_ourHero1->setPosition(m_ourStartPointVecotr[i]);
            ourSpCount++;
        }
    }
    
    
    int countt = (int)enamyHeroVect.size();
    for (int i = 0; i < countt; i++) {
        if (enamyHeroVect[i]) {
            //static BaseSprite* createWithID(int ID,WarLayerBase* warLayer,bool isFaceRight,int spLeve,int skillleve1,int skillleve2,int skillleve3,int skillleve4,int skillleve5,int skillleve6)
            BaseSprite* m_enemyHero1 = BaseSprite::createWithID(enamyHeroVect[i],this,false,1,1,1,1,1,1,1); //1011
            m_enemyHero1->setPosition(m_enemyStartPointVector[i]);
            this->addChild(m_enemyHero1);
            m_enemyHeroVector.push_back(m_enemyHero1);
            enemyCount++;
        }else{
            BaseSprite* m_enemyHero6 = nullptr;
            m_enemyHeroVector.push_back(m_enemyHero6);
        }
    }


}
void WarScenceLayer::nextWarStart()
{
    scheduleUpdate();
    m_warCount++;
    m_isWarEnd = false;
    m_isSetWarEnd = 0;
    //战斗开始，我方角色向上移动到屏1/4处。
    int count = (int)m_ourHeroVector.size();
    for (int i = 0; i < count; i++) {
        if (m_ourHeroVector[i] != nullptr) {
            m_ourHeroVector[i]->m_spaceNumber = i;
            m_ourHeroVector[i]->warStart();
        }
    }
    count = (int)m_ourSoliderVector.size();
    for (int i = 0; i < count; i++) {
        if (m_ourSoliderVector[i] != nullptr) {
            m_ourSoliderVector[i]->m_spaceNumber = i;
            m_ourSoliderVector[i]->warStart();
        }
    }
    count = (int)m_enemyHeroVector.size();
    for (int i = 0; i < count; i++) {
        if (m_enemyHeroVector[i] != nullptr) {
            m_enemyHeroVector[i]->m_spaceNumber = i;
            
            m_enemyHeroVector[i]->registerStateChangeEventListen(e_warDie, e_stateIn, this, event_callbackStr(WarScenceLayer::spriteDieEndCallBack));
            m_enemyHeroVector[i]->warStart();
        }
    }

    if (Director::getInstance()->getScheduler()->isScheduled(schedule_selector(WarScenceLayer::warEndUpdataZoder), this)) {
        //刷新精灵z坐标,判断战斗是否结束,每0.5秒进行一次
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(WarScenceLayer::warEndUpdataZoder), this);
    }
    //刷新精灵z坐标,判断战斗是否结束,每0.5秒进行一次
    Director::getInstance()->getScheduler()->schedule(schedule_selector(WarScenceLayer::warUpdataZoder), this, 0.3f, false);
    
    //战斗倒计时时间显示
    Director::getInstance()->getScheduler()->schedule(schedule_selector(WarScenceLayer::showTimeUpdate), this, 1.0f, false);
}
void WarScenceLayer::setSelectMoveToFlog(Point po)
{
    if (!m_MoveToAction->isVisible()) {
        m_MoveToAction->setVisible(true);
        m_MoveToAction->getAnimation()->play("play");
    }
    m_MoveToAction->setPosition(po);
    int pot = (int)((kHeightWindow - po.y)/kupDataJinDu);
    m_MoveToAction->setLocalZOrder(pot);
}
void WarScenceLayer::hideSelectMoveToFlog(BaseSprite* moveSp)
{
    if (m_touchSprite == moveSp) {
        m_MoveToAction->getAnimation()->stop();
        m_MoveToAction->setVisible(false);
        m_touchSprite = nullptr;
//        if (m_touchAttackSprite) {
//            m_touchAttackSprite->setShowAttackSelect(false);
//            m_touchAttackSprite = nullptr;
//        }
    }else{
        m_MoveToAction->getAnimation()->stop();
        m_MoveToAction->setVisible(false);
    }
}
void WarScenceLayer::setAllHeroButton()
{
    if (m_ourHeroVector[0]) {
        m_ourHeroVector[0]->hero1Layout = hero1Layout;
        m_ourHeroVector[0]->heroicon1 = heroicon1;
        m_ourHeroVector[0]->hero1StarVector[0] = hero1StarVector[0];
        m_ourHeroVector[0]->hero1StarVector[1] = hero1StarVector[1];
        m_ourHeroVector[0]->hero1StarVector[2] = hero1StarVector[2];
        m_ourHeroVector[0]->hero1StarVector[3] = hero1StarVector[3];
        m_ourHeroVector[0]->hero1StarVector[4] = hero1StarVector[4];
        m_ourHeroVector[0]->setSkillRealesButton(heroBtn1);
        m_ourHeroVector[0]->setHeroSkillAction(hero1skill);
        m_ourHeroVector[0]->initHeroIconButton();
    }
    if (m_ourHeroVector[1]) {
        m_ourHeroVector[1]->hero1Layout = hero2Layout;
        m_ourHeroVector[1]->heroicon1 = heroicon2;
        m_ourHeroVector[1]->hero1StarVector[0] = hero2StarVector[0];
        m_ourHeroVector[1]->hero1StarVector[1] = hero2StarVector[1];
        m_ourHeroVector[1]->hero1StarVector[2] = hero2StarVector[2];
        m_ourHeroVector[1]->hero1StarVector[3] = hero2StarVector[3];
        m_ourHeroVector[1]->hero1StarVector[4] = hero2StarVector[4];
        m_ourHeroVector[1]->setSkillRealesButton(heroBtn2);
        m_ourHeroVector[1]->setHeroSkillAction(hero2skill);
        m_ourHeroVector[1]->initHeroIconButton();
    }
    if (m_ourHeroVector[2]) {
        m_ourHeroVector[2]->hero1Layout = hero3Layout;
        m_ourHeroVector[2]->heroicon1 = heroicon3;
        m_ourHeroVector[2]->hero1StarVector[0] = hero3StarVector[0];
        m_ourHeroVector[2]->hero1StarVector[1] = hero3StarVector[1];
        m_ourHeroVector[2]->hero1StarVector[2] = hero3StarVector[2];
        m_ourHeroVector[2]->hero1StarVector[3] = hero3StarVector[3];
        m_ourHeroVector[2]->hero1StarVector[4] = hero3StarVector[4];
        m_ourHeroVector[2]->setSkillRealesButton(heroBtn3);
        m_ourHeroVector[2]->setHeroSkillAction(hero3skill);
        m_ourHeroVector[2]->initHeroIconButton();
    }
    if (m_ourHeroVector[3]) {
        m_ourHeroVector[3]->hero1Layout = hero4Layout;
        m_ourHeroVector[3]->heroicon1 = heroicon4;
        m_ourHeroVector[3]->hero1StarVector[0] = hero4StarVector[0];
        m_ourHeroVector[3]->hero1StarVector[1] = hero4StarVector[1];
        m_ourHeroVector[3]->hero1StarVector[2] = hero4StarVector[2];
        m_ourHeroVector[3]->hero1StarVector[3] = hero4StarVector[3];
        m_ourHeroVector[3]->hero1StarVector[4] = hero4StarVector[4];
        m_ourHeroVector[3]->setSkillRealesButton(heroBtn4);
        m_ourHeroVector[3]->setHeroSkillAction(hero4skill);
        m_ourHeroVector[3]->initHeroIconButton();
    }
    if (m_ourHeroVector[4]) {
        m_ourHeroVector[4]->hero1Layout = hero5Layout;
        m_ourHeroVector[4]->heroicon1 = heroicon5;
        m_ourHeroVector[4]->hero1StarVector[0] = hero5StarVector[0];
        m_ourHeroVector[4]->hero1StarVector[1] = hero5StarVector[1];
        m_ourHeroVector[4]->hero1StarVector[2] = hero5StarVector[2];
        m_ourHeroVector[4]->hero1StarVector[3] = hero5StarVector[3];
        m_ourHeroVector[4]->hero1StarVector[4] = hero5StarVector[4];
        m_ourHeroVector[4]->setSkillRealesButton(heroBtn5);
        m_ourHeroVector[4]->setHeroSkillAction(hero5skill);
        m_ourHeroVector[4]->initHeroIconButton();
    }
    
}
void WarScenceLayer::setEnamyDataWithSplitString(string &str)
{
    std::string tmpefid = str;
    std::vector<std::string> tmpx;
    StrSplit::split(tmpefid,";",tmpx);
    for (int i = 0; i < (int)tmpx.size(); i++) {
        std::string tmpt1 = tmpx[i];
        std::vector<std::string> tmpxx;
        StrSplit::split(tmpt1, ",", tmpxx);
        
        m_enamyDataST[atoi(tmpxx[5].c_str())-1].ID = atoi(tmpxx[0].c_str());
        m_enamyDataST[atoi(tmpxx[5].c_str())-1].type = atoi(tmpxx[1].c_str());
        m_enamyDataST[atoi(tmpxx[5].c_str())-1].pinzhi = atoi(tmpxx[2].c_str());
        m_enamyDataST[atoi(tmpxx[5].c_str())-1].star = atoi(tmpxx[3].c_str());
        m_enamyDataST[atoi(tmpxx[5].c_str())-1].leve = atoi(tmpxx[4].c_str());
        m_enamyDataST[atoi(tmpxx[5].c_str())-1].space = atoi(tmpxx[5].c_str());
    }
}
//设置副本怪物掉落
void WarScenceLayer::setEnamyDropItemsDataWithSplitString(string &str)
{
    std::string tmpefid = str;
    std::vector<std::string> tmpx = StrSplit::split(tmpefid, ";");
    
    int count = (int)tmpx.size();
    
    for (int i = 0; i < count; i++) {
        std::vector<std::string> tmpxx = StrSplit::split(tmpx[i], ",");;
        m_enamyDropItem[i].ID = atoi(tmpxx[0].c_str());
        m_enamyDropItem[i].count = atoi(tmpxx[1].c_str());
        m_enamyDropItem[i].gailv = atoi(tmpxx[2].c_str());
        m_enamyDropItem[i].dropCount = atoi(tmpxx[3].c_str());
    }
    this->addEnamyDropItem(count);
}
void WarScenceLayer::addEnamyDropItem(int c)
{
    for(int i = 0;i < c;i++)
    {
        m_enamyDropItemVector.push_back(m_enamyDropItem[i]);
    }
}
void WarScenceLayer::setDropShowItemsIDWithSplitString(string &str)
{
    std::string tmpefid = str;
    std::vector<std::string> tmpx;
    StrSplit::split(tmpefid,",",tmpx);
    for (int i = 0; i < (int)tmpx.size(); i++) {
        m_dropShowIDVector.push_back(atoi(tmpx[i].c_str()));
    }
}
void WarScenceLayer::initSpriteHero(vector<int> &ourHeroVect,vector<int> &enamyHeroVect)
{
    int count = (int)ourHeroVect.size();
    for (int i = 0; i < count; i++) {
        if (ourHeroVect[i]) {
            BaseSprite* m_ourHero1 = BaseSprite::createWithID(ourHeroVect[i],this,true,1,1,1,1,1,1,1);
            m_ourHero1->setPosition(m_ourStartPointVecotr[i]);
            this->addChild(m_ourHero1);
            string tmpstr = "hearhand" + to_string(i+1) + "_space";
            ui::Layout* layout1 = static_cast<ui::Layout*>(_layout->getChildByName(tmpstr));
            layout1->setVisible(false);
            //anger
            ui::LoadingBar* angerbar1 = static_cast<ui::LoadingBar*>(layout1->getChildByName("anger_bar"));
            //blood
            ui::LoadingBar* bloodbar1 = static_cast<ui::LoadingBar*>(layout1->getChildByName("blood_bar"));
            m_ourHero1->setBloodSliderUI(bloodbar1);
            m_ourHero1->setAngerSliderUI(angerbar1);
            layout1->setVisible(true);
            m_ourHeroVector.push_back(m_ourHero1);
            ourSpCount++;
        }else{
            BaseSprite* m_enemyHero6 = nullptr;
            m_ourHeroVector.push_back(m_enemyHero6);
        }
    }
    count = (int)enamyHeroVect.size();
    for (int i = 0; i < count; i++) {
        if (enamyHeroVect[i]) {
//static BaseSprite* createWithID(int ID,WarLayerBase* warLayer,bool isFaceRight,int spLeve,int skillleve1,int skillleve2,int skillleve3,int skillleve4,int skillleve5,int skillleve6)
            BaseSprite* m_enemyHero1 = BaseSprite::createWithID(enamyHeroVect[i],this,false,1,1,1,1,1,1,1); //1011
            m_enemyHero1->setPosition(m_enemyStartPointVector[i]);
            this->addChild(m_enemyHero1);
            m_enemyHeroVector.push_back(m_enemyHero1);
            enemyCount++;
        }else{
            BaseSprite* m_enemyHero6 = nullptr;
            m_enemyHeroVector.push_back(m_enemyHero6);
        }
    }
}
void WarScenceLayer::initSpriteSolider(vector<string> ourSoliderVect,vector<string> enamySoliderVect)
{
    
}

void WarScenceLayer::showTimeUpdate(float dt)
{
    s_time--;
    if (s_time >= 0) {
        s_timeText->setString(TimeUtil::secendToString_M_S(s_time));
    }else{
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(WarScenceLayer::showTimeUpdate), this);
        this->scenceBackToMainCity();
    }
    
  
}
vector<BaseSprite*> WarScenceLayer::getOurHeroVector()
{
    return this->m_ourHeroVector;
}
vector<BaseSprite*> WarScenceLayer::getOurSoliderVector()
{
    return this->m_ourSoliderVector;
}
vector<BaseSprite*> WarScenceLayer::getEnemyHeroVector()
{
    return this->m_enemyHeroVector;
}
vector<BaseSprite*> WarScenceLayer::getEnemySoliderVector()
{
    return this->m_enemySoliderVector;
}
//战斗结束地图切换时刷新地图英雄z坐标
void WarScenceLayer::warEndUpdataZoder(float dt)
{
    //角色
    int count = (int)m_ourHeroVector.size();
    for (int i = 0; i < count; i++) {
        if (m_ourHeroVector[i] != nullptr && (!m_ourHeroVector[i]->s_isDie)) {
            int pot = (int)((kHeightWindow - m_ourHeroVector[i]->getPosition().y)/kupDataJinDu);
            m_ourHeroVector[i]->setLocalZOrder(pot);
        }
    }
}
void WarScenceLayer::warUpdataZoder(float dt)//刷新地图中角色的z坐标
{
    //角色
    int count = (int)m_ourHeroVector.size();
    for (int i = 0; i < count; i++) {
        if (m_ourHeroVector[i] != nullptr && (!m_ourHeroVector[i]->s_isDie)) {
            int pot = (int)((kHeightWindow - m_ourHeroVector[i]->getPosition().y)/kupDataJinDu);
                m_ourHeroVector[i]->setLocalZOrder(pot);
        }
    }
    count = (int)m_ourSoliderVector.size();
    for (int i = 0; i < count; i++) {
        if (m_ourSoliderVector[i] != nullptr && (!m_ourSoliderVector[i]->s_isDie)) {
            int pot = (int)((kHeightWindow - m_ourSoliderVector[i]->getPosition().y)/kupDataJinDu);
            m_ourSoliderVector[i]->setLocalZOrder(pot);
        }
    }
    count = (int)m_enemyHeroVector.size();
    for (int i = 0; i < count; i++) {
        if (m_enemyHeroVector[i] != nullptr && (!m_enemyHeroVector[i]->s_isDie)) {
            int pot = (int)((kHeightWindow - m_enemyHeroVector[i]->getPosition().y)/kupDataJinDu);
            if (m_enemyHeroVector[i]->m_ID != 1506) {
                m_enemyHeroVector[i]->setLocalZOrder(pot);
            }
        }
    }
    count = (int)m_enemySoliderVector.size();
    for (int i = 0; i < count; i++) {
        if (m_enemySoliderVector[i] != nullptr && (!m_enemySoliderVector[i]->s_isDie)) {
            int pot = (int)((kHeightWindow - m_enemySoliderVector[i]->getPosition().y)/kupDataJinDu);
            m_enemySoliderVector[i]->setLocalZOrder(pot);
        }
    }

    //选择拖动线上的点
    if (!m_selectShowLine.empty()) {
        for (std::list<Sprite*>::iterator it = m_selectShowLine.begin(); it != m_selectShowLine.end() ; it++) {
            Sprite* tmps = (*it);
            int pot = (int)((kHeightWindow - tmps->getPosition().y)/kupDataJinDu);
            tmps->setLocalZOrder(pot);
        }
    }
    
    //子弹
    if (!m_bullet.empty()) {
        for (std::list<SkillBullet*>::iterator it = m_bullet.begin(); it != m_bullet.end() ; it++) {
            SkillBullet* tmps = (*it);
            int pot = (int)((kHeightWindow + 110 - tmps->getPosition().y)/kupDataJinDu);
            tmps->setLocalZOrder(pot);  //子弹要打在人身上，所以子弹层数要高,人物高度为135
        }
    }
}
//数据相关
void WarScenceLayer::loadnetData(string netConfig)     //载入地图网络数据
{
    
}
void WarScenceLayer::loadLocalData()
{
    
}

//交互
//Layer界面中的按钮被点击时运行的方法
void  WarScenceLayer::buttonHeroEvent(Ref *pSender, ui::Widget::TouchEventType   type)
{
    //ui::Button* buttontmp = dynamic_cast<ui::Button*>(pSender);
    
    switch (type)
	{
        case  ui::Widget::TouchEventType::BEGAN:
            //MessageBox("fgfggf", "dsdsss");
            break;
        case  ui::Widget::TouchEventType::MOVED:
            //MessageBox("fgfggf", "dsdsss");
            break;
            
        case  ui::Widget::TouchEventType::ENDED:
        {
            WarNetDataManger::sharedWarNetDataManger()->m_reopenWarLayer = false;
            this->scenceBackToMainCity();
            //界面按钮被点击的音效
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Click_Button.wav");
            break;
        }
            
        case  ui::Widget::TouchEventType::CANCELED:
            
            break;
            
        default:
            break;
	}
    
}
void WarScenceLayer::scenceBackToMainCity()
{
    Scene* sc = Scene::create();
    MainCityScence* scLayer = MainCityScence::create();
    sc->addChild(scLayer);
    Director::getInstance()->replaceScene(sc);
}
//战场添加战斗单位,战场添加好单位之后，要在本方法中增加精灵死亡事件监听。
void WarScenceLayer::addSpriteInWar(BaseSprite* sp,int zoder,int tag)
{
    
}
//某个精灵死亡时的回调方法,返回精灵名称，和精灵对象指针,战场可将目标移除
void WarScenceLayer::spriteDieCallBack(string name,Ref* sp)
{
    
}
//有子弹的单位攻击目标事件监听回调，在这个方法中战场进行子弹的初始化，并将子弹加入战场,即，有子弹的单位不直接攻击目标，而由战场创建的子弹对目标造成攻击
void WarScenceLayer::spriteAttackCallBack(string name,Ref* sp)
{
    
}


//游戏逻辑相关
void WarScenceLayer::gameWarStart()                     //战斗开始
{
    scheduleUpdate();
    m_warCount++;
    m_isWarEnd = false;
    m_isSetWarEnd = 0;
    //战斗开始，我方角色向上移动到屏1/4处。
    int count = (int)m_ourHeroVector.size();
    for (int i = 0; i < count; i++) {
        if (m_ourHeroVector[i] != nullptr) {
            m_ourHeroVector[i]->m_spaceNumber = i;
            m_ourHeroVector[i]->registerStateChangeEventListen(e_warDie, e_stateIn, this, event_callbackStr(WarScenceLayer::warSpriteDieCallBack));
            m_ourHeroVector[i]->warStart(true);
        }
    }
    count = (int)m_ourSoliderVector.size();
    for (int i = 0; i < count; i++) {
        if (m_ourSoliderVector[i] != nullptr) {
            m_ourSoliderVector[i]->m_spaceNumber = i;

            m_ourSoliderVector[i]->registerStateChangeEventListen(e_warDie, e_stateIn, this, event_callbackStr(WarScenceLayer::warSpriteDieCallBack));
            m_ourSoliderVector[i]->warStart(true);
        }
    }
    count = (int)m_enemyHeroVector.size();
    for (int i = 0; i < count; i++) {
        if (m_enemyHeroVector[i] != nullptr) {
            m_enemyHeroVector[i]->m_spaceNumber = i;

            m_enemyHeroVector[i]->registerStateChangeEventListen(e_warDie, e_stateIn, this, event_callbackStr(WarScenceLayer::spriteDieEndCallBack));
            m_enemyHeroVector[i]->warStart(true);
            m_isSetWarEnd++;//每有一个敌人，记一个数
        }
    }
    
    //音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/warBgmusic.mp3",true);
    
}
void WarScenceLayer::update(float dt)
{
    s_box2dWord->box2duUdate(dt);
}
void WarScenceLayer::gameWarEnd(bool isWin)                       //战斗结束
{
    unscheduleUpdate();
    this->hideSelectMoveToFlog();
    m_isWarEnd = true;
    m_isSetWarEnd = 0;
    
    if (m_warCount >= m_mapNumber || !isWin) { //战斗结束
        soundValue = 1.0f;
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(soundValue);
        Director::getInstance()->getScheduler()->schedule(schedule_selector(WarScenceLayer::backSoundEnd), this, 0.18f, false);
        
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(WarScenceLayer::warUpdataZoder), this);
        //战斗倒计时时间显示
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(WarScenceLayer::showTimeUpdate), this);
        
        Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
        if (isWin) {
            Director::getInstance()->getScheduler()->schedule(schedule_selector(WarScenceLayer::showWinLayer), this, 1.0f, false);
            
        }else{
            Director::getInstance()->getScheduler()->schedule(schedule_selector(WarScenceLayer::showLoseLayer), this, 1.0f, false);
        }
        b2Body* body = s_box2dWord->_world->GetBodyList();
        int count = s_box2dWord->_world->GetBodyCount();
        do{
            Box2dSprite* boxsp = (Box2dSprite*)body->GetUserData();
            if (boxsp->box2dSpriteType == kButtleBox2d) {
                boxsp->removeFromeWarScence();
                body->SetUserData(NULL);
            }
            count--;
        }while (count <=0);//删除子弹和技能
        
    }else{
       
        //刷新精灵z坐标,判断战斗是否结束,每0.5秒进行一次
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(WarScenceLayer::warUpdataZoder), this);
        //刷新精灵z坐标,判断战斗是否结束,每0.5秒进行一次
        Director::getInstance()->getScheduler()->schedule(schedule_selector(WarScenceLayer::warEndUpdataZoder), this, 0.3f, false);
        //战斗倒计时时间显示
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(WarScenceLayer::showTimeUpdate), this);
        m_touchSprite = nullptr;
        m_touchAttackSprite = nullptr;
        b2Body* body = s_box2dWord->_world->GetBodyList();
        int count = s_box2dWord->_world->GetBodyCount();
        
        if (body) {
            do{
                Box2dSprite* boxsp = (Box2dSprite*)body->GetUserData();
                if (boxsp && boxsp->box2dSpriteType == kButtleBox2d) {
                    boxsp->removeFromeWarScence();
                    body->SetUserData(NULL);
                }
                body = body->GetNext();
                count--;
            }while (count <=0);//删除子弹和技能
        }
        //所有友方英友向上走出地图
        s_box2dWord->destroyInstance();
        float moveTime = 0.0f;//最大移动时间。

        int herocount = (int)m_ourHeroVector.size();
        for (int i = 0; i < herocount; i++) {
            if (m_ourHeroVector[i]) {
                BaseSprite* tmpsp = m_ourHeroVector[i];
                int lenth = kHeightWindow - tmpsp->getPosition().y - 100;
                float tmptime = (float)(lenth/tmpsp->m_heroDataST.move_speed);
                if (moveTime < tmptime) {
                    moveTime = tmptime;
                }
                tmpsp->armature->setScale(1.0f);
                tmpsp->m_isCanChangeTarget = true;//技能播放结束，可以更改攻击目标
                tmpsp->isSkillRun = false;
                Point tmppox = Point(tmpsp->getPosition().x,kHeightWindow+100);
                tmpsp->stopAllActions();
                tmpsp->runAction(MoveTo::create(tmptime, tmppox));
                tmpsp->s_isMove = true;
                tmpsp->playRunActionWhenWarEnd();
            }
        }
        CallFunc* func = CallFunc::create(CC_CALLBACK_0(WarScenceLayer::initWarEnemyData,this));
        this->runAction(Sequence::create(DelayTime::create(moveTime+0.1f),func, NULL));
    }
}
void WarScenceLayer::backSoundEnd(float dt)
{
    if (soundValue > 0.0f) {
        soundValue -=0.2f;
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(soundValue);
    }else{
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
}
void WarScenceLayer::showWinLayer(float dt)
{
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(WarScenceLayer::showWinLayer),this);
    this->showWinLayer();
}
void WarScenceLayer::showLoseLayer(float dt)
{
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(WarScenceLayer::showLoseLayer),this);
    this->showLoseLayer();
}
void WarScenceLayer::showWinLayer()
{
    
    WinDialog* winl = WinDialog::create();
    this->addChild(winl,kUILayercount);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Battle_Win.mp3",false);
}
void WarScenceLayer::showLoseLayer()
{
    LossDialog* lossl = LossDialog::create();
    this->addChild(lossl,kUILayercount);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Battle_Lose.mp3",false);
}
void WarScenceLayer::warEndGetReward()                  //战斗结束获得奖励
{
    
}
//精灵进入战斗状态完成时的注册回调
void WarScenceLayer::someSpriteWarStartMoveEnd(std::string name,cocos2d::Ref* sp)
{
//    BaseSprite* tmpSp = dynamic_cast<BaseSprite*>(sp);
//    tmpSp->warFindEnemy(m_enemyHeroVector, m_ourHeroVector);
}
//战斗相关
//敌人进入警戒状态时的回调
void WarScenceLayer::CallBackWarStartForEnemy(string name,Ref* sp)
{
//    BaseSprite* tmpSp = dynamic_cast<BaseSprite*>(sp);
//    //通知敌人，我方所有角色对象,这时由敌人定时刷新查找进入攻击范围的友方目标
//    tmpSp->warWaitInToAttackRange(this);
}
//监听精灵死亡事件,当有精灵死亡时，会得到通知
void WarScenceLayer::warSpriteDieCallBack(std::string name,cocos2d::Ref* sp)
{
    BaseSprite* sprite = dynamic_cast<BaseSprite*>(sp);
    
    switch (sprite->s_spriteSpaceType) {
        case e_OurHero://亡的是我方英雄
            m_ourHeroVector[sprite->m_spaceNumber] = nullptr;
            ourSpCount--;
            break;
        case e_EnemyHero://亡的是敌方英雄
            m_enemyHeroVector[sprite->m_spaceNumber] = nullptr;
            enemyCount--;
            break;
        case e_EnemySolider://亡的是我方小兵
            m_enemySoliderVector[sprite->m_spaceNumber] = nullptr;
            break;
        case e_OurSolider://亡的是我方小兵
            m_ourSoliderVector[sprite->m_spaceNumber] = nullptr;
            break;
        default:
            break;
    }
    
    if (ourSpCount == 0 ) {
        this->gameWarEnd(false);
    }
}
//某个敌方精灵死亡动画结束时的回调方法，在这里设置一个奖励物品
void WarScenceLayer::spriteDieEndCallBack(string name,Ref* sp)
{
    BaseSprite* sprite = dynamic_cast<BaseSprite*>(sp);
    
    switch (sprite->s_spriteSpaceType) {
        case e_EnemyHero:
            m_enemyHeroVector[sprite->m_spaceNumber] = nullptr;
            if (ourSpCount) {
                enemyCount--;
            }
            enemyHeroDieShowBox(sprite->getPosition(),sprite->m_spaceNumber);
            break;
        case e_EnemySolider:
            m_enemySoliderVector[sprite->m_spaceNumber] = nullptr;
            enemySoliderDieShowBox(sprite->getPosition(),sprite->m_spaceNumber);
            break;
        default:
            break;
    }
    
}

//显示奖励动画,参数为敌人死亡时坐标，从这里创建一个宝箱
void WarScenceLayer::enemyHeroDieShowBox(Point po,int spaceNumber)//英雄死亡
{
    if (ourSpCount > 0 && enemyCount == 0) {
        m_isWarEnd = true;
    }
    //m_isSetWarEnd++;
    
    Sprite* box = Sprite::createWithSpriteFrameName("box.png");
    box->setPosition(po);
    this->addChild(box,kBoxLayerCount);
    Point targetPo = s_box->getPosition();
    targetPo.subtract(po);
    float moveTime = targetPo.length()/kRewardMoveSpeed; //宝箱移动时间

    MoveTo* easeInout = MoveTo::create(moveTime, s_box->getPosition());
    CallFuncN* funcn = CallFuncN::create([this](cocos2d::Ref* sp)->void{
        Sprite* spx = dynamic_cast<Sprite*>(sp);
        spx->removeFromParent();
        this->s_boxNumber++;
        this->s_textBoxCount->setString(to_string(this->s_boxNumber));
        if (m_isSetWarEnd > 0) {
            m_isSetWarEnd--;
        }
        
        if (m_isSetWarEnd == 0 && ourSpCount > 0 && enemyCount == 0) {
            this->gameWarEnd(true);
        }
    });
    box->runAction(Sequence::create(easeInout,funcn,NULL));
    
//    MoveTo* moveto = MoveTo::create(;, ;)
}
void WarScenceLayer::enemySoliderDieShowBox(Point po,int spaceNumber)//小兵死亡
{
    
}


//战场创建子弹，并开始移动，到达目标后对目标造成伤害,
void WarScenceLayer::bulletCreatAndAttack(BaseSprite* fromSp,BaseSprite* toSp)
{
    
}


//网络交互
void WarScenceLayer::netWarEnd(bool isWin)              //向服务器发送战斗结束信息
{
    
}
void WarScenceLayer::netCallBackWarEnd(string json)     //服务器返回战斗结束奖励
{
    
}

void WarScenceLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    
//    cocos2d::Layer::draw(renderer, transform, flags);
//    
//    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
//    
//    kmGLPushMatrix();
//    
//    Box2dWordManger::sharedBox2dWordManger()->_world->DrawDebugData();//这个是一定要写的 其他几句不知道啥意思 看别人代码抄的
//    
//    kmGLPopMatrix();
//    
//    CHECK_GL_ERROR_DEBUG();
}
void WarScenceLayer::onExit()
{
    this->unscheduleUpdate();
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    Box2dWordManger::sharedBox2dWordManger()->destroyInstance();
    Layer::onExit();
}
void WarScenceLayer::onEnter()
{
    Layer::onEnter();
}
//释放技能时添加黑色背景
void WarScenceLayer::showMaskLayer()
{
    //s_pausm = Director::getInstance()->getScheduler()->pauseAllTargets();
    
    this->pauseAllSprite();
    this->pause();
    
    //if (showMaskCount == 0) {
        s_skillMaskBG->setVisible(true);
   // }

    //showMaskCount++;
    
}
void WarScenceLayer::hideMaskLayer()
{
    //showMaskCount--;
    //if (showMaskCount == 0) {
        s_skillMaskBG->setVisible(false);
    //}
    this->resumeAllSprite();
    this->resume();
    //Director::getInstance()->getScheduler()->resumeTargets(s_pausm);
}
////暂停所有角色，释放技能
void WarScenceLayer::whenRunSkillStopMoveAction()//当技能运行时停止移动动画
{
    if (m_MoveToAction->isVisible()) {
        m_MoveToAction->getAnimation()->stop();
        m_MoveToAction->setVisible(false);
    }
    m_touchSprite = nullptr;
    if (m_touchAttackSprite) {
        m_touchAttackSprite = nullptr;
    }

}
void WarScenceLayer::pauseAllSprite()
{
    vector<BaseSprite*> ourheroVet = this->getOurHeroVector();
    int count = (int)ourheroVet.size();
    for (int i = 0; i < count; i++) {
        if (ourheroVet[i]) {
            //Director::getInstance()->getScheduler()->pauseTarget(ourheroVet[i]);
            ourheroVet[i]->armature->pause();
            //ourheroVet[i]->armature->getAnimation()->pause();
            ourheroVet[i]->pause();
            
        }
    }
    vector<BaseSprite*> oursolider = this->getOurSoliderVector();
    count = (int)oursolider.size();
    for (int i = 0; i < count; i++) {
        if (oursolider[i]) {
            //Director::getInstance()->getScheduler()->pauseTarget(oursolider[i]);
            oursolider[i]->armature->pause();
            //oursolider[i]->armature->getAnimation()->pause();
            oursolider[i]->pause();
        }
    }
    vector<BaseSprite*> enemyVet = this->getEnemyHeroVector();
    count = (int)enemyVet.size();
    for (int i = 0; i < count; i++) {
        if (enemyVet[i]) {
            //Director::getInstance()->getScheduler()->pauseTarget(enemyVet[i]);
            enemyVet[i]->armature->pause();
            //enemyVet[i]->armature->getAnimation()->pause();
            enemyVet[i]->pause();
        }
    }
    vector<BaseSprite*> enemysoliderVet = this->getEnemySoliderVector();
    count = (int)enemysoliderVet.size();
    for (int i = 0; i < count; i++) {
        if (enemysoliderVet[i]) {
            //Director::getInstance()->getScheduler()->pauseTarget(enemysoliderVet[i]);
            enemysoliderVet[i]->armature->pause();
            //enemysoliderVet[i]->armature->getAnimation()->pause();
            enemysoliderVet[i]->pause();
        }
    }
}
void WarScenceLayer::resumeAllSprite()
{
    vector<BaseSprite*> ourheroVet = this->getOurHeroVector();
    int count = (int)ourheroVet.size();
    for (int i = 0; i < count; i++) {
        if (ourheroVet[i]) {
            ourheroVet[i]->resume();
            ourheroVet[i]->armature->resume();
            //Director::getInstance()->getScheduler()->resumeTarget(ourheroVet[i]);
        }
    }
    vector<BaseSprite*> oursolider = this->getOurSoliderVector();
    count = (int)oursolider.size();
    for (int i = 0; i < count; i++) {
        if (oursolider[i]) {
            oursolider[i]->resume();
            oursolider[i]->armature->resume();
            //Director::getInstance()->getScheduler()->resumeTarget(oursolider[i]);
        }
    }
    vector<BaseSprite*> enemyVet = this->getEnemyHeroVector();
    count = (int)enemyVet.size();
    for (int i = 0; i < count; i++) {
        if (enemyVet[i]) {
            enemyVet[i]->resume();
            if (!enemyVet[i]->isSkillPaused) {
                enemyVet[i]->armature->resume();
            }
            //Director::getInstance()->getScheduler()->resumeTarget(enemyVet[i]);
        }
    }
    vector<BaseSprite*> enemysoliderVet = this->getEnemySoliderVector();
    count = (int)enemysoliderVet.size();
    for (int i = 0; i < count; i++) {
        if (enemysoliderVet[i]) {
            enemysoliderVet[i]->resume();
            enemysoliderVet[i]->armature->resume();
             //Director::getInstance()->getScheduler()->resumeTarget(enemysoliderVet[i]);
        }
    }
}
bool WarScenceLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    if (m_isWarEnd) {
        return false;
    }
    
   Point touchpo = touch->getLocation();
    std::vector<BaseSprite*> ourherovector =  this->getOurHeroVector();
    m_tmpPoint = touchpo;
    BaseSprite* touchSp = nullptr;
    float lenth = 1000.0f;
    int count = (int)ourherovector.size();
    for (int i = 0; i < count; i++) {
        if (ourherovector[i]){
            Rect tmp = ourherovector[i]->getBoundingBox();
            tmp.origin.add(Point(-135.0f/2.0f,0.0f));
            tmp.size = Size(135,135);
            if (tmp.containsPoint(touchpo)) {
                if (touchSp) {
                    Point potmp = ourherovector[i]->getPosition();
                    potmp.subtract(touchpo);
                    
                    float tmplen = potmp.length();
                    if (tmplen < lenth) {
                        touchSp = ourherovector[i];
                    }else{
                        continue;
                    }
                    
                }else{
                    Point potmp = ourherovector[i]->getPosition();
                    potmp.subtract(touchpo);
                    lenth = potmp.length();
                    touchSp = ourherovector[i];
                }
            }
        }
    }

    std::vector<BaseSprite*> enemyvector =  this->getEnemyHeroVector();
    BaseSprite* touchSpEnemy = nullptr;
    lenth = 1000.0f;
    count = (int)enemyvector.size();
    for (int i = 0; i < count; i++) {
        if (enemyvector[i]){
            Rect tmp = enemyvector[i]->getBoundingBox();
            //ourherovector[i]->armature->getBoundingBox().containsPoint(touchpo);
            tmp.origin.add(Point(-135.0f/2.0f,0.0f));
            tmp.size = Size(135,135);
            if (tmp.containsPoint(touchpo)) {
                if (touchSpEnemy) {
                    Point potmp = enemyvector[i]->getPosition();
                    potmp.subtract(touchpo);
                    
                    float tmplen = potmp.length();
                    if (tmplen < lenth) {
                        touchSpEnemy = enemyvector[i];
                    }else{
                        continue;
                    }
                    
                }else{
                    Point potmp = enemyvector[i]->getPosition();
                    potmp.subtract(touchpo);
                    lenth = potmp.length();
                    touchSpEnemy = enemyvector[i];
                }
            }
        }
    }
    
    if (touchSpEnemy && touchSp) {
        Point potmpe = touchSpEnemy->getPosition();
        Point potmpo = touchSp->getPosition();
        potmpe.subtract(touchpo);
        float lenEnemy = potmpe.length();
        potmpo.subtract(touchpo);
        float lenOur = potmpo.length();
        if (lenEnemy >= lenOur) {
            touchSpEnemy = nullptr;
        }else{
            touchSp = nullptr;
        }
    }

    
    if (touchSp) {
        
        if (touchSp == m_touchSprite) {
            //
            m_touchSprite->setShowSelectMove(true);
            return true;
        }else{
            if (m_touchSprite) {
                m_touchSprite->setShowSelectMove(false);
                m_touchSprite = touchSp;
                m_touchSprite->setShowSelectMove(true);
                this->hideSelectMoveToFlog();
                return true;
            }else{
                m_touchSprite = touchSp;
                m_touchSprite->setShowSelectMove(true);
                return true;
            }
        }
        
        
    }else if(touchSpEnemy){

        if (m_touchSprite) {
            m_touchAttackSprite = touchSpEnemy;
            m_touchAttackSprite->setShowAttackSelect(true);
            m_touchSprite->touchMoveToSprite(touchSpEnemy);
        }
    }else{

        if (m_touchSprite) {
            this->setSelectMoveToFlog(touchpo);
            m_touchSprite->touchMoveToPosition(touchpo);
        }else if(m_touchAttackSprite){
            m_touchAttackSprite->setShowAttackSelect(false);
            m_touchAttackSprite = nullptr;
        }
    }

    return false;
    
}
void WarScenceLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    
    Point touchpo = touch->getLocation();
    
    Point xtm = touchpo;
    xtm.subtract(m_tmpPoint);
    if (xtm.length() < 10) {
        return;
    }
    m_tmpPoint = touchpo;
    std::vector<BaseSprite*> enemyvector =  this->getEnemyHeroVector();
    BaseSprite* touchSp = nullptr;
    float lenth = 1000.0f;
    int count = (int)enemyvector.size();
    for (int i = 0; i < count; i++) {
        if (enemyvector[i]){
            Rect tmp = enemyvector[i]->getBoundingBox();
            //ourherovector[i]->armature->getBoundingBox().containsPoint(touchpo);
            tmp.origin.add(Point(-135.0f/2.0f,0.0f));
            tmp.size = Size(135,135);
            if (tmp.containsPoint(touchpo)) {
                if (touchSp) {
                    Point potmp = enemyvector[i]->getPosition();
                    potmp.subtract(touchpo);
                    
                    float tmplen = potmp.length();
                    if (tmplen < lenth) {
                        touchSp = enemyvector[i];
                    }else{
                        continue;
                    }
                    
                }else{
                    Point potmp = enemyvector[i]->getPosition();
                    potmp.subtract(touchpo);
                    lenth = potmp.length();
                    touchSp = enemyvector[i];
                }
            }
        }
    }
    
    if (touchSp && m_touchSprite) {

        this->hideSelectMoveToFlog();
        if(m_touchAttackSprite && touchSp != m_touchAttackSprite){
            m_touchAttackSprite->setShowAttackSelect(false);
            m_touchAttackSprite = touchSp;
            touchSp->setShowAttackSelect(true);
        }else if(!m_touchAttackSprite){
            m_touchAttackSprite = touchSp;
            touchSp->setShowAttackSelect(true);
        }
        this->showSelectLine(m_touchSprite->getPosition(),touchpo);
        
    }else if(m_touchSprite){
        this->setSelectMoveToFlog(touchpo);
        if (m_touchAttackSprite) {
            m_touchAttackSprite->setShowAttackSelect(false);
            m_touchAttackSprite = nullptr;
        }
        this->showSelectLine(m_touchSprite->getPosition(),touchpo);
    }
    
}
void WarScenceLayer::showSelectLine(Point fromPo,Point toPo)
{
    Point tmp = toPo;
    tmp.subtract(fromPo);
    float lenth = tmp.length();  //得到失量常度
    Point normalPoint = tmp.getNormalized(); //得到单位向量
    int count = (int)(lenth/30.0f);
    int sizecount = (int)m_selectShowLine.size();
    
    if (m_selectShowLine.empty()) {
        for (int i = 0; i < count; i++) {
            Sprite* stmp = Sprite::createWithSpriteFrameName("war_roaddian.png");
            Point totmpo = normalPoint*(30*i);
            totmpo.add(fromPo);
            stmp->setPosition(totmpo);
            this->addChild(stmp);
            m_selectShowLine.push_back(stmp);
        }
    }else if(sizecount > count){
        int bigcount = sizecount - count;
        do{
            Sprite* tmps = m_selectShowLine.back();
            this->removeChild(tmps,true);
            m_selectShowLine.pop_back();
        }while (bigcount == (int)m_selectShowLine.size());
    }else if(sizecount == count)
    {
        int i = 0;
        std::list<Sprite*> tmplist;
        do{
            Sprite* tmpp = m_selectShowLine.front();
            m_selectShowLine.pop_front();
            Point totmpo = normalPoint*(30*i);
            totmpo.add(fromPo);
            tmpp->setPosition(totmpo);
            tmplist.push_back(tmpp);
            i++;
        }while (!m_selectShowLine.empty());
        m_selectShowLine = tmplist;
    }else if(sizecount < count)
    {
        int i = 0;
        std::list<Sprite*> tmplist;
        do{
            Sprite* tmpp = m_selectShowLine.front();
            Point totmpo = normalPoint*(30*i);
            totmpo.add(fromPo);
            i++;
            tmpp->setPosition(totmpo);
            tmplist.push_back(tmpp);
            m_selectShowLine.pop_front();
        }while (!m_selectShowLine.empty());
        m_selectShowLine = tmplist;
        
        //
        for (int i = sizecount; i < count; i++) {
            Sprite* tmpx = Sprite::createWithSpriteFrameName("war_roaddian.png");
            Point totmpo = normalPoint*(30*i);
            totmpo.add(fromPo);
            tmpx->setPosition(totmpo);
            this->addChild(tmpx);
            m_selectShowLine.push_back(tmpx);
        }
        
        
    }
}
void WarScenceLayer::hideShowSelectLine()
{
   while (!m_selectShowLine.empty())
    {
        Sprite* deltmp = m_selectShowLine.front();
        this->removeChild(deltmp,true);
        m_selectShowLine.pop_front();
    };
}
void WarScenceLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    
    this->hideShowSelectLine();
    if(m_touchAttackSprite){
        m_touchAttackSprite->setShowAttackSelect(false);
        m_touchAttackSprite = nullptr;
    }
    
    Point touchpo = touch->getLocation();
    log("touch point = (%f,%f)",touchpo.x,touchpo.y);
    std::vector<BaseSprite*> enemyvector =  this->getEnemyHeroVector();
    
    BaseSprite* touchSp = nullptr;
    float lenth = 1000.0f;
    int count = (int)enemyvector.size();
    for (int i = 0; i < count; i++) {
        if (enemyvector[i]){
            Rect tmp = enemyvector[i]->getBoundingBox();
            //ourherovector[i]->armature->getBoundingBox().containsPoint(touchpo);
            tmp.origin.add(Point(-135.0f/2.0f,0.0f));
            tmp.size = Size(135,135);
            if (tmp.containsPoint(touchpo)) {
                if (touchSp) {
                    Point potmp = enemyvector[i]->getPosition();
                    potmp.subtract(touchpo);
                    
                    float tmplen = potmp.length();
                    if (tmplen < lenth) {
                        touchSp = enemyvector[i];
                    }else{
                        continue;
                    }
                    
                }else{
                    Point potmp = enemyvector[i]->getPosition();
                    potmp.subtract(touchpo);
                    lenth = potmp.length();
                    touchSp = enemyvector[i];
                }
            }
        }
    }
    
    if (touchSp) {
        m_touchAttackSprite = touchSp;
    }else{
        if (m_touchAttackSprite) {
            m_touchAttackSprite->setShowAttackSelect(false);
            m_touchAttackSprite = nullptr;
        }
        m_touchMovePoint = touchpo;

    }
    if (m_touchSprite) {
        Point tmpt = m_touchSprite->getPosition();
        tmpt.add(Vec2(0,135/2.0f));
        tmpt.subtract(m_touchMovePoint);
        if (tmpt.length() >= 80) {
            if (m_touchAttackSprite) {
                m_touchAttackSprite->setShowAttackSelect(true);
                m_touchSprite->touchMoveToSprite(m_touchAttackSprite);
                
               // m_touchSprite->setShowSelectMove(false);
               // m_touchSprite = nullptr;
            }else{
                this->setSelectMoveToFlog(m_touchMovePoint);
                m_touchSprite->touchMoveToPosition(m_touchMovePoint);
               // m_touchSprite->setShowSelectMove(false);
               // m_touchSprite = nullptr;
            }
        }
    }
    //m_touchAttackSprite = nullptr;
}
void WarScenceLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{
    
}
//播放技能动画
void WarScenceLayer::showSkillRunForHero(BaseSprite* runSkillSp)
{
    this->showMaskLayer();
    m_skillEAction->setVisible(true);
    m_skillEAction->playSkillWithHero(runSkillSp);
}
void WarScenceLayer::addWarBullte(SkillBullet* bullet)
{
    this->addChild(bullet);
    m_bullet.push_back(bullet);
}
//将一颗子弹从战场移除
void WarScenceLayer::removeWarBullet(SkillBullet* bullet)
{
    for (std::list<SkillBullet*>::iterator it = m_bullet.begin(); it != m_bullet.end(); it ++ ) {
        if ((*it) == bullet) {
            m_bullet.erase(it);
            break;
        }
    }
    bullet->removeFromParent();
}
