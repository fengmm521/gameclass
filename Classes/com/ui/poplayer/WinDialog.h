/***************************


***************************/
#pragma once

#ifndef __WINDIALOG_H__
#define __WINDIALOG_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "WarConfig.h"


USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace std;

class BaseSprite;

class WinDialog : public Layer
{
public:
	WinDialog();
	~WinDialog();

    virtual bool init();  
	CREATE_FUNC(WinDialog);
    
	void  button_goEvent(Ref *pSender, Widget::TouchEventType   type);
	void  button_backEvent(Ref *pSender, Widget::TouchEventType   type);
	Widget *m_pNode;

    virtual void onExit();
    virtual void onEnter();

private:
    
    ImageView* s_winIconBG;  //胜利背景图标
    
    ImageView* s_winIcon;   //胜利图标
    
    ImageView* s_winText;   //胜利两个字
    
    ImageView* s_star1;     //第一颗星星
    ImageView* s_star2;     //第二颗星星
    ImageView* s_star3;     //第三果星星
    
    
    
    ImageView* s_boxIcon;   //宝箱数量图标
    ImageView* s_goldIcon;  //金币数量图标
    
    Text* s_boxLabel;        //宝箱数量
    
    int s_boxtmpNumber;
    void setBoxNumber(float dt);
    
    Text* s_goldNumberLabel; //金币数量
    int s_goletmpNumber;
    void setGoldNumber(float dt);
    
    //宝箱与金币数量显示
    int s_boxNumber;         //要设置的宝箱数量
    int s_goldNumber;        //要设置的金币数量
    
    //物品奖利
    std::list<int> s_getGoodIDlist; //战斗奖励的物品ID
    
    void setGoodActionTimer(float dt);
    
    //英雄的经验奖利
    int s_winGetExp[kUserHeroNumber];   //5个战斗结束得到的经验奖利值
    
    int s_heroLeveArr[kUserHeroNumber]; //
    
    float s_winBarPercent[kUserHeroNumber]; //经验条停止时的值
    
    //玩家参战的英雄数据
    WarHeroData s_warHeroArr[kUserHeroNumber];
    
    std::list<ImageView*> s_goodBoxVector;
    
    ImageView* s_heroBoxArr[kUserHeroNumber];
    
    
    //cocos2d::ui::LoadingBar* s_HeroExpBarArr[kUserHeroNumber];
    
    
    void showWinActionStart();//开始播放动画
    
    void onWinIconSetEnd(float dt); //胜利图标动画播放结束事件
    
    void onStarSetEnd();    //星星动画播放结束事件
    
    void setBoxNumberWithAction();
    void onSetBoxNumberEnd();
    
    void setGoleNumberWithAction();
    void onSetGoldNumberEnd();
    
    void setWinGoodWithAction();    //使用动画播放战斗结束时得到的物品奖利
    
    void setWinHeroExpWithAction(); //设置经验条动画
    
    //
    LoadingBar* loadbar[kUserHeroNumber];
    float loadBarTmp[kUserHeroNumber];
    bool isLoadEnd[kUserHeroNumber];
    float loadbarPercent[kUserHeroNumber];
    void loadingbarAction(float dt);

    void allActionEnd();//所有动画播放结束
    
    bool isActionEnd;
    
    //当用户想要提前结束动时点击了屏幕
    void whenUserTouchEndAction();
    
    
    
};

#endif
