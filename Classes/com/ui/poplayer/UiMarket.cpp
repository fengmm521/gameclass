/**********************************************
市场界面；
 
 **********************************************/

#include "UiMarket.h"

using namespace cocos2d::ui;


bool UiMarket::init()
{
    if ( !UiBase::init() )  {      return false;    }
    log("UiMarket::====init");
    
    //界面；
	m_pNode = GUIReader::getInstance()->widgetFromJsonFile("uiMarket.ExportJson");     //  VIPRecharge/UiMarket.ExportJson
	m_pNodeBase->getChildByName("imageBK0")->setVisible(false);
    m_pNodeBase->addChild(m_pNode);
    m_pNode->setTouchEnabled(false);
    
    //刷新时间；
    Text*   textFlush=static_cast<Text*>(Helper::seekWidgetByName(m_pNode, "textFlush"));
    string flushTime="18:00";
    string  strFlush="下次刷新时间："+flushTime;
    textFlush->setString(strFlush);
    
    //商品ID;
    m_goods.clear();
    m_goods.push_back("1001");
    m_goods.push_back("1002");
    m_goods.push_back("1003");
    m_goods.push_back("1004");
    m_goods.push_back("300001");
    m_goods.push_back("300010");
    m_goods.push_back("300019");
    m_goods.push_back("300028");
    m_goods.push_back("100001");
    m_goods.push_back("100002");
    m_goods.push_back("100003");
    m_goods.push_back("100004");
    
    //面板；
    setPanel(m_goods,9);
    
    
    
    //按钮；
    buttonInit();
    
    
    return true;
}




//////////////////////////////////////////////
//面板设置；
void   UiMarket::setPanel(vector<string>  itemID, int  itemNum){     //===设置面板; (商品，面板项数)；
    
    //增加精灵项；
    //Layout*  panelItem3=(Layout*)pWidget->getChildByName("panelMaterial");
    
    Layout*  panelItem=static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelItem"));
    Point  Pt0=panelItem->getPosition();
    Size  size=panelItem->getContentSize();
    log("UiMarket::panelItem-============+++++++==width:%f,height:%f",size.width,size.height);
    
    if(m_panelItem.size()>0){
        for(Layout *panelItem:m_panelItem){
            panelItem->removeFromParent();
        }
        m_panelItem.clear();
    }
    
    for(int  i=0;  i<itemNum; i++){
        Point  pt;
        pt.x=Pt0.x+(i%3)*(size.width+12);
        pt.y=Pt0.y-(int(i/3))*(size.height+12);
        
        Layout *panelItem2=(Layout*)panelItem->clone();
        panelItem2->setVisible(true);
        panelItem2->setPosition(pt);
        
        int n=rand()%(itemID.size());
        
        m_panelItem.push_back(panelItem2);                       //项集；不让重复创建；
        panelItem->getParent()->addChild(panelItem2,0,itemID[n]);         //以ID号为名字；
        setItem(panelItem2, itemID  ,n);  //------设置里面的项
        
        
        log("UiMarket::panelItem-============%s",itemID[n].c_str());
        
    }
    
    panelItem->setVisible(false);                                   //原始项，隐藏，

    
}

void UiMarket::setItem(Widget *pSender, vector<string>  itemID, int n ){            //======设置里面的项；(项，itemID,id对应的项)
    
    string str1="",          //头像，
          str2="",          //底框，
          str3="",          //名字，
          str4="1000";      //价格，
    
    //id类型；
    int  type=getGoodsType(itemID[n]);  //1英雄，2技能， 3装备，4材料；
    switch (type) {
        case 0:
            
            break;
        case 1:
        {
            str1="hero/"+Account::sharedAccount()->m_heroProperty[  atoi(itemID[n].c_str()) ].table.hero_icon;
            str2=getQualityFrame1(n%8);
            str3=Account::sharedAccount()->m_heroProperty[  atoi(itemID[n].c_str()) ].table.hero_name;
            str4="8000";
        }
            break;
            
        case 2:
        {
       
        }
            break;
        case 3:
        {
            str1="equip/"+Account::sharedAccount()->m_equipProperty[  atoi(itemID[n].c_str()) ].table.equip_icon;
            str2=getQualityFrame1(n%8);
            str3=Account::sharedAccount()->m_equipProperty[  atoi(itemID[n].c_str()) ].table.equip_name;
            str4="5000";
        }
            break;
        case 4:
        {
            str1="prop/"+Account::sharedAccount()->m_propProperty[  atoi(itemID[n].c_str()) ].table.item_icon;
            str2=getQualityFrame1(n%8);
            str3=Account::sharedAccount()->m_propProperty[  atoi(itemID[n].c_str()) ].table.item_name;
            str4="3000";
        }
            break;
            
        default:
            break;
    }

    //设置项；
    
    ImageView  *imageHead=(ImageView*)pSender->getChildByName("imageHead");
    if(type==1){  imageHead->setScale(0.9);  }
    imageHead->loadTexture(str1,TextureResType::PLIST);
    
    Button  *buttonHead=(Button*)pSender->getChildByName("buttonHead");
    buttonHead->loadTextureNormal(str2,TextureResType::PLIST);
    
    Text  *textName=(Text*)pSender->getChildByName("textName");
    textName->setString(str3);
    
    Text  *textPrice=(Text*)pSender->getChildByName("textPrice");
    textPrice->setString(str4);
 
    
    
}






///////////////////////////////////////////////
///////按钮

bool  UiMarket::buttonInit(){
    
    Button  *buttonRecharge = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonFlush"));         //刷新按钮；
    if (!buttonRecharge){ log("UiMarket::button====buttonFlush get error");return false; }
    buttonRecharge->addTouchEventListener(CC_CALLBACK_2(UiMarket::buttonEvent, this));
    
    return  true;
    
}


void  UiMarket::buttonEvent(Ref *pSender, Widget::TouchEventType type)             //按钮响应函数；
{
    
    Button*  button=dynamic_cast<Button*>(pSender);
    string   str=button->getName();
    
    string  str1="buttonFlush";
    
    switch (type)
    {
        case  Widget::TouchEventType::ENDED:
        {
            if (str==str1) {                  //刷新按钮；
                
                //CC_SAFE_RETAIN(this);
                //this->removeFromParent();

                //init();
                setPanel(m_goods,9);
                //MessageBox("刷新", "刷新");
                
            }
            
            
        }
            break;
            
        default:      break;
    }
}



void UiMarket::onEnter()
{
    Layer::onEnter();
}

void UiMarket::onExit()
{
    Layer::onExit();
    m_goods.clear();
    m_panelItem.clear();
}



