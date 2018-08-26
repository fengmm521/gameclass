//
//  FuBeiUILayer.cpp
//  game2
//
//  Created by 俊盟科技1 on 9/15/14.
//
//

#include "FuBeiUILayer.h"
#include "StrSplit.h"
#include "cocostudio/CocoStudio.h"
#include "strHash.h"
#include "WarScenceLayer.h"

#define kuiPoPLayer   2000
using namespace cocos2d::ui;



FuBeiUILayer* FuBeiUILayer::createForScence(Layer* p,int ID)
{
    FuBeiUILayer* tmp = new FuBeiUILayer();
    tmp->autorelease();
    tmp->m_parent = p;
    tmp->m_ID = ID;
    tmp->init();
    return tmp;
}
// on "init" you need to initialize your instance
bool FuBeiUILayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    
    do
    {
        
        isbuttontouch = false;
        
        m_mapDataST = LocalDataManger::sharedLocalDataManger()->getConfigtab_checkpoints_sysDataST(m_ID);
        _layout = dynamic_cast<ui::Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/FubeiUI/FubeiUI_1.ExportJson"));
        
        this->addChild(_layout,kuiPoPLayer);
       
 
        
        this->setEnamyDataWithSplitString(m_mapDataST.checkpoint_monsters);
        
        
        
        
        //征战
        Button* zhenzhanBtn = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_zhenzhan"));
        zhenzhanBtn->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
       // CC_CALLBACK_2
        //扫挡
        Button* saodangBtn = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_saodang"));
        saodangBtn->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        //扫挡10
        Button* saodang10Btn = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_saodang10"));
        saodang10Btn->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        //购买
        Button* buyBtn = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_buy"));
        buyBtn->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        //阵容
        Button* zhenrongBtn = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_zhenrong"));
        zhenrongBtn->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        
        
        //怪物头像
        Button* hero1 = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_sp1"));
        hero1->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        enamyIconPo[0] = hero1->getWorldPosition();
        Button* hero2 = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_sp2"));
        hero2->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        enamyIconPo[1] = hero2->getWorldPosition();
        Button* hero3 = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_sp3"));
        hero3->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        enamyIconPo[2] = hero3->getWorldPosition();
        Button* hero4 = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_sp4"));
        hero4->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        enamyIconPo[3] = hero4->getWorldPosition();
        Button* hero5 = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_sp5"));
        hero5->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        enamyIconPo[4] = hero5->getWorldPosition();
        
        //掉落物品
        Button* good1 = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_g1"));
        good1->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        Button* good2 = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_g2"));
        good2->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        Button* good3 = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_g3"));
        good3->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        Button* good4 = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_g4"));
        good4->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        Button* good5 = dynamic_cast<ui::Button*>(_layout->getChildByName("Button_g5"));
        good5->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));

        //返回
        Button* backBtn = dynamic_cast<Button*>(_layout->getChildByName("Button_back"));
        backBtn->addTouchEventListener(std::bind(&FuBeiUILayer::buttonHeroEvent,this,std::placeholders::_1,std::placeholders::_2));
        
        //副本描述
        fubeiDesText = dynamic_cast<Text*>(_layout->getChildByName("Label_32"));
        //怪物血量
        BoosBloodText = dynamic_cast<Text*>(_layout->getChildByName("Label_29"));
        //今日出战次数
        chuzhanCiShuText = dynamic_cast<Text*>(_layout->getChildByName("Label_33"));
        //扫挡卷数量
        sdjCountText = dynamic_cast<Text*>(_layout->getChildByName("Label_sdjcount"));
        
        
       this->setEnamyIcon();
        
        
    }while(0);
    
    return true;
}
void FuBeiUILayer::setEnamyDataWithSplitString(string &str)
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
        log("id=%d,type=%d,pinzhi=%d,star=%d,leve=%d,spqce=%d",atoi(tmpxx[0].c_str()),atoi(tmpxx[1].c_str()),atoi(tmpxx[2].c_str()),atoi(tmpxx[3].c_str()),atoi(tmpxx[4].c_str()),atoi(tmpxx[5].c_str()));
    }
}
void FuBeiUILayer::setEnamyIcon()
{
    for(int i = 0;i < 5;i++)
    {
        if (m_enamyDataST[i].ID > 0) {
            string tmx = to_string(m_enamyDataST[i].ID) + "_touxiang.png";
            ImageView* tmpimage = ImageView::create(tmx,TextureResType::PLIST);
            tmpimage->setPosition(enamyIconPo[i]);
            this->addChild(tmpimage,kuiPoPLayer);
        }
    }
}
void  FuBeiUILayer::buttonHeroEvent(Ref *pSender, ui::Widget::TouchEventType   type)
{
    
    Button* btntmp = dynamic_cast<Button*>(pSender);
    if (type == Widget::TouchEventType::ENDED) {
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Click_Button.wav");
        
        switch(hash_(btntmp->getName().c_str())){
            case "Button_zhenzhan"_hash:
            {
                if (isbuttontouch) {
                    return;
                }
                this->buttonZhenZhanTouched();
            }
                break;
            case "Button_saodang"_hash:
            {
                this->buttonSaoDangTouched();
            }
                break;
            case "Button_saodang10"_hash:
            {
                this->buttonSaoDang10Touched();
            }
                break;
            case "Button_buy"_hash:
            {
                this->buttonBuyTouched();
            }
                break;
            case "Button_zhenrong"_hash:
            {
                this->buttonZhenRongTouched();
            }
                break;
            case "Button_sp1"_hash:
            {
                this->buttonHero1Touched();
            }
                break;
            case "Button_sp2"_hash:
            {
                this->buttonHero2Touched();
            }
                break;
            case "Button_sp3"_hash:
            {
                this->buttonHero3Touched();
            }
                break;
            case "Button_sp4"_hash:
            {
                this->buttonHero4Touched();
            }
                break;
            case "Button_sp5"_hash:
            {
                this->buttonHero5Touched();
            }
                break;
            case "Button_g1"_hash:
            {
                this->buttonGood1Touched();
            }
                break;
            case "Button_g2"_hash:
            {
                this->buttonGood2Touched();
            }
                break;
            case "Button_g3"_hash:
            {
                this->buttonGood3Touched();
            }
                break;
            case "Button_g4"_hash:
            {
                this->buttonGood4Touched();
            }
                break;
            case "Button_g5"_hash:
            {
                this->buttonGood5Touched();
            }
                break;
            case "Button_back"_hash:
            {
                this->buttonBackTouched();
            }
                break;
            default:
            {
                
            }
                break;
        }
    }
}
void FuBeiUILayer::buttonZhenZhanTouched()
{
    isbuttontouch = true;
    auto scene = Scene::create();
    WarScenceLayer* layer = WarScenceLayer::createWarWithMapID(m_mapDataST.ID);
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    
}
void FuBeiUILayer::buttonSaoDangTouched()
{
    
}
void FuBeiUILayer::buttonSaoDang10Touched()
{
    
}
void FuBeiUILayer::buttonBuyTouched()
{
    
}
void FuBeiUILayer::buttonZhenRongTouched()
{
    
}
void FuBeiUILayer::buttonHero1Touched()
{
    
}
void FuBeiUILayer::buttonHero2Touched()
{
    
}
void FuBeiUILayer::buttonHero3Touched()
{
    
}
void FuBeiUILayer::buttonHero4Touched()
{
    
}
void FuBeiUILayer::buttonHero5Touched()
{
    
}
void FuBeiUILayer::buttonGood1Touched()
{
    
}
void FuBeiUILayer::buttonGood2Touched()
{
    
}
void FuBeiUILayer::buttonGood3Touched()
{
    
}
void FuBeiUILayer::buttonGood4Touched()
{
    
}
void FuBeiUILayer::buttonGood5Touched()
{
    
}
void FuBeiUILayer::buttonBackTouched()
{
    this->closd();
}
void FuBeiUILayer::closd()
{
    this->removeFromParent();
}
void FuBeiUILayer::onExit()
{
    
    Layer::onExit();
}
void FuBeiUILayer::onEnter()
{
    Layer::onEnter();
    
}