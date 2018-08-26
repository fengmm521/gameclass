//
//  BloodBar.h
//  game1
//  精灵类，主要用来创建一些定制的精灵动画。
//  Created by 俊盟科技1 on 8/20/14.
// 血条
//

#ifndef __game1__BloodBar__
#define __game1__BloodBar__

#include <iostream>

#include "cocos2d.h"
#include "BloodNumber.h"
#include "BaseSprite.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
class BloodBar:public cocos2d::Sprite
{
private:
    bool s_isGree;
    BaseSprite* s_targetSp;
    Sprite *bgSprite;//血条底
    Sprite *hpSprite;//血条
    ui::LoadingBar* s_bloodSlider;
public:
    int m_blood; //血量显示值
    int m_realBlood; //真实血量值
    float m_barPercent; //血量条显示百分比
    int m_maxBlood;
    
    
    cocos2d::ProgressTimer* progressTimer;
    
    void setBloodSlider(ui::LoadingBar* slider);
    
public:
    
    //创建一个红色血条，血量值，血条所属精灵对象
    static BloodBar* createBarRed(int maxValue,BaseSprite* target);
    //创建一个绿色血条，血量值，血条所属精灵对象
    static BloodBar* createBarGree(int maxValue,BaseSprite* target);
    
    virtual bool init();
    
    //被攻击掉血
    void attackBloodSub(int subValue,bool isBaoJi = false);
    //攻击被闪避
    void attackFinding();
    //加血
    void addBloodValue(int addValue);
    
    void cleanBloodWhenDie();
    
private:
    void bloodDie();//血条空血角色死亡
};


#endif /* defined(__game1__BloodBar__) */
