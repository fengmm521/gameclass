/**********************************************
邮箱界面；


**********************************************/
#pragma once

#ifndef __UiEmail_H__
#define __UiEmail_H__


#include "cocos2d.h"
#include"cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace std;

#include"UiVIP.h"
#include "UiBase.h"
#include "Account.h"


class UiEmail : public UiBase
{
public:
public:
    //初始化函数；
    UiEmail();
    ~UiEmail();
    virtual bool init();
    CREATE_FUNC(UiEmail);
    virtual void onExit();
    virtual void onEnter();
    
    
    
    
    //列表；
    void setListView();
    void setItem(Widget *pSender,int  n);   //设置里面的项；
    
    void  setPanelItemShow(ssize_t index);
    void  setPanelItemHide();
    
    //响应函数；
    void  scrollViewEvent(Ref *pSender, ui::ScrollView::EventType type);      //滚动图层回调函数，；
    void  listViewEvent(Ref *pSender, ui::ListView::EventType type);
    void  sliderEvent(Ref *pSender, Slider::EventType type);
    
    
    //按钮
    
    bool  buttonInit();                           //初始化按钮；
    void  buttonEvent(Ref *pSender, Widget::TouchEventType    type);   //按钮响应；
    
    
    
    

    
    
    
public:
    Widget *m_pNode;                //UI界面；
    
    ui::ListView  *m_listView;
    Slider  *m_slider;
    
    float   m_percent;
    ssize_t   m_prePress;
};
#endif
