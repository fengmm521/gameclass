/**********************************************
邮箱界面；
 
 **********************************************/

#include "UiEmail.h"

using namespace cocos2d::ui;

#include "MD5.h"
#include<iostream>
#include<string>

UiEmail::UiEmail(){
    m_percent=15;
    m_prePress=0;
    m_listView=NULL;
    m_slider=NULL;
    
}

UiEmail::~UiEmail(){}



bool UiEmail::init()
{
    if ( !UiBase::init() )  {      return false;    }
    
    //界面；
    m_pNode = GUIReader::getInstance()->widgetFromJsonFile("uiEmail.ExportJson");     //  VIPRecharge/UiEmail.ExportJson
    m_pNodeBase->addChild(m_pNode);
    m_pNode->setTouchEnabled(false);
    
    
    
    //账号；
    //Account::sharedAccount();
    
    
    //滑块；
    m_slider=static_cast<Slider*>(Helper::seekWidgetByName(m_pNode,"slider"));
    m_slider->addEventListener(CC_CALLBACK_2(UiEmail::sliderEvent, this));
    m_slider->setVisible(true);
    
    //列表框
    m_listView = static_cast<ui::ListView*>(Helper::seekWidgetByName(m_pNode, "listView"));
    m_listView->addEventListener(CC_CALLBACK_2(UiEmail::scrollViewEvent, this));
    m_listView->addEventListener(CC_CALLBACK_2(UiEmail::listViewEvent, this));
    setListView();
    

    
    //按钮；
    buttonInit();
    
    
    
    
    
    
    return true;
}






//////////////////////////////////////////////
//列表框设置；
void   UiEmail::setListView(){
    
    //原有项；
    Layout*  panelItem=static_cast<Layout*>(Helper::seekWidgetByName(m_listView, "panelItem"));
    
    //
    int count=5;//(int)Account::sharedAccount()->m_equip.size();
    if(count<7){   m_slider->setVisible(false);  }
    for (int i=0; i<count; i++) {
        Layout*  panelItem2=(Layout*)panelItem->clone();
        panelItem2->setName(Account::sharedAccount()->m_equip[i].c_str());
        
        //
        setItem(panelItem2,i);      //------设置里面的项
        
        //
        m_listView->insertCustomItem(panelItem2, i+1);
    }
    
    m_listView->removeItem(0);
    
    
}

void UiEmail::setItem(Widget *pSender,  int n ){            //======设置里面的项；
    //头像；
    string str2="hero/"+Account::sharedAccount()->m_heroProperty[atoi(Account::sharedAccount()->m_hero[n].c_str())].table.hero_icon;
    ImageView  *imageHead=(ImageView*)pSender->getChildByName("imageHead");
    imageHead->loadTexture(str2,TextureResType::PLIST);
    
    
    Button*   button1=(Button*)pSender->getChildByName("buttonOpen");
    button1->addTouchEventListener(CC_CALLBACK_2(UiEmail::buttonEvent, this));
    
    
    //       string str2="equip/"+Account::sharedAccount()->m_equipProperty[atoi(Account::sharedAccount()->m_equip[i].c_str())].table.equip_icon; //账号-装备ID-表结构体-图片；
    //        string str3=Account::sharedAccount()->m_equipProperty[atoi(Account::sharedAccount()->m_equip[i].c_str())].table.equip_name;
    //        string str4=to_string(Account::sharedAccount()->m_equipProperty[atoi(Account::sharedAccount()->m_equip[i].c_str())].table.equip_apparel_level)+"级";
    //
    
    //
    //        Text*  textName=(Text*)panelItem2->getChildByName("textName");
    //        textName->setString(str3);
    //
    //        Text*  textLevel=(Text*)panelItem2->getChildByName("textLevel");
    //        textLevel->setString(str4);
    
    
    
    
}





void  UiEmail::setPanelItemShow(ssize_t index){   //选中；
    
    
    
    Layer*   panelItem=(Layer*)m_listView->getItem(index);
    Button*  buttonItem=(Button*)panelItem->getChildByName("buttonItem");
    buttonItem->loadTextureNormal("ui_renwu_03.png",TextureResType::PLIST);
    buttonItem->loadTexturePressed("ui_renwu_04.png",TextureResType::PLIST);
    
    
}


void  UiEmail::setPanelItemHide(){   //先前选中的；
    
    Layer*   panelItem=(Layer*)m_listView->getItem(m_prePress);
    Button*  buttonItem=(Button*)panelItem->getChildByName("buttonItem");
    buttonItem->loadTextureNormal("ui_renwu_04.png",TextureResType::PLIST);
    buttonItem->loadTexturePressed("ui_renwu_03.png",TextureResType::PLIST);
    
    
}






////////////////////////////////////
//控件响应事件；


void  UiEmail::sliderEvent(Ref *pSender, Slider::EventType type){    //滑块响应函数，控制滚动层；
    
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


void  UiEmail::scrollViewEvent(Ref *pSender, ui::ScrollView::EventType type){   //====列表层调用滚动层响应函数，控制滑块；；
    
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

void  UiEmail::listViewEvent(Ref *pSender, ui::ListView::EventType type){   //====列表层第二个响应函数；
    
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

bool  UiEmail::buttonInit(){
    
//    Button  *buttonRecharge = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonVIP"));         //VIP按钮；
//    if (!buttonRecharge){ log("UiEmail::button====buttonVIP");return false; }
//    buttonRecharge->addTouchEventListener(CC_CALLBACK_2(UiEmail::buttonEvent, this));
    
    return  true;
    
}


void  UiEmail::buttonEvent(Ref *pSender, Widget::TouchEventType type)             //按钮响应函数；
{
    
    Button*  button=dynamic_cast<Button*>(pSender);
    string   str=button->getName();
    
    string  str1="buttonOpen";
    
    switch (type)
    {
        case  Widget::TouchEventType::ENDED:
        {
            if (str==str1) {                  //打开按钮；
                
                string strmessage="打开"+to_string(m_listView->getCurSelectedIndex());      //n对应着m_equip;
                
                MessageBox(strmessage.c_str(), "打开");
            
            }
            
            
        }
            break;
            
        default:      break;
    }
}




void UiEmail::onEnter()
{
    Layer::onEnter();
}

void UiEmail::onExit()
{
    Layer::onExit();
}





