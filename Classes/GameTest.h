//
//  GameTest.h
//  game3
//
//  Created by 俊盟科技1 on 10/20/14.
//
// 游戏界面
//
#ifndef __game3__GameTest__
#define __game3__GameTest__

#include "cocos2d.h"

using namespace cocos2d;


class GameTest : public cocos2d::Layer
{
public:
    virtual bool init();
    // a selector callback
    
    CREATE_FUNC(GameTest);
    
    virtual void onExit();
    virtual void onEnter();
    
    TMXTiledMap* tmap;
    
};
#endif /* defined(__game3__GameTest__) */
