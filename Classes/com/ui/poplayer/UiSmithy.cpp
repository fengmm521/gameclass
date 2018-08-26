/**********************************************
铁匠铺界面；
 
 **********************************************/

#include "UiSmithy.h"
#include<iostream>

using namespace cocos2d::ui;

UiSmithy::UiSmithy (){
    m_percent=15;
    //m_account=null;
    m_prePress=0;
   // m_backPress=0;
}

UiSmithy::~UiSmithy (){

}

bool UiSmithy::init()
{
    if ( !UiBase::init() )  {      return false;    }

    //界面；
    m_pNode = GUIReader::getInstance()->widgetFromJsonFile("uiSmithy.ExportJson");
    m_pNodeBase->addChild(m_pNode);
    m_pNodeBase->getChildByName("imageBK0")->setVisible(false);
    m_pNode->setTouchEnabled(false);
    
    //三个面板；
    m_panelStrengthen = static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelStrengthen"));
    m_panelStrengthen->setVisible(true);
    m_panelUp = static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelUp"));
    m_panelUp->setVisible(false);
    m_panelSeparate= static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelSeparate"));
    m_panelSeparate->setVisible(false);
    
    //账号；
    m_account=Account::sharedAccount();
   // m_account->retain();
    
    //滑块；
    Slider  *slider=static_cast<Slider*>(Helper::seekWidgetByName(m_pNode,"slider"));
    slider->addEventListener(CC_CALLBACK_2(UiSmithy::sliderEvent, this));
    //slider->setVisible(false);
    
    //初始化列表图层；
    setListView();                  //列表框设置；
    setPanelItemShow(m_prePress);   //列表框初始选中项；
    
    //设置强化面板；
     setPanelStrengthen();
    
    //升阶；
    setPanelUp();
    
    //分解；
    setPanelSeparate();
    
    //按钮；
    buttonInit();
    
    
    return true;
}


//////////////////////////////////////////////
//列表框设置；
void   UiSmithy::setListView(){
    
    //原有项；
    ui::ListView  *listViewTie = static_cast<ui::ListView*>(Helper::seekWidgetByName(m_pNode, "listView"));
    Layout*  panelItem=static_cast<Layout*>(Helper::seekWidgetByName(listViewTie, "panelItem"));
    listViewTie->addEventListener(CC_CALLBACK_2(UiSmithy::scrollViewEvent, this));
    listViewTie->addEventListener(CC_CALLBACK_2(UiSmithy::listViewEvent, this));
    
    int count=(int)m_account->m_equip.size();
    log("************%d",count);
    for (int i=0; i<count; i++) {
        Layout*  panelItem2=(Layout*)panelItem->clone();
        
        //设置头像；文字，级别；
        string str2="equip/"+m_account->m_equipProperty[atoi(m_account->m_equip[i].c_str())].table.equip_icon; //账号-装备ID-表结构体-图片；
        string str3=m_account->m_equipProperty[atoi(m_account->m_equip[i].c_str())].table.equip_name;
        string str4=to_string(m_account->m_equipProperty[atoi(m_account->m_equip[i].c_str())].table.equip_apparel_level)+"级";
        string str5=getQualityFrame3(rand()%8);
        
        ImageView  *imageHead=(ImageView*)panelItem2->getChildByName("imageHead");
        imageHead->loadTexture(str2,TextureResType::PLIST);
        
        Button  *buttonHead=(Button*)panelItem2->getChildByName("buttonHead");
        buttonHead->loadTextureNormal(str5,TextureResType::PLIST);
        
        
        Text*  textName=(Text*)panelItem2->getChildByName("textName");
        textName->setString(str3);
        
        Text*  textLevel=(Text*)panelItem2->getChildByName("textLevel");
        textLevel->setString(str4);
        
        
        listViewTie ->insertCustomItem(panelItem2, i+1);
    }
   
    listViewTie->removeItem(0);
    
    
}

void  UiSmithy::setPanelItemShow(ssize_t index){   //选中；
    
    ui::ListView  *listView = static_cast<ui::ListView*>(Helper::seekWidgetByName(m_pNode, "listView"));

    Layer*   panelItem=(Layer*)listView->getItem(index);
    Button*  buttonItem=(Button*)panelItem->getChildByName("buttonItem");
    buttonItem->loadTextureNormal("ui_tiejiang01_21.png",TextureResType::PLIST);
    buttonItem->loadTexturePressed("ui_tiejiang01_22.png",TextureResType::PLIST);
    
    
}


void  UiSmithy::setPanelItemHide(){   //先前选中的；

    ui::ListView  *listView = static_cast<ui::ListView*>(Helper::seekWidgetByName(m_pNode, "listView"));
    
    Layer*   panelItem=(Layer*)listView->getItem(m_prePress);
    Button*  buttonItem=(Button*)panelItem->getChildByName("buttonItem");
    buttonItem->loadTextureNormal("ui_tiejiang01_22.png",TextureResType::PLIST);
    buttonItem->loadTexturePressed("ui_tiejiang01_21.png",TextureResType::PLIST);
    
    
}

////////////////////////////////////
//强化；
void  UiSmithy::setPanelStrengthen(){               //设置强化面板；
    //Layout  *panelStrengthen = static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelStrengthen"));
    
    
    //int n=m_prePress%6;
    int n=(int)m_prePress;
    
    int  index=atoi(m_account->m_equip[n].c_str());
    
    
    
    string str0="equip/"+m_account->m_equipProperty[index].table.equip_icon;
    //log("str0==++++++====%s",str0.c_str());
    string str1=to_string(m_account->m_equipProperty[index].table.equip_quality);
       str1=getQualityFrame3(atoi(str1.c_str()));
    //log("str1====+++++++==%s",str1.c_str());
    
    string str2=m_account->m_equipProperty[index].table.equip_name;                   //账号-装备ID-表结构体-图片；
    
    string str3=to_string(m_account->m_equipProperty[index].level);
       str3="等级:"+str3+">>"+to_string(atoi(str3.c_str())+1);
    
    string str4=m_account->m_equipProperty[index].table.equip_physic_act;
       if (str4=="-1") {  str4="2000+150";  }
       str4="物攻:"+str4;
    
    string str5=m_account->m_accountST.life;
       str5="血量:"+str5;
    
    string str6=to_string(m_account->m_equipProperty[index].table.equip_advance_gola_expend);
       if (str6=="-1") {  str6="3000";  }
       str6="消耗:"+str6;
    
    string str7="100";
    
    string str8=m_account->m_accountST.gold;
       str8="持有:"+str8;
    string str9=m_account->m_accountST.gem;
    
    
    
    //0头像
    
    setHead(m_panelStrengthen, str0);
    
    //1底框；
    setHeadBK(m_panelStrengthen, str1);
    
    //2名字
    Text*  textName=(Text*)m_panelStrengthen->getChildByName("textName");
    textName->setString(str2);
   
    //3等级；
    Text*  textLevel=(Text*)m_panelStrengthen->getChildByName("textLevel");
    textLevel->setString(str3);
    
    //4物攻；
    Text*  textFight=(Text*)m_panelStrengthen->getChildByName("textFight");
    textFight->setString(str4);
    
    //5血量；
    Text*  textLife=(Text*)m_panelStrengthen->getChildByName("textLife");
     textLife->setString(str5);
    
    //6消耗1；
    Text*  textPay1=(Text*)m_panelStrengthen->getChildByName("textPay1");
    textPay1->setString(str6);
    
    //7消耗2；
    Text*  textPay2=(Text*)m_panelStrengthen->getChildByName("textPay2");
    textPay2->setString(str7);
    
    //8持有1；
    Text*  textHave1=(Text*)m_panelStrengthen->getChildByName("textHave1");
    textHave1->setString(str8);
    
    //9持有2；
    Text*  textHave2=(Text*)m_panelStrengthen->getChildByName("textHave2");
    textHave2->setString(str9);
    
    
    
    Button*  buttonStrengthen1=(Button*)m_panelStrengthen->getChildByName("buttonStrengthen1");
    buttonStrengthen1->setName("buttonStrengthen1");
    buttonStrengthen1->addTouchEventListener(CC_CALLBACK_2(UiSmithy::buttonEvent, this));
    
    
    Button*  buttonStrengthen2=(Button*)m_panelStrengthen->getChildByName("buttonStrengthen2");
    buttonStrengthen2->setName("buttonStrengthen2");
    buttonStrengthen2->addTouchEventListener(CC_CALLBACK_2(UiSmithy::buttonEvent, this));
    
}






void  UiSmithy::setHead(Widget* pWidget, string headImage){       //设置头像；
    
    ImageView  *imageHead=(ImageView*)pWidget->getChildByName("imageHead");
    imageHead->loadTexture(headImage,TextureResType::PLIST);
    
}


void  UiSmithy::setHeadBK(Widget* pWidget,string frameLevel,string buttonName){        //设置底框；tag 100, 101
    
    //头像的底框是个按钮；
    Button  *buttonHead=(Button*)pWidget->getChildByName("buttonHead");
    buttonHead->loadTextureNormal(frameLevel,TextureResType::PLIST);
    //buttonHead->setName(buttonName);
   // buttonHead->setTag(100);
    buttonHead->addTouchEventListener(CC_CALLBACK_2(UiSmithy::buttonEvent, this));
    
    
}





////////////////////////////////////
//升阶；
void  UiSmithy::setPanelUp(){

    int n=(int)m_prePress;
    int  index=atoi(m_account->m_equip[n].c_str());
    
    string str0="equip/"+m_account->m_equipProperty[index].table.equip_icon;      //第一个图标；
    log("panelUpstr0==++++++====%s",str0.c_str());
    
    string str1=to_string(m_account->m_equipProperty[index].table.equip_quality);
    str1=getQualityFrame3(atoi(str1.c_str()));
    log("panelUpstr1====+++++++==%s",str1.c_str());
    
    
    int  index2=m_account->m_equipProperty[index].table.equip_next_id;
    string str01="";
    string str11="";
    string str2="已经到顶级了";
    string str3=to_string(m_account->m_equipProperty[index].table.equip_apparel_level);
    str3=str3+"/";
    
    if(index2!=-1){
       str01="equip/"+m_account->m_equipProperty[index2].table.equip_icon;     //下阶的图标；
       str11=to_string(m_account->m_equipProperty[index2].table.equip_quality);
       str11=getQualityFrame3(atoi(str11.c_str()));
        
       str2="升阶为"+m_account->m_equipProperty[index2].table.equip_name;
       str3=str3+to_string(m_account->m_equipProperty[index2].table.equip_apparel_level);
        
    }
    

    
    string str4=m_account->m_equipProperty[index].table.equip_physic_act;
    if (str4=="-1") {  str4="2000+500";  }
    str4="物攻:"+str4;
    
    string str5=m_account->m_accountST.life;
    str5="血量:"+str5+"+"+"1000";
    
    string str6=to_string(m_account->m_equipProperty[index].table.equip_advance_gola_expend);
    if (str6=="-1") {  str6="6000";  }
    str6="消耗:"+str6;
    

    
    
    
    //0头像
    
    setHead(m_panelUp, str0);
    
    //1底框；
    setHeadBK(m_panelUp, str1);
    
    if(index2!=-1){
    
        ImageView  *imageHead=(ImageView*)m_panelUp->getChildByName("imageHead2");   //0头像
        imageHead->loadTexture(str01,TextureResType::PLIST);
        
        Button  *buttonHead2=(Button*)m_panelUp->getChildByName("buttonHead2");      //1底框；
        buttonHead2->loadTextureNormal(str11,TextureResType::PLIST);
        buttonHead2->addTouchEventListener(CC_CALLBACK_2(UiSmithy::buttonEvent, this));
   
    }
    
    //2名字
    Text*  textName=(Text*)m_panelUp->getChildByName("textName");
    textName->setString(str2);
    
    //3等级；
    Text*  textLevel=(Text*)m_panelUp->getChildByName("textLevel");
    textLevel->setString(str3);
    
    //4物攻；
    Text*  textFight=(Text*)m_panelUp->getChildByName("textFight");
    textFight->setString(str4);
    
    //5血量；
    Text*  textLife=(Text*)m_panelUp->getChildByName("textLife");
    textLife->setString(str5);
    
    //6消耗1；
    Text*  textPay=(Text*)m_panelUp->getChildByName("textPay");
    textPay->setString(str6);
    

    
    
    //升阶；
    Button*  buttonStrengthen1=(Button*)m_panelUp->getChildByName("buttonUp2");
    buttonStrengthen1->setName("buttonUp2");
    buttonStrengthen1->addTouchEventListener(CC_CALLBACK_2(UiSmithy::buttonEvent, this));
    
    
    //升阶材料；
    string   strMaterial=m_account->m_equipProperty[index].table.equip_advance_material;  //读表的数据；
    
    vector<string> itemID;
    if(strMaterial=="-1"){  itemID=m_account->m_prop;   }  //一个账号里的材料；
    else{ StrSplit::split(strMaterial, ",",itemID);   }   //表中的材料；
    
    log("UiSmithy::strMaterial============+++++++==%s",itemID[0].c_str());
    
    Layout*  panelItem3=(Layout*)m_panelUp->getChildByName("panelMaterial");
    setPanelMaterial(panelItem3,itemID, 6);         //-------设置升阶材料
    
}


void  UiSmithy::setPanelMaterial(Widget* pWidget,vector<string> itemID, int num){            //====设置升阶材料； (父节点，材料ID，数目)；

    
    
    //增加精灵项；
    //Layout*  panelItem3=(Layout*)pWidget->getChildByName("panelMaterial");
    
    Layout*  panelItem=(Layout*)pWidget->getChildByName("panelItem");
    Point  Pt0=panelItem->getPosition();
    Size  size=panelItem->getContentSize();
    log("UiSmithy::panelItem-============+++++++==width:%f,height:%f",size.width,size.height);
    
    for(int  i=0;  i<num; i++){
        Point  pt;
        pt.x=Pt0.x+(i%3)*(size.width);
        pt.y=Pt0.y-(int(i/3))*(size.height+8);

        Layout *panelItem2=(Layout*)panelItem->clone();
        panelItem2->setVisible(true);
        panelItem2->setPosition(pt);
        
        //图标
        string  strIcon="prop/"+m_account->m_propProperty[atoi(itemID[i].c_str())].table.item_icon;
        //log("UiSmithy::panelItem-============+++++++==width:%s",strIcon.c_str());
        setHead(panelItem2, strIcon);  //---
        

        //底框；
        string  strFrame= getQualityFrame1(m_account->m_propProperty[atoi(itemID[i].c_str())].table.item_quality);
        log("UiSmithy::panelItem-============+++++++==width:%s",strIcon.c_str());
        setHeadBK(panelItem2, strFrame);  //---
        
        panelItem->getParent()->addChild(panelItem2,0,itemID[i]);         //以ID号为名字；
        
       
    }
    
    panelItem->setVisible(false);                                   //原始项，隐藏，

}







////////////////////////////////////
//分解；
void  UiSmithy::setPanelSeparate(){


    int n=(int)m_prePress;
    int  index=atoi(m_account->m_equip[n].c_str());
    
    
    //0头像
    Layout*  panelItem1=(Layout*)m_panelSeparate->getChildByName("panelItem");
    string str0="equip/"+m_account->m_equipProperty[index].table.equip_icon;
    setHead(panelItem1, str0);
   
    //1底框；
    string str1=to_string(m_account->m_equipProperty[index].table.equip_quality);
    str1=getQualityFrame3(atoi(str1.c_str()));
    setHeadBK(panelItem1, str1);

    
    
    //分解材料；
    string   strMaterial=m_account->m_equipProperty[index].table.equip_decompose_materials;  //读表的数据；
    
    vector<string> itemID;
    if(strMaterial=="-1"){  itemID=m_account->m_prop;   }        //一个账号里的材料；
    else{ StrSplit::split(strMaterial, ",",itemID);   }          //表中的材料；
    
    log("UiSmithy::strMaterial============+++++++==%s",itemID[0].c_str());
    
    
    Layout*  panelItem3=(Layout*)m_panelSeparate->getChildByName("panelMaterial");
    setPanelMaterial(panelItem3,itemID, 6);         //-------设置升阶材料
    
    
    //随机材料；
    vector<string>  itemGet;
    
    for (int i=0; i<6; i++) {
        int  getnum=rand()%6;
        itemGet.push_back(itemID[getnum]);
    }
    
    Layout*  panelItem4=(Layout*)m_panelSeparate->getChildByName("panelGet");
    setPanelMaterial(panelItem4,itemGet,3);         //-------
    
    
    //分解按钮；
    Button*  buttonSeparate=(Button*)m_panelSeparate->getChildByName("buttonSeparate2");
    buttonSeparate->setName("buttonSeparate2");
    buttonSeparate->addTouchEventListener(CC_CALLBACK_2(UiSmithy::buttonEvent, this));


}







////////////////////////////////////
//控件响应事件；


void  UiSmithy::sliderEvent(Ref *pSender, Slider::EventType type){    //滑块响应函数，控制滚动层；
    
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
        
    }
    
}


void  UiSmithy::scrollViewEvent(Ref *pSender, ui::ScrollView::EventType type){   //====列表层调用滚动层响应函数，控制滑块；；
    
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

void  UiSmithy::listViewEvent(Ref *pSender, ui::ListView::EventType type){   //====列表层第二个响应函数；
    
    ui::ListView* listView=static_cast<ui::ListView*>(pSender);
    if(!listView){log("ScrollView  is  NULL"); return;}
    
    
    switch (type) {
        case ui::ListView::EventType::ON_SELECTED_ITEM_END :    //点；
        {
            ssize_t  n=listView->getCurSelectedIndex();      //n对应着m_equip;
            
            setPanelItemShow(n);                           // 显示底；
            if(n!=m_prePress){  setPanelItemHide();  }     //隐藏前一项的底；
            
            m_prePress=n;                                 //前一项的索引；
            
            setPanelStrengthen();                        //设置强化面板；
            setPanelUp();                                //升阶；
            setPanelSeparate();                          //分解；
            
            log("ON_SELECTED_ITEM_START =====%d",(int)n);
        }
            break;
        

            
            
        default:
            break;
    }

}






////////////////////////////////////////
////////////////////////////////////////
//按钮

bool  UiSmithy::buttonInit(){
    
    
    Button  *buttonStar = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonStrengthen"));      //强化按钮；
    if (!buttonStar){ log("no-buttonStrengthen");return false; }
    buttonStar->addTouchEventListener(CC_CALLBACK_2(UiSmithy::buttonEvent, this));
    
    Button  *buttonSkill = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonUp"));             //升阶按钮；
    if (!buttonSkill){ log("no-buttonUp");return false; }
    buttonSkill->addTouchEventListener(CC_CALLBACK_2(UiSmithy::buttonEvent, this));
    
    Button  *buttonProperty = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonSeparate"));    //分解按钮；
    if (!buttonProperty){ log("no-buttonSeparate"); return  false; }
    buttonProperty->addTouchEventListener(CC_CALLBACK_2(UiSmithy::buttonEvent, this));
    

    return  true;
    
}


void  UiSmithy::buttonEvent(Ref *pSender, Widget::TouchEventType type)             //按钮响应函数；
{
    
    Button*  button=dynamic_cast<Button*>(pSender);
    string   str=button->getName();
    log("UiSmithy::button============+++++++==%s",str.c_str());
    string  str1="buttonBack";
    
    //三个面板按钮；
    string  str2="buttonStrengthen";
    string  str3="buttonUp";
    string  str4="buttonSeparate";

    //强化；
    string  str5="buttonStrengthen1";
    string  str6="buttonStrengthen2";
    
    //升阶
    string  str7="buttonUp2";
    
    //分解
    string  str8="buttonSeparate2";
    
    
    switch (type)
    {
        case  Widget::TouchEventType::ENDED:
        {
            if (str==str1) {   //返回；
                CC_SAFE_RETAIN(this);
                this->removeFromParent();
            }
            
            else if (str==str2||str==str3||str==str4){
                buttonPress(pSender);        //-----按钮选项卡；
            }
            
            else if(str==str5){
                
                MessageBox("一键强化", "一键强化");
            }
            
            else if (str==str6){
                
                MessageBox("强化", "强化");
            }
            
            else if (str==str7){
                
                MessageBox("升阶", "升阶");
            }
            else if (str==str8){
                
                MessageBox("分解", "分解");
            }
            
        }
            break;
            
        default:      break;
    }
    
    
    
    
    
    
}


void  UiSmithy::buttonPress(Ref *pSender){    //====按钮选项卡；
    
    if (!pSender) {   return;  }
    
    Button  *button1 = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonStrengthen"));
    Button  *button2 = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonUp"));
    Button  *button3 = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonSeparate"));
    
    
    Text  *text1 = button1->getChildByName<Text*>( "textName");
    Text  *text2 = button2->getChildByName<Text*>( "textName");
    Text  *text3 = button3->getChildByName<Text*>( "textName");
    
    
    
    //Layout  *panelStrengthen = static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelStrengthen"));
    //Layout  *panelUp = static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelUp"));
    Layout  *panelSeparate= static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelSeparate"));

    
    string  strShow="ui_cangku_02.png";
    string  strHide="ui_cangku_03.png";
    Color3B  colorShow=Color3B(255, 237, 222);
    Color3B  colorHide=Color3B(46, 28, 8);
    
    
    Button*  button=dynamic_cast<Button*>(pSender);
    string   str=button->getName();
    
    string  str1="buttonStrengthen";
    string  str2="buttonUp";
    string  str3="buttonSeparate";

 
    if (str==str1) {
        button1->loadTextureNormal(strShow,TextureResType::PLIST);
        button1->loadTexturePressed(strHide,TextureResType::PLIST);
        button2->loadTextureNormal(strHide,TextureResType::PLIST);
        button2->loadTexturePressed(strShow,TextureResType::PLIST);
        button3->loadTextureNormal(strHide,TextureResType::PLIST);
        button3->loadTexturePressed(strShow,TextureResType::PLIST);

        
        text1->setColor(colorShow);
        text2->setColor(colorHide);
        text3->setColor(colorHide);

        
        m_panelStrengthen ->setVisible(true);
        m_panelUp->setVisible(false);
        panelSeparate->setVisible(false);

        
    }
    else if(str==str2){
        
        button1->loadTextureNormal(strHide,TextureResType::PLIST);
        button1->loadTexturePressed(strShow,TextureResType::PLIST);
        button2->loadTextureNormal(strShow,TextureResType::PLIST);
        button2->loadTexturePressed(strHide,TextureResType::PLIST);
        button3->loadTextureNormal(strHide,TextureResType::PLIST);
        button3->loadTexturePressed(strShow,TextureResType::PLIST);

        
        text1->setColor(colorHide);
        text2->setColor(colorShow);
        text3->setColor(colorHide);

        
        m_panelStrengthen ->setVisible(false);
        m_panelUp->setVisible(true);
        panelSeparate->setVisible(false);

        
    }
    
    else if(str==str3){
        
        button1->loadTextureNormal(strHide,TextureResType::PLIST);
        button1->loadTexturePressed(strShow,TextureResType::PLIST);
        button2->loadTextureNormal(strHide,TextureResType::PLIST);
        button2->loadTexturePressed(strShow,TextureResType::PLIST);
        button3->loadTextureNormal(strShow,TextureResType::PLIST);
        button3->loadTexturePressed(strHide,TextureResType::PLIST);

        
        text1->setColor(colorHide);
        text2->setColor(colorHide);
        text3->setColor(colorShow);

        
        m_panelStrengthen ->setVisible(false);
        m_panelUp->setVisible(false);
        panelSeparate->setVisible(true);

    }
   
   
    
}





void UiSmithy::onEnter()
{
    Layer::onEnter();
}

void UiSmithy::onExit()
{
    Layer::onExit();
}



/*
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
 
 
 MessageBox("fgfggf", "dsdsss");;
 
 }
 break;
 
 case  Widget::TouchEventType::CANCELED:
 {
 
 }
 break;
 
 default:
 break;
 }
*/



