/**********************************************
铁匠铺界面；


**********************************************/
#pragma once

#ifndef __UiSmithy_H__
#define __UiSmithy_H__


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
#include"Account.h"
#include "StrSplit.h"


class UiSmithy : public UiBase
{
public:
    //初始化函数；
    UiSmithy ();
    ~UiSmithy ();
    virtual bool init();  
	CREATE_FUNC(UiSmithy);
    virtual void onExit();
    virtual void onEnter();

    

    //列表；
    void setListView();
    
    void  setPanelItemShow(ssize_t index);
    void  setPanelItemHide();
    
    //强化；
    void  setPanelStrengthen();
    
    void  setHead(Widget* pWidget, string headImage);      //设置头像；
    void  setHeadBK(Widget* pWidget,string frameLevel,string buttonName="");      //设置头像底框；
    
    
    //升阶；
    void  setPanelUp();
    void  setPanelMaterial(Widget* pWidget,vector<string> materialUp,int num);   //====设置升阶材料,分解材料


    //分解；
    void  setPanelSeparate();
    
    
    //响应函数；
    void  scrollViewEvent(Ref *pSender, ui::ScrollView::EventType type);      //滚动图层回调函数，；
    void  listViewEvent(Ref *pSender, ui::ListView::EventType type);
    void  sliderEvent(Ref *pSender, Slider::EventType type);
    
    //按钮;
    
    virtual bool  buttonInit();                           //初始化按钮；
    virtual void  buttonEvent(Ref *pSender, Widget::TouchEventType    type);   //按钮响应；
    void  buttonPress(Ref *pSender);
    
    
    
    
    //
    
public:
    Widget *m_pNode;                //UI界面；
    Account  *m_account;            //账号；
    float  m_percent;               //滑块位置；
    
    ssize_t  m_prePress;              //先前选择的装备索引；
    
    Layout  *m_panelStrengthen;        //强化；
    Layout  *m_panelUp;                //升阶；
    Layout  *m_panelSeparate;         //分解；
    
   // vector<string> m_materialUp;     //升阶材料；
    
};

#endif
