/**********************************************
市场界面；


**********************************************/
#pragma once

#ifndef __UiMarket_H__
#define __UiMarket_H__


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
#include "Account.h"


class UiMarket : public UiBase
{
public:
    //初始化函数；
    virtual bool init();  
	CREATE_FUNC(UiMarket);
    virtual void onExit();
    virtual void onEnter();

    
    //面板；
    void setPanel(vector<string>  itemID,  int  itemNum);         //设置面板; (商品，面板项数)；
    void setItem(Widget *pSender, vector<string>  itemID, int n ); //======设置里面的项；
    
    
	//按钮
    
	bool  buttonInit();                           //初始化按钮；
    void  buttonEvent(Ref *pSender, Widget::TouchEventType    type);   //按钮响应；
	
    
    
    
    //
    

public:
    Widget *m_pNode;                //UI界面；
    vector<string>  m_goods;         //商品ID;

    vector<Layout*>  m_panelItem;    //项集；不让重复创建；
};

#endif
