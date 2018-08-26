//
//  ObjectMassageManger.h
//  game3
//  C++单例类模板，非线程安全单例类，并且实例化后会常注内存
//类对象通信管理器,负责不同对象之间的交互
//
//  Created by 俊盟科技1 on 11/4/14.
//
//

#ifndef __game3__ObjectMassageManger__
#define __game3__ObjectMassageManger__

#include "cocos2d.h"
class ObjectMassageManger:public cocos2d::Ref
{
public:
    static ObjectMassageManger* sharedObjectMassageManger();
    static void destroyInstance();
private:
	/**
     * @js ctor
     */
    ObjectMassageManger(void);
    /**
     * @js NA
     * @lua NA
     */
    ~ObjectMassageManger(void);
    
public:
    
    /**
     * Init ObjectMassageManger
     */
    virtual bool init();
    
    
    
    
};

#endif /* defined(__game3__ObjectMassageManger__) */
