//
//  AngerBar.h
//  game1
//  精灵类，主要用来创建一些定制的精灵动画。
//  Created by 俊盟科技1 on 8/20/14.
//
//

#ifndef __game1__AngerBar__
#define __game1__AngerBar__

#include <iostream>
#include "WarConfig.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class BaseSprite;
//怒气条
class AngerBar:public cocos2d::Ref
{
private:
    int m_Anger; //怒气值
    int m_maxValue; //怒气上限
    BaseSprite* s_OunerSprite;
    cocos2d::ui::LoadingBar* s_AngerSlider;
public:
    
    static AngerBar* create(BaseSprite* spint,int maxValue = kMaxAnger);
    
    virtual bool init();
    
    void angerFull();//怒气值满了要运行的方法。
    
    //根据不同类型来增加怒气值，
    //1.普通攻击，100
    //2.技能攻击，100
    //3.奥义攻击，100
    //4.击杀1个目标，300
    //5,击杀一个召唤目标，100
    //6,被攻击，50
    //
    void addAngerWithType(int type);
    
    void sendAngerChange();//通知与怒气相关技能怒气值改变
    
    
    bool isFull();
    
    void setAngerSlider(cocos2d::ui::LoadingBar* slider);
    
    //能量增加
    void addAngerWhenAttack();//普通攻击增加能量
    void addAngerWhenSkillAttack(); //技能攻击增加能量
    void addAngerWhenAoyiAttack();  //奥义攻击时能量增加
    void addAngerWhenKill();        //当击杀目标后能量增加
    void addAngerWhenKillSummon();  //当击杀了招换之后
    void addAngerWhenBeAttack();    //被攻击时增加能量
    
    //技能释放后能量清空
    void cleanAnger();
    
};


#endif /* defined(__game1__AngerBar__) */
