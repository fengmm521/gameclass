//
//  AccountDataManger.cpp
//  game4
//
//  Created by Junpeng Zhang on 12/24/14.
//
//

#include "AccountDataManger.h"
#include "ClientSocketManger.h" //客户端网络请求单例类
#include "ObserverManger.h"

static AccountDataManger *s_sharedAccountDataManger = nullptr;

AccountDataManger *AccountDataManger::sharedAccountDataManger()
{
    if (s_sharedAccountDataManger == nullptr)
    {
        s_sharedAccountDataManger = new AccountDataManger();
        if (!s_sharedAccountDataManger || !s_sharedAccountDataManger->init())
        {
            CC_SAFE_DELETE(s_sharedAccountDataManger);
        }
    }
    return s_sharedAccountDataManger;
}

void AccountDataManger::destroyInstance()
{
    //删除观查者
    ObserverManger::shareObserverManger()->unregisterCallBackEvent("netstate",s_sharedAccountDataManger,event_callbackStr(AccountDataManger::ClientNetStateChangeCallBack));
    CC_SAFE_RELEASE_NULL(s_sharedAccountDataManger);
}

AccountDataManger::AccountDataManger(void)
{
  
}

AccountDataManger::~AccountDataManger(void)
{
   
}


bool AccountDataManger::init()
{
    bool bRet = false;
    do
    {
        //注册网络状态改变的观查着
        ObserverManger::shareObserverManger()->registerCallBackEvent("netstate", this, event_callbackStr(AccountDataManger::ClientNetStateChangeCallBack));
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

std::vector<std::string> AccountDataManger::getOwnerHeroVector()          //所有英雄列表
{
    std::vector<std::string> tmp;
    tmp.push_back("1001");
    return tmp;
}
std::vector<std::string> AccountDataManger::getOwnerStagePropVector()     //所有道具列表
{
    std::vector<std::string> tmp;
    tmp.push_back("1001");
    return tmp;
}
std::vector<std::string> AccountDataManger::getOwnerEquipFragmentVector() //所有装备碎片列表
{
    std::vector<std::string> tmp;
    tmp.push_back("1001");
    return tmp;
}
std::vector<std::string> AccountDataManger::getOwnerHeroFragmentVector()  //所有英雄碎片列表
{
    std::vector<std::string> tmp;
    tmp.push_back("1001");
    return tmp;
}
std::vector<std::string> AccountDataManger::getOwnerEquipVector()         //所有装备列表
{
    std::vector<std::string> tmp;
    tmp.push_back("1001");
    return tmp;
}
std::vector<std::string> AccountDataManger::getOwnerConsumptionVector()   //所有消耗物品列表
{
    std::vector<std::string> tmp;
    tmp.push_back("1001");
    return tmp;
}

//装备
//通过字符串网络ID得到装备数据
AccountEquipData AccountDataManger::getEquipDataWithStringID(std::string &strID)
{
    AccountEquipData tmp;
    return tmp;
}
//通过整数id编号得到装备数据
AccountEquipData AccountDataManger::getEquipDataWithIntID(int intID)
{
    AccountEquipData tmp;
    return tmp;
}

//英雄
//通过英雄字符串网络ID得到英雄相关所有数据
AccountHeroData AccountDataManger::getHeroDataWithStringID(std::string &strID)
{
    AccountHeroData tmp;
    return tmp;
}
//通过英雄整数编号网络ID得到英雄相关所有数据
AccountHeroData AccountDataManger::getHeroDataWithStringID(int intID)
{
    AccountHeroData tmp;
    return tmp;
}

//道具
//通过道具字符串ID得到道具所有数据
AccountStagePropData AccountDataManger::getStagePropDataWithStringID(std::string &strID)
{
    AccountStagePropData tmp;
    return tmp;
}
//通过道具整数编号ID得到道具所有数据
AccountStagePropData AccountDataManger::getStagePropDataWithIntID(int intID)
{
    AccountStagePropData tmp;
    return tmp;
}

//阵容
//获得玩家普通战斗阵容
std::vector<std::string> AccountDataManger::getNomalLineupVector()
{
    std::vector<std::string> tmp;
    tmp.push_back("1001");
    return tmp;
}
//获得玩家竟技场阵容
std::vector<std::string> AccountDataManger::getFightLineupVector()
{
    std::vector<std::string> tmp;
    tmp.push_back("1001");
    return tmp;
}
//获得玩家征战阵容
std::vector<std::string> AccountDataManger::getZhenZhanLineupVector()
{
    std::vector<std::string> tmp;
    tmp.push_back("1001");
    return tmp;
}


//数据操作的有关方法
//英雄装备
//某个英雄使用某个装备
void AccountDataManger::heroUsedOneEquip(int heroNetID,int equipNetID)
{
    
}
//某个英雄一次装备数个装备
void AccountDataManger::heroUserSomeEquip(int heroNetID,std::list<int> equipNetIDList)
{
    
}
//获得某个英雄的可使用装备列表,列表为空，则说明无可使用装备，ID为负值则英雄等级不够
std::list<int> AccountDataManger::getHeroCanUsedEquipList(int heroNetID)
{
    std::list<int> tmp;
    tmp.push_back(1);
    return tmp;
}
//获理某个英雄的某个装备位可使用装备
int AccountDataManger::heroSpaceCanUsedEquip(int heroNetID,int spaceNumber)
{
    return 0;
}

//装备与道具
//分解某个装备,得到碎片或者尘
std::list<int> AccountDataManger::ResolutionEquip(int equipNetID)
{
    std::list<int> tmp;
    tmp.push_back(1);
    return tmp;
}
//分解某个重复英雄，得到一定数量的英雄碎片
int AccountDataManger::ResolutionHero(int heroNetID)
{
    return 0;
}
//通过道具ID得到玩家当前道具的服务器ID,如果得到值为0,则说明玩家身上没有本道具
int AccountDataManger::getNetIDFromStagePropID(int spID)
{
    return 0;
}
//装备碎片合成装备
bool AccountDataManger::SynthesisEquipWithFragment(int equipFragmentID)
{
    return false;
}
//合成新装备
bool AccountDataManger::SynthesisEquipWithEquip(int newEquipID)
{
    return false;
}
//英雄碎片合成英雄
bool AccountDataManger::SynthesisHero(int heroFragmentID)
{
    return false;
}
//使用消耗品
bool AccountDataManger::ConsumptionUsed(int ConsumptionFragmentID)
{
    return false;
}

//资源使用
//玩家使用宝石
bool AccountDataManger::usedGem(int usedCount)
{
    return false;
}
//玩家使用金币
bool AccountDataManger::usedGold(int usedGold)
{
    return false;
}
//玩家使用道具id和使用数量
bool AccountDataManger::usedStageProp(int spID,int count)
{
    return false;
}

//阵容
//普通战斗阵容改变
void AccountDataManger::changeNomalLineup(std::list<int> lineupList)
{
    
}
//竟技场阵容改变
void AccountDataManger::changeFightLineup(std::list<int> lineupList)
{
    
}
//征战阵容改变
void AccountDataManger::changeZhenZhanLineup(std::list<int> lineupList)
{
    
}

//资源观查者是否已注册
bool AccountDataManger::isegisterUserDataChangeEventListen(UserDataEventType stateType,cocos2d::Ref* ins,Event_CallBackDic selector)
{
    std::list<cocos2d::Ref*> arr=s_userDataObserver[stateType];
    
    if(arr.empty())
    {
        return false;
        
    }else{
        for (std::list<cocos2d::Ref*>::iterator it = arr.begin(); it != arr.end(); it++) {
            EventCallBackDicVO* tmpfun = (EventCallBackDicVO*)(*it);
            if (tmpfun->m_target == ins && tmpfun->m_funf == selector) {
                return true;
            }
        }
    }
    return false;
}
//注册资源改变监听
void AccountDataManger::registerUserDataChangeEventListen(UserDataEventType stateType,cocos2d::Ref* ins,Event_CallBackDic selector)
{
    EventCallBackDicVO *fun=EventCallBackDicVO::initWithData(ins,selector);
    fun->retain();
    std::list<cocos2d::Ref*> arr=s_userDataObserver[stateType];
    
    if(arr.empty())
    {
        arr.push_back(fun);
        s_userDataObserver[stateType] = arr;
        
    }else{
        for (std::list<cocos2d::Ref*>::iterator it = arr.begin(); it != arr.end(); it++) {
            EventCallBackDicVO* tmpfun = (EventCallBackDicVO*)(*it);
            if (tmpfun->m_target == ins && tmpfun->m_funf == selector) {
                fun->release();
                return;
            }
        }
        arr.push_back(fun);
        s_userDataObserver[stateType] = arr;
    }
}
//移除状态监听
void AccountDataManger::unregisterUserDataChangeEventListen(UserDataEventType stateType,cocos2d::Ref* ins,Event_CallBackDic selector)
{
    if(s_userDataObserver.find(stateType) == s_userDataObserver.end())
    {
        return;
    }
    std::list<cocos2d::Ref*> refList = s_userDataObserver[stateType];
    if (refList.empty()) {
        return;
    }
    for (std::list<cocos2d::Ref*>::iterator it = refList.begin(); it != refList.end();)
    {
        EventCallBackDicVO* tmp = (EventCallBackDicVO*)(*it);
        if(tmp->m_target == ins && selector == tmp->m_funf){
            (*it)->release();
            it = refList.erase(it++);
        }else{
            ++it;
        }
    }
    
    s_userDataObserver[stateType].clear();
    s_userDataObserver[stateType] = refList;
}
//资源改变事件
void AccountDataManger::onUserDataChangeEvent(UserDataEventType stateType)
{
    std::list<cocos2d::Ref*> refList =s_userDataObserver[stateType];
    if(refList.empty())
    {
        return;
    }
    log("list size is=%d",(int)refList.size());
    for (std::list<cocos2d::Ref*>::iterator it = refList.begin(); it != refList.end(); it++) {
        EventCallBackDicVO* fun=(EventCallBackDicVO*)(*it);
        if(fun)
        {
            __Dictionary* dictmp = this->getChangeUserDataDicWithType(stateType);
            fun->execute(dictmp,this);
            dictmp->release();
        }
    }
}
__Dictionary* AccountDataManger::getChangeUserDataDicWithType(UserDataEventType stateType)
{
    __Dictionary* dic = __Dictionary::create();
    dic->retain();
//这里加入状态改变的数据,__Dictionary中可以保存作何继承自Ref的对象。这里可以发送数据到监听者
    switch (stateType) {
        case e_onHeroLeveUpChange://英雄升级事件,会改变玩家战斗力
        {
            
        }
            break;
        case e_onHeroStarUpChange://英雄升星事件
        {
            
        }
            break;
        case e_onHeroSynthesis://英雄合成
        {
            
        }
            break;
        case e_onHeroResolution://重复英雄分解
        {
            
        }
            break;
        case e_onHeroUsedEquip://英雄使用装备
        {
            
        }
            break;
        case e_onEquipSynthesis://装备合成
        {
            
        }
            break;
        case e_onEquipResolution://装备分解
        {
            
        }
            break;
        case e_onConsumptionUsed://消耗品使用
        {
            
        }
            break;
        case e_onNomalLineupChange://普通阵容改变
        {
            
        }
            break;
        case e_onFightLineupChange://竟技场阵容改变
        {
            
        }
            break;
        case e_onZhenZhanLineupChange://征战阵容改变
        {
            
        }
            break;
        case e_onEnageChange://战斗能量改变
        {
            
        }
            break;
        case e_onGoleOrGemChange://宝石或金币数量改变
        {
            
        }
            break;
        case e_onUserLeveUp://玩家升级事件
        {
            
        }
            break;
        case e_userBaseDataChange://玩家基本信息改变，名称，头像，公会等等。
        {
            
        }
            break;
        default:
        {
            
        }
            break;
    }
    return dic;
}
//网络发送消息的回调方法
void AccountDataManger::reciveDataHandler(std::string &msg,int type,bool is_push)
{
    if (is_push) {
        //服务器推送消息
        
    }else{
        //客户端请求消息
        
    }
}
void AccountDataManger::ClientNetStateChangeCallBack(std::string changetype,cocos2d::Ref* obj)
{
    if (changetype.compare("netstate") == 0) { //说明是网络状态改变的回调
        __String* tmpstr = dynamic_cast<__String*>(obj);
        int nettype = tmpstr->intValue();
        switch (nettype) {
            case 11:
            {
                log("CONNECT_SUCCEED:net state is change to %d",nettype);
            }
                break;
            case 12:
            {
                log("CONNECT_FAIL:net state is change to %d",nettype);
            }
                break;
            case 13:
            {
                log("DISCONNECT:net state is change to %d",nettype);
            }
                break;
                
            default:
                break;
        }
    }
}
