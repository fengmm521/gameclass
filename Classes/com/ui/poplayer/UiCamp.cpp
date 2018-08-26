/**********************************************
 阵容界面；
 
 拖拉动画，和ScrollView案例；
 
 没有使用#include "Account.h"，需要修改；
 
 **********************************************/

#include "UiCamp.h"

#include "MainCityScence.h"

using namespace cocos2d::ui;

#define   TAGARMATURE   60

class UiArena;


UiCamp::UiCamp(){
    m_pNode=nullptr;                //UI界面；
    m_scrollView=nullptr;
    m_slider=nullptr;
    m_imageHero1=nullptr;
    m_imageHero2=nullptr;
    m_imageHero3=nullptr;
    m_imageHero4=nullptr;
    m_imageHero5=nullptr;
    
    m_imageHeroDel=nullptr;

    m_percent=15;

    
    //vector<bool>  m_heroStand;       //6个位上是否有站立的英雄；
    m_pressID="";                    //跟随鼠标移动的精灵的名字；
    m_listener1=NULL;               //层的监听事件；
    m_ptStart=Point(0,0);                //随鼠标移动的精灵的开始位置；
    m_ptEnd=Point(0,0);
    //
    m_type=0;
    
}

UiCamp::~UiCamp(){}


bool UiCamp::init()
{
    if ( !UiBase::init() )  {      return false;    }
    log("UiCamp::====init");
    //界面；
    m_pNodeBase->setVisible(false);          //隐藏父类界面；
    m_pNode = GUIReader::getInstance()->widgetFromJsonFile("uiCamp.ExportJson");
    this->addChild(m_pNode);
    //m_pNode->setTouchEnabled(false);
    
    //
    m_account=Account::sharedAccount();
    
    
    //一个帐号里的英雄；
    m_string.push_back("1001");
    m_string.push_back("1002");
    m_string.push_back("1003");
    m_string.push_back("1004");
    m_string.push_back("1008");
    m_string.push_back("1010");
    m_string.push_back("1012");
    m_string.push_back("1015");
    m_string.push_back("1029");
    

    
    
    //6个位上是否有站立的英雄；
    for(int i=0;i<6;i++){
        m_heroStand.push_back(false);
    }
   
    //自己的阵容；
    m_camp.clear();
    m_camp.push_back("1004");
    m_camp.push_back("1003");
    m_camp.push_back("1008");
    m_camp.push_back("1002");
    m_camp.push_back("1015");
    
    
    //滑块；
    m_slider=static_cast<Slider*>(Helper::seekWidgetByName(m_pNode,"slider"));
    m_slider->setPercent(15);
    m_slider->addEventListener(CC_CALLBACK_2(UiCamp::sliderEvent, this));      //事件监听；
    
    //滚动图层；
    m_scrollView=static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode,"scrollViewHero"));
    m_scrollView->addEventListener(  CC_CALLBACK_2(UiCamp::scrollViewEvent,this)  );    //事件监听；
    
    scrollViewInit();
    
    //5个上阵的位置；
    m_imageHero1=static_cast<ImageView*>(Helper::seekWidgetByName(m_pNode,"imageHero1"));
    m_imageHero2=static_cast<ImageView*>(Helper::seekWidgetByName(m_pNode,"imageHero2"));
    m_imageHero3=static_cast<ImageView*>(Helper::seekWidgetByName(m_pNode,"imageHero3"));
    m_imageHero4=static_cast<ImageView*>(Helper::seekWidgetByName(m_pNode,"imageHero4"));
    m_imageHero5=static_cast<ImageView*>(Helper::seekWidgetByName(m_pNode,"imageHero5"));
    initLocal();      //初始站位,
    
    
    //按钮；
    buttonInit();
    
    
    
    //创建监听对象；
    Layout *listenerLayer=Layout::create();
    m_pNode->addChild(listenerLayer, 100, "listenerLayer");
    
    m_listener1=EventListenerTouchOneByOne::create();   //创建一个单点监听事件；
    //listener1->setSwallowTouches(true);                   //设置事件屏蔽；
    m_listener1->onTouchBegan=CC_CALLBACK_2(UiCamp::onTouchBegan,  this);
    m_listener1->onTouchMoved=CC_CALLBACK_2(UiCamp::onTouchMoved,  this);
    m_listener1->onTouchEnded=CC_CALLBACK_2(UiCamp::onTouchEnded,  this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener1,  listenerLayer);
    
    //设置初始阵容；
    setCamp();
    
    
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//滚动图层;

void  UiCamp::scrollViewInit(){                      //初始化英雄的个数；

    //滚动图层里面的图层；
    Layout  *panelHero=static_cast<Layout*>(Helper::seekWidgetByName(m_scrollView,"panelHero"));
    
    //原始的一个项，隐藏，
    ImageView  *imageItem1=static_cast<ImageView*>(Helper::seekWidgetByName(panelHero,"imageItem1"));
    Size  heroSize=imageItem1->getContentSize();
   

    //设置滚动层
    int line=(int)(m_string.size()/5);
    if (m_string.size()/5<3) {                                         //比显示窗小时；
        line=2;
        m_slider->setVisible(false);
    }
    
    float  panelHight=(line+1)*(heroSize.height+80);
    float  panelWidth=panelHero->getContentSize().width;
    
    panelHero->setContentSize(Size(panelWidth,panelHight));            //设置层的大小；
    m_scrollView->setInnerContainerSize(Size(panelWidth,panelHight));  //设置滚动区的大小；和层一样大；
    
    imageItem1->setPositionY(panelHight-heroSize.height/2-50);         //设置第一个顶的位置；
    Point  heroPt=imageItem1->getPosition();

    //增加项；m_string一个帐号里的英雄；
    
    for(int  i=0;  i<m_string.size();i++){
        Point  pt;
        pt.x=heroPt.x+(i%5)*(heroSize.width+52);
        pt.y=heroPt.y-(int(i/5))*(heroSize.height+80);

        ImageView  *imageItem2=(ImageView  *)imageItem1->clone();
        imageItem2->setVisible(true);
        imageItem2->setPosition(pt);
        setImageItem(imageItem2 ,atoi(m_string[i].c_str()));             //----设置一个英雄框；
        panelHero->addChild(imageItem2,0,m_string[i]);
    }
   imageItem1->setVisible(false);                                     //原始的一个项，隐藏，
}


void  UiCamp::setImageItem(Widget* imageItem ,int  heroID){              //====设置一个英雄框；

    
    string str1="hero/"+Account::sharedAccount()->m_heroProperty[ heroID ].table.hero_icon;
    string str2=getQualityFrame1( heroID%8 );

    
    //头像
    ImageView  *imageHead=(ImageView*)imageItem->getChildByName( "imageHead");
    imageHead->loadTexture(str1,TextureResType::PLIST);
    //按钮框；
    Button  *buttonHead=(Button  *)imageItem->getChildByName( "buttonHead");
    buttonHead->loadTextureNormal(str2,TextureResType::PLIST);
    buttonHead->setName(to_string(heroID));         //把按钮名字调成ID号；
    buttonHead->addTouchEventListener(CC_CALLBACK_2(UiCamp::buttonEvent, this));

     //标记
    ImageView  *imageSigned=(ImageView*)imageItem->getChildByName("imageSigned");
    imageSigned->setVisible(false);

    //级别；
    setLevel(imageItem,88);    //+to_string(Account::sharedAccount()->m_heroProperty[ heroID ].table.hero_level);
    //星级；
    setStar(imageItem,4);
    

}


void  UiCamp::setLevel(Widget* pWidget,int level){

    Text  *textLevel=(Text*)pWidget->getChildByName("textLevel");
    textLevel->setVisible(true);
    if (level==0) {
        textLevel->setVisible(false);
    }
    string str3="LV"+to_string(level);
    textLevel->setString(str3);

    
}



void  UiCamp::setStar(Widget * pWidget,int starLevel){      //设置星级；
    
    //清空星；
    Vector<Node*>  star=pWidget->getChildren();
    for(Node* startmp:star){
        if (startmp->getTag()==11) {
            pWidget->removeChild(startmp);
        }
    
    }
    
    //
     Text* textLevel=static_cast<Text* >(Helper::seekWidgetByName(pWidget,"textLevel"));
     Point  pt = textLevel->getPosition();
     pt += Point(0, -10);
    
     ImageView  *imageStar1=static_cast<ImageView*>(Helper::seekWidgetByName(pWidget,"imageStar"));
    imageStar1->setVisible(true);
    float x=imageStar1->getContentSize().width;
    
    if(starLevel==0){ imageStar1->setVisible(false); return;    }
    
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




////////////////////////////////////////////////////////////////////////////////
//控件响应;

void  UiCamp::sliderEvent(Ref *pSender, Slider::EventType type){    //===滑块响应函数，控制滚动层；

    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {

        Slider* slider = dynamic_cast<Slider*>(pSender);    //滑块在15到85之间滑动；
        int percent = slider->getPercent();
        if (percent<15) {  percent=15;slider->setPercent(15);}
        if (percent>85) { percent=85;slider->setPercent(85);}
        percent =percent-15;
        //m_percent=percent;
        percent=percent*100/70;
        
        ui::ScrollView* scrollViewHero=static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode,"scrollViewHero"));
        scrollViewHero->scrollToPercentVertical(percent, 0.2, true);
        
  
    }

}


void  UiCamp::scrollViewEvent(Ref *pSender, ui::ScrollView::EventType type){   //====滚动层响应函数；


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
            //log("scrollViewHero pt =====%f,y====%f",pt.x, pt.y);
            
            
        }
            break;
            
        case ui::ScrollView::EventType::SCROLL_TO_TOP:     //到达顶点，只是一次响应；
        {
            log("slider  top =====d");
            
            m_slider->setPercent(14);
        }
            break;
            
        case ui::ScrollView::EventType::SCROLL_TO_BOTTOM:    //到达底点；
        {
            m_slider->setPercent(86);
            
            log("slider bottom =====d");
        }
            break;
            
            
        default:
            break;
    }

    
    
    
}




////////////////////////////////////////////////////////////////////////////////
//拖动英雄;
void  UiCamp::initLocal(){              //初始站位,
    
    setStar(m_imageHero1,0);         //设置星级；
    setLevel(m_imageHero1,0);
    
    setStar(m_imageHero2,0);         //设置星级；
    setLevel(m_imageHero2,0);
    
    setStar(m_imageHero3,0);         //设置星级；
    setLevel(m_imageHero3,0);
    
    setStar(m_imageHero4,0);         //设置星级；
    setLevel(m_imageHero4,0);
    
    setStar(m_imageHero5,0);         //设置星级；
    setLevel(m_imageHero5,0);
    
    
}

/////////站立的英雄；
bool  UiCamp::initStandHero(string heroID){  //===添加动画；
    
 
    if (!m_heroStand[0]) {

        setStandHero(m_imageHero1, heroID);     //-----
        m_heroStand[0]=true;
    }
    
    else if (!m_heroStand[1]) {

       setStandHero(m_imageHero2, heroID);
       m_heroStand[1]=true;
    }
    
    else if (!m_heroStand[2]) {

         setStandHero(m_imageHero3, heroID);
         m_heroStand[2]=true;
    }
    
    else if (!m_heroStand[3]) {

         setStandHero(m_imageHero4, heroID);
         m_heroStand[3]=true;
    }
    
    else if (!m_heroStand[4]) {

         setStandHero(m_imageHero5, heroID);
         m_heroStand[4]=true;
    }

    else{
        //MessageBox("出战英雄已经站满", "满员");
        return  false;
    }
    return  true;
}


void  UiCamp::setStandHero(Widget* imageHero, string heroID){
    
    int  str1=atoi(heroID.c_str());
    Configtab_card_attribute_sysDataST  m_mapDataST = LocalDataManger::sharedLocalDataManger()->getConfigtab_card_attribute_sysDataST(str1);
    
    //设置星级，等级；
    m_mapDataST.hero_star=4;            //
    m_mapDataST.hero_level=88;
    
    setStar(imageHero,m_mapDataST.hero_star);
    setLevel(imageHero,m_mapDataST.hero_level);
    
    //导入动画
    string  strPath=heroID+".ExportJson";
     
     ArmatureDataManager::getInstance()->addArmatureFileInfo(strPath.c_str());
     Armature *armature = Armature::create(heroID);
     armature->getAnimation()->playByIndex(0);
    
    
     //ImageView* imageStar=static_cast<ImageView*>(Helper::seekWidgetByName(imageHero,"imageStar"));
     Text* textLevel=static_cast<Text* >(Helper::seekWidgetByName(imageHero,"textLevel"));
     Point  pt = textLevel->getPosition();
     pt += Point(5, 25);
     //log("x=====%f;  y=====%f",pt.x, pt.y);
      armature->setPosition(pt);
    
     armature->setTag(TAGARMATURE);
     imageHero->addChild(armature,2,heroID);
    

    
  }


ImageView *   UiCamp::delStandHero(string heroID){     //===删除动画；
    
    if(heroID==""){ return   nullptr;}
    
    if (m_heroStand[0]) {
        
        Armature* armature=m_imageHero1->getChildByName<Armature*>((heroID));
        if (armature) {
            m_imageHero1->removeChildByName(heroID);  //删除动画；
           
            setSigned(heroID, false );            //----去掉标志
             m_heroStand[0]=false;
            
            setLevel(m_imageHero1,0);
            setStar(m_imageHero1,0);              //去掉星星；
            return m_imageHero1;                  //返回站台；
            
        }
    }
    
    if (m_heroStand[1]) {

        Armature* armature=m_imageHero2->getChildByName<Armature*>((heroID));
        if (armature) {
            m_imageHero2->removeChildByName(heroID);  //删除动画；
            setSigned(heroID, false );//----去掉标志
            m_heroStand[1]=false;
            
            setLevel(m_imageHero2,0);
            setStar(m_imageHero2,0);              //去掉星星；
            return m_imageHero2;                  //返回站台；
        }
    }
    
    if (m_heroStand[2]) {

        Armature* armature=m_imageHero3->getChildByName<Armature*>((heroID));
        if (armature) {
            m_imageHero3->removeChildByName(heroID);  //删除动画；
            setSigned(heroID, false );//----去掉标志
            m_heroStand[2]=false;
            
            setLevel(m_imageHero3,0);
            setStar(m_imageHero3,0);              //去掉星星；
            return m_imageHero3;                  //返回站台；
        }
    }
    
    if (m_heroStand[3]) {
        
        Armature* armature=m_imageHero4->getChildByName<Armature*>((heroID));
        if (armature) {
            m_imageHero4->removeChildByName(heroID);  //删除动画；
            setSigned(heroID, false );//----去掉标志
            m_heroStand[3]=false;
            
            setLevel(m_imageHero4,0);
            setStar(m_imageHero4,0);              //去掉星星；
            return m_imageHero4;                  //返回站台；
        }
    }
    
    if (m_heroStand[4]) {
        
        Armature* armature=m_imageHero5->getChildByName<Armature*>((heroID));
        if (armature) {
            m_imageHero5->removeChildByName(heroID);  //删除动画；
            setSigned(heroID, false );//----去掉标志
            m_heroStand[4]=false;
            
            setLevel(m_imageHero5,0);
            setStar(m_imageHero5,0);              //去掉星星；
            return m_imageHero5;                  //返回站台；
        }
    }
  
  return   nullptr;
}




void  UiCamp::replaceStandHero(string  heroID){   //====交换动画；


    replaceStandHero2(m_imageHero1, heroID,0);   //-----

    replaceStandHero2(m_imageHero2, heroID,1);

    replaceStandHero2(m_imageHero3, heroID,2);

    replaceStandHero2(m_imageHero4, heroID,3);

    replaceStandHero2(m_imageHero5, heroID,4);
    


}



void  UiCamp::replaceStandHero2(Widget* imageHero, string heroID,int i){

    Rect  r=imageHero->boundingBox();
    r.origin=imageHero->getParent()->convertToWorldSpace(r.origin);
    r.size.height+=50;
    
    if(r.containsPoint(m_ptEnd)){
        
        /////前面有的动画；
        if (m_heroStand[i]){
            
            //去掉标志；
            string oldHero=imageHero->getChildByTag(TAGARMATURE)->getName();
            setSigned(oldHero, false );//----去掉标志
    
            //删除动画；
            imageHero->removeChildByTag(TAGARMATURE,false);
            
            //移过来的站台上加上动画；
            if(m_imageHeroDel){
            setStandHero(m_imageHeroDel, oldHero); //---移过来的站台上加上动画；
            if (m_imageHeroDel==m_imageHero1) {   m_heroStand[0]=true; }
            if (m_imageHeroDel==m_imageHero2) {   m_heroStand[1]=true; }
            if (m_imageHeroDel==m_imageHero3) {   m_heroStand[2]=true; }
            if (m_imageHeroDel==m_imageHero4) {   m_heroStand[3]=true; }
            if (m_imageHeroDel==m_imageHero5) {   m_heroStand[4]=true; }
            setSigned(oldHero, true );             //----加上标志
                m_imageHeroDel=nullptr;
            }
            
        }
        
        
        ////后面加的动画；
        //加上动画；
        setStandHero(imageHero,heroID);
        m_heroStand[i]=true;

        //加上标志；
        setSigned(heroID.c_str(), true );//----加上标志

        
    }


}

 void  UiCamp::setSigned(string ID, bool  sig )//=====设置标志的显示否；
{
    Layout  *panelHero=static_cast<Layout*>(Helper::seekWidgetByName(m_pNode,"panelHero"));
    ImageView  *button=static_cast<ImageView*>(Helper::seekWidgetByName(panelHero,ID));
    ImageView  *imageSigned=static_cast<ImageView*>(Helper::seekWidgetByName(button,"imageSigned"));
    imageSigned->setVisible(sig);


}





void  UiCamp::pressCallback(float  dt){                 //长按定时器；//按下时在监听层生成一个动画；随鼠标移动，松开时删掉；
    
    this->unschedule(schedule_selector(UiCamp::pressCallback));
    
    /*
     //创建精灵；
     string  str=m_pressID+"_touxiang.png";                     //创建头像的精灵；按钮没有鼠标定位，层上加监听器才能定位；m_pressID是英雄ID;
     Sprite* sprite=Sprite::createWithSpriteFrameName(str);
     sprite->setPosition(m_ptStart);
     //sprite->setVisible(false);
     m_pNode->getChildByName("listenerLayer")->addChild(sprite,100, "pressHero");
     */
    
    m_imageHeroDel=delStandHero(m_pressID);  //----站位台上删除动画；
    
    //创建动画；
    Armature*  armature=getArmatrue(m_pressID);                                        //创建动画；
    if(armature){
      armature->setPosition(m_ptStart);                                                  //位置；
      m_pNode->getChildByName("listenerLayer")->addChild(armature,101, "pressHero2");    //加入监听层；
    }
    
    
    
}

string   UiCamp::getPressID(Point  pt)    //========点按位置区，获取动画ID,用来使上面的定时器有ID生成动画；
{
    string str="";
    Point  ppt(0,0);

    Rect  r;
    if(m_heroStand[0]){
        r=m_imageHero1->getChildByTag(TAGARMATURE)->boundingBox();
        r.origin=m_imageHero1->convertToWorldSpace(r.origin);
        if(r.containsPoint(pt)){ str=m_imageHero1->getChildByTag(TAGARMATURE)->getName();return  str; }
    }
    
    if(m_heroStand[1]){
        r=m_imageHero2->getChildByTag(TAGARMATURE)->boundingBox();
        r.origin=m_imageHero2->convertToWorldSpace(r.origin);
        if(r.containsPoint(pt)){ str=m_imageHero2->getChildByTag(TAGARMATURE)->getName();return  str;  }
    }
    if(m_heroStand[2]){
        r=m_imageHero3->getChildByTag(TAGARMATURE)->boundingBox();
        r.origin=m_imageHero3->convertToWorldSpace(r.origin);
        if(r.containsPoint(pt)){ str=m_imageHero3->getChildByTag(TAGARMATURE)->getName(); return  str; }
    }
    if(m_heroStand[3]){
        r=m_imageHero4->getChildByTag(TAGARMATURE)->boundingBox();
        r.origin=m_imageHero4->convertToWorldSpace(r.origin);
        if(r.containsPoint(pt)){ str=m_imageHero4->getChildByTag(TAGARMATURE)->getName(); return  str; }
    }
    if(m_heroStand[4]){
        r=m_imageHero5->getChildByTag(TAGARMATURE)->boundingBox();
        r.origin=m_imageHero5->convertToWorldSpace(r.origin);
        if(r.containsPoint(pt)){ str=m_imageHero5->getChildByTag(TAGARMATURE)->getName(); return  str; }
    }
    
   // log("pt----------x%f, y%f",pt.x,pt.y);
   // log("Rect----------x%f, y%f  w:%f  h %f ",r.origin.x,r.origin.y, r.size.width,r.size.height);
   // log("ppt----------x%s",str.c_str());
    
    return  str;
}



//ImageView  *   UiCamp::getLocal(Point  pt){        //==========点获取站位,
//
//    Rect  r=imageHero->boundingBox();
//    r.origin=imageHero->getParent()->convertToWorldSpace(r.origin);
//    r.size.height+=50;
//
//
//}



////////////////////////////////////////////////////////////////////////////////
//按钮响应;

bool  UiCamp::buttonInit(){
    
    
    
    Button  *buttonClose = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonClose"));           //关闭按钮；
    if (!buttonClose){ return false; }
    buttonClose->addTouchEventListener(CC_CALLBACK_2(UiCamp::buttonEvent, this));
    
    return  true;

}


void  UiCamp::buttonEvent(Ref *pSender, Widget::TouchEventType type)             //按钮响应函数；
{
    int buttonNum=2;
    Button*  button=dynamic_cast<Button*>(pSender);
    string  str1="buttonClose";
  
    if (button->getName().c_str()==str1) {  buttonNum=1;  }
    else{ buttonNum=2; }
    
    switch (buttonNum){
     //关闭按钮；
        case  1:
        {
            switch (type)
            {
                case  Widget::TouchEventType::ENDED:
                {
                    CC_SAFE_RETAIN(this);
                    this->removeFromParent();
                }
                    break;
                    
                default:   break;
            }
  
        }
            break;
            
            
     /////
        case  2:
        {
         switch (type)
          {
            case  Widget::TouchEventType::BEGAN:{
                //有标记时不产生；
                ImageView  *imageSigned=static_cast<ImageView*>(Helper::seekWidgetByName((Widget*)button->getParent(),"imageSigned"));
                if(!imageSigned->isVisible()){
                     this->schedule(schedule_selector(UiCamp::pressCallback),0.5f);   //长按定时器；
                }
                
                m_pressID=button->getName();           //给产生动画的ID赋值；
                
                m_del=true;
               
                
            }
                break;
                  
            case  Widget::TouchEventType::MOVED:{
            
                this->unschedule(schedule_selector(UiCamp::pressCallback));    //长按定时器；
                
                m_del=false;
            
            }
                break;
                
            case  Widget::TouchEventType::ENDED:
            {
                
                this->unschedule(schedule_selector(UiCamp::pressCallback));     //长按定时器；
                
                
                if(m_del){
                //点击按顺序加动画，不要删了；
                   ImageView  *imageSigned=static_cast<ImageView*>(Helper::seekWidgetByName((Widget*)button->getParent(),"imageSigned"));
                   imageSigned->isVisible();
                
                   if(imageSigned->isVisible()){
                        imageSigned->setVisible(false);
                        delStandHero(button->getName());   //删除动画；按钮的名字已经设置成了ID;
                    
                     }
                   else{
                     bool full=initStandHero(button->getName().c_str());    //设置动画；按钮的名字已经设置成了ID;
                      if(full){imageSigned->setVisible(true);}
                    
                        }
                }
                
                
            }
                break;

                
            default:    break;
          }
            
       }
   
        ////////
            
        default:      break;
    }

            
         
}
    

//////////////////////////////////////////////////////////////
///////////////////////////////层监听事件；拖动加动画

//按下；
bool  UiCamp::onTouchBegan (Touch  * touch,  Event*  event){
    
    m_ptStart=touch->getLocation();

   /*
    //有精灵时才执行；长按时；
    Sprite*  sprite=(Sprite* )m_pNode->getChildByName("listenerLayer")->getChildByName("pressHero");  //监听层的精灵的名字，以ID为m_pressID；
    if (sprite) {
        
        sprite->setPosition(touch->getLocation());
        
        //log("sprite+++");
        m_listener1->setSwallowTouches(true);
    }
   */
    
    //有dh时才执行；长按时；
    Armature*  armature=(Armature* )m_pNode->getChildByName("listenerLayer")->getChildByName("pressHero2");  //监听层的精灵的名字，以ID为m_pressID；
    if (armature) {
        armature->setPosition(touch->getLocation());
        m_listener1->setSwallowTouches(true);
    }

    
    
    this->schedule(schedule_selector(UiCamp::pressCallback),0.5f);   //长按定时器；
    m_pressID=getPressID(touch->getLocation());                   //从站台上获取动画名字，长按定时器产生动画；
    
    
    return  true;          //true事件传给moved和ended;不传给下一层；
    
}

//移动；
void  UiCamp::onTouchMoved (Touch  *touch,  Event * event){
    
    this->unschedule(schedule_selector(UiCamp::pressCallback));     //长按定时器；

    
    /*
    //有精灵时才执行；长按时；
    Sprite*  sprite=(Sprite* )m_pNode->getChildByName("listenerLayer")->getChildByName("pressHero");
    if (sprite) {
        sprite->setPosition(touch->getLocation());
         log("pressspriteMove");
        m_listener1->setSwallowTouches(true);
    }
    */
    
    
    //有dh时才执行；长按时；
    Armature*  armature=(Armature* )m_pNode->getChildByName("listenerLayer")->getChildByName("pressHero2");  //监听层的精灵的名字，以ID为m_pressID；
    if (armature) {
        armature->setPosition(touch->getLocation());
        m_listener1->setSwallowTouches(true);
    }
    
 
    
}


//松开；

void  UiCamp::onTouchEnded(Touch*  touch,  Event* event){
    
    this->unschedule(schedule_selector(UiCamp::pressCallback));     //长按定时器；
    
 
    
    m_ptEnd=touch->getLocation();
    m_ptEnd=event->getCurrentTarget()->convertToWorldSpace(m_ptEnd);
    
    /*
    //有精灵时才执行；长按时；
    Sprite*  sprite=(Sprite* )m_pNode->getChildByName("listenerLayer")->getChildByName("pressHero");
    if (sprite) {
        m_pNode->getChildByName("listenerLayer")->removeChild(sprite,false);
       if(m_pressID!=""){
          replaceStandHero(m_pressID);
          m_pressID="";
       }
        
       m_del=false;
       m_listener1->setSwallowTouches(false);
       
        
    }
    */
    
    //有动画时才执行；长按时,产生动画到监听层，在监听层上，动画随鼠标移动，松开时替换站位上的动画；
    Armature*  armature=(Armature* )m_pNode->getChildByName("listenerLayer")->getChildByName("pressHero2");  //监听层的精灵的名字，以ID为m_pressID；
    if (armature) {
        m_pNode->getChildByName("listenerLayer")->removeChild(armature,false);    //删掉监听层的动画；
       
        if(m_pressID!=""){
            replaceStandHero(m_pressID);                                          //---替换动画；
            m_pressID="";                                                         //给产生动画的ID赋空值；
        }
        
        m_del=false;
        m_listener1->setSwallowTouches(false);
    }
    
    //占击，去掉台上的动画；
    else if(m_ptStart==m_ptEnd){
        
        string id=getPressID(m_ptEnd);      //----获取动画ID;
        if(id!=""){
          delStandHero(id);                //----删除动画；
          setSigned(id, false);            //--滚动层去掉图标；
        }
    }

    
    m_pressID="";
    
}





//////////////////////////////////////////////////////////////
//其它面板设置的阵容；
void  UiCamp::setType(int  n){
    
    m_type=n;                         //哪个界面打开阵容时，要设置这个值；
}

vector<string>  UiCamp::getCamp()        //获取设置好后的阵容；
{

    m_camp.clear();
    if(m_heroStand[0]){ string str=m_imageHero1->getChildByTag(TAGARMATURE)->getName();  m_camp.push_back(str);  }
    if(m_heroStand[1]){ string str=m_imageHero2->getChildByTag(TAGARMATURE)->getName();  m_camp.push_back(str);  }
    if(m_heroStand[2]){ string str=m_imageHero3->getChildByTag(TAGARMATURE)->getName();  m_camp.push_back(str);  }
    if(m_heroStand[3]){ string str=m_imageHero4->getChildByTag(TAGARMATURE)->getName();  m_camp.push_back(str);  }
    if(m_heroStand[4]){ string str=m_imageHero5->getChildByTag(TAGARMATURE)->getName();  m_camp.push_back(str);  }
    
    return m_camp;
}

void  UiCamp::setCamp(){         //设置阵容；
    
    m_camp.clear();
    if(m_type==2){  m_camp=m_account->m_campST.m_mainCamp;  }
    if(m_type==1){  m_camp=m_account->m_campST.m_arenaCamp;  }
    
    //点击按顺序加动画，不要删了；
    for(int i=0; i<m_camp.size();i++){
        initStandHero(m_camp[i]);    //设置动画；按钮的名字已经设置成了ID;
        setSigned(m_camp[i], true);
    }
   

}

void UiCamp::onEnter()
{
    Layer::onEnter();
}

void UiCamp::onExit()
{
    getCamp();
    //其它面板设置的阵容；
    if(m_type==1){    //1竞技场；                 //哪个界面打开阵容时，在创建阵容界面时要设置这个值；
        m_account->m_campST.m_arenaCamp=m_camp;  //账号里的值 ；
        
        ((UiArena*)this->getParent())->setCamp(m_camp);   //调用界面的函数设置；
        
    }
    if(m_type==2){    //2主场景；
        m_account->m_campST.m_mainCamp=m_camp;      //账号里的值 ；
        m_account->saveCamp();
        
        ((MainCityScence*)this->getParent())->initHeroST(m_camp);//调用界面的函数设置；
        ((MainCityScence*)this->getParent())->heroLoad();
        
    }
    
    
    
    Layer::onExit();
}




