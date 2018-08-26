//
//  LoadingScence.cpp
//  game1
//
//  Created by 俊盟科技1 on 9/4/14.
//
//

#include "LoadingScence.h"
#include "ScenceManger.h"
#include "SplitDataConfig.h"
#include "LocalDataManger.h"
// on "init" you need to initialize your instance
using namespace cocos2d;

Scene* LoadingScence::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadingScence::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool LoadingScence::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    do
    {
        s_st = ScenceManger::sharedScenceManger()->nextSt;
        
        //进度条背景
        bgSprite = Sprite::create("bloodbarbg.png");
        addChild(bgSprite, 0, 0);

        hpSprite = Sprite::create("jindutiao.png");//资源加载进度条
        progressTimer = ProgressTimer::create(hpSprite);
        progressTimer->setType(ProgressTimer::Type::BAR);
        
        progressTimer->setMidpoint(Point(0, 0.5));
        progressTimer->setBarChangeRate(Point(1, 0));
        
        progressTimer->setPercentage(0);//满值 100%
        
        addChild(progressTimer, 0, 0);
        
        
        
        s_loaded = 0;
        s_maxLoad = 0;
        s_xmlLoadList.clear();
        s_resLoadList.clear();
        loadDataInit();
    }while(0);
    
    return true;
}
void LoadingScence::loadDataInit()
{
    int num = s_st.number;
    switch (num) {
        case kScenceLogin://登陆游戏场景
        {
            
        }
            break;
        case kScenceMainCity://游戏主城场景
        {
            
        }
            break;
        case kScenceWar://游戏关卡战斗场景
        {
            addXml(1001);
            addXml(1002);
            addXml(1003);
            addXml(1004);
            addRes("");
            loadStart();
        }
            break;
        default:
            break;
    }
}
//添加一个资源到加载列表
void LoadingScence::addRes(std::string res)
{
    
}
//添加一个xml加载项到列表
void LoadingScence::addXml(int n)
{
    
}
void LoadingScence::loadStart() //开始载入资源
{
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    if (!s_xmlLoadList.empty()) {
        int swi = s_xmlLoadList.front();
        s_xmlLoadList.pop_front();
        loadXml(swi);
        
        
    }else if(!s_resLoadList.empty())
    {
        std::string filen = s_resLoadList.front();
        s_resLoadList.pop_front();
        loadRes(filen);
    }
    
}
void LoadingScence::loadXml(int n)
{
    switch (n) {
        case 1001:
//        {
//            LocalDataManger::sharedLocalDataManger()->readConfigTable1001Data();
//        }
//            break;
//        case 1002:
//        {
//            LocalDataManger::sharedLocalDataManger()->readConfigTable1002Data();
//        }
//            break;
//        case 1003:
//        {
//            LocalDataManger::sharedLocalDataManger()->readConfigTable1003Data();
//        }
//            break;
//        case 1004:
//        {
//            LocalDataManger::sharedLocalDataManger()->readConfigTable1004Data();
//        }
//            break;
//        case 1005:
//        {
//            LocalDataManger::sharedLocalDataManger()->readConfigTable1004Data();
//        }
//            break;
//        case 1006:
//        {
//            LocalDataManger::sharedLocalDataManger()->readConfigTable1004Data();
//        }
//            break;
//        case 1007:
//        {
//            LocalDataManger::sharedLocalDataManger()->readConfigTable1004Data();
//        }
//            break;
//        case 1008:
//        {
//            LocalDataManger::sharedLocalDataManger()->readConfigTable1004Data();
//        }
//            break;
//        case 1009:
//        {
//            LocalDataManger::sharedLocalDataManger()->readConfigTable1004Data();
//        }
//            break;
//        case 1010:
//        {
//            LocalDataManger::sharedLocalDataManger()->readConfigTable1004Data();
//        }
            break;
        default:
            break;
    }
}
void LoadingScence::loadRes(std::string filename)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename.c_str());
}
void LoadingScence::updateBar()//更新进度条显示
{
    
}