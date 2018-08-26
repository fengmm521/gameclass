/**********************************************
UI界面基类；


**********************************************/
#pragma once

#ifndef __UiBase_H__
#define __UiBase_H__


#include "cocos2d.h"
#include"cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace std;


#include "Account.h"

//网络；
#include"netConfig.h"
#include"ClientSocketManger.h"
#include"ODSocket.h"
#include"SocketDelegate.h"


struct HeroProperty{       //英雄的基本属性结构体；//从英雄的属性表赋值；存在的意义是接口，表一修改，只修改赋值就行；
  
    string  headBK="";         //头像框；
    string  headImage="";      //头像；
    string  heroName="";       //名字；
    string  heroExperience;    //经验
    
    int   heroID=0;          //英雄ID
    int   starLevel=0;       //星级；
    int   level=0;           //等级；
    int   sword=0;           //战力；
    
    bool  heroSigne=0;    //是否有遮挡，签到，点击变暗；
};



struct EquipProperty{       //装备的基本属性结构体；//从英雄的属性表赋值；存在的意义是接口，表一修改，只修改赋值就行；
    
    int   equipID=0;          //装备ID
    
    string  equipImage="";      //装备图标；

    
    bool  equipSigne=0;      //是否有遮挡，无装备；
};



//继承SocketReciveDelegate用来发送消息和接收消息；

class UiBase : public Layer//,SocketReciveDelegate
{
public:
    //初始化函数；
    virtual bool init();  
	CREATE_FUNC(UiBase);
    virtual void onExit();
    virtual void onEnter();

   //公共函数；
    Armature *  getArmatrue(string  heroID);      //=====根据ID导入动画
    string   getQualityFrame1( int  quality);      //====根据品质获取品质框图片名，方的；
    string   getQualityFrame2( int  quality);      //===根据品质获取品质框图片名，长的；
    string   getQualityFrame3( int  quality);      //===根据品质获取品质框图片名，装备的框；
    int      getGoodsType(string  goodsID);        //===根据ID获取类型，1英雄，2技能， 3装备，4材料；
   
    //按钮
    
	bool  buttonInit();                           //初始化按钮；
    void  buttonEvent(Ref *pSender, Widget::TouchEventType    type);   //按钮响应；
	
    
    
    
    //网络；
   // virtual void  reciveDataHandler(string &data,  int type,  bool  ispush);
    
    
public:
    Widget *m_pNodeBase;                //UI界面；
    //vector<string>  m_string;
    
};

#endif
