//
//  Skill.h
//  game3
//  这个是创建一些基本的cocos2d类时会用到
//  Created by 俊盟科技1 on 10/13/14.
//
//

#ifndef __game3__Skill__
#define __game3__Skill__

#include "cocos2d.h"
#include "LocalDataManger.h"
#include "SpriteConfig.h"
using namespace cocos2d;

class WarScenceLayer;
class BaseSprite;
class Box2dSprite;
class SkillBullet;
class SkillAction:public Ref
{

public:
    ~SkillAction();
    int m_skillID;
    std::list<int> m_skillEffectIDList;
    WarScenceLayer* m_warlayer;
    
    Box2dSprite* m_Ower;
    BaseSprite* m_fromSp;
    SkillBullet* m_fromBullet;
    BaseSprite* m_toSp;
    
    Configtab_skill_visual_effectDataST m_skillDataST;
    
    bool isHero;
    
    SpriteWarDataST m_warDataST;
    
    int m_skillLeve;    //当前技能等级

    static SkillAction* createWithID(int ID);
    
    bool init();
    void playSkillEffectList();
    void setSkillData(Box2dSprite* skillOwner,WarScenceLayer* warLayer,int skillLeve);
    //技能数据初始化结速运行方法
    void whenInitSkillDataEnd();
    void runSkill(BaseSprite* Attacktarget);
    void setSkillData();
    list<BaseSprite*> getRandomTargetList();
};
#endif /* defined(__game3__Skill__) */
