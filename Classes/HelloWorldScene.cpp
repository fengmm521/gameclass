#include "HelloWorldScene.h"
#include "WarScenceLayer.h"
#include "GameViewConfig.h"
#include "Box2dConfig.h"
#include "Box2dWordManger.h"
using namespace cocostudio;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
//    s_MapBG = Sprite::create("map1.jpg");
//    s_MapBG->setPosition(Vec2(kWidthWindow/2.0f,kHeightWindow/2.0f));
//    this->addChild(s_MapBG);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

//    std::vector<int> tmpvector;
//    tmpvector.push_back(1);
//    WarScenceLayer* tmpWar = WarScenceLayer::createWarWithMapID(1, tmpvector);
//    
//    this->addChild(tmpWar);
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    closeItem->setTag(1);
    auto closeItem1 = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    closeItem1->setTag(2);
	closeItem1->setPosition(Vec2(origin.x + visibleSize.width/2 - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,closeItem1, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    test =false;
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
//    
    playName[0] = "Stand";
    playName[1] = "Run";
    playName[2] = "Die";
    playName[3] = "Attack";
    playName[4] = "Character";
    playName[5] = "Hited";
    playName[6] = "Magic01";
    playName[7] = "Hited02";
    
    playCount = 0;
    
//    ArmatureDataManager::getInstance()->addArmatureFileInfo("10020.png","10020.plist","1002.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("sprite/1506/15060.png","sprite/1506/15060.plist","sprite/1506/1506.ExportJson");
//    ArmatureDataManager::getInstance()->addArmatureFileInfo("10110.png","10110.plist","1011.ExportJson");
    
//    armature = Armature::create( "1002");
//    armature->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
   
//    armature->getAnimation()->play(playName[playCount]);
//    this->addChild(armature);
    
    armature1001 = Armature::create("1506");
    armature1001->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
    armature1001->getAnimation()->play(playName[playCount]);
    this->addChild(armature1001);
    
    //敌人
//    armature1011 = Armature::create("1011");
//    armature1011->getAnimation()->play(playName[playCount]);
    sp1 = BaseSprite::createWithID(1011,NULL,false,1,1,1,1,1,1,1);
   // sp1->addChild(armature1011);
    sp1->setTag(10);
    sp1->setAnchorPoint(Vec2(0.0f,0.3f));
    sp1->setFlippedX(true);
    sp1->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.7));
    this->addChild(sp1);
    
//    enemyTest = Armature::create("1002");
//    enemyTest->getAnimation()->play(playName[playCount]);
    sp2 = BaseSprite::createWithID(1002,NULL,false,1,1,1,1,1,1,1);
   // sp2->addChild(enemyTest);
    sp2->setTag(20);
    sp2->setAnchorPoint(Vec2(0.0f,0.3f));
    sp2->setFlippedX(true);
    sp2->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.7));
    this->addChild(sp2);

    boxsp1 = Sprite::create();
    boxsp1->setTag(30);
    boxsp1->setAnchorPoint(Vec2(0.0f,0.3f));
    boxsp1->setPosition(Vec2(300,500));
    this->addChild(boxsp1);
    

    this->initBox2D();
    
    
    boxsp2 = Sprite::create();
    boxsp2->setPosition(Vec2(300,400));
    boxsp2->setAnchorPoint(Vec2(0.0f,0.3f));
    boxsp2->setTag(40);
    this->addChild(boxsp2);
    
    this->addBoxBodyForSprite(sp1, "sp1");
    this->addBoxBodyForSprite(sp2, "sp2");
    
    this->addBoxBodyForSprite(boxsp1, "boxsp1");
    this->addBoxBodyForSprite(boxsp2, "boxsp2");
    
    m_maptest[0] = sp1;
    m_maptest[1] = sp2;
    
    
    
    scheduleUpdate();
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    playCount++;
    if (playCount > 6) {
        playCount = 0;
    }
    
    if (playCount == 4) {
        armature1001->getAnimation()->play(playName[playCount]);
        //armature->getAnimation()->play(playName[playCount]);
    }else{
        //armature1011->getAnimation()->play(playName[playCount]);
        armature1001->getAnimation()->play(playName[playCount]);
        //armature->getAnimation()->play(playName[playCount]);
        
    }
    if (playCount%2 == 0) {
        //this->reorderChild(armature, 10);
        this->reorderChild(armature1001, 9);
        
        m_maptest[0]->setZOrder(100);
        m_maptest[1]->setZOrder(10);
//        this->reorderChild(sp1, 100);
//        this->reorderChild(Sp2, 10);
    }else{
        //this->reorderChild(armature, 9);
        this->reorderChild(armature1001, 10);
        
        m_maptest[0]->setZOrder(10);
        m_maptest[1]->setZOrder(100);
//        this->reorderChild(sp1, 10);
//        this->reorderChild(sp2, 100);
    }
    
    if (playCount%4 == 0) {
        sp1->s_b2body->SetLinearVelocity(b2Vec2(3.0f,0.0f));
    }else if(playCount%4 == 1)
    {
        sp1->s_b2body->SetLinearVelocity(b2Vec2(0.0f,-3.0f));
    }else if(playCount%4 == 2)
    {
        sp1->s_b2body->SetLinearVelocity(b2Vec2(-3.0f,0.0f));
    }else if(playCount%4 ==3)
    {
        sp1->s_b2body->SetLinearVelocity(b2Vec2(0.0f,3.0f));
    }
    
    MenuItem* itemtmp = dynamic_cast<MenuItem*>(pSender);
    if(itemtmp->getTag() == 2)
    {
        test = !test;
    }else{
        if (!test) {
            int16 tmp = Box2dWordManger::sharedBox2dWordManger()->getOnlyInt16();
            log("get new int16 is:%d,maxcount is=%d",tmp,Box2dWordManger::sharedBox2dWordManger()->s_maxInt16);
            std::list<int16> deltmp = Box2dWordManger::sharedBox2dWordManger()->s_delInt16;
            log("deltmp list size=%d",(int)deltmp.size());
            int tmpl = 0;
            for (std::list<int16>::iterator it = deltmp.begin(); it != deltmp.end(); it++) {
                tmpl++;
                log("del %d is:%d",tmpl,(*it));
            }
            aa.push_back(tmp);
        }else{
            if(!aa.empty()){
                int xtmp = aa.front();
                aa.pop_front();
                Box2dWordManger::sharedBox2dWordManger()->deleInt16(xtmp);
                std::list<int16> deltmp = Box2dWordManger::sharedBox2dWordManger()->s_delInt16;
                log("del (%d) maxcount is=%d",xtmp,Box2dWordManger::sharedBox2dWordManger()->s_maxInt16);
                log("deltmp list size=%d",(int)deltmp.size());
                int tmpl = 0;
                for (std::list<int16>::iterator it = deltmp.begin(); it != deltmp.end(); it++) {
                    tmpl++;
                    log("del %d is:%d",tmpl,(*it));
                }
            }
            
        }
    }
    
    
    
//    Point po1 = Vec2(100,100);
//    Point po2 = Vec2(300,300);
//    Point pox ;
//    cocos2d::Vec2::subtract(po1,po2,&pox);
//    log("anlg is:%f",pox.getAngle()*360/(2*3.14159));
    
    
//得到6个位置的精灵位
    Point oPo = Vec2(1,0);
    Point tmpx = oPo.rotateByAngle(Vec2(0,0), 2*3.1415926*30/360);
    tmpx.scale(50);
    log("tmpx poing is:(%f,%f)",tmpx.x,tmpx.y);
/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
*/
}
void HelloWorld::initBox2D()
{
    b2Vec2 gravity = b2Vec2(0.0f,0.0f);
    //bool doSleep = false;
    _world = new b2World(gravity);
    _world->SetAllowSleeping(false);
    //b2AABB
    _world->SetAllowSleeping(true);
    _deBugDraw = new GLESDebugDraw(PTM_RATIO);
    //b2World.SetDebugDraw(_deBugDraw);
    
    _world->SetDebugDraw(_deBugDraw);
    _world->SetContinuousPhysics(true);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    _deBugDraw->SetFlags(flags);
    
    _contactListener = new MyContactListener();
    _world->SetContactListener(_contactListener);
    
    b2BodyDef groundbodydef;
    groundbodydef.position.Set(0,0);
    
    b2Body* groundbody = _world->CreateBody(&groundbodydef);
    
    b2EdgeShape groundbox;
    
    groundbox.Set(b2Vec2(0,0), b2Vec2(2*kWidthWindow/PTM_RATIO,0));
    groundbody->CreateFixture(&groundbox, 0);
    
    groundbox.Set(b2Vec2(0,0), b2Vec2(0,2*kHeightWindow/PTM_RATIO));
    groundbody->CreateFixture(&groundbox,0);
    
    groundbox.Set(b2Vec2(0,2*kHeightWindow/PTM_RATIO), b2Vec2(2*kWidthWindow/PTM_RATIO,2*kHeightWindow/PTM_RATIO));
    groundbody->CreateFixture(&groundbox,0);
    
    groundbox.Set(b2Vec2(2*kWidthWindow/PTM_RATIO,0), b2Vec2(2*kWidthWindow/PTM_RATIO,2*kHeightWindow/PTM_RATIO));
    groundbody->CreateFixture(&groundbox,0);
    
    
    b2Vec2 po = groundbody->GetPosition();
    
    log("groundbody position is (%f,%f)",po.x,po.y);
    
    
}

void HelloWorld::addBoxBodyForSprite(Sprite *sprite,string shapeName)
{
    
    
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    //bodyDef.linearDamping = 0.0f;
    //bodyDef.angularDamping = 0.0f;
    bodyDef.position.Set(sprite->getPosition().x/PTM_RATIO, sprite->getPosition().y/PTM_RATIO);
    bodyDef.userData = sprite;
    b2Body *body = _world->CreateBody(&bodyDef);
    
    
    // Define another box shape for our dynamic body.

    if (sprite->getTag() == 10) {
        //body->ApplyForceToCenter(b2Vec2(0.0f,-50.0f), true);
        //body->ApplyLinearImpulse(b2Vec2(0.0f,-5.0f), body->GetLocalCenter(), false);
        BaseSprite* bsp = dynamic_cast<BaseSprite*>(sprite);
        bsp->s_b2body = body;
 
        body->SetLinearVelocity(b2Vec2(0.0f,-2.0f));
        //body->ApplyForceToCenter(b2Vec2(0.0f,-30.0f), false);
    }
    
    b2CircleShape circleShape;
    
    circleShape.m_radius = 2.0f;
    
    
    
    
//    b2PolygonShape dynamicBox;
//    dynamicBox.SetAsBox(0.5f, 0.5f);//These are mid points for our 1m box
//    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    switch (sprite->getTag()) {
        case 10:
            fixtureDef.filter.groupIndex = -1;
            fixtureDef.filter.maskBits = 0x00001; //当两个组groupIndex不相同时，两个物体的mask按位与并类别categoryBits按位与都不为0时可碰撞
            fixtureDef.filter.categoryBits = 0x00001;
            fixtureDef.isSensor = true;
            break;
        case 20:
            fixtureDef.filter.groupIndex = -1;
            fixtureDef.isSensor = true;
            break;
        case 30:
            fixtureDef.filter.groupIndex = -2;
            fixtureDef.isSensor = true;
            break;
        case 40:
            fixtureDef.filter.groupIndex = -2;
            fixtureDef.isSensor = true;
            break;
        default:
            break;
    }
    
    
    //fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    body->GetFixtureList();
    //body->SetSleepingAllowed(false);

}


void HelloWorld::update(float dt)
{
   
    //box2d-------------------
    {
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        
        // Instruct the world to perform a single step of simulation. It is
        // generally best to keep the time step and iterations fixed.
        _world->Step(dt, velocityIterations, positionIterations);
        
    
        //Iterate over the bodies in the physics world
        // _world->Step(dt, 10, 10);
        
        // Loop through all of the Box2D bodies in our Box2D world..
        for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) {
            
            // See if there's any user data attached to the Box2D body
            // There should be, since we set it in addBoxBodyForSprite
            if (b->GetUserData() != NULL) {
                
                // We know that the user data is a sprite since we set
                // it that way, so cast it...
                Sprite *sprite = (Sprite *)b->GetUserData();
                
                
                
                Point snakePoint;
                
               
                snakePoint = Vec2(b->GetPosition().x*PTM_RATIO,b->GetPosition().y*PTM_RATIO);
                
                // Convert the Cocos2D position/rotation of the sprite to the Box2D position/rotation
                //b2Vec2 b2Position = b2Vec2(snakePoint.x/PTM_RATIO,snakePoint.y/PTM_RATIO);
                //float32 b2Angle = -1 * CC_DEGREES_TO_RADIANS(sprite->getRotation());
                
                // Update the Box2D position/rotation to match the Cocos2D position/rotation
                //b->SetTransform(b2Position, b2Angle);
                
                //   CCLOG(@"sprite tag is %i x,y is (%f,%f)",sprite.tag,snakePoint.x,snakePoint.y);
                
                sprite->setPosition(snakePoint);
            }
        }
        //----------------------
    }
    
    //碰撞检测
    
    std::vector<b2Body *>toDestroy;
    std::vector<MyContact>::iterator pos;
    for(pos = _contactListener->_contacts.begin(); pos != _contactListener->_contacts.end(); ++pos) {
        MyContact contact = *pos;
        
        // Get the box2d bodies for each object

        b2Body *bodyA = contact.fixtureA->GetBody();
        b2Body *bodyB = contact.fixtureB->GetBody();
        if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
            Sprite *spriteA = (Sprite *) bodyA->GetUserData();
            Sprite *spriteB = (Sprite *) bodyB->GetUserData();
            
            //CCLOG(@"actick ones....");
            
            // Is sprite A a cat and sprite B a car?  If so, push the cat on a list to be destroyed...
            if (spriteA->getTag() == 10 && spriteB->getTag() == 20) {
                //toDestroy.push_back(bodyA);
                
                bodyA->SetLinearVelocity(b2Vec2(0,0));
                //enum_Tick_ = e_snakeEatChick;
                log("10 touch 20");
                break;
            }else if (spriteA->getTag() == 20 && spriteB->getTag() == 10) { // Is sprite A a car and sprite B a cat?  If so, push the cat on a list to be destroyed...
                //toDestroy.push_back(bodyB);
                log("20 touch 10");
                break;
            }else if (spriteA->getTag() == 10 && (spriteB->getTag() == 30)){
//                enum_Tick_ = e_snakeKickRock;
//                toDestroy.push_back(bodyA);
                log("10 touch 30");
                break;
            }else if(spriteA->getTag()  == 30 && (spriteB->getTag() == 10)){
//                enum_Tick_ = e_snakeKickRock;
//                toDestroy.push_back(bodyB);
                log("30 touch 10");
                break;
            }else if (spriteA->getTag() == 10 && (spriteB->getTag() == 40)){
//                enum_Tick_ = e_snakeKickTree;
//                toDestroy.push_back(bodyA);
                log("10 touch 40");
                break;
            }else if(spriteA->getTag() == 40 && (spriteB->getTag() == 10)){
//                enum_Tick_ = e_snakeKickTree;
//                toDestroy.push_back(bodyB);
                CCLOG("40 touch 10");
                break;
            }
        }
    }
    

}
void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
//
//    cocos2d::Layer::draw(renderer, transform, flags);
//    
//    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
//    
//    kmGLPushMatrix();
//    
//    _world->DrawDebugData();//这个是一定要写的 其他几句不知道啥意思 看别人代码抄的
//    
//    kmGLPopMatrix();
//    
//    CHECK_GL_ERROR_DEBUG();
}

