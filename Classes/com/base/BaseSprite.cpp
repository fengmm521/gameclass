//
//  BaseSprite.cpp
//  game1
//
//  Created by 俊盟科技1 on 8/20/14.
//
// 1001 ＝ tab_checkpoints_sys
// ConfigTable1001DataS_ = Configtab_checkpoints_sysDataST
// 1002 = tab_skill_visual_effect
// ConfigTable1002DataS_ = Configtab_skill_visual_effectDataST
// 1003 = tab_skill_effect
// ConfigTable1003DataS_ = Configtab_skill_effectDataST
// 1004 = tab_skill_trajectory
// ConfigTable1004DataS_ = Configtab_skill_trajectoryDataST
// 1005 = tab_skill_upgrade
// ConfigTable1005DataS_ = Configtab_skill_upgradeDataST
// 1006 = tab_card_attribute_sys
// ConfigTable1006DataS_ = Configtab_card_attribute_sysDataST
// 1007 = tab_card_star_sys
// Configtab_card_star_sysDataST = Configtab_card_star_sysDataST
// 1008 = tab_card_quality_sys
// ConfigTable1008DataS_ = Configtab_card_quality_sysDataST
// 1009 = tab_equipbase_sys
// ConfigTable1009DataS_ = Configtab_equipbase_sysDataST
// 1010 = tab_item_base_sys
// ConfigTable1010DataS_ = Configtab_item_base_sysDataST
#include "BaseSprite.h"
#include "GameViewConfig.h"
#include "BloodBar.h"
#include "StrSplit.h"
#include "strHash.h"
#include "WarScenceLayer.h"
#include "external/Box2d/Box2D.h"
#include "Box2dWordManger.h"
#include "SkillBullet.h"
#include "WarLayerBase.h"
#include "SkillActionManger.h"
#include "AStarMap6SideManger.h"
//#include "Skill.h"
#include "SkillAction.h"
#define kUpdataFindAttackSp   0.01f    //当敌方精灵为寻找可攻击目标时，每过0.2f时间寻找一次地图
#define kUpdateMoveSp         0.1f
#define tFacetext 1

#define kRunSkillScale   1.25f

using namespace cocostudio;
using namespace std;

BaseSprite* BaseSprite::createWithID(int ID,WarScenceLayer* warLayer,bool isFaceRight,int spLeve,int skillleve1,int skillleve2,int skillleve3,int skillleve4,int skillleve5,int skillleve6)
{
    BaseSprite* tmp = new BaseSprite();
    tmp->autorelease();
    tmp->m_warLayer = warLayer;
    tmp->m_ID = ID;
    tmp->m_warData.s_leve = spLeve;
    tmp->m_isFaceRight = isFaceRight;
    tmp->m_skillLeve[0] = skillleve1;
    tmp->m_skillLeve[1] = skillleve2;
    tmp->m_skillLeve[2] = skillleve3;
    tmp->m_skillLeve[3] = skillleve4;
    tmp->m_skillLeve[4] = skillleve5;
    tmp->m_skillLeve[5] = skillleve6;
    
    tmp->init();
    return tmp;
}
void BaseSprite::onExit()
{
    m_angerBar->release();
//    if (m_skill[0]) {
//        m_skill[0]->release();
//    }
//    if (m_skill[1]) {
//        m_skill[1]->release();
//    }
//    if (m_skill[2]) {
//        m_skill[2]->release();
//    }
//    if (m_skill[3]) {
//        m_skill[3]->release();
//    }
//    if (m_skill[4]) {
//        m_skill[4]->release();
//    }
//    if (m_skill[5]) {
//        m_skill[5]->release();
//    }
    
    Box2dSprite::onExit();
}
void BaseSprite::onEnter()
{
    Box2dSprite::onEnter();
    //
}

bool BaseSprite::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Box2dSprite::init()) {
        return false;
    }
    bool bRet = false;
    do
    {
        s_spriteObserver.clear();
        s_spriteType = e_null;              //初始化精灵状态为未设置状态
        s_stateInOrOut = e_stateNull;       //初始化为未设置状态
        s_stateShow = 0;
        s_b2WordManger = Box2dWordManger::sharedBox2dWordManger();
        s_isMoveForBox2d = false;
        
        m_nowPlayAction = -1;    //初始化时未播放动画
//        m_poisonValue = 0;       //初始化中毒技能效果值为0
        
        isNoSkill = false;
        
        //技能序列
        m_attackPCount = 0;
        m_nowAttackPCount = 0;
        m_isFirstAttackSkill = true;
        for (int i = 0; i < 6; i++) {
            m_firstAttackSkillArr[i] = -1;
            m_nomalAttackSkillArr[i] = -1;
        }
        
        
        
        this->loadNetData();      //初始化网络数据
        this->loadLocalData();    //初始化角色属性
        
        isSkillCanStop = false;   //初始化技能可打断为否
        
        this->initALLSkill();     //初始化技能
        this->initBaseAction();   //初始化基本动画
        
        //初始化血条
        if (m_isFaceRight) {//是我方角色，面向右,血条为绿色
            m_bloodBar = BloodBar::createBarGree(s_bloodValue,this);
            m_bloodBar->setPosition(Vec2(0,150));
            this->addChild(m_bloodBar);
        }else{//敌方角色，面向左，血条为红色
            m_bloodBar = BloodBar::createBarRed(s_bloodValue, this);
            m_bloodBar->setPosition(Vec2(0,150));
            this->addChild(m_bloodBar);
        }
        if (m_isFaceRight) {
            this->setFaceRight();
        }else{
            this->setFaceLeft();
        }
        bRet = true;
    }
    while (0);
    
    return bRet;
}
//数据
void BaseSprite::loadNetData()
{
    
}

void BaseSprite::loadLocalData()
{
    isSkillPaused = false;
    s_isDie = false;                        //初始化时精灵未死亡
    m_nowSkillNumber = 2;                   //初始化攻击为普通攻击
    box2dSpriteType = kSpriteBox2d;
    isShowSKill = false;
    isSkillRun = false;
    isPlayStart = false;
    isTouchMove = false;    //初始化点击移动设置为未移动
    //技能生命
    isChangeBody = false;  //当前是否变身状态
    changeBodyOldID = m_ID;     //变身之后的骨骼动画ID
    changeBodyarmature = nullptr; //变身之后的骨骼动画
    s_arrackRangeFixture = nullptr;
    m_isSkillButtonTouched = false;
    
    m_heroDataST = LocalDataManger::sharedLocalDataManger()->getConfigtab_card_attribute_sysDataST(m_ID);
    this->initHeroSkillAttackList();
    this->initHeroWarData();

    //log("sprite name ==%s,id==%d, blood =======%d",m_heroDataST.hero_name.c_str(),m_ID, s_bloodValue);
    if (m_isFaceRight)
    {
        s_spriteSpaceType = e_OurHero;
    }else{
        s_spriteSpaceType = e_EnemyHero;
    }
    //角色综合战斗力算法
    //(力量+智力+敏捷)+附加气血*0.06+附加物理攻击*1+附加魔法强度*1+附加护甲*0.04+附加魔抗*0.05+附加物理暴击*0.06+生命恢复*0.06+能量恢复*0.18+闪避*0.06
    //角色能量条
    m_angerBar = AngerBar::create(this);
    m_angerBar->retain();
}
void BaseSprite::initHeroSkillAttackList()
{
    std::vector<std::string> tmpx3 = StrSplit::split(m_heroDataST.hero_skillrelease_rule, ";");
    int count = (int)tmpx3.size();
    for (int i = 0; i < count; i++) {
        switch (i) {
            case 0:
            {
                std::vector<std::string> tmpxx = StrSplit::split(tmpx3[i], ",");
                int countj = (int)tmpxx.size();
                for (int j = 0; j < countj; j++) {
                    m_firstAttackSkillArr[j] = atoi(tmpxx[j].c_str()) - 1;//数组是从0开始
                }
            }
                break;
            case 1:
            {
                std::vector<std::string> tmpxx = StrSplit::split(tmpx3[i], ",");
                int countj = (int)tmpxx.size();
                for (int j = 0; j < countj; j++) {
                    m_nomalAttackSkillArr[j] = atoi(tmpxx[j].c_str()) - 1;//数组是从0开始
                }
            }
                break;
            default:
                break;
        }
    }
}
//初始化英雄战斗数据
void BaseSprite::initHeroWarData()
{
    //星级成长数据
    Configtab_card_star_sysDataST tabData1007 = LocalDataManger::sharedLocalDataManger()->getConfigtab_card_star_sysDataST(m_heroDataST.star_quene);
    //英雄星级成长系数
    float strengthUp = 1.0f;
    float intelligenceUp = 1.0f;
    float agileUp = 1.0f;
    switch (m_heroDataST.hero_star) {
        case 0://1星
        {
            strengthUp = tabData1007.one_star_power_grow;
            intelligenceUp = tabData1007.one_star_mental_grow;
            agileUp = tabData1007.one_star_agile_grow;
        }
            break;
        case 1://2星
        {
            strengthUp = tabData1007.two_star_power_grow;
            intelligenceUp = tabData1007.two_star_mental_grow;
            agileUp = tabData1007.two_star_agile_grow;
        }
            break;
        case 2://3星
        {
            strengthUp = tabData1007.three_star_power_grow;
            intelligenceUp = tabData1007.three_star_mental_grow;
            agileUp = tabData1007.three_star_agile_grow;
        }
            break;
        case 3://4星
        {
            strengthUp = tabData1007.four_star_power_grow;
            intelligenceUp = tabData1007.four_star_mental_grow;
            agileUp = tabData1007.four_star_agile_grow;
        }
            break;
        case 4://5星
        {
            strengthUp = tabData1007.five_star_power_grow;
            intelligenceUp = tabData1007.five_star_mental_grow;
            agileUp = tabData1007.five_star_agile_grow;
        }
            break;
        default:
            break;
    }
    
    //1008品质数据表
    Configtab_card_quality_sysDataST tabData1008 = LocalDataManger::sharedLocalDataManger()->getConfigtab_card_quality_sysDataST(m_heroDataST.hero_quality+8000);
    
    m_warData.s_strength = (int)(m_heroDataST.hero_power+tabData1008.hero_power_add+strengthUp*(m_warData.s_leve-1));
    m_warData.s_intelligence = (int)(m_heroDataST.mental + tabData1008.mental_add + intelligenceUp*(m_warData.s_leve-1));
    m_warData.s_agile = (int)(m_heroDataST.agile + tabData1008.agile_add+agileUp*(m_warData.s_leve-1));
    
    //通过英雄的力量，智力，敏捷初始化英雄的生命
    //计算公式
    //属性换算
    //    生命=力量*16+敏捷*4 + 品质增加生命
    s_bloodValue = m_warData.s_strength*16 + m_warData.s_agile*4 + tabData1008.hero_hp_add;
    //    物攻=力量+敏捷*0.4 ＋ 品质增加物攻强度
    m_warData.s_attack = (int)(m_warData.s_strength + m_warData.s_agile*0.4f) + tabData1008.physics_act_add;
    //    物防=力量*0.6+敏捷*0.3 + 品质增加物防强度
    m_warData.s_Defense = (int)(m_warData.s_strength*0.6f + m_warData.s_agile*0.3f) + tabData1008.armor_add;
    //    法攻=智力*2 + 品质增加法攻强度
    m_warData.s_magicAttack = (int)(2.0f*m_warData.s_intelligence) + tabData1008.magic_strength_add;
    //    法防=智力*1 + 品质增加法防强度
    m_warData.s_magicDefense = (int)(m_warData.s_intelligence) + tabData1008.magic_resist_add;
    //    暴击=敏捷*1.0+力量*0.3 + 品质增加暴击
    m_warData.s_BaoJiProbability = (float)(m_warData.s_agile + 0.3f*m_warData.s_strength) + tabData1008.physics_act_add;
    //闪避 = 品质增加＋装备增加
    m_warData.s_evade = 0 + tabData1008.hero_evade_add;
    
    //    	附伤减伤通过装备获得
    //伤害及暴击闪避公式如下表
    //    公式计算
    //    物理伤害=物攻*[1-（物防*0.06）/（1+物防*0.06）]
    //    技能伤害=物伤+法攻*0.1+技能附加伤害-法防*10
    //    暴击判断=攻方暴击/（守方暴击+攻方暴击）
    //    命中判断=1-对方闪避/[（对方闪避+我方闪避）*3]
    //    生命=力量*16+敏捷*4
    //    物理攻击=主属性*1+0.5*敏捷
    //    法术强度=法强*2
    //    护甲=力量*0.6+敏捷*0.3
    //    暴击=敏捷*1+力量*0.3
    //    魔抗=智力*1
    //    暴击率=我方暴击等级/(1.5*暴击等级+对方等级+对方暴击等级)
    //    伤害命中判断=1-（敌方闪避/（（我方闪避+敌方闪避+1））*3）
    //
    //    吸血比率:	吸血等级/(吸血等级+500+目标等级)
    //    治疗效果提升:	治疗*(1+提升)
    //    护甲穿透	护甲-穿透
    //    技能伤害	攻击*a+技能初始伤害*b+技能附加*c
    //    忽视魔抗	魔抗-忽视
    //    魔法伤害	伤害^2/(伤害+0.5*魔抗)
    //    暴击率	我方暴击等级/(1.5*暴击等级+对方等级+对方暴击等级)
    //    物理伤害	伤害^2/(伤害+0.5*护甲)
    //    命中判断	1-（敌方闪避/（（我方闪避+敌方闪避+1））*3）
    //
    //    (力量+智力+敏捷)+附加气血*0.08+附加物理攻击*1+附加魔法强度*1+附加护甲*0.08+附加魔抗*0.06+附加物理暴击*0.06+生命恢复*0.08+能量恢复*0.18+闪避*0.06
    
}

void BaseSprite::removeFromeWarScence()
{
    switch (s_spriteSpaceType) {
        case e_OurHero://亡的是我方英雄
            m_warLayer->m_ourHeroVector[m_spaceNumber] = nullptr;
            m_warLayer->ourSpCount--;
            break;
        case e_EnemyHero://亡的是敌方英雄
            m_warLayer->m_enemyHeroVector[m_spaceNumber] = nullptr;
            m_warLayer->enemyCount--;
            break;
        case e_EnemySolider://亡的是我方小兵
            m_warLayer->m_enemySoliderVector[m_spaceNumber] = nullptr;
            break;
        case e_OurSolider://亡的是我方小兵
            m_warLayer->m_ourSoliderVector[m_spaceNumber] = nullptr;
            break;
        default:
            break;
    }
    this->removeFromParent();
}
void BaseSprite::setHeroSkillAction(cocostudio::Armature* heroAc)
{
    hero1skill = heroAc;
    hero1skill->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(BaseSprite::onFrameSkillBtnEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}
void BaseSprite::onFrameSkillPlayEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
    //log("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt.c_str(), currentFrameIndex);
    //log("hero name=%s",m_heroDataST.hero_name.c_str());
    string evtx = evt;
    switch(hash_(evtx.c_str())){
        case "attack"_hash:
        {
            //log("attack");
        }
            break;
        case "playEnd"_hash:
        {
            cocostudio::Armature* tmparm = bone->getArmature();
            if (tmparm) {
                if (skillIconTime > 0) {
                    CallFunc* func  = CallFunc::create([=]()->void{
                        skillIconTime = 0;
                        tmparm->removeFromParent();
                    });
                    tmparm->runAction(Sequence::create(DelayTime::create(skillIconTime/1000.0f),func, NULL));
                } else {
                    tmparm->removeFromParent();
                }
            }
        }
            break;
        case "attackEnd"_hash:
        {
            //log("addack end.");
            bone->getArmature()->removeFromParent();
        }
            break;
        default:
            //log("sprite default.....");
            break;
    }
}
void BaseSprite::onFrameSkillBtnEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
    //log("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt.c_str(), currentFrameIndex);
    //log("hero name=%s",m_heroDataST.hero_name.c_str());
    string evtx = evt;
    switch(hash_(evtx.c_str())){
        case "playEnd"_hash:
        {
            if (isPlayStart) {
                this->showSkillBtnUsed();
            }else{
                this->unShowSkillBtnUsed();
            }
        }
            break;
        default:
            //log("sprite default.....");
            break;
    }
}
void BaseSprite::initHeroIconButton()
{
    log("hero icon=%s,id = %d,name = %s",m_heroDataST.hero_icon.c_str(),m_ID,m_heroDataST.hero_name.c_str());
    hero1Layout->setVisible(true);
    heroicon1->loadTexture(m_heroDataST.hero_icon,TextureResType::PLIST);
    this->initHeroStar();
}
void BaseSprite::showSkillBtnUsed()
{
    
    m_skillRealesBtn->setTouchEnabled(true);
    if (!hero1skill->isVisible()) {
        hero1skill->setVisible(true);
    }
    isShowSKill = true;
    hero1skill->getAnimation()->play("play");
}
void BaseSprite::showSkillBtnUsedplayStart()
{
    if(!isPlayStart){
        hero1skill->setVisible(true);
        isPlayStart = true;
        hero1skill->getAnimation()->play("play2");
    }
}
void BaseSprite::showSkillBtnUsedplayEnd()
{
    isPlayStart = false;
    hero1skill->getAnimation()->play("play2");
}
void BaseSprite::unShowSkillBtnUsed()
{
    isShowSKill = false;
    m_skillRealesBtn->setTouchEnabled(false);
    hero1skill->getAnimation()->stop();
    hero1skill->setVisible(false);
}
void BaseSprite::initHeroStar()
{
    switch (m_heroDataST.hero_star) {
        case 0:
        {
            hero1StarVector[0]->setVisible(false);
            hero1StarVector[1]->setVisible(false);
            hero1StarVector[2]->setVisible(true);
            hero1StarVector[3]->setVisible(false);
            hero1StarVector[4]->setVisible(false);
        }
            break;
        case 1:
        {
            hero1StarVector[0]->setVisible(false);
            hero1StarVector[1]->setVisible(true);
            hero1StarVector[2]->setVisible(true);
            hero1StarVector[3]->setVisible(false);
            hero1StarVector[4]->setVisible(false);
        }
            break;
        case 2:
        {
            hero1StarVector[0]->setVisible(false);
            hero1StarVector[1]->setVisible(true);
            hero1StarVector[2]->setVisible(true);
            hero1StarVector[3]->setVisible(true);
            hero1StarVector[4]->setVisible(false);
        }
            break;
        case 3:
        {
            hero1StarVector[0]->setVisible(true);
            hero1StarVector[1]->setVisible(true);
            hero1StarVector[2]->setVisible(true);
            hero1StarVector[3]->setVisible(true);
            hero1StarVector[4]->setVisible(false);
        }
            break;
        case 4:
        {
            hero1StarVector[0]->setVisible(true);
            hero1StarVector[1]->setVisible(true);
            hero1StarVector[2]->setVisible(true);
            hero1StarVector[3]->setVisible(true);
            hero1StarVector[4]->setVisible(true);
        }
            break;
        default:
        {
            hero1StarVector[0]->setVisible(false);
            hero1StarVector[1]->setVisible(false);
            hero1StarVector[2]->setVisible(false);
            hero1StarVector[3]->setVisible(false);
            hero1StarVector[4]->setVisible(false);
        }
            break;
    }
}
void BaseSprite::initALLSkill() //初始化英雄技能
{
    //奥义技能,普能技能,第3技能,第4技能,第5技能,第6技能
    m_skillID[0] = m_heroDataST.hero_skill_id1;
    m_skillID[1] = m_heroDataST.hero_skill_id2;
    m_skillID[2] = m_heroDataST.hero_skill_id3;
    m_skillID[3] = m_heroDataST.hero_skill_id4;
    m_skillID[4] = m_heroDataST.hero_skill_id5;
    m_skillID[5] = m_heroDataST.hero_skill_id6;
    
    string soundpath;
    for (int i = 0; i < 6; i++) {
        skillIDAndLeveMap[m_skillID[i]] = m_skillLeve[i];
        if (m_skillID[i] > 0) {
            this->loadSkillBuffActionWithSkillID(m_skillID[i]);
            m_skillDataST[i] = LocalDataManger::sharedLocalDataManger()->getConfigtab_skill_visual_effectDataST(m_skillID[i]);
            if (!m_skillDataST[i].skill_sound_effect.empty()) {
                string soundpath = "sound/skillsound/" + m_skillDataST[i].skill_sound_effect;
                CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(soundpath.c_str());
            }
            if (!m_skillDataST[i].skill_hit_resource.empty()) {
                SkillActionManger::sharedSkillActionManger()->loadSkillHide(m_skillDataST[i].skill_hit_resource);
            }
            if (m_skillDataST[i].track_id > 0) {
                Configtab_skill_trajectoryDataST bulletDat = LocalDataManger::sharedLocalDataManger()->getConfigtab_skill_trajectoryDataST(m_skillDataST[i].track_id);
                if (bulletDat.track_sub_type == 0) {
                    SkillActionManger::sharedSkillActionManger()->loadSkillBullet(bulletDat.bullet_texture);
                }
            }
            m_skill[i] = SkillAction::createWithID(m_skillID[i]);
//            m_skill[i] = Skill::createWithID(m_skillID[i]);
            m_skill[i]->setSkillData(this,m_warLayer, m_skillLeve[i]);
        }else{
            m_skill[i] = nullptr;
        }
    }
}
void BaseSprite::initBaseAction()
{
    m_isShowSelect = false;
    m_isShowAttack = false;
    //选择动画
    //友方
    m_selectArmature = Armature::create("tx_xiangzhong");
    m_selectArmature->setVisible(false);
    this->addChild(m_selectArmature,-1);
    //敌方
    m_attackArmature = Armature::create("tx_miaozhunl");
    m_attackArmature->setVisible(false);
    this->addChild(m_attackArmature,-1);

    //加载精灵骨骼动画
    string s_strID = to_string(m_ID);
    SkillActionManger::sharedSkillActionManger()->loadSprite(m_ID);
    armature = Armature::create(s_strID);
    //设置骨格动画回调方法,监听骨格动画帧事件
    armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(BaseSprite::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    armature->getAnimation()->play(kAnimationStand);
    this->initAllPoint();
    this->addChild(armature);
    
    this->preLoadChangeBody();
}
void BaseSprite::onFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
    //log("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt.c_str(), currentFrameIndex);
   // log("hero name=%s",m_heroDataST.hero_name.c_str());
    string evtx = evt;
    switch(hash_(evtx.c_str())){
        case "attackStart"_hash:
        {
            this->frameAttackStart();
        }
            break;
        case "attackEnd"_hash:
        {
            this->frameAttackEnd();
        }
            break;
        case "dieEnd"_hash:
        {
            this->dieActionEnd();
        }
            break;
        case "hitedEnd"_hash:
        {
            
            if (!s_isDie) {
                this->frameAttackEnd();
            }
        }
            break;
        case "readyEnd"_hash:
        {
            this->magic01Ready();
        }
            break;
        case "playEnd"_hash:
        {
            if (!m_warLayer->m_isWarEnd) {
                this->magic01Start();
            }
        }
            break;
        case "magic01End"_hash:
        {
            this->magic01End();
            if (m_ID == 1506) {
                this->setLocalZOrder(0);
            }
        }
            break;
        default:
            //log("sprite default.....");
            break;
    }

    /*
     * originFrameIndex is the frame index editted in Action Editor
     * currentFrameIndex is the current index animation played to
     * frame event may be delay emit, so originFrameIndex may be different from currentFrameIndex.
     */
    
}
void BaseSprite::magic01Ready()
{
    if (m_skillDataST[0].track_id == 0 ) {
        m_skill[0]->runSkill(m_targetSp);
    }
}
void BaseSprite::magic01Start()
{
    isSkillCanStop = false;
    
    if (m_skillDataST[0].track_id == 0 ) return;
    
    if (m_skillDataST[0].track_id > 0 ) {
        std::list<BaseSprite*> targetList;
        int skill_range = m_skillDataST[0].skill_range;
        if (skill_range > 0 && skill_range < 10) {
            targetList = m_skill[0]->getRandomTargetList();
        } else {
            targetList.push_back(m_targetSp);
        }
        
        while (!targetList.empty()) {
            BaseSprite* targettmp = targetList.front();
            
            if (targettmp && !targettmp->s_isDie) {
                Point potmp = targettmp->getPosition();
                SkillBullet* tmpbullet = SkillBullet::createSkillBullet(this, targettmp, &_position, &potmp,m_skillDataST[0].track_id,m_skillDataST[0].ID,m_skillLeve[1]);
                if (tmpbullet) {
                    Point tarpo = this->getPosition();
                    Point bupo;
                    if (m_isNowFaceRight) {
                        bupo = s_bulltePoint[m_nowSkillNumber-1];
                    }else{
                        bupo = Vec2(-s_bulltePoint[m_nowSkillNumber-1].x,s_bulltePoint[m_nowSkillNumber-1].y);
                    }
                    tarpo.add(bupo);
                    tmpbullet->setPosition(tarpo);
                    Point tmpPo = targettmp->getPosition();
                    tmpPo.subtract(tmpbullet->getPosition());
                    //计算子弹运行角度
                    float angletmp = -(tmpPo.getAngle()/6.2831852f)*360;
                    tmpbullet->setRotation(angletmp);
                    Director::getInstance()->getRunningScene()->addChild(tmpbullet,1300);
                    tmpbullet->bulletStartMove();
                }
            }
            
            targetList.pop_front();
        }
    } else {//近战攻击
        m_skill[0]->runSkill(m_targetSp);
    }
}

void BaseSprite::magic01End()
{
    armature->setScale(1.0f);
    m_isCanChangeTarget = true;//技能播放结束，可以更改攻击目标
    isSkillRun = false;
    if (!s_isDie) {
        this->findAttackTarget();
    }
}
void BaseSprite::frameAttackStart() //普能攻击事件
{
    m_angerBar->addAngerWhenAttack();//普通攻击增加能量
    
    int skillNumbertmp;
    if (m_isFirstAttackSkill) {
            skillNumbertmp = m_firstAttackSkillArr[m_nowAttackPCount];
    }else{
            skillNumbertmp = m_nomalAttackSkillArr[m_nowAttackPCount];
    }
    
    
    if (m_targetSp != nullptr && !m_targetSp->s_isDie) {
        SkillBullet* tmpbullet = nullptr;
        if (m_skillDataST[skillNumbertmp].track_id > 0) {
            Point potmp = m_targetSp->getPosition();
            tmpbullet = SkillBullet::createSkillBullet(this, m_targetSp, &_position,&potmp,m_skillDataST[skillNumbertmp].track_id,m_skillDataST[skillNumbertmp].ID,m_skillLeve[skillNumbertmp]);
        }
        if (!m_skillDataST[skillNumbertmp].skill_sound_effect.empty()) {
            string soundpath = "sound/skillsound/" + m_skillDataST[skillNumbertmp].skill_sound_effect;
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundpath.c_str());
        }
            if (tmpbullet) {
                Point tarpo = this->getPosition();
                Point bupo;
                if (m_isNowFaceRight) {
#if tFacetext
                    if (m_ID > 1500) {
                        bupo = Vec2(-s_bulltePoint[m_nowSkillNumber-1].x,s_bulltePoint[m_nowSkillNumber-1].y);
                    }else{
                        bupo = s_bulltePoint[m_nowSkillNumber-1];
                    }
#else
                    bupo = s_bulltePoint[m_nowSkillNumber-1];
#endif
                }else{
#if tFacetext
                    if (m_ID > 1500) {
                        bupo = s_bulltePoint[m_nowSkillNumber-1];
                    }else{
                        bupo = Vec2(-s_bulltePoint[m_nowSkillNumber-1].x,s_bulltePoint[m_nowSkillNumber-1].y);
                    }
#else
                    bupo = Vec2(-s_bulltePoint[m_nowSkillNumber-1].x,s_bulltePoint[m_nowSkillNumber-1].y);
#endif
                }
                tarpo.add(bupo);
                tmpbullet->setPosition(tarpo);
                Point tmpPo = m_targetSp->getPosition();
                tmpPo.subtract(tmpbullet->getPosition());
                //计算子弹运行角度
                float angletmp = -(tmpPo.getAngle()/6.2831852f)*360;
                tmpbullet->setRotation(angletmp);
                m_warLayer->addWarBullte(tmpbullet);
                tmpbullet->bulletStartMove();
            }else{//近战攻击
                //角色近战攻击技能触发
                m_skill[skillNumbertmp]->runSkill(m_targetSp);
            }
    }
    
    m_attackPCount++;
    
}
//攻击动画结束
void BaseSprite::frameAttackEnd()
{
    
    this->playStandAction();
    
//    Director::getInstance()->getScheduler()->schedule(schedule_selector(BaseSprite::attackDelayTime), this, (m_heroDataST.attact_interval/1000.0f), false);
    Director::getInstance()->getScheduler()->schedule([=](float tm){
        m_isCanChangeTarget = true;
        this->findAttackTarget();
    }, this, (m_heroDataST.attact_interval/1000.0f), 0, 0, false, "frameAttackEnd");
}
//攻击间隔
//void BaseSprite::attackDelayTime(float dt)
//{
//    Director::getInstance()->getScheduler()->unschedule(schedule_selector(BaseSprite::attackDelayTime), this);
//    m_isCanChangeTarget = true;
//    this->findAttackTarget();
//}
//角色死亡动画结束
void BaseSprite::dieActionEnd()
{
    CallFunc* funa = CallFunc::create([=]()->void{
        FadeOut* fadeout = FadeOut::create(2.0f);
        armature->runAction(fadeout);
    });
    CallFunc* funb = CallFunc::create([=]()->void{
        this->updataState(e_warDie, e_stateOut);
    });
    CallFunc* fun = CallFunc::create([=]()->void{
        this->removeFromParent();
    });
    this->runAction(Sequence::create(DelayTime::create(0.3f),funa,DelayTime::create(2.0f),funb,DelayTime::create(0.1f),fun, NULL));
}
void BaseSprite::frameHitedEnd()
{
    this->findAttackTarget();
}
//在战场寻找可攻击目标
void BaseSprite::findAttackTarget()
{
    if (isSkillRun) {
        
    }else
    {
        m_nowPlayAction = e_AniNull;//站立
        if (m_isFaceRight) {
            std::vector<BaseSprite*> allEnemyHero = m_warLayer->getEnemyHeroVector();
            std::vector<BaseSprite*> allEnemySolider = m_warLayer->getEnemySoliderVector();
            this->updataState(e_warAutoFind, e_stateIn);//进入自动寻找敌人状态
            int count = 0;
            int findSp = -1; //查找离自已最近的敌人目标,这里记录目标在敌人数组中的编号
            float minDistance = -1; //最近的目标离自已的距离，－1表示没有目标
            count = (int)allEnemyHero.size();
            for (int i = 0; i < count; i++) {
                if (allEnemyHero[i] != nullptr && (!allEnemyHero[i]->s_isDie)) {
                    float tmpDistance = getPosition().distance(allEnemyHero[i]->getPosition());
                    if (minDistance == -1 || minDistance > tmpDistance) {
                        minDistance = tmpDistance;
                        findSp = i;
                    }
                }
            }
            int counte = 0;
            int findSpe = -1; //查找离自已最近的敌人目标,这里记录目标在敌人数组中的编号
            float minDistancee = -1; //最近的目标离自已的距离，－1表示没有目标
            
            counte = (int)allEnemySolider.size();
            for (int i = 0; i < counte; i++) {
                if (allEnemySolider[i] != nullptr && (!allEnemySolider[i]->s_isDie)) {
                    float tmpDistance = getPosition().distance(allEnemySolider[i]->getPosition());
                    if (minDistancee == -1 || minDistancee > tmpDistance) {
                        minDistancee = tmpDistance;
                        findSpe = i;
                    }
                }
            }
            //log("找到了距离最近的敌人。number:%d",findSp);
            updataState(e_warAutoFind, e_stateOut);//退出自动寻找敌人状态，进入向敌人移动状态
            if (findSp != -1) {
                this->lockAttackTarget(allEnemyHero[findSp]);
            }else if(findSpe != -1){
                this->lockAttackTarget(allEnemySolider[findSp]);
            }else{
                
                this->cleanChangeBody();
                
                if (Director::getInstance()->getScheduler()->isScheduled(schedule_selector(BaseSprite::moveFindAttackTarget), this)){
                    Director::getInstance()->getScheduler()->unschedule(schedule_selector(BaseSprite::moveFindAttackTarget), this);
                    
                }
//                if (Director::getInstance()->getScheduler()->isScheduled(schedule_selector(BaseSprite::attackDelayTime), this)) {
//                    Director::getInstance()->getScheduler()->unschedule(schedule_selector(BaseSprite::attackDelayTime), this);
//                }
                if (Director::getInstance()->getScheduler()->isScheduled("frameAttackEnd", this)) {
                    Director::getInstance()->getScheduler()->unschedule("frameAttackEnd", this);
                }
                if (m_targetSp) {
                    m_targetSp = nullptr;
                    
                }
                
                isNoSkill = true;
                
                if (m_warLayer->m_warCount >= m_warLayer->m_mapNumber) {
                    this->playCharcterAction();//战斗胜利，地图上已经没有活着的敌人了。
                    hero1skill->setVisible(false);
                }else{
                    this->playStandAction();//战斗胜利，地图上已经没有活着的敌人了。
                    hero1skill->setVisible(false);
                }
            }
        }else{
            std::vector<BaseSprite*> allOurHero = m_warLayer->getOurHeroVector();
            std::vector<BaseSprite*> allOurSolider = m_warLayer->getOurSoliderVector();
            
            int count = 0;
            int findSp = -1; //查找离自已最近的敌人目标,这里记录目标在敌人数组中的编号
            float minDistance = -1; //最近的目标离自已的距离，－1表示没有目标
            count = (int)allOurHero.size();
            for (int i = 0; i < count; i++) {
                if (allOurHero[i] != nullptr && (!allOurHero[i]->s_isDie)) {
                    float tmpDistance = getPosition().distance(allOurHero[i]->getPosition());
                    if (minDistance == -1 || minDistance > tmpDistance) {
                        minDistance = tmpDistance;
                        findSp = i;
                    }
                }
            }
            
            int counte = 0;
            int findSpe = -1; //查找离自已最近的敌人目标,这里记录目标在敌人数组中的编号
            float minDistancee = -1; //最近的目标离自已的距离，－1表示没有目标
            
            counte = (int)allOurSolider.size();
            for (int i = 0; i < counte; i++) {
                if (allOurSolider[i] != nullptr && (!allOurSolider[i]->s_isDie)) {
                    float tmpDistance = getPosition().distance(allOurSolider[i]->getPosition());
                    if (minDistancee == -1 || minDistancee > tmpDistance) {
                        minDistancee = tmpDistance;
                        findSpe = i;
                    }
                }
            }
            //log("找到了距离最近的敌人。number:%d",findSp);
            updataState(e_warAutoFind, e_stateOut);//退出自动寻找敌人状态，进入向敌人移动状态
            if (findSp != -1) {
                this->lockAttackTarget(allOurHero[findSp]);
            }else if(findSpe != -1){
                this->lockAttackTarget(allOurSolider[findSp]);
            }
        }

    }
}
void BaseSprite::initAllPoint()
{

    std::vector<std::string> tmpx = StrSplit::split(m_heroDataST.skill_buff_coor, ",");
    s_beBuffPoint = Vec2(atoi(tmpx[0].c_str()),atoi(tmpx[1].c_str()));
    std::vector<std::string> tmpx2 = StrSplit::split(m_heroDataST.skill_hit_coor, ",");
    s_beBulltePoint = Vec2(atoi(tmpx2[0].c_str()),atoi(tmpx2[1].c_str()));
    std::vector<std::string> tmpx3 = StrSplit::split(m_heroDataST.skill_track_coor, ";");
    int count = (int)tmpx3.size();
    for (int i = 0; i < count; i++) {
        std::vector<std::string> tmpxx = StrSplit::split(tmpx3[i], ",");;
        s_bulltePoint[i] = Vec2(atoi(tmpxx[0].c_str()),atoi(tmpxx[1].c_str()));
    }
    
}
void BaseSprite::lockAttackTarget(BaseSprite* sp,bool isMastAttack/* = false*/)   //锁定攻击与追击目标
{
    if (sp == m_targetSp) {//如果锁定的目标是当前已有目标，
        if (!s_isMove) {//如果当前自已没有在移动追击中，开始追击目标
            this->pursueAttack();        //追击目标
        }
        return;
    }else if(m_targetSp && sp != m_targetSp) {
        //如果当前目标不是已有目标,清除已有目标死亡通知
        if(!m_targetSp->s_isDie){
           m_targetSp->unregisterStateChangeEventListen(e_warDie, e_stateIn, this, event_callbackStr(BaseSprite::onEnamyDie));
        }
        
        //移除目标身上的碰撞体
        b2Fixture* fixture = NULL;
        if(m_targetSp->s_fixtureMap.size() > 0 && m_targetSp->s_fixtureMap.find(this) !=  m_targetSp->s_fixtureMap.end())
        {
           fixture = m_targetSp->s_fixtureMap[this];
        }
        
        if(fixture && !m_targetSp->s_isDie){
            m_targetSp->s_b2body->DestroyFixture(fixture);
            map<Box2dSprite*,b2Fixture*>::iterator it = m_targetSp->s_fixtureMap.find(this);
            if (it != m_targetSp->s_fixtureMap.end()) {
                m_targetSp->s_fixtureMap.erase(it);
            }
        }
        
        //注册目标死亡之前的通知回调
        sp->registerStateChangeEventListen(e_warDie, e_stateIn, this, event_callbackStr(BaseSprite::onEnamyDie));
    }else{
        //注册目标死亡之前的通知回调
        sp->registerStateChangeEventListen(e_warDie, e_stateIn, this, event_callbackStr(BaseSprite::onEnamyDie));
    }
    this->m_targetSp = sp;
    this->pursueAttack(isMastAttack);        //追击目标
}
void BaseSprite::attackTarget()
{
    //当前精灵正在攻击中不可更改攻击目标
    m_isCanChangeTarget = false;
    this->playAttackAction();
}
void BaseSprite::pursueAttack(bool isMastAttack)//追击目标
{
    //    //在锁定目标后和一次攻击结束后，以及一次受击结束后会调用本方法来判断是否再进行攻击
    //    /*
    //                    目标是否在攻击范围
    //                      /        \
    //                   是/          \否
    //                    v            v
    //             进行一次攻击       加物理并追击，同时开启寻找最近目标定时器
    //     */
    if (!m_targetSp || m_targetSp->s_isDie) {
        this->m_targetSp = nullptr;
        this->findAttackTarget();
        return;
    }else{
        Point postart = _position;//this->getPosition();
        Point poattack = m_targetSp->getPosition();
        postart.subtract(poattack);
        float dis = postart.length();
        bool isBox2dMove = false;
        //目标是否在当前技能的可攻击范围内
        
        int skillNumbertmp;
        if (m_isFirstAttackSkill) {

            skillNumbertmp = m_firstAttackSkillArr[m_nowAttackPCount];

        }else{
            skillNumbertmp = m_nomalAttackSkillArr[m_nowAttackPCount];
        }
        
        
        if (dis <= m_skillDataST[skillNumbertmp].skill_attact_distance*2*khalfTiledWidth) {
            this->attackTarget();//进行一次攻击
        }else{
            //为目标添加碰撞检测体
            isBox2dMove = true;
        }
        if (isBox2dMove) {
            AStarMap6SideManger::sharedAStarMap6SideManger()->cleanMapPoint((int)m_TiledPoint.x, (int)m_TiledPoint.y);
            AStarMap6SideManger::sharedAStarMap6SideManger()->cleanTiledPointNumber((int)m_TiledPoint.x, (int)m_TiledPoint.y, santdPoint);
            if (isMastAttack) {
                if (Director::getInstance()->getScheduler()->isScheduled(schedule_selector(BaseSprite::moveFindAttackTarget), this)){
                    Director::getInstance()->getScheduler()->unschedule(schedule_selector(BaseSprite::moveFindAttackTarget), this);
                }
            }else{
                if (!(Director::getInstance()->getScheduler()->isScheduled(schedule_selector(BaseSprite::moveFindAttackTarget), this))){
                    Director::getInstance()->getScheduler()->schedule(schedule_selector(BaseSprite::moveFindAttackTarget), this, 1.0f, false);
                }
            }
            this->addBox2dForAttack();
        }
    }
}

void BaseSprite::moveFindAttackTarget(float dt)//寻找离自已最近的目标定时器
{
    if (m_isCanChangeTarget) {
        //如果当前角色不在攻击中
        this->findAttackTarget();
    }
}
void BaseSprite::addBox2dForAttack()
{
    //为目标添加碰撞检测体
    b2Fixture* fixture = nullptr;
    
    if (m_targetSp->s_fixtureMap.size() > 0 && m_targetSp->s_fixtureMap.find(this) != m_targetSp->s_fixtureMap.end()) {
        fixture = m_targetSp->s_fixtureMap[this];
    }
    
    if (fixture) {
        m_targetSp->s_b2body->DestroyFixture(fixture);
        map<Box2dSprite*,b2Fixture*>::iterator it = m_targetSp->s_fixtureMap.find(this);
        if (it != m_targetSp->s_fixtureMap.end()) {
            m_targetSp->s_fixtureMap.erase(it);
        }
    }

    m_targetSp->s_fixtureMap[this] =  Box2dWordManger::sharedBox2dWordManger()->addSpriteToWorldWithCollision(m_targetSp, this);
    s_isMoveForBox2d = true;
    s_isMove = true;
    this->updataState(e_warRunTo, e_stateIn);//开始移动

    if (m_targetSp->getPosition().x >= getPosition().x) {
        this->setFaceRight();
        this->playRunAction();
    }else{
        this->setFaceLeft();
        this->playRunAction();
    }
}
//当角色是友方角色时设置下方角色能量条与血条
void BaseSprite::setAngerSliderUI(ui::LoadingBar* angSlider)
{
    angSlider->setPercent(0);
    m_angerBar->setAngerSlider(angSlider);
}
void BaseSprite::setBloodSliderUI(ui::LoadingBar* bloodSlider)
{
    m_bloodBar->setBloodSlider(bloodSlider);
}
void BaseSprite::setSkillRealesButton(ui::Button* skillBtn)
{
    m_skillRealesBtn = skillBtn;
    m_skillRealesBtn->addTouchEventListener(CC_CALLBACK_2(BaseSprite::buttonSkillEvent, this));
}
void  BaseSprite::buttonSkillEvent(Ref *pSender, ui::Widget::TouchEventType   type)
{
    switch (type)
    {
        case  ui::Widget::TouchEventType::BEGAN:
            //MessageBox("fgfggf", "dsdsss");
            break;
        case  ui::Widget::TouchEventType::MOVED:
            //MessageBox("fgfggf", "dsdsss");
            break;
            
        case  ui::Widget::TouchEventType::ENDED:
        {
            if (m_angerBar->isFull()) {
                if (!m_isSkillButtonTouched && !m_warLayer->m_isWarEnd) {
                    
                    if (SkillActionManger::sharedSkillActionManger()->isAddPlaySkill(this) || isNoSkill) {
                        return;
                    }else{
                       m_isSkillButtonTouched = true;
                        
                    }
                    
                    this->playSkill();
                }
            }else{
                log("anger bar is not full..");
            }
            break;
        }
            
        case  ui::Widget::TouchEventType::CANCELED:
            
            break;
            
        default:
            break;
    }
}
void BaseSprite::playSkill()
{
    log("play skill inter face.....");
    SkillActionManger::sharedSkillActionManger()->addPlaySkillSprite(this);
    m_angerBar->cleanAnger();
    this->showSkillBtnUsedplayEnd();
    m_warLayer->showSkillRunForHero(this);
    
    isSkillRun = true;
}
void BaseSprite::playEnemySkill()
{
    this->cleanBox2dAndAttackTarget();
    this->stopAllActions();
    this->playMagic01Action();
    
    if (m_ID == 1506) {
        this->setLocalZOrder(128);
    }
}
void BaseSprite::playSkillActionEnd()
{
    //this->stopAllActions();
    if (m_selectArmature->isVisible()) {
        this->setShowSelectMove(false);
    }
    if (m_attackArmature->isVisible()) {
        this->setShowAttackSelect(false);
    }
    m_warLayer->whenRunSkillStopMoveAction();
    this->cleanBox2dAndAttackTarget();
    this->cleanChangeBody();
    this->playMagic01Action();
   // this->showSkillBtnUsedplayEnd();
    //m_angerBar->cleanAnger();
    SkillActionManger::sharedSkillActionManger()->m_isSkillRun = false;
    m_isSkillButtonTouched = false;
}
//物理引擎
void BaseSprite::initBox2dBodyWithAttackRange()
{
    int skillNumbertmp;
    if (m_isFirstAttackSkill) {
        
        skillNumbertmp = m_firstAttackSkillArr[m_nowAttackPCount];
        
    }else{
        skillNumbertmp = m_nomalAttackSkillArr[m_nowAttackPCount];
    }
    m_range = m_skillDataST[skillNumbertmp].skill_attact_distance;
   s_arrackRangeFixture = Box2dWordManger::sharedBox2dWordManger()->addBodyForInitSpiite(this, m_range);
}
void BaseSprite::changeAttackRange()
{
    bool tmpxx = s_isMoveForBox2d;
    s_isMoveForBox2d = false;
    int skillNumbertmp;
    if (m_isFirstAttackSkill) {
        
        skillNumbertmp = m_firstAttackSkillArr[m_nowAttackPCount];
        
    }else{
        skillNumbertmp = m_nomalAttackSkillArr[m_nowAttackPCount];
    }
    m_range = m_skillDataST[skillNumbertmp].skill_attact_distance;
    s_arrackRangeFixture = Box2dWordManger::sharedBox2dWordManger()->changeBodyForInitSpiite(this, m_range);
    s_isMoveForBox2d = tmpxx;
}
void BaseSprite::removeBox2dBodyWhenDie()
{
    
}
void BaseSprite::AddFixtureIndexForSprite(Box2dSprite* sp)
{
    
}
void BaseSprite::removeFixtureForSprite(Box2dSprite* sp)
{
    
}

void BaseSprite::unregisterStateChangeWhenDie()
{
    if (this->m_targetSp != nullptr) {
        this->m_targetSp->unregisterStateChangeEventListen(e_warDie, e_stateIn, this, event_callbackStr(BaseSprite::onEnamyDie));
    }
}
void BaseSprite::warBloodEmpty()
{
    s_isDie = true;
    s_isMove = false;
    s_isMoveForBox2d = false;
    if (m_angerBar) {
        m_angerBar->cleanAnger();
    }
    if (isShowSKill || isPlayStart) {
        this->unShowSkillBtnUsed();
    }
    if (m_TiledPoint.x > 0 && m_TiledPoint.y > 0) {
        AStarMap6SideManger::sharedAStarMap6SideManger()->cleanMapPoint((int)m_TiledPoint.x, (int)m_TiledPoint.y);
        AStarMap6SideManger::sharedAStarMap6SideManger()->cleanTiledPointNumber((int)m_TiledPoint.x, (int)m_TiledPoint.y, santdPoint);
    }
//    if (m_isShowAttack) {
//        this->setShowAttackSelect(false);
//    }
//    //清除角色身上的buff效果动画
//    if (!buffList.empty()) {
//        do{
//            cocostudio::Armature* armtmp = buffList.back();
//            armtmp->getAnimation()->stop();
//            armtmp->removeFromParent();
//            buffList.pop_back();
//        }while (!buffList.empty());
//    }
//    //清除角色身上的buff效果图片
//    if (!buffIconList.empty()) {
//        do{
//            Sprite* icontmp = buffIconList.back();
//            icontmp->removeFromParent();
//            buffIconList.pop_back();
//        }while (!buffIconList.empty());
//    }
    
    //如果角色静止,则继续
    if (isSkillPaused) {
        this->armature->resume();
//        this->resume();
        isSkillPaused = false;
    }
    
    if (buffIcon) {
        buffIcon->removeFromParent();
    }
    if (beAttackArm) {
        beAttackArm->removeFromParent();
    }
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);

    this->cleanChangeBody();//清除变身效果
    
    armature->setScale(1.0f);//如果精灵正在放技能，则恢复正常
    if (s_b2body) {
        s_b2body->SetUserData(nullptr);
        //角色死了之后移除物理引擎
        Box2dWordManger::sharedBox2dWordManger()->delBodyFixture(this->s_b2body,this->getTag());
        s_b2body = NULL;
    }
    
    m_bloodBar->setVisible(false);
    
    if (isSkillRun) {
        isSkillRun = false;
    }
    //如果当前角色是被选中，则清除战场选择动画
    if (m_isShowSelect) {
        this->setShowSelectMove(false);
        m_warLayer->hideSelectMoveToFlog(this);
    }
    if (m_isShowAttack) {
        this->setShowAttackSelect(false);
        m_warLayer->hideSelectMoveToFlog(this);
    }
    this->stopAllActions();
    s_fixtureMap.clear();
    
    this->updataState(e_warDie, e_stateIn);//精灵将要死亡
    //清除战场精灵
    this->unregisterStateChangeWhenDie();
    
    
    this->playDieAction();
}

//注册状态改变监听
void BaseSprite::registerStateChangeEventListen(SpriteTypeE state,StateInOrOut inOrOut,cocos2d::Ref* ins,Event_CallBackStr selector)
{
    EventCallBackStrVO *fun=EventCallBackStrVO::initWithData(ins,selector);
    fun->retain();
    int statetmp = state*100 + inOrOut;
    
//    bool isfindstate = false;
//    for (map<int,std::list<Ref*>>::iterator it = s_spriteObserver.begin(); it != s_spriteObserver.end(); it++) {
//        if (it->first == statetmp) {
//            isfindstate = true;
//        }
//    }
//    if(isfindstate)
//    {
//        return;
//    }
    
    
    std::list<cocos2d::Ref*> arr=s_spriteObserver[statetmp];
    
	if(arr.empty())
	{
        arr.push_back(fun);
        s_spriteObserver[statetmp] = arr;
        
	}else{
        for (std::list<cocos2d::Ref*>::iterator it = arr.begin(); it != arr.end(); it++) {
            EventCallBackStrVO* tmpfun = (EventCallBackStrVO*)(*it);
            if (tmpfun->m_target == ins && tmpfun->m_funf == selector) {
                fun->release();
                return;
            }
        }
        arr.push_back(fun);
        s_spriteObserver[statetmp] = arr;
    }
    //log("observer child count is:%d",(int)s_spriteObserver.size());
}
//移除状态监听
void BaseSprite::unregisterStateChangeEventListen(SpriteTypeE state,StateInOrOut inOrOut,cocos2d::Ref* ins,Event_CallBackStr selector)
{
    int statetmp = ((int)state)*100 + (int)inOrOut;
    
//    bool isNotFind = true;
//    for (map<int,std::list<Ref*>>::iterator it = s_spriteObserver.begin(); it != s_spriteObserver.end(); it++) {
//        if (it->first == statetmp) {
//            isNotFind = false;
//        }
//    }
//    if (isNotFind) {
//        return;
//    }

    //map<int,std::list<Ref*>> s_spriteObserver;
    bool isfindstate = false;
    if (s_spriteObserver.size() > 0) {
        for (map<int,std::list<Ref*>>::iterator it = s_spriteObserver.begin(); it != s_spriteObserver.end(); it++) {
            if (it->first == statetmp) {
                isfindstate = true;
            }
        }
    }

    if(!isfindstate)
    {
        return;
    }
    std::list<cocos2d::Ref*> refList = s_spriteObserver[statetmp];
    if (refList.empty()) {
        return;
    }
    for (std::list<cocos2d::Ref*>::iterator it = refList.begin(); it != refList.end();)
    {
        EventCallBackStrVO* tmp = (EventCallBackStrVO*)(*it);
        if(tmp->m_target == ins && selector == tmp->m_funf){
            (*it)->release();
            it = refList.erase(it++);
        }else{
            ++it;
        }
    }
    
    s_spriteObserver[statetmp].clear();
    s_spriteObserver[statetmp] = refList;
}
void BaseSprite::onStateChangeEvent(SpriteTypeE state,StateInOrOut inOrOut)
{
    int tmp = state*100 + inOrOut;
    std::list<cocos2d::Ref*> refList =s_spriteObserver[tmp];
	if(refList.empty())
    {
		return;
    }
    log("list size is=%d",(int)refList.size());
    for (std::list<cocos2d::Ref*>::iterator it = refList.begin(); it != refList.end(); it++) {
        EventCallBackStrVO* fun=(EventCallBackStrVO*)(*it);
		if(fun)
		{
			fun->execute(m_heroDataST.hero_name,this);
		}
    }
    
}

//精灵当前状态更新
void BaseSprite::updataState(SpriteTypeE stateNew,StateInOrOut inOrOutNew)
{
    s_stateShow = stateNew*100+inOrOutNew;
    s_spriteType = stateNew;
    s_stateInOrOut = inOrOutNew;
    //通知相关观查者
    this->onStateChangeEvent(stateNew,inOrOutNew);
}

//精灵坐标位相关
void BaseSprite::setSpaceNumber(int number)//设置精灵初始化时在地图上的站位
{
    m_spaceNumber = number;
}
//精灵移动到某点
void BaseSprite::moveToPosition(Point po,CallFunc* func)
{
    
    float dis = this->getPosition().distance(po);
    
    float moveTime = dis/m_heroDataST.move_speed;
    
    MoveTo* movetmp = MoveTo::create(moveTime,po);
    
    CallFunc* functmp = CallFunc::create(CC_CALLBACK_0(BaseSprite::moveToCallBack,this));
    if (po.x >= getPosition().x) {
        setFaceRight();
        playRunAction();
    }else{
        setFaceLeft();
        playRunAction();
    }
    if (!s_isMove) {
        s_isMove = true;
        updataState(e_warRunTo, e_stateIn);
    }
    if (func) {
        runAction(Sequence::create(movetmp,functmp, NULL));
    }else{
        runAction(Sequence::create(movetmp,functmp, NULL));
    }
    
}
void BaseSprite::cleanBox2dAndAttackTarget() //取消一个攻击目标，当角色移动时
{
    //同时要取消目标死亡观查者
    this->stopAllActions();
    isTouchMove = false;
    if (m_targetSp) {
        m_targetSp->unregisterStateChangeEventListen(e_warDie, e_stateIn, this, event_callbackStr(BaseSprite::onEnamyDie));
        if (s_isMoveForBox2d) {
            if(this->s_fixtureMap[m_targetSp] && !m_targetSp->s_isDie){
                m_targetSp->s_b2body->DestroyFixture(m_targetSp->s_fixtureMap[this]);
            }
            map<Box2dSprite*,b2Fixture*>::iterator it = m_targetSp->s_fixtureMap.find(this);
            if (it != m_targetSp->s_fixtureMap.end()) {
                m_targetSp->s_fixtureMap.erase(it);
            }
            //先移除移动碰撞体字典
            m_targetSp = nullptr;
            s_isMove = true;
            s_isMoveForBox2d = false;
            //this->stopAllActions();
        }
    }
    //armature->getAnimation()->stop();
    
}
//玩家点击之后移动到某点
void BaseSprite::touchMoveToPosition(Point po,CallFunc *func)
{
    //当精灵分为三种状态，
    //1,当前精灵正在攻击某个目标，
    //2,当前精灵正在使用box2d追击某个目标
    //3,当前精灵正在向某个坐标移动
    
    m_isCanChangeTarget = false;
    
    if (Director::getInstance()->getScheduler()->isScheduled(schedule_selector(BaseSprite::moveFindAttackTarget), this)){
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(BaseSprite::moveFindAttackTarget), this);
    }
    
    armature->getAnimation()->stop();
    armature->setScale(1.0f);//如果精灵正在放大招，则恢复精灵大小
    if (m_targetSp) {
        m_targetSp->unregisterStateChangeEventListen(e_warDie, e_stateIn, this, event_callbackStr(BaseSprite::onEnamyDie));
        if (s_isMoveForBox2d) {
            if(!m_targetSp->s_isDie && m_targetSp->s_fixtureMap[this]){
                m_targetSp->s_b2body->DestroyFixture(m_targetSp->s_fixtureMap[this]);
            }
            this->s_b2body->SetLinearVelocity(b2Vec2(0,0));
            map<Box2dSprite*,b2Fixture*>::iterator it = m_targetSp->s_fixtureMap.find(this);
            if (it != m_targetSp->s_fixtureMap.end()) {
                m_targetSp->s_fixtureMap.erase(it);
            }
            //先移除移动碰撞体字典
            m_targetSp = nullptr;
            s_isMove = true;
            s_isMoveForBox2d = false;
        }
    }
    this->stopAllActions();
    isTouchMove = true;
    this->moveToPosition(po,func);
}

//私有方法，只能自已使用
void BaseSprite::moveToCallBack()//精灵移动到某个点之后的回调方法
{
    log("move to po end");
    s_isMove = false;
    m_isCanChangeTarget = true; //移动到位，可以搜索最近的敌人了
    isTouchMove = false;
    m_warLayer->hideSelectMoveToFlog(this);
    if (m_isShowSelect) {
        this->setShowSelectMove(false);
    }
    if (!(Director::getInstance()->getScheduler()->isScheduled(schedule_selector(BaseSprite::moveFindAttackTarget), this))){
         Director::getInstance()->getScheduler()->schedule(schedule_selector(BaseSprite::moveFindAttackTarget), this, 1.0f, false);
    }
    this->findAttackTarget();
}

void BaseSprite::touchMoveToSprite(BaseSprite* sp)
{
    //追击某个精灵
    this->stopAllActions();
    isTouchMove = false;
    s_isMove = false;
    this->lockAttackTarget(sp,true);
}

void BaseSprite::Attack()                  //攻击锁定目标
{
    if (m_targetSp != nullptr) {
        map<Box2dSprite*,b2Fixture*>::iterator it = m_targetSp->s_fixtureMap.find(this);
        if (it != m_targetSp->s_fixtureMap.end()) {
            m_targetSp->s_fixtureMap.erase(it);
        }
    }
    s_isMove = false;
    s_isMoveForBox2d = false;
    //先移除移动碰撞体字典
    if (m_targetSp != nullptr && !m_targetSp->s_isDie) {
//        m_targetSp->unregisterStateChangeEventListen(e_warDie, e_stateIn, this, event_callbackStr(BaseSprite::onEnamyDie));
        updataState(e_warRunTo, e_stateOut);
        this->moveToTiledPoint();
    }
}
//调整攻击位置
void BaseSprite::moveToTiledPoint()
{
    m_isCanChangeTarget = false;//当前正在调整攻击位置，不搜索最近目标
    Point po = m_targetSp->getPosition();
    Point ang = this->getPosition();
    ang.subtract(po);
    AStarTiledPoint tiPoNext;
    //log("show sprite id = %d",m_ID);
    if (m_range == 1) {
        tiPoNext = AStarMap6SideManger::sharedAStarMap6SideManger()->findAttackPointForOneTiled1(po, this->getPosition());
    }else if (m_range == 2)
    {
        tiPoNext = AStarMap6SideManger::sharedAStarMap6SideManger()->findAttackPointForOneTiled2(po, this->getPosition());
    }else if (m_range == 3 || m_range ==4)
    {
        tiPoNext = AStarMap6SideManger::sharedAStarMap6SideManger()->findAttackPointForOneTiled3(po, this->getPosition());
    }else{
        tiPoNext = AStarMap6SideManger::sharedAStarMap6SideManger()->findAttackPointForOneTiled1(po, this->getPosition());
    }

    bool isFull = false;
    if (tiPoNext.x > 900) {
        isFull = true;
        tiPoNext.x -= 1000;
    }
    //要达到的地图坐标
    AStarPixelPoint toP  = AStarMap6SideManger::sharedAStarMap6SideManger()->getPixelPointFromTiledPoint(tiPoNext);
    
    m_TiledPoint = Vec2(tiPoNext.x,tiPoNext.y);
    AStarMap6SideManger::sharedAStarMap6SideManger()->setMapPoint(tiPoNext.x, tiPoNext.y);
    
    Point tmpTarP = toP.po;
    if (isFull) {
        //目标身上已经没有攻击位可以站了，生成一个新的坐标。
        //一个地图块上一共可以有七个站位，我们要根据不同方向设置合适的站位
        Point xpo = po;
        xpo.subtract(toP.po);
        float anglex = xpo.getAngle();
        santdPoint = 0;
        
        if (!(AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 0))) {
            
            if (anglex > 0 && anglex <= 1.05) {
                //可站位为,0,1,2,3,6
                
                
                if ((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 1))) {
                    santdPoint = 1;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 2)))
                {
                    santdPoint = 2;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 3)))
                {
                    santdPoint = 3;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 6)))
                {
                    santdPoint = 6;
                }else{
                    santdPoint = 0;
                }
            }else if(anglex > 1.05 && anglex <= 2.0944)
            {
                //0,1,2,3,4
                if ((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 2))) {
                    santdPoint = 2;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 3)))
                {
                    santdPoint = 3;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 4)))
                {
                    santdPoint = 4;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 1)))
                {
                    santdPoint = 1;
                }else{
                    santdPoint = 0;
                }
                
            }else if(anglex > 2.0944)
            {
                //0,2,3,4,5
                if ((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 3))) {
                    santdPoint = 3;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 4)))
                {
                    santdPoint = 4;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 5)))
                {
                    santdPoint = 5;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 2)))
                {
                    santdPoint = 2;
                }else{
                    santdPoint = 0;
                }
            }else if(anglex <= 0 && anglex > -1.0472)
            {
                //0,3,4,5,6
                if ((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 4))) {
                    santdPoint = 4;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 5)))
                {
                    santdPoint = 5;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 3)))
                {
                    santdPoint = 3;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 6)))
                {
                    santdPoint = 6;
                }else{
                    santdPoint = 0;
                }
            }else if(anglex > -2.0944 && anglex <= -1.0472)
            {
                //0,4,5,6,1
                if ((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 5))) {
                    santdPoint = 5;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 6)))
                {
                    santdPoint = 6;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 4)))
                {
                    santdPoint = 4;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 1)))
                {
                    santdPoint = 1;
                }else{
                    santdPoint = 0;
                }
            }else if(anglex <= -2.0944)
            {
                //0,2,5,6,1
                if ((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 6))) {
                    santdPoint = 6;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 1)))
                {
                    santdPoint = 1;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 2)))
                {
                    santdPoint = 2;
                }else if((AStarMap6SideManger::sharedAStarMap6SideManger()->getTiledPointNumber(tiPoNext.x, tiPoNext.y, 5)))
                {
                    santdPoint = 5;
                }else{
                    santdPoint = 0;
                }
            }

        }
        switch (santdPoint) {
            case 0:
            {
                
            }
                break;
            case 1:
            {
                Point tmpd = Vec2::forAngle(0);
                tmpTarP.add(tmpd*40.0f);
                
            }
                break;
            case 2:
            {
                Point tmpd = Vec2::forAngle(1.0472);
                tmpTarP.add(tmpd*40.0f);
                
            }
                break;
            case 3:
            {
                Point tmpd = Vec2::forAngle(2.0944);
                tmpTarP.add(tmpd*40.0f);
                
            }
                break;
            case 4:
            {
                Point tmpd = Vec2::forAngle(3.15149);
                tmpTarP.add(tmpd*40.0f);
            }
                break;
            case 5:
            {
                Point tmpd = Vec2::forAngle(-2.0944);
                tmpTarP.add(tmpd*40.0f);
            }
                break;
            case 6:
            {
                Point tmpd = Vec2::forAngle(-1.0472);
                tmpTarP.add(tmpd*40.0f);
            }
                break;
                
            default:
            {
                
            }
                break;
        }
        
    }
    
    AStarMap6SideManger::sharedAStarMap6SideManger()->setTiledPointNumber(tiPoNext.x, tiPoNext.y, santdPoint);
    
    Point tmp = tmpTarP;
    tmp.subtract(this->getPosition());
    
    if(tmp.getAngle() > -1.570796 && tmp.getAngle() <= 1.570796) //这时面向右
    {
        this->setFaceRight();
    }else{
        this->setFaceLeft();
    }
    
    float moveTime = tmp.length()/m_heroDataST.move_speed;
    CallFunc* func = CallFunc::create(CC_CALLBACK_0(BaseSprite::moveToTiledPointEnd,this));
    
    this->runAction(Sequence::create(MoveTo::create(moveTime, tmpTarP),func, NULL));
}
void BaseSprite::moveToTiledPointEnd()
{
    if (m_isShowSelect) {
        this->setShowSelectMove(false);
        if (m_targetSp && m_targetSp->m_isShowAttack) {
            m_targetSp->setShowAttackSelect(false);
        }
        m_warLayer->hideSelectMoveToFlog(this);
    }
    
    if (this->m_targetSp == nullptr) {
        m_isCanChangeTarget = true;//已经移动到位，可开始攻击目标
        this->findAttackTarget();
    }else{
        updataState(e_warAttack, e_stateIn);//转为开始攻击状态
        if (m_targetSp->getPosition().x >= getPosition().x) {
            this->setFaceRight();
        }else{
            this->setFaceLeft();
        }
        if ((m_targetSp != nullptr) && (!m_targetSp->s_isDie)) {
            this->attackTarget();
        }else{
             m_isCanChangeTarget = true;//已经移动到位，可开始攻击目标
            this->findAttackTarget();
        }
    }
}

void BaseSprite::setFaceRight()
{
#if tFacetext
    if (!m_isNowFaceRight) {
        
        m_isNowFaceRight = true;
        if (m_heroDataST.hero_faceto == 0) {
            this->setScaleX(-1.0f);
            if (m_bloodBar) {
                m_bloodBar->setScaleX(-1.0f);
            }
        }else{
            this->setScaleX(1.0f);
            if (m_bloodBar) {
                m_bloodBar->setScaleX(1.0f);
            }
        }
    }
#else
    if (!m_isNowFaceRight) {
        
        m_isNowFaceRight = true;
        this->setScaleX(1.0f);
        if (m_bloodBar) {
            m_bloodBar->setScaleX(1.0f);
        }
    }
#endif

}
void BaseSprite::setFaceLeft()
{
#if tFacetext
    if (m_isNowFaceRight) {
        m_isNowFaceRight = false;
        if (m_heroDataST.hero_faceto == 0) {
            this->setScaleX(1.0f);
            m_bloodBar->setScaleX(1.0f);
        }else{
            this->setScaleX(-1.0f);
            m_bloodBar->setScaleX(-1.0f);
        }
        
    }
#else
    if (m_isNowFaceRight) {
        m_isNowFaceRight = false;
        this->setScaleX(-1.0f);
        m_bloodBar->setScaleX(-1.0f);
    }
#endif
   
}
void BaseSprite::playStandAction()   //站立动画
{
    this->playStandAction(0.0f);
    //Director::getInstance()->getScheduler()->schedule(schedule_selector(BaseSprite::playStandAction), this, 0.1f, false);
}
void BaseSprite::playRunActionWhenWarEnd()
{
//    this->stopAllActions();
//    this->armature->getAnimation()->stop();
    m_nowPlayAction = e_AniRun;//站立
    armature->getAnimation()->play(kAnimationRun);
}
void BaseSprite::playWinActionWhenWarEnd()
{
    this->playCharcterAction();
}
void BaseSprite::playRunAction()     //移动动画
{
    this->playRunAction(0.0f);
    //Director::getInstance()->getScheduler()->schedule(schedule_selector(BaseSprite::playRunAction), this, 0.1f, false);
}
void BaseSprite::playDieAction()     //死亡动画(动画结束帧事件)
{
    this->playDieAction(0.0f);
    //Director::getInstance()->getScheduler()->schedule(schedule_selector(BaseSprite::playDieAction), this, 0.1f, false);
}
void BaseSprite::playAttackAction()//攻击动画(攻击伤害和攻击结束事件)
{
    
    this->playAttackAction(0.0f);
    
//    Director::getInstance()->getScheduler()->schedule(schedule_selector(BaseSprite::playAttackAction), this, 0.1f, false);
}
void BaseSprite::playCharcterAction()//战斗胜利动画
{
    this->stopAllActions();
    this->playCharcterAction(0.0f);
}
void BaseSprite::playMagic01Action() //技能动画(技能开始，释放，结束3事件)
{
     m_isCanChangeTarget = false;//正在释放技能，不能攻击目标
    if (!m_skillDataST[0].skill_sound_effect.empty()) {
        string soundpath = "sound/skillsound/" + m_skillDataST[0].skill_sound_effect;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundpath.c_str());
    }
    this->playMagic01Action(0.0f);
    //Director::getInstance()->getScheduler()->schedule(schedule_selector(BaseSprite::playMagic01Action), this, 0.01f, false);
}
void BaseSprite::playHitedAction()   //受攻击事件(动画结束事件)
{
    this->playHitedAction(0.0f);
    //Director::getInstance()->getScheduler()->schedule(schedule_selector(BaseSprite::playHitedAction), this, 0.01f, false);
}
void BaseSprite::playStandAction(float dt)     //播放等待动画
{
    
//     Director::getInstance()->getScheduler()->unschedule(schedule_selector(BaseSprite::playStandAction), this);
    if (s_isDie) {
        return;
    }
    if (armature->getAnimation()->isPlaying() && m_nowPlayAction != e_AniStand) {
        m_nowPlayAction = e_AniStand;//站立
        armature->getAnimation()->play(kAnimationStand);
    }else{
        m_nowPlayAction = e_AniStand;//站立
        armature->getAnimation()->play(kAnimationStand);
    }
}
void BaseSprite::playRunAction(float dt)    //播放移动动画
{
    //Director::getInstance()->getScheduler()->unschedule(schedule_selector(BaseSprite::playRunAction), this);
    if (s_isDie) {
        return;
    }
    if (this->armature->getAnimation()->isPlaying() && this->m_nowPlayAction != e_AniRun) {
        m_nowPlayAction = e_AniRun;//站立
        armature->getAnimation()->play(kAnimationRun);
    }else{
        m_nowPlayAction = e_AniRun;//站立
        armature->getAnimation()->play(kAnimationRun);
    }
    
}
void BaseSprite::playDieAction(float dt)     //播放死亡动画
{
    //Director::getInstance()->getScheduler()->unschedule(schedule_selector(BaseSprite::playDieAction), this);
    if (armature->getAnimation()->isPlaying() && m_nowPlayAction != e_AniDie) {
        m_nowPlayAction = e_AniDie;//站立
        armature->getAnimation()->play(kAnimationDie);
    }else{
        m_nowPlayAction = e_AniDie;//站立
        armature->getAnimation()->play(kAnimationDie);
    }
}
void BaseSprite::playAttackAction(float dt)  //播放攻击动画
{
    //Director::getInstance()->getScheduler()->unschedule(schedule_selector(BaseSprite::playAttackAction), this);
    if (m_targetSp == nullptr || s_isDie ) {
        
        return;
    }
    if (this->m_targetSp->getPosition().x >= _position.x) {
        this->setFaceRight();
    }else{
        this->setFaceLeft();
    }
    
    int skillNumbertmp;
    if (m_isFirstAttackSkill) {
        if (m_attackPCount > 5 || m_firstAttackSkillArr[m_attackPCount] < 0) {
            m_attackPCount = 0;
            m_nowAttackPCount = 0;
            skillNumbertmp = m_nomalAttackSkillArr[m_attackPCount];
            m_isFirstAttackSkill = false;
        }else{
            m_nowAttackPCount = m_attackPCount;
            skillNumbertmp = m_firstAttackSkillArr[m_attackPCount];
        }
        //m_attackPCount++;
    }else{
        if (m_attackPCount > 5 || m_nomalAttackSkillArr[m_attackPCount] < 0) {
            m_attackPCount = 0;
            m_nowAttackPCount = 0;
            skillNumbertmp = m_nomalAttackSkillArr[m_attackPCount];
        }else{
            m_nowAttackPCount = m_attackPCount;
            skillNumbertmp = m_nomalAttackSkillArr[m_attackPCount];
        }
        //m_attackPCount++;
    }
    
    if (armature->getAnimation()->isPlaying() && m_nowPlayAction != e_AniAttack) {
        m_nowPlayAction = e_AniAttack;//站立
        
        
        armature->getAnimation()->play(m_skillDataST[skillNumbertmp].skill_animation_resource);
    }else{
        m_nowPlayAction = e_AniAttack;//站立
        armature->getAnimation()->play(m_skillDataST[skillNumbertmp].skill_animation_resource);
    }
}
void BaseSprite::playCharcterAction(float dt)  //播放胜利动画
{
    if (armature->getAnimation()->isPlaying() && m_nowPlayAction != e_AniCharacter) {
        m_nowPlayAction = e_AniCharacter;//站立
        armature->getAnimation()->play(kAnimationCharacter);
    }else{
        m_nowPlayAction = e_AniCharacter;//站立
        armature->getAnimation()->play(kAnimationCharacter);
    }
}
void BaseSprite::playMagic01Action(float dt)  //播放第一技能动画
{
    
    //Director::getInstance()->getScheduler()->unschedule(schedule_selector(BaseSprite::playMagic01Action), this);
    if (armature->getAnimation()->isPlaying() && m_nowPlayAction != e_AniMagic01) {
        m_nowPlayAction = e_AniMagic01;//站立
        armature->getAnimation()->play(kAnimationMagic01);
    }else{
        m_nowPlayAction = e_AniMagic01;//站立
        armature->getAnimation()->play(kAnimationMagic01);
    }
    if (m_isFaceRight) {
        armature->setScale(kRunSkillScale);
    }else{
        armature->setScale(1.0f);
    }
    isSkillCanStop = true;
}
void BaseSprite::playHitedAction(float dt)                //播放受击动画
{
   // Director::getInstance()->getScheduler()->unschedule(schedule_selector(BaseSprite::playHitedAction), this);
    if (armature->getAnimation()->isPlaying() && m_nowPlayAction != e_AniBeAttack) {
        m_nowPlayAction = e_AniBeAttack;//站立
        armature->getAnimation()->play(kAnimationHited);
    }else{
        m_nowPlayAction = e_AniBeAttack;//站立
        armature->getAnimation()->play(kAnimationHited);
    }
    
}
void BaseSprite::onEnamyDie(string name,cocos2d::Ref* sp)  //敌人死亡
{
    this->m_targetSp = nullptr;
    s_isMoveForBox2d = false;
    s_isMove = false;
    if (s_isDie) {
        return;
    }
    if (m_angerBar) {
        m_angerBar->addAngerWhenKill();//击杀目标后，增加能量
    }
    this->findAttackTarget();
}
void BaseSprite::warStart(bool isFirst)          //战场战斗开始
{
    
    this->initBox2dBodyWithAttackRange();
    
    
    if (m_isFaceRight) {//为我方单位
        updataState(e_warStart, e_stateIn);
        Point moveToP = Vec2(getPosition().x,kHeightWindow/4);
        moveToPosition(moveToP);
    }else{//为上边敌方单位
        //为敌方进入等待状态，这里会通知地图，扫描是否有角色进入禁戒范围
        Point moveToP = Vec2(getPosition().x,kHeightWindow*3/4);
        
        if (!m_isFaceRight && m_ID == 1506) {
            moveToP.add(Point(0,-100.0f));
        }
        
        moveToPosition(moveToP);
        updataState(e_warStart, e_stateIn);
    }
    if (!isFirst && m_isFaceRight) {
        Director::getInstance()->getScheduler()->schedule(schedule_selector(BaseSprite::playShowSkillEffect), this, 2.0f,false);
    }
}
void BaseSprite::playShowSkillEffect(float dt)
{
    isNoSkill = false;
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(BaseSprite::playShowSkillEffect), this);
    if (hero1skill && !hero1skill->isVisible()) {
        hero1skill->setVisible(true);
    }
    
}
//加载有buff有技能buff的buff动画
void BaseSprite::loadSkillBuffActionWithSkillID(int ID)
{
    Configtab_skill_visual_effectDataST skillData = LocalDataManger::sharedLocalDataManger()->getConfigtab_skill_visual_effectDataST(ID);
    vector<string> skillEfectvec = StrSplit::split(skillData.skill_effect_id,",");

    list<int> skillEfectList;
    do{
        skillEfectList.push_back(atoi(skillEfectvec.back().c_str()));
        skillEfectvec.pop_back();
    }while (!skillEfectvec.empty());
    
    do{//技能攻击特效
        int SID = skillEfectList.front();
        skillEfectList.pop_front();
        Configtab_skill_effectDataST efectdata = LocalDataManger::sharedLocalDataManger()->getConfigtab_skill_effectDataST(SID);
        if (efectdata.specil_effect_resource.size() > 2) {
            if (efectdata.specil_effect_resource.find(".png") == string::npos) {
                SkillActionManger::sharedSkillActionManger()->loadSkillBuff(efectdata.specil_effect_resource);
            }
        }
        
        if (efectdata.skill_effect_type == 43) {//预加载变身动画
            SkillActionManger::sharedSkillActionManger()->loadSprite(efectdata.skill_base_damage);
        }
        
    }while (!skillEfectList.empty());
}
void BaseSprite::playHitedNoamlAction(string ActionName,int pointType,int layerType,Vec2 vec2) //普通无打断受击动画
{
    if (ActionName.size() > 2) {
        cocostudio::Armature* beAttackArm = cocostudio::Armature::create(ActionName);
        beAttackArm->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(BaseSprite::onFrameSkillPlayEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
        //s_beBulltePoint
        switch (pointType) {
            case 0://头部
            {
                beAttackArm->setPosition(s_beBuffPoint);
            }
                break;
            case 1://身体
            {
                beAttackArm->setPosition(s_beBulltePoint);
            }
                break;
            case 2://下部
            {
                beAttackArm->setPosition(Vec2(0,0));
            }
                break;
                
            default:
            {
                beAttackArm->setPosition(Vec2(0,0));
            }
                break;
        }

        switch (layerType) {
            case -1://精灵上
            {
                this->addChild(beAttackArm);
            }
                break;
            case 0://地图上
            {
                beAttackArm->setPosition(vec2);
                m_warLayer->addChild(beAttackArm);
            }
                break;
            case 1://精灵下层
            {
                this->addChild(beAttackArm,-2);
            }
                break;
                
            default:
            {
                this->addChild(beAttackArm);
            }
                break;
        }
        
        beAttackArm->getAnimation()->play("play");
    }
}
void BaseSprite::playBuff(std::string buffName,float time,int pointType)//播放技能效果buff,time时间
{
    Vec2 buffPoint;
    switch (pointType) {
        case 0://头部
        {
            buffPoint = s_beBuffPoint;
        }
            break;
        case 1://身体
        {
            buffPoint = s_beBulltePoint;
        }
            break;
        case 2://下部
        {
            buffPoint = Vec2(0,0);
        }
            break;
            
        default:
            break;
    }
    if (buffName.size() > 2) {
        if (buffName.find(".png") != string::npos) {
            if (Director::getInstance()->getScheduler()->isScheduled("buffIcon", this)) {
                Director::getInstance()->getScheduler()->unschedule("buffIcon", this);
            }
            if (buffIcon != nullptr) {
                buffIcon->removeFromParent();
                buffIcon = nullptr;
            }
            buffIcon = Sprite::create(buffName);
            buffIcon->setPosition(buffPoint);
            this->addChild(buffIcon);
            Director::getInstance()->getScheduler()->schedule([=](float tm){
                buffIcon->removeFromParent();
                buffIcon = nullptr;
            }, this, time, 0, 0, false, "buffIcon");
//            Sprite* buffIcon = Sprite::create(buffName);
//            buffIcon->setPosition(buffPoint);
//            this->addChild(buffIcon);
//            buffIconList.push_back(buffIcon);
//            CallFuncN* func  = CallFuncN::create([this](Node *sender)->void{
//                
//                std::list<Sprite*>::iterator findit;
//                for (std::list<Sprite*>::iterator it = buffIconList.begin(); it != buffIconList.end(); it++) {
//                    if ((*it) == sender) {
//                        findit = it;
//                        break;
//                    }
//                }
//                buffIconList.erase(findit);
//                sender->removeFromParent();
//            });
//            buffIcon->runAction(Sequence::create(DelayTime::create(time),func, NULL));
        } else {
            if (Director::getInstance()->getScheduler()->isScheduled("buffArm", this)) {
                Director::getInstance()->getScheduler()->unschedule("buffArm", this);
            }
            if (beAttackArm != nullptr) {
                beAttackArm->removeFromParent();
                beAttackArm = nullptr;
            }
            beAttackArm = cocostudio::Armature::create(buffName);
            beAttackArm->setPosition(buffPoint);
            this->addChild(beAttackArm);
            beAttackArm->getAnimation()->play("play");
            Director::getInstance()->getScheduler()->schedule([=](float tm){
                beAttackArm->removeFromParent();
                beAttackArm = nullptr;
            }, this, time, 0, 0, false, "buffArm");
//            cocostudio::Armature* beAttackArm = cocostudio::Armature::create(buffName);
//            beAttackArm->setPosition(buffPoint);
//            this->addChild(beAttackArm);
//            beAttackArm->getAnimation()->play("play");
//            buffList.push_back(beAttackArm);
//            CallFuncN* func  = CallFuncN::create([this](Node *sender)->void{
//                
//                std::list<cocostudio::Armature*>::iterator findit;
//                for (std::list<cocostudio::Armature*>::iterator it = buffList.begin(); it != buffList.end(); it++) {
//                    if ((*it) == sender) {
//                        findit = it;
//                        break;
//                    }
//                }
//                buffList.erase(findit);
//                sender->removeFromParent();
//                
//            });
//            beAttackArm->runAction(Sequence::create(DelayTime::create(time),func, NULL));
        }
    }
}

//初始化时角色的被动技能设置,使用被动技能ID初始化角色
//被动技能特别，增加基本属性，如攻击力，生命值，防御，三围等
void BaseSprite::initLocalSkill(int skillID)
{
    
}
//---------------------------
//技能效果代理方法
void BaseSprite::skillEffect(SpriteWarDataST warData,int skillEffectID,int skillLevel,Configtab_skill_visual_effectDataST m_skillDataST){
    Configtab_skill_effectDataST effectdat = LocalDataManger::sharedLocalDataManger()->getConfigtab_skill_effectDataST(skillEffectID);
    int skill_effect_type = effectdat.skill_effect_type;
    switch (skill_effect_type) {
        case -1:
        {
            this->skillEffectNomal(warData, effectdat);
        }
            break;
        case 1:
        {

        }
            break;
        case 2:
        {
            
        }
            break;
        case 3:
        {
            this->skillEffect3Poison(warData, effectdat, skillLevel);
        }
            break;
        case 4:
        {
            
        }
            break;
        case 5:
        {
            
        }
            break;
        case 6:
        {
            
        }
            break;
        case 7:
        {
            
        }
            break;
        case 8:
        {
            
        }
            break;
        case 9:
        {
            this->skillEffect9Life(warData, effectdat, skillLevel);
        }
            break;
        case 10:
        {
            
        }
            break;
        case 11:
        {
            
        }
            break;
        case 12:
        {
            
        }
            break;
        case 13:
        {
            
        }
            break;
        case 14:
        {
            
        }
            break;
        case 15:
        {
            
        }
            break;
        case 16:
        {
            this->skillEffect16PhysicalAttack(warData, effectdat, skillLevel);
        }
            break;
        case 17:
        {
            this->skillEffect17MagicAttack(warData, effectdat, skillLevel);
        }
            break;
        case 18:
        {
            
        }
            break;
        case 19:
        {
            
        }
            break;
        case 20:
        {
            
        }
            break;
        case 21:
        {
            
        }
            break;
        case 22:
        {
            this->skillEffect22MoveSpeed(warData, effectdat, skillLevel);
        }
            break;
        case 23:
        {
            
        }
            break;
        case 24:
        {
            this->skillEffect24NoPhysicalAttack(warData, effectdat, skillLevel);
        }
            break;
        case 25:
        {
            this->skillEffect25NoMagicAttack(warData, effectdat, skillLevel);
        }
            break;
        case 26:
        {
            
        }
            break;
        case 27:
        {
            
        }
            break;
        case 28:
        {
            
        }
            break;
        case 29:
        {
            
        }
            break;
        case 30:
        {
            
        }
            break;
        case 31:
        {
            
        }
            break;
        case 32:
        {
            
        }
            break;
        case 33:
        {
            
        }
            break;
        case 34:
        {
            this->skillEffect34Ice(warData, effectdat, skillLevel);
        }
            break;
        case 35:
        {
            
        }
            break;
        case 36:
        {
            
        }
            break;
        case 37:
        {
            
        }
            break;
        case 38:
        {
            
        }
            break;
        case 39:
        {
            this->skillEffect39Fetter(warData, effectdat, skillLevel);
        }
            break;
        case 40:
        {
            
        }
            break;
        case 41:
        {
            
        }
            break;
        case 42:
        {
            
        }
            break;
        case 43:
        {
            this->skillEffect43ChangeBody(effectdat, m_skillDataST);
        }
            break;
        case 44:
        {
            this->skillEffect44TimeAttack(warData, effectdat, skillLevel, m_skillDataST);
        }
            break;
            
        default:
            break;
    }
}

//-1普通造成伤害效果,attackValue:计算后得到的攻击伤害值,hited:攻击方的命中
void BaseSprite::skillEffectNomal(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat)
{
    int attackType = effectdat.skill_demage_type;
    int attacksub = this->getAttackValue(warData, attackType);
    bool isBaoji = this->isBaoJi(warData);
    if (isBaoji) {
        attacksub *=2;
    }
    bool isMingZ = this->isMingZhong(warData);
    if (isMingZ) {
        m_angerBar->addAngerWhenBeAttack();//被攻击增加能量
        m_bloodBar->attackBloodSub(attacksub, isBaoji);
    }else{
        m_bloodBar->attackFinding();
    }
}

//1眩晕效果,time:眩晕时间
void BaseSprite::skillEffect1Dizziness(float time,std::string buffname)
{
    
}
//2击退效果,direction:击退方向，Length:击退距离
void BaseSprite::skillEffect2Repelling(float direction,int Length,int speed,std::string buffname)
{
    
}
//3中毒,time:中毒总时间,steptime:伤害间隔,Injury:单次伤害值
void BaseSprite::skillEffect3Poison(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel)
{
    if (s_isDie) return;
    int probability = effectdat.skill_effect_probability;
    bool isPlay = this->isPlaySkillEffect(probability, skillLevel);
    
    if (!isPlay) return;
    float time = effectdat.skill_effect_time/1000.0f;
    float intervalTime = effectdat.skill_effect_interval/1000.0f;//攻击间隔
    int attcount = (int)time/intervalTime;
    
    int attackType = effectdat.skill_demage_type;
    int attacksub = this->getAttackValue(warData, attackType);
    //播放buff动画
    this->playBuff(effectdat.specil_effect_resource, time);
    
    Director::getInstance()->getScheduler()->schedule([=](float tm){
        m_bloodBar->attackBloodSub(attacksub);
    }, this, intervalTime, attcount-1, 0, false, "poison");
}
//4燃烧
void BaseSprite::skillEffect4Combustion(float time,float steptime,int ingury,std::string buffname)
{
    
}
//5沉默
void BaseSprite::skillEffect5Silence(float time,std::string buffname)
{
    
}
//6定身
void BaseSprite::skillEffect6DecidesTheBody(float time,std::string buffname)
{
    
}
//7拉拽
void BaseSprite::skillEffect7Entrains(float direction,int Length,int speed,std::string buffname)
{
    
}
//8流血
void BaseSprite::skillEffect8Bleeding(float time,float steptime,int ingury,std::string buffname)
{
    
}
//9生命
void BaseSprite::skillEffect9Life(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel)
{
    if (s_isDie) return;
    int probability = effectdat.skill_effect_probability;
    bool isPlay = this->isPlaySkillEffect(probability, skillLevel);
    
    if (!isPlay) return;
    float time = effectdat.skill_effect_time/1000.0f;
    float intervalTime = effectdat.skill_effect_interval/1000.0f;//攻击间隔
    int attcount = (int)time/intervalTime;
    
    int attackType = effectdat.skill_demage_type;
    int attacksub = this->getAttackValue(warData, attackType);
    //播放buff动画
    this->playBuff(effectdat.specil_effect_resource, time, 2);
    
    Director::getInstance()->getScheduler()->schedule([=](float tm){
        m_bloodBar->addBloodValue(attacksub);
    }, this, intervalTime, attcount-1, 0, false, "life");
}
//10物理暴击
void BaseSprite::skillEffect10PhysicalBaoJi(float time,int value,std::string buffname)
{
    
}
//11魔法暴击
void BaseSprite::skillEffect11MagicBaoJi(float time,int value,std::string buffname)
{
    
}
//12闪避
void BaseSprite::skillEffect12Fending(float time,int value,std::string buffname)
{
    
}
//13命中
void BaseSprite::skillEffect13Hit(float time,int value,std::string buffname)
{
    
}
//14魔抗
void BaseSprite::skillEffect14MagicResistance(float time,int value,std::string buffname)
{
    
}
//15物防
void BaseSprite::skillEffect15PhysicalDefense(float time,int value,std::string buffname)
{
    
}
//16物理攻击
void BaseSprite::skillEffect16PhysicalAttack(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel)
{
    if (s_isDie) return;
    int probability = effectdat.skill_effect_probability;
    bool isPlay = this->isPlaySkillEffect(probability, skillLevel);
    
    if (!isPlay) return;
    float time = effectdat.skill_effect_time/1000.0f;
    float para = effectdat.self_act_parameter;
    
    this->playBuff(effectdat.specil_effect_resource, time);
    
    float physics_act = m_heroDataST.physics_act;
    m_heroDataST.physics_act = physics_act*para;
    
    Director::getInstance()->getScheduler()->schedule([=](float tm){
        m_heroDataST.physics_act = physics_act;
    }, this, time, 0, 0, false, "physicalAttack");
}
//17魔法攻击
void BaseSprite::skillEffect17MagicAttack(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel)
{
    if (s_isDie) return;
    int probability = effectdat.skill_effect_probability;
    bool isPlay = this->isPlaySkillEffect(probability, skillLevel);
    
    if (!isPlay) return;
    float time = effectdat.skill_effect_time/1000.0f;
    float para = effectdat.self_act_parameter;
    
//    this->playBuff(effectdat.specil_effect_resource, time);
    
    float magic_strength = m_heroDataST.magic_strength;
    m_heroDataST.magic_strength = magic_strength*para;

    Director::getInstance()->getScheduler()->schedule([=](float tm){
        m_heroDataST.magic_strength = magic_strength;
    }, this, time, 0, 0, false, "magicAttack");
}
//18吸血
void BaseSprite::skillEffect18Hemophagia(float time,float pecent,std::string buffname)
{
    
}
//19力量
void BaseSprite::skillEffect19Strength(float time,int value,std::string buffname)
{
    
}
//20智力
void BaseSprite::skillEffect20Intelligence(float time,int value,std::string buffname)
{
    
}
//21敏捷
void BaseSprite::skillEffect21Agile(float time,int value,std::string buffname)
{
    
}
//22移动速度
void BaseSprite::skillEffect22MoveSpeed(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel)
{
    if (s_isDie) return;
    int probability = effectdat.skill_effect_probability;
    bool isPlay = this->isPlaySkillEffect(probability, skillLevel);
    
    if (!isPlay) return;
    float time = effectdat.skill_effect_time/1000.0f;
    float para = effectdat.self_act_parameter;

    this->playBuff(effectdat.specil_effect_resource, time);
    
    float move_speed = m_heroDataST.move_speed;
    m_heroDataST.move_speed = move_speed*para;
    
    Director::getInstance()->getScheduler()->schedule([=](float tm){
        m_heroDataST.move_speed = move_speed;
    }, this, time, 0, 0, false, "moveSpeed");
}
//23攻击速度
void BaseSprite::skillEffect23AttackSpeed(float time,int value,std::string buffname)
{
    
}
//24免疫物理攻击
void BaseSprite::skillEffect24NoPhysicalAttack(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel)
{
    if (s_isDie) return;
    int probability = effectdat.skill_effect_probability;
    bool isPlay = this->isPlaySkillEffect(probability, skillLevel);
    
    if (!isPlay) return;
    float time = effectdat.skill_effect_time/1000.0f;
    
//    this->playBuff(effectdat.specil_effect_resource, time);
    
    isNoPhysicalAttack = true;
    Director::getInstance()->getScheduler()->schedule([=](float tm){
        isNoPhysicalAttack = false;
    }, this, time, 0, 0, false, "noPhysicalAttack");
}
//25免疫魔法攻击
void BaseSprite::skillEffect25NoMagicAttack(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel)
{
    if (s_isDie) return;
    int probability = effectdat.skill_effect_probability;
    bool isPlay = this->isPlaySkillEffect(probability, skillLevel);
    
    if (!isPlay) return;
    float time = effectdat.skill_effect_time/1000.0f;
    
    //    this->playBuff(effectdat.specil_effect_resource, time);
    
    isNoMagicAttack = true;
    Director::getInstance()->getScheduler()->schedule([=](float tm){
        isNoMagicAttack = false;
    }, this, time, 0, 0, false, "noMagicAttack");
}
//26无敌
void BaseSprite::skillEffect26Invincible(float time,std::string buffname)
{
    
}
//27能量
void BaseSprite::skillEffect27Energy(float time,int value,std::string buffname)
{
    
}
//28虚弱
void BaseSprite::skillEffect28Weak(float time,int value,std::string buffname)
{
    
}
//29易伤
void BaseSprite::skillEffect29EasyBeInjured(float time,int vlaue,std::string buffname)
{
    
}
//30反射
void BaseSprite::skillEffect30Reflection(float time,float pencent,std::string buffname)
{
    
}
//31减伤
void BaseSprite::skillEffect31SubAttack(float time,int value,std::string buffname)
{
    
}
//32圣盾
void BaseSprite::skillEffect32SaintShield(float time,int value,std::string buffname)
{
    
}
//33免疫负面效果
void BaseSprite::skillEffect33NoDebuff(float time,std::string buffname)
{
    
}
//34冰冻
void BaseSprite::skillEffect34Ice(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel)
{
    if (s_isDie) return;
    int probability = effectdat.skill_effect_probability;
    bool isPlay = this->isPlaySkillEffect(probability, skillLevel);
        
    if (!isPlay) return;
    float time = effectdat.skill_effect_time/1000.0f;
    
    this->playBuff(effectdat.specil_effect_resource, time, 1);
    
    Director::getInstance()->getScheduler()->schedule([=](float tm){
        if (isSkillPaused) {
            this->armature->resume();
//            this->resume();
            isSkillPaused = false;
        }
    }, this, time, 0, 0, false, "ice");
    
    if (!isSkillPaused) {
        this->armature->pause();
//        this->pause();
        isSkillPaused = true;
    }
    
//    CallFuncN* func  = CallFuncN::create([this](Node *sender)->void{
//        sender->resume();
//        this->resume();
//    });
//    this->armature->runAction(Sequence::create(DelayTime::create(time),func, NULL));
}
//35恐惧
void BaseSprite::skillEffect35Frightened(float time,std::string buffname)
{
    
}
//36抑制治疗
void BaseSprite::skillEffect36SuppressesTreatment(float time,float pencent,std::string buffname)
{
    
}
//37无视物理防御
void BaseSprite::skillEffect37NoPhysicalDefense(float time,std::string buffname)
{
    
}
//38无视法术抗性
void BaseSprite::skillEffect38NoMagicResistance(float time,std::string buffname)
{
    
}
//39束缚
void BaseSprite::skillEffect39Fetter(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel)
{
    if (s_isDie) return;
    int probability = effectdat.skill_effect_probability;
    bool isPlay = this->isPlaySkillEffect(probability, skillLevel);
    
    if (!isPlay) return;
    float time = effectdat.skill_effect_time/1000.0f;
    
    this->playBuff(effectdat.specil_effect_resource, time, 2);
    
    Director::getInstance()->getScheduler()->schedule([=](float tm){
        if (isSkillPaused) {
            this->armature->resume();
            //            this->resume();
            isSkillPaused = false;
        }
    }, this, time, 0, 0, false, "fetter");
    
    if (!isSkillPaused) {
        this->armature->pause();
        //        this->pause();
        isSkillPaused = true;
    }
}
//40魅惑
void BaseSprite::skillEffect40Attracting(float time,std::string buffname)
{
    
}
//41召唤
void BaseSprite::skillEffect41Summon(float time,int spriteID,std::string buffname)
{
    
}
//42复活
void BaseSprite::skillEffect42Relive(float time,std::string buffname)
{
    
}
//43变身
void BaseSprite::skillEffect43ChangeBody(Configtab_skill_effectDataST effectdat,Configtab_skill_visual_effectDataST m_skillDataST)
{
    int time = effectdat.skill_effect_time/1000.0f;
    int spriteID = effectdat.skill_base_damage;
    do{
        armature->setScale(1.0f);

        cocostudio::Armature* tmp = armature;
        armature->setVisible(false);
        armature = changeBodyarmature;
        armature->setVisible(true);
        changeBodyarmature = tmp;
        this->initChangeBodyData(spriteID);

        isChangeBody = true;
    }while (0);
    
    Director::getInstance()->getScheduler()->schedule([=](float tm){
        do{
            this->cleanChangeBody();
            
            this->playHitedNoamlAction(m_skillDataST.skill_hit_resource,m_skillDataST.skill_effect_location);
        }while (0);
    }, this, time, 0, 0, false, "changeBody");
}

void BaseSprite::preLoadChangeBody()
{
    if (m_ID == 1003) {
        changeBodyarmature = Armature::create(to_string(6003));
        //设置骨格动画回调方法,监听骨格动画帧事件
        changeBodyarmature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(BaseSprite::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
        
        changeBodyarmature->getAnimation()->play(kAnimationStand);
        
        //this->initAllPoint();
        this->addChild(changeBodyarmature);
        changeBodyarmature->setVisible(false);
    }
}

void BaseSprite::cleanChangeBody()
{
    do{
        if (isChangeBody) {
            if (Director::getInstance()->getScheduler()->isScheduled("changeBody", this)) {
                Director::getInstance()->getScheduler()->unschedule("changeBody", this);
            }
            
            isChangeBody = false;
            cocostudio::Armature* tmp = armature;
            armature->setVisible(false);
            armature = changeBodyarmature;
            armature->setVisible(true);
            changeBodyarmature = tmp;
            armature->setScale(1.0f);
            
            this->initChangeBodyData(changeBodyOldID);
        }
    }while (0);
}
void BaseSprite::initChangeBodyData(int ID) //变身的属性初始化
{
    if (ID == changeBodyOldID) {
        isChangeBody = false;  //当前是否变身状态
    }else{
        isChangeBody = true;
    }
    
    m_heroDataST = LocalDataManger::sharedLocalDataManger()->getConfigtab_card_attribute_sysDataST(ID);
    
    m_skillID[0] = m_heroDataST.hero_skill_id1;
    m_skillID[1] = m_heroDataST.hero_skill_id2;
    m_skillID[2] = m_heroDataST.hero_skill_id3;
    m_skillID[3] = m_heroDataST.hero_skill_id4;
    m_skillID[4] = m_heroDataST.hero_skill_id5;
    m_skillID[5] = m_heroDataST.hero_skill_id6;
    
    for (int i = 0; i < 6; i++) {
        m_skillDataST[i] = LocalDataManger::sharedLocalDataManger()->getConfigtab_skill_visual_effectDataST(m_skillID[i]);
        this->loadSkillBuffActionWithSkillID(m_skillID[0]);
        
        if (!m_skillDataST[i].skill_sound_effect.empty()) {
            string soundpath = "sound/skillsound/" + m_skillDataST[i].skill_sound_effect;
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(soundpath.c_str());
        }
        
        if (!m_skillDataST[i].skill_hit_resource.empty()) {
            SkillActionManger::sharedSkillActionManger()->loadSkillHide(m_skillDataST[i].skill_hit_resource);
        }
        if (m_skillDataST[i].track_id > 0) {
            Configtab_skill_trajectoryDataST bulletDat = LocalDataManger::sharedLocalDataManger()->getConfigtab_skill_trajectoryDataST(m_skillDataST[i].track_id);
            if (bulletDat.track_sub_type == 0) {
                SkillActionManger::sharedSkillActionManger()->loadSkillBullet(bulletDat.bullet_texture);
            }
        }
    }
    
    this->initHeroWarData();
    
    this->changeAttackRange();
}
//44间歇伤害，如旋风斧
void BaseSprite::skillEffect44TimeAttack(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel,Configtab_skill_visual_effectDataST m_skillDataST)
{
    if (s_isDie) return;
    int probability = effectdat.skill_effect_probability;
    bool isPlay = this->isPlaySkillEffect(probability, skillLevel);
    
    if (!isPlay) return;
    float time = effectdat.skill_effect_time/1000.0f;
    float intervalTime = effectdat.skill_effect_interval/1000.0f;//攻击间隔
    int attcount = (int)time/intervalTime;
    
    int attacksub = this->getAttackValue(warData, effectdat.skill_demage_type);

    Director::getInstance()->getScheduler()->schedule([=](float tm){
        int sub = attacksub;
        bool isBaoji = this->isBaoJi(warData);
        if (isBaoji) {
            sub *= 2;
        }
        bool isMingZ = this->isMingZhong(warData);
        if (isMingZ) {
            m_bloodBar->attackBloodSub(sub, isBaoji);
        } else {
            m_bloodBar->attackFinding();
        }

        this->playHitedNoamlAction(m_skillDataST.skill_hit_resource, m_skillDataST.skill_effect_location);

    }, this, intervalTime, attcount-1, 0, false, "timeAttack");
}

//战斗中的选中操作显示
//当友方被选中时显示选中框
void BaseSprite::setShowSelectMove(bool isShow)
{
    if (isShow && m_selectArmature) {
        m_selectArmature->setVisible(true);
        m_selectArmature->getAnimation()->play("play");
    }else if(m_selectArmature){
        m_selectArmature->getAnimation()->stop();
        m_selectArmature->setVisible(false);
    }
    m_isShowSelect = isShow;
}
//当攻击的敌人被选中时，显示红色框
void BaseSprite::setShowAttackSelect(bool isShow)
{
    if (isShow && m_attackArmature && !(m_attackArmature->isVisible())) {
        m_attackArmature->setVisible(true);
        m_attackArmature->getAnimation()->play("play");
    }else if(m_attackArmature){
        m_attackArmature->getAnimation()->stop();
        m_attackArmature->setVisible(false);
    }
    m_isShowAttack = isShow;
}

float BaseSprite::getAttackValue(SpriteWarDataST warData, int attackType)
{
    int attackValue;
    int defense;
    int attacksub = 0;
    switch (attackType) {
        case -1://无伤害类型
        {
            
        }
            break;
        case 1://物理伤害类型
        {
            if (!isNoPhysicalAttack) {
                //计算公式
                //物理伤害
                //伤害^2/(伤害+0.5*护甲)
                attackValue = warData.s_attack;
                defense = m_warData.s_Defense;
                attacksub = (int)((attackValue*attackValue)/(attackValue+0.5f*defense));
            }
        }
            break;
        case 2://法术伤害类型
        {
            if (!isNoMagicAttack) {
                //计算公式
                //法术伤害
                //伤害^2/(伤害+0.5*魔抗)
                attackValue = warData.s_magicAttack;
                defense = m_warData.s_magicDefense;
                attacksub = (int)((attackValue*attackValue)/(attackValue+0.5f*defense));
            }
        }
            break;
        default:
            break;
    }
    return attacksub;
}

bool BaseSprite::isBaoJi(SpriteWarDataST warData)
{
    //    暴击判断=我方暴击等级/(1.5*暴击等级+对方等级+对方暴击等级)
    float baojiattack =warData.s_BaoJiProbability;
    float baoji = (float)(m_warData.s_BaoJiProbability/(1.5f*m_warData.s_BaoJiProbability + warData.s_leve + baojiattack));
    int baojiX = (int)10000*baoji;
    bool isBaoji = baojiX > (int)(random()%10000);
    return isBaoji;
}

bool BaseSprite::isMingZhong(SpriteWarDataST warData)
{
    //    命中判断=1-对方闪避/[（对方闪避+我方闪避）*3]
    float pEvade = warData.s_evade;
    float Fending = 1.0f - (float)(pEvade/((m_warData.s_evade+pEvade+1)*3));
    int mingz = (int)(10000*Fending);
    bool isMingZ = mingz > (int)(random()%10000);
    return isMingZ;
}

bool BaseSprite::isPlaySkillEffect(int probability,int skillLevel)
{
    bool isPlay = false;
    if (probability == -1) {
        int proba = 1/((m_warData.s_leve-skillLevel)*0.3+1)*10000;
        int random_num = (int)(random()%10000);
        if (random_num <= proba) {
            isPlay = true;
        }
    } else if (probability == 10000) {
        isPlay = true;
    } else {
        int random_num = (int)(random()%10000);
        if (random_num <= probability) {
            isPlay = true;
        }
    }
    return isPlay;
}