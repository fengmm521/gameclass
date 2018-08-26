//
//  SkillBullet.h
//  game3
//  精灵类，主要用来创建一些定制的精灵动画。
//  技能子弹，普通攻击也是一种技能，所以普通攻击也使用当前技能子弹
//  Created by 俊盟科技1 on 10/15/14.
//
//

#ifndef __game3__SkillBullet__
#define __game3__SkillBullet__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Box2dSprite.h"
#include "LocalDataConfig.h"
using namespace cocos2d;
class BaseSprite;
class SkillAction;
class WarScenceLayer;
class SkillBullet:public Box2dSprite
{
protected:
    ~SkillBullet();
    SkillBullet();
public:
    
    virtual bool init();
    virtual void Attack(); //进行一次攻击
    virtual void onEnter();
    virtual void onExit();
    
    static SkillBullet* createSkillBullet(BaseSprite* fromSP,BaseSprite* toSP,Point* startPo,Point* toPo,int buttleID,int skillID,int skillLeve);
    
    SkillAction* m_owerSkill;
    //-------------------
    BaseSprite* m_fromSp;       //子弹发射角色
    BaseSprite* m_toSp;         //子弹攻击角色
    Point m_startPoint;         //起始坐标
    Point m_endPoint;           //结束坐标
   // bool isFaceRight;           //角色面对方向
    
    Configtab_skill_trajectoryDataST bulletDataST; //弹道数据
    float m_Direction;          //子弹攻击方向
    int m_skillID;              //技能子弹技能效果编号，
    int m_skillLeve;    //当前技能等级
    
    //战斗属性
    SpriteWarDataST m_warData;
    //所有子弹的初始方向都是向右
    cocostudio::Armature *armature; //子弹动画
    //子弹图片名
    Sprite* m_buttleImageSp;
    //WarScenceLayer* m_warLayer;          //战斗场景
    //    id                    子弹编号
    int m_ID; //弹道轨迹
    int m_moveSpeed;            //子弹移动速度
    //    子弹编号	子弹动画类型	子弹移动动画或图片名	子弹消失动画图片名
    
    //新数据表中的数据
    int track_type;        //弹道类型
    std::string bullet_texture;        //弹道贴图
    int speed;        //飞行速度
    //新数据表数据结束
    
    void initLocalAction();
    void addBox2dBodyForButtle();
    void removeBox2dBodyForButtle();
    void playEndAction();
    virtual void removeFromeWarScence();
public:
    
    void bulletStartMove();
    //攻击的目标死亡监听
    void toSpriteDieCallBack(std::string name,Ref* sp);
    //清除角色死亡监听
    void cleanDieListion();
};


#endif /* defined(__game3__SkillBullet__) */
