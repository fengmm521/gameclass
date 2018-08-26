//
//  ScenceLayerConfig.h
//  game1
//  使用结构体来进行游戏属性存储会比较方便快捷
//
//  Created by 俊盟科技1 on 9/4/14.
//
// 全部游戏场景宏定义
//

#ifndef game1_ScenceLayerConfig_h
#define game1_ScenceLayerConfig_h
#include "cocos2d.h"
//游戏场景编号,每增加一个场景顺序增加相应编号
#define kScenceLoading  1       //场景数据加载过度场景
#define kScenceMainCity 2       //主城场景
#define kScenceLogin    3       //登陆场景
#define kScenceWar      4       //战斗关卡场景
#define kPoPFuBeiUILayer 5      //副本弹出界面
#define kPoPHeroUILayer  6      //角色属性面板界面
//场景切换时要传送给下一个场景的结构体参数
struct ScenceChangeDataStruct
{
    std::vector<std::string> strVector;
    std::vector<cocos2d::Ref*> refVector;
    std::vector<int> intVector;
    std::vector<float> floatVector;
    int tag = 0;
    bool flog = 0;
    int type = 0;                                   //场景切换动画类型
    int number = 0;                                 //切换到的目标场景
    std::string str = "";
    cocos2d::Ref* target = nullptr;
    void* pVoid = nullptr;
};

typedef struct ScenceChangeDataStruct ScenceChangeDataST;

#endif
