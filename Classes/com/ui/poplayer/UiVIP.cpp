/**********************************************
 VIP权利；
 
 PageView案例；
 **********************************************/

#include "UiVIP.h"
#include"UiRecharge.h"

using namespace cocos2d::ui;


bool UiVIP::init()
{
    if ( !UiBase::init() )  {      return false;    }

    //界面；
	m_pNode = GUIReader::getInstance()->widgetFromJsonFile("uiVIP.ExportJson");     //  VIPRecharge/uiVIP.ExportJson
	m_pNodeBase->getChildByName("imageBK0")->setVisible(false);
    m_pNodeBase->addChild(m_pNode);
	m_pNode->setTouchEnabled(false);
    //m_pNodeBase->runAction(Blink::create(2, 10));
    
    
    //动画；
    /*
	ArmatureDataManager::getInstance()->addArmatureFileInfo("sprite/1002/10020.png", "sprite/1002/10020.plist", "sprite/1002/1002.ExportJson");
	Armature *armature = Armature::create("1002");
	armature->getAnimation()->playByIndex(0);
	Point  pt = Helper::seekWidgetByName(m_pNode, "image_hd_heroname")->getPosition();
	pt += Point(0, 80);
    
	armature->setPosition(pt);
	armature->setScale(1.7);
	m_pNode->addChild(armature);
    */
    
    //进度条
    progressInit();
    
    //翻页层；
    pageViewInit(10);
    
    
    //按钮；
    buttonInit();
	
    
    
    
    return true;
}



void  UiVIP::progressInit(){                    //进度条，以及上下的图片，文字；
    
    
    ImageView* imageVIPLevel=static_cast<ImageView*>(Helper::seekWidgetByName(m_pNode,"imageVIPLevel"));
    imageVIPLevel->loadTexture("ui_chongzhi_11.png",TextureResType::PLIST);                                // PLIST：从PLIST文件中；LOCAL：从单独的PNG文件中；
    
    
    Text* textOwe=static_cast<Text*>(Helper::seekWidgetByName(m_pNode,"textOwe"));
    textOwe->setString("再充值200元即可以成为VIP3");
    
    LoadingBar* progressRecharge=static_cast<LoadingBar*>(Helper::seekWidgetByName(m_pNode,"progressRecharge"));
    progressRecharge->setPercent(60);
    
    Text* textProgress =static_cast<Text*>(Helper::seekWidgetByName(m_pNode,"textProgress"));
    textProgress->setString("60/100");
    
}




bool  UiVIP::pageViewInit(int count){                    //初始化翻页层；
    
    //初始文字集
    vector<string> str;
    for (int i=1; i<20; i++){
        string  strMessage=to_string(i)+".有无限体力！！";
        str.push_back(strMessage);
        
    }
    
    
    //获取翻页层；
    PageView *pageView=static_cast<PageView*>(Helper::seekWidgetByName(m_pNode,"pageView"));
    if (!pageView){ return false; }
    
    //第一子层；
    Layout * pageLayer1=static_cast<Layout*>(Helper::seekWidgetByName(pageView,"pageLayer1"));
    if (!pageLayer1){ return false; }
    setTextPrivilege(pageLayer1,str, 1,10);
    
    //克隆第一子层，在后面添加子层；
    for (int i=2; i<count+1; i++) {
        Layout * pageLayer2=static_cast<Layout*>(pageLayer1->clone());
        
        pageView->addPage(pageLayer2);
        
        setTextPrivilege(pageLayer2,str, i,10);     //设置层里的文字；(层，文字容器，等级,文字项)
    }
    
    //第一页的页码；
    Text *  textPage=static_cast<Text*>(Helper::seekWidgetByName(m_pNode,"textPage"));
    ImageView *  imagePage=static_cast<ImageView *>(Helper::seekWidgetByName(m_pNode,"imagePage"));
    imagePage->setPositionX(textPage->getPositionX()-23);
    
    //翻页层回调函数，
    
    pageView->addEventListener(CC_CALLBACK_2(UiVIP::pageViewEvent, this));    //翻页层回调函数，
    
    
    return  true;
}


void  UiVIP::setTextPrivilege(Layout * pageLayer, vector<string> str, int  level, int num){     //-====设置层里的文字；(层，文字容器，等级,文字项)
    
    
      //设置文字，标题；
      Text* textPrivilege=static_cast<Text*>(Helper::seekWidgetByName(pageLayer,"textPrivilege"));
      string  str0="VIP"+to_string(level)+"等级特权";
      textPrivilege->setString(str0);
    
      //子项；
      Text* textPrivilege1=static_cast<Text*>(Helper::seekWidgetByName(pageLayer,"textPrivilege1"));
      textPrivilege1->setString(str[0]);
    
     //克隆第一子项，在后面添加子项；
      for (int i=1; i<num; i++) {
         Text* textPrivilege2=static_cast<Text*>(textPrivilege1->clone());
         textPrivilege2->setPositionY(textPrivilege1->getPositionY()-i*(textPrivilege1->getContentSize().height+10));
         textPrivilege2->setString(str[i]);
         pageLayer->addChild(textPrivilege2);                           //这里要加入子节点，不然不显示；
        
      }
    
}

void  UiVIP::pageViewEvent(Ref *pSender, PageView::EventType type )     //翻页层回调函数，设置页面数字；
{
  
     switch (type) {
        case  PageView::EventType::TURNING:
        {
            PageView* pageView = dynamic_cast<PageView*>(pSender);
            
            //数字；
            size_t i=pageView->getCurPageIndex()+1;
            string strPage="  "+to_string(i-1)+"  "+to_string(i)+"  "+to_string(i+1)+"  ";
            Text *  textPage=static_cast<Text*>(Helper::seekWidgetByName(m_pNode,"textPage"));
            
            //底图；
            ImageView *  imagePage=static_cast<ImageView *>(Helper::seekWidgetByName(m_pNode,"imagePage"));
            float  pageX=textPage->getPositionX();
            
            if (i==1) {
                strPage="  "+to_string(i)+"  "+to_string(i+1)+"  "+to_string(i+2)+"  ";
                pageX-=28;
            }
            else if (i==pageView->getChildrenCount()) {
                strPage="  "+to_string(i-2)+"  "+to_string(i-1)+"  "+to_string(i)+"  ";
                pageX+=28;
            }
            else if(i==2){   pageX-=2;   }      //2,9页有偏移，调整一下；
            else if(i==9){   pageX-=5;   }
            
            textPage->setString(strPage);
            imagePage->setPositionX(pageX);
            
           
           
        }
            break;
        default:
            break;
    }
   
    

}






bool  UiVIP::buttonInit(){
    
    Button  *buttonRecharge = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonRecharge"));      //充值按钮；
    if (!buttonRecharge){ log("UiVIP::button====buttonRecharge");return false; }
    buttonRecharge->addTouchEventListener(CC_CALLBACK_2(UiVIP::buttonEvent, this));
    
    
    Button  *buttonLeft = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonLeft"));             //左按钮；
    if (!buttonLeft){log("UiVIP::button====buttonLeft"); return false; }
    buttonLeft->addTouchEventListener(CC_CALLBACK_2(UiVIP::buttonEvent, this));
    
    Button  *buttonRight = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonRight"));           //右按钮；
    if (!buttonRight){ log("UiVIP::button====buttonRight");return false; }
    buttonRight->addTouchEventListener(CC_CALLBACK_2(UiVIP::buttonEvent, this));

    return  true;

}


void  UiVIP::buttonEvent(Ref *pSender, Widget::TouchEventType type)
{

    Button*  button=dynamic_cast<Button*>(pSender);
    string   str=button->getName();
   
    string  str1="buttonRecharge";
    string  str2="buttonLeft";
    string  str3="buttonRight";
    
    
    switch (type)
    {
        case  Widget::TouchEventType::ENDED:
        {
            if (str==str1) {                  //充值按钮；
                Layer * uiRechargeLayer= UiRecharge::create();
                this->getParent()->addChild(uiRechargeLayer);
                CC_SAFE_RETAIN(this);
                this->removeFromParent();
            }
            
            
            else if(str==str2){              //左按钮；
                PageView *pageView=static_cast<PageView*>(Helper::seekWidgetByName(m_pNode,"pageView"));
                if (!pageView){ return ; }
                
                size_t  page=pageView->getCurPageIndex();
                if(page==0){page=pageView->getChildrenCount();}
                pageView->scrollToPage(page-1);
            }
            
            else if (str==str3){            //右按钮；
                
                PageView *pageView=static_cast<PageView*>(Helper::seekWidgetByName(m_pNode,"pageView"));
                if (!pageView){ return ; }
                
                size_t  page=pageView->getCurPageIndex();
                if(page==pageView->getChildrenCount()-1){page=-1;}
                pageView->scrollToPage(page+1);
            }
            
            
        }
            break;
            
        default:      break;
    }
    
    
    
 }
    
    



void UiVIP::onEnter()
{
    Layer::onEnter();
}

void UiVIP::onExit()
{
    Layer::onExit();
}



