//
//  AnimationConfig.h
//  game1
//  使用结构体来进行游戏属性存储会比较方便快捷
//
//  Created by 俊盟科技1 on 8/20/14.
//
//

#ifndef game1_AnimationConfig_h
#define game1_AnimationConfig_h


//角色动画类型，当前有两种动画类型，
//1.英雄动画类型：站立，移动，普攻，普通技能*1，奥义技能*1，胜利，死亡，受击，个性动作（待定），共9个动作资源
//
//
//所有动画默认都是向右边，由程序进行反转
#define kAnimationStand      "Stand"     //站立
#define kAnimationRun        "Run"       //移动
#define kAnimationDie        "Die"       //死亡
#define kAnimationAttack     "Attack"    //攻击
#define kAnimationCharacter  "Character" //胜利
#define kAnimationMagic01    "Magic01"   //技能1
#define kAnimationHited      "Hited"     //受击1
//精灵动画类型
enum AnimationTypeEnum
{
    e_solider = 1,
    e_heaos
};

typedef enum AnimationTypeEnum AnimationTypeE;


//精灵状态类型
enum SpriteTypeEnum
{
    e_warStart = 1,             //战斗开始
    e_warAutoFind,              //进入自动搜寻敌人状态
    e_warSystemFind,            //系统分配敌人状态
    e_warWait,                  //等待状态
    e_warRunTo,                 //向目标位置移动状态
    e_warAttack,                //攻击状态
    e_warBeAttack,              //被攻击状态
    e_warSkill,                 //释放技能准备状态
    e_warSkillRleas,            //释放技能动画状态
    e_warSkillAction,           //释放技能效果状态
    e_warDie,                   //死亡状态
    e_warCharacter,             //战斗胜利状态
    e_null,
};

typedef enum SpriteTypeEnum SpriteTypeE;

enum SpriteStateEnum
{
    e_stateIn = 1,
    e_stateOut,
    e_stateNull
};

typedef enum SpriteStateEnum StateInOrOut;

enum SpriteAnimationEnum
{
    e_AniStand=1,               //等待状态
    e_AniRun,                   //向目标位置移动状态
    e_AniAttack,                //攻击状态
    e_AniBeAttack,              //被攻击状态
    e_AniMagic01,               //释放攻击
    e_AniDie,                   //死亡状态
    e_AniCharacter,             //战斗胜利状态
    e_AniNull
};

typedef enum SpriteAnimationEnum SPAnimationTypeE;


#endif
