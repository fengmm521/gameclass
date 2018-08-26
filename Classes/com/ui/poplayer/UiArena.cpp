/**********************************************
竞技场界面；
 
 **********************************************/

#include "UiArena.h"

using namespace cocos2d::ui;

UiArena::UiArena(){

    m_panelExchangepa=NULL;    //兑换面板；
    m_panelArena=NULL;         //竞技面板；
    m_buttonExchange=NULL;     //兑换按钮
    m_buttonArena=NULL;        //竞技按钮
    m_time=80;
    

}

UiArena::~UiArena(){
    
    m_goods.clear();              //商品ID;
    
    m_panelItem.clear();        //5个阵容英雄；
    m_camp.clear();             //自己的阵容；
    m_panelHero.clear();       //3个对手；
    m_adversary.clear();       //对手；



}


bool UiArena::init()
{
    if ( !UiBase::init() )  {      return false;    }
    //if ( !SocketReciveDelegate::init() )  {      return false;    }
    log("UiArena::====init");
    

    
    
    
    
    
    //界面；
    m_pNode = GUIReader::getInstance()->widgetFromJsonFile("uiArena.ExportJson");
    m_pNodeBase->addChild(m_pNode);
    m_pNodeBase->getChildByName("imageBK0")->setVisible(false);
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
   
    
    
    ////对手；
    m_adversary.clear();
    adversaryST  adversary1;
    m_adversary.push_back(adversary1);
    
    adversaryST  adversary2;
    adversary2.id="1002";
    adversary2.name="羽飞";
    adversary2.sword="战斗力:13000";
    adversary2.ranking="排名:1802";
    m_adversary.push_back(adversary2);
    
    adversaryST  adversary3;
    adversary3.id="1003";
    adversary3.name="百无估柳";
    adversary3.sword="战斗力:18600";
    adversary3.ranking="排名:1202";
    m_adversary.push_back(adversary3);

    
    //自己的阵容；
    m_camp.clear();
    m_camp=Account::sharedAccount()->m_campST.m_arenaCamp;
  
    
    //面板；
    m_panelArena=static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelArena"));
    setPanelArena();
    
    m_panelExchangepa=static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelExchange"));
    setPanel(m_panelExchangepa,m_goods,9);
    
    
    schedule(schedule_selector(UiArena::timeCallback),1);
    
    //按钮；
    buttonInit();
    buttonPress(m_buttonArena);     //默认按钮；
    
    return true;
}




//////////////////////////////////////////////
//竞技面板；
void UiArena::setPanelArena()    //设置面板; (商品，面板项数)；
{
    //按钮
    Button  *buttonCamp=(Button*) m_panelArena->getChildByName( "buttonCamp");                 //阵容按钮；
    buttonCamp->addTouchEventListener(CC_CALLBACK_2(UiArena::buttonEvent, this));
    Button  *buttonAward=(Button*) m_panelArena->getChildByName("buttonAward");               //奖励按钮；
    buttonAward->addTouchEventListener(CC_CALLBACK_2(UiArena::buttonEvent, this));
    Button  *buttonRanking=(Button*) m_panelArena->getChildByName("buttonRanking");           //排行按钮；
    buttonRanking->addTouchEventListener(CC_CALLBACK_2(UiArena::buttonEvent, this));
    Button  *buttonRecord=(Button*) m_panelArena->getChildByName("buttonRecord");             //记录按钮；
    buttonRecord->addTouchEventListener(CC_CALLBACK_2(UiArena::buttonEvent, this));
    Button  *buttonFlush2=(Button*) m_panelArena->getChildByName("buttonFlush2");             //刷新按钮；
    buttonFlush2->addTouchEventListener(CC_CALLBACK_2(UiArena::buttonEvent, this));
    
    //
    string  str1=Account::sharedAccount()->m_accountST.level+"级";
    string  str2=Account::sharedAccount()->m_accountST.ranking;
    string  str3="12000";
    string  str4="2/5";
    string  str5=to_string(m_time);
    
    Text  *text1=(Text*) m_panelArena->getChildByName("text1");             //级别；
    text1->setString(str1);
    Text  *text2=(Text*) m_panelArena->getChildByName("text2");             //排行；
    text2->setString(str2);
    Text  *text3=(Text*) m_panelArena->getChildByName("text3");             //战力；
    text3->setString(str3);
    Text  *text4=(Text*) m_panelArena->getChildByName("text4");             //次数；
    text4->setString(str4);
    Text  *text5=(Text*) m_panelArena->getChildByName("text5");             //时间；
    text5->setString(str5);
    
    //
    initPanelHero(m_panelArena,m_adversary);   //对手；
    
    initPanelItem(m_panelArena, m_camp);    //初始化阵容的英雄；
    
}




void UiArena::initPanelItem(Widget *pSender, vector<string>  itemID) //======设置自己的英雄；
{
    Layout*  panelItem=(Layout*)pSender->getChildByName("panelItem");
    Point  Pt0=panelItem->getPosition();
    Size  size=panelItem->getContentSize();
    //log("UiArena::panelItem-============+++++++==width:%f,height:%f",size.width,size.height);
    
    m_panelItem.clear();
    
    for(int  i=0;  i<5; i++){
        Point  pt;
        pt.x=Pt0.x+(i%5)*(size.width+6);
        pt.y=Pt0.y;
        
        Layout *panelItem2=(Layout*)panelItem->clone();
        panelItem2->setVisible(true);
        panelItem2->setPosition(pt);
        
        m_panelItem.push_back(panelItem2);
        panelItem->getParent()->addChild(panelItem2);
    
    }
    
    panelItem->setVisible(false);                       //原始项，隐藏，
    setPanelItem(m_panelItem, m_camp);                  //-----设置自己的英雄；
    
}

void UiArena::setPanelItem( vector<Layout*>  panelItem, vector<string>  camp)//======设置自己的英雄；
{
    int n=(int)panelItem.size();
    
    for(int i=0;i<n; i++){
    
        Layout *panelItem2=panelItem[i];

        if (i<camp.size()) {
            
            panelItem2->setName(camp[i]);
            //设置项；
            string str1="hero/"+Account::sharedAccount()->m_heroProperty[  atoi(camp[i].c_str()) ].table.hero_icon;
            string str2=getQualityFrame1( i%8 );
            string str3="LV88";
            
            ImageView  *imageHead=static_cast<ImageView*>(Helper::seekWidgetByName(panelItem2,"imageHead"));
            imageHead->loadTexture(str1,TextureResType::PLIST);
            
            Button  *buttonHead=static_cast<Button*>(Helper::seekWidgetByName(panelItem2,"buttonHead"));
            buttonHead->loadTextureNormal(str2,TextureResType::PLIST);
            
            Text  *textLevel=static_cast<Text*>(Helper::seekWidgetByName(panelItem2,"textLevel"));
            textLevel->setString(str3);
            
        }
        else{                                                         //上阵的少于5个时为空；
            panelItem2->setName(to_string(i));;                        //以号为名字；
            
            //设置项；
            string str2=getQualityFrame1( i%8 );
            
            ImageView  *imageHead=static_cast<ImageView*>(Helper::seekWidgetByName(panelItem2,"imageHead"));
            imageHead->loadTexture(str2,TextureResType::PLIST);      //设置成一个框；
            
            Button  *buttonHead=static_cast<Button*>(Helper::seekWidgetByName(panelItem2,"buttonHead"));
            buttonHead->loadTextureNormal(str2,TextureResType::PLIST);
            
            Text  *textLevel=static_cast<Text*>(Helper::seekWidgetByName(panelItem2,"textLevel"));
            textLevel->setVisible(false);
            
        }

    }


}

void UiArena::setCamp(vector<string> camp){        //=======设置阵容，接收阵容界面的数据；
    
    m_camp.clear();
    m_camp=camp;
    setPanelItem(m_panelItem, m_camp);  //-----设置自己的英雄；
    
}




//

void UiArena::initPanelHero(Widget *pSender, vector<adversaryST> adversary)         //===初始化挑战的英雄；
{
    Layout*  panelItem=(Layout*)pSender->getChildByName("panelHero");
    Point  Pt0=panelItem->getPosition();
    Size  size=panelItem->getContentSize();
    //log("UiArena::panelItem-============+++++++==width:%f,height:%f",size.width,size.height);
    
    
    m_panelHero.clear();
    
    for(int  i=0;  i<3; i++){
        Point  pt;
        pt.x=Pt0.x+(i%3)*(size.width);
        pt.y=Pt0.y;
        
        Layout *panelItem2=(Layout*)panelItem->clone();
        panelItem2->setVisible(true);
        panelItem2->setPosition(pt);

        panelItem->getParent()->addChild(panelItem2,0,adversary[i].id);         //以ID号为名字；

        m_panelHero.push_back(panelItem2);
 
        
    }
    
    panelItem->setVisible(false);                                   //原始项，隐藏，
    
    setPanelHero(m_panelHero, m_adversary);                         //------设置挑战的英雄；

}


void UiArena::setPanelHero(vector<Layout*>  panelHero, vector<adversaryST> adversary)   //===设置挑战的英雄；
{

    
    for(int  i=0;  i<3; i++){

        Layout *panelItem2=panelHero[i];
        panelItem2->setName(adversary[i].id);         //以ID号为名字；
        
        
        //设置对手项；
        string str1="hero/"+Account::sharedAccount()->m_heroProperty[  atoi(m_goods[random()%6].c_str()) ].table.hero_icon;
        string str2=getQualityFrame1( i%8 );
        string str3="LV88";
        string str4="ui_jingji01_1"+to_string(3+i)+".png";
        
        Button  *buttonItem=(Button*)panelItem2->getChildByName("buttonItem");             //底按钮；
        buttonItem->loadTextureNormal(str4,TextureResType::PLIST);
        
        //buttonItem->setName(adversary[i].id);
        buttonItem->addTouchEventListener(CC_CALLBACK_2(UiArena::buttonEvent,this));
        
        Button  *buttonChallenge=(Button*)panelItem2->getChildByName("buttonChallenge");             //挑战按钮；
        buttonChallenge->addTouchEventListener(CC_CALLBACK_2(UiArena::buttonEvent,this));
        
        ImageView  *imageHead=static_cast<ImageView*>(Helper::seekWidgetByName(panelItem2,"imageHead"));   //头像；
        imageHead->loadTexture(str1,TextureResType::PLIST);
        
        Button  *buttonHead=static_cast<Button*>(Helper::seekWidgetByName(panelItem2,"buttonHead"));   //头像框按钮；
        buttonHead->loadTextureNormal(str2,TextureResType::PLIST);
        
        Text  *textLevel=static_cast<Text*>(Helper::seekWidgetByName(panelItem2,"textLevel"));
        textLevel->setString(str3);
        
        Text  *textName=(Text*)panelItem2->getChildByName("textName");    //名字；
        textName->setString(adversary[i].name);
        
        Text  *textSword=(Text*)panelItem2->getChildByName("textSword");   //战力；
        textSword->setString(adversary[i].sword);
        
        Text  *textRanking=(Text*)panelItem2->getChildByName("textRanking");  //排名；
        textRanking->setString(adversary[i].ranking);
        
        
        
    }



}








void UiArena::timeCallback(float dt){                                 ////时间；
    
    if(m_time==0){  unschedule(schedule_selector(UiArena::timeCallback));   return;}
    m_time--;
    string  str;
    int  min=(int)m_time/60;
    
    if (min<10) {  str="0"+to_string(min); }
    else{ str=to_string(min);}
    
    int  sec=(int)m_time%60;
    if (sec<10) {  str=str+":"+"0"+to_string(sec); }
    else{ str=str+":"+to_string(sec);}
    
    
    Text  *text5=(Text*) m_panelArena->getChildByName("text5");             //时间；
    text5->setString(str);
    
    
}




//////////////////////////////////////////////
//兑换面板设置；
void   UiArena::setPanel(Widget *pSender,vector<string>  itemID, int  itemNum){     //===兑换设置面板; (商品，面板项数)；
    
    //增加精灵项；
   
    Layout*  panelItem=(Layout*)pSender->getChildByName("panelItem");
    Point  Pt0=panelItem->getPosition();
    Size  size=panelItem->getContentSize();
    //log("UiArena::panelItem-============+++++++==width:%f,height:%f",size.width,size.height);
    
    
    if(m_panelItem2.size()>0){
        for(Layout *panelItem:m_panelItem2){
            panelItem->removeFromParent();
        }
        m_panelItem2.clear();
    }
    
    
    
    for(int  i=0;  i<itemNum; i++){
        Point  pt;
        pt.x=Pt0.x+(i%3)*(size.width+12);
        pt.y=Pt0.y-(int(i/3))*(size.height+12);
        
        Layout *panelItem2=(Layout*)panelItem->clone();
        panelItem2->setVisible(true);
        panelItem2->setPosition(pt);
        
        m_panelItem2.push_back(panelItem2);
        int n=rand()%(itemID.size());
        
        
        panelItem->getParent()->addChild(panelItem2,0,itemID[n]);         //以ID号为名字；
        setItem(panelItem2, itemID  ,n);  //------设置里面的项
        
        
        //log("UiArena::panelItem-============%s",itemID[n].c_str());
        
    }
    
    panelItem->setVisible(false);                                   //原始项，隐藏，
    
    
}

void UiArena::setItem(Widget *pSender, vector<string>  itemID, int n ){            //======设置里面的项；(项，itemID,id对应的项)
    
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

bool  UiArena::buttonInit(){
    
  
    
    m_buttonArena= static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonArena"));                     //竞技按钮；
    if (!m_buttonArena){ log("UiArena::button====buttonExchange get error");return false; }
    m_buttonArena->addTouchEventListener(CC_CALLBACK_2(UiArena::buttonEvent, this));
    
    m_buttonExchange= static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonExchange"));                //兑换按钮；
    if (!m_buttonExchange){ log("UiArena::button====buttonExchangeget error");return false; }
    m_buttonExchange->addTouchEventListener(CC_CALLBACK_2(UiArena::buttonEvent, this));
    
    
    Button  *buttonRecharge = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonFlush"));         //刷新按钮；
    if (!buttonRecharge){ log("UiArena::button====buttonFlush get error");return false; }
    buttonRecharge->addTouchEventListener(CC_CALLBACK_2(UiArena::buttonEvent, this));
    
    
    
    
    
    return  true;
    
}


void  UiArena::buttonEvent(Ref *pSender, Widget::TouchEventType type)             //按钮响应函数；
{
    
    Button*  button=dynamic_cast<Button*>(pSender);
    string   str=button->getName();
    
    string  str1="buttonFlush";
    

    //面板按钮；
    string  str2="buttonExchange";
    string  str3="buttonArena";

    //竞技面板按钮;
    string  str4="buttonCamp";
    string  str5="buttonAward";
    string  str6="buttonRanking";
    string  str7="buttonRecord";
    string  str8="buttonFlush2";
    
    //竞技面板对手按钮
    string  str9="buttonChallenge";
    string  str10="buttonItem";
    
    
    switch (type)
    {
        case  Widget::TouchEventType::ENDED:
        {
            if (str==str1) {                  //刷新按钮；

                setPanel(m_panelExchangepa,m_goods,9);
                
            }
            else if (str==str2||str==str3){
                buttonPress(pSender);        //-----按钮选项卡；
            }
            
            else if (str==str4){                      //--阵容;
                UiCamp*  uiCamp=UiCamp::create();
                this->addChild(uiCamp);
                uiCamp->setType(1);
                uiCamp->setCamp();
                //inclMessageBox("阵容", "阵容");
            }
            
            else if (str==str5){
//                if(!m_connect){
//                    ClientSocketManger::sharedClientSocketManger()->connectSocket();//连接；
//                    m_connect=true;
//                    log("UiArena::  connect");
//                }
//                else{
//                   ClientSocketManger::sharedClientSocketManger()->send("898598888",100,this);  //发送；
//                   log("UiArena::  send");
//                
//                }
                
               Account::sharedAccount()->login();
                
               // Account::sharedAccount()->init();
                
             //schedule(schedule_selector(Account::sendCallback),1);
              // MessageBox("奖励", "奖励");
            }
            else if (str==str6){
                
                MessageBox("排行", "排行");
            }
            else if (str==str7){
                
                MessageBox("记录", "记录");
            }
            else if (str==str8){
                
                
                adversaryST temp0=m_adversary[0];
                adversaryST temp1=m_adversary[1];
                adversaryST temp2=m_adversary[2];
                m_adversary.clear();
                m_adversary.push_back(temp1);
                m_adversary.push_back(temp2);
                m_adversary.push_back(temp0);
                //sort(m_adversary.begin(),m_adversary.end());
                setPanelHero(m_panelHero, m_adversary);
                
            }
            else if (str==str9||str==str10){
                
                MessageBox(button->getParent()->getName().c_str(), "挑战");
            }
            
        }
            break;
            
        default:      break;
    }
}



void  UiArena::buttonPress(Ref *pSender){    //====按钮选项卡；
    
    if (!pSender) {   return;  }
    
    Button  *button1 = m_buttonArena;
    Button  *button2 = m_buttonExchange;

    Text  *text1 = button1->getChildByName<Text*>( "textName");
    Text  *text2 = button2->getChildByName<Text*>( "textName");

    string  strShow="ui_cangku_02.png";
    string  strHide="ui_cangku_03.png";
    Color3B  colorShow=Color3B(255, 237, 222);
    Color3B  colorHide=Color3B(46, 28, 8);
    
    
    Button*  button=dynamic_cast<Button*>(pSender);
    string   str=button->getName();
    
    string  str1="buttonArena";
    string  str2="buttonExchange";

    
    
    if (str==str1) {
        button1->loadTextureNormal(strShow,TextureResType::PLIST);
        button1->loadTexturePressed(strHide,TextureResType::PLIST);
        button2->loadTextureNormal(strHide,TextureResType::PLIST);
        button2->loadTexturePressed(strShow,TextureResType::PLIST);
  
        text1->setColor(colorShow);
        text2->setColor(colorHide);

        m_panelArena->setVisible(true);
        m_panelExchangepa->setVisible(false);

        
    }
    else if(str==str2){
        
        button1->loadTextureNormal(strHide,TextureResType::PLIST);
        button1->loadTexturePressed(strShow,TextureResType::PLIST);
        button2->loadTextureNormal(strShow,TextureResType::PLIST);
        button2->loadTexturePressed(strHide,TextureResType::PLIST);
        
        text1->setColor(colorHide);
        text2->setColor(colorShow);
        
        m_panelArena->setVisible(false);
        m_panelExchangepa->setVisible(true);
        
    }
  
    
    
}






void UiArena::onEnter()
{
    Layer::onEnter();
}

void UiArena::onExit()
{
    Layer::onExit();
}



