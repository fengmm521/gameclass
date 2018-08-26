//
//  LoginLayer.h
//  game4
//
//  Created by Junpeng Zhang on 12/26/14.
//
//
//资源加载适合cocos2d-x 3.2版本的cocostudio for mac 1.0.0
//

#ifndef __game4__LoginLayer__
#define __game4__LoginLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "SocketDelegate.h"

USING_NS_CC;

class LoginLayer : public cocos2d::Layer,SocketReciveDelegate
{
public:
    virtual bool init();
    
    ui::Button* m_btn;
    
    // a selector callback
    void menuTouchCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(LoginLayer);
    void  buttonHeroEvent(Ref *pSender, ui::Widget::TouchEventType type);
    virtual void reciveDataHandler(std::string &msg,int type,bool is_push = false);
    //网络状态改变回调
    void ClientNetStateChangeCallBack(std::string changetype,cocos2d::Ref* obj);
    
    //延时连接网络
    void connectNetDelay(float dt);
    void gotoMainCityScence();
};

#endif /* defined(__game4__LoginLayer__) */
