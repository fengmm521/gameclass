//
//  WarLayerBase.cpp
//  game2
//
//  Created by 俊盟科技1 on 9/10/14.
//
//

#include "WarLayerBase.h"
// on "init" you need to initialize your instance
bool WarLayerBase::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_warType = 1; //默认为1.副本战斗,2.PVP战斗,3.任务战斗
    
    
    return true;
}
