//
//  AndriodLogLayer.h
//  game4
//
//  Created by Junpeng Zhang on 12/26/14.
//
//
//资源加载适合cocos2d-x 3.2版本的cocostudio for mac 1.0.0
//

#ifndef __game4__AndriodLogLayer__
#define __game4__AndriodLogLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"
USING_NS_CC;
class AndriodLogLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    
    void menuTouchCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(AndriodLogLayer);

    void logLayerEnd(float dt);
};


#endif /* defined(__game4__AndriodLogLayer__) */
