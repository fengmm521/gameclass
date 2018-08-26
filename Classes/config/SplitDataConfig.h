//
//  SplitDataConfig.h
//  game3
//  使用结构体来进行游戏属性存储会比较方便快捷
//
//  Created by 俊盟科技1 on 9/20/14.
//
//

#ifndef game3_SplitDataConfig_h
#define game3_SplitDataConfig_h

//怪物序列,英雄ID,类别,品质,星级,等级,位置
struct CheckPoint_monsters_struct
{
    int ID = 0;
    int type =0;
    int pinzhi =0;
    int star = 0;
    int leve = 0;
    int space = 0;
};
typedef struct CheckPoint_monsters_struct CheckPointMonstersST;

//副本数据表怪物掉落
//作者:
//ID,数量,概率,节点次数;ID,数量,概率,节点次数
//
//概率：
//
//概率是万分比
//
//节点次数：
//到了掉落节点，概率忽视，直接掉落
struct CheckPoint_Drop_itemsStruct
{
    int ID = 0;
    int count = 0;
    int gailv = 0;
    int dropCount =0;
};
typedef struct CheckPoint_Drop_itemsStruct DropItemsST;

#endif
