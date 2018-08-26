//
//  Box2dWordManger.cpp
//  game1
//
//  Created by 俊盟科技1 on 8/30/14.
//
//

#include "Box2dWordManger.h"
#include "GameViewConfig.h"
#include "Box2dConfig.h"
#include "BaseSprite.h"
#include "Box2dSprite.h"
#include "SkillBullet.h"

#define kAttackRange1   230 //220
#define kAttackRange2   290
#define kAttackRange3   430
#define kAttackRange4   520
using namespace cocos2d;
using namespace std;

static Box2dWordManger *s_sharedBox2dWordManger = nullptr;

Box2dWordManger *Box2dWordManger::sharedBox2dWordManger()
{
    if (s_sharedBox2dWordManger == nullptr)
    {
        s_sharedBox2dWordManger = new Box2dWordManger();
        if (!s_sharedBox2dWordManger || !s_sharedBox2dWordManger->init())
        {
            CC_SAFE_DELETE(s_sharedBox2dWordManger);
        }
    }
    return s_sharedBox2dWordManger;
}

void Box2dWordManger::destroyInstance()
{
    
    CC_SAFE_RELEASE_NULL(s_sharedBox2dWordManger);
}

Box2dWordManger::Box2dWordManger(void)
{
  
}


Box2dWordManger::~Box2dWordManger(void)
{
   
}


bool Box2dWordManger::init()
{
    bool bRet = false;
    do
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
        
        //可以在这里初始化一个地图边界
        list<Point> mapEagePointList;
        mapEagePointList.clear();
        initMapBoxWorldEdgeShape(mapEagePointList);
        
        s_maxInt16 = 0; //初始化已设置精灵碰撞体形状为0个。
        
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}
//使用地图坐标点绘制地图可移动范围,地图的碰撞编号设置为1
void Box2dWordManger::initMapBoxWorldEdgeShape(list<Point> MapPointList)
{
    if (MapPointList.empty()) {//如果所给的绘置点为空,绘制边界为游戏屏边界
        
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
        
    }else{
        
    }
}
//实现这个方法来绘制地图内部不可通过点
void Box2dWordManger::initInMapCollision(list<list<Point>> inMapPointList)
{
    
}
//void Box2dWordManger::startBox2dWorld()//战斗开始时开启物理引擎
//{
//    scheduleUpdate();
//}
//void Box2dWordManger::stopBox2dWorld()//战斗结束时关闭物理引擎以省电
//{
//    unscheduleUpdate();
//}

//碰撞检测扫描
void Box2dWordManger::box2duUdate(float dt)
{
    //box2d-------------------
    
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    _world->Step(dt, velocityIterations, positionIterations);
    
    
    //移动相关
    // Loop through all of the Box2D bodies in our Box2D world..
    for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) {
        
        // See if there's any user data attached to the Box2D body
        // There should be, since we set it in addBoxBodyForSprite
        if (b->GetUserData() != NULL) {
            //更新精灵坐标
            Box2dSprite* sptmp = (Box2dSprite*)b->GetUserData();
            switch (sptmp->box2dSpriteType) {
                case kSpriteBox2d:
                {
                    
                    BaseSprite *sprite = (BaseSprite *)b->GetUserData();
                    if (!sprite->s_isDie) {
                        if (sprite->s_isMoveForBox2d && (sprite->m_targetSp) != nullptr && !(sprite->m_targetSp->s_isDie) && !(sprite->isTouchMove)) {
                            Point snakePoint;
                            snakePoint = Vec2(b->GetPosition().x*PTM_RATIO,b->GetPosition().y*PTM_RATIO);
                            sprite->setPosition(snakePoint);
                            
                            //如果精灵在追击中，为精灵添加一个追击速度
                            Point tmpPo = (sprite->m_targetSp->getPosition());
                            tmpPo.subtract(sprite->getPosition());
                            tmpPo.normalize();//得到速度的单位矢量
                            //得到当前精灵移动速度
                            tmpPo.scale(sprite->m_heroDataST.move_speed/PTM_RATIO);                    b->SetLinearVelocity(b2Vec2(tmpPo.x,tmpPo.y));
                        }else{
                            b->SetLinearVelocity(b2Vec2(0,0));
                            Point sn = sprite->getPosition();
                            b2Vec2 b2Position = b2Vec2(sn.x/PTM_RATIO,sn.y/PTM_RATIO);
                            b->SetTransform(b2Position,0.0f);
                        }
                    }
                }
                    break;
                case kButtleBox2d:
                {
                    SkillBullet *sprite = (SkillBullet *)b->GetUserData();
                    if (sprite) {
                        if (sprite->s_isMoveForBox2d && sprite->m_toSp != nullptr) {
                            Point snakePoint;
                            snakePoint = Vec2(b->GetPosition().x*PTM_RATIO,b->GetPosition().y*PTM_RATIO);
                            sprite->setPosition(snakePoint);
                            //如果精灵在追击中，为精灵添加一个追击速度
                            Point tmpPo = sprite->m_toSp->getPosition();
                            tmpPo.add(sprite->m_toSp->s_beBulltePoint);
                            tmpPo.subtract(sprite->getPosition());
                            tmpPo.normalize();//得到速度的单位矢量
                            //得到当前精灵移动速度
                            tmpPo.scale(sprite->m_moveSpeed/PTM_RATIO);
                            b->SetLinearVelocity(b2Vec2(tmpPo.x,tmpPo.y));
                            float angletmp = -(tmpPo.getAngle()/6.2831852f)*360;
                            //log("jiando=%f",angletmp);
                            sprite->setRotation(angletmp);
                        }else if(sprite->m_toSp == nullptr){
                            b->SetLinearVelocity(b2Vec2(0,0));
                            Point snakePoint = sprite->getPosition();
                            b2Vec2 b2Position = b2Vec2(snakePoint.x/PTM_RATIO,
                                                       snakePoint.y/PTM_RATIO);
                            b->SetTransform(b2Position,0.0f);
                        }else{
                            b->SetLinearVelocity(b2Vec2(0,0));
                            Point snakePoint = sprite->getPosition();
                            b2Vec2 b2Position = b2Vec2(snakePoint.x/PTM_RATIO,
                                                       snakePoint.y/PTM_RATIO);
                            b->SetTransform(b2Position,0.0f);
                        }
                    }
                }
                    break;
                default:
                    break;
            }
            
        }
    }
    //----------------------
    //碰撞检测
/*
    当检测到碰撞时，要销毁掉当前检测体,避免发生重复碰撞
    在检测到碰撞之后，主动精灵要停止移动并进行一次攻击，同时目标精灵要移除碰撞检测体，
 在动精灵攻击结束时，再次判断是否要再次创建碰撞体，如果目标在攻击范围内，或者目标没有在移动中，无需在目标身上创建碰撞测检体。
    如果目标没有移动，则向目标可攻击位移动，移动过程中可以被目标开始移动打断，打断之后，马
 上判读目标是否在攻击范围内，在，则进行一次攻击，攻击结束时再次判断是否要创建碰撞体。
    如果目标在移动中，并在攻击范围内，则再进行一次攻击。攻击结束时再次判断是否要创建碰撞体。
    如果目标在移动中，且不在攻击范围内，则创建碰撞体，并向目标移动。
*/
    //std::vector<Box2dDestroyCollision>toDestroy;//碰撞之后要删除的碰撞体
    std::vector<MyContact>::iterator pos;
    for(pos = _contactListener->_contacts.begin(); pos != _contactListener->_contacts.end(); ++pos) {
        MyContact contact = *pos;
        
        // Get the box2d bodies for each object
        
        b2Body *bodyA = contact.fixtureA->GetBody();
        b2Body *bodyB = contact.fixtureB->GetBody();
        if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
            Box2dSprite *spriteAtmp = (Box2dSprite *) bodyA->GetUserData();
            Box2dSprite *spriteBtmp = (Box2dSprite *) bodyB->GetUserData();
            
            if (spriteAtmp->box2dSpriteType == kSpriteBox2d && spriteBtmp->box2dSpriteType == kSpriteBox2d) {
                BaseSprite* spriteA = dynamic_cast<BaseSprite*>(spriteAtmp);
                BaseSprite* spriteB = dynamic_cast<BaseSprite*>(spriteBtmp);
                if ((spriteA->m_targetSp) == spriteB && (spriteA->s_isMove)) {//A追击Ｂ
                    if (spriteB->s_fixtureMap[spriteA] == NULL) {
                        continue;
                    }
                    spriteB->s_b2body->DestroyFixture(spriteB->s_fixtureMap[spriteA]);
                    //deleInt16((int16)spriteA->getTag());
                    //一个body一个碰撞编号，
                    bodyA->SetLinearVelocity(b2Vec2(0,0));
                    spriteA->Attack();
                    break;
                }
                if ((spriteB->m_targetSp) == spriteA && (spriteB->s_isMove)) {//B追击Ａ
                    if (spriteA->s_fixtureMap[spriteB] == NULL) {
                        continue;
                    }
                    spriteA->s_b2body->DestroyFixture(spriteA->s_fixtureMap[spriteB]);
                    //deleInt16((int16)spriteB->getTag());
                    bodyB->SetLinearVelocity(b2Vec2(0,0));
                    spriteB->Attack();
                    break;
                }

            }else if(spriteAtmp->box2dSpriteType == kButtleBox2d)
            {
                SkillBullet* spriteA = dynamic_cast<SkillBullet*>(spriteAtmp);
                BaseSprite* spriteB = dynamic_cast<BaseSprite*>(spriteBtmp);
                if (spriteA->m_toSp == spriteB && spriteA->s_isMove) {//A追击Ｂ
                    
                    spriteB->s_b2body->DestroyFixture(spriteB->s_fixtureMap[spriteA]);
                    //deleInt16((int16)spriteA->getTag());
                    bodyA->SetLinearVelocity(b2Vec2(0,0));
                    spriteA->Attack();
                    break;
                }
            }else if (spriteBtmp->box2dSpriteType == kButtleBox2d){
                SkillBullet* spriteB = dynamic_cast<SkillBullet*>(spriteBtmp);
                BaseSprite* spriteA = dynamic_cast<BaseSprite*>(spriteAtmp);
                if (spriteB->m_toSp == spriteA && spriteB->s_isMove) {//B追击Ｂ
                    
                    spriteA->s_b2body->DestroyFixture(spriteA->s_fixtureMap[spriteB]);
                   // deleInt16((int16)spriteB->getTag());
                    bodyB->SetLinearVelocity(b2Vec2(0,0));
                    spriteB->Attack();
                    break;
                }
            }
        }
    }
}
int16 Box2dWordManger::getOnlyInt16()       //为新形状获取一个新的int16编号
{
    if (s_delInt16.empty()) {
        s_maxInt16 = s_maxInt16+1;
        return s_maxInt16+kMinCollisionIndex;
    }else{
        int16 tmp = s_delInt16.front();
        s_delInt16.pop_front();
        return tmp+kMinCollisionIndex;
    }
}
void Box2dWordManger::deleInt16(int16 tag)
{
    s_delInt16.push_back(tag-kMinCollisionIndex);
}
//改变精灵的攻击范围
b2Fixture* Box2dWordManger::changeBodyForInitSpiite(BaseSprite* initSp,int attackNewRange)
{
    b2Body *body = initSp->s_b2body;
    int16 tmp16 = initSp->getTag();
    
    body->DestroyFixture(initSp->s_arrackRangeFixture);
    
    int box2dRange;
    
    switch (attackNewRange) {
        case 1:
        {
            box2dRange = kAttackRange1;   // < 208
        }
            break;
        case 2:
        {
            box2dRange = kAttackRange2;   //210 - 295
        }
            break;
        case 3:
        {
            box2dRange = kAttackRange3;   //392 - 435
        }
            break;
        case 4:
        {
            box2dRange = kAttackRange4;
        }
            break;
        default:
        {
            box2dRange = attackNewRange;
        }
            break;
    }
    
    b2CircleShape circleShape;
    //
    circleShape.m_radius = box2dRange/PTM_RATIO;
    //攻击碰撞体为圆形,半径大小与攻击距离有关
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    //设置精灵的碰撞体分组
    fixtureDef.filter.groupIndex = tmp16;
    fixtureDef.filter.maskBits = 0x00000;
    //当两个组groupIndex不相同时，两个物体的mask按位与并类别categoryBits按位与都不为0时可碰撞
    fixtureDef.isSensor = true; //是否为传感器
    fixtureDef.density = 1.0f;//密度为1
    fixtureDef.friction = 0.3f; //摩擦系数
    return  body->CreateFixture(&fixtureDef);
}
//根据精灵的攻击范围初始化精灵的攻击碰撞体
b2Fixture* Box2dWordManger::addBodyForInitSpiite(BaseSprite* initSp,int attackRange)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(initSp->getPosition().x/PTM_RATIO, initSp->getPosition().y/PTM_RATIO);
    bodyDef.userData = initSp;
    b2Body *body = _world->CreateBody(&bodyDef);
    initSp->s_b2body = body;
    int16 tmp16 = getOnlyInt16();
    s_fixtureMap[initSp] = tmp16;
    initSp->setTag(tmp16);
    b2CircleShape circleShape;
    //
    int box2dRange;
    
    switch (attackRange) {
        case 1:
        {
            box2dRange = kAttackRange1;
        }
            break;
        case 2:
        {
            box2dRange = kAttackRange2;
        }
            break;
        case 3:
        {
            box2dRange = kAttackRange3;
        }
            break;
        case 4:
        {
            box2dRange = kAttackRange4;
        }
            break;
        default:
        {
            box2dRange = attackRange;
        }
            break;
    }
    
    circleShape.m_radius = box2dRange/PTM_RATIO;
    
    //攻击碰撞体为圆形,半径大小与攻击距离有关
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    //设置精灵的碰撞体分组
    fixtureDef.filter.groupIndex = tmp16;
    fixtureDef.filter.maskBits = 0x00000;
    //当两个组groupIndex不相同时，两个物体的mask按位与并类别categoryBits按位与都不为0时可碰撞
    //fixtureDef.filter.categoryBits = 0x00001;
    fixtureDef.isSensor = true; //是否为传感器
    fixtureDef.density = 1.0f;//密度为1
    fixtureDef.friction = 0.3f; //摩擦系数
    return body->CreateFixture(&fixtureDef);
}
//初始化子弹的碰撞体
void Box2dWordManger::addBodyForInitButtle(SkillBullet* initSp,int buttleRiad)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    //bodyDef.linearDamping = 0.0f;
    //bodyDef.angularDamping = 0.0f;
    bodyDef.position.Set(initSp->getPosition().x/PTM_RATIO, initSp->getPosition().y/PTM_RATIO);
    bodyDef.userData = initSp;
    b2Body *body = _world->CreateBody(&bodyDef);
    initSp->s_b2body = body;
    int16 tmp16 = getOnlyInt16();
    s_fixtureMap[initSp] = tmp16;
    initSp->setTag(tmp16);
    
    b2CircleShape circleShape;
    //
    circleShape.m_radius = buttleRiad/PTM_RATIO;
    //攻击碰撞体为圆形,半径大小与攻击距离有关
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    //设置精灵的碰撞体分组
    fixtureDef.filter.groupIndex = tmp16;
    //当两个组groupIndex不相同时，两个物体的mask按位与并类别categoryBits按位与都不为0时可碰撞
    fixtureDef.filter.maskBits = 0x00000;
    //fixtureDef.filter.categoryBits = 0x00001;
    fixtureDef.isSensor = true; //是否为传感器
    fixtureDef.density = 1.0f;//密度为1
    fixtureDef.friction = 0.3f; //摩擦系数
    body->CreateFixture(&fixtureDef);

}
//为b2body增加新的攻击者精灵碰撞体
b2Fixture* Box2dWordManger::addSpriteToWorldWithCollision(BaseSprite* sp,Box2dSprite* attacksSp)
{
    b2Body *body = sp->s_b2body;
    Point poSape;
    int tag;
    switch (attacksSp->box2dSpriteType) {
        case kSpriteBox2d:
        {
            BaseSprite* tmp =   dynamic_cast<BaseSprite*>(attacksSp);
            tag = tmp->getTag();
            poSape = Vec2(0.0f,0.0f);
        }
            break;
        case kButtleBox2d:
        {
            SkillBullet* tmp =   dynamic_cast<SkillBullet*>(attacksSp);
            tag = tmp->getTag();
            poSape = sp->s_beBulltePoint;
        }
            break;
        default:
            break;
    }
    b2CircleShape circleShape;
    if (attacksSp->box2dSpriteType == kButtleBox2d) {
        circleShape.m_radius = kCollisionRadius/PTM_RATIO;
       circleShape.m_p = b2Vec2(poSape.x/PTM_RATIO,poSape.y/PTM_RATIO);
    }else{
        circleShape.m_radius = kCollisionRadius/PTM_RATIO;

    }
    //攻击碰撞体为圆形,半径大小与攻击距离有关
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.filter.groupIndex = (int16)tag;
    //当两个组groupIndex不相同时，两个物体的mask按位与并类别categoryBits按位与都不为0时可碰撞
    fixtureDef.filter.maskBits = 0x00000;
    //fixtureDef.filter.categoryBits = 0x00001;
    fixtureDef.isSensor = true; //是否为传感器
    fixtureDef.density = 1.0f;//密度为1
    fixtureDef.friction = 0.3f; //摩擦系数
    return body->CreateFixture(&fixtureDef);
}
////精灵死亡时，删除精灵身上攻击碰撞体
void Box2dWordManger::delBodyFixture(b2Body* b2body,int tag)
{
    _world->DestroyBody(b2body);
    deleInt16((int16)tag);
}
