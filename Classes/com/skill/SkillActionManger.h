//
//  SkillActionManger.h
//  game3
//  C++单例类模板，非线程安全单例类，并且实例化后会常注内存
//
//  Created by 俊盟科技1 on 9/20/14.
//
//

#ifndef __game3__SkillActionManger__
#define __game3__SkillActionManger__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class BaseSprite;
class WarScenceLayer;
using namespace std;
class SkillActionManger:public cocos2d::Ref
{
public:
    static SkillActionManger* sharedSkillActionManger();
    static void destroyInstance();
private:
	/**
     * @js ctor
     */
    SkillActionManger(void);
    /**
     * @js NA
     * @lua NA
     */
    ~SkillActionManger(void);
    
public:
    
    /**
     * Init SkillActionManger
     */
    //技能属性
    //受击动画
    map<string,bool> hideskillArmatureMap;
    
    virtual bool init();
    //加载技能动画-----受击动画,播放使用play
    void loadSkillHide(string &ID);
    void unLoadSkillHide(string &ID);
    //加载技能动画-----buff动画,播放使用play
    void loadSkillBuff(string &ID);
    void unLoadSkillBuff(string &ID);
    //加载技能动画-----子弹动画,播放使用play
    void loadSkillBullet(string &ID);
    void unLoadSkillBullet(string &ID);
    //加载效果动画-----战斗效果动画,播放使用play
    void loadEffectAction(string &ID);
    void unLoadEffectAction(string &ID);
    void loadEffectWhenWarStart();//战斗开始时必须加载的效果
    void unloadEffectWhenWarEnd();//战斗结束时移除效果
    //
    void loadSprite(int ID);
    //释放动画内存
    void unLoadSprite(int ID);
    //初始化战场时加载技能动画
    void loadSkillHideWhenInitWar(list<string> IDList);
    void unLoadSkillHideWhenWarRealse(list<string> IDList);
    //初始化战场时加载游戏角色动画
    void loadSpriteWhenInitWar(list<int> IDList);
    void unLoadSpriteWhenWarRealse(list<int> IDList);
    
    bool m_isSkillRun;
    std::list<BaseSprite*> m_skillPlayList;
    void addPlaySkillSprite(BaseSprite* sp);
    bool isAddPlaySkill(BaseSprite* sp);
    void playAllSkill();
};

#endif /* defined(__game3__SkillActionManger__) */
