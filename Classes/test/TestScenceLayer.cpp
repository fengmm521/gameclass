//
//  TestScenceLayer.cpp
//  game1
//
//  Created by 俊盟科技1 on 8/20/14.
//
//

#include "TestScenceLayer.h"
//#include "ClientSocketController.h"
// on "init" you need to initialize your instance
using namespace cocos2d;
bool TestScenceLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    do{
        
        Sprite* bg = Sprite::create("test/map1.jpg");
        bg->setAnchorPoint(Vec2(0,0));
        bg->setTag(-1);
        this->addChild(bg);
        
//        LayerColor* tmp = LayerColor::create(Color4B(255,255,255,255), 720, 1280);
//        tmp->setAnchorPoint(Vec2());
//        this->addChild(tmp);
        
        
        AtartManger = AStarMap6SideManger::sharedAStarMap6SideManger();
        
        AtartManger->initMapArrWithMapID(1);
        AStarPixelPoint tmppo = AtartManger->getPixePointFromTiledPoint(Vec2(1,1));
        log("pixel point (%f,%f) = %d",tmppo.po.x,tmppo.po.y,*(tmppo.value));
        
        
        
        int maxX = kTiledMapWidth;
        int maxY = kTiledMapHeight;
        for (int i = 0; i < maxX; i++) {
            for (int j = 0; j < maxY; j++) {
                AStarPixelPoint tmpx = AtartManger->getPixePointFromTiledPoint(Vec2(i,j));
                Sprite* tSp = Sprite::create("test/tiled_wightbig.png");
                tSp->setPosition(tmpx.po);
                if(j%2==0){
                    if (i%3 == 0) {
                        tSp->setColor(Color3B(255,0,0));
                        
                    }else if(i%3 == 1)
                    {
                        tSp->setColor(Color3B(0,255,0));
                    }else if(i%3 == 2)
                    {
                        tSp->setColor(Color3B(0,0,255));
                    }
                }else{
                    if (i%3 == 0) {
                        tSp->setColor(Color3B(255,0,255));
                        
                    }else if(i%3 == 1)
                    {
                        tSp->setColor(Color3B(255,0,0));
                    }else if(i%3 == 2)
                    {
                        tSp->setColor(Color3B(0,255,0));
                    }
                }
                
                tSp->setCascadeOpacityEnabled(true);
                tSp->setOpacity(20);
                
                tSp->setTag(i+j*kTiledMapWidth);
                this->addChild(tSp);
                log("(i,j) = (%d,%d), pixel point (%f,%f) = %d",i,j,tmpx.po.x,tmpx.po.y,*(tmpx.value));
            }
        }
        
        
        lastTiledPo = Vec2(-1,-1);
        startTiled = Vec2(-1,-1);
        isSetTiled = true;
        
    }while (0);
    
    //创建一个单点监听对像
    auto listener1 = EventListenerTouchOneByOne::create();
    
    // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    listener1->setSwallowTouches(true);
    
    // 使用 lambda 实现 onTouchBegan 事件回调函数
    listener1->onTouchBegan = [](Touch* touch, Event* event)
    {
        // 获取事件所绑定的 target
        auto target = static_cast<TestScenceLayer*>(event->getCurrentTarget());
        
        // 获取当前点击点所在相对按钮的位置坐标
        // touch-getLocation返回的是open GL的坐标系
        //Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Point touchPo = touch->getLocation();
        
        AStarTiledPoint tiled1 = target->AtartManger->getTiledPointFromPixelPoint(touchPo);
        
        
        
        log("touchpo=(%f,%f),tiledPo=(%d,%d)",touchPo.x,touchPo.y,tiled1.x,tiled1.y);
        
        AStar6SidePoint side6Po = target->AtartManger->conventTiledPointTo6SidePoint(tiled1);
        log("6side point = (%d,%d,%d)",side6Po.a,side6Po.b,side6Po.c);
        
        if (target->isSetTiled)
        {
            if (target->AtartManger->getMapPointValue(tiled1.x, tiled1.y) == 0)
            {
                target->AtartManger->setMapPoint(tiled1.x, tiled1.y);
                Sprite* xtm = (Sprite*)target->getChildByTag(tiled1.x+tiled1.y*kTiledMapWidth);
                    xtm->setOpacity(255);
            }else{
                target->AtartManger->cleanMapPoint(tiled1.x, tiled1.y);
                Sprite* xtm = (Sprite*)target->getChildByTag(tiled1.x+tiled1.y*kTiledMapWidth);
                    xtm->setOpacity(20);
            }
        }else{
            
            
            if (target->startTiled.x <0 || target->startTiled.y <0) {
                target->startTiled = Vec2(tiled1.x,tiled1.y);
                Sprite* xtm = (Sprite*)target->getChildByTag(tiled1.x+tiled1.y*kTiledMapWidth);
                xtm->setOpacity(255);
            }else if(target->startTiled.x == tiled1.x && target->startTiled.y == tiled1.y)
            {
                target->startTiled = Vec2(-1,-1);
                Sprite* xtm = (Sprite*)target->getChildByTag(tiled1.x+tiled1.y*kTiledMapWidth);
                xtm->setOpacity(20);
            }else{
                if (target->lastTiledPo.x >0 &&target->lastTiledPo.y >0) {
                    Sprite* lastm = (Sprite*)target->getChildByTag(target->lastTiledPo.x+target->lastTiledPo.y*kTiledMapWidth);
                    lastm->setOpacity(20);
                }
                
                Sprite* xtm = (Sprite*)target->getChildByTag(tiled1.x+tiled1.y*kTiledMapWidth);
                xtm->setOpacity(255);
                target->lastTiledPo = Vec2(tiled1.x,tiled1.y);
            }
            
            AStarPixelPoint tmpsp = AStarMap6SideManger::sharedAStarMap6SideManger()->getPixePointFromTiledPoint(target->startTiled);
            AStarPixelPoint tmpep = AStarMap6SideManger::sharedAStarMap6SideManger()->getPixePointFromTiledPoint(target->lastTiledPo);
            
            Point startPo = tmpsp.po;
            Point endPo = tmpep.po;
            endPo.subtract(startPo);
            float jiaodu = endPo.getAngle();
            log("jiaodu from end to start = %f",jiaodu);
            
        }
        
        
        return false;
    };
    
    // 触摸移动时触发
    listener1->onTouchMoved = [](Touch* touch, Event* event)
    {
       // auto target = static_cast<TestScenceLayer*>(event->getCurrentTarget());
        
        // 移动当前按钮精灵的坐标位置
        // touch-getDelta()返回当前坐标物体最初坐标的差值，这样能保证物体实时在移动，动作很连贯
       // target->setPosition(target->getPosition() + touch->getDelta());
    };
    
    // 点击事件结束处理
    listener1->onTouchEnded = [=](Touch* touch, Event* event)
    {
        //auto target = static_cast<TestScenceLayer*>(event->getCurrentTarget());
        //log("sprite onTouchesEnded.. ");
        //设置透明度为255
        
        
        // 重新设置 ZOrder，显示的前后顺序将会改变
        // 是的，你没有看错，sprite2出现了，我一直以为lambda表达式只是匿名函数名
        // 原来在同一个函数内外面的变量在lambda表达式中还有效。

    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(TestScenceLayer::menuTouchCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    closeItem->setTag(1);
    
    
    auto startAstar = MenuItemFont::create("Astar",CC_CALLBACK_1(TestScenceLayer::menuTouchCallback, this));
    startAstar->setTag(2);
    startAstar->setPosition(Vec2(100,100));
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,startAstar, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    return true;
}

//Layer界面中的按钮被点击时运行的方法
void TestScenceLayer::menuTouchCallback(Ref* pSender)
{
   
    auto menu = dynamic_cast<MenuItem*>(pSender);
    switch (menu->getTag()) {
        case 1:
        {
               // isSetTiled = !isSetTiled;
            //ClientSocketController::sharedClientSocketController()->serverconnect();
        }
            break;
        case 2:
        {
//            string name = "name";
//            string password = "password";
//            string email = "email@email.com";
            //ClientSocketController::sharedClientSocketController()->serverTest(name, password,email,this);
            
//          std::list<AStarTiledPoint> listroad =  AtartManger->findRoadWithTiledPoint(startTiled, lastTiledPo);
//            log("touch start astar node count = %d",(int)listroad.size());
//            this->showRoad(listroad);
            
            
            
            
        }
            break;
        default:
            break;
    }

}

void TestScenceLayer::showRoad(std::list<AStarTiledPoint> &listtiled)
{
     listtil = listtiled;
    this->showRoad();
}

void TestScenceLayer::showRoad()
{
    if (!listtil.empty()) {
        t0 = listtil.front();
        listtil.pop_front();
        Director::getInstance()->getScheduler()->schedule(schedule_selector(TestScenceLayer::showRoadOne), this, 0.3f, false);
    }else{
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(TestScenceLayer::showRoadOne), this);
    }
}

void TestScenceLayer::showRoadOne(float dt)
{
    Sprite* tx = (Sprite*)this->getChildByTag(t0.x+t0.y*kTiledMapWidth);
    tx->setOpacity(80);
    this->showRoad();
}

void TestScenceLayer::onSocketCallBack(std::string data)
{
    log("get string is:%s",data.c_str());
    //__String* tmp = CCString::createWithFormat("get string from server:%s",data.c_str());
}
