//
//  SocketTestLayer.cpp
//  game4
//
//  Created by Junpeng Zhang on 12/8/14.
//
//资源加载适合cocos2d-x 3.2版本的cocostudio for mac 1.0.0
//

#include "SocketTestLayer.h"
#include "ClientSocketManger.h"
#include "Cmds.pb.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d;
// on "init" you need to initialize your instance


SocketTestLayer* SocketTestLayer::create()
{
    SocketTestLayer* tmp = new SocketTestLayer();
    tmp->autorelease();
    tmp->init();
    return tmp;
}
bool SocketTestLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto startAstar = MenuItemFont::create("connect",CC_CALLBACK_1(SocketTestLayer::menuTouchCallback, this));
    startAstar->setTag(1);
    startAstar->setPosition(Vec2(200,500));
    
    
    auto startAstar1 = MenuItemFont::create("send",CC_CALLBACK_1(SocketTestLayer::menuTouchCallback, this));
    startAstar1->setTag(2);
    startAstar1->setPosition(Vec2(200,400));
    
    
    // create menu, it's an autorelease object
    auto menu = cocos2d::Menu::create(startAstar,startAstar1, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
}
//Layer界面中的按钮被点击时运行的方法
void SocketTestLayer::menuTouchCallback(Ref* pSender)
{
    MenuItem* tmpmitem= (MenuItem*)pSender;
    switch (tmpmitem->getTag()) {
        case 1://连接网络
        {
            
            
            ClientSocketManger::sharedClientSocketManger()->connectSocket();
//
//            x = 0;
//            
//            Director::getInstance()->getScheduler()->schedule([&](float dt)->void{
//                x++;
//                log("sssss%d",x);
//                
//                
//            }, this, 1.0f, false, "xxx");
        }
            break;
        case 2://发送测试数据
        {
            //Director::getInstance()->getScheduler()->unschedule("xxx", this);
            
            Cmd::EchoTest* echotest = new Cmd::EchoTest();
            echotest->set_a(123);
            echotest->set_b(1.2f);
            echotest->set_c(32);
            echotest->set_d(64);
            echotest->set_e("aabbcc");
            
            std::string strdata = echotest->SerializeAsString();
            
            int sizestr = (int)strdata.size();
            
            const char* data = strdata.data();
            
            std::string outstr = "";
            const char* pot = data;
            for (int i = 0; i < sizestr; i++) {
                pot+=i;
                char strout[10] = {0};
                unsigned char ch= *pot;
                sprintf(strout, "%02X ",ch);
                outstr += std::string(strout);
            }
            
            
            log("strdata size = %d",(int)strdata.size());
            log("str data hex=%s",outstr.c_str());
            
            std::string debugstr = echotest->Utf8DebugString();
            log("echotest=%s",debugstr.c_str());
            std::string sendmsg = echotest->SerializeAsString();
            ClientSocketManger::sharedClientSocketManger()->send(sendmsg, 10001, this);
            
        }
            break;
        default:
            break;
    }
    
    
}
void SocketTestLayer::reciveDataHandler(std::string &msg,int type,bool is_push)
{
    Cmd::EchoTest *echotest = new Cmd::EchoTest();
//    double a = echotest->a();
//    float b = echotest->b();
//    int32_t c = echotest->c();
//    int64_t d= echotest->d();
//    std::string e = echotest->e();
    echotest->ParseFromString(msg);
    std::string logecho = echotest->Utf8DebugString();
    log("get protobuf=%s",logecho.c_str());
    
}