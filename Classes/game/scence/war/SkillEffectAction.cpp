//
//  SkillEffectAction.cpp
//  game3
//
//  Created by 俊盟科技1 on 11/5/14.
//
//

#include "SkillEffectAction.h"
#include "cocostudio/CocoStudio.h"
#include "strHash.h"
#include "WarScenceLayer.h"
#include "BaseSprite.h"
#include "SkillActionManger.h"
using namespace cocos2d;
// on "init" you need to initialize your instance
SkillEffectAction* SkillEffectAction::createForScence(Layer* p)
{
    SkillEffectAction* tmp = new SkillEffectAction();
    tmp->autorelease();
    tmp->m_warlayer = (WarScenceLayer*)p;
    tmp->init();
    return tmp;
}
bool SkillEffectAction::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    do
    {
        //tx_shifang
        m_skillRunEffect = cocostudio::Armature::create("tx_shifang");
        this->addChild(m_skillRunEffect);

        for (int i = 0; i < 5; i++) {
            m_heroIcon[i] = Sprite::create();
            m_heroIcon[i]->setPosition(Point(-460,25));
            m_heroSkillName[i] = Label::createWithTTF("", "mnjzy2.TTF", 80.0f,Size::ZERO,TextHAlignment::LEFT);
            m_heroSkillName[i]->setColor(Color3B(255,191,91));
            m_heroSkillName[i]->enableShadow();
//            m_heroSkillName[i]->setPosition(Point(400.0f,100.0f));
//            m_heroIcon[i]->addChild(m_heroSkillName[i]);
            m_heroSkillName[i]->setPosition(Point(-180,0));
            this->addChild(m_heroSkillName[i]);
            this->addChild(m_heroIcon[i]);
        }
        m_runSkillCount = 0;
    }while (0);
    return true;
}

void SkillEffectAction::playSkillWithHero(BaseSprite* sp)
{
    //m_heroIcon->setTexture("");
    //half_number.png
        std::string iconname = "skill/effect/half_" + to_string(sp->m_ID) + ".png";
        //m_nowRunSkillSp = sp;
        if (m_skillRunEffect->getAnimation()->isPlaying()) {
            if (m_iconruning[0]) {
                if (m_iconruning[1]) {
                    if (m_iconruning[2]) {
                        if (m_iconruning[3]) {
                            //icon5
                            
                            m_heroIcon[4]->setTexture(iconname);
                            m_heroSkillName[4]->setString(sp->m_skillDataST[0].skill_name);
                            if (!m_heroIcon[4]->isVisible()) {
                                m_heroIcon[4]->setVisible(true);
                                m_heroSkillName[4]->setVisible(true);
                            }
                            m_runSkillCount++;
                            m_iconruning[4] = true;
                            this->showHero(4);
                        }else{
                            //icon4
                            
                            m_heroIcon[3]->setTexture(iconname);
                            m_heroSkillName[3]->setString(sp->m_skillDataST[0].skill_name);
                            if (!m_heroIcon[3]->isVisible()) {
                                m_heroIcon[3]->setVisible(true);
                                m_heroSkillName[3]->setVisible(true);
                            }
                            m_runSkillCount++;
                            m_iconruning[3] = true;
                            this->showHero(3);
                        }
                    }else{
                        //icon3
                        
                        m_heroIcon[2]->setTexture(iconname);
                        m_heroSkillName[2]->setString(sp->m_skillDataST[0].skill_name);
                        if (!m_heroIcon[2]->isVisible()) {
                            m_heroIcon[2]->setVisible(true);
                            m_heroSkillName[2]->setVisible(true);
                        }
                        m_runSkillCount++;
                        m_iconruning[2] = true;
                        this->showHero(2);
                    }
                }else{
                    //icon2
                    
                    m_heroIcon[1]->setTexture(iconname);
                    m_heroSkillName[1]->setString(sp->m_skillDataST[0].skill_name);
                    if (!m_heroIcon[1]->isVisible()) {
                        m_heroIcon[1]->setVisible(true);
                        m_heroSkillName[1]->setVisible(true);
                    }
                    m_runSkillCount++;
                    m_iconruning[1] = true;
                    this->showHero(1);
                }
            }else{
                //icon1
            }
        }else{
            m_skillRunEffect->getAnimation()->play("play");
            m_heroIcon[0]->setTexture(iconname);
            m_heroIcon[0]->setPosition(-460,25);
            m_heroSkillName[0]->setString(sp->m_skillDataST[0].skill_name);
            m_heroSkillName[0]->setPosition(-180,0);
            if (!m_heroIcon[0]->isVisible()) {
                m_heroIcon[0]->setVisible(true);
                m_heroSkillName[0]->setVisible(true);
            }
            m_runSkillCount = 1;
            nowSkillNumber = 0;
            this->showHero(0);
            m_iconruning[0] = true;
            m_iconruning[1] = false;
            m_iconruning[2] = false;
            m_iconruning[3] = false;
            m_iconruning[4] = false;
            m_heroIcon[1]->setPosition(-460,25);
            m_heroIcon[2]->setPosition(-460,25);
            m_heroIcon[3]->setPosition(-460,25);
            m_heroIcon[4]->setPosition(-460,25);
            m_heroSkillName[1]->setPosition(-180,0);
            m_heroSkillName[2]->setPosition(-180,0);
            m_heroSkillName[3]->setPosition(-180,0);
            m_heroSkillName[4]->setPosition(-180,0);
        }
    
}
void SkillEffectAction::showHero(int number)
{
    if (number > 0) {
        nowSkillNumber = number;
        m_heroIcon[number-1]->stopAllActions();
        
        MoveTo* movebyremove = MoveTo::create(0.2f,Point(460,25)); //545
        CallFunc* func = CallFunc::create([=]()->void{
            //this->m_warlayer->hideMaskLayer();
            this->m_runSkillCount--;
            this->m_heroIcon[number-1]->setVisible(false);
            if (this->m_runSkillCount == 0) {
                this->setVisible(false);
                this->m_skillRunEffect->getAnimation()->stop();
                this->m_warlayer->hideMaskLayer();
                SkillActionManger::sharedSkillActionManger()->playAllSkill();
                for(int i = 0;i <5;i++)
                {
                    m_iconruning[i] = false;
                }
            }
        });
        m_heroIcon[number-1]->runAction(Sequence::create(movebyremove,DelayTime::create(0.1f),func,NULL));
        
        
        //number
        MoveBy* moveby1 = MoveBy::create(0.2f, Point(250,0));
        MoveBy* moveByDe1  = MoveBy::create(1.2f,Point(100,0));
        MoveBy* movebyremove1 = MoveBy::create(0.2f,Point(570,0)); //545
        
        CallFunc* func1 = CallFunc::create([=]()->void{
            //this->m_warlayer->hideMaskLayer();
            this->m_runSkillCount--;
            this->m_heroIcon[number]->setVisible(false);
            if (this->m_runSkillCount == 0) {
                this->setVisible(false);
                this->m_skillRunEffect->getAnimation()->stop();
                this->m_warlayer->hideMaskLayer();
                SkillActionManger::sharedSkillActionManger()->playAllSkill();
                for(int i = 0;i <5;i++)
                {
                    m_iconruning[i] = false;
                }
            }
        });
        m_heroIcon[number]->runAction(Sequence::create(moveby1,moveByDe1,movebyremove1,DelayTime::create(0.1f),func1,NULL));
        
        
        //暂时做法
        m_heroSkillName[number-1]->stopAllActions();
        
        MoveTo* movebyremove2 = MoveTo::create(0.2f,Point(460,0)); //545
        CallFunc* func2 = CallFunc::create([=]()->void{
            this->m_heroSkillName[number-1]->setVisible(false);
        });
        m_heroSkillName[number-1]->runAction(Sequence::create(movebyremove2,DelayTime::create(0.1f),func2,NULL));
        
        
        //number
        MoveBy* moveby3 = MoveBy::create(0.2f, Point(250,0));
        MoveBy* moveByDe3  = MoveBy::create(1.2f,Point(100,0));
        MoveBy* movebyremove3 = MoveBy::create(0.2f,Point(570,0)); //545
        
        CallFunc* func3 = CallFunc::create([=]()->void{
            this->m_heroSkillName[number]->setVisible(false);
        });
        m_heroSkillName[number]->runAction(Sequence::create(moveby3,moveByDe3,movebyremove3,DelayTime::create(0.1f),func3,NULL));
        
        
    }else{
        MoveBy* moveby = MoveBy::create(0.2f, Point(250,0));
        MoveBy* moveByDe  = MoveBy::create(1.2f,Point(100,0));
        MoveBy* movebyremove = MoveBy::create(0.2f,Point(570,0)); //545
        
        CallFunc* func = CallFunc::create([=]()->void{
            //this->m_warlayer->hideMaskLayer();
            this->m_runSkillCount--;
            this->m_heroIcon[number]->setVisible(false);
            if (this->m_runSkillCount == 0) {
                this->setVisible(false);
                this->m_skillRunEffect->getAnimation()->stop();
                this->m_warlayer->hideMaskLayer();
                SkillActionManger::sharedSkillActionManger()->playAllSkill();
                for(int i = 0;i <5;i++)
                {
                    m_iconruning[i] = false;
                }
            }
        });
        m_heroIcon[number]->runAction(Sequence::create(moveby,moveByDe,movebyremove,DelayTime::create(0.1f),func,NULL));
        
        MoveBy* moveby2 = MoveBy::create(0.2f, Point(250,0));
        MoveBy* moveByDe2  = MoveBy::create(1.2f,Point(100,0));
        MoveBy* movebyremove2 = MoveBy::create(0.2f,Point(570,0)); //545
        
        CallFunc* func2 = CallFunc::create([=]()->void{
            this->m_heroSkillName[number]->setVisible(false);
        });
        m_heroSkillName[number]->runAction(Sequence::create(moveby2,moveByDe2,movebyremove2,DelayTime::create(0.1f),func2,NULL));
    }
}
void SkillEffectAction::showNewHero(int number)
{
    
}
void SkillEffectAction::onExit()
{
    
    Layer::onExit();
}
void SkillEffectAction::onEnter()
{
    Layer::onEnter();
    
}
