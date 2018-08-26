//
//  ScenceManger.cpp
//  game1
//
//  Created by 俊盟科技1 on 9/4/14.
//
//

#include "ScenceManger.h"
#include "WarScenceLayer.h"
using namespace cocos2d;
static ScenceManger *s_sharedScenceManger = nullptr;

ScenceManger *ScenceManger::sharedScenceManger()
{
    if (s_sharedScenceManger == nullptr)
    {
        s_sharedScenceManger = new ScenceManger();
        if (!s_sharedScenceManger || !s_sharedScenceManger->init())
        {
            CC_SAFE_DELETE(s_sharedScenceManger);
        }
    }
    return s_sharedScenceManger;
}

void ScenceManger::destroyInstance()
{
    
    CC_SAFE_RELEASE_NULL(s_sharedScenceManger);
}

ScenceManger::ScenceManger(void)
{
  
}


ScenceManger::~ScenceManger(void)
{
   
}


bool ScenceManger::init()
{
    bool bRet = false;
    do
    {
        lastScenceNumber = -1;
        newScenceNumber = 0;
        lastScence = nullptr;
        s_loadScence = nullptr;
        m_loadFlog.clear();
        bRet = true;
    }
    while (0);
    
    return bRet;
}

//新场景加载资源,显示加载资源界面
void ScenceManger::loadResForScence()
{
    lastScence = Director::getInstance()->getRunningScene();
    Scene* sc = LoadingScence::createScene();
    Director::getInstance()->replaceScene(sc);
}
void ScenceManger::loadResEnd()//资源加载结束
{
    int nexts = nextSt.number;
    switch (nexts) {
        case kScenceLogin: //登陆
        {
            //在这里创建新游戏场景并转向新场景
            Scene* sc = Scene::create();
            std::vector<int> atmp;
            atmp.push_back(1);
            WarScenceLayer* layer = WarScenceLayer::createWarWithMapID(400001);
            sc->addChild(layer);
            Director::getInstance()->replaceScene(sc);
            
        }
            break;
        case kScenceMainCity: //主城
        {
            //在这里创建新游戏场景并转向新场景
            Scene* sc = Scene::create();
            std::vector<int> atmp;
            atmp.push_back(1);
            WarScenceLayer* layer = WarScenceLayer::createWarWithMapID(400001);
            sc->addChild(layer);
            Director::getInstance()->replaceScene(sc);
            
        }
            break;
        case kScenceWar: //关卡战斗
        {
            //在这里创建新游戏场景并转向新场景
            Scene* sc = Scene::create();
            std::vector<int> atmp;
            atmp.push_back(1);
            WarScenceLayer* layer = WarScenceLayer::createWarWithMapID(400001);
            sc->addChild(layer);
            Director::getInstance()->replaceScene(sc);
        }
            break;
        default:
            break;
    }
}
bool ScenceManger::getFlog(std::string str)
{
    return m_loadFlog[str];
}
void ScenceManger::setFlog(std::string str)
{
    m_loadFlog[str] = true;
}
//清除内存空间
void ScenceManger::cleanMemery(std::string plist)
{
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plist);
    m_loadFlog[plist] = false;
}

//不带参数，切换到编号场景
void ScenceManger::changeScenceTo(int scenceNumber)
{
    
}
//代有场景切换参数的场景切换
void ScenceManger::changeScenceTo(ScenceChangeDataST st)
{
    
}