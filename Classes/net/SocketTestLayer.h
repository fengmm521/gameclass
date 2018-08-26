//
//  SocketTestLayer.h
//  game4
//
//  Created by Junpeng Zhang on 12/8/14.
//
//
//资源加载适合cocos2d-x 3.2版本的cocostudio for mac 1.0.0
//

#ifndef __game4__SocketTestLayer__
#define __game4__SocketTestLayer__

#include "cocos2d.h"
#include "SocketDelegate.h"
USING_NS_CC;
class Message;
class SocketTestLayer : public cocos2d::Layer,SocketReciveDelegate
{
public:
    
    ~SocketTestLayer(void){};
    
    static SocketTestLayer* create();
    
    virtual bool init();
    // a selector callback
    void menuTouchCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    virtual void reciveDataHandler(std::string &msg,int type,bool is_push = false);
    
};
#endif /* defined(__game4__SocketTestLayer__) */
