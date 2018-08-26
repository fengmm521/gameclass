/**********************************************
UI界面基类；
 
 **********************************************/

#include "UiBase.h"

using namespace cocos2d::ui;


bool UiBase::init()
{
    if ( !Layer::init() )  {      return false;    }
    
    //网络；
    //ClientSocketManger::sharedClientSocketManger()->connectSocket();//连接；
    //ClientSocketManger::sharedClientSocketManger()->send("898598888",100,this);  //发送；
    
    
    

    //界面；
	m_pNodeBase = GUIReader::getInstance()->widgetFromJsonFile("uiBase.ExportJson");
    this->addChild(m_pNodeBase);
    
    //m_pNodeBase->setScaleX(0.1);
    //m_pNodeBase->runAction(ScaleTo::create(0.5, 1, 1));
   // m_pNodeBase->setOpacity(10);
    //m_pNodeBase->runAction( FadeIn::create(1));
    
    //按钮；
    buttonInit();
    
    
    return true;
}



Armature *  UiBase::getArmatrue(string  heroID){    //===========根据ID导入动画
    
    if(heroID!=""){
    //导入动画
    string  strPath=heroID+".ExportJson";
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo(strPath.c_str());
    Armature *armature = Armature::create(heroID);
    armature->getAnimation()->playByIndex(0);
    
    return armature;
    }
    return nullptr;
}



string   UiBase::getQualityFrame1( int  quality)   //=============根据品质获取品质框图片名，方的；
{
    string  str="ui_c_frame1.png";
    switch (quality)
    {
        case  0:{  str="ui_c_frame1.png";      }   break;
        case  1:{  str="ui_c_frame2.png";      }   break;
        case  2:{  str="ui_c_frame2_1.png";      }   break;
        case  3:{  str="ui_c_frame3.png";      }   break;
        case  4:{  str="ui_c_frame3_1.png";    }   break;
        case  5:{  str="ui_c_frame3_2.png";      }   break;
        case  6:{  str="ui_c_frame4.png";    }   break;
        case  7:{  str="ui_c_frame4_1.png";      }   break;
        case  8:{  str="ui_c_frame4_2.png";    }   break;
            
        default: {  str="ui_c_frame1.png";     }   break;
            
    }
    return str;
}

string   UiBase::getQualityFrame2( int  quality)   //=============根据品质获取品质框图片名，长的；
{
    string  str="ui_dengji2.png";
    switch (quality)
    {
        case  0:{  str="ui_dengji2.png";      }   break;
        case  1:{  str="ui_dengji1.png";      }   break;
        case  2:{  str="ui_dengji2.png";      }   break;
        case  3:{  str="ui_dengji2.png";      }   break;
        case  4:{  str="ui_dengji2_1.png";    }   break;
        case  5:{  str="ui_dengji3.png";      }   break;
        case  6:{  str="ui_dengji3_1.png";    }   break;
        case  7:{  str="ui_dengji4.png";      }   break;
        case  8:{  str="ui_dengji4_1.png";    }   break;
            
        default: {  str="ui_dengji2.png";     }   break;
            
    }
    return str;
}

string   UiBase::getQualityFrame3( int  quality)   //=============根据品质获取品质框图片名，装备的框；
{
    string  str="ui_c_frameE1.png";
    switch (quality)
    {
        case  0:{  str="ui_c_frameE1.png";      }   break;
        case  1:{  str="ui_c_frameE2.png";      }   break;
        case  2:{  str="ui_c_frameE2_1.png";      }   break;
        case  3:{  str="ui_c_frameE3.png";      }   break;
        case  4:{  str="ui_c_frameE3_1.png";    }   break;
        case  5:{  str="ui_c_frameE3_2.png";      }   break;
        case  6:{  str="ui_c_frameE4.png";    }   break;
        case  7:{  str="ui_c_frameE4_1.png";      }   break;
        case  8:{  str="ui_c_frameE4_2.png";    }   break;
            
        default: {  str="ui_c_frameE1.png";     }   break;
            
    }
    return str;
}






int   UiBase::getGoodsType(string  goodsID){    //===根据ID获取类型，1英雄，2技能， 3装备，4材料；
    int i=atoi(goodsID.c_str());
    if(i<100000){  return  1;  }
    if(100000<i&&i<200000){  return  4;  }
    if(200000<i&&i<300000){  return  2;  }
    if(300000<i&&i<400000){  return  3;  }
    
    return  0;
}











///////

bool  UiBase::buttonInit(){
    
    
    
    Button  *buttonClose = static_cast<Button*>(Helper::seekWidgetByName(m_pNodeBase, "buttonClose"));           //关闭按钮；
    if (!buttonClose){ return false; }
    buttonClose->addTouchEventListener(CC_CALLBACK_2(UiBase::buttonEvent, this));
   
    /*
     Button  *buttonRecharge = static_cast<Button*>(Helper::seekWidgetByName(m_pNodeBase, "buttonBack"));         //VIP按钮；
     if (!buttonRecharge){ return false; }
     buttonRecharge->addTouchEventListener(CC_CALLBACK_2(UiBase::buttonEvent, this));
     
    
    */
    return  true;

}


void  UiBase::buttonEvent(Ref *pSender, Widget::TouchEventType type)             //按钮响应函数；
{
    int buttonNum=0;
    Button*  button=dynamic_cast<Button*>(pSender);
    string  str1="buttonBack";
    string  str2="buttonClose";

    if (button->getName().c_str()==str1) {  buttonNum=1;  }
    else if (button->getName().c_str()==str2) {  buttonNum=2;  }
    else{ buttonNum=0; }
    
    switch (buttonNum){
         //返回按钮；
//        case  1:
//        {
//            switch (type)
//            {
//                case  Widget::TouchEventType::BEGAN:
//                {
//                    
//                }
//                    break;
//                case  Widget::TouchEventType::MOVED:
//                {
//                    
//                    
//                }
//                    break;
//                    
//                case  Widget::TouchEventType::ENDED:
//                {
//                    //Layer * uiVIPLayer= UiVIP::create();
//                    //this->getParent()->addChild(uiVIPLayer);
//                    CC_SAFE_RETAIN(this);
//                    this->removeFromParent();
//                    
//                    
//                    
//                }
//                    break;
//                    
//                case  Widget::TouchEventType::CANCELED:
//                {
//                    
//                }
//                    break;
//                    
//                default:
//                    break;
//            }
//            
//            
//        }
//        break;
            
        //关闭按钮；
        case  2:
        {
            switch (type)
            {
                case  Widget::TouchEventType::ENDED:
                {
                   // ClientSocketManger::sharedClientSocketManger()->endSocket();//断开网络；
                    
                    CC_SAFE_RETAIN(this);
                    this->removeFromParent();
                    //MessageBox("base", "base");
                    
                 }
                    break;
                
                    
                default:
                    break;
            }
            
        }
        break;
 
            
        default:
            break;
            
    
    }
    
}


/*

////网络；
void UiBase::reciveDataHandler(std::string &data,int type,bool ispush){    //===自动接收到的服务器的信息，发送消息的ClientSockeManeger::send()
    if(ispush){
        log("push message======%s",data.c_str());
    }
    else{
        log("back   message===________===%s",data.c_str());
    
    }
}

ClientSocketManger::sharedClientSocketManger()->connectSocket();//连接；
ClientSocketManger::sharedClientSocketManger()->send("message",100,this);  //发送；

*/








void UiBase::onEnter()
{
    Layer::onEnter();
}

void UiBase::onExit()
{
    Layer::onExit();
}




