//
//  TestScenceLayer.h
//  game1
//
//  Created by 俊盟科技1 on 8/20/14.
//
//

#ifndef __game1__TestScenceLayer__
#define __game1__TestScenceLayer__
#include "cocos2d.h"
#include "AStarMap6SideManger.h"
//#include "NetConfig.h"

using namespace cocos2d;
typedef struct AstarTiledPointST AStarTiledPoint;
class TestScenceLayer : public cocos2d::Layer//,public UserSocketCallBack
{
public:
    AStarMap6SideManger* AtartManger;
    
    virtual bool init();
    // a selector callback
    void menuTouchCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(TestScenceLayer);
    
    bool isSetTiled;
    
    bool isSetStartTiledPo;
    Point lastTiledPo;
    
    Point startTiled;
    
    void showRoad(std::list<AStarTiledPoint> &listtiled);
    
    void showRoad();
    
    std::list<AStarTiledPoint> listtil;
    
    AStarTiledPoint t0;
    void showRoadOne(float dt);
    
    virtual void onSocketCallBack(std::string data);
    
};
#endif /* defined(__game1__TestScenceLayer__) */
