/**********************************************
充值界面；
 
 
 **********************************************/

#include "UiRecharge.h"

using namespace cocos2d::ui;

UiRecharge::UiRecharge(){
    m_percent=15;
    m_prePress=0;
    m_listView=NULL;
    m_slider=NULL;
}

UiRecharge::~UiRecharge(){}



bool UiRecharge::init()
{
    if ( !UiBase::init() )  {      return false;    }

    //界面；
	m_pNode = GUIReader::getInstance()->widgetFromJsonFile("uiRecharge.ExportJson");     //  VIPRecharge/uiRecharge.ExportJson
	m_pNodeBase->getChildByName("imageBK0")->setVisible(false);
    m_pNodeBase->addChild(m_pNode);
	m_pNode->setTouchEnabled(false);
    

     //账号；
    //Account::sharedAccount();

    //进度条；
    progressInit();

    //滑块；
    m_slider=static_cast<Slider*>(Helper::seekWidgetByName(m_pNode,"slider"));
    m_slider->addEventListener(CC_CALLBACK_2(UiRecharge::sliderEvent, this));
    m_slider->setVisible(true);
    
    //列表框
    m_listView = static_cast<ui::ListView*>(Helper::seekWidgetByName(m_pNode, "listView"));
    m_listView->addEventListener(CC_CALLBACK_2(UiRecharge::scrollViewEvent, this));
    m_listView->addEventListener(CC_CALLBACK_2(UiRecharge::listViewEvent, this));
    setListView();
    

    
    //按钮；
    buttonInit();
    

    
    return true;
}



//////////////////////////////////////////////
//进度条
void  UiRecharge::progressInit(){                    //进度条，以及上下的图片，文字；
    
    //VIP
    ImageView* imageVIPLevel=static_cast<ImageView*>(Helper::seekWidgetByName(m_pNode,"imageVIPLevel"));
    imageVIPLevel->loadTexture("ui_chongzhi_11.png",TextureResType::PLIST);                                // PLIST：从PLIST文件中；LOCAL：从单独的PNG文件中；
    
    //再充值
    Text* textOwe=static_cast<Text*>(Helper::seekWidgetByName(m_pNode,"textOwe"));
    textOwe->setString("再充值100元即可以成为VIP2");
   
    //进度条；
    LoadingBar* progressRecharge=static_cast<LoadingBar*>(Helper::seekWidgetByName(m_pNode,"progressRecharge"));
    progressRecharge->setPercent(30);
    
    Text* textProgress =static_cast<Text*>(Helper::seekWidgetByName(m_pNode,"textProgress"));
    textProgress->setString("30/100");

}





//////////////////////////////////////////////
//列表框设置；
void   UiRecharge::setListView(){
    
    //原有项；
    Layout*  panelItem=static_cast<Layout*>(Helper::seekWidgetByName(m_listView, "panelItem"));

    //
    int count=12;//(int)Account::sharedAccount()->m_equip.size();
    if(count<5){  m_slider->setVisible(false);   }
    for (int i=0; i<count; i++) {
        Layout*  panelItem2=(Layout*)panelItem->clone();
        panelItem2->setName(Account::sharedAccount()->m_prop[i].c_str());
        //设置项
        setItem(panelItem2,i);   //--设置里面的项；
        
        //
        
        //
        m_listView->insertCustomItem(panelItem2, i+1);
    }
    
    m_listView->removeItem(0);
    
    
}

void UiRecharge::setItem(Widget *pSender,  int n ){            //======设置里面的项；
        //头像；
        string str2="prop/"+Account::sharedAccount()->m_propProperty[atoi(Account::sharedAccount()->m_prop[n].c_str())].table.item_icon;
        ImageView  *imageHead=(ImageView*)pSender->getChildByName("imageHead");
        imageHead->loadTexture(str2,TextureResType::PLIST);
        
    
    
    
    

}





void  UiRecharge::setPanelItemShow(ssize_t index){   //选中；
    
   
    
    Layer*   panelItem=(Layer*)m_listView->getItem(index);
    Button*  buttonItem=(Button*)panelItem->getChildByName("buttonItem");
    buttonItem->loadTextureNormal("ui_renwu_03.png",TextureResType::PLIST);
    buttonItem->loadTexturePressed("ui_renwu_04.png",TextureResType::PLIST);
    
    
}


void  UiRecharge::setPanelItemHide(){   //先前选中的；
    
    Layer*   panelItem=(Layer*)m_listView->getItem(m_prePress);
    Button*  buttonItem=(Button*)panelItem->getChildByName("buttonItem");
    buttonItem->loadTextureNormal("ui_renwu_04.png",TextureResType::PLIST);
    buttonItem->loadTexturePressed("ui_renwu_03.png",TextureResType::PLIST);
    
    
}






////////////////////////////////////
//控件响应事件；


void  UiRecharge::sliderEvent(Ref *pSender, Slider::EventType type){    //滑块响应函数，控制滚动层；
    
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        
        Slider* slider = dynamic_cast<Slider*>(pSender);    //滑块在15到85之间滑动；
        int percent = slider->getPercent();
        if (percent<14) {  percent=14;slider->setPercent(14);}
        if (percent>86) { percent=86;slider->setPercent(86);}
        percent =percent-15;
        //m_percent=percent;
        percent=percent*100/70;
        
        ui::ListView* scrollViewHero=static_cast<ui::ListView*>(Helper::seekWidgetByName(m_pNode,"listView"));
        scrollViewHero->scrollToPercentVertical(percent, 0.2, true);
        //m_listView->scrollToPercentVertical(percent, 0.2, true);
    }
    
}


void  UiRecharge::scrollViewEvent(Ref *pSender, ui::ScrollView::EventType type){   //====列表层调用滚动层响应函数，控制滑块；；
    
    ui::ListView* scrollViewHero=static_cast<ui::ListView*>(pSender);
    if(!scrollViewHero){log("ScrollView  is  NULL"); return;}
    
    Slider  *slider=static_cast<Slider*>(Helper::seekWidgetByName(m_pNode,"slider"));
    if(!slider){log("Slider  is  NULL"); return;}
    
    //int  percent=slider->getPercent();
    if (m_percent<15) {  m_percent=15;slider->setPercent(15);}
    if (m_percent>85) { m_percent=85;slider->setPercent(85);}
    
    
    switch (type) {
        case ui::ScrollView::EventType::SCROLLING:        //滚动过程中有好多次响应；
        {
            Point  pt=scrollViewHero->getInnerContainer()->getPosition();
            Size  size=scrollViewHero->getInnerContainer()->getContentSize();
            
            float  percentScroll=(size.height+pt.y)/size.height*70;
            slider->setPercent(percentScroll);
            log("percentScroll ====+++++++++++++++++++++++=%f",percentScroll);
            log("scrollViewHero pt =====%f,y====%f",pt.x, pt.y);
            
            
        }
            break;
            
        case ui::ScrollView::EventType::SCROLL_TO_TOP:     //到达顶点，只是一次响应；
        {
            log("slider  top =====d");
            
            slider->setPercent(14);
        }
            break;
            
        case ui::ScrollView::EventType::SCROLL_TO_BOTTOM:    //到达底点；
        {
            slider->setPercent(86);
            
            log("slider bottom =====d");
        }
            break;
            
            
            
            
        default:
            break;
    }
    
    
}

void  UiRecharge::listViewEvent(Ref *pSender, ui::ListView::EventType type){   //====列表层第二个响应函数；
    
    ui::ListView* listView=static_cast<ui::ListView*>(pSender);
    if(!listView){log("ScrollView  is  NULL"); return;}
    
    
    switch (type) {
        case ui::ListView::EventType::ON_SELECTED_ITEM_END :    //点；
        {
            ssize_t  n=listView->getCurSelectedIndex();      //n对应着m_equip;
            
            setPanelItemShow(n);                           // 显示底；
            if(n!=m_prePress){  setPanelItemHide();  }     //隐藏前一项的底；
            
            m_prePress=n;                                 //前一项的索引；
            
            
            
            log("ON_SELECTED_ITEM_START =====%d",(int)n);
        }
            break;
            
            
            
            
        default:
            break;
    }
    
}









///////////////////////////////////////////////
///////按钮

bool  UiRecharge::buttonInit(){
    
    Button  *buttonRecharge = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonVIP"));         //VIP按钮；
    if (!buttonRecharge){ log("UiRecharge::button====buttonVIP");return false; }
    buttonRecharge->addTouchEventListener(CC_CALLBACK_2(UiRecharge::buttonEvent, this));

    return  true;

}


void  UiRecharge::buttonEvent(Ref *pSender, Widget::TouchEventType type)             //按钮响应函数；
{

    Button*  button=dynamic_cast<Button*>(pSender);
    string   str=button->getName();
    
    string  str1="buttonVIP";

    switch (type)
    {
        case  Widget::TouchEventType::ENDED:
        {
            if (str==str1) {                  //VIP按钮；
                Layer * uiVIPLayer= UiVIP::create();
                this->getParent()->addChild(uiVIPLayer);
                CC_SAFE_RETAIN(this);
                this->removeFromParent();
            }
     
            
        }
            break;
            
        default:      break;
    }
}
    
    





void UiRecharge::onEnter()
{
    Layer::onEnter();
}

void UiRecharge::onExit()
{
    Layer::onExit();
}







