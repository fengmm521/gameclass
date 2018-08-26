//
//  SkillActionManger.cpp
//  game3
//
//  Created by 俊盟科技1 on 9/20/14.
//
//

#include "SkillActionManger.h"
#include "BaseSprite.h"
#include "WarScenceLayer.h"
static SkillActionManger *s_sharedSkillActionManger = nullptr;

SkillActionManger *SkillActionManger::sharedSkillActionManger()
{
    if (s_sharedSkillActionManger == nullptr)
    {
        s_sharedSkillActionManger = new SkillActionManger();
        if (!s_sharedSkillActionManger || !s_sharedSkillActionManger->init())
        {
            CC_SAFE_DELETE(s_sharedSkillActionManger);
        }
    }
    return s_sharedSkillActionManger;
}

void SkillActionManger::destroyInstance()
{
    
    CC_SAFE_RELEASE_NULL(s_sharedSkillActionManger);
}

SkillActionManger::SkillActionManger(void)
{
  
}
SkillActionManger::~SkillActionManger(void)
{
    hideskillArmatureMap.clear();
}
bool SkillActionManger::init()
{
    bool bRet = false;
    do
    {
        
        m_isSkillRun = false;
        
        hideskillArmatureMap.clear();
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}
//加载技能动画到内存
void SkillActionManger::loadSkillHide(string &ID)
{
    string s_strID = ID;
    if (hideskillArmatureMap[s_strID]) {
        return;
    }
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("skill/skillsjtx/"+s_strID+"/" + s_strID +"0.png","skill/skillsjtx/"+s_strID+"/" + s_strID + "0.plist","skill/skillsjtx/"+s_strID+"/" +s_strID + ".ExportJson");
    hideskillArmatureMap[s_strID] = true;
}
void SkillActionManger::unLoadSkillHide(string &ID)
{
    if (hideskillArmatureMap[ID]) {
        string s_strID = ID;
        cocostudio::ArmatureDataManager::getInstance()->removeArmatureFileInfo("skill/skillsjtx/"+s_strID+"/" +s_strID + ".ExportJson");
        hideskillArmatureMap[s_strID] = false;
        hideskillArmatureMap.erase(s_strID);
    }
    
}


//加载技能动画-----buff动画
void SkillActionManger::loadSkillBuff(string &ID)
{
    string s_strID = ID;
    if(hideskillArmatureMap[s_strID])
    {
        return;
    }
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("skill/skillbuff/"+s_strID+"/" + s_strID +"0.png","skill/skillbuff/"+s_strID+"/" + s_strID + "0.plist","skill/skillbuff/"+s_strID+"/" +s_strID + ".ExportJson");
    hideskillArmatureMap[s_strID] = true;
}
void SkillActionManger::unLoadSkillBuff(string &ID)
{
    if (hideskillArmatureMap[ID]) {
        string s_strID = ID;
        cocostudio::ArmatureDataManager::getInstance()->removeArmatureFileInfo("skill/skillsjtx/"+s_strID+"/" +s_strID + ".ExportJson");
        hideskillArmatureMap[s_strID] = false;
        hideskillArmatureMap.erase(s_strID);
    }
}
//加载技能动画-----子弹动画
void SkillActionManger::loadSkillBullet(string &ID)
{
    string s_strID = ID;
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("skill/skillbullet/"+s_strID+"/" + s_strID +"0.png","skill/skillbullet/"+s_strID+"/" + s_strID + "0.plist","skill/skillbullet/"+s_strID+"/" +s_strID + ".ExportJson");
    hideskillArmatureMap[s_strID] = true;
}
void SkillActionManger::unLoadSkillBullet(string &ID)
{
    if (hideskillArmatureMap[ID]) {
        string s_strID = ID;
        cocostudio::ArmatureDataManager::getInstance()->removeArmatureFileInfo("skill/skillbullet/"+s_strID+"/" +s_strID + ".ExportJson");
        hideskillArmatureMap[s_strID] = false;
        hideskillArmatureMap.erase(s_strID);
    }
}

void SkillActionManger::loadSprite(int ID)
{
    string s_strID = to_string(ID);
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("sprite/"+s_strID+"/" + s_strID +"0.png","sprite/"+s_strID+"/" + s_strID + "0.plist","sprite/"+s_strID+"/" +s_strID + ".ExportJson");
}
//释放动画内存
void SkillActionManger::unLoadSprite(int ID)
{
    string s_strID = to_string(ID);
    cocostudio::ArmatureDataManager::getInstance()->removeArmatureFileInfo("sprite/"+s_strID+"/" +s_strID + ".ExportJson");
}
//初始化战场时加载动画
void SkillActionManger::loadSkillHideWhenInitWar(list<string> IDList)
{
    while (!IDList.empty()) {
        string tmp = IDList.front();
        IDList.pop_front();
        this->loadSkillHide(tmp);
    }
}
void SkillActionManger::unLoadSkillHideWhenWarRealse(list<string> IDList)
{
    while(!IDList.empty())
    {
        string tmp = IDList.front();
        IDList.pop_front();
        this->unLoadSkillHide(tmp);
    }
}

void SkillActionManger::loadEffectAction(string &ID)
{
    string s_strID = ID;
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("skill/effect/"+s_strID+"/" + s_strID +"0.png","skill/effect/"+s_strID+"/" + s_strID + "0.plist","skill/effect/"+s_strID+"/" +s_strID + ".ExportJson");
}
void SkillActionManger::unLoadEffectAction(string &ID)
{
    string s_strID = ID;
    cocostudio::ArmatureDataManager::getInstance()->removeArmatureFileInfo("skill/effect/"+s_strID+"/" +s_strID + ".ExportJson");
}
void SkillActionManger::loadEffectWhenWarStart()//战斗开始时必须加载的效果
{
    string tmp ="tx_dianjizhou";
    this->loadEffectAction(tmp);
    tmp = "tx_miaozhunl";
    this->loadEffectAction(tmp);
    tmp = "tx_shifang";
    this->loadEffectAction(tmp);
    tmp = "tx_xiangzhong";
    this->loadEffectAction(tmp);
    tmp = "tx_shifang";
    this->loadEffectAction(tmp);
}
void SkillActionManger::unloadEffectWhenWarEnd()//战斗结束时移除效果
{
    string tmp ="tx_dianjizhou";
    this->unLoadEffectAction(tmp);
    tmp = "tx_miaozhunl";
    this->unLoadEffectAction(tmp);
    tmp = "tx_shifang";
    this->unLoadEffectAction(tmp);
    tmp = "tx_xiangzhong";
    this->unLoadEffectAction(tmp);
    tmp = "tx_shifang";
    this->unLoadEffectAction(tmp);
}

//初始化战场时加载游戏角色动画
void SkillActionManger::loadSpriteWhenInitWar(list<int> IDList)
{
    while (!IDList.empty()) {
        int tmp = IDList.front();
        IDList.pop_front();
        this->loadSprite(tmp);
    }
}
void SkillActionManger::unLoadSpriteWhenWarRealse(list<int> IDList)
{
    while(!IDList.empty())
    {
        int tmp = IDList.front();
        IDList.pop_front();
        this->unLoadSprite(tmp);
    }
}
void SkillActionManger::addPlaySkillSprite(BaseSprite* sp)
{
    m_skillPlayList.push_back(sp);
}
void SkillActionManger::playAllSkill()
{
    while (!m_skillPlayList.empty()) {
        BaseSprite* tmp = m_skillPlayList.front();
        m_skillPlayList.pop_front();
        tmp->playSkillActionEnd();
    }
}
bool SkillActionManger::isAddPlaySkill(BaseSprite* sp)
{
    for (list<BaseSprite*>::iterator it = m_skillPlayList.begin(); it != m_skillPlayList.end(); it++) {
        if ((*it) == sp) {
            return true;
        }
    }
    return false;
}

