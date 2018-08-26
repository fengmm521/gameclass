/**********************************************
仓库界面；


**********************************************/
#pragma once

#ifndef __UiDepot_H__
#define __UiDepot_H__


#include "cocos2d.h"
#include"cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include<iostream>

#include<string>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace std;

#include"UiBase.h"

#include"Account.h"
#include"LocalDataConfig.h"
#include"LocalDataManger.h"
#include"MD5.h"

class UiDepot : public UiBase
{
public:
    //初始化函数；
    UiDepot();
    ~UiDepot();
    virtual bool init();  
	CREATE_FUNC(UiDepot);
    virtual void onExit();
    virtual void onEnter();

    //
    void  geoodsClassify();   //物品分类；
    
    //滚动图层；
    bool  scrollViewInit(ui::ScrollView* scrollView,vector<string>  goods, Slider*  &slider);   //初始化滚动图层；并添加精灵项；(滚动图层,ID,滑块)
    void  setItem(Widget* imageItem,string  itemID);    //设置一个精灵项；
    
   
   
    
    //响应函数；
    void  scrollViewEvent(Ref *pSender,    ui::ScrollView::EventType type  );      //滚动图层回调函数，设置页面数字；
    void  sliderEvent(Ref *pSender, Slider::EventType type);
    
    
    
    //按钮;
    
    bool  buttonInit();                           //初始化按钮；
    void  checkBoxEvent(Ref *pSender, CheckBox::EventType    type);   //复选响应；
    void  checkBoxPress(Ref *pSender);
    void  checkBoxSetTure(CheckBox  *button,Text  *text,Slider*   slider, ui::ScrollView*  scrollView);
    
    
    void  buttonEvent(Ref *pSender, Widget::TouchEventType type);   //按钮响应；
    
    
    //
    
public:
    Widget *m_pNode;                //UI界面；
    //vector<string>  m_string;
    
    ui::ScrollView*  m_scrollView1;  //
    ui::ScrollView*  m_scrollView2;
    ui::ScrollView*  m_scrollView3;
    ui::ScrollView*  m_scrollView4;
    ui::ScrollView*  m_scrollView5;
    ui::ScrollView*  m_scrollView6;
    
    Slider*   m_slider;
    Slider*   m_slider1;
    Slider*   m_slider2;
    Slider*   m_slider3;
    Slider*   m_slider4;
    Slider*   m_slider5;
    Slider*   m_slider6;
    
    CheckBox  *m_buttonPre;
    Text  *m_textPre;
    Slider*   m_sliderPre;
    ui::ScrollView*  m_scrollViewPre;
    
    vector<string>  m_goods;         //商品ID;
    
    vector<string>  m_hero;          //1英雄，， ，
    vector<string>  m_equip;         //3装备
    vector<string>  m_prop;          //4材料；
    
    float  m_percent;
    //float  m_panelHight;
    
    
};

#endif
