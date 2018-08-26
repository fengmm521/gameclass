//
//  OnlyMarkingManger.h
//  game1
//  C++单例类模板，非线程安全单例类，并且实例化后会常注内存
//
//  Created by 俊盟科技1 on 8/22/14.
//
//
/********************************
  游戏唯一标识生成管理器，使用系统时间，每一次只生成一个唯一的标识符，用来在程序中区分不同调用

************************************/

#ifndef __game1__OnlyMarkingManger__
#define __game1__OnlyMarkingManger__

#include "cocos2d.h"
class OnlyMarking
{

public:
    //获取一个唯一标识符,所谓唯一标识符，即每一次取的值都不能一样,这里只保证在一定时间定不重复就可以了
    static std::string getNewMarking();
    
};

#endif /* defined(__game1__OnlyMarkingManger__) */
