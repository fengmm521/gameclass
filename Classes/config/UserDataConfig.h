//
//  UserDataConfig.h
//  game4
//  使用结构体来进行游戏属性存储会比较方便快捷
//
//  Created by Junpeng Zhang on 12/24/14.
//
//

#ifndef game4_UserDataConfig_h
#define game4_UserDataConfig_h
#include "cocos2d.h"
using namespace std;


enum HeroUsedLienup_E
{
    e_nomalLineup = 1,
    e_fightLineup,
    e_zhenZhanLineup,
    e_noUsed
};
typedef enum HeroUsedLienup_E HeroLineUp; //英雄所在阵容

//装备数据equip
struct AccountEquip_ST
{
    int ID＝0;                         //装备ID
    int netID;                        //用户装备服务器ID
    int star=0;                       //装备星级
    int FM=0;                         //附魔等级,品质
    int leve=0;                       //装备等级
    int usedHeroID = 0;               //装备所在英雄
    int usedSpase = 0;                //装备所有装备栏位置
};
typedef struct AccountEquip_ST  AccountEquipData;


//英雄数据hero
struct AccountHero_ST
{
    int ID=0;                        //英雄ID
    int netID=0;                     //用户英雄服务器ID,玩家英雄不能重复时，本netID=ID
    int leve = 0;                    //英雄等级
    int star = 0;                    //英雄星级
    int quality = 0;                 //英雄品质
    int skillleve[6];                //英雄技能等级
    int fighting = 0;                //英雄战斗力
    int AccountEquipData[6];         //英雄装备数据
    HeroLineUp lineup = e_noUsed;    //英雄所在阵容
    AccountHero_ST()
    {
        for(int i = 0;i < 6; i++)
        {
            AccountEquipData[i] = 0;
            skillleve[i] = 0;
        }
    };
};
typedef struct AccountHero_ST AccountHeroData;


//道具数据Stage prop
struct AccountStageProp_ST
{
    int ID=0;                         //道具ID
    int netID=0;                      //玩家道具服务器ID
    int count=1;                      //道具数量
    int quality=0;                    //道具品质
    int star=0;                       //星级
    int type = -1;                    //道具类型,药品，英雄碎片，装备碎片，金币，宝石，能量
    int usedOnerID = 0;               //道具所属ID;
};
typedef struct AccountStageProp_ST AccountStagePropData;


//玩家基本数据
struct Account_ST{       ////一个账号的基本属性；
    
    unsigned int gold = 0;              //金币数
    unsigned int gem = 0;               //宝石数
    unsigned int experience = 0;        //经验
    int userEnage = 0;                  //士气能量
    string userName;                    //用户名
    string userID;                      //用户ID
    string userLoginToken;              //用户服务器登陆token
    string userIcon;                    //用户头像图标
    
    
    
    int userleve = 1;                   //玩家等级
    int expRanking = 0;                 //经验排行榜
    
    int allHeroLeve = 0;
    int heroRanking = 0;                //英雄等级排行榜
    
    int fightAttackValue = 0;           //竟技场战力
    int fightRanking = 0;               //竟技场排行榜
    
    int nomalTranNumber = 0;            //普通副本进度
    int nomalTranStarCount = 0;         //普通副本星星数量
    int nomalTranRanking = 0;           //普通副本排行榜
    
    int outstandingTranNumber = 0;      //精英副本进度
    int outstandingTranStarCount = 0;   //精英副本星星数量
    int outstandingTranRanking = 0;     //精英副本排行榜
    
    int allFightRanking = 0;            //综合战力排行榜
    
    std::list<int> heaveHeroNetIDList;                   //玩家英雄netID列表
    std::map<int,AccountHeroData> userHeroDataMap;       //玩家拥有英雄数据
    
    std::list<int> stagePropNetIDList;                   //玩家道具netID列表
    std::map<int,AccountStagePropData> userStagePropMap; //玩家拥有道具数据
    
    int userLineupArr_nomal[6];         //玩家普通战斗阵容,保存英雄netID
    int userLineupArr_fight[6];         //玩家竟技场阵容
    int userLineupArr_zhenZhan[6];      //玩家征战阵容
    
    
    bool userRegistration[12][31];       //玩家是否签到,12个月31天
    
};

typedef struct Account_ST AccountBaseData;

//资源状态改变类型
enum UserDataEventType_E
{
    e_onHeroLeveUpChange = 1,  //英雄升级事件,会改变玩家战斗力
    e_onHeroStarUpChange,      //英雄升星事件
    e_onHeroSynthesis,         //英雄合成
    e_onHeroResolution,        //重复英雄分解
    e_onHeroUsedEquip,         //英雄使用装备
    e_onEquipSynthesis,        //装备合成
    e_onEquipResolution,       //装备分解
    e_onConsumptionUsed,       //消耗品使用
    e_onNomalLineupChange,     //普通阵容改变
    e_onFightLineupChange,     //竟技场阵容改变
    e_onZhenZhanLineupChange,  //征战阵容改变
    e_onEnageChange,           //战斗能量改变
    e_onGoleOrGemChange,       //宝石或金币数量改变
    e_onUserLeveUp,            //玩家升级事件
    e_userBaseDataChange       //玩家基本信息改变，名称，头像，公会等等。
};
typedef enum UserDataEventType_E UserDataEventType;

#endif
