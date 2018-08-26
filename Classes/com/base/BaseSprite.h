//
//  BaseSprite.h
//  game1
//  精灵类，主要用来创建一些定制的精灵动画。
//  Created by 俊盟科技1 on 8/20/14.
//  精灵基础类，这里包括精灵的基本属性
//

#ifndef __game1__BaseSprite__
#define __game1__BaseSprite__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "AnimationConfig.h"
#include "LocalDataManger.h"
//#include "BloodBar.h"
#include "AngerBar.h"
#include "CallBackVo.h"
#include "SkillBullet.h"
#include "Box2dSprite.h"
//#include "SkillEffectDelegate.h"
class BloodBar;
class b2Body;
class b2Fixture;
class Box2dWordManger;
class BaseSkill;

//class Skill;
class SkillAction;
using namespace cocos2d;
using namespace std;


//class BaseSprite:public Box2dSprite,SkillEffectDelegate
class BaseSprite:public Box2dSprite
{
public:
    ~BaseSprite(){};
    //属性
    BloodBar* m_bloodBar; //血条
    AngerBar* m_angerBar; //能量条
    cocostudio::Armature* armature;   //骨格动画
    bool isSkillPaused; //英雄是否被技能定住
    
    //英雄属性数值
    int m_ID;
    Configtab_card_attribute_sysDataST m_heroDataST;       //英雄数据
    int s_bloodValue;       //血量--

    SpriteWarDataST m_warData; //角色战斗数据
    //通过英雄的力量，智力，敏捷初始化英雄的生命
    
    //初始化英雄战斗数据
    void initHeroWarData();
    //获取英雄战斗数据
    SpriteWarDataST getHeroWarData();
    
    //战斗相关数据
    bool m_isFaceRight;     //当前角色所属阵容,下方向右，上方向左
    bool m_isNowFaceRight;  //当前精灵面向方向
    bool s_isDie;               //当前精灵是否死亡
    bool m_isCanChangeTarget;   //当前角色是否可更改攻击目标
    int  m_spaceNumber;         //精灵所在阵形编号(出场位)
    
    Point s_beBulltePoint;     //被子弹攻击坐标点
    Point s_bulltePoint[6];    //普通攻击坐标点
    Point s_beBuffPoint;       //buff坐标点
    
    //初始化技能受击与释放坐标点
    void initAllPoint();
    
    
    //物理引擎
    Box2dWordManger* s_b2WordManger;  //物理世界
    //精灵钢体上所有的碰撞检测体,每有一个敌人或者子弹追杀当前精灵时，其就会给当前精灵增加一个磁撞检测体，本碰撞检测体maskBits为0,表示不与安装碰撞体之后的其他作何物体作碰撞检测。
    b2Fixture* s_arrackRangeFixture;    //攻击范围碰撞形状
    
    map<Box2dSprite*,b2Fixture*> s_fixtureMap;  //被攻击时的碰撞体
    void initBox2dBodyWithAttackRange();
    void removeBox2dBodyWhenDie();
    void AddFixtureIndexForSprite(Box2dSprite* sp);
    void removeFixtureForSprite(Box2dSprite* sp);
    //增加目标物理碰撞体，并设置自已为物理引擎驱动方式移动
    void addBox2dForAttack();
    
//    //精灵类型，
//    //我方英雄：1
//    //我方小兵: 2
//    //敌方英雄: 3
//    //敌方小兵: 4
    //角色类型
    SpriteSpaceType s_spriteSpaceType;
    
    //单体攻击时的目标精灵
    BaseSprite* m_targetSp;   //目标精灵
    ui::Button* m_skillRealesBtn;//技能释放按钮
    
    
    //游戏角色ＵＩ
    ui::Layout* hero1Layout;
    ui::ImageView* heroicon1;
    ui::ImageView* hero1StarVector[5];
    cocostudio::Armature* hero1skill; //能量满动画
    
    void initHeroIconButton();
    void initHeroStar();
    void setHeroSkillAction(cocostudio::Armature* heroAc);
    void showSkillBtnUsed();
    
    bool isPlayStart;
    bool isShowSKill;
    bool isSkillRun;
    bool isSkillCanStop;   //技能是否可打断状态
    
    
    
    void showSkillBtnUsedplayStart();
    void showSkillBtnUsedplayEnd();
    void unShowSkillBtnUsed();
    
    void setAngerSliderUI(ui::LoadingBar* angSlider);
    void setBloodSliderUI(ui::LoadingBar* bloodSlider);
    void setSkillRealesButton(ui::Button* skillBtn);
    void  buttonSkillEvent(Ref *pSender, ui::Widget::TouchEventType   type);
    
    bool m_isSkillButtonTouched;
   
    //战斗普通攻击序列
public:
    int m_attackPCount;      //战斗攻击的序列计数器
    int m_nowAttackPCount;   //当前战斗序列号
    int m_firstAttackSkillArr[6]; //战斗攻击序列
    int m_nomalAttackSkillArr[6]; //战斗攻击序列
    bool m_isFirstAttackSkill;
    void initHeroSkillAttackList();//初始化技能序列，hero_skillrelease_rule
    
    
    
    //注册状态改变监听及分发
    void registerStateChangeEventListen(SpriteTypeE state,StateInOrOut inOrOut,cocos2d::Ref* ins,Event_CallBackStr selector);
    void unregisterStateChangeEventListen(SpriteTypeE state,StateInOrOut inOrOut,cocos2d::Ref* ins,Event_CallBackStr selector);
    void unregisterStateChangeWhenDie();
    void onStateChangeEvent(SpriteTypeE state,StateInOrOut inOrOut);
    
protected:
    //精灵当前状态模式，由其来设计当前精灵状态机
    SpriteTypeE s_spriteType;
    //其他要监听当前精灵的状态的容器，当前精灵状态发生改变时，会通知相关精灵其状态改变
    StateInOrOut s_stateInOrOut;
    map<int,std::list<Ref*>> s_spriteObserver;
    //精灵当前状态更新,分发状态更新消息
    void updataState(SpriteTypeE stateNew,StateInOrOut inOrOutNew);
    
public:
    //方法
    //创建对象
    static BaseSprite* createWithID(int ID,WarScenceLayer* warLayer,bool isFaceRight,int spLeve,int skillleve1,int skillleve2,int skillleve3,int skillleve4,int skillleve5,int skillleve6);
    //初始化
    virtual bool init();
    virtual void onExit();
    virtual void onEnter();
    //数据
    void loadNetData();
    void loadLocalData();
    void initBaseAction();

    //战斗相关
    void warReady();          //战场准备
    void warStart(bool isFirst = false);          //战场战斗开始
    void warEnd();            //战场战斗结束
    virtual void Attack();                  //攻击锁定目标
    virtual void removeFromeWarScence();
    //调整攻击位置
    void moveToTiledPoint();    //移动到某个瓦片地图块
    Point m_TiledPoint;         //瓦片地图坐标
    int santdPoint;             //站立位置
    void moveToTiledPointEnd(); //移动到某个瓦片地图动作结束
    void findAttackTarget();    //在战场寻找可攻击目标
    //定时寻找可攻击目标定时器
    void findAttackTarget(float dt);
    void moveFindAttackTarget(float dt);//寻找离自已最近的目标定时器
    //攻击间隔
//    void attackDelayTime(float dt);
    
    void lockAttackTarget(BaseSprite* sp,bool isMastAttack = false);//锁定攻击目标
    
    //战斗状态改变事件
    void onEnamyDie(string name,cocos2d::Ref* sp); //敌人死亡
    void warBloodEmpty();    //已经空血
    //能量满了时，释放技能
    void playSkill();
    void playSkillActionEnd();
    
    //怪物能量满，可释放技能
    void playEnemySkill();
    
    
    int s_stateShow; //当前精灵状态
    void attackTarget(); //攻击目标,播放一次普通攻击动画
    
    //战斗相关
    //追击,是否必须攻击一次目标才可更改目标
    void pursueAttack(bool isMastAttack = false);
    void setSpaceNumber(int number); //设置精灵出场时的位置
    void cleanBox2dAndAttackTarget(); //取消一个攻击目标，当角色移动时
    
protected:
    //动画动作
    int m_nowPlayAction;
    
    //设置精灵面向
    void setFaceRight();      //面向右
    void setFaceLeft();       //面向左
    
    void playStandAction();    //站立动画
    void playRunAction();      //移动动画
    void playDieAction();      //死亡动画(动画结束帧事件)
    void playAttackAction();   //攻击动画(攻击伤害和攻击结束事件)
    void playCharcterAction(); //战斗胜利动画
    void playMagic01Action();  //技能动画(技能开始，释放，结束3事件)
    void playHitedAction();  //受攻击中断事件(动画结束事件)
    
    //定时器
    void playStandAction(float dt);   //站立动画
    void playRunAction(float dt);     //移动动画
    void playDieAction(float dt);     //死亡动画(动画结束帧事件)
    void playAttackAction(float dt);  //攻击动画(攻击伤害和攻击结束事件)
    void playCharcterAction(float dt);//战斗胜利动画
    void playMagic01Action(float dt); //技能动画(技能开始，释放，结束3事件)
    void playHitedAction(float dt);   //受攻击事件(动画结束事件)
    
    
    //动画帧事件回调
    void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
    //技能动画帧事件回调
    void onFrameSkillBtnEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
    
    //技能播放动画帧事件回调
    void onFrameSkillPlayEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
    
    
    //动画帧事件响应方法
    //普通攻击帧事件
    void frameAttackStart();
    void frameAttackEnd();
    void frameHitedEnd();
    
    
    //奥义技能帧事件
    void magic01Ready();
    void magic01Start();
    void magic01End();
    //死亡动画结束帧事件
    void dieActionEnd();
    
    
public:
    bool isTouchMove;
    void touchMoveToPosition(Point po,CallFunc* func = nullptr);//点击移动到某点,以及移动结束回调
    void touchMoveToSprite(BaseSprite* sp);
    void moveToPosition(Point po,CallFunc* func = nullptr);
    void moveToCallBack();//精灵移动到某个点之后的回调方法
    
public:
    //技能攻击设计思路
    void playHitedNoamlAction(string ActionName,int pointType = 0,int layerType = -1,Vec2 vec2 = Vec2(0,0)); //普通无打断受击动画,0:头部，1:身体，2:下部
    int skillIconTime;  //技能图片持续时间
private:
    //所有可能的技能作用效果,主动技能型，需要玩家手动触发来释放
    //播放技能buff动画time秒
    void loadSkillBuffActionWithSkillID(int ID);
    void playBuff(std::string buffName,float time,int pointType = 0);
    Sprite* buffIcon;
    cocostudio::Armature* beAttackArm;
//    std::list<cocostudio::Armature*> buffList;
//    std::list<Sprite*> buffIconList;
    
//-------------------------------
//初始化时角色的被动技能设置,使用被动技能ID初始化角色
    //被动技能特别，增加基本属性，如攻击力，生命值，防御，三围等
    void initLocalSkill(int skillID);
public:
    //战斗中的选中操作显示
    //当友方被选中时显示选中框
    cocostudio::Armature* m_selectArmature;   //选中骨格动画
    cocostudio::Armature* m_attackArmature;   //攻击骨格动画
    
    bool m_isShowSelect;
    void setShowSelectMove(bool isShow);
    //当攻击的敌人被选中时，显示红色框
    bool m_isShowAttack;
    void setShowAttackSelect(bool isShow);
    
//------------------
public:
//技能效果代理方法
    void skillEffect(SpriteWarDataST warData,int skillEffectID,int skillLevel,Configtab_skill_visual_effectDataST m_skillDataST);
    //-1普通造成伤害效果,attackValue:计算后得到的攻击伤害值,hited:攻击方的命中
    void skillEffectNomal(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat);
    
    //1眩晕效果,time:眩晕时间
    void skillEffect1Dizziness(float time,std::string buffname = "");
    //2击退效果,direction:击退方向，Length:击退距离
    void skillEffect2Repelling(float direction,int Length,int speed,std::string buffname = "");
    //3中毒,time:中毒总时间,steptime:伤害间隔,Injury:单次伤害值
    void skillEffect3Poison(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel);
    //4燃烧
    void skillEffect4Combustion(float time,float steptime,int ingury,std::string buffname = "");
    //5沉默
    void skillEffect5Silence(float time,std::string buffname = "");
    //6定身
    void skillEffect6DecidesTheBody(float time,std::string buffname = "");
    //7拉拽
    void skillEffect7Entrains(float direction,int Length,int speed,std::string buffname = "");
    //8流血
    void skillEffect8Bleeding(float time,float steptime,int ingury,std::string buffname = "");
    //9生命
    void skillEffect9Life(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel);
    //10物理暴击
    void skillEffect10PhysicalBaoJi(float time,int value,std::string buffname = "");
    //11魔法暴击
    void skillEffect11MagicBaoJi(float time,int value,std::string buffname = "");
    //12闪避
    void skillEffect12Fending(float time,int value,std::string buffname = "");
    //13命中
    void skillEffect13Hit(float time,int value,std::string buffname = "");
    //14魔抗
    void skillEffect14MagicResistance(float time,int value,std::string buffname = "");
    //15物防
    void skillEffect15PhysicalDefense(float time,int value,std::string buffname = "");
    //16物理攻击
    void skillEffect16PhysicalAttack(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel);
    //17魔法攻击
    void skillEffect17MagicAttack(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel);
    //18吸血
    void skillEffect18Hemophagia(float time,float pecent,std::string buffname = "");
    //19力量
    void skillEffect19Strength(float time,int value,std::string buffname = "");
    //20智力
    void skillEffect20Intelligence(float time,int value,std::string buffname = "");
    //21敏捷
    void skillEffect21Agile(float time,int value,std::string buffname = "");
    //22移动速度
    void skillEffect22MoveSpeed(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel);
    //23攻击速度
    void skillEffect23AttackSpeed(float time,int value,std::string buffname = "");
    //24免疫物理攻击
    void skillEffect24NoPhysicalAttack(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel);
    bool isNoPhysicalAttack;
    //25免疫魔法攻击
    void skillEffect25NoMagicAttack(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel);
    bool isNoMagicAttack;
    //26无敌
    void skillEffect26Invincible(float time,std::string buffname = "");
    //27能量
    void skillEffect27Energy(float time,int value,std::string buffname = "");
    //28虚弱
    void skillEffect28Weak(float time,int value,std::string buffname = "");
    //29易伤
    void skillEffect29EasyBeInjured(float time,int vlaue,std::string buffname);
    //30反射
    void skillEffect30Reflection(float time,float pencent,std::string buffname = "");
    //31减伤
    void skillEffect31SubAttack(float time,int value,std::string buffname = "");
    //32圣盾
    void skillEffect32SaintShield(float time,int value,std::string buffname = "");
    //33免疫负面效果
    void skillEffect33NoDebuff(float time,std::string buffname = "");
    //34冰冻
    void skillEffect34Ice(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel);
    //35恐惧
    void skillEffect35Frightened(float time,std::string buffname = "");
    //36抑制治疗
    void skillEffect36SuppressesTreatment(float time,float pencent,std::string buffname = "");
    //37无视物理防御
    void skillEffect37NoPhysicalDefense(float time,std::string buffname = "");
    //38无视法术抗性
    void skillEffect38NoMagicResistance(float time,std::string buffname = "");
    //39束缚
    void skillEffect39Fetter(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel);
    //40魅惑
    void skillEffect40Attracting(float time,std::string buffname = "");
    //41召唤
    void skillEffect41Summon(float time,int spriteID,std::string buffname = "");
    //42复活
    void skillEffect42Relive(float time,std::string buffname = "");
    //43变身
    void skillEffect43ChangeBody(Configtab_skill_effectDataST effectdat,Configtab_skill_visual_effectDataST m_skillDataST);
    //预加载变身后精灵动画,否则第一次变身会卡顿
    void preLoadChangeBody();
    //技能变身结束
//    void skillEffect43timer(float dt);
    //ID，变身后的角色ID，time,变身持续时间
    bool isChangeBody;  //当前角色是否变身
    int changeBodyOldID;   //变身之前的动画ID
    cocostudio::Armature* changeBodyarmature;   //骨格动画
    void initChangeBodyData(int ID); //变身之后的属性初始化
    void cleanChangeBody();
    void changeAttackRange();
    //44间歇伤害，如旋风斧
    void skillEffect44TimeAttack(SpriteWarDataST warData,Configtab_skill_effectDataST effectdat,int skillLevel,Configtab_skill_visual_effectDataST m_skillDataST);
    
public:
    int m_nowSkillNumber; //当前攻击技能编号
    int m_range;          //当前释放技能攻击范围
//技能初始化
    //奥义技能,普能技能,第3技能,第4技能,第5技能,第6技能
    int m_skillID[6];    //技能ID
    int m_skillLeve[6];  //技能等级
    SkillAction* m_skill[6];   //技能
    Configtab_skill_visual_effectDataST m_skillDataST[6]; //技能数据
    map<int,int> skillIDAndLeveMap; //技能对应等级
    void initALLSkill();
    
    void playRunActionWhenWarEnd();
    void playWinActionWhenWarEnd();
    void playShowSkillEffect(float dt);
    bool isNoSkill;
    
public:
    //工具方法
    float getAttackValue(SpriteWarDataST warData, int attackType); //计算攻击值
    bool isBaoJi(SpriteWarDataST warData);
    bool isMingZhong(SpriteWarDataST warData);
    bool isPlaySkillEffect(int probability,int skillLevel);    //根据概率计算是否播放技能特效
};
#endif /* defined(__game1__BaseSprite__) */
