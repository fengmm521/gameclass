//
//  WarNetDataManger.cpp
//  game4
//
//  Created by Junpeng Zhang on 12/5/14.
//
//

#include "WarNetDataManger.h"

static WarNetDataManger *s_sharedWarNetDataManger = nullptr;

WarNetDataManger *WarNetDataManger::sharedWarNetDataManger()
{
    if (s_sharedWarNetDataManger == nullptr)
    {
        s_sharedWarNetDataManger = new WarNetDataManger();
        if (!s_sharedWarNetDataManger || !s_sharedWarNetDataManger->init())
        {
            CC_SAFE_DELETE(s_sharedWarNetDataManger);
        }
    }
    return s_sharedWarNetDataManger;
}

void WarNetDataManger::destroyInstance()
{
    
    CC_SAFE_RELEASE_NULL(s_sharedWarNetDataManger);
}

WarNetDataManger::WarNetDataManger(void)
{
  
}


WarNetDataManger::~WarNetDataManger(void)
{
   
}


bool WarNetDataManger::init()
{
    bool bRet = false;
    do
    {
        m_reopenWarLayer = false;
        m_isWaring = false;
        m_nowWarID = 400101;
        m_nowWarType = 1;
        m_userWarJQID = 400101;
        m_userWarJYID = 400201;
        m_userWarHDID = 0;
        
        //战斗奖利
        m_warWinGood.push_back(100001);
        m_warWinGood.push_back(100002);
        m_warWinGood.push_back(300001);
        m_warWinGold = 1250;
        m_warWinExp = 95;
        
        
//        ourheroVector.push_back(1008);
//        ourheroVector.push_back(1002);
//        ourheroVector.push_back(1012);
//        ourheroVector.push_back(1003);
//        ourheroVector.push_back(1010);测试用的几个英雄
        
        WarHeroData tmpdata1;
        tmpdata1.heroID = 1008;
        tmpdata1.leve = 1;
        tmpdata1.exp = 75;
        tmpdata1.pinzhi = 0;
        tmpdata1.star = 0;
        m_warHeroDataArr.push_back(tmpdata1);
        
        WarHeroData tmpdata2;
        tmpdata2.heroID = 1002;
        tmpdata2.leve = 1;
        tmpdata2.exp = 75;
        tmpdata2.pinzhi = 0;
        tmpdata2.star = 0;
        m_warHeroDataArr.push_back(tmpdata2);
        
        WarHeroData tmpdata3;
        tmpdata3.heroID = 1012;
        tmpdata3.leve = 1;
        tmpdata3.exp = 0;
        tmpdata3.pinzhi = 0;
        tmpdata3.star = 0;
        m_warHeroDataArr.push_back(tmpdata3);
        
        WarHeroData tmpdata4;
        tmpdata4.heroID = 1003;
        tmpdata4.leve = 1;
        tmpdata4.exp = 75;
        tmpdata4.pinzhi = 0;
        tmpdata4.star = 0;
        m_warHeroDataArr.push_back(tmpdata4);
        
        WarHeroData tmpdata5;
        tmpdata5.heroID = 1010;
        tmpdata5.leve = 1;
        tmpdata5.exp = 75;
        tmpdata5.pinzhi = 0;
        tmpdata5.star = 0;
        m_warHeroDataArr.push_back(tmpdata5);
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}
void WarNetDataManger::setIsWaring(bool isWar)
{
    m_isWaring = isWar;
}
bool WarNetDataManger::isWaring()
{
    return m_isWaring;
}

void WarNetDataManger::setNowWarID(int ID)
{
    m_nowWarID = ID;
}
int WarNetDataManger::getNowWarID()
{
    return m_nowWarID;
}

void WarNetDataManger::setNowWarType(int wartype)
{
    m_nowWarType = wartype;
}
int WarNetDataManger::getNowWarType()
{
    return m_nowWarType;
}

void WarNetDataManger::setUserWarJQID(int ID)
{
    m_userWarJQID = ID;
}
void WarNetDataManger::setUserWarJYID(int ID)
{
    m_userWarJYID = ID;
}
void WarNetDataManger::setUserWarHDID(int ID)
{
    m_userWarHDID = ID;
}

int WarNetDataManger::getUserWarJQID()
{
    return m_userWarJQID;
}
int WarNetDataManger::getUserWarJYID()
{
    return m_userWarJYID;
}
int WarNetDataManger::getUserWarHDID()
{
    return m_userWarHDID;
}

void WarNetDataManger::setWarWinGood(std::list<int> goodlist)
{
    m_warWinGood = goodlist;
}
void WarNetDataManger::setWarWinGold(int gold)
{
    m_warWinGold = gold;
}
void WarNetDataManger::setWarWinExp(int exp)
{
    m_warWinExp = exp;
}

std::list<int> WarNetDataManger::getWarWinGood()
{
    return m_warWinGood;
}
int WarNetDataManger::getWarWinGold()
{
    return m_warWinGold;
}
int WarNetDataManger::getWarWinExp()
{
    return m_warWinExp;
}

void WarNetDataManger::setWarHeroArr(std::vector<WarHeroData> warheroVector)
{
    m_warHeroDataArr = warheroVector;
}
std::vector<WarHeroData> WarNetDataManger::getWarHeroArr()
{
    return m_warHeroDataArr;
}

