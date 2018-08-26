/**********************************************
经验界面；



 **********************************************/

#include "UiExperience.h"

using namespace cocos2d::ui;


UiExperience::UiExperience(){
    
    m_pNode=nullptr;
    m_scrollView=nullptr;
    m_slider=nullptr;
    m_buttonPre=nullptr;
    
    
}


UiExperience::~UiExperience(){
    m_hero.clear();
    m_heroProperty.clear();
}



bool UiExperience::init()
{
    if ( !UiBase::init() )  {      return false;    }

   // m_sliderNo=true;
    //界面；
    m_pNode = GUIReader::getInstance()->widgetFromJsonFile("uiExperience.ExportJson");
    m_pNodeBase->addChild(m_pNode);
    m_pNode->setTouchEnabled(false);
    
    //
    m_pNodeBase->getChildByName("buttonClose")->setVisible(false);
    Helper::seekWidgetByName(m_pNodeBase,"imageTitle")->setVisible(false);
    

    //一个账号里的英雄；
   
    m_hero=Account::sharedAccount()->m_hero;
    m_heroProperty=Account::sharedAccount()->m_heroProperty;
    
    
    //滑块；
    m_slider=static_cast<Slider*>(Helper::seekWidgetByName(m_pNode,"slider"));
    m_slider->setPercent(14);
    m_slider->addEventListener(CC_CALLBACK_2(UiExperience::sliderEvent, this));      //事件监听；
    
    
    //初始化滚动图层；并添加精灵项；
    m_scrollView=static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode,"scrollViewSet"));
    if (!m_scrollView){ log("scrollView  error!");  return false; }
    m_scrollView->addEventListener(  CC_CALLBACK_2(UiExperience::scrollViewEvent,this)  );    //事件监听；
    
    scrollViewInit();

    //按钮；
    buttonInit();
    
    

    
    return true;
}




//////////////////////////////
//初始化滚动图层；并添加精灵项

bool  UiExperience::scrollViewInit(){                    //============初始化滚动图层；并添加精灵项；

   
    //滚动图层里面的图层；
    Layout  *panelSet=static_cast<Layout*>(Helper::seekWidgetByName(m_scrollView,"panelSet"));
    
    //原始的一个项，隐藏，
    Layout  *panelItem=static_cast<Layout*>(Helper::seekWidgetByName(panelSet,"panelItem"));
    Size  heroSize=panelItem->getContentSize();
    

    //设置滚动层
    int line=(int)(m_hero.size()/2);
    if(m_hero.size()%2==1){ line+=1; }
    if (line<5) {                                            //比显示窗小时；
        line=5;
        m_slider->setVisible(false);
    }
    

    float  panelHight=(line)*(heroSize.height+9);                      //层高；
    float  panelWidth=panelSet->getContentSize().width;
    panelSet->setContentSize(Size(panelWidth,panelHight));              //设置层的大小；
    m_scrollView->setInnerContainerSize(Size(panelWidth,panelHight));   //设置滚动区的大小；和层一样大；
    
    
    //增加精灵项；m_hero一个帐号里的英雄；
    panelItem->setPosition(Point(5,panelHight-heroSize.height/2-100));   //原始项的位置；
    Point  heroPt=panelItem->getPosition();
    
    for(int  i=0;  i<m_hero.size();i++){
        Point  pt;
        
        pt.x=heroPt.x+(i%2)*(heroSize.width+2);
        pt.y=heroPt.y-(int(i/2))*(heroSize.height+8);
        
        Layout  *panelItem2=(Layout*)panelItem->clone();
        panelItem2->setVisible(true);
        panelItem2->setPosition(pt);
        
        panelSet->addChild(panelItem2,0,m_hero[i]);         //以ID号为名字；
        
        setItem(panelItem2, m_hero[i]);                    //-------------设置精灵项；
    }
   
    panelItem->setVisible(false);                                   //原始项，隐藏，
    
  return  true;
}



//设置项目；

void  UiExperience::setItem(Widget* imageItem ,string  ID){              //设置一个英雄框；
    
    
    //设置到像框；
    setHeadBK(imageItem,ID);
    setHead(imageItem, ID);
    setStar(imageItem,4);
    setLevel(imageItem,68);
    setHeroName(imageItem,ID,8);
    setProgress(imageItem,ID);


    
    
}




void  UiExperience::setHeadBK(Widget* pWidget,string ID){        //设置底框；tag 100, 101
    
    //头像的底框是个按钮；
    string  str2;
    str2=getQualityFrame1(rand()%8);
    
    Button  *buttonHead=static_cast<Button*>(Helper::seekWidgetByName(pWidget,"buttonHead"));
    buttonHead->loadTextureNormal(str2,TextureResType::PLIST);
    buttonHead->setTag(100);
    //buttonHead->addTouchEventListener(CC_CALLBACK_2(UiExperience::buttonEvent, this));
    
    //整个项的底框是个按钮；
    Button  *buttonImage=static_cast<Button*>(Helper::seekWidgetByName(pWidget,"buttonItem"));
    buttonImage->setName(ID);             //把按钮名字调成ID号；
    buttonImage->setTag(101);
    buttonImage->addTouchEventListener(CC_CALLBACK_2(UiExperience::buttonEvent, this));
    
}


void  UiExperience::setHead(Widget* pWidget, string ID){       //设置头像；
    string  str1;
    str1="hero/"+m_heroProperty[atoi(ID.c_str())].table.hero_icon;

    
    ImageView  *imageHead=static_cast<ImageView*>(Helper::seekWidgetByName(pWidget,"imageHead"));
    imageHead->loadTexture(str1,TextureResType::PLIST);
    
}





void  UiExperience::setStar(Widget * pWidget,int starLevel){      //====设置星级；
    

    
    Button  *buttonHead=static_cast<Button*>(Helper::seekWidgetByName(pWidget,"buttonHead"));
    Point  pt= buttonHead->getPosition();
    pt.y=pt.y-(buttonHead->getContentSize().height/2);
    
    
    ImageView  *imageStar1=static_cast<ImageView*>(Helper::seekWidgetByName(pWidget,"imageStar"));
    float x=imageStar1->getContentSize().width;
    
    if(starLevel%2==0){                                  //偶数星时要移位，使它中间对齐；
        pt.x=pt.x+x/2;
        imageStar1->setPositionX(pt.x);
    }
    
    for(int  i=1;i<starLevel; i++){
        ImageView*  imageStar2=(ImageView*)imageStar1->clone();
        if(i%2==0){
            imageStar2->setPositionX(pt.x+(i/2)*x+2);
        }
        else{
            imageStar2->setPositionX(pt.x-(i+1)/2*x-2);
            
        }
        imageStar1->getParent()->addChild(imageStar2,1,11);
    }
    
}




void  UiExperience::setLevel(Widget * pWidget,int  level){       //====设置等级；
    
    Text  *textLevel=static_cast<Text*>(Helper::seekWidgetByName(pWidget,"text4"));
    string  str="LV"+to_string(level);
    textLevel->setString(str);
    
    Text  *textLeve2=static_cast<Text*>(Helper::seekWidgetByName(pWidget,"text2"));
    string  str2=to_string(level)+ "级";
    textLeve2->setString(str2);
    
}

void  UiExperience::setHeroName(Widget * pWidget, string  ID, int  quality){       //设置名字；
    
    string name=m_heroProperty[(atoi(ID.c_str()))].table.hero_name;
    string  str=name+"+"+to_string(quality);
    
    Text  *textName=static_cast<Text*>(Helper::seekWidgetByName(pWidget,"text1"));
    textName->setString(str);
    
    
}

void  UiExperience::setProgress(Widget * pWidget,  string  ID){       //=====设置战力；
    
    LoadingBar  *loadingBar=static_cast<LoadingBar*>(Helper::seekWidgetByName(pWidget,"ProgressBar"));
    loadingBar->setPercent(40);
    

    string  str="1200/3000";
    Text  *textName=static_cast<Text*>(Helper::seekWidgetByName(pWidget,"text3"));
    textName->setString(str);
    
    
}







////////////////////////////////////
//控件响应事件；


void  UiExperience::sliderEvent(Ref *pSender, Slider::EventType type){    //===滑块响应函数，控制滚动层；
    
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
 
        Slider* slider = dynamic_cast<Slider*>(pSender);    //滑块在15到85之间滑动；
        int percent = slider->getPercent();
        if (percent<14) {  percent=14;slider->setPercent(14);}
        if (percent>86) { percent=86;slider->setPercent(86);}
        percent =percent-15;
        //m_percent=percent;
        percent=percent*100/70;
        
        ui::ScrollView* scrollViewHero=static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode,"scrollViewSet"));
        scrollViewHero->scrollToPercentVertical(percent, 0.2, true);
   
    }

}


void  UiExperience::scrollViewEvent(Ref *pSender, ui::ScrollView::EventType type){   //====滚动层响应函数，控制滑块；；
    

    if (m_percent<15) {  m_percent=15;m_slider->setPercent(15);}
    if (m_percent>85) { m_percent=85;m_slider->setPercent(85);}
    
    
    switch (type) {
        case ui::ScrollView::EventType::SCROLLING:        //滚动过程中有好多次响应；
        {
            Point  pt=m_scrollView->getInnerContainer()->getPosition();
            Size  size=m_scrollView->getInnerContainer()->getContentSize();
            
            float  percentScroll=(size.height+pt.y)/size.height*70;
            m_slider->setPercent(percentScroll);
            //log("percentScroll ====+++++++++++++++++++++++=%f",percentScroll);
           // log("scrollViewHero pt =====%f,y====%f",pt.x, pt.y);
            
            
        }
            break;
            
        case ui::ScrollView::EventType::SCROLL_TO_TOP:     //到达顶点，只是一次响应；
        {
            //log("slider  top =====d");
            
            m_slider->setPercent(14);
        }
            break;
            
        case ui::ScrollView::EventType::SCROLL_TO_BOTTOM:    //到达底点；
        {
            m_slider->setPercent(86);
            
            //log("slider bottom =====d");
        }
            break;
            
            
        default:
            break;
    }

    
}




/////////////////////
//按钮

bool  UiExperience::buttonInit(){
    
    
    
    Button  *buttonBack = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonBack"));           //返回按钮；
    if (!buttonBack){ log("buttonBack  ----error");return false; }
    buttonBack->addTouchEventListener(CC_CALLBACK_2(UiExperience::buttonEvent, this));


   
    
    return  true;

}



void  UiExperience::buttonEvent(Ref *pSender, Widget::TouchEventType type)             //=====按钮响应函数；
{
    Button*  button=dynamic_cast<Button*>(pSender);
    
    string  str=button->getName();
    string  str1="buttonBack";
    
    
    switch (type)
    {
        case  Widget::TouchEventType::ENDED:
        {
            if (str==str1) {
                CC_SAFE_RETAIN(this);
                this->removeFromParent();
            }
            else if(button->getTag()==101){            //项的TAG，名字已经改成了ID;
                if(m_buttonPre){
                    m_buttonPre->loadTextureNormal("ui_jingyan_04.png",TextureResType::PLIST);
                    m_buttonPre->loadTexturePressed("ui_jingyan_01.png",TextureResType::PLIST);
                }
                
                button->loadTextureNormal("ui_jingyan_01.png",TextureResType::PLIST);
                button->loadTexturePressed("ui_jingyan_04.png",TextureResType::PLIST);
                m_buttonPre=button;
                MessageBox(str.c_str(), "ddd");
            
            }
            
  
        }
            break;
      
        default:
            break;
    }
    
    
    
    
}




void UiExperience::onEnter()
{
    Layer::onEnter();
}

void UiExperience::onExit()
{
    Layer::onExit();
}

