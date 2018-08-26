//
//  SkillOwnerDelegate.h
//  game3
//
// 代理类，主要用为作接口使用。
//
//  Created by 俊盟科技1 on 10/15/14.
//
//

#ifndef __game3__SkillOwnerDelegate__
#define __game3__SkillOwnerDelegate__

#include "cocos2d.h"
class Box2dSprite;
class WarScenceLayer;
class BaseSprite;
class SkillOwnerDelegate
{
private:
    ~SkillOwnerDelegate(){};
public:
    virtual WarScenceLayer* getWarLayer() = 0;
    virtual int getBaseAttackValue() = 0;
    virtual BaseSprite* getFromSprite() = 0;
    virtual Box2dSprite* getOwerSprite() = 0;
    virtual cocos2d::Point getAttackTargetPoint() = 0;
    virtual BaseSprite* getAttackTarget() = 0;
};



#endif /* defined(__game3__SkillOwnerDelegate__) */
