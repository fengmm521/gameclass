//
//  Box2dSprite.h
//  game1
//  精灵类，主要用来创建一些定制的精灵动画。
//  Created by 俊盟科技1 on 9/5/14.
//
//

#ifndef __game1__Box2dSprite__
#define __game1__Box2dSprite__

#include <iostream>

#include "cocos2d.h"
#include "SpriteConfig.h"
#define kSpriteBox2d 1
#define kButtleBox2d 2

class b2Body;
class b2Fixture;
class Box2dWordManger;
class WarScenceLayer;
class Box2dSprite:public cocos2d::Sprite
{
public:
     CREATE_FUNC(Box2dSprite);
    b2Body* s_b2body;           //精灵所带钢体
    bool s_isMove;    //是否正在移动中
    bool s_isMoveForBox2d; //是否正在追击敌人中
    int box2dSpriteType;    //当前精灵类型,1.战斗精灵，2.子弹，3.技能
    WarScenceLayer* m_warLayer; //战场
    virtual bool init();
    virtual void Attack();
    virtual void onEnter();
    virtual void onExit();
    virtual void removeFromeWarScence();
};


#endif /* defined(__game1__Box2dSprite__) */
