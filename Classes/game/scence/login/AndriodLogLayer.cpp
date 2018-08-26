//
//  AndriodLogLayer.cpp
//  game4
//
//  Created by Junpeng Zhang on 12/26/14.
//
//资源加载适合cocos2d-x 3.2版本的cocostudio for mac 1.0.0
//

#include "AndriodLogLayer.h"
#include "LoginLayer.h"
USING_NS_CC;
using namespace std;
// on "init" you need to initialize your instance
bool AndriodLogLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Sprite* logbg = Sprite::create("gamelog.png");
    Size si = Director::getInstance()->getWinSize();
    logbg->setPosition(si.width/2,si.height/2);
    this->addChild(logbg,0);
    
    Director::getInstance()->getScheduler()->schedule(schedule_selector(AndriodLogLayer::logLayerEnd), this, 0.5f, false);
    
    return true;
}
//Layer界面中的按钮被点击时运行的方法
void AndriodLogLayer::menuTouchCallback(Ref* pSender)
{
   
    
    
}
void AndriodLogLayer::logLayerEnd(float dt)
{
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(AndriodLogLayer::logLayerEnd), this);
    
    Scene* loginScence = Scene::create();
    LoginLayer* loginlayer = LoginLayer::create();
    loginScence->addChild(loginlayer);
    Director::getInstance()->replaceScene(loginScence);
    
}