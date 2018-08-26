#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameViewConfig.h"
#include "WarScenceLayer.h"
#include "MainCityScence.h"
#include "GameTest.h"
#include "TestScenceLayer.h"
#include "ClientSocketManger.h"
#include "LocalDataManger.h"
#include "SocketTestLayer.h"
#include "LoginLayer.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS || CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
#include "AndriodLogLayer.h"
#endif
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    
    //网络管理类初始化
    ClientSocketManger::sharedClientSocketManger();
    LocalDataManger::sharedLocalDataManger();
    
    log("app run 1 1...");
    
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
        
    }

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/Click_Button.wav");
    Size si = Director::getInstance()->getWinSize();
    float xtmp = ((float)si.height/(float)si.width);
    if (xtmp < 1.6f) {
        glview->setDesignResolutionSize(kWidthWindow, kHeightWindow, ResolutionPolicy::SHOW_ALL);
    }else{
        glview->setDesignResolutionSize(kWidthWindow, kHeightWindow, ResolutionPolicy::EXACT_FIT);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);

    
    log("app run...");
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
#if 0
    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
    auto scene = Scene::create();
    SocketTestLayer* testSc = SocketTestLayer::create();
    scene->addChild(testSc);
    
#else
    auto scene = Scene::create();
    
//    vector<int> atmp;
//    atmp.push_back(1);
//    WarScenceLayer* layer = WarScenceLayer::createWarWithMapID(1, atmp);
//#define CC_PLATFORM_UNKNOWN            0
//#define CC_PLATFORM_IOS                1
//#define CC_PLATFORM_ANDROID            2
//#define CC_PLATFORM_WIN32              3
//#define CC_PLATFORM_MARMALADE          4
//#define CC_PLATFORM_LINUX              5
//#define CC_PLATFORM_BADA               6
//#define CC_PLATFORM_BLACKBERRY         7
//#define CC_PLATFORM_MAC                8
//#define CC_PLATFORM_NACL               9
//#define CC_PLATFORM_EMSCRIPTEN        10
//#define CC_PLATFORM_TIZEN             11
//#define CC_PLATFORM_QT5               12
//#define CC_PLATFORM_WP8               13
//#define CC_PLATFORM_WINRT             14
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
//    MainCityScence* layer = MainCityScence::create();
//    scene->addChild(layer);
    LoginLayer* loginlayer = LoginLayer::create();
    scene->addChild(loginlayer);
#else
    AndriodLogLayer* layer = AndriodLogLayer::creat();
    scene->addChild(layer);
#endif

#endif
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
