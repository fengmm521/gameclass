/**********************************************
 英雄集界面；


 没有使用#include "Account.h"，需要修改；
 **********************************************/

#include "UiHeroSet.h"

using namespace cocos2d::ui;


bool UiHeroSet::init()
{
    if ( !UiBase::init() )  {      return false;    }

   // m_sliderNo=true;
    //界面；
    m_pNode = GUIReader::getInstance()->widgetFromJsonFile("uiHeroSet.ExportJson");
    m_pNodeBase->addChild(m_pNode);
    m_pNode->setTouchEnabled(false);
    
    //滑块；
    m_slider=static_cast<Slider*>(Helper::seekWidgetByName(m_pNode,"slider"));
    m_slider->setPercent(0);
    m_slider->addEventListener(CC_CALLBACK_2(UiHeroSet::sliderEvent, this));      //事件监听；
    
    //获取滚动图层；
    m_scrollViewHero=static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode,"scrollViewSet"));
    m_scrollViewHero->addEventListener(  CC_CALLBACK_2(UiHeroSet::scrollViewEvent,this)  );    //事件监听；
    
    
    //一个帐号里的英雄；
    m_string.push_back("1001");
    m_string.push_back("1002");
    m_string.push_back("1003");
    m_string.push_back("1004");
    m_string.push_back("1010");
    m_string.push_back("1012");
    m_string.push_back("1501");
    m_string.push_back("1502");
    m_string.push_back("1503");
    
    m_string.push_back("1001");
    m_string.push_back("1002");
    m_string.push_back("1003");
    m_string.push_back("1004");
    
    
    //一个英雄里的装备；
    m_equip.push_back("300001");
    m_equip.push_back("300010");
    m_equip.push_back("300019");
    m_equip.push_back("300028");
    m_equip.push_back("300037");
    m_equip.push_back("300046");
    

    //初始化滚动图层；并添加精灵项；
    scrollViewInit();

    //按钮；
    //buttonInit();
    
    

    
    return true;
}




//////////////////////////////
//初始化滚动图层；并添加精灵项

bool  UiHeroSet::scrollViewInit(){                    //============初始化滚动图层；并添加精灵项；
    

   
    //滚动图层里面的图层；
    Layout  *panelHero=static_cast<Layout*>(Helper::seekWidgetByName(m_pNode,"panelSet"));
    
    //原始的一个项，隐藏，
    Layout  *panelItem=static_cast<Layout*>(Helper::seekWidgetByName(m_pNode,"panelItem"));
    Size  heroSize=panelItem->getContentSize();
    
  
    
    
    //设置滚动层
    int line=(int)(m_string.size()/2);
    if (m_string.size()/2<5) {  //比显示窗小时；
        line=5;
        m_slider->setVisible(false);
    }
    
    float  panelHight=(line+1)*(heroSize.height+9);       //层高；
    float  panelWidth=panelHero->getContentSize().width;
    m_panelHight=panelHight;
    
    panelHero->setContentSize(Size(panelWidth,panelHight));    //设置层的大小；
    m_scrollViewHero->setInnerContainerSize(Size(panelWidth,panelHight));  //设置滚动区的大小；和层一样大；
    
    
    //增加精灵项；m_string一个帐号里的英雄；
    panelItem->setPosition(Point(5,panelHight-heroSize.height/2-100));   //原始项的位置；
    Point  heroPt=panelItem->getPosition();
    
  
    for(int  i=0;  i<m_string.size();i++){
        Point  pt;
        
        pt.x=heroPt.x+(i%2)*(heroSize.width+2);
        pt.y=heroPt.y-(int(i/2))*(heroSize.height+8);
        
        //log("x=====%d",(int)m_string.size());
        //log("y=%d",(int(i/6)));
        
        Layout  *panelItem2=(Layout*)panelItem->clone();
        panelItem2->setVisible(true);
        panelItem2->setPosition(pt);
        panelHero->addChild(panelItem2,0,m_string[i]);         //以ID号为名字；
        
        setItem(panelItem2, m_string[i]);    //-------------设置精灵项；
    }
   
    panelItem->setVisible(false);                                   //原始项，隐藏，
    
  return  true;
}



//设置项目；

void  UiHeroSet::setItem(Widget* imageItem ,string  heroID){              //设置一个英雄框；
    
    //英雄的属性表；
    
    m_mapDataST = LocalDataManger::sharedLocalDataManger()->getConfigtab_card_attribute_sysDataST(atoi(heroID.c_str()));
    
    
    //英雄属性赋值；固定；
    m_heroProperty.heroID=m_mapDataST.ID;                    //英雄ID
    m_heroProperty.headBK="ui_c_frame3_1.png";               //头像框；  品质3；
    m_heroProperty.headImage="hero/"+m_mapDataST.hero_icon;          //头像；
    m_heroProperty.starLevel=3;                              //星级；
    m_heroProperty.level=68;                                 //等级；
    m_heroProperty.heroName=m_mapDataST.hero_name;           //名字；
    m_heroProperty.sword=8150;                               //战力；
    

    
    
    //设置到像框；
    setHeadBK(imageItem,m_heroProperty.headBK);
    setHead(imageItem, m_heroProperty.headImage);
    setStar(imageItem,m_heroProperty.starLevel);
    setLevel(imageItem,m_heroProperty.level);
    setHeroName(imageItem,m_heroProperty.heroName,3);
    setSword(imageItem,m_heroProperty.sword);
    setEquip(imageItem, m_equip);
   // setSigned(imageItem,m_heroProperty.heroSigne);
    
    
}




void  UiHeroSet::setHeadBK(Widget* pWidget,string frameLevel){        //设置底框；tag 100, 101
    
    //头像的底框是个按钮；
    Button  *buttonHead=static_cast<Button*>(Helper::seekWidgetByName(pWidget,"buttonHead"));
    buttonHead->loadTextureNormal(frameLevel,TextureResType::PLIST);
    buttonHead->setTag(100);
    buttonHead->addTouchEventListener(CC_CALLBACK_2(UiHeroSet::buttonEvent, this));
    
    //整个项的底框是个按钮；
    Button  *buttonImage=static_cast<Button*>(Helper::seekWidgetByName(pWidget,"buttonItem"));
    buttonImage->setName(to_string(m_heroProperty.heroID));             //把按钮名字调成ID号；
    buttonImage->setTag(101);
    buttonImage->addTouchEventListener(CC_CALLBACK_2(UiHeroSet::buttonEvent, this));
    
}


void  UiHeroSet::setHead(Widget* pWidget, string headImage){       //设置头像；
    
    ImageView  *imageHead=static_cast<ImageView*>(Helper::seekWidgetByName(pWidget,"imageHead"));
    imageHead->loadTexture(headImage,TextureResType::PLIST);
    
}




void  UiHeroSet::setStar(Widget * pWidget,int starLevel){      //设置星级；tag 11;
    
 
    
    ImageView  *imageStar1=static_cast<ImageView*>(Helper::seekWidgetByName(pWidget,"imageStar"));
    float x=imageStar1->getContentSize().width;
    Point  pt=imageStar1->getPosition();
    
    if(starLevel==0){
        imageStar1->setVisible(false);
    }
    
    for(int  i=2;i<=starLevel; i++){
        ImageView*  imageStar2=(ImageView*)imageStar1->clone();
        imageStar2->setPositionX(pt.x+(i-1)*x+2);
        imageStar1->getParent()->addChild(imageStar2,1,11);
    }
    
    
}



void  UiHeroSet::setLevel(Widget * pWidget,int  level){       //设置等级；
    
    Text  *textLevel=static_cast<Text*>(Helper::seekWidgetByName(pWidget,"textLevel"));
    string  str="LV"+to_string(level);
    textLevel->setString(str);
    
    
}

void  UiHeroSet::setHeroName(Widget * pWidget, string  name, int  quality){       //设置名字；
    
    Text  *textName=static_cast<Text*>(Helper::seekWidgetByName(pWidget,"textName"));
    string  str=name+"+"+to_string(quality);
    textName->setString(str);
    
    
}

void  UiHeroSet::setSword(Widget * pWidget,  int  sword){       //设置战力；
    
    Text  *textSword=static_cast<Text*>(Helper::seekWidgetByName(pWidget,"textSword"));
    string  str="战斗力:"+to_string(sword);
    textSword->setString(str);
    
    
}



void  UiHeroSet::setEquip(Widget * pWidget, vector<string>  equip){  //设置装备；tag  20;
    
        
     //框；
     ImageView  *imageEquipBK1=static_cast<ImageView*>(Helper::seekWidgetByName(pWidget,"imageEquipBK1"));
     float   x=imageEquipBK1->getContentSize().width;
     x=0.7*x;              //缩放了；获取的宽度还是原来的大小；
     log("width=====%f", x);
     Point  pt=imageEquipBK1->getPosition();
    
    
    //头像；
     ImageView  *imageEquip1=static_cast<ImageView*>(Helper::seekWidgetByName(pWidget,"imageEquip1"));
    
    
    for (int i=1; i<7; i++) {
        //框；
        ImageView  *imageEquipBK2=(ImageView*)imageEquipBK1->clone();
        imageEquipBK2->setPosition(imageEquipBK1->getPosition());
        imageEquipBK2->setPositionX(pt.x+(i-1)*(x+4));
        imageEquipBK1->getParent()->addChild(imageEquipBK2,0,20);
        
        //头像；
        ImageView  *imageEquip2=(ImageView*)imageEquip1->clone();
        
        m_equipST = LocalDataManger::sharedLocalDataManger()->getConfigtab_equipbase_sysDataST(atoi(m_equip[i-1].c_str()));   ////////////装备的属性表；
        log("equip===+++++%s", m_equipST.equip_icon.c_str());
        string  str="equip/"+m_equipST.equip_icon;                                     //装备是放在文件夹里的，要加文件夹名；
        imageEquip2->loadTexture(str.c_str(),TextureResType::PLIST);                      //设置装备图片；
        
        
        imageEquip2->setPosition(imageEquipBK2->getPosition());
        log("width===+++++%d", i);
        imageEquipBK2->getParent()->addChild(imageEquip2,0,21);
    }
    
    
    imageEquip1->setVisible(false);              //克隆前不能隐藏；
    imageEquipBK1->setVisible(false);
    
}

////////////////////////////////////
//控件响应事件；


void  UiHeroSet::sliderEvent(Ref *pSender, Slider::EventType type){    //滑块响应函数，控制滚动层；
    
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


void  UiHeroSet::scrollViewEvent(Ref *pSender, ui::ScrollView::EventType type){   //====滚动层响应函数，控制滑块；；
    
    ui::ScrollView* scrollViewHero=static_cast<ui::ScrollView*>(pSender);
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




/////////////////////
//按钮

bool  UiHeroSet::buttonInit(){
    
    
    
//    Button  *buttonBack = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonBack"));           //返回按钮；
//    if (!buttonBack){ return false; }
//    buttonBack->addTouchEventListener(CC_CALLBACK_2(UiHeroSet::buttonEvent, this));
//    

   
    
    return  true;

}



void  UiHeroSet::buttonEvent(Ref *pSender, Widget::TouchEventType type)             //按钮响应函数；
{
    Button*  button=dynamic_cast<Button*>(pSender);
    
    string  str="";
    if (button->getTag()==101) {
       str=button->getName();
    }
    if (button->getTag()==100){
        str=button->getParent()->getChildByTag(101)->getName();
    
    }
    
    
    switch (type)
    {
        case  Widget::TouchEventType::ENDED:
        {

            UiHeroDetail* herol = UiHeroDetail::create(str);
            this->addChild(herol);
  
        }
            break;
      
        default:
            break;
    }
    
    
    
    
}




void UiHeroSet::onEnter()
{
    Layer::onEnter();
}

void UiHeroSet::onExit()
{
    Layer::onExit();
}





/******************监听实例；
//init(){

//创建监听对象；
//    Layout *listenerLayer=Layout::create();
//    m_pNode->addChild(listenerLayer, 1000, "listenerLayer");
//
//    m_listener1=EventListenerTouchOneByOne::create();   //创建一个单点监听事件；
//    //listener1->setSwallowTouches(true);                   //设置事件屏蔽；
//    m_listener1->onTouchBegan=CC_CALLBACK_2(UiHeroSet::onTouchBegan,  this);
//    m_listener1->onTouchMoved=CC_CALLBACK_2(UiHeroSet::onTouchMoved,  this);
//    m_listener1->onTouchEnded=CC_CALLBACK_2(UiHeroSet::onTouchEnded,  this);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener1,  listenerLayer);
//}


//virtual bool  onTouchBegan (Touch  * touch,  Event*  event);
//virtual void  onTouchMoved (Touch  *touch,  Event * event);
//virtual void  onTouchEnded(Touch*  touch,  Event* event);

//Point   m_ptStart;                //随鼠标移动的精灵的开始位置；
//Point   m_ptEnd;                  //随鼠标移动的精灵的结束位置；



///////////////////////////////
//层监听事件；拖动加动画
//
////按下；
//bool  UiHeroSet::onTouchBegan (Touch  * touch,  Event*  event){
//
//    m_ptStart=touch->getLocation();
//
//    return  true;          //true事件传给moved和ended;不传给下一层；
//
//}
//
////移动；
//void  UiHeroSet::onTouchMoved (Touch  *touch,  Event * event){
//
//}
//
////松开；
//
//void  UiHeroSet::onTouchEnded(Touch*  touch,  Event* event){
//
//    m_ptEnd=touch->getLocation();
//    m_ptEnd=event->getCurrentTarget()->convertToWorldSpace(m_ptEnd);
//
//
//    //滚动图层控制滑块的位置；
//    if(m_scrollChangeSlider&&m_sliderNo){ // 留下的问题：滑块动的时候会使滚动层监听开启，使这个变量改成了TRUE,会执行这个函数；
//        ui::ScrollView* scrollViewHero=static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode,"scrollViewSet"));
//        if(!scrollViewHero){log("ScrollView  is  NULL"); return;}
//        Layout  *panelHero=static_cast<Layout*>(Helper::seekWidgetByName(scrollViewHero,"panelSet"));
//        if(!panelHero){log("ScrollView:panelHero  is  NULL"); return;}
//
//        Slider  *slider=static_cast<Slider*>(Helper::seekWidgetByName(m_pNode,"slider"));
//        if(!slider){log("Slider  is  NULL"); return;}
//
//
//        int  dis=(m_ptEnd.y-m_ptStart.y)/(m_panelHight-scrollViewHero->getContentSize().height)*70;
//        //int  dis=(m_ptEnd.y-m_ptStart.y)/m_panelHight*70;
//        m_percent=slider->getPercent();
//
//        if(m_sliderDirection){  //拖滑块时，也拖动了滚动层，方向相反；
//            m_percent-=dis;
//            m_sliderDirection=false;
//        }
//        else  {   m_percent+=dis;   }
//
//        if (m_percent<15) {  m_percent=15;}
//        if (m_percent>85) { m_percent=85;}
//        slider->setPercent(m_percent);
//
//        log("dis)dis)===########==%d",dis);
//        log("dis)dis)===###==%d",m_percent);
//
//        m_scrollChangeSlider=false;
//
//    }
//
//    m_sliderNo=true;
//
//}
//
//

*******************/

