//
//  Box2dSprite.cpp
//  game1
//
//  Created by 俊盟科技1 on 9/5/14.
//
//

#include "Box2dSprite.h"
void Box2dSprite::onEnter()
{
    Sprite::onEnter();
}
void Box2dSprite::onExit()
{
    Sprite::onExit();
}
bool Box2dSprite::init()
{
    //////////////////////////////
    // 1. super init first
    if (!cocos2d::Sprite::init()) {
        return false;
    }
    bool bRet = false;
    do
    {
        s_isMoveForBox2d = false;
        box2dSpriteType = kSpriteBox2d;
        s_b2body = nullptr;
        bRet = true;
    }
    while (0);
    
    return bRet;
}
void Box2dSprite::Attack()
{
    
}
void Box2dSprite::removeFromeWarScence()
{
    
}