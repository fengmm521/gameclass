//
//  LoadingScence.h
//  game1
//
//  Created by 俊盟科技1 on 9/4/14.
//  游戏数据加载场景动画
//

#ifndef __game1__LoadingScence__
#define __game1__LoadingScence__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ScenceLayerConfig.h"
using namespace cocos2d;
class LoadingScence : public cocos2d::Layer
{
public:
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(LoadingScence);
    static Scene* createScene();
private:
    Sprite *bgSprite;//进度条底
    Sprite *hpSprite;//进度条
    int s_loaded;  //已加载资源数量
    int s_maxLoad; //总计加载资源数量
    ProgressTimer* progressTimer;
    ScenceChangeDataST s_st;
    
    ui::Text *loadText;    //当前加载的资源名称
    ui::Text *gameVersion; //游戏版本号
    
    //添加一个资源到加载列表
    void addRes(std::string res);
    //添加一个xml加载项到列表
    void addXml(int n);
    void loadDataInit();
    
    void loadStart(); //开始载入资源
    std::list<int> s_xmlLoadList;
    void loadXml(int n);
    std::list<std::string> s_resLoadList;
    void loadRes(std::string filename);
    void updateBar();//更新进度条显示
    
};
#endif /* defined(__game1__LoadingScence__) */
