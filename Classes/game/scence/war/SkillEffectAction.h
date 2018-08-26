//
//  SkillEffectAction.h
//  game3
//
//  Created by 俊盟科技1 on 11/5/14.
//
// 游戏界面
//
#ifndef __game3__SkillEffectAction__
#define __game3__SkillEffectAction__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;

class WarScenceLayer;
class BaseSprite;
class SkillEffectAction : public cocos2d::Layer
{
public:
    virtual bool init();
    // a selector callback
    static SkillEffectAction* createForScence(Layer* p);
    Layer* m_parent;
    ui::Text* fubeiDesText; //副本描述
    
    cocostudio::Armature* m_skillRunEffect;  //释放技能动画
    
    Sprite* m_heroIcon[5];
    Label* m_heroSkillName[5];
    bool m_iconruning[5];
    int m_runSkillCount;
    
    WarScenceLayer* m_warlayer; //战场
    

    void playSkillWithHero(BaseSprite* sp);
    
    virtual void onExit();
    virtual void onEnter();
    
private:
    void showHero(int number);
    void showNewHero(int number);
    int nowSkillNumber;
};
#endif /* defined(__game3__SkillEffectAction__) */
