//
//  FuBeiUILayer.h
//  game2
//
//  Created by 俊盟科技1 on 9/15/14.
//
//

#ifndef __game2__FuBeiUILayer__
#define __game2__FuBeiUILayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SplitDataConfig.h"
#include "LocalDataManger.h"
using namespace cocos2d;
class FuBeiUILayer : public cocos2d::Layer
{
public:
    virtual bool init();
    // implement the "static create()" method manually
    static FuBeiUILayer* createForScence(Layer* p,int ID);
    Layer* m_parent;
    ui::Widget* _layout;
    int m_ID; //副本ID
    Configtab_checkpoints_sysDataST m_mapDataST;     //副本数据
    CheckPointMonstersST m_enamyDataST[5]; //怪物序列数据
    //分解字符串，得到怪物数据
    void setEnamyDataWithSplitString(std::string &str);
    
    void  buttonHeroEvent(Ref *pSender, ui::Widget::TouchEventType  type);
    
    bool isbuttontouch;
    void buttonZhenZhanTouched();
    void buttonSaoDangTouched();
    void buttonSaoDang10Touched();
    void buttonBuyTouched();
    void buttonZhenRongTouched();
    void buttonHero1Touched();
    void buttonHero2Touched();
    void buttonHero3Touched();
    void buttonHero4Touched();
    void buttonHero5Touched();
    void buttonGood1Touched();
    void buttonGood2Touched();
    void buttonGood3Touched();
    void buttonGood4Touched();
    void buttonGood5Touched();
    void buttonBackTouched();
    
    
    ui::Text* fubeiDesText; //副本描述
    ui::Text* BoosBloodText; //怪物血量"生命值 %d"10
    ui::Text* chuzhanCiShuText; //今日出战次数"今日出战次数 99/99"
    ui::Text* sdjCountText;     //扫挡卷数量"99"
    
    void closd();
    
    virtual void onExit();
    virtual void onEnter();
    
    Point enamyIconPo[5];
    
    void setEnamyIcon();
    
    
};
#endif /* defined(__game2__FuBeiUILayer__) */
