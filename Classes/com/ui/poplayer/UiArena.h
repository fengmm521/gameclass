/**********************************************
竞技场界面；


**********************************************/
#pragma once

#ifndef __UiArena_H__
#define __UiArena_H__


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
#include"UiCamp.h"





struct  adversaryST{
    string  id="1001";
    string  imageHead="1001";
    string  buttonHead="1001";
    
    string  name="天山剑客";
    string  sword="战斗力:10000";
    string  ranking="排名:1902";
    
};





class UiArena : public UiBase
{
public:
    //初始化函数；
    UiArena();
    ~UiArena();
    virtual bool init();  
	CREATE_FUNC(UiArena);
    virtual void onExit();
    virtual void onEnter();
    
    //竞技面板；
    void setPanelArena();    //设置面板; (商品，面板项数)；
    void initPanelItem(Widget *pSender, vector<string>  itemID);              //======初始化自己的英雄；
    void setPanelItem( vector<Layout*>  panelItem, vector<string>  camp);  //======设置自己的英雄；
    void setCamp(vector<string> camp);  //设置阵容，接收阵容界面的数据；
    
    
    void initPanelHero(Widget *pSender, vector<adversaryST> adversary);       //===初始化挑战的英雄；
    void setPanelHero(vector<Layout*>  panelHero, vector<adversaryST> adversary);       //===设置挑战的英雄；
   
    
    void timeCallback(float dt);
    //兑换面板；
    void setPanel(Widget *pSender,vector<string>  itemID,  int  itemNum);         //设置面板; (商品，面板项数)；
    void setItem(Widget *pSender, vector<string>  itemID, int n ); //======设置里面的项；
    
    
    //按钮
    
    bool  buttonInit();                           //初始化按钮；
    void  buttonEvent(Ref *pSender, Widget::TouchEventType    type);   //按钮响应；
    
    void  buttonPress(Ref *pSender);
    
    


public:
    Widget *m_pNode;                //UI界面；
    vector<string>  m_goods;         //商品ID;

    //竞技
    Layout*   m_panelArena;         //竞技面板；
    Button*   m_buttonArena;        //竞技按钮
    
    vector<Layout*>  m_panelItem;    //5个阵容英雄；
    vector<string> m_camp;           //自己的阵容；
    
    vector<Layout*>  m_panelHero;    //3个对手；
    vector<adversaryST> m_adversary;       //对手；
    
    //兑换
    Layout*   m_panelExchangepa;    //兑换面板；
    Button*   m_buttonExchange;     //兑换按钮
    vector<Layout*>  m_panelItem2;    //5个阵容英雄；
    int    m_time;      //倒计时；
    

    
};

#endif
