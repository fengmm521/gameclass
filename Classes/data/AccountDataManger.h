//
//  AccountDataManger.h
//  game4
//  C++单例类模板，非线程安全单例类，并且实例化后会常注内存
//
//  Created by Junpeng Zhang on 12/24/14.
//
//

#ifndef __game4__AccountDataManger__
#define __game4__AccountDataManger__

#include "cocos2d.h"
#include "UserDataConfig.h"
#include "CallBackVo.h"
#include "SocketDelegate.h"
class AccountDataManger:public cocos2d::Ref,SocketReciveDelegate
{
public:
    static AccountDataManger* sharedAccountDataManger();
    static void destroyInstance();
private:
	/**
     * @js ctor
     */
    AccountDataManger(void);
    /**
     * @js NA
     * @lua NA
     */
    ~AccountDataManger(void);
    
public:
    
    /**
     * Init AccountDataManger
     */
    virtual bool init();
    
    AccountBaseData m_userBaseDataST; //玩家帐号基本数据
    
    
    std::vector<std::string> getOwnerHeroVector();          //所有英雄列表
    std::vector<std::string> getOwnerStagePropVector();     //所有道具列表
    std::vector<std::string> getOwnerEquipFragmentVector(); //所有装备碎片列表
    std::vector<std::string> getOwnerHeroFragmentVector();  //所有英雄碎片列表
    std::vector<std::string> getOwnerEquipVector();         //所有装备列表
    std::vector<std::string> getOwnerConsumptionVector();   //所有消耗物品列表
    
    //装备
    //通过字符串网络ID得到装备数据
    AccountEquipData getEquipDataWithStringID(std::string &strID);
    //通过整数id编号得到装备数据
    AccountEquipData getEquipDataWithIntID(int intID);
    
    //英雄
    //通过英雄字符串网络ID得到英雄相关所有数据
    AccountHeroData getHeroDataWithStringID(std::string &strID);
    //通过英雄整数编号网络ID得到英雄相关所有数据
    AccountHeroData getHeroDataWithStringID(int intID);
    
    //道具
    //通过道具字符串ID得到道具所有数据
    AccountStagePropData getStagePropDataWithStringID(std::string &strID);
    //通过道具整数编号ID得到道具所有数据
    AccountStagePropData getStagePropDataWithIntID(int intID);
    
    //阵容
    //获得玩家普通战斗阵容
    std::vector<std::string> getNomalLineupVector();
    //获得玩家竟技场阵容
    std::vector<std::string> getFightLineupVector();
    //获得玩家征战阵容
    std::vector<std::string> getZhenZhanLineupVector();
    
    
    //数据操作的有关方法
    //英雄装备
    //某个英雄使用某个装备
    void heroUsedOneEquip(int heroNetID,int equipNetID);
    //某个英雄一次装备数个装备
    void heroUserSomeEquip(int heroNetID,std::list<int> equipNetIDList);
    //获得某个英雄的可使用装备列表,列表为空，则说明无可使用装备，ID为负值则英雄等级不够
    std::list<int> getHeroCanUsedEquipList(int heroNetID);
    //获理某个英雄的某个装备位可使用装备
    int heroSpaceCanUsedEquip(int heroNetID,int spaceNumber);
    
    //装备与道具
    //分解某个装备,得到碎片或者尘
    std::list<int> ResolutionEquip(int equipNetID);
    //分解某个重复英雄，得到一定数量的英雄碎片
    int ResolutionHero(int heroNetID);
    //通过道具ID得到玩家当前道具的服务器ID,如果得到值为0,则说明玩家身上没有本道具
    int getNetIDFromStagePropID(int spID);
    //装备碎片合成装备
    bool SynthesisEquipWithFragment(int equipFragmentID);
    //合成新装备
    bool SynthesisEquipWithEquip(int newEquipID);
    //英雄碎片合成英雄
    bool SynthesisHero(int heroFragmentID);
    //使用消耗品
    bool ConsumptionUsed(int ConsumptionFragmentID);
    
    //资源使用
    //玩家使用宝石
    bool usedGem(int usedCount);
    //玩家使用金币
    bool usedGold(int usedGold);
    //玩家使用道具id和使用数量
    bool usedStageProp(int spID,int count);
    
    //阵容
    //普通战斗阵容改变
    void changeNomalLineup(std::list<int> lineupList);
    //竟技场阵容改变
    void changeFightLineup(std::list<int> lineupList);
    //征战阵容改变
    void changeZhenZhanLineup(std::list<int> lineupList);

    //资源观查者是否已注册
    bool isegisterUserDataChangeEventListen(UserDataEventType stateType,cocos2d::Ref* ins,Event_CallBackDic selector);
    //注册资源改变监听
    void registerUserDataChangeEventListen(UserDataEventType stateType,cocos2d::Ref* ins,Event_CallBackDic selector);
    //移除状态监听
    void unregisterUserDataChangeEventListen(UserDataEventType stateType,cocos2d::Ref* ins,Event_CallBackDic selector);
    //资源改变事件
    void onUserDataChangeEvent(UserDataEventType stateType);
    
    //网络回调方法
    virtual void reciveDataHandler(std::string &msg,int type,bool is_push = false);
    
    //网络状态改变回调
    void ClientNetStateChangeCallBack(std::string changetype,cocos2d::Ref* obj);
    
private:
    map<int,std::list<Ref*>> s_userDataObserver;
    __Dictionary* getChangeUserDataDicWithType(UserDataEventType stateType);
};

#endif /* defined(__game4__AccountDataManger__) */
