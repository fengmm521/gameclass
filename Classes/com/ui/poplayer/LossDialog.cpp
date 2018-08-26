#include "LossDialog.h"
#include "MainCityScence.h"
using namespace cocos2d;
using namespace cocos2d::ui;

LossDialog::LossDialog()
{
	
}
LossDialog::~LossDialog()
{	
}

void LossDialog::onExit()
{
    Layer::onExit();
}
void LossDialog::onEnter()
{
    Layer::onEnter();
}

bool LossDialog::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    do
    {
        m_pNode = GUIReader::getInstance()->widgetFromJsonFile("ui/winLoss/winLoss_2.ExportJson");
        this->addChild(m_pNode);
        //sss
        Button  *button_go = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "button_go"));             //£Ω£ΩºÃ–¯∞¥≈•£ª
        if (!button_go){ return false; }
        button_go->addTouchEventListener(CC_CALLBACK_2(LossDialog::button_goEvent, this));
        
        Button  *button_back = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "button_back"));           //£Ω£Ω∑µªÿ∞¥≈•£ª
        if (!button_back){ return false; }
        button_back->addTouchEventListener(CC_CALLBACK_2(LossDialog::button_backEvent, this));
    }while (0);
    return true;
}
void  LossDialog::button_goEvent(Ref *pSender, Widget::TouchEventType   type)
{
	switch (type)
	{
	case  Widget::TouchEventType::BEGAN:
        {
            
        }
		break;
	case  Widget::TouchEventType::MOVED:
	   {

	   }
		break;

	case  Widget::TouchEventType::ENDED:
	   {
           CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Click_Button.wav");
       }
		break;

	case  Widget::TouchEventType::CANCELED:
        {
            
        }
		break;

	default:
		break;
	}
}

void  LossDialog::button_backEvent(Ref *pSender, Widget::TouchEventType   type)
{
	switch (type)
	{
	case  Widget::TouchEventType::BEGAN:
        {
            
        }
		break;
	case  Widget::TouchEventType::MOVED:
        {
            
        }
		break;

	case  Widget::TouchEventType::ENDED:
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Click_Button.wav");
            MainCityScence* mainl = MainCityScence::create();
            cocos2d::Scene* sc = cocos2d::Scene::create();
            sc->addChild(mainl);
            Director::getInstance()->replaceScene(sc);
        }
		break;
	case  Widget::TouchEventType::CANCELED:
        {
            
        }
		break;
	default:
		break;
	}
}