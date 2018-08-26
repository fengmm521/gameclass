//
//  WarLayerBase.h
//  game2
//
//  Created by 俊盟科技1 on 9/10/14.
//
//

#ifndef __game2__WarLayerBase__
#define __game2__WarLayerBase__

#include "cocos2d.h"

class WarLayerBase : public cocos2d::Layer
{
public:
    virtual bool init();
    // implement the "static create()" method manually
    int m_warType;  //战场类型,默认为1.副本战斗,2.PVP战斗,3.任务战斗
    CREATE_FUNC(WarLayerBase);
    
};
#endif /* defined(__game2__WarLayerBase__) */
