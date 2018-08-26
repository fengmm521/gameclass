//
//  Box2dWordManger.h
//  game1
//  C++单例类模板，非线程安全单例类，并且实例化后会常注内存
//
//  Created by 俊盟科技1 on 8/30/14.
//
//

#ifndef __game1__Box2dWordManger__
#define __game1__Box2dWordManger__

#include "cocos2d.h"
#include "external/Box2d/Box2D.h"
#include "MyContactListener.h"
#include "GLES-Render.h"
#include "SkillBullet.h"
class BaseSprite;
class Box2dSprite;
using namespace cocos2d;
using namespace std;

class Box2dWordManger:public cocos2d::Node
{
public:
    static Box2dWordManger* sharedBox2dWordManger();
    static void destroyInstance();
private:
	/**
     * @js ctor
     */
    Box2dWordManger(void);
    /**
     * @js NA
     * @lua NA
     */
    ~Box2dWordManger(void);
    
//private:
public:
    //box2d 世界
    //box2D class
    b2World *_world;
    GLESDebugDraw *_deBugDraw;
    MyContactListener *_contactListener;
    
    map<Sprite*,int16> s_fixtureMap;

    //得到唯一一个int16形的编号
    int s_maxInt16;             //创建过的最大编号数这个数不能大于2的16次方
    list<int16> s_delInt16;     //使用过的已删除的int16编号
    int16 getOnlyInt16();       //为新形状获取一个新的int16编号
    void deleInt16(int16 tag);
    
public:
    
    /**
     * Init Box2dWordManger
     */
    virtual bool init();
    
    //使用地图坐标点绘制地图可移动范围,地图的碰撞编号设置为1
    void initMapBoxWorldEdgeShape(list<Point> MapPointList);
    //绘制地图内部不可通过点
    void initInMapCollision(list<list<Point>> inMapPointList);
    //根据精灵的攻击范围初始化精灵的攻击碰撞体和地图不可移动点碰撞体
    //不可移动点根据精灵体积确定，碰撞编号与地图相同为1,
    //攻击碰撞体根据精灵攻击范围确定,编号为精灵对象指针数制
    //所有碰撞体的maskBits都为0;
    b2Fixture* addBodyForInitSpiite(BaseSprite* initSp,int attackRange);
    
    b2Fixture* changeBodyForInitSpiite(BaseSprite* initSp,int attackNewRange);
    
    
    void addBodyForInitButtle(SkillBullet* initSp,int buttleRiad);
    
    //为b2body增加新的攻击者精灵碰撞体
    b2Fixture* addSpriteToWorldWithCollision(BaseSprite* sp,Box2dSprite* attacksSp);
    
//    //精灵死亡时，删除精灵身上攻击碰撞体
    void delBodyFixture(b2Body* b2body,int tag);
    
    virtual void box2duUdate(float dt);
    
//    void startBox2dWorld();//战斗开始时开启物理引擎
//    void stopBox2dWorld();//战斗结束时关闭物理引擎以省电

};

#endif /* defined(__game1__Box2dWordManger__) */
