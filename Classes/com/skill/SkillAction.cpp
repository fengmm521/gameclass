//
//  Skill.cpp
//  game3
//
//  Created by 俊盟科技1 on 10/13/14.
//
//

#include "SkillAction.h"
#include "Box2dSprite.h"
#include "BaseSprite.h"
#include "SkillBullet.h"
#include "StrSplit.h"
#include "WarScenceLayer.h"
//#include "ClassFromString.h"

SkillAction::~SkillAction()
{
    
}

SkillAction* SkillAction::createWithID(int ID)
{
//    std::string CalssName = "Skill"+to_string(ID);
//    Skill* tmp = ClassFromString::SkillFromName(CalssName);
    SkillAction* tmp = new SkillAction();
    tmp->m_skillID = ID;
    tmp->init();
    return tmp;
}
bool SkillAction::init()
{
    //////////////////////////////
    // 1. super init first
    bool bRet = false;
    do
    {
        isHero = false;
        this->setSkillData();
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void SkillAction::setSkillData(Box2dSprite* skillOwner,WarScenceLayer* warLayer,int skillLeve)
{
    m_Ower = skillOwner;
    m_warlayer = warLayer;
    m_skillLeve = skillLeve;
    switch (m_Ower->box2dSpriteType) {
        case kSpriteBox2d://技能拥有者为精灵
        {
            BaseSprite* tmpsp = dynamic_cast<BaseSprite*>(m_Ower);
            m_fromSp = tmpsp;
            m_warDataST = tmpsp->m_warData;
            m_fromBullet = nullptr;
            isHero = m_fromSp->m_isFaceRight;
        }
            break;
        case kButtleBox2d://技能拥有者为子弹
        {
            SkillBullet* tmpbul = dynamic_cast<SkillBullet*>(m_Ower);
            m_fromBullet = tmpbul;
            m_warDataST = tmpbul->m_warData;
            m_fromSp = m_fromBullet->m_fromSp;
            isHero = m_fromSp->m_isFaceRight;
        }
            break;
        default:
            break;
    }
    this->whenInitSkillDataEnd();//技能数据设置结速,这里技能就可以用了
}

void SkillAction::setSkillData()
{
    this->m_skillDataST = LocalDataManger::sharedLocalDataManger()->getConfigtab_skill_visual_effectDataST(m_skillID);
    
    vector<string> skillEfectvec = StrSplit::split(this->m_skillDataST.skill_effect_id,",");
    
    list<int> skillEfectList;
    
    do{
        skillEfectList.push_back(atoi(skillEfectvec.back().c_str()));
        skillEfectvec.pop_back();
    }while (!skillEfectvec.empty());
    
    do{//技能攻击特效
        int SID = skillEfectList.front();
        skillEfectList.pop_front();
        m_skillEffectIDList.push_back(SID);
    }while (!skillEfectList.empty());
    
}
void SkillAction::playSkillEffectList()
{
    std::list<BaseSprite*> targetList;
    int skill_range = m_skillDataST.skill_range;

    //显示多个弹道的要拆成一个一个弹道单独处理
    if (m_skillDataST.track_id > 0 && skill_range > 0 && skill_range < 10) {
        skill_range = -1;
    }
    switch (skill_range) {
        case -1: //单体攻击
        {
            switch (m_skillDataST.target_type) {
                case -1://攻击目标无限制
                {
                    
                }
                    break;
                case 1://技能目标为自身
                {
                    targetList.push_back(m_fromSp);
                }
                    break;
                case 2://技能目标为友方
                {
                    
                }
                    break;
                case 3://技能目标为敌人
                {
                    targetList.push_back(m_toSp);
                }
                    break;
                default:
                    break;
            }
        }
            break;
        case 0: //全体攻击
        {
            switch (m_skillDataST.target_type) {
                case -1://攻击目标无限制
                {
                    
                }
                    break;
                case 1://技能目标为自身
                {
                    
                }
                    break;
                case 2://技能目标为友方
                {
                    std::vector<BaseSprite*> herovector;
                    if (!isHero) {//当前技能属于下方英雄，
                        herovector = m_warlayer->getEnemyHeroVector();//得到所有敌方英雄，如果目标死亡，则值为nullptr
                    }else{//当前技能属于上方怪物
                        herovector = m_warlayer->getOurHeroVector();//得到所有敌方英雄，如果目标死亡，则值为nullptr
                    }
                    int sizev = (int)herovector.size();
                    for (int i = 0; i < sizev; i++) {
                        if (herovector[i]) {
                            targetList.push_back(herovector[i]);
                        }
                    }
                }
                    break;
                case 3://技能目标为敌人
                {
                    std::vector<BaseSprite*> herovector;
                    if (isHero) {//当前技能属于下方英雄，
                        herovector = m_warlayer->getEnemyHeroVector();//得到所有敌方英雄，如果目标死亡，则值为nullptr
                    }else{//当前技能属于上方怪物
                        herovector = m_warlayer->getOurHeroVector();//得到所有敌方英雄，如果目标死亡，则值为nullptr
                    }
                    int sizev = (int)herovector.size();
                    for (int i = 0; i < sizev; i++) {
                        if (herovector[i]) {
                            targetList.push_back(herovector[i]);
                        }
                    }
                }
                    break;
                default:
                    break;
            }
            
        }
            break;

        default:
        {
            if (skill_range < 10) {   //随机
                switch (m_skillDataST.target_type) {
                    case -1://攻击目标无限制
                    {
                        
                    }
                        break;
                    case 1://技能目标为自身
                    {
                        
                    }
                        break;
                    case 2://技能目标为友方
                    {
                        
                    }
                        break;
                    case 3://技能目标为敌人
                    {
                        targetList = this->getRandomTargetList();
                    }
                        break;
                    default:
                        break;
                }
            } else {    //范围
                switch (m_skillDataST.target_type) {
                    case -1://攻击目标无限制
                    {
                        
                    }
                        break;
                    case 1://技能目标为自身
                    {
                        
                    }
                        break;
                    case 2://技能目标为友方
                    {
                        
                    }
                        break;
                    case 3://技能目标为敌人
                    {
                        Vec2 m_fromSp_vec2 = m_fromSp->getPosition();
                        
                        std::vector<BaseSprite*> herovector;
                        if (isHero) {//当前技能属于下方英雄，
                            herovector = m_warlayer->getEnemyHeroVector();//得到所有敌方英雄，如果目标死亡，则值为nullptr
                        }else{//当前技能属于上方怪物
                            herovector = m_warlayer->getOurHeroVector();//得到所有敌方英雄，如果目标死亡，则值为nullptr
                        }
                        int sizev = (int)herovector.size();
                        for (int i = 0; i < sizev; i++) {
                            if (herovector[i]) {
                                Vec2 vec2 = herovector[i]->getPosition();
                                Vec2 sub_vec2 = m_fromSp_vec2.operator-(vec2);
                                float length = sub_vec2.getLength();
                                if (length <= skill_range) {
                                    targetList.push_back(herovector[i]);
                                }
                            }
                        }
                        
                        //技能特效动画显示在地面上的特殊处理
                        if (m_skillID == 200026) {
                            std::list<Vec2> skillPosList;    //技能帧动画坐标
                            //计算技能特效所在坐标
                            float value = (float)M_PI/180;
                            for (int i = 0; i < 6; i++) {
                                Vec2 vec2 = m_fromSp_vec2.operator+(cocos2d::Vec2::forAngle(60*i*value)*144);
                                skillPosList.push_back(vec2);
                                if (skill_range/144 >= 2) {
                                    Vec2 vec2_1 = m_fromSp_vec2.operator+(cocos2d::Vec2::forAngle(60*i*value)*144*2);
                                    Vec2 vec2_2 = m_fromSp_vec2.operator+(cocos2d::Vec2::forAngle((30+60*i)*value)*(144*2*cosf(30*value)));
                                    skillPosList.push_back(vec2_1);
                                    skillPosList.push_back(vec2_2);
                                }
                            }
                            skillPosList.push_back(m_fromSp_vec2);
                            
                            m_fromSp->skillIconTime = 3000;
                            while (!skillPosList.empty()) {
                                Vec2 vec2 = skillPosList.front();
                                //播放受击动画
                                m_fromSp->playHitedNoamlAction(m_skillDataST.skill_hit_resource,m_skillDataST.skill_effect_location,0,vec2);
                                skillPosList.pop_front();
                            }
                        }
                    }
                        
                        break;
                    default:
                        break;
                }
            }
        }
            break;
    }
    
    while (!targetList.empty()) {
        BaseSprite* targettmp = targetList.front();
        
        if (targettmp && !targettmp->s_isDie) {
            //冰封世界和熊变特殊处理
            if (m_skillID != 200026) {
                if (m_skillDataST.track_id != 0 || m_skillID == 200012) {
                    //播放受击动画
                    targettmp->playHitedNoamlAction(m_skillDataST.skill_hit_resource,m_skillDataST.skill_effect_location);
                }
            }
            
            for (std::list<int>::iterator it = m_skillEffectIDList.begin(); it != m_skillEffectIDList.end(); it++) {
                int SID = (*it);
                targettmp->skillEffect(m_warDataST, SID, m_skillLeve, m_skillDataST);
            }
        }
        
        targetList.pop_front();
    }
}

list<BaseSprite*> SkillAction::getRandomTargetList()
{
    std::list<BaseSprite*> targetList;
    int random_num = (int)(random()%m_skillDataST.skill_range)+1;
    std::vector<BaseSprite*> herovector;
    if (isHero) {//当前技能属于下方英雄，
        herovector = m_warlayer->getEnemyHeroVector();//得到所有敌方英雄，如果目标死亡，则值为nullptr
    }else{//当前技能属于上方怪物
        herovector = m_warlayer->getOurHeroVector();//得到所有敌方英雄，如果目标死亡，则值为nullptr
    }
    int sizev = (int)herovector.size();
    int real_size = 0;
    for (int i = 0; i < sizev; i++) {
        if (herovector[i]) {
            real_size++;
        }
    }
    if (real_size <= random_num) {
        for (int i = 0; i < sizev; i++) {
            if (herovector[i]) {
                targetList.push_back(herovector[i]);
            }
        }
    } else {
        std::vector<int> indexvector;
        int count = 0;
        while (count < random_num) {
            int index = (int)(random()%sizev);
            if (std::find(indexvector.begin(), indexvector.end(), index) == indexvector.end() && herovector[index]) {
                targetList.push_back(herovector[index]);
                indexvector.push_back(index);
                count++;
            }
        }
    }
    return targetList;
}

void SkillAction::whenInitSkillDataEnd() //技能数据初始化结束时调用的方法
{
    
}

void SkillAction::runSkill(BaseSprite* Attacktarget)
{
    m_toSp = Attacktarget;

    if (!m_skillEffectIDList.empty()) {
        this->playSkillEffectList();
    }
}