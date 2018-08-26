/**********************************************
酒馆界面；
 
 **********************************************/

#include "UiTavern.h"

using namespace cocos2d::ui;

UiTavern::UiTavern(){
    m_panelItem1=nullptr;      //3个面板；
    m_panelItem2=nullptr;
    m_panelItem3=nullptr;

}


UiTavern::~UiTavern(){
    m_panelItem.clear();
    m_goods.clear();
}



bool UiTavern::init()
{
    if ( !UiBase::init() )  {      return false;    }
     log("UiTavern::====init");
    
    //界面；
    m_pNode = GUIReader::getInstance()->widgetFromJsonFile("uiTavern.ExportJson");
    m_pNodeBase->addChild(m_pNode);
    m_pNodeBase->getChildByName("imageBK0")->setVisible(false);
    m_pNode->setTouchEnabled(false);        //不然父类的按钮没用；
    
    //
    m_goods.clear();
    m_goods.push_back("100001");
    m_goods.push_back("100002");
    m_goods.push_back("100003");
    m_goods.push_back("100004");
    m_goods.push_back("100005");
    m_goods.push_back("100006");
    m_goods.push_back("100007");


    //3个面板；
    m_panelItem1=static_cast<Layout*>(ui::Helper::seekWidgetByName(m_pNode,"panelItem1"));
    m_panelItem2=static_cast<Layout*>(ui::Helper::seekWidgetByName(m_pNode,"panelItem2"));
    m_panelItem3=static_cast<Layout*>(ui::Helper::seekWidgetByName(m_pNode,"panelItem3"));
    initPanelItem1();
    initPanelItem2();
    initPanelItem3();
    
    
    //刷新时间；
     Text*  textFlush=static_cast<Text*>(ui::Helper::seekWidgetByName(m_pNode,"textFlush"));
     textFlush->setString("下次刷新时间：18:00");
    
    
    //按钮；
    buttonInit();
    
    
    return true;
}

////////////////////////////////////////
////////////////////////////////////////
//3个面板；
void UiTavern::initPanelItem1(){        //===面板1;
    //设置项；
    
//    ImageView  *imageHead=(ImageView*)pSender->getChildByName("imageHead");
//    if(type==1){  imageHead->setScale(0.9);  }
//    imageHead->loadTexture(str1,TextureResType::PLIST);
//    
//    Button  *buttonHead=(Button*)pSender->getChildByName("buttonHead");
//    buttonHead->loadTextureNormal(str2,TextureResType::PLIST);
    string str3="剩余:3/5";
    Text  *textName=(Text*)m_panelItem1->getChildByName("textTimes");
    textName->setString(str3);
    
    string str4="6000";
    Text  *textGold1=(Text*)m_panelItem1->getChildByName("textGold1");
    textGold1->setString(str4);
    
    string str5="50000";
    Text  *textGold2=(Text*)m_panelItem1->getChildByName("textGold2");
    textGold2->setString(str5);
    

}


void UiTavern::initPanelItem2(){    //===面板2;

    string str3="10:35:20后免费";
    Text  *textName=(Text*)m_panelItem2->getChildByName("textTime");
    textName->setString(str3);
    
    string str4="12000";
    Text  *textGold1=(Text*)m_panelItem2->getChildByName("textGold1");
    textGold1->setString(str4);
    
    string str5="100000";
    Text  *textGold2=(Text*)m_panelItem2->getChildByName("textGold2");
    textGold2->setString(str5);
    
    
    
}


void UiTavern::initPanelItem3(){            //===面板3;

    string str5="50000";
    Text  *textGold2=(Text*)m_panelItem3->getChildByName("textGold2");
    textGold2->setString(str5);
    
    
    //
    Layout*  panelItem=(Layout*)m_panelItem3->getChildByName("panelItem");
    Point  Pt0=panelItem->getPosition();
    Size  size=panelItem->getContentSize();
    //log("UiArena::panelItem-============+++++++==width:%f,height:%f",size.width,size.height);
    
    m_panelItem.clear();
    
    for(int  i=0;  i<6; i++){
        Point  pt;
        pt.x=Pt0.x+(i%3)*(size.width+6);
        pt.y=Pt0.y-(int(i/3))*(size.height+8);
        
        
        Layout *panelItem2=(Layout*)panelItem->clone();
        panelItem2->setVisible(true);
        panelItem2->setPosition(pt);
        
        m_panelItem.push_back(panelItem2);
        panelItem->getParent()->addChild(panelItem2);
        
    }
    
    panelItem->setVisible(false);                       //原始项，隐藏，
    setPanelItem(m_panelItem, m_goods);                  //-----设置项;
    
    

}





void UiTavern::setPanelItem( vector<Layout*>  panelItem, vector<string>  camp)//======设置项；
{
    int n=(int)panelItem.size();
    if (n>6) { log("error !panelItem  must  be  6;");  }
    
    for(int i=0;i<n; i++){
        
        Layout *panelItem2=panelItem[i];
        
        if (i<camp.size()) {
            
            panelItem2->setName(camp[i]);
            //设置项；
            string str1="prop/"+Account::sharedAccount()->m_propProperty[  atoi(camp[random()%7].c_str()) ].table.item_icon;
            string str2=getQualityFrame1( i%8 );
            //string str3="LV88";
            
            ImageView  *imageHead=static_cast<ImageView*>(Helper::seekWidgetByName(panelItem2,"imageHead"));
            imageHead->loadTexture(str1,TextureResType::PLIST);
            
            Button  *buttonHead=static_cast<Button*>(Helper::seekWidgetByName(panelItem2,"buttonHead"));
            //buttonHead->loadTextureNormal(str2,TextureResType::PLIST);
            
 
            
        }
        else{                                                         //少于6个时为空；
            panelItem2->setName(to_string(i));;                        //以号为名字；
            
            //设置项；
            string str2=getQualityFrame1( i%8 );
            
            ImageView  *imageHead=static_cast<ImageView*>(Helper::seekWidgetByName(panelItem2,"imageHead"));
            imageHead->loadTexture(str2,TextureResType::PLIST);      //设置成一个框；
            
            Button  *buttonHead=static_cast<Button*>(Helper::seekWidgetByName(panelItem2,"buttonHead"));
            //buttonHead->loadTextureNormal(str2,TextureResType::PLIST);
            

            
        }
        
    }
    
    
}






////////////////////////////////////////
////////////////////////////////////////
//按钮


bool  UiTavern::buttonInit(){
    
    
    
    Button  *buttonFlush = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonFlush"));         //刷新；
    
    buttonFlush->addTouchEventListener(CC_CALLBACK_2(UiTavern::buttonEvent, this));
    
    //第一组；
   
    Button  *buttonBuy1 = static_cast<Button*>(Helper::seekWidgetByName(m_panelItem1, "buttonBuy1"));             //买1按钮；
    buttonBuy1->addTouchEventListener(CC_CALLBACK_2(UiTavern::buttonEvent, this));
    
    Button  *buttonBuy10 = static_cast<Button*>(Helper::seekWidgetByName(m_panelItem1, "buttonBuy10"));           //买10按钮；
    buttonBuy10->addTouchEventListener(CC_CALLBACK_2(UiTavern::buttonEvent, this));
    
    //第二组；

    Button  *buttonBuy1b = static_cast<Button*>(Helper::seekWidgetByName(m_panelItem2, "buttonBuy1"));             //买1按钮；
    buttonBuy1b->addTouchEventListener(CC_CALLBACK_2(UiTavern::buttonEvent, this));
    
    Button  *buttonBuy10b = static_cast<Button*>(Helper::seekWidgetByName(m_panelItem2, "buttonBuy10"));           //买10按钮；
    buttonBuy10b->addTouchEventListener(CC_CALLBACK_2(UiTavern::buttonEvent, this));
    
    //第三组；
    Button  *buttonBuy10c = static_cast<Button*>(Helper::seekWidgetByName(m_panelItem3, "buttonBuy10"));           //买10按钮；
    buttonBuy10c->addTouchEventListener(CC_CALLBACK_2(UiTavern::buttonEvent, this));
    
    return  true;

}


void  UiTavern::buttonEvent(Ref *pSender, Widget::TouchEventType type)             //按钮响应函数；
{
    
    Button*  button=dynamic_cast<Button*>(pSender);
    string  str=button->getName();
    string  str0=button->getParent()->getName();
    
    string  str1="buttonFlush";
    string  str2="";
    
    string  str3="buttonBuy1";
    string  str4="buttonBuy10";
    
    string  str5="panelItem1";
    string  str6="panelItem2";
    string  str7="panelItem3";
 

    switch (type)
    {
        case  Widget::TouchEventType::ENDED:
        {
         
                if (str==str1) {            //刷新；
                    MessageBox("刷新", "刷新");
                }
                
                else if (str==str2){
                    
            
                }
                //
                else if (str==str3&&str0==str5){        //1买1按钮；
                    MessageBox("1买1", "购买");
                }
                else if (str==str4&&str0==str5){        //1买10按钮；
                    
                    MessageBox("1买10", "购买");
                }
                //
                else if (str==str3&&str0==str6){        //2买1按钮；
                    
                    MessageBox("2买1", "购买");
                }
            
                else if (str==str4&&str0==str6){        //2买10按钮；
                    MessageBox("2买10", "购买");
                }
            
                //
                else if (str==str4&&str0==str7){        //3买10按钮；
                    MessageBox("3买10", "购买");
                    
                }
           
        }
            break;
            
        default:   break;
    }
    
    
 
    
}




void UiTavern::onEnter()
{
    Layer::onEnter();
}

void UiTavern::onExit()
{
    Layer::onExit();
}




