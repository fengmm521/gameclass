//
//  BloodNumber.h
//  game1
//
//  Created by 俊盟科技1 on 8/20/14.
//  血量显示数字
//

#ifndef __game1__BloodNumber__
#define __game1__BloodNumber__

#include <iostream>

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;
class BloodNumber:public cocos2d::Sprite
{
    public:
        virtual void onEnter();
        virtual void onExit();
        virtual bool init();
        void setData(int index);
        int currIndex;
        CREATE_FUNC(BloodNumber);
        string getSprite(int i);
};


#endif /* defined(__game1__BloodNumber__) */
