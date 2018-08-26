/**********************************************
酒馆界面；


**********************************************/
#pragma once

#ifndef __UiTavern_H__
#define __UiTavern_H__


#include "cocos2d.h"
#include"cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace std;

#include"UiBase.h"



class UiTavern : public UiBase
{
public:
    //初始化函数；
    UiTavern();
    ~UiTavern();
    virtual bool init();  
	CREATE_FUNC(UiTavern);
    virtual void onExit();
    virtual void onEnter();

    
    //3个面板；
    void initPanelItem1();
    void initPanelItem2();
    void initPanelItem3();
    
    
    void setPanelItem( vector<Layout*>  panelItem, vector<string>  camp);  //======设置自己的英雄；
    
    
	//按钮
    
	virtual bool  buttonInit();                           //初始化按钮；
    virtual void  buttonEvent(Ref *pSender, Widget::TouchEventType    type);   //按钮响应；
	
    
    
    
    //
    
public:
   
    Widget *m_pNode;                //UI界面；
    
    vector<Layout*>  m_panelItem;    //面板3的6个栏；
    vector<string>  m_goods;         //面板3的6个栏物品；
    
    Layout*  m_panelItem1;      //3个面板；
    Layout*  m_panelItem2;
    Layout*  m_panelItem3;
    
};

#endif
