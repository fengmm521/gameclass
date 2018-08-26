/**********************************************
签到界面；
 
 **********************************************/

#include "UiSign.h"

using namespace cocos2d::ui;


UiSign::UiSign(){
    
    m_pNode=NULL;
    m_year=2014;
    m_month=11;
    m_day=10;
}
UiSign::~UiSign(){
    m_signed.clear();
}


bool UiSign::init()
{
    if ( !UiBase::init() )  {      return false;    }
    log("UiBase::====init");
    //界面；
    m_pNodeBase->setVisible(false);          //隐藏父类界面；
	m_pNode = GUIReader::getInstance()->widgetFromJsonFile("uiSign.ExportJson");     //  VIPRecharge/UiSign.ExportJson
	this->addChild(m_pNode);

    
    //已经签到的；
    m_signed.clear();
    
//    m_signed.push_back("1");
//    m_signed.push_back("2");
//    m_signed.push_back("3");
//    m_signed.push_back("4");
//    m_signed.push_back("5");
//    m_signed.push_back("6");
//    m_signed.push_back("8");
//    m_signed.push_back("10");
//    m_signed.push_back("12");
//    m_signed.push_back("13");
//    m_signed.push_back("15");
//    m_signed.push_back("16");

   
    

    //日期；
    tm *tm;                //#include"time.h"
    time_t timep;
    time(&timep);
    tm = localtime(&timep);
    m_year=tm->tm_year+1900;
    m_month = tm->tm_mon + 1;
    m_day = tm->tm_mday;
    
   //log("UiBase::===_____________=time_t  yy:%d ,mm:%d,dd:%d ",m_year,m_month,m_day);
    
    //设置月和次数；
    string  strMonth=to_string(m_month)+"月签到奖励";
    string  strTimes=to_string(m_signed.size());
    
    Text  *textName=(Text*)m_pNode->getChildByName("textMonth");
    textName->setString(strMonth);
    
    Text  *textPrice=(Text*)m_pNode->getChildByName("textTimes");
    textPrice->setString(strTimes);
    
    
    //面板；
    int  day;       //天数；
    if(m_month==2){
        if (m_year%4==0) {day=28 ;}
        else {day=29 ;}
       }
    else if(m_month<8){
        if(m_month%2==1){day=31;}
        else{day=30;}
    }
    else if(m_month>=8){
        if(m_month%2==1){day=30;}
        else{day=31;}
    }
    
    setPanel(m_signed,day);  //---面板


    
    //按钮；
    buttonInit();
    
    
    return true;
}


//////////////////////////////////////////////
//面板设置；
void   UiSign::setPanel(vector<string>  itemID, int  itemNum){     //===设置面板; (商品，面板项数)；
    
    //增加精灵项；
    Layout*  panelItem=static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelItem"));
    Point  Pt0=panelItem->getPosition();
    Size  size=panelItem->getContentSize();
    log("UiSign::::panelItem-============+++++++==width:%f,height:%f",size.width,size.height);
    
    for(int  i=0;  i<itemNum; i++){
        Point  pt;
        pt.x=Pt0.x+(i%5)*(size.width+7);
        pt.y=Pt0.y-(int(i/5))*(size.height+2);
        
        Layout *panelItem2=(Layout*)panelItem->clone();
        panelItem2->setVisible(true);
        panelItem2->setPosition(pt);
        

        panelItem->getParent()->addChild(panelItem2,0,to_string(i));         //以日期为名字；
        setItem(panelItem2, itemID  ,i);                                    //------设置里面的项
        

        
    }
    
    panelItem->setVisible(false);                                   //原始项，隐藏，
    
    
}

void UiSign::setItem(Widget *pSender, vector<string>  itemID, int i ){            //======设置里面的项；(项，itemID,id对应的项)
    
    //
    string str1="",          //头像，
    str2="";                 //底框，

    str1="prop/"+Account::sharedAccount()->m_propProperty[  atoi(Account::sharedAccount()->m_prop[i%9].c_str()) ].table.item_icon;
    str2=getQualityFrame1(rand()%8);

    
    //设置项；
    //头像； 设置成随机数了；
    ImageView  *imageHead=(ImageView*)pSender->getChildByName("imageHead");
    imageHead->loadTexture(str1,TextureResType::PLIST);
    
    //按钮；
    Button  *buttonHead=(Button*)pSender->getChildByName("buttonHead");
    buttonHead->setTouchEnabled(false);
    if(i!=m_day-1){ buttonHead->loadTextureNormal(str2,TextureResType::PLIST);}
    else{
        buttonHead->setScale(1);
        buttonHead->loadTextureNormal("ui_c_frame6.png",TextureResType::PLIST);
        buttonHead->setTouchEnabled(true);
        buttonHead->addTouchEventListener(CC_CALLBACK_2(UiSign::buttonEvent,this));
    }
    
    //双倍；
    ImageView  *imageDouble=(ImageView*)pSender->getChildByName("imageDouble");
    imageDouble->setVisible(true);
    
    //已签；
    ImageView  *imageSigned=(ImageView*)pSender->getChildByName("imageSigned");
    imageSigned->setVisible(false);
    
    for(string  strSi:itemID){           //标记为已签；
        if(atoi(strSi.c_str())==i+1){
            imageSigned->setVisible(true);
        
        }
    }
    
    
    
    
}



///////////////////////////////////////////////
///////按钮
bool  UiSign::buttonInit(){
    
    
    
    Button  *buttonClose = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonClose"));           //关闭按钮；
    if (!buttonClose){ return false; }
    buttonClose->addTouchEventListener(CC_CALLBACK_2(UiSign::buttonEvent, this));
    
 
    return  true;

}


void  UiSign::buttonEvent(Ref *pSender, Widget::TouchEventType type)             //按钮响应函数；
{
    Button*  button=dynamic_cast<Button*>(pSender);
    string   str=button->getName();
    string   strParent=button->getParent()->getName();
    //log("UiSign::button-============+++++++==: %s,",strParent.c_str());
    
    string  str1="buttonClose";     //关闭按钮；
    string  str2=to_string(m_day-1);   //签到按钮；
    //log("UiSign::button-============+++++++==: %s,",str2.c_str());
    
    switch (type)
    {
        case  Widget::TouchEventType::ENDED:
        {
            if (str==str1) {                  //关闭按钮；
                
                CC_SAFE_RETAIN(this);
                this->removeFromParent();
                
            }
            if (strParent==str2) {                  //签到按钮；
                //标记
                ImageView  *imageSigned=(ImageView*)button->getParent()->getChildByName("imageSigned");
                imageSigned->setVisible(true);
                button->setTouchEnabled(false);
                
                //修改签到次数；
                m_signed.push_back(str2);
                Text  *textPrice=(Text*)m_pNode->getChildByName("textTimes");
                textPrice->setString(to_string(m_signed.size()));
            }
            
        }
            break;
            
        default:      break;
    }
 
}




void UiSign::onEnter()
{
    Layer::onEnter();
}

void UiSign::onExit()
{
    Layer::onExit();
}



