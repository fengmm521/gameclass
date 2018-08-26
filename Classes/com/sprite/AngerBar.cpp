//
//  AngerBar.cpp
//  game1
//
//  Created by 俊盟科技1 on 8/20/14.
//
//

#include "AngerBar.h"
#include "BaseSprite.h"

AngerBar* AngerBar::create(BaseSprite* sp,int maxValue)
{
    AngerBar* tmp = new AngerBar();
    tmp->autorelease();
    tmp->s_OunerSprite = sp;
    tmp->m_maxValue = maxValue;
    tmp->init();
    return tmp;
}

bool AngerBar::init()
{
    //////////////////////////////
    // 1. super init first
    
    bool bRet = false;
    do
    {
        s_AngerSlider = nullptr;
        m_Anger = 0;
        bRet = true;
    }
    while (0);
    
    return bRet;
}


void AngerBar::addAngerWithType(int type)
{
    switch (type) {
        case e_nomalAttack:
            m_Anger += kAddAngerNomalAttack;
            
            if (m_Anger > m_maxValue) {
                m_Anger = m_maxValue;
            }
            
            break;
        case e_skillAttack:
            m_Anger += kAddAngerSkillAttack;
            if (m_Anger > m_maxValue) {
                m_Anger = m_maxValue;
            }
            break;
        case e_aoyiAttack:
            m_Anger += kAddAngerAoyiAttack;
            if (m_Anger > m_maxValue) {
                m_Anger = m_maxValue;
            }
            break;
        case e_kill:
            m_Anger += kAddAngerKill;
            if (m_Anger > m_maxValue) {
                m_Anger = m_maxValue;
            }
            break;
        case e_killSummon:
            m_Anger += kAddAngerKillSummon;
            if (m_Anger > m_maxValue) {
                m_Anger = m_maxValue;
            }
            break;
        case e_beAttack:
            m_Anger += kAddAngerBeAttack;
            if (m_Anger > m_maxValue) {
                m_Anger = m_maxValue;
            }
            break;
        default:
            return;
            break;
    }
    this->sendAngerChange();
}

void AngerBar::sendAngerChange()//通知与怒气相关技能怒气值改变
{
    
    if (!s_OunerSprite->m_isFaceRight) {
        log("boss enage = %d",m_Anger);
    }
    
    if (m_Anger == m_maxValue) {
        this->angerFull();
    }else{
        if (s_AngerSlider) {
            int per = (int)((m_Anger*100/m_maxValue));
            s_AngerSlider->setPercent(per);
        }
    }
}
void AngerBar::angerFull()//怒气值满了要运行的方法。
{
    if (s_AngerSlider) {
        s_AngerSlider->setPercent(100);
    }
    if(s_OunerSprite->m_isFaceRight)//下方友方技能可释放
    {
        if (!s_OunerSprite->isShowSKill) {
            s_OunerSprite->showSkillBtnUsedplayStart();
        }
    }else{//上方敌人技能可释放
        if (!s_OunerSprite->isShowSKill) {
            this->cleanAnger();
            s_OunerSprite->playEnemySkill();
        }
    }
}
bool AngerBar::isFull()
{
    return (m_Anger == m_maxValue);
}
void AngerBar::setAngerSlider(cocos2d::ui::LoadingBar* slider)
{
    s_AngerSlider = slider;
}

//能量增加
void AngerBar::addAngerWhenAttack()//普通攻击增加能量
{
    this->addAngerWithType(e_nomalAttack);
}
void AngerBar::addAngerWhenSkillAttack() //技能攻击增加能量
{
    this->addAngerWithType(e_skillAttack);
}
void AngerBar::addAngerWhenAoyiAttack() //奥义攻击时能量增加
{
    this->addAngerWithType(e_aoyiAttack);
}
void AngerBar::addAngerWhenKill()       //当击杀目标后能量增加
{
    this->addAngerWithType(e_kill);
}
void AngerBar::addAngerWhenKillSummon()  //当击杀了招换之后
{
    this->addAngerWithType(e_killSummon);
}
void AngerBar::addAngerWhenBeAttack()    //被攻击时增加能量
{
    this->addAngerWithType(e_beAttack);
}
void AngerBar::cleanAnger()
{
    m_Anger = 0;
    if (s_AngerSlider) {
        s_AngerSlider->setPercent(0);
    }
}