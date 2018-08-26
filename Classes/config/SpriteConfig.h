//
//  SpriteConfig.h
//  game1
//  使用结构体来进行游戏属性存储会比较方便快捷
//
//  Created by 俊盟科技1 on 8/27/14.
//
//

#ifndef game1_SpriteConfig_h
#define game1_SpriteConfig_h


//精灵类型，
//我方英雄：s_spriteType=1
//我方小兵: s_spriteType=2
//敌方英雄: s_spriteType=3
//敌方小兵: s_spriteType=4
enum SpriteSpaceTypeEnum
{
    e_OurHero =1,
    e_OurSolider,
    e_EnemyHero,
    e_EnemySolider
};

typedef enum SpriteSpaceTypeEnum SpriteSpaceType;

#define kActionButtle  1 //骨骼动画子弹
#define kFramButtle    2 //帧动画子弹
#define kImageButtle   3 //图片子弹


//子弹攻击类型
//1.物理子弹:曲线攻击
//2.魔法子弹:直线攻击
#define kButtleAttackPhysical  1   //1.物理子弹:曲线攻击
#define kButtleAttackMagic     2   //2.魔法子弹:直线攻击

//技能效果类型
enum SpriteSkillTypeEnum
{
    e_skillNoEffect = -1,  //无效果
    e_skillDizziness = 1,  //眩晕1
    e_skillRepelling,      //击退2
    e_skillPoison,         //中毒3
    e_skillFire,           //燃烧4
    e_skillSilence,        //沉默5
    e_skillDecidesTheBody, //定身6
    e_skillEntrains,       //拉拽7
    e_skillLoseBlood,      //流血8
    e_skillAddBlood,       //生命9
    e_skillPhysicalBoJi,   //物理暴击10
    e_skillMagicBoJi,      //魔法暴击11
    e_skillFending,        //闪避12
    e_skillHit,            //命中13
    e_skillMagicResistance,//魔抗14
    e_skillPhysicalDefense,//物防15
    e_skillPhysicaAttack,  //物理攻击16
    e_skillMagicAttack,    //魔法攻击17
    e_skillHemophagia,     //吸血18
    e_skillStrength,       //力量19
    e_skillIntelligence,   //智力20
    e_skillAgile,          //敏捷21
    e_skillMoveSpeed,      //移动速度22
    e_skillAttackSpeed,    //攻击速度23
    e_skillNoPhysicaAttack,//物理攻击免疫24
    e_skillNoMagicAttack,  //魔法攻击免疫25
    e_skillInvincible,     //无敌26
    e_skillEnergy,         //能量27
    e_skillXuRuo,          //虚弱28
    e_skillAddAttack,      //伤害加成29
    e_skillReflection,     //反射30
    e_skillReducesTheWound,//减伤31
    e_skillSaintShield,    //圣盾，吸收伤害32
    e_skillNoSkillBuff,    //免疫负面效果33
    e_skillIceBuff,        //冰冻34
    e_skillFrightened,     //恐惧35
    e_skillSuppressesTt,   //抑制制疗36
    e_skillNoPhysicalDef,  //无视物理防御37
    e_skillNoMagicDef,     //无视魔法抗性38
    e_skillFetter,         //束缚39
    e_skillAttracting,     //魅惑40
    e_skillSummon,         //召唤41
    e_skillReactivating,   //复活42
    e_skillChangeBody,     //变身43
};
typedef enum SpriteSkillTypeEnum SkillEfectTypeE; //技能效果类型

struct SpriteWarDataStruct
{
    
    //--------------------------------
    //角色属性
    //由属性计算的数值
    int s_leve;                 //角色等级
    int s_attack;               //物攻
    int s_Defense;              //物防
    int s_magicAttack;          //法攻
    int s_magicDefense;         //法防
    float s_BaoJiProbability;   //暴击值
    float s_Fending;            //命中值
    int s_evade;                //闪避值
    
    int s_strength;     //品质及星级之后的最终力量
    int s_intelligence; //品质及星级之后的最终智力
    int s_agile;        //品质及星级之后的最终敏捷
};

typedef struct SpriteWarDataStruct SpriteWarDataST;

#endif
