//
//  TimeUtil.h
//  game2
//  这个是创建一些基本的cocos2d类时会用到
//  Created by 俊盟科技1 on 9/11/14.
//
//

#ifndef __game2__TimeUtil__
#define __game2__TimeUtil__

#include "cocos2d.h"
using namespace std;
class TimeUtil
{
protected:
    TimeUtil(){};
    virtual ~TimeUtil(){};
public:
    //将秒数转换为形如时分秒的时间 hh:mm:ss
    static string secendToString_M_S(int secend);
    static string secendToString_H_M_S(int secend);
    static string secendToString_D_H_M_S(int secend);
    
};
#endif /* defined(__game2__TimeUtil__) */
