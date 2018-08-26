//
//  MainCityScence.h
//  game1
//
//  Created by 俊盟科技1 on 9/5/14.
//
//

#ifndef __game1__MainCityScence__
#define __game1__MainCityScence__


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

////////
#include "Account.h"
#include"StrSplit.h"



////////////////////
struct   HERO{          //英雄动画结构体；
    
    Armature * armature;    //英雄动画；
    ImageView  *Dialog;       //对话框；
    
    int    vIndex;                  //点的索引；
    bool   stop;                    //是否站立；
    bool   Direction;               //行走方向；
    
    vector<Point>  pointV;          //TILED定位点容器；
    vector<string>  showWordV;        //显示的信息容器；
};






class MainCityScence : public cocos2d::Layer
{
    
public:
    //初始化函数；
    MainCityScence();
    ~MainCityScence();
    virtual bool init();
    CREATE_FUNC(MainCityScence);
    
    void  setResoursePath();                  //=====添加整个工程的资源路径；
    

public:
    //功能函数；

    void  monsterCallback1(float  dt);        //====定时器；
    void  monsterCallback2(float  dt);        //====定时器；
    void  monsterCallback3(float  dt);        //====定时器；
    void  monsterCallback4(float  dt);        //====定时器；
    void  monsterCallback5(float  dt);        //====定时器；
    void  monsterCallback6(float  dt);        //====定时器；
    
    void  setZ(Armature *armatureHero, ImageView *textDialog);        //位置和Z；
    Armature *  getArmature(string  ID);                               //用ID获取动画；
    void  heroLoad();                                  //初始位置；
    void  initHeroST(vector<string> m_hero);             //初始化英雄动画结构体；
    void  heroMove(HERO &hero,float &moveT);            //定时器里调用的英雄移动函数；
    
    
public:
    //界面函数，按钮，文字设置；
    //设置文本;
    void  setTextLevel(std::string  str);
    void  setTextName(std::string  str);
    void  setTextScore(std::string  str);
    void  setTextGold(std::string  str);
    void  setTextDialog(std::string   str);
    
    //按钮；
    bool  buttonLoad();       //按钮设置监听；
    void  buttonEvent(Ref *pSender, Widget::TouchEventType   type);  //按钮响应函数；
    void  openUI(string  strUI,int  tag);    //----打开界面；
    
   
	
   

public:
    //全局变量；
    
	Widget *m_pNode;                 //UI界面；
    Account  *m_account;             //账号；
    vector<string> m_resoursePath;     //资源路径；
    vector<string> m_heroID;            //走动的英雄ID集；
    vector<HERO>  m_heroArmature;     //走动的英雄集；
    Color3B  m_buttonPress;          //按下按钮的颜色；
    
    
    
};

#endif /* defined(__game1__MainCityScence__) */




