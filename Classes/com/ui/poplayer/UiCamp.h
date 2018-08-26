/**********************************************
阵容界面；


**********************************************/
#pragma once

#ifndef __UiCamp_H__
#define __UiCamp_H__

#include"iostream"
#include "cocos2d.h"
#include"cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace std;
////////
#include"UiBase.h"
#include"LocalDataConfig.h"
#include"LocalDataManger.h"
#include"UiArena.h"

class  MainCityScence;

//////////
class UiCamp : public UiBase
{
public:
    //初始化函数；
    UiCamp();
    ~UiCamp();
    virtual bool init();  
	CREATE_FUNC(UiCamp);
    virtual void onExit();
    virtual void onEnter();

    
    virtual bool  onTouchBegan (Touch  * touch,  Event*  event);
    virtual void  onTouchMoved (Touch  *touch,  Event * event);
    virtual void  onTouchEnded(Touch*  touch,  Event* event);
    

    
    //滚动图层；
    void  scrollViewInit();                               //初始化英雄的个数；
    void  setImageItem(Widget* imageItem,int  heroID);    //设置一个英雄框；
    void  setStar(Widget* pWidget,int starLevel);         //设置星级；
    void  setLevel(Widget* pWidget,int level);
    
   
    
    
    void  sliderEvent(Ref *pSender, Slider::EventType type);
    void  scrollViewEvent(Ref *pSender, ui::ScrollView::EventType type);
    
    /////////站立的英雄；
    void  initLocal();                       //初始站位,
    bool  initStandHero(string heroID);     //点击加动画；
    void  setStandHero(Widget* imageHero, string heroID);  //设置动画；
    ImageView * delStandHero(string heroID);     //点击删除动画；

    void  replaceStandHero(string  heroID);     //拖动加动画；
    void  replaceStandHero2(Widget* imageHero, string heroID,int i);
    
    void  setSigned(string ID, bool  sig );    //设置标志的显示否；
    void  pressCallback(float  dt);     //长按定时器；//按下时在监听层生成一个动画；随鼠标移动，松开时删掉；
    string   getPressID(Point  pt);    //点获取动画ID,用来使上面的定时器有ID生成动画；
    
    
    
    //按钮
    
	virtual bool  buttonInit();                           //初始化按钮；
    virtual void  buttonEvent(Ref *pSender, Widget::TouchEventType    type);   //按钮响应；
	
    //其它面板设置的阵容；
    void  setType(int  n);
    vector<string>  getCamp();         //获取设置好后的阵容；
    void setCamp();         //设置阵容；
    
public:
    Widget *m_pNode;                //UI界面；
    Account* m_account;             //帐号;
    vector<string>  m_string;         //一个帐号里的英雄；
    ui::ScrollView* m_scrollView;     //滚动图层;
    Slider  *m_slider;                //滑块；
    
    ImageView  *m_imageHero1;        //5个上阵的位置；
    ImageView  *m_imageHero2;
    ImageView  *m_imageHero3;
    ImageView  *m_imageHero4;
    ImageView  *m_imageHero5;
    
    int   m_percent;                  //滑块的位置；
   
    //
    vector<bool>  m_heroStand;       //6个位上是否有站立的英雄；
    string   m_pressID;               //跟随鼠标移动的精灵的名字；
    EventListenerTouchOneByOne*  m_listener1;               //层的监听事件；
    Point   m_ptStart;                //随鼠标移动的精灵的开始位置；
    Point   m_ptEnd;                  //随鼠标移动的精灵的结束位置；
    ImageView  *m_imageHeroDel;       //删除动画的站台；
    
    bool   m_del;                     //拖动开启的情况下不执行里面的代码，不然会把加的动画删除；

    //其它面板设置的阵容；
    vector<string>  m_camp;           //上阵的英雄；
    int   m_type;                       //区别哪个场景来设置阵容；

};

#endif
