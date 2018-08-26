//
//  FubeiMapUILayer.cpp
//  game2
//
//  Created by 俊盟科技1 on 9/15/14.
//
//

#include "FubeiMapUILayer.h"
#include "cocostudio/CocoStudio.h"
#include "strHash.h"
#include "FuBeiUILayer.h"
#include "FuBeiUILayer.h"

#define kButton_left   100
#define kButton_right  101
#define kButton_close  102

#define kGameMissionMax 16

#define kBaseMissionNum 400000    //基础关卡数编号

using namespace cocos2d::ui;

// on "init" you need to initialize your instance
FubeiMapUILayer* FubeiMapUILayer::createForScence(Layer* p)
{
    FubeiMapUILayer* tmp = new FubeiMapUILayer();
    tmp->autorelease();
    tmp->m_parent = p;
    tmp->init();
    return tmp;
}
// on "init" you need to initialize your instance
bool FubeiMapUILayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //加载怪物头像
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/WarUI/WarUI0.plist");
    //加载英雄图标
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icon/equip_icon.plist");
    //加载道具图标
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icon/hero_icon.plist");
    //加载装备图标
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icon/tools_icon.plist");
    
    
    _layout = dynamic_cast<ui::Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/FubeiMapUI/FubeiMapUI_1.ExportJson"));
    
    
    this->addChild(_layout);
    
    do
    {
    
        //选项框
        //据情副本
        checkBoxJuQing = dynamic_cast<CheckBox*>(_layout->getChildByName("CheckBox_jq"));
        checkBoxJuQing->addEventListener(std::bind(&FubeiMapUILayer::checkBoxEvent,this,std::placeholders::_1,std::placeholders::_2));
        checkBoxJuQing->setSelectedState(true);
        
        //精英副本
        checkBoxJingYing = dynamic_cast<CheckBox*>(_layout->getChildByName("CheckBox_jy"));
        checkBoxJingYing->addEventListener(std::bind(&FubeiMapUILayer::checkBoxEvent,this,std::placeholders::_1,std::placeholders::_2));
        
        //活动副本
        checkBoxHuoDong = dynamic_cast<CheckBox*>(_layout->getChildByName("CheckBox_hd"));
        checkBoxHuoDong->addEventListener(std::bind(&FubeiMapUILayer::checkBoxEvent,this,std::placeholders::_1,std::placeholders::_2));
        
        selectCheckBoxType = 1;
        
        //征战
        Button* leftBtn = dynamic_cast<Button*>(_layout->getChildByName("Button_left"));
        leftBtn->setTag(kButton_left);
        leftBtn->addTouchEventListener(std::bind(&FubeiMapUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        // CC_CALLBACK_2
        //扫挡
        Button* rightBtn = dynamic_cast<Button*>(_layout->getChildByName("Button_right"));
        rightBtn->setTag(kButton_right);
        rightBtn->addTouchEventListener(std::bind(&FubeiMapUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        
        //关闭
        Button* backBtn = dynamic_cast<Button*>(_layout->getChildByName("Button_close"));
        backBtn->setTag(kButton_close);
        backBtn->addTouchEventListener(std::bind(&FubeiMapUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        
        point1Image = dynamic_cast<ImageView*>(_layout->getChildByName("Image_p1"));
        
        point2Image = dynamic_cast<ImageView*>(_layout->getChildByName("Image_p2"));
        point2Image->setColor(Color3B(135,135,135));
        
        point3Image = dynamic_cast<ImageView*>(_layout->getChildByName("Image_p3"));
        point3Image->setColor(Color3B(135,135,135));
        
        
        mapPageView = dynamic_cast<PageView*>(_layout->getChildByName("PageView_map"));
        mapPageView->setSize(Size(640, 865));
        
        Layout* laytmp = dynamic_cast<ui::Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/FubeiMapUI/FubeiMapUI_2.ExportJson"));
        
        for (int i = 0; i < 3; ++i)
        {
            Layout* layo1 = dynamic_cast<Layout*>(laytmp->clone());
            layo1->setSize(Size(640, 865));

            for (int i = 1;i <= kGameMissionMax; i++) {
                std::string tmpstr = "Button_gk" + to_string(i);
                Button* enamy1 = dynamic_cast<Button*>(layo1->getChildByName(tmpstr));
                enamy1->setTag(i);
                enamy1->addTouchEventListener(std::bind(&FubeiMapUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
            }
            mapPageView->addPage(layo1);
        }
        mapPageView->addEventListener(std::bind(&FubeiMapUILayer::pageViewEvent,this,std::placeholders::_1,std::placeholders::_2));
        
    }while(0);
    
    return true;
}
void FubeiMapUILayer::pageViewEvent(Ref *pSender,PageView::EventType type)
{
    switch (type)
    {
        case PageView::EventType::TURNING:
        {
            PageView* pageView = dynamic_cast<PageView*>(pSender);
             selectPage = (int)pageView->getCurPageIndex();
            log("select page number is:%d",selectPage);
            this->pageviewChanged();
        }
            break;
            
        default:
            break;
    }
}
void FubeiMapUILayer::pageviewChanged()
{
    switch (selectPage) {
        case 0:
        {
            point1Image->setColor(Color3B(255,255,255));
            point2Image->setColor(Color3B(135,135,135));
            point3Image->setColor(Color3B(135,135,135));
        }
            break;
        case 1:
        {
            point1Image->setColor(Color3B(135,135,135));
            point2Image->setColor(Color3B(255,255,255));
            point3Image->setColor(Color3B(135,135,135));
        }
            break;
        case 2:
        {
            point1Image->setColor(Color3B(135,135,135));
            point2Image->setColor(Color3B(135,135,135));
            point3Image->setColor(Color3B(255,255,255));
        }
            break;
        default:
            break;
    }
}
void FubeiMapUILayer::toPageViewLeftPage()
{
   
}
void FubeiMapUILayer::toPageViewRightPage()
{
    
}
void FubeiMapUILayer::checkBoxEvent(Ref *pSender,ui::CheckBox::EventType type)
{
    CheckBox* btntmp = dynamic_cast<CheckBox*>(pSender);
    if (type == CheckBox::EventType::SELECTED) {
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Click_Button.wav");
        
        switch(hash_(btntmp->getName().c_str())){
            case "CheckBox_jq"_hash: //据情选项被按下
            {
                this->selectJuQingPageView();
            }
                break;
            case "CheckBox_jy"_hash: //精英选项被按下
            {
                this->selectJingYingPageView();
            }
                break;
            case "CheckBox_hd"_hash: //活动选项被按下
            {
                this->selectHouDongPageView();
            }
                break;
            default:
            {
                
            }
                break;
        }
    }
}
void  FubeiMapUILayer::buttonHeroEvent(Ref *pSender, ui::Widget::TouchEventType   type)
{
    Button* btntmp = dynamic_cast<Button*>(pSender);
    if (type == Widget::TouchEventType::ENDED) {
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Click_Button.wav");
    
        int tagtmp = btntmp->getTag();
        switch (tagtmp) {
            case kButton_left:
            {
                this->buttonLeftTouched();
            }
                break;
            case kButton_right:
            {
                this->buttonRightTouched();
            }
                break;
            case kButton_close:
            {
                this->buttonBackTouched();
            }
                break;
            default:
            {
                if (tagtmp >= 1 && tagtmp <= kGameMissionMax) {
                    this->buttonTouchedWithNumber(tagtmp);
                }
            }
                break;
        }
        
    }
}
void FubeiMapUILayer::buttonRightTouched()
{
    log("right button touched");
    if (mapPageView->getCurPageIndex() < mapPageView->getPages().size()) {
        mapPageView->scrollToPage(mapPageView->getCurPageIndex() + 1);
    }
}
void FubeiMapUILayer::buttonLeftTouched()
{
    log("left button touched");
    if (mapPageView->getCurPageIndex() > 0) {
        mapPageView->scrollToPage(mapPageView->getCurPageIndex() - 1);
    }
}
//boss
void FubeiMapUILayer::buttonTouchedWithNumber(int number)
{
    int stageNum = kBaseMissionNum + 100*(selectPage+1) + number;
    FuBeiUILayer* tmplayer = FuBeiUILayer::createForScence(m_parent,stageNum);
    m_parent->addChild(tmplayer);
}

void FubeiMapUILayer::selectJuQingPageView()
{
    if(selectCheckBoxType != 1){
        checkBoxJuQing->setSelectedState(true);
        checkBoxJingYing->setSelectedState(false);
        checkBoxHuoDong->setSelectedState(false);
        log("select juqing checkbox");
        selectCheckBoxType = 1;
    }
}
void FubeiMapUILayer::selectJingYingPageView()
{
    if(selectCheckBoxType != 2){
        checkBoxJuQing->setSelectedState(false);
        checkBoxJingYing->setSelectedState(true);
        checkBoxHuoDong->setSelectedState(false);
        log("select juqing checkbox");
        selectCheckBoxType = 2;
    }
}
void FubeiMapUILayer::selectHouDongPageView()
{
    if(selectCheckBoxType != 3){
        checkBoxJuQing->setSelectedState(false);
        checkBoxJingYing->setSelectedState(false);
        checkBoxHuoDong->setSelectedState(true);
        log("select juqing checkbox");
        selectCheckBoxType = 3;
    }
}
void FubeiMapUILayer::buttonBackTouched()
{
    this->closd();
}
void FubeiMapUILayer::closd()
{
    this->removeFromParent();
}
void FubeiMapUILayer::onExit()
{
    
    Layer::onExit();
}
void FubeiMapUILayer::onEnter()
{
    Layer::onEnter();
    
}