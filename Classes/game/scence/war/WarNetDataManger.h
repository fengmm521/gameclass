//
//  WarNetDataManger.h
//  game4
//  C++单例类模板，非线程安全单例类，并且实例化后会常注内存
//
//  Created by Junpeng Zhang on 12/5/14.
//
//

#ifndef __game4__WarNetDataManger__
#define __game4__WarNetDataManger__

#include "cocos2d.h"
#include "WarConfig.h"
class BaseSprite;
class WarNetDataManger:public cocos2d::Ref
{
public:
    static WarNetDataManger* sharedWarNetDataManger();
    static void destroyInstance();
private:
	/**
     * @js ctor
     */
    WarNetDataManger(void);
    /**
     * @js NA
     * @lua NA
     */
    ~WarNetDataManger(void);
    
public:
    
    /**
     * Init WarNetDataManger
     */
    virtual bool init();
    
    void setIsWaring(bool isWar);
    bool isWaring();
    
    void setNowWarID(int ID);
    int getNowWarID();
    
    void setNowWarType(int wartype);
    int getNowWarType();
    
    
    void setUserWarJQID(int ID);
    void setUserWarJYID(int ID);
    void setUserWarHDID(int ID);
    
    int getUserWarJQID();
    int getUserWarJYID();
    int getUserWarHDID();
    
    void setWarWinGood(std::list<int> goodlist);
    void setWarWinGold(int gold);
    void setWarWinExp(int exp);
    
    std::list<int> getWarWinGood();
    int getWarWinGold();
    int getWarWinExp();
    
    
    void setWarHeroArr(std::vector<WarHeroData> warheroVector);
    std::vector<WarHeroData> getWarHeroArr();
    
    
    bool m_reopenWarLayer;
    
    
private:
    bool m_isWaring;   //玩家是否正在战斗中
    
    int m_nowWarID;   //当前战斗ID
    //当前战斗类型,1普通副本，2精英副本,3活动副本
    int m_nowWarType;
    
    int m_userWarJQID;   //玩家剧情战斗到达ID
    int m_userWarJYID;   //玩精英副本到达ID;
    int m_userWarHDID;   //玩家活动副本ID;
    
    
    std::list<int> m_warWinGood;  //战斗胜利奖利物品ID
    
    int m_warWinGold;             //战斗胜利奖利金币
    
    int m_warWinExp;              //战斗胜利奖利经验
    
    std::vector<WarHeroData> m_warHeroDataArr;//玩家战斗中的英雄数据

    
};

#endif /* defined(__game4__WarNetDataManger__) */
