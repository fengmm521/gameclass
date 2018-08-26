//
//  MyContactListener.h
//  game1
//  这个是创建一些基本的cocos2d类时会用到
//  Created by 俊盟科技1 on 8/28/14.
//
//

#ifndef __game1__MyContactListener__
#define __game1__MyContactListener__

#include "cocos2d.h"
#include "external/Box2d/Box2D.h"
struct MyContact {
    b2Fixture *fixtureA;
    b2Fixture *fixtureB;
    bool operator==(const MyContact& other) const
    {
        return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
    }
};

class MyContactListener : public b2ContactListener {
    
public:
    std::vector<MyContact>_contacts;
    
    MyContactListener();
    ~MyContactListener();
    
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
};

#endif /* defined(__game1__MyContactListener__) */
