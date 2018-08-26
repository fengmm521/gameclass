/***************************
副本失败对话框；


***************************/


#pragma once

#ifndef __LOSSDIALOG_H__
#define __LOSSDIALOG_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace std;

class LossDialog : public Layer
{
public:

	LossDialog();
	~LossDialog();
    virtual bool init();  
	CREATE_FUNC(LossDialog);

	//按钮
	void  button_goEvent(Ref *pSender, Widget::TouchEventType   type);
	void  button_backEvent(Ref *pSender, Widget::TouchEventType   type);

	Widget *m_pNode;
	
    virtual void onExit();
    virtual void onEnter();
	
};

#endif
