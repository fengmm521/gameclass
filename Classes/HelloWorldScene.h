#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "BaseSprite.h"
#include "Box2d/Box2D.h"
#include "MyContactListener.h"
#include "GLES-Render.h"
using namespace cocostudio;
using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    Sprite* s_MapBG;
    
    Armature *armature;
    
    Armature *armature1001;
    
    Armature *armature1011;
    
    BaseSprite* sp1;
    BaseSprite* sp2;
    
    Sprite* boxsp1;
    Sprite* boxsp2;
    
    std::map<int,BaseSprite*> m_maptest;
    
    
    Armature *enemyTest;
    
    int playCount;
    
    std::map<int,std::string> playName;
    
public:
    //box2d 世界
    //box2D class
    b2World *_world;
    GLESDebugDraw *_deBugDraw;
    MyContactListener *_contactListener;
    
    void initBox2D();
    //为精灵添加形状
    void addBoxBodyForSprite(Sprite *sprite,string shapeName);
    
    virtual void update(float dt);
virtual void draw(Renderer *renderer, const Mat4 &transform,uint32_t flags);
    
    
private:
    //测试
  
    bool test;
    list<int16> aa;

};

#endif // __HELLOWORLD_SCENE_H__
