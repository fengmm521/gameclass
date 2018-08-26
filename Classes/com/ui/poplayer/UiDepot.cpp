/**********************************************
仓库界面；
 
 **********************************************/

#include "UiDepot.h"
#include<iostream>
#include<string>

using namespace cocos2d::ui;

UiDepot::UiDepot(){
    m_scrollView1=NULL;
    m_scrollView2=NULL;
    m_scrollView3=NULL;
    m_scrollView4=NULL;
    m_scrollView5=NULL;
    m_slider=NULL;
    
    m_buttonPre=nullptr;
    m_textPre=nullptr;
    m_sliderPre=nullptr;
    m_scrollViewPre=nullptr;
}
UiDepot::~UiDepot(){
    
    m_hero.clear();
    m_equip.clear();
    m_prop.clear();
    m_goods.clear();

}






bool UiDepot::init()
{
    if ( !UiBase::init() )  {      return false;    }

    //界面；
    m_pNode = GUIReader::getInstance()->widgetFromJsonFile("uiDepot.ExportJson");
    m_pNodeBase->addChild(m_pNode);
    m_pNodeBase->getChildByName("imageBK0")->setVisible(false);
    m_pNode->setTouchEnabled(false);
    log("UiDepot::====init");
    
    //物品ID;
    m_goods.clear();
    m_goods.push_back("1001");
    m_goods.push_back("1002");
    m_goods.push_back("1003");
    m_goods.push_back("1004");
    m_goods.push_back("1001");
    m_goods.push_back("1002");
    m_goods.push_back("1003");
    m_goods.push_back("1004");
    m_goods.push_back("1010");
    m_goods.push_back("1012");
    m_goods.push_back("1501");
    m_goods.push_back("1502");
    m_goods.push_back("1503");
    m_goods.push_back("6003");
    m_goods.push_back("300001");
    m_goods.push_back("300010");
    m_goods.push_back("300019");
    m_goods.push_back("300028");
    m_goods.push_back("100001");
    m_goods.push_back("100002");
    m_goods.push_back("100003");
    m_goods.push_back("100004");
    
    m_goods.push_back("300001");
    m_goods.push_back("300010");
    m_goods.push_back("300019");
    m_goods.push_back("300028");
    m_goods.push_back("300037");
    m_goods.push_back("300046");
    
    m_goods.push_back("300002");
    m_goods.push_back("300011");
    m_goods.push_back("300020");
    m_goods.push_back("300029");
    m_goods.push_back("300038");
    m_goods.push_back("300047");

    m_goods.push_back("100001");
    m_goods.push_back("100002");
    m_goods.push_back("100003");
    m_goods.push_back("100004");
    m_goods.push_back("100005");
    m_goods.push_back("100006");
    m_goods.push_back("100007");
    m_goods.push_back("100001");
    m_goods.push_back("100002");
    m_goods.push_back("100003");
    m_goods.push_back("100004");
    m_goods.push_back("100005");
    m_goods.push_back("100006");
    m_goods.push_back("100007");
    m_goods.push_back("100001");
    m_goods.push_back("100002");
    m_goods.push_back("100003");
    m_goods.push_back("100004");
    m_goods.push_back("100005");
    m_goods.push_back("100006");
    m_goods.push_back("100007");
    m_goods.push_back("100001");
    m_goods.push_back("100002");
    m_goods.push_back("100003");
    m_goods.push_back("100004");
    m_goods.push_back("100005");
    m_goods.push_back("100006");
    m_goods.push_back("100007");
    m_goods.push_back("100001");
    m_goods.push_back("100002");
    m_goods.push_back("100003");
    m_goods.push_back("100004");
    m_goods.push_back("100005");
    m_goods.push_back("100006");
    m_goods.push_back("100007");
    m_goods.push_back("100001");
    m_goods.push_back("100002");
    m_goods.push_back("100003");
    m_goods.push_back("100004");
    m_goods.push_back("100005");
    m_goods.push_back("100006");
    m_goods.push_back("100007");
    
    //物品分类；
    geoodsClassify();   //---物品分类；
    
    //滑块；
    Layout*panelSlider=static_cast<Layout*>(Helper::seekWidgetByName(m_pNode,"panelSlider"));
    
    m_slider=static_cast<Slider*>(Helper::seekWidgetByName(m_pNode,"slider"));
    m_slider1=(Slider*)m_slider->clone(); m_slider1->setName("m_slider1"); panelSlider->addChild(m_slider1);
    m_slider2=(Slider*)m_slider->clone(); m_slider2->setName("m_slider2"); panelSlider->addChild(m_slider2);
    m_slider3=(Slider*)m_slider->clone(); m_slider3->setName("m_slider3"); panelSlider->addChild(m_slider3);
    m_slider4=(Slider*)m_slider->clone(); m_slider4->setName("m_slider4"); panelSlider->addChild(m_slider4);
    m_slider5=(Slider*)m_slider->clone(); m_slider5->setName("m_slider5"); panelSlider->addChild(m_slider5);
    m_slider6=(Slider*)m_slider->clone(); m_slider6->setName("m_slider6"); panelSlider->addChild(m_slider6);
    m_slider1->setVisible(false);
    m_slider2->setVisible(false);
    m_slider3->setVisible(false);
    m_slider4->setVisible(false);
    m_slider5->setVisible(false);
    m_slider6->setVisible(false);
    m_slider->setVisible(false);
    
    //初始化滚动图层；
    m_scrollView1=static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode, "scrollView1"));      //滚动图全部；
    m_scrollView2=static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode, "scrollView2"));      //滚动图碎片；
    m_scrollView3=static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode, "scrollView3"));      //滚动图装备；
    m_scrollView4=static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode, "scrollView4"));      //滚动图装碎；
    m_scrollView5=static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode, "scrollView5"));      //滚动图消耗；
    m_scrollView6=static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode, "scrollView6"));      //滚动图消耗；
    m_scrollView1->setVisible(false);
    m_scrollView2->setVisible(false);
    m_scrollView3->setVisible(false);
    m_scrollView4->setVisible(false);
    m_scrollView5->setVisible(false);
    m_scrollView6->setVisible(false);
    
    scrollViewInit(m_scrollView1, m_goods,  m_slider1);
    scrollViewInit(m_scrollView2, m_hero,  m_slider2);
    scrollViewInit(m_scrollView3, m_equip,  m_slider3);
    scrollViewInit(m_scrollView4, m_equip,  m_slider4);
    scrollViewInit(m_scrollView5, m_prop,  m_slider5);
    scrollViewInit(m_scrollView6, m_hero,  m_slider6);
    
    
    //默认选项；
    CheckBox  *button1 = static_cast<CheckBox*>(Helper::seekWidgetByName(m_pNode, "checkBoxAll"));      //全部；
    checkBoxPress(button1);
    
    //按钮；
    buttonInit();

    
    return true;
}


void  UiDepot::geoodsClassify(){                     //=======物品分类；
    m_hero.clear();
    m_equip.clear();
    m_prop.clear();
    for(string temp:m_goods){
     int  type=getGoodsType(temp);  //1英雄，2技能， 3装备，4材料；
        
        switch (type) {
                
            case 0:{                           }  break;
            case 1:{  m_hero.push_back(temp);    }  break;
            case 2:{                            }  break;
            case 3:{  m_equip.push_back(temp);  }  break;
            case 4:{  m_prop.push_back(temp);    }  break;

            default:   break;
        }
    
    }

}



////////////////////////////////////////////////////////////
//初始化滚动图层；并添加精灵项

bool  UiDepot::scrollViewInit(ui::ScrollView* scrollView, vector<string>  goods, Slider*  &slider){       //============初始化滚动图层；并添加精灵项；(滚动图层,ID,滑块)
    
    int  lineNum=5;
    //获取滚动图层；
    scrollView->addEventListener(  CC_CALLBACK_2(UiDepot::scrollViewEvent,this)  );    //事件监听；
    
    //滚动图层里面的图层；
    Layout  *panelscrollView=(Layout*)(scrollView->getChildByName("panelScrollView"));
    
    //滑块；
    slider->setPercent(14);
    slider->addEventListener(CC_CALLBACK_2(UiDepot::sliderEvent, this));      //事件监听；
    

    //原始的一个项，
    Layout  *panelItem=(Layout*)(panelscrollView->getChildByName("panelItem"));
    Size  size=panelItem->getContentSize();
    
 
    //1设置滚动层高,
    int line=(int)(goods.size()/lineNum);
    if(goods.size()%lineNum!=0){ line+=1; }
    if (line<8) {                                                    //比显示窗小时；
        line=8;
        
       Layout*panelSlider=static_cast<Layout*>(Helper::seekWidgetByName(m_pNode,"panelSlider"));
       panelSlider->removeChild(slider);
       slider=nullptr;
    }

    
    float  panelHight=(line)*(size.height+9);                      //层高；
    float  panelWidth=panelscrollView->getContentSize().width;
   
    
    panelscrollView->setContentSize(Size(panelWidth,panelHight));    //设置层的大小；
    scrollView->setInnerContainerSize(Size(panelWidth,panelHight));  //设置滚动区的大小；和层一样大；
    
    
    //2增加精灵项；goods一个帐号里的英雄；
    panelItem->setPosition(Point(5,panelHight-size.height/2-55));   //原始项的位置；
    Point  heroPt=panelItem->getPosition();

    for(int  i=0;  i<goods.size();i++){
        Point  pt;
        pt.x=heroPt.x+(i%lineNum)*(size.width+2);
        pt.y=heroPt.y-(int(i/lineNum))*(size.height+4);

        
        Layout  *panelItem2=(Layout*)panelItem->clone();
        panelItem2->setVisible(true);
        panelItem2->setPosition(pt);
        panelscrollView->addChild(panelItem2,0,goods[i]);         //以ID号为名字；
        
        setItem(panelItem2, goods[i]);                            //-------------设置精灵项；
    }
    
    panelItem->setVisible(false);                                   //原始项，隐藏，
    
    return  true;
}



//设置项目；

void  UiDepot::setItem(Widget* imageItem ,string  itemID){              //设置一个英雄框；
    
    string str1="",          //头像，
          str2="";          //底框，
    
    //id类型；
    int  type=getGoodsType(itemID);  //1英雄，2技能， 3装备，4材料；
    
    switch (type) {
            
        case 0:{  }   break;
            
        case 1:
        {
            str1="hero/"+Account::sharedAccount()->m_heroProperty[  atoi(itemID.c_str()) ].table.hero_icon;
            str2=getQualityFrame1(rand()%8);

        }
            break;
            
        case 2:{  }     break;
            
        case 3:
        {
            str1="equip/"+Account::sharedAccount()->m_equipProperty[  atoi(itemID.c_str()) ].table.equip_icon;
            str2=getQualityFrame3(rand()%8);

        }
            break;
            
        case 4:
        {
            str1="prop/"+Account::sharedAccount()->m_propProperty[  atoi(itemID.c_str()) ].table.item_icon;
            str2=getQualityFrame1(rand()%8);

        }
            break;
            
        default:     break;
    }
    
    //设置项；
    
    ImageView  *imageHead=(ImageView*)imageItem->getChildByName("imageHead");
    if(type==1){imageHead->setScale(0.9);}                                        //英雄的头像大些；
    imageHead->loadTexture(str1,TextureResType::PLIST);
    
    Button  *buttonHead=(Button*)imageItem->getChildByName("buttonHead");
    buttonHead->loadTextureNormal(str2,TextureResType::PLIST);
    buttonHead->setName(itemID);
    buttonHead->addTouchEventListener(CC_CALLBACK_2(UiDepot::buttonEvent, this));    //按钮响应；
    
}


////////////////////////////////////
//控件响应事件；


void  UiDepot::sliderEvent(Ref *pSender, Slider::EventType type){    //滑块响应函数，控制滚动层；
    
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        
        Slider* slider = dynamic_cast<Slider*>(pSender);    //滑块在15到85之间滑动；
        int percent = slider->getPercent();
        if (percent<14) {  percent=14;slider->setPercent(14);}
        if (percent>86) { percent=86;slider->setPercent(86);}
        percent =percent-15;
        //m_percent=percent;
        percent=percent*100/70;
        
        //
        if (slider==m_slider1) {  m_scrollView1->scrollToPercentVertical(percent, 0.2, true);  }
        else if (slider==m_slider2) {  m_scrollView2->scrollToPercentVertical(percent, 0.2, true);  }
        else if (slider==m_slider3) {  m_scrollView3->scrollToPercentVertical(percent, 0.2, true);  }
        else if (slider==m_slider4) {  m_scrollView4->scrollToPercentVertical(percent, 0.2, true);  }
        else if (slider==m_slider5) {  m_scrollView5->scrollToPercentVertical(percent, 0.2, true);  }
        else if (slider==m_slider6) {  m_scrollView6->scrollToPercentVertical(percent, 0.2, true);  }
        log("slider->getName() ====+++++++++++++++++++++++=%s",slider->getName().c_str());
    }
    
}


void  UiDepot::scrollViewEvent(Ref *pSender, ui::ScrollView::EventType type){   //====滚动层响应函数，控制滑块；；
    
    ui::ScrollView* scrollView=static_cast<ui::ScrollView*>(pSender);
    if(!scrollView){log("ScrollView  is  NULL"); return;}
    
    Slider  *slider;
    if (scrollView==m_scrollView1) { slider=m_slider1;    }
    else if (scrollView==m_scrollView2) { slider=m_slider2;    }
    else if (scrollView==m_scrollView3) { slider=m_slider3;    }
    else if (scrollView==m_scrollView4) { slider=m_slider4;    }
    else if (scrollView==m_scrollView5) { slider=m_slider5;    }
    else if (scrollView==m_scrollView6) { slider=m_slider6;    }

    if (m_percent<15) {  m_percent=15;slider->setPercent(15);}
    if (m_percent>85) { m_percent=85;slider->setPercent(85);}
    
    if(slider!=NULL){
    switch (type) {
        case ui::ScrollView::EventType::SCROLLING:        //滚动过程中有好多次响应；
        {
            Point  pt=scrollView->getInnerContainer()->getPosition();
            Size  size=scrollView->getInnerContainer()->getContentSize();
            float  percentScroll=(size.height+pt.y)/size.height*70;
            slider->setPercent(percentScroll);
            
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
    
}





////////////////////////////////////////
////////////////////////////////////////
//按钮

bool  UiDepot::buttonInit(){
    
    Button  *buttonClose = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonClose"));           //关闭按钮；
    if (!buttonClose){ log("UiDepot::no-buttonClose");return false;}
    buttonClose->addTouchEventListener(CC_CALLBACK_2(UiDepot::buttonEvent, this));
    
    
    CheckBox  *button1 = static_cast<CheckBox*>(Helper::seekWidgetByName(m_pNode, "checkBoxAll"));      //全部；
    if (!button1){ log("UiDepot::no-checkBoxAll");return false; }
    button1->addEventListener(CC_CALLBACK_2(UiDepot::checkBoxEvent, this));
    
    CheckBox  *button2 = static_cast<CheckBox*>(Helper::seekWidgetByName(m_pNode, "checkBoxChip"));      //碎片；
    if (!button2){ log("UiDepot::no-checkBoxChip");return false; }
    button2->addEventListener(CC_CALLBACK_2(UiDepot::checkBoxEvent, this));
    
    CheckBox  *button3 = static_cast<CheckBox*>(Helper::seekWidgetByName(m_pNode, "checkBoxEquip"));      //装备；
    if (!button3){ log("UiDepot::no-checkBoxEquip");return false; }
    button3->addEventListener(CC_CALLBACK_2(UiDepot::checkBoxEvent, this));
    
    CheckBox  *button4 = static_cast<CheckBox*>(Helper::seekWidgetByName(m_pNode, "checkBoxEquipChip"));   //装碎；
    if (!button4){ log("UiDepot::no-checkBoxEquipChip");return false; }
    button4->addEventListener(CC_CALLBACK_2(UiDepot::checkBoxEvent, this));
    
    CheckBox  *button5 = static_cast<CheckBox*>(Helper::seekWidgetByName(m_pNode, "checkBoxExpend"));      //消耗；
    if (!button5){ log("UiDepot::no-checkBoxExpend");return false; }
    button5->addEventListener(CC_CALLBACK_2(UiDepot::checkBoxEvent, this));
    
    CheckBox  *button6 = static_cast<CheckBox*>(Helper::seekWidgetByName(m_pNode, "checkBoxHead"));      //头像；
    if (!button6){ log("UiDepot::no-ccheckBoxHead");return false; }
    button6->addEventListener(CC_CALLBACK_2(UiDepot::checkBoxEvent, this));
    
    
    return  true;
    
}


void  UiDepot::buttonEvent(Ref *pSender, Widget::TouchEventType type)             //按钮响应函数；
{
    
    Button*  button=dynamic_cast<Button*>(pSender);
    string   str=button->getName();
    string  str1="buttonClose";

    
    switch (type)
    {
        case  Widget::TouchEventType::ENDED:
        {
            if (str==str1) {
                CC_SAFE_RETAIN(this);
                this->removeFromParent();
            }
 
            
        }
            break;
            
        default:      break;
    }
}





void  UiDepot::checkBoxEvent(Ref *pSender, CheckBox::EventType    type)             //复选响应函数；
{


    switch (type)
    {
        case  CheckBox::EventType::SELECTED:
        {
   
                checkBoxPress(pSender);        //-----复选选项卡；
  
        }
            break;
            
        case  CheckBox::EventType::UNSELECTED:
        {
 
                checkBoxPress(pSender);        //-----复选选项卡；
 
        }
            break;
            
        default:      break;
    }
    
   
    
}


void  UiDepot::checkBoxPress(Ref *pSender){    //====复选选项卡；
    
    if (!pSender) {   return;  }
    
    Layout  *panelCheckBox = static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelCheckBox"));      //；
    
    CheckBox  *button1 = panelCheckBox->getChildByName<CheckBox*>( "checkBoxAll");      //全部；
    CheckBox  *button2 = panelCheckBox->getChildByName<CheckBox*>("checkBoxChip");      //碎片；
    CheckBox  *button3 = panelCheckBox->getChildByName<CheckBox*>( "checkBoxEquip");      //装备；
    CheckBox  *button4 = panelCheckBox->getChildByName<CheckBox*>("checkBoxEquipChip");   //装碎；
    CheckBox  *button5 = panelCheckBox->getChildByName<CheckBox*>( "checkBoxExpend");      //消耗；
    CheckBox  *button6 = panelCheckBox->getChildByName<CheckBox*>( "checkBoxHead");      //头像；
    
    
    Text  *text1 = panelCheckBox->getChildByName<Text*>( "textAll");
    Text  *text2 = panelCheckBox->getChildByName<Text*>( "textChip");
    Text  *text3 = panelCheckBox->getChildByName<Text*>( "textEquip");
    Text  *text4 = panelCheckBox->getChildByName<Text*>( "textEquipChip");
    Text  *text5 = panelCheckBox->getChildByName<Text*>( "textExpend");
    Text  *text6 = panelCheckBox->getChildByName<Text*>( "textHead");
 
    
    
    CheckBox *  button=dynamic_cast<CheckBox *>(pSender);
    string   str=button->getName();
    
    string  str1="checkBoxAll";
    string  str2="checkBoxChip";
    string  str3="checkBoxEquip";
    string  str4="checkBoxEquipChip";
    string  str5="checkBoxExpend";
    string  str6="checkBoxHead";
    
    if (str==str1) {
        
        checkBoxSetTure(button1,text1,m_slider1, m_scrollView1);

    }
    else if(str==str2){
       checkBoxSetTure(button2,text2,m_slider2, m_scrollView2);
    }
    
    else if(str==str3){
        checkBoxSetTure(button3,text3,m_slider3, m_scrollView3);
    }
    
    else if(str==str4){
        checkBoxSetTure(button4,text4,m_slider4, m_scrollView4);
    }
    
    else if(str==str5){
        checkBoxSetTure(button5,text5,m_slider5, m_scrollView5);
    }
    else if(str==str6){
        checkBoxSetTure(button6,text6,m_slider6, m_scrollView6);
    }
    
    
}

void  UiDepot::checkBoxSetTure(CheckBox  *button,Text  *text,Slider*   slider, ui::ScrollView*  scrollView){


    Color3B  colorShow=Color3B(255, 237, 222);
    Color3B  colorHide=Color3B(46, 28, 8);
    
    //按下的；
    button->setSelectedState(true);         //复选框实现单选框的效果；
    text->setColor(colorShow);
    scrollView->setVisible(true);   scrollView->scrollToTop(0.2, true);
    if(slider!=nullptr){  slider->setVisible(true); slider->setPercent(15);}
    
    //前面的；
    if(m_buttonPre!=nullptr&&button!=m_buttonPre){
        m_buttonPre->setSelectedState(false);
        m_textPre->setColor(colorHide);
        m_scrollViewPre->setVisible(false);
        if(m_sliderPre){  m_sliderPre->setVisible(false); }
    }
    //前面的重新赋值；
    m_buttonPre=button;
    m_textPre=text;
    m_scrollViewPre=scrollView;
    m_sliderPre=slider;
}


void UiDepot::onEnter()
{
    Layer::onEnter();
}

void UiDepot::onExit()
{
    Layer::onExit();
}





