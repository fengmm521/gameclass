//
//  FubeiMapUILayer.h
//  game2
//
//  Created by 俊盟科技1 on 9/15/14.
//
//  副本地图层
//

#ifndef __game2__FubeiMapUILayer__
#define __game2__FubeiMapUILayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class FubeiMapUILayer : public cocos2d::Layer
{
public:
    virtual bool init();
    // implement the "static create()" method manually
    static FubeiMapUILayer* createForScence(Layer* p);
    Layer* m_parent;
    ui::Widget* _layout;
    
    void  buttonHeroEvent(Ref *pSender, ui::Widget::TouchEventType  type);
    
    void pageViewEvent(Ref *pSender,ui::PageView::EventType type);
    
    void buttonRightTouched();
    void buttonLeftTouched();
    void buttonBackTouched();
    //page view

    void buttonTouchedWithNumber(int number);


    
    void selectJuQingPageView();
    void selectJingYingPageView();
    void selectHouDongPageView();
    
    
    ui::PageView* mapPageView;
    
    int selectCheckBoxType;
    ui::CheckBox* checkBoxJuQing;   //1
    ui::CheckBox* checkBoxJingYing; //2
    ui::CheckBox* checkBoxHuoDong;  //3
    
    
    void checkBoxEvent(Ref *pSender,ui::CheckBox::EventType type);
    
    ui::ImageView* point1Image;  //下方点1
    ui::ImageView* point2Image;  //下方点2
    ui::ImageView* point3Image;  //下方点3
    
    int selectPage;   //1.
    
    void pageviewChanged();
    void toPageViewLeftPage();
    void toPageViewRightPage();
    
    
    
    void closd();
    
    virtual void onExit();
    virtual void onEnter();

    
};
#endif /* defined(__game2__FubeiMapUILayer__) */
