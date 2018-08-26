//
//  ObjectMassageManger.cpp
//  game3
//
//  Created by 俊盟科技1 on 11/4/14.
//
//

#include "ObjectMassageManger.h"

static ObjectMassageManger *s_sharedObjectMassageManger = nullptr;

ObjectMassageManger *ObjectMassageManger::sharedObjectMassageManger()
{
    if (s_sharedObjectMassageManger == nullptr)
    {
        s_sharedObjectMassageManger = new ObjectMassageManger();
        if (!s_sharedObjectMassageManger || !s_sharedObjectMassageManger->init())
        {
            CC_SAFE_DELETE(s_sharedObjectMassageManger);
        }
    }
    return s_sharedObjectMassageManger;
}

void ObjectMassageManger::destroyInstance()
{
    
    CC_SAFE_RELEASE_NULL(s_sharedObjectMassageManger);
}

ObjectMassageManger::ObjectMassageManger(void)
{
  
}


ObjectMassageManger::~ObjectMassageManger(void)
{
   
}


bool ObjectMassageManger::init()
{
    bool bRet = false;
    do
    {
        
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}
