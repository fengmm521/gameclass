/**********************************************
英雄详情界面；


**********************************************/
#pragma once

#ifndef __UiHeroDetail_H__
#define __UiHeroDetail_H__


#include "cocos2d.h"
#include"cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace std;

#include"UiBase.h"
#include"LocalDataConfig.h"
#include"LocalDataManger.h"
#include"UiDepot.h"

#include"Account.h"

////////////
#define kHeroleveUpBtnTag 100
#define kHeroStarUpBtnTag 101


class UiHeroDetail : public UiBase
{
public:
    //初始化函数；
    UiHeroDetail();
    ~UiHeroDetail();
    
    virtual bool init();  
	CREATE_FUNC(UiHeroDetail);
    virtual void onExit();
    virtual void onEnter();

    static UiHeroDetail* create(string  heroID);
    
    //设置面板；
     void  mainPanelInit(Widget* imageItem,string  heroID);  //====主面板设置；
  
     void  setLevel(Widget * pWidget,int  level);                     //设置等级；
     void  setHeroName(Widget * pWidget, string  name,int  quality);   //名字；（品质）
     void  setSword(Widget * pWidget, int  sword);                    //战力；
     void  setExperience(Widget * pWidget, string   experience);       //设置经验；
     void  setStar(Widget* pWidget,int starLevel);                    //设置星级；
     void  setEquip(Widget * pWidget, vector<string>  equip);           //设置装备；
    
    
    //星阶面板
    void   setPanelStar();
    
    //技能面板
    bool   setPanelSkill();
    void   setSkillItem(Widget* imageItem,string  heroID);              //设置一个精灵项；
    void  setHeadBK(Widget* pWidget,string frameLevel,string  nameID);   //设置底框；
    void  setHead(Widget* pWidget, string headImage);                   //设置头像；
    
    
    
    //属性面板
    void   setPanelProperty();
    
    //羁绊面板
    void   setPanelTie();
    
 
    //响应函数；
    void  scrollViewEvent(Ref *pSender,    ui::ScrollView::EventType type  );      //滚动图层回调函数，；
    void  sliderEvent(Ref *pSender, Slider::EventType type);
    
	//按钮;
    
	virtual bool  buttonInit();                           //初始化按钮；
    virtual void  buttonEvent(Ref *pSender, Widget::TouchEventType    type);   //按钮响应；
    void  buttonPress(Ref *pSender);
    
    
    
    //
    
public:
    string  m_heroID;               //英雄ID;
    Widget *m_pNode;                //UI界面；
    
    Configtab_card_attribute_sysDataST  m_mapDataST;   //英雄的属性表；
    HeroProperty    m_heroProperty;                    //英雄的属性；
    
    Configtab_equipbase_sysDataST     m_equipST;       //装备的属性表；
    
    Configtab_skill_visual_effectDataST    m_skillST;    //技能表；
    //Configtab_skill_visual_effectDataST    m_skillST2 ;
   
    //需要从帐号里获取的数据；
    vector<string>  m_string;          //一个帐号里的英雄；
    vector<string>  m_equip;           //一个英雄里的装备；
    vector<string>  m_skill;           //一个英雄里的技能；
                  
    float  m_panelHight;
    float  m_percent;
    
    //UiAccount account;
   //Account*  m_account;
    
    
//界面效果
private:
    //英雄技能升级效果,map<skillID,Action>
    std::map<string,Armature*> s_skillUpEffectMap;
    //Armature* s_SkillUpEffect;
    //英雄星阶升星效果
    Armature* s_StarUpEffect;//英雄升星动画tag = 101

    //英雄星阶升级效果
    Armature* s_LeveUpEffect;//英雄升级动画tag=100,
    
    //动画结束帧事件:playEnd
    //动画效果播放:play
    void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
    
    //在技能图标上播放动画
    void playSKillUpEffectForImage(ImageView* skillImage);
    //在播放英雄升级动画
    void playHeroLeveUpEffect();
    //播放英雄升星动画
    void playHeroStarUpEffect();
    
    //技能升级按钮被按下事件
    void  buttonSkillEvent(Ref *pSender, ui::Widget::TouchEventType   type);
    void skillLeveUpButtonEventForSkillID(int skillID);
    void skillLeveUpEffectPlayEnd(int skillID);
    
    //星阶中的动画播放结束,effect,英雄升级动画tag=100,英雄升星动画tag = 101
    void heroEffectPlayEnd(int effectType);
    
};

#endif
