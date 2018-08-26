//
//  WarConfig.h
//  game1
//  使用结构体来进行游戏属性存储会比较方便快捷
//
//  Created by 俊盟科技1 on 8/20/14.
//
//

#ifndef game1_WarConfig_h
#define game1_WarConfig_h

//怒气相关

#define kMaxAnger            1000

#define kAddAngerNomalAttack 100
#define kAddAngerSkillAttack 100
#define kAddAngerAoyiAttack  100
#define kAddAngerKill        300
#define kAddAngerKillSummon  100
#define kAddAngerBeAttack    50

//怒气增加方式
enum AngerAddTypeENUM
{
    e_nomalAttack = 1,  //普通攻击
    e_skillAttack,      //技能攻击
    e_aoyiAttack,       //奥义攻击
    e_kill,             //击杀
    e_killSummon,       //击杀召唤
    e_beAttack          //被攻击
};

typedef enum AngerAddTypeENUM AngerAddTypeE;

//战斗位置相关
#define kAttackSpaceMax 6      //每个角色的最大近战攻击位
//战斗位置的相对矢量
//当前精灵的攻击位上是否有精灵，精灵近战攻击位编号如下
/*
     1   6
    2  s  5
     3   4
 */
//1 = 135度，
//2 = 180度，
//3 = -135度，
//4 = -45度，
//5 = 0度，
//6 = 45度。

#define kAttackJiaoDu1 (150.0f)   //135
#define kAttackJiaoDu2 (180.0f)
#define kAttackJiaoDu3 (-150.0f)  //-135
#define kAttackJiaoDu4 (-30.0f)   //-45
#define kAttackJiaoDu5 (0.0f)
#define kAttackJiaoDu6 (30.0f)    //45

#define kdistancep      1.0f

#define kdistancep1     kdistancep
#define kdistancep2     1.0f
#define kdistancep3     kdistancep
#define kdistancep4     kdistancep
#define kdistancep5     1.0f
#define kdistancep6     kdistancep


#define kUserHeroNumber 5  //我方英雄最大数量

typedef struct warHeroDataST
{
    int heroID = 0;
    int star = 0;
    int leve = 0;
    int pinzhi = 0;
    int exp = 0;
}WarHeroData;


#endif
