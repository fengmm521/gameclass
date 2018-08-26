//
//  PoPUIManger.h
//  game2
//  C++单例类模板，非线程安全单例类，并且实例化后会常注内存
//
//  Created by 俊盟科技1 on 9/15/14.
//
//

#ifndef __game2__PoPUIManger__
#define __game2__PoPUIManger__

#include "cocos2d.h"
#include "ScenceLayerConfig.h"
using namespace cocos2d;
class PoPUIManger:public cocos2d::Ref
{
public:
    static PoPUIManger* sharedPoPUIManger();
    static void destroyInstance();
private:
	/**
     * @js ctor
     */
    PoPUIManger(void){};
    /**
     * @js NA
     * @lua NA
     */
    ~PoPUIManger(void){};
    
public:
    
    /**
     * Init PoPUIManger
     */
    virtual bool init();
    
    
    Sprite *bgSprite;//进度条底
    Sprite *hpSprite;//进度条
    int s_loaded;  //已加载资源数量
    int s_maxLoad; //总计加载资源数量
    ProgressTimer* progressTimer;
    ScenceChangeDataST s_st;
    
    
    void loadResInit();          //加载资源初始化
    void loadResStart();         //开始加载
    void addXML();
    void addRes();
    void OpenNewPoPLayer(ScenceChangeDataST st);  //打开界面
};

#endif /* defined(__game2__PoPUIManger__) */
