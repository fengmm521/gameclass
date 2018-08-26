//
//  SkillBullet.cpp
//  game3
//
//  Created by 俊盟科技1 on 10/15/14.
//
//

#include "SkillBullet.h"
#include "BaseSprite.h"
#include "BaseSprite.h"
#include "LocalDataManger.h"
#include "Box2dConfig.h"
#include "Box2dWordManger.h"
//#include "ClassFromString.h"
#include "SkillAction.h"
#include "WarScenceLayer.h"
using namespace cocos2d;

SkillBullet::SkillBullet()
{
    
}
SkillBullet::~SkillBullet()
{
    
}
SkillBullet* SkillBullet::createSkillBullet(BaseSprite* fromSP,BaseSprite* toSP,Point* startPo,Point* toPo,int buttleID,int skillID,int skillLeve)
{
    SkillBullet* tmp = new SkillBullet();
    tmp->autorelease();
    tmp->m_fromSp = fromSP;
    tmp->m_toSp = toSP;
    tmp->m_startPoint = *startPo;
    tmp->m_endPoint = *toPo;
    tmp->m_skillID = skillID;
    tmp->m_ID = buttleID;
    tmp->m_skillLeve = skillLeve;
    tmp->init();
    return tmp;
}
bool SkillBullet::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Box2dSprite::init()) {
        return false;
    }
    
    bool bRet = false;
    do
    {
        m_warData = m_fromSp->m_warData;
        box2dSpriteType = kButtleBox2d;
        m_warLayer = m_fromSp->m_warLayer; //子弹所在战斗场景就是发射子弹角色所在场景
        //读取子弹数据表
        bulletDataST = LocalDataManger::sharedLocalDataManger()->getConfigtab_skill_trajectoryDataST(m_ID);
        track_type = bulletDataST.track_type;
        bullet_texture = bulletDataST.bullet_texture;
        m_moveSpeed = bulletDataST.speed;
        s_isMove = false;
        s_isMoveForBox2d = false;
        m_Direction = 0.0f; //初始方向都为向右
        this->initLocalAction();
        m_owerSkill = SkillAction::createWithID(m_skillID);
        m_owerSkill->setSkillData(this, m_warLayer, m_skillLeve);
        this->setVisible(false);

        bRet = true;
    }
    while (0);
    
    return bRet;
}
void SkillBullet::Attack()
{
    s_isMove = false;
    s_isMoveForBox2d = false;
    //选移除移动碰撞体字典
    this->cleanDieListion();
    this->removeBox2dBodyForButtle();
    if (m_toSp) {
        map<Box2dSprite*,b2Fixture*>::iterator it = m_toSp->s_fixtureMap.find(this);
        if (it != m_toSp->s_fixtureMap.end()) {
            m_toSp->s_fixtureMap.erase(it);
        }
        if (!m_toSp->s_isDie) {
            m_owerSkill->runSkill(m_toSp);
        }
    }else{
        m_owerSkill->runSkill(m_toSp);
    }

    this->playEndAction();

}
void SkillBullet::onEnter()
{
    Box2dSprite::onEnter();
}
void SkillBullet::onExit()
{
    Box2dSprite::onExit();
}

void SkillBullet::initLocalAction()
{
    armature = nullptr;
    m_buttleImageSp = nullptr;
    if (bulletDataST.track_sub_type == 1) {
        m_buttleImageSp = Sprite::createWithSpriteFrameName(bullet_texture);
        m_buttleImageSp->setRotation(m_Direction);
        this->addChild(m_buttleImageSp);
    }else if(bulletDataST.track_sub_type == 0)
    {
        armature = cocostudio::Armature::create(bulletDataST.bullet_texture);
        this->addChild(armature);
    }
}
void SkillBullet::addBox2dBodyForButtle()
{
    Box2dWordManger::sharedBox2dWordManger()->addBodyForInitButtle(this,kCollisionRadius);
}
void SkillBullet::removeBox2dBodyForButtle()
{
    this->s_b2body->SetLinearVelocity(b2Vec2(0.0f,0.0f));
    this->s_b2body->SetUserData(nullptr);
    Box2dWordManger::sharedBox2dWordManger()->delBodyFixture(s_b2body, getTag());
    
}
void SkillBullet::playEndAction()
{
    this->removeFromeWarScence();
}
void SkillBullet::removeFromeWarScence()
{
    m_warLayer->removeWarBullet(this);
}
void SkillBullet::bulletStartMove()
{
    
    this->setVisible(true);
    
    
    if (armature) {
        armature->getAnimation()->play("play");
    }
    if (!m_toSp->s_isDie) {
        
        this->addBox2dBodyForButtle();
        
        if (m_toSp->s_fixtureMap[this] == nullptr) {
            m_toSp->s_fixtureMap[this] =  Box2dWordManger::sharedBox2dWordManger()->addSpriteToWorldWithCollision(m_toSp, this);
        }else{
            m_toSp->s_b2body->DestroyFixture(m_toSp->s_fixtureMap[this]);
            map<Box2dSprite*,b2Fixture*>::iterator it = m_toSp->s_fixtureMap.find(this);
            if (it != m_toSp->s_fixtureMap.end()) {
                m_toSp->s_fixtureMap.erase(it);
            }
            m_toSp->s_fixtureMap[this] =  Box2dWordManger::sharedBox2dWordManger()->addSpriteToWorldWithCollision(m_toSp, this);
        }
        //    m_toSp->s_fixtureMap[this] =  Box2dWordManger::sharedBox2dWordManger()->addSpriteToWorldWithCollision(m_toSp, this);
        m_toSp->registerStateChangeEventListen(e_warDie, e_stateIn, this, event_callbackStr(SkillBullet::toSpriteDieCallBack));
        s_isMove = true;
        s_isMoveForBox2d = true;
    }else{
        this->removeFromeWarScence();
    }
}
//攻击的目标死亡监听
void SkillBullet::toSpriteDieCallBack(std::string name,Ref* sp)
{
    
    
    
    if(s_isMoveForBox2d){
        s_isMoveForBox2d = false;
        s_isMove = false;
        
        this->removeBox2dBodyForButtle();
        
    }
    
    this->m_toSp->unregisterStateChangeEventListen(e_warDie, e_stateIn, this, event_callbackStr(SkillBullet::toSpriteDieCallBack));
    
    if (m_toSp && !m_toSp->s_isDie) {
        m_toSp->s_b2body->DestroyFixture(m_toSp->s_fixtureMap[this]);
        map<Box2dSprite*,b2Fixture*>::iterator it = m_toSp->s_fixtureMap.find(this);
        if (it != m_toSp->s_fixtureMap.end()) {
            m_toSp->s_fixtureMap.erase(it);
        }
    }
    
    this->m_toSp = nullptr;
    //子弹的攻击目标死亡时，让子弹在0.3秒内消失
    FadeOut* faout = FadeOut::create(0.3f);
    CallFunc* func = CallFunc::create([=]()->void{
        this->removeFromeWarScence();
    });
    if (armature) {
        armature->getAnimation()->stop();
        armature->runAction(Sequence::create(faout,func, NULL));
    }
    if (m_buttleImageSp) {
        this->removeFromeWarScence();
    }
}
//清除角色死亡监听
void SkillBullet::cleanDieListion()
{
    if (this->m_toSp != nullptr) {
        this->m_toSp->unregisterStateChangeEventListen(e_warDie, e_stateIn, this, event_callbackStr(SkillBullet::toSpriteDieCallBack));
    }
}
