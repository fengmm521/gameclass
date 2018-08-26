#include "WinDialog.h"
#include "MainCityScence.h"
#include "WarNetDataManger.h"
#include "BaseSprite.h"
using namespace cocos2d;
using namespace cocos2d::ui;

#define kGoodBoxMaxNumber 10

WinDialog::WinDialog()
{

}
WinDialog::~WinDialog()
{
    
}

void WinDialog::onExit()
{
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    Layer::onExit();
}
void WinDialog::onEnter()
{
    Layer::onEnter();
}
bool WinDialog::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    do
    {
        m_pNode = GUIReader::getInstance()->widgetFromJsonFile("ui/winLoss/winLoss_1.ExportJson");
        //m_pNode->setTouchEnabled(true);
        
        
        Button  *button_go = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "button_go"));
        if (!button_go){ return false; }
        button_go->addTouchEventListener(CC_CALLBACK_2(WinDialog::button_goEvent, this));
        
        Button  *button_back = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "button_back"));
        if (!button_back){ return false; }
        button_back->addTouchEventListener(CC_CALLBACK_2(WinDialog::button_backEvent, this));
        
        
        auto tmpWidget = static_cast<ImageView*>(m_pNode->getChildByName("fixed"));
        
        s_winIconBG = static_cast<ImageView*>(Helper::seekWidgetByName(tmpWidget, "Image_34"));
        s_winIconBG->setVisible(false);
        
        s_winIcon = static_cast<ImageView*>(Helper::seekWidgetByName(tmpWidget, "Image_5"));
        s_winIcon->setVisible(false);
        
        s_winText = static_cast<ImageView*>(Helper::seekWidgetByName(tmpWidget, "Image_6"));
        s_winText->setVisible(false);
        
        s_star1 = static_cast<ImageView*>(Helper::seekWidgetByName(tmpWidget, "Image_star1"));
        s_star1->setVisible(false);
        
        s_star2 = static_cast<ImageView*>(Helper::seekWidgetByName(tmpWidget, "Image_star2"));
        s_star2->setVisible(false);
        
        s_star3 = static_cast<ImageView*>(Helper::seekWidgetByName(tmpWidget, "Image_star3"));
        s_star3->setVisible(false);
        
        s_boxIcon = static_cast<ImageView*>(Helper::seekWidgetByName(tmpWidget, "Image_box"));
        s_boxIcon->setVisible(false);
        
        s_goldIcon = static_cast<ImageView*>(Helper::seekWidgetByName(tmpWidget,"Image_gold"));
        s_goldIcon->setVisible(false);
        
        s_boxLabel = static_cast<Text*>(m_pNode->getChildByName("label_chest"));
        s_boxLabel->setString("0");
        s_boxLabel->setVisible(false);
        
        s_goldNumberLabel = static_cast<Text*>(m_pNode->getChildByName("label_gold"));
        s_goldNumberLabel->setString("0");
        s_goldNumberLabel->setVisible(false);
        
        s_getGoodIDlist = WarNetDataManger::sharedWarNetDataManger()->getWarWinGood();
        
        s_boxNumber = (int)s_getGoodIDlist.size();
        
        s_goldNumber = WarNetDataManger::sharedWarNetDataManger()->getWarWinGold();
        
        for (int i = 0; i < kGoodBoxMaxNumber; i++) {
            std::string tmpstr = "image_res" + to_string(i);
            ImageView* tmpboxview = static_cast<ImageView*>(m_pNode->getChildByName(tmpstr));
            s_goodBoxVector.push_back(tmpboxview);
        }
        
        for (int i = 0; i < kUserHeroNumber; i++) {
            std::string tmpstr = "image_hero" + to_string(i+1);
            s_heroBoxArr[i] = static_cast<ImageView*>(m_pNode->getChildByName(tmpstr));
            s_heroBoxArr[i]->setVisible(false);
        }
        
        
        int exptmp = WarNetDataManger::sharedWarNetDataManger()->getWarWinExp();
        for (int i = 0; i < kUserHeroNumber;i++) {
            s_winGetExp[i] = exptmp;
        }
        
        for (int i = 0 ; i < kUserHeroNumber; i++) {
            WarHeroData datanull;
            datanull.heroID = 0;
            s_warHeroArr[i] = datanull;
        }

        std::vector<WarHeroData> datatmp = WarNetDataManger::sharedWarNetDataManger()->getWarHeroArr();
        int herocount = (int)datatmp.size();
        for (int i = 0; i < herocount; i++) {
            s_warHeroArr[i] = datatmp[i];
        }
        
        
        for (int i = 0; i < kUserHeroNumber; i++) {
            if (s_warHeroArr[i].heroID > 100) {
                ImageView* tmpview = s_heroBoxArr[i];
                
                ImageView* heroIcon = static_cast<ImageView*>(Helper::seekWidgetByName(tmpview, "head_image"));
                Configtab_card_attribute_sysDataST heroData = LocalDataManger::sharedLocalDataManger()->getConfigtab_card_attribute_sysDataST(s_warHeroArr[i].heroID);//s_warHeroArr[i].heroID;
                
                heroIcon->loadTexture(heroData.hero_icon,TextureResType::PLIST);
                heroIcon->setVisible(true);
                tmpview->setVisible(true);
                loadbar[i] = static_cast<LoadingBar*>(Helper::seekWidgetByName(tmpview, "ProgressBar_experience"));
                loadbar[i]->setPercent(0);
                
            }
        }
        
        
        this->addChild(m_pNode);
        
        isActionEnd = false;
        
        this->showWinActionStart();
        
    }while(0);
    return true;
}
void  WinDialog::button_goEvent(Ref *pSender, Widget::TouchEventType   type)
{
	switch (type)
	{
	case  Widget::TouchEventType::BEGAN:
		{
            
        }
		break;
	case  Widget::TouchEventType::MOVED:
        {
            
        }
		break;

	case  Widget::TouchEventType::ENDED:
        {
            WarNetDataManger::sharedWarNetDataManger()->m_reopenWarLayer = true;
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Click_Button.wav");
            MainCityScence* mainl = MainCityScence::create();
            cocos2d::Scene* sc = cocos2d::Scene::create();
            sc->addChild(mainl);
            Director::getInstance()->replaceScene(sc);
        }
		break;

	case  Widget::TouchEventType::CANCELED:
        {
            
        }
		break;

	default:
		break;
	}
}

void  WinDialog::button_backEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case  Widget::TouchEventType::BEGAN:
        {
            
        }
		break;
	case  Widget::TouchEventType::MOVED:
        {
            
        }
		break;

	case  Widget::TouchEventType::ENDED:
        {
            WarNetDataManger::sharedWarNetDataManger()->m_reopenWarLayer = true;
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Click_Button.wav");
            MainCityScence* mainl = MainCityScence::create();
            cocos2d::Scene* sc = cocos2d::Scene::create();
            sc->addChild(mainl);
            Director::getInstance()->replaceScene(sc);
        }
		break;

	case  Widget::TouchEventType::CANCELED:
        {
            
        }
		break;
	default:
		break;
	}
}

void WinDialog::showWinActionStart()//开始播放动画
{
    s_winIconBG->setVisible(true);
    s_winIconBG->runAction(RepeatForever::create(RotateBy::create(5.0f, 360)));
    
    s_winIcon->setScale(3.0f);
    s_winIcon->runAction(Sequence::create(Show::create(),ScaleTo::create(0.5f, 1.0f), NULL));
    
    s_winText->setScale(3.0f);
    s_winText->runAction(Sequence::create(DelayTime::create(0.6f),Show::create(),ScaleTo::create(0.5f, 1.0f), NULL));
    
    Director::getInstance()->getScheduler()->schedule(schedule_selector(WinDialog::onWinIconSetEnd), this, 1.2f, false);
    
}
void WinDialog::onWinIconSetEnd(float dt) //胜利图标动画播放结束事件
{
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(WinDialog::onWinIconSetEnd), this);
    
    
    
    s_star1->setScale(5.0f);
    s_star1->setVisible(true);
    
    CallFunc* functmp = CallFunc::create(CC_CALLBACK_0(WinDialog::onStarSetEnd,this));
    s_star1->runAction(Sequence::create(ScaleTo::create(0.2f, 1.0f), NULL));
    
    s_star2->setScale(3.0f);
    s_star2->runAction(Sequence::create(DelayTime::create(0.3f),Show::create(),ScaleTo::create(0.2f, 1.0f), NULL));
    
    s_star3->setScale(5.0f);
    s_star3->runAction(Sequence::create(DelayTime::create(0.6f),Show::create(),ScaleTo::create(0.2f, 1.0f),DelayTime::create(0.2f),functmp,NULL));
    
}

void WinDialog::onStarSetEnd()    //星星动画播放结束事件
{
    s_boxIcon->setVisible(true);
    s_boxIcon->runAction(Sequence::create(RotateBy::create(0.02f, -30),RotateBy::create(0.02f, 60),RotateBy::create(0.02f, -30), NULL));
    s_boxLabel->setVisible(true);
    this->setBoxNumberWithAction();
    
    s_goldIcon->setVisible(true);
    s_goldIcon->runAction(Sequence::create(RotateBy::create(0.02f, -30),RotateBy::create(0.04f, 60),RotateBy::create(0.02f, -30), NULL));
    s_goldNumberLabel->setVisible(true);
    this->setGoleNumberWithAction();
    
    this->setWinGoodWithAction();
    
}

void WinDialog::setBoxNumberWithAction()
{
    s_boxtmpNumber = 0;
    Director::getInstance()->getScheduler()->schedule(schedule_selector(WinDialog::setBoxNumber), this, 0.1f, false);
}

void WinDialog::setBoxNumber(float dt)
{
    s_boxtmpNumber++;
    if (s_boxtmpNumber >= s_boxNumber) {
        s_boxLabel->setString(to_string(s_boxNumber));
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(WinDialog::setBoxNumber), this);
        this->onSetBoxNumberEnd();
    }else{
        s_boxLabel->setString(to_string(s_boxtmpNumber));
    }
}

void WinDialog::onSetBoxNumberEnd()
{
    
}

void WinDialog::setGoleNumberWithAction()
{
    s_goletmpNumber = 0;
    Director::getInstance()->getScheduler()->schedule(schedule_selector(WinDialog::setGoldNumber), this, 0.001f, false);
}
void WinDialog::setGoldNumber(float dt)
{
    s_goletmpNumber+=100;
    if (s_goletmpNumber >= s_goldNumber) {
        s_goldNumberLabel->setString(to_string(s_goldNumber));
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(WinDialog::setGoldNumber), this);
        this->onSetGoldNumberEnd();
    }else{
        s_goldNumberLabel->setString(to_string(s_goletmpNumber));
    }
}
void WinDialog::onSetGoldNumberEnd()
{
    
}

void WinDialog::setWinGoodWithAction()    //使用动画播放战斗结束时得到的物品奖利
{
    if (!s_getGoodIDlist.empty()) {
        Director::getInstance()->getScheduler()->schedule(schedule_selector(WinDialog::setGoodActionTimer), this, 0.2f, false);
    }
}

void WinDialog::setGoodActionTimer(float dt)
{
    
    if (s_getGoodIDlist.empty()) {
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(WinDialog::setGoodActionTimer), this);
        this->setWinHeroExpWithAction();
    }else{
        int goodid = s_getGoodIDlist.front();
        s_getGoodIDlist.pop_front();
        if (goodid < 300000) {
            //掉落物品为道具tab_item_base_sys
            Configtab_item_base_sysDataST itemData = LocalDataManger::sharedLocalDataManger()->getConfigtab_item_base_sysDataST(goodid);
            ImageView* goodbox = s_goodBoxVector.front();
            s_goodBoxVector.pop_front();
            //std::string tmpstr = "prop/"+itemData.item_icon;
            Sprite* itemIcon = Sprite::createWithSpriteFrameName(itemData.item_icon);
            itemIcon->setPosition(Point(54,54));
            goodbox->addChild(itemIcon);
        
            
        }else{
            //掉落物品为装备tab_equipbase_sys
            Configtab_equipbase_sysDataST equiData = LocalDataManger::sharedLocalDataManger()->getConfigtab_equipbase_sysDataST(goodid);
            ImageView* goodbox = s_goodBoxVector.front();
            s_goodBoxVector.pop_front();
            //std::string tmpstr = "equip/"+equiData.equip_icon;
            Sprite* itemIcon = Sprite::createWithSpriteFrameName(equiData.equip_icon);
            itemIcon->setPosition(Point(54,54));
            goodbox->addChild(itemIcon);
        }
    }
    
}

void WinDialog::setWinHeroExpWithAction() //设置经验条动画
{
    for (int i = 0; i < kUserHeroNumber; i++) {
        if (s_warHeroArr[i].heroID > 100) {
            ImageView* tmpview = s_heroBoxArr[i];
//            tmpview->setVisible(true);
//            ImageView* heroIcon = static_cast<ImageView*>(Helper::seekWidgetByName(tmpview, "head_image"));
//            Configtab_card_attribute_sysDataST heroData = LocalDataManger::sharedLocalDataManger()->getConfigtab_card_attribute_sysDataST(s_warHeroArr[i].heroID);//s_warHeroArr[i].heroID;
//            
//            heroIcon->loadTexture(heroData.hero_icon,TextureResType::PLIST);
            
            loadbar[i] = static_cast<LoadingBar*>(Helper::seekWidgetByName(tmpview, "ProgressBar_experience"));
            isLoadEnd[i] = false;
            float leveNeedExp = 100.0f;  //当前等级升级需要多少经验，由经验算得
            loadbarPercent[i] = (float)(s_warHeroArr[i].exp/leveNeedExp)*100.0f;
            
        }
    }
    Director::getInstance()->getScheduler()->schedule(schedule_selector(WinDialog::loadingbarAction), this, 0.01f, false);
}

void WinDialog::loadingbarAction(float dt)
{
    bool isEnd =true;
    for (int i = 0; i < kUserHeroNumber; i++) {
        if (!isLoadEnd[i] && s_warHeroArr[i].heroID > 100) {
            if (loadbar[i]->getPercent() >= loadbarPercent[i]) {
                loadbar[i]->setPercent(loadbarPercent[i]);
                isLoadEnd[i] = true;
            }else{
                float tmpx = loadbar[i]->getPercent();
                float tmp = tmpx + 2.0f;
                loadbar[i]->setPercent(tmp);
                isEnd = false;
            }
        }
        
    }
    
    if (isEnd) {
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(WinDialog::loadingbarAction), this);
        this->allActionEnd();
    }
}
void WinDialog::allActionEnd()//所有动画播放结束
{
    isActionEnd = true;
}

//当用户想要提前结束动时点击了屏幕
void WinDialog::whenUserTouchEndAction()
{
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    
    s_winIcon->stopAllActions();
    s_winIcon->setScale(1.0f);
    
    s_winText->stopAllActions();
    s_winText->setScale(1.0f);
    
    s_star1->stopAllActions();
    s_star1->setScale(1.0f);
    s_star2->stopAllActions();
    s_star2->setScale(1.0f);
    s_star3->stopAllActions();
    s_star3->setScale(1.0f);
    
    s_boxIcon->stopAllActions();
    s_boxIcon->setRotation(0.0f);
    s_boxIcon->setVisible(true);
    
    s_goldIcon->stopAllActions();
    s_goldIcon->setRotation(0.0f);
    s_goldIcon->setVisible(true);
    
    s_boxLabel->setString(to_string(s_boxNumber));
    s_goldNumberLabel->setString(to_string(s_goldNumber));
    
    
    while (!s_getGoodIDlist.empty()) {
        int goodid = s_getGoodIDlist.front();
        s_getGoodIDlist.pop_front();
        if (goodid < 300000) {
            //掉落物品为道具tab_item_base_sys
            Configtab_item_base_sysDataST itemData = LocalDataManger::sharedLocalDataManger()->getConfigtab_item_base_sysDataST(goodid);
            ImageView* goodbox = s_goodBoxVector.front();
            s_goodBoxVector.pop_front();
            //std::string tmpstr = "prop/"+itemData.item_icon;
            Sprite* itemIcon = Sprite::createWithSpriteFrameName(itemData.item_icon);
            itemIcon->setPosition(Point(54,54));
            goodbox->addChild(itemIcon);
            
            
        }else{
            //掉落物品为装备tab_equipbase_sys
            Configtab_equipbase_sysDataST equiData = LocalDataManger::sharedLocalDataManger()->getConfigtab_equipbase_sysDataST(goodid);
            ImageView* goodbox = s_goodBoxVector.front();
            s_goodBoxVector.pop_front();
            //std::string tmpstr = "equip/"+equiData.equip_icon;
            Sprite* itemIcon = Sprite::createWithSpriteFrameName(equiData.equip_icon);
            itemIcon->setPosition(Point(54,54));
            goodbox->addChild(itemIcon);
        }
    }
    
    for (int i = 0; i < kUserHeroNumber; i++) {
        if (s_warHeroArr[i].heroID > 100) {
            ImageView* tmpview = s_heroBoxArr[i];
//            tmpview->setVisible(true);
//            ImageView* heroIcon = static_cast<ImageView*>(Helper::seekWidgetByName(tmpview, "head_image"));
//            Configtab_card_attribute_sysDataST heroData = LocalDataManger::sharedLocalDataManger()->getConfigtab_card_attribute_sysDataST(s_warHeroArr[i].heroID);//s_warHeroArr[i].heroID;
//            
//            heroIcon->loadTexture(heroData.hero_icon,TextureResType::PLIST);
            
            loadbar[i] = static_cast<LoadingBar*>(Helper::seekWidgetByName(tmpview, "ProgressBar_experience"));
            float leveNeedExp = 100.0f;  //当前等级升级需要多少经验，由经验算得
            loadbar[i]->setPercent((float)(s_warHeroArr[i].exp/leveNeedExp)*100.0f);
            isLoadEnd[i] = true;
            
        }
    }
}