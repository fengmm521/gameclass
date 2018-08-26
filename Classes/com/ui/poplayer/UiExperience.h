/**********************************************
经验界面；


**********************************************/
#pragma once

#ifndef __UiExperience_H__
#define __UiExperience_H__


#include "cocos2d.h"
#include"cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include<iostream>
#include<stdlib.h>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace std;

///////

#include"UiBase.h"
#include"Account.h"

//#include"LocalDataConfig.h"
//#include"LocalDataManger.h"







class UiExperience : public UiBase
{
public:
    //初始化函数；
    UiExperience();
    ~UiExperience();
    
    virtual bool init();  
	CREATE_FUNC(UiExperience);
    virtual void onExit();
    virtual void onEnter();

    
   
    //滚动图层；
    bool  scrollViewInit();                 //初始化滚动图层；并添加精灵项；
    
    void  setItem(Widget* imageItem,string  ID);    //设置一个精灵项；
    
    void  setHeadBK(Widget* pWidget,string ID);   //设置底框；
    void  setHead(Widget* pWidget, string ID);       //设置头像；
    void  setStar(Widget* pWidget,int starLevel);         //设置星级；
    void  setLevel(Widget * pWidget,int  level);         //设置等级；
    void  setHeroName(Widget * pWidget, string  ID,int  quality);   //名字；（品质）
    void  setProgress(Widget * pWidget, string ID);           //战力；
    
    
    //void  setSigned(Widget* pWidget,bool visible);       //设置标记；
    
    
    //响应函数；
    void  scrollViewEvent(Ref *pSender,    ui::ScrollView::EventType type  );      //滚动图层回调函数，设置页面数字；
    void  sliderEvent(Ref *pSender, Slider::EventType type);
    
    
	//按钮
    
	virtual bool  buttonInit();                           //初始化按钮；
    virtual void  buttonEvent(Ref *pSender, Widget::TouchEventType    type);   //按钮响应；
	

    
public:
    Widget *m_pNode;                   //UI界面；
    ui::ScrollView*    m_scrollView;   //滚动图层
    Slider  *m_slider;                 //滑块；
    Button  *m_buttonPre;              //先前按过的；
    
    
    vector<string> m_hero;               //一个账号里的装备
    map<int,HeroST> m_heroProperty;       //装备；

    int   m_percent;                      //滑块的位置；
   
    
    EventListenerTouchOneByOne*  m_listener1;    //层的监听事件；
    
    
};

#endif
