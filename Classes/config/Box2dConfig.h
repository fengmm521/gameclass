//
//  Box2dConfig.h
//  game1
//  使用结构体来进行游戏属性存储会比较方便快捷
//
//  Created by 俊盟科技1 on 8/30/14.
//
//

#ifndef game1_Box2dConfig_h
#define game1_Box2dConfig_h

class b2Body;
class b2Fixture;

using namespace std;


#define PTM_RATIO               32.0f//像素/米

#define kCollisionRadius        12   //像素，精灵自身的体积默认为5像素
#define kMinCollisionIndex      100  //专为精灵碰撞设置的编号最小数从101开始，最大不可大于（2的16次方－101）地图上最大碰撞检测块数量不得大于这个数
#define kMapCollisiionIndex     1    //地图碰撞默认编号为1,
//在碰撞检测之后精灵要删除的碰撞形状
struct Box2dDestroyStruct
{
    b2Body* body;
    b2Fixture* fixture;
};

typedef struct Box2dDestroyStruct Box2dDestroyCollision;


#endif
