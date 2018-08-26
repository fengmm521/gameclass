//
//  LoginLayer.cpp
//  game4
//
//  Created by Junpeng Zhang on 12/26/14.
//
//资源加载适合cocos2d-x 3.2版本的cocostudio for mac 1.0.0
//

#include "LoginLayer.h"
#include "MainCityScence.h"
#include "ClientSocketManger.h"
#include "netConfig.h"
#include "CallBackVo.h"
#include "ObserverManger.h"
#include "GameViewConfig.h"
USING_NS_CC;

#define kIsUsedNet 0

using namespace std;
// on "init" you need to initialize your instance
bool LoginLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Sprite* bg = Sprite::create("lodingLog.jpg");
    Size si = Director::getInstance()->getWinSize();
    bg->setPosition(si.width/2,si.height/2);
    this->addChild(bg,0);
    
    
    ObserverManger::shareObserverManger()->registerCallBackEvent(kNetState, this, event_callbackStr(LoginLayer::ClientNetStateChangeCallBack));
    
    m_btn = ui::Button::create("gameStart.png");
    //m_backBtn->addTouchEventListener(CC_CALLBACK_2(WarScenceLayer::buttonHeroEvent, this));
    m_btn->addTouchEventListener(CC_CALLBACK_2(LoginLayer::buttonHeroEvent, this));
    m_btn->setPosition(Vec2(si.width/2,si.height/10.5f));
#if kIsUsedNet
    m_btn->setEnabled(false);
    m_btn->setVisible(false);
#endif
    this->addChild(m_btn,1);
    
#if kIsUsedNet
    Director::getInstance()->getScheduler()->schedule(schedule_selector(LoginLayer::connectNetDelay), this, 0.01f, false);
#endif
    
    return true;
}
void LoginLayer::connectNetDelay(float dt)
{
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(LoginLayer::connectNetDelay), this);
    ClientSocketManger::sharedClientSocketManger()->connectSocket();
}

void  LoginLayer::buttonHeroEvent(Ref *pSender, ui::Widget::TouchEventType   type)
{
    //ui::Button* buttontmp = dynamic_cast<ui::Button*>(pSender);
    
    switch (type)
    {
        case  ui::Widget::TouchEventType::BEGAN:
            //MessageBox("fgfggf", "dsdsss");
            break;
        case  ui::Widget::TouchEventType::MOVED:
            //MessageBox("fgfggf", "dsdsss");
            break;
            
        case  ui::Widget::TouchEventType::ENDED:
        {
            //界面按钮被点击的音效
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Click_Button.wav");
#if kIsUsedNet
//            // 第一步伪装登陆
//            message Login_Request {
//                optional bytes formid  = 1;		// 平台ID
//                optional bytes fromuid = 2;		// 平台用户ID
//                optional bytes session = 3; 	// 平台登陆会话
//                optional bytes token   = 4; 	// 服务器加密项
//                optional bytes version = 5; 	// 客户端游戏版本
//                optional bytes device  = 6; 	// 终端设备型号
//                optional bytes system  = 7; 	// 终端系统版本
//                optional bytes uniqueness = 8; 	// 终端设备号
//            }

            Cmd::Login_Request* logintmp = new Cmd::Login_Request();
            logintmp->set_formid(kFormid);
            //logintmp->set_fromuid(kFromuid); //平台用户ID,在没有平台时不赋值
            logintmp->set_session(kSession);
            logintmp->set_token(kToken);
            logintmp->set_version(kVersionClient);
            logintmp->set_device(kDeviceNumber);
            logintmp->set_system(kSystemVersion);
            logintmp->set_uniqueness(kUniqueness);
            std::string sendmsg = logintmp->SerializeAsString();
            ClientSocketManger::sharedClientSocketManger()->send(sendmsg, client_protocol::CP_LOGIN_SERVER, this);
#else
            auto scene = Scene::create();
            MainCityScence* layer = MainCityScence::create();
            scene->addChild(layer);
            Director::getInstance()->replaceScene(scene);
#endif
            break;
        }
            
        case  ui::Widget::TouchEventType::CANCELED:
            
            break;
            
        default:
            break;
    }
    
}
//Layer界面中的按钮被点击时运行的方法
void LoginLayer::menuTouchCallback(Ref* pSender)
{
   
    
    
}
//网络状态改变回调
void LoginLayer::ClientNetStateChangeCallBack(std::string changetype,cocos2d::Ref* obj)
{
    //    enum EventType{
    //        REQUEST = 1,
    //        RESPONSE = 2,
    //        CONNECT_SUCCEED = 11,
    //        CONNECT_FAIL = 12,
    //        DISCONNECT = 13
    //    };
    
    __String* strstate = dynamic_cast<__String*>(obj);
    int state = strstate->intValue();
    switch (state) {
        case EventType::CONNECT_SUCCEED:
        {
            m_btn->setEnabled(true);
            m_btn->setVisible(true);
        }
            break;
        case EventType::CONNECT_FAIL:
        {
            m_btn->setEnabled(false);
            m_btn->setVisible(false);
        }
            break;
        case EventType::DISCONNECT:
        {
            m_btn->setEnabled(false);
            m_btn->setVisible(false);
        }
            break;
        default:
            break;
    }
}
void LoginLayer::reciveDataHandler(std::string &msg,int type,bool is_push)
{
    //服务器返回
    //    // 第一步伪装登陆
    //    message Login_Response {
    //        optional bytes uid  = 1;		// 用户ID
    //        optional bytes fromuid = 2;		// 平台用户ID
    //    }
    if (is_push) {
        
    }else{
        
        
        
        switch (type) {
            case client_protocol::CP_LOGIN_SERVER:// 登陆// Request: Login_Request, Response: Login_Response
            {
                Cmd::Login_Response *resserver = new Cmd::Login_Response();
                resserver->ParseFromString(msg);
                std::string tmptest = resserver->Utf8DebugString();
                log("get server msg = %s",tmptest.c_str());
                ClientSocketManger::sharedClientSocketManger()->send("", client_protocol::CP_LOAD_ROLE, this);
            }
                break;
            case client_protocol::CP_LOAD_ROLE:// 获取主角 // Request: NULL, Response: Role
            {
                if (msg.empty()) {
                    log("no user.");
                    Cmd::CreateRole_Request * sendprto = new Cmd::CreateRole_Request();
                    sendprto->set_figure(1);
                    sendprto->set_name("testuser1");
                    std::string sendmsg = sendprto->SerializeAsString();
                    ClientSocketManger::sharedClientSocketManger()->send(sendmsg, client_protocol::CP_CREATE_ROLE, this);
                }else{//服务器有玩家
                    Cmd::Role *resserver = new Cmd::Role();
                    resserver->ParseFromString(msg);
                    std::string tmptest = resserver->Utf8DebugString();
                    log("heave user = %s",tmptest.c_str());
                    
                    this->gotoMainCityScence();
                }
                //客户端发送
                //    message CreateRole_Request {
                //        optional sint32 figure = 1;		// 形像
                //        optional bytes  name   = 2;		// 角色名
                //    }
            }
                break;
            case client_protocol::CP_CREATE_ROLE:// 创建主角// Request: CreateRole_Request, Response: Role
            {
                //服务器端返回
                //    message Role {
                //        optional sint32 figure 	= 1;	// 形象
                //        optional sint32 viplv 	= 2;	// VIP 等级
                //        optional sint32 viptub 	= 3; 	// VIP 经验
                //        optional sint32 mclv  	= 4;    // 主角等级
                //        optional sint32 mctub 	= 5;    // 主角经验
                //        optional sint32 newbies = 6;	// 新手
                //        optional bytes name 	= 7;	// 主角色名称
                //    }
                Cmd::Role *resserver = new Cmd::Role();
                resserver->ParseFromString(msg);
                std::string tmptest = resserver->Utf8DebugString();
                log("get server msg = %s",tmptest.c_str());
                
                this->gotoMainCityScence();
                
                
            }
                break;
            default:
                break;
        }

    }
}
void LoginLayer::gotoMainCityScence()
{
    auto scene = Scene::create();
    MainCityScence* layer = MainCityScence::create();
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
}
