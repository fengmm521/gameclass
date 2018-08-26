//
//  ScenceManger.h
//  game1
//  C++单例类模板，非线程安全单例类，并且实例化后会常注内存
//
//  Created by 俊盟科技1 on 9/4/14.
//
//  游戏场景切换管理单例类，负责所有场景切换时将要加载和释放资源
//以及加载过度场景的切入与切出
//

#ifndef __game1__ScenceManger__
#define __game1__ScenceManger__

#include "cocos2d.h"
#include "ScenceLayerConfig.h"
#include "LoadingScence.h"
class ScenceManger:public cocos2d::Ref
{
public:
    static ScenceManger* sharedScenceManger();
    static void destroyInstance();
private:

    ScenceManger(void);

    ~ScenceManger(void);
    
public:
    
    int lastScenceNumber;   //上次场景
    int newScenceNumber;    //将要打开的场景编号
    bool isLoading;         //场景是否加载结束
    ScenceChangeDataST nextSt;//下一个场景加载传递参数
    
    cocos2d::Scene* lastScence; //上一个场景
    
    //不带参数，切换到编号场景
    void changeScenceTo(int scenceNumber);
    //代有场景切换参数的场景切换
    void changeScenceTo(ScenceChangeDataST st);
    /**
     * Init ScenceManger
     */
    virtual bool init();
    
    bool getFlog(std::string str);
    void setFlog(std::string str);
    
    //清除内存空间
    void cleanMemery(std::string plist);
    
private:
    LoadingScence* s_loadScence;
    //新场景加载资源,显示加载资源界面
    void loadResForScence();
    void loadResEnd();//资源加载结束
    std::map<std::string,bool> m_loadFlog;
};

#endif /* defined(__game1__ScenceManger__) */
