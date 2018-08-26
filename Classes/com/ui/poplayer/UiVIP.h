/**********************************************
VIP权利；


**********************************************/
#pragma once

#ifndef __UiVIP_H__
#define __UiVIP_H__


#include "cocos2d.h"
#include"cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace std;
#include "UiBase.h"

class  UiRecharge;

class UiVIP : public UiBase
{
public:
    //初始化函数；
    virtual bool init();  
	CREATE_FUNC(UiVIP);
    virtual void onExit();
    virtual void onEnter();

    //进度条，
    void  progressInit();
    
    
    //翻页层；
    bool  pageViewInit(int count);                 //初始化翻页层；
    void  setTextPrivilege( Layout * pageLayer, vector<string> str, int  level,int num);   //-==设置层里的文字；(层，文字容器，等级,文字项)
    void  pageViewEvent(Ref *pSender,    PageView::EventType type  );      //翻页层回调函数，设置页面数字；
    
    //
    
	//按钮
    
	bool  buttonInit();                           //初始化按钮；
    void  buttonEvent(Ref *pSender, Widget::TouchEventType    type);   //按钮响应；
	
    
    
    
    //
    
public:
    Widget *m_pNode;                //UI界面；
    //vector<string>  m_string;
    
};

#endif
