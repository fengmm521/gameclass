//
//  PoPUIManger.cpp
//  game2
//
//  Created by 俊盟科技1 on 9/15/14.
//
//

#include "PoPUIManger.h"


static PoPUIManger *s_sharedPoPUIManger = nullptr;

PoPUIManger *PoPUIManger::sharedPoPUIManger()
{
    if (s_sharedPoPUIManger == nullptr)
    {
        s_sharedPoPUIManger = new PoPUIManger();
        if (!s_sharedPoPUIManger || !s_sharedPoPUIManger->init())
        {
            CC_SAFE_DELETE(s_sharedPoPUIManger);
        }
    }
    return s_sharedPoPUIManger;
}

void PoPUIManger::destroyInstance()
{
    
    CC_SAFE_RELEASE_NULL(s_sharedPoPUIManger);
}

bool PoPUIManger::init()
{
    bool bRet = false;
    do
    {
        
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}
void PoPUIManger::OpenNewPoPLayer(ScenceChangeDataST st)  //
{
    
}
void PoPUIManger::loadResInit()          //加载资源
{
    
}
void PoPUIManger::loadResStart()         //开始加载
{
    
}
void PoPUIManger::addXML()
{
    
}
void PoPUIManger::addRes()
{
    
}
