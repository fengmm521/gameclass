/**********************************************
英雄集界面；


**********************************************/
#pragma once

#ifndef __UiHeroSet_H__
#define __UiHeroSet_H__


#include "cocos2d.h"
#include"cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include<iostream>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace std;

#include"UiBase.h"
#include"UiHeroDetail.h"
#include"LocalDataConfig.h"
#include"LocalDataManger.h"







class UiHeroSet : public UiBase
{
public:
    //初始化函数；
    virtual bool init();  
	CREATE_FUNC(UiHeroSet);
    virtual void onExit();
    virtual void onEnter();

    
   
    //滚动图层；
    bool  scrollViewInit();                 //初始化滚动图层；并添加精灵项；
    
    void  setItem(Widget* imageItem,string  heroID);    //设置一个精灵项；
    
    void  setHeadBK(Widget* pWidget,string frameLevel);   //设置底框；
    void  setHead(Widget* pWidget, string headImage);       //设置头像；
    void  setStar(Widget* pWidget,int starLevel);         //设置星级；
    void  setLevel(Widget * pWidget,int  level);         //设置等级；
    void  setHeroName(Widget * pWidget, string  name,int  quality);   //名字；（品质）
    void  setSword(Widget * pWidget, int  sword);           //战力；
    void  setEquip(Widget * pWidget, vector<string>  equip);  //设置装备；
    
    
    //void  setSigned(Widget* pWidget,bool visible);       //设置标记；
    
    
    //响应函数；
    void  scrollViewEvent(Ref *pSender,    ui::ScrollView::EventType type  );      //滚动图层回调函数，设置页面数字；
    void  sliderEvent(Ref *pSender, Slider::EventType type);
    
    
	//按钮
    
	virtual bool  buttonInit();                           //初始化按钮；
    virtual void  buttonEvent(Ref *pSender, Widget::TouchEventType    type);   //按钮响应；
	

    
public:
    Widget *m_pNode;                //UI界面；
    Slider  *m_slider;
    ui::ScrollView* m_scrollViewHero;
    
    Configtab_card_attribute_sysDataST  m_mapDataST;   //英雄的属性表；
    HeroProperty    m_heroProperty;    //英雄的属性；
   
    Configtab_equipbase_sysDataST     m_equipST;  //装备的属性表；
   //EquipProperty  m_equipProperty;  //装备的属性；
    
    vector<string>  m_string;          //一个帐号里的英雄；
    vector<string>  m_equip;           //一个英雄里的装备；
    
    float  m_panelHight;              //滚动层里的层高；
    int   m_percent;                  //滑块的位置；
   
    
    EventListenerTouchOneByOne*  m_listener1;    //层的监听事件；
    
    
};

#endif
