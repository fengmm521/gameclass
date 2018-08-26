/**********************************************
 账号类；
 与服务器的接口；

**********************************************/
#pragma once

#ifndef __Account_H__
#define __Account_H__


#include "cocos2d.h"
#include"cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace std;
//////////////
//网络；
#include"netConfig.h"
#include"ClientSocketManger.h"
#include"ODSocket.h"
#include"SocketDelegate.h"
#include"MD5.h"

//读表数据；
#include"LocalDataConfig.h"
#include"LocalDataManger.h"

#include"StrSplit.h"

//
struct AccountST{       ////一个账号的基本属性；
    
    
    string  gold="8950000";               //金币；
    string  gem="86400";                  //宝石；
    string  experience="15223400";        //经验；
    string  life="8500";                   //生命；
    string  level="68";                    //等级；
    string  ranking="1580";                 //排名；
    string  fight="12000";                 //
    
    //
    //    int   heroID=0;          //英雄ID
    //    int   starLevel=0;       //星级；
    //    int   level=0;           //等级；
    //    int   sword=0;           //战力；
    //
    //    bool  heroSigne=0;    //是否有遮挡，签到，点击变暗；
};

//
struct HeroST{       //英雄；
  
    Configtab_card_attribute_sysDataST   table=LocalDataManger::sharedLocalDataManger()->getConfigtab_card_attribute_sysDataST(1001);
    
    

    
    
//    string  headBK="";         //头像框；
//    string  headImage="";      //头像；
//    string  heroName="";       //名字；
//    string  heroExperience;    //经验
//    
//    int   heroID=0;          //英雄ID
//    int   starLevel=0;       //星级；
//    int   level=0;           //等级；
//    int   sword=0;           //战力；
//    
//    bool  heroSigne=0;    //是否有遮挡，签到，点击变暗；
};



struct SkillST{       //技能；
    
    Configtab_skill_visual_effectDataST   table=LocalDataManger::sharedLocalDataManger()->getConfigtab_skill_visual_effectDataST(200010);
    
    
    //    string  headBK="";         //头像框；
    //    string  headImage="";      //头像；
    //    string  heroName="";       //名字；
    //    string  heroExperience;    //经验
    //
    //    int   heroID=0;          //英雄ID
    //    int   starLevel=0;       //星级；
    //    int   level=0;           //等级；
    //    int   sword=0;           //战力；
    //
    //    bool  heroSigne=0;    //是否有遮挡，签到，点击变暗；
};


struct EquipST{       //装备；
    
    Configtab_equipbase_sysDataST   table=LocalDataManger::sharedLocalDataManger()->getConfigtab_equipbase_sysDataST(300001);
    
    
    //    string  headBK="";         //头像框；
    //    string  headImage="";      //头像；
    //    string  heroName="";       //名字；
    //    string  heroExperience;    //经验
    //
    //    int   heroID=0;          //英雄ID
    //    int   starLevel=0;       //星级；
          int   level=25;           //等级；
    //    int   sword=0;           //战力；
    //
    //    bool  heroSigne=0;    //是否有遮挡，签到，点击变暗；
};

struct PropST{       ///道具；
    
    Configtab_item_base_sysDataST  table=LocalDataManger::sharedLocalDataManger()->getConfigtab_item_base_sysDataST(100001);;
    
    
    //    string  headBK="";         //头像框；
    //    string  headImage="";      //头像；
    //    string  heroName="";       //名字；
    //    string  heroExperience;    //经验
    //
    //    int   heroID=0;          //英雄ID
    //    int   starLevel=0;       //星级；
    //    int   level=0;           //等级；
    //    int   sword=0;           //战力；
    //
    //    bool  heroSigne=0;    //是否有遮挡，签到，点击变暗；
};

//
struct  CampST{                         //阵容
    
    vector<string>   m_mainCamp;       //主阵容；
    vector<string>   m_arenaCamp;      //竞技场阵容；


};





/////////////////////////////////////////////////////////////////////
class Account:public  Ref    //,SocketReciveDelegate
{
public:
    //初始化函数；
    static  Account*  sharedAccount();
    static  void  destroyAccount();
    

    CREATE_FUNC(Account);
    //static Account* create(string accountID);
    virtual bool init();

    void onExit();
    void onEnter();

    //
    void  setAccountID(string accountID );

    //MAP设置函数；
    void  setHero( );     //英雄；
    void  setSkill( );    //技能；
    void  setEquip( );    //装备；
    void  setProp( );     //道具；
    void  setCamp(vector<string> camp,int  type);      //阵容;  (英雄ID,类型1主阵2竞技场)
    void  saveCamp();
private:
    Account();
    ~Account();

    
public:
    string  m_accountID;              //存储账号；
    AccountST   m_accountST;              //一个账号的基本属性；如金币，宝石，
    
    //STRING是一些ID; MAP每个ID的属性值；结构体包含固定的读表值table和自定的表中没有的属性；
    
    vector<string >  m_hero;               //一个账号里的英雄
    map<int ,HeroST>   m_heroProperty;    //一个英雄的属性；
    
    vector<string> m_skill;                //一个账号里的技能
    map<int ,SkillST> m_skillProperty;    //技能；
    
    vector<string> m_equip;               //一个账号里的装备
    map<int,EquipST> m_equipProperty;    //装备；
    
    vector<string> m_prop;                //一个账号里的道具
    map<int,PropST> m_propProperty;      //道具；材料
    
    
    
    CampST  m_campST;                       //阵容;
    
    
    
    
    
    
    
    
/////////////////////////////////////////////////////////////////////
public:
    //网络；
    void  reciveDataHandler(string &data,  int type,  bool  ispush=false);  //接收消息；
    
    
    void  sendCallback(float  dt);   //定时器；
    void  login();                  //登录；
    void  send100(string sendstr);  //发送设备码；
    void  send105(string  sendstr);  //（账号+密码=MD51）+设备码+时间=MD52；

public:
    //账号；
   // static Account*  s_account;
    bool  m_connect;   //是否连接上服务器；
    
    string  m_message100;     //接收到的100的消息；
    bool   m_sendTrue100;      //是否可以继续发送；
    string  m_message105;     //接收到的105的消息；
    bool   m_sendTrue105;
    int    m_second;         //定时器计数，10秒后开启sendTrue100才可以重发；
};

#endif
