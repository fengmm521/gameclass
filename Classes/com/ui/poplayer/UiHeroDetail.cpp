/**********************************************
英雄详情界面；
 
 **********************************************/

#include "UiHeroDetail.h"
#include "strHash.h"
using namespace cocos2d::ui;

UiHeroDetail::UiHeroDetail(){
   m_heroID="";
   m_panelHight=600;
   m_percent=15;
}

UiHeroDetail::~UiHeroDetail(){
    
}



UiHeroDetail* UiHeroDetail::create(string  heroID)   //====静态创建函数；
{
  
    UiHeroDetail *pRet = new UiHeroDetail();
   
    if (pRet){
        pRet->m_heroID=heroID;
        
        }
    
    if (pRet && pRet->init())
    {
       
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}






bool UiHeroDetail::init()
{
    if ( !UiBase::init() )  {      return false;    }
    log("UiHeroDetail::====init");
    //界面导入；
    m_pNode = GUIReader::getInstance()->widgetFromJsonFile("uiHeroDetail.ExportJson");
    m_pNodeBase->getChildByName("buttonClose")->setVisible(false);
    m_pNodeBase->getChildByName("imageBK0")->setVisible(false);
    m_pNodeBase->addChild(m_pNode);
    m_pNode->setTouchEnabled(false);
    
    
    //一个英雄里的装备；
    m_equip.push_back("300001");
    m_equip.push_back("300010");
    m_equip.push_back("300019");
    m_equip.push_back("300028");
    m_equip.push_back("300037");
    m_equip.push_back("300046");
    
    //主面板设置；
    mainPanelInit(m_pNode,m_heroID);
  
    //星阶面板设置；
    setPanelStar();
    
    //技能面板
    setPanelSkill();
    
    //属性面板
    setPanelProperty();
    
    //羁绊面板
    setPanelTie();
    
    
    
    //按钮；
    buttonInit();
    
    
    return true;
}


//////////////////////////////////////////////
//====主面板设置；

void  UiHeroDetail::mainPanelInit(Widget* imageItem,string  heroID){     //====主面板设置；

    //英雄的属性表；
    
    m_mapDataST = LocalDataManger::sharedLocalDataManger()->getConfigtab_card_attribute_sysDataST(atoi(heroID.c_str()));
    

    
    //英雄属性赋值；固定；
    m_heroProperty.heroID=m_mapDataST.ID;                    //英雄ID
    
    m_heroProperty.headBK="ui_c_frame3_1.png";               //头像框；  品质3；
    m_heroProperty.headImage=m_mapDataST.hero_icon;          //头像；
    m_heroProperty.starLevel=3;                              //星级；
    m_heroProperty.level=68;                                 //等级；
    m_heroProperty.heroName=m_mapDataST.hero_name;           //名字；
    m_heroProperty.sword=8150;                               //战力；
    m_heroProperty.heroExperience="8989556/10000000";        //经验
    
    

    
    m_skill.push_back("200010");
    
    m_skill.push_back("200011");
    m_skill.push_back("200012");
    m_skill.push_back("200013");
    m_skill.push_back("200014");
    m_skill.push_back("200015");
    m_skill.push_back("200016");
    m_skill.push_back("200017");
    m_skill.push_back("200018");
    m_skill.push_back("200019");
    
    //m_heroProperty.heroSigne=false;                         //是否有遮挡，签到，点击变暗；
    
    
    //设置动画；
    Armature*  armature=getArmatrue(m_heroID);
    ImageView*  imageHero=static_cast<ImageView*>(Helper::seekWidgetByName(m_pNode, "imageHero"));
    float  h=armature->getContentSize().height;
    armature->setPosition(imageHero->getPosition()+Point(0,h/2+20));
    armature->setScale(1.7);
    if(armature->getContentSize().height>300){armature->setScale(1.2);}
    m_pNode->addChild(armature);
    log("heroID--------------------------%s",m_heroID.c_str());
    log("heroIDContentSize-----------------%f",armature->getContentSize().height);
  
    
    //设置；
    setSword(imageItem,m_heroProperty.sword);
    setLevel(imageItem,m_heroProperty.level);
    setExperience(imageItem,m_heroProperty.heroExperience);
    setHeroName(imageItem,m_heroProperty.heroName,6);
    setStar(imageItem,m_heroProperty.starLevel);
    setEquip(imageItem, m_equip);
    
    
    //setHeadBK(imageItem,m_heroProperty.headBK);
    //setHead(imageItem, m_heroProperty.headImage);
    // setSigned(imageItem,m_heroProperty.heroSigne);
 
    
    
    //效果资源载入
    std::string actionID = "tx_jinengsj"; //技能升级
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("ui/tx/"+actionID+"/" + actionID +"0.png","ui/tx/"+actionID+"/" + actionID + "0.plist","ui/tx/"+actionID+"/" +actionID + ".ExportJson");
    
    actionID = "tx_shenxing"; //星阶升星
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("ui/tx/"+actionID+"/" + actionID +"0.png","ui/tx/"+actionID+"/" + actionID + "0.plist","ui/tx/"+actionID+"/" +actionID + ".ExportJson");
    
    actionID = "tx_xigjiesj"; //星阶升级
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("ui/tx/"+actionID+"/" + actionID +"0.png","ui/tx/"+actionID+"/" + actionID + "0.plist","ui/tx/"+actionID+"/" +actionID + ".ExportJson");
    
    //英雄技能升级效果
    if (!s_skillUpEffectMap.empty()) {
        s_skillUpEffectMap.clear();
    }
    
    
    //英雄星阶升星效果
    s_StarUpEffect = cocostudio::Armature::create("tx_shenxing");
    s_StarUpEffect->setTag(kHeroStarUpBtnTag);
    s_StarUpEffect->setPosition(armature->getPosition());
    s_StarUpEffect->setVisible(false);
    m_pNode->addChild(s_StarUpEffect,2);
    
    //英雄星阶升级效果
    s_LeveUpEffect = cocostudio::Armature::create("tx_xigjiesj");
    s_LeveUpEffect->setTag(kHeroleveUpBtnTag);
    s_LeveUpEffect->setPosition(armature->getPosition());
    s_LeveUpEffect->setVisible(false);
    m_pNode->addChild(s_LeveUpEffect,2);
    
}



void  UiHeroDetail::setSword(Widget * pWidget,  int  sword){       //=======设置战力；
    
    Text  *textSword=static_cast<Text*>(Helper::seekWidgetByName(pWidget,"textSword"));
    string  str=to_string(sword);
    textSword->setString(str);
    
    
}

void  UiHeroDetail::setLevel(Widget * pWidget,int  level){       //=======设置等级；
    
    Text  *textLevel=static_cast<Text*>(Helper::seekWidgetByName(pWidget,"textLevel"));
    string  str=to_string(level);
    textLevel->setString(str);
    
    
}

void  UiHeroDetail::setExperience(Widget * pWidget, string experience){       //========设置经验；
    
    Text  *textExperience=static_cast<Text*>(Helper::seekWidgetByName(pWidget,"textExperience"));
    
    textExperience->setString(experience);
    
    
}

void  UiHeroDetail::setHeroName(Widget * pWidget, string  name, int  quality){       //设置名字；
    
    ImageView  *imageHero=static_cast<ImageView*>(Helper::seekWidgetByName(pWidget,"imageHero"));
    //底框；
    ImageView  *imageFrame=static_cast<ImageView*>(Helper::seekWidgetByName(imageHero,"imageFrame"));
    string  strImage=getQualityFrame2(quality);     //----
    imageFrame->loadTexture(strImage.c_str(),TextureResType::PLIST);
    
    //名字；
    Text  *textName=static_cast<Text*>(Helper::seekWidgetByName(imageHero,"textName"));
    textName->setString(name);
    //品质；
    Text  *textLevelH=static_cast<Text*>(Helper::seekWidgetByName(imageHero,"textLevelH"));
    textLevelH->setPositionX(textName->getPositionX()+textName->getContentSize().width/2+2);
    string  str="+"+to_string(quality);
    textLevelH->setString(str);
  
    
}



void  UiHeroDetail::setStar(Widget * pWidget,int starLevel){      //=====设置星级；tag 11;
    
    
    
    ImageView  *imageStar1=static_cast<ImageView*>(Helper::seekWidgetByName(pWidget,"imageStar1"));
    
    imageStar1->loadTexture("ui_c_star2.png",TextureResType::PLIST);
    if(1<=starLevel){  imageStar1->loadTexture("ui_c_star1.png",TextureResType::PLIST); }
    float y=imageStar1->getContentSize().height;
    Point  pt=imageStar1->getPosition();
    
    
    
    for(int  i=2;i<=5; i++){
        ImageView*  imageStar2=(ImageView*)imageStar1->clone();
        imageStar2->setPositionY(pt.y+(i-1)*y+3);
        
        imageStar2->loadTexture("ui_c_star2.png",TextureResType::PLIST);
        if(i<=starLevel){  imageStar2->loadTexture("ui_c_star1.png",TextureResType::PLIST); }
        imageStar1->getParent()->addChild(imageStar2,1,11);
        
        
    }
 
    
}


void  UiHeroDetail::setEquip(Widget * pWidget, vector<string>  equip){  //=======设置装备；tag  20;
    //框；
    ImageView  *imageEquipItem1=static_cast<ImageView*>(Helper::seekWidgetByName(pWidget,"imageEquipItem"));
    Size   size=imageEquipItem1->getContentSize();
    Point  pt=imageEquipItem1->getPosition();
    log("imageEquipItemwidth=====%f", size.width);
   
    
    for (int i=0; i<6; i++) {
        //复制装备项；
        ImageView  *imageEquipItem2=(ImageView*)imageEquipItem1->clone();
        Point  tempt;
        tempt.x=pt.x+(i%2)*(size.width+40);
        tempt.y=pt.y-(int(i/2))*(size.height+45);
        
        imageEquipItem2->setPosition(tempt);
        imageEquipItem1->getParent()->addChild(imageEquipItem2,0,20);
        
        
        //头像；
        ImageView  *imageEquip=static_cast<ImageView*>(Helper::seekWidgetByName(imageEquipItem2,"imageEquip"));
        string  strBK="equip/equip_bk"+to_string(i+1)+".png";
        imageEquip->loadTexture(strBK,TextureResType::PLIST);                    //设置装备图片黑白图；
        
        string  str="";
        m_equipST = LocalDataManger::sharedLocalDataManger()->getConfigtab_equipbase_sysDataST(atoi(m_equip[i].c_str()));   ////////////装备的属性表；
        str="equip/"+m_equipST.equip_icon;                                     //装备是放在文件夹里的，要加文件夹名；
        if(i==5){str=""; }
        imageEquip->loadTexture(str,TextureResType::PLIST);                    //设置装备图片；
        
        //+号；
        Button  *buttonAdd=static_cast<Button*>(Helper::seekWidgetByName(imageEquipItem2,"buttonAdd"));
        buttonAdd->setVisible(false);
        if(i==5){
            buttonAdd->setVisible(true);
            buttonAdd->setTouchEnabled(false);
            
        }
        
        
        
        //按钮；
        Button  *buttonEquip=static_cast<Button*>(Helper::seekWidgetByName(imageEquipItem2,"buttonEquip"));
        string  str2=getQualityFrame3(i+3);
        buttonEquip->loadTextureNormal(str2,TextureResType::PLIST);
        buttonEquip->setName(equip[i]);
        buttonEquip->addTouchEventListener(CC_CALLBACK_2(UiHeroDetail::buttonEvent, this));
 
    }
    
    
    imageEquipItem1->setVisible(false);              //克隆前不能隐藏；
   
    
}


//////////////////////////////////////////////
//星阶面板设置；
void   UiHeroDetail::setPanelStar(){

    Layout  *panelStar = static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelStar"));
    
    
    Text  *textExpend1=static_cast<Text*>(Helper::seekWidgetByName(panelStar,"textExpend1"));
    textExpend1->setString("88888");
    Text  *textExpend2=static_cast<Text*>(Helper::seekWidgetByName(panelStar,"textExpend2"));
    textExpend2->setString("99999");
    
    
    //框；
    ImageView  *imageItem1=static_cast<ImageView*>(Helper::seekWidgetByName(panelStar,"imageItem"));
    Size   size=imageItem1->getContentSize();
    Point  pt=imageItem1->getPosition();
    
    log("imageItem1=====%f", pt.y);
    
    
    //英雄升级按钮
    Button* heroLeveBtn = static_cast<Button*>(Helper::seekWidgetByName(panelStar, "buttonUp"));
    heroLeveBtn->setTag(kHeroleveUpBtnTag);
    heroLeveBtn->addTouchEventListener(CC_CALLBACK_2(UiHeroDetail::buttonSkillEvent, this));
    //英雄升星按钮
    Button* heroStarUpBtn = static_cast<Button*>(Helper::seekWidgetByName(panelStar, "buttonUpStar"));
    heroStarUpBtn->setTag(kHeroStarUpBtnTag);
    heroStarUpBtn->addTouchEventListener(CC_CALLBACK_2(UiHeroDetail::buttonSkillEvent, this));
    
    for (int i=0; i<5; i++) {
        //复制装备项；
        ImageView  *imageItem2=(ImageView*)imageItem1->clone();
        Point  tempt;
        tempt.x=pt.x+(i)*(size.width+32);
        tempt.y=pt.y;
        imageItem2->setPosition(tempt);
        imageItem1->getParent()->addChild(imageItem2,0,20);
        
        //头像；
        ImageView  *imageFrame=static_cast<ImageView*>(Helper::seekWidgetByName(imageItem2,"imageFrame"));
        
        m_equipST = LocalDataManger::sharedLocalDataManger()->getConfigtab_equipbase_sysDataST(atoi(m_equip[i].c_str()));   ////////////装备的属性表；
        string  str="equip/"+m_equipST.equip_icon;                              //装备是放在文件夹里的，要加文件夹名；
        imageFrame->loadTexture(str,TextureResType::PLIST);                    //设置装备图片；
        
        
        //按钮；
        Button  *buttonFrame=static_cast<Button*>(Helper::seekWidgetByName(imageItem2,"buttonFrame"));
        string  str2=getQualityFrame3(i+3);
        buttonFrame->loadTextureNormal(str2,TextureResType::PLIST);
       
        buttonFrame->addTouchEventListener(CC_CALLBACK_2(UiHeroDetail::buttonEvent, this));
        
        
        
    }

     imageItem1->setVisible(false);              //克隆前不能隐藏；

}

//////////////////////////////////////////////
//2技能面板设置；
bool   UiHeroDetail::setPanelSkill(){              //============初始化滚动图层；并添加精灵项；
  
        //获取滚动图层；
        ui::ScrollView* scrollViewSkill=static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode,"scrollViewSkill"));
        if (!scrollViewSkill){ log("Can't  get  scrollViewSkill-----------------"); return false;   }
        scrollViewSkill->addEventListener(  CC_CALLBACK_2(UiHeroDetail::scrollViewEvent,this)  );    //事件监听；
    
    
       //滑块；
       Slider  *slider=static_cast<Slider*>(Helper::seekWidgetByName(m_pNode,"slider"));
       slider->setPercent(14);
       slider->addEventListener(CC_CALLBACK_2(UiHeroDetail::sliderEvent, this));                     //事件监听；
    
    
        //滚动图层里面的图层；
        Layout  *panelSkill=static_cast<Layout*>(Helper::seekWidgetByName(scrollViewSkill,"panelSkill"));
        if (!panelSkill){ log("Can't  get  panelSkill-----------------"); return false;   }
    
        //原始的一个项，隐藏，
        Layout  *panelItem=static_cast<Layout*>(Helper::seekWidgetByName(m_pNode,"panelItem"));
        if (!panelItem){ log("Can't  get  panelItem-----------------"); return false;   }
    
    
 
        //设置滚动层
        int line=(int)(m_skill.size()/2);
        if(m_skill.size()/2==1){line+=1;}
    
        if (m_skill.size()/2<3) {                                                //比显示窗小时；
            line=3;
            slider->setVisible(false);
        }
    
        Size  size=panelItem->getContentSize();
    
        float  panelHight=(line)*(size.height+8);                           //层高；
        float  panelWidth=panelSkill->getContentSize().width;
        m_panelHight=panelHight;
        
        panelSkill->setContentSize(Size(panelWidth,panelHight));                 //设置层的大小；
        scrollViewSkill->setInnerContainerSize(Size(panelWidth,panelHight));     //设置滚动区的大小；和层一样大；
        
        
        //增加精灵项；m_string一个帐号里的英雄；
        panelItem->setPosition(Point(10,panelHight-size.height/2-90));       //原始项的位置；
        Point  heroPt=panelItem->getPosition();
    
        
        for(int  i=0;  i<m_skill.size();i++){
            Point  pt;
            pt.x=heroPt.x+(i%2)*(size.width+5);
            pt.y=heroPt.y-(int(i/2))*(size.height+8);
            
            //log("x=====%d",(int)m_string.size());
            //log("y=%d",(int(i/6)));
            
            Layout  *panelItem2=(Layout*)panelItem->clone();
            panelItem2->setVisible(true);
            panelItem2->setPosition(pt);
            panelItem->getParent()->addChild(panelItem2,0,m_skill[i]);         //以ID号为名字；
            
            setSkillItem(panelItem2, m_skill[i]);    //-------------设置精灵项；
        }
    
        panelItem->setVisible(false);                               //原始项，隐藏，
    
    
    return  true;
    
}
    
    
void   UiHeroDetail::setSkillItem(Widget* imageItem,  string  skillID)    //=======设置一个精灵项；
{
    if (!imageItem){  return ;}
    if (skillID==""){  return ;}
    
    m_skillST=LocalDataManger::sharedLocalDataManger()->getConfigtab_skill_visual_effectDataST(  atoi(skillID.c_str())  );
    
    //设置文本；
    Text*  textName=(Text*)(imageItem->getChildByName("textName"));
    textName->setString(m_skillST.skill_name);
    
    Text*  textLevel=(Text*)(imageItem->getChildByName("textLevel"));
    string  strlevel="LV"+to_string(m_skillST.skill_level);
    textLevel->setString(strlevel);
    
    Text*  textPrice=(Text*)(imageItem->getChildByName("textPrice"));
    textPrice->setString("8000");
    
    
    
    
    //设置图片；底框；
    ImageView  *imageHead=(ImageView  *)(imageItem->getChildByName("imageHead"));
    string  strskill="skill/"+m_skillST.skill_icon;
    imageHead->loadTexture(strskill,TextureResType::PLIST);
    
    //添加技能升级效果
    Armature* tmpEffect = cocostudio::Armature::create("tx_jinengsj");
    //添加动画播放结束事件
    tmpEffect->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(UiHeroDetail::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    
    tmpEffect->setVisible(false);
    tmpEffect->setPosition(imageHead->getPosition());
    imageItem->addChild(tmpEffect,2);
    s_skillUpEffectMap[skillID] = tmpEffect;
    //string  strframe="ui_c_frame3.png";
    //setHeadBK(imageItem,"",skillID);

    Button* leveUpbtn = (Button*)(imageItem->getChildByName("buttonUp"));
    leveUpbtn->setTag(atoi(skillID.c_str()));
    leveUpbtn->addTouchEventListener(CC_CALLBACK_2(UiHeroDetail::buttonSkillEvent, this));
}


///////////

void  UiHeroDetail::buttonSkillEvent(Ref *pSender, ui::Widget::TouchEventType   type)
{
    switch (type)
    {
        case  ui::Widget::TouchEventType::BEGAN:
            //MessageBox("fgfggf", "dsdsss");
            break;
        case  ui::Widget::TouchEventType::MOVED:
            //MessageBox("fgfggf", "dsdsss");
            break;
            
        case  ui::Widget::TouchEventType::ENDED:
        {
            Button* tmpbtn = (Button*)pSender;
            int tmptag = tmpbtn->getTag();
            switch (tmptag) {
                case kHeroleveUpBtnTag:
                {
                    this->playHeroLeveUpEffect();
                }
                    break;
                case kHeroStarUpBtnTag:
                {
                    this->playHeroStarUpEffect();
                }
                    break;
                default:
                {
                    this->skillLeveUpButtonEventForSkillID(tmpbtn->getTag());
                }
                    break;
            }
            break;
        }
            
        case  ui::Widget::TouchEventType::CANCELED:
            
            break;
            
        default:
            break;
    }
}

//在播放英雄升级动画
void UiHeroDetail::playHeroLeveUpEffect()
{
    s_LeveUpEffect->setVisible(true);
    s_LeveUpEffect->getAnimation()->play("play");
}
//播放英雄升星动画
void UiHeroDetail::playHeroStarUpEffect()
{
    s_StarUpEffect->setVisible(true);
    s_StarUpEffect->getAnimation()->play("play");
}

//英雄技能升级事件
void UiHeroDetail::skillLeveUpButtonEventForSkillID(int skillID)
{
    std::string tmpSkillid = to_string(skillID);
    s_skillUpEffectMap[tmpSkillid]->setVisible(true);
    s_skillUpEffectMap[tmpSkillid]->getAnimation()->play("play");
}
//技能升级动画播放结束
void UiHeroDetail::skillLeveUpEffectPlayEnd(int skillID)
{
    std::string tmpSkillid = to_string(skillID);
    s_skillUpEffectMap[tmpSkillid]->setVisible(false);
}
//星阶中的动画播放结束
void UiHeroDetail::heroEffectPlayEnd(int effectType)
{
    switch (effectType) {
        case 100:
            s_LeveUpEffect->setVisible(false);
            break;
        case 101:
            s_StarUpEffect->setVisible(false);
            break;
        default:
            break;
    }
}
//动画效果播放:play结束事件
void UiHeroDetail::onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
    string evtx = evt;
    switch(hash_(evtx.c_str())){
        case "playEnd"_hash:
        {
            int tagtmp = bone->getArmature()->getTag();
            if (tagtmp > 1000) {
                this->skillLeveUpEffectPlayEnd(tagtmp);
            }else{
                this->heroEffectPlayEnd(tagtmp);
            }
        }
            break;
        default:
            //log("sprite default.....");
            break;
    }
}


//////

void  UiHeroDetail::setHeadBK(Widget* pWidget,string frameLevel,string  nameID){        //=========设置底框；tag 100, 101
    
    log("frameLevel=====%s",frameLevel.c_str());
    if (frameLevel=="") {   frameLevel="ui_c_frame4.png";  }
    log("frameLevel=====%s",frameLevel.c_str());
    
    //头像的底框是个按钮；
    Button  *buttonHead=(Button*)(pWidget->getChildByName("buttonHead"));
    //buttonHead->loadTextureNormal(frameLevel.c_str(),TextureResType::PLIST);   //出错；
    buttonHead->setTag(100);
    buttonHead->addTouchEventListener(CC_CALLBACK_2(UiHeroDetail::buttonEvent, this));
    
    //整个项的底框是个按钮；
    Button  *buttonImage=(Button*)(pWidget->getChildByName("buttonImage"));
    buttonImage->setName(nameID);             //把按钮名字调成ID号；
    buttonImage->setTag(101);
    buttonImage->addTouchEventListener(CC_CALLBACK_2(UiHeroDetail::buttonEvent, this));
    
}


void  UiHeroDetail::setHead(Widget* pWidget, string headImage){                    //==========设置头像；
    
    ImageView  *imageHead=static_cast<ImageView*>(Helper::seekWidgetByName(pWidget,"imageHead"));
    imageHead->loadTexture(headImage,TextureResType::PLIST);
    
}
    
    
    

//////////////////////////////////////////////
//3属性面板设置；
void   UiHeroDetail::setPanelProperty(){
    
    //赋初值；
    Layout  *panelProperty= static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelProperty"));
    
    string str0="0";
    string  str1=to_string(m_mapDataST.hero_hp);      if(str1==str0){str1="894545+88";}
    string  str2=to_string(m_mapDataST.hero_evade);   if(str2==str0){str2="894545+88";}
    string  str3=to_string(m_mapDataST.hero_hit);     if(str3==str0){str3="8945+88";}
    string  str4="32332+100";    //
    string  str5="5744+200";     //
    
    string  str6=to_string(m_mapDataST.physics_act);   if(str6==str0){str6="879445+88";}
    string  str7="46654+300";    //
    string  str8="78875+400";///
    string  str9="78845+500";//
    string  str10=to_string(m_mapDataST.hp_restore);   if(str10==str0){str6="87945+88";}
    
    
    Text  *textDescribe=static_cast<Text*>(Helper::seekWidgetByName(panelProperty,"textDescribe"));
    textDescribe->setString(m_mapDataST.hero_description);
    
    Text  *textProperty1=static_cast<Text*>(Helper::seekWidgetByName(panelProperty,"textProperty1"));
    textProperty1->setString(str1);
    
    Text  *textProperty2=static_cast<Text*>(Helper::seekWidgetByName(panelProperty,"textProperty2"));
    textProperty2->setString(str2);
    
    Text  *textProperty3=static_cast<Text*>(Helper::seekWidgetByName(panelProperty,"textProperty3"));
    textProperty3->setString(str3);
    
    Text  *textProperty4=static_cast<Text*>(Helper::seekWidgetByName(panelProperty,"textProperty4"));
    textProperty4->setString(str4);
    
    Text  *textProperty5=static_cast<Text*>(Helper::seekWidgetByName(panelProperty,"textProperty5"));
    textProperty5->setString(str5);
    
    
    Text  *textProperty6=static_cast<Text*>(Helper::seekWidgetByName(panelProperty,"textProperty6"));
    textProperty6->setString(str6);
 
    Text  *textProperty7=static_cast<Text*>(Helper::seekWidgetByName(panelProperty,"textProperty7"));
    textProperty7->setString(str7);
    
    Text  *textProperty8=static_cast<Text*>(Helper::seekWidgetByName(panelProperty,"textProperty8"));
    textProperty8->setString(str8);
    
    Text  *textProperty9=static_cast<Text*>(Helper::seekWidgetByName(panelProperty,"textProperty9"));
    textProperty9->setString(str9);
    
    Text  *textProperty10=static_cast<Text*>(Helper::seekWidgetByName(panelProperty,"textProperty10"));
    textProperty10->setString(str10);

}

    
    
    
//////////////////////////////////////////////
//4羁绊面板设置；
void   UiHeroDetail::setPanelTie(){

    ui::ListView  *listViewTie = static_cast<ui::ListView*>(Helper::seekWidgetByName(m_pNode, "listViewTie"));
    Layout*  panelItem=static_cast<Layout*>(Helper::seekWidgetByName(listViewTie, "panelItem"));
  
    for (int i=1; i<10; i++) {
        Layout*  panelItem2=(Layout*)panelItem->clone();
        listViewTie ->insertCustomItem(panelItem2, i);
    }
    
    
    
    

}
        
        
////////////////////////////////////
//控件响应事件；


void  UiHeroDetail::sliderEvent(Ref *pSender, Slider::EventType type){    //===滑块响应函数，控制滚动层；
    
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        
        Slider* slider = dynamic_cast<Slider*>(pSender);    //滑块在15到85之间滑动；
        int percent = slider->getPercent();
        if (percent<14) {  percent=14;slider->setPercent(14);}
        if (percent>86) { percent=86;slider->setPercent(86);}
        percent =percent-15;
        //m_percent=percent;
        percent=percent*100/70;
        
        ui::ScrollView* scrollViewHero=static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode,"scrollViewSkill"));
        scrollViewHero->scrollToPercentVertical(percent, 0.2, true);
        
    }
    //m_sliderDirection=true;
   // m_scrollChangeSlider=false;
   // m_sliderNo=false;
}


void  UiHeroDetail::scrollViewEvent(Ref *pSender, ui::ScrollView::EventType type){   //====滚动层响应函数，控制滑块，；
    
    ui::ScrollView* scrollViewHero=static_cast<ui::ScrollView*>(pSender);
    if(!scrollViewHero){log("ScrollView  is  NULL"); return;}
    //Layout  *panelSet=static_cast<Layout*>(Helper::seekWidgetByName(scrollViewHero,"panelSkill"));
    //if(!panelSet){log("ScrollView:panelHero  is  NULL"); return;}
    
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
    
    
    //m_scrollChangeSlider=true;
    
}





////////////////////////////////////////
////////////////////////////////////////
//按钮

bool  UiHeroDetail::buttonInit(){
    
 
    Button  *buttonBack = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonBack"));           //返回按钮；
    if (!buttonBack){ return false; }
    buttonBack->addTouchEventListener(CC_CALLBACK_2(UiHeroDetail::buttonEvent, this));
   
    
    Button  *buttonStar = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonStar"));           //星阶按钮；
    if (!buttonStar){ return false; }
    buttonStar->addTouchEventListener(CC_CALLBACK_2(UiHeroDetail::buttonEvent, this));
    
    Button  *buttonSkill = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonSkill"));           //技能按钮；
    if (!buttonSkill){ return false; }
    buttonSkill->addTouchEventListener(CC_CALLBACK_2(UiHeroDetail::buttonEvent, this));
    
    Button  *buttonProperty = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonProperty"));    //属性按钮；
    if (!buttonProperty){ return false; }
    buttonProperty->addTouchEventListener(CC_CALLBACK_2(UiHeroDetail::buttonEvent, this));
    
    Button  *buttonTie = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonTie"));           //羁绊按钮；
    if (!buttonTie){ return false; }
    buttonTie->addTouchEventListener(CC_CALLBACK_2(UiHeroDetail::buttonEvent, this));
    
    
    
    return  true;

}


void  UiHeroDetail::buttonEvent(Ref *pSender, Widget::TouchEventType type)             //按钮响应函数；
{
 
    Button*  button=dynamic_cast<Button*>(pSender);
    string   str=button->getName();
    
    string  str1="buttonBack";
    
    string  str2="buttonStar";
    string  str3="buttonSkill";
    string  str4="buttonProperty";
    string  str5="buttonTie";
    

    
  
    switch (type)
     {
                case  Widget::TouchEventType::ENDED:
                {
                   if (str==str1) {   //返回；
                    CC_SAFE_RETAIN(this);
                    this->removeFromParent();
                   }
                    
                   else if (str==str2||str==str3||str==str4||str==str5){
                       buttonPress(pSender);        //-----按钮选项卡；
                   }
                   
                   else if(1){          //装备；
                       for (string strEquip:m_equip) {
                           if (strEquip==str) {
                               UiDepot*  uiDepot=UiDepot::create();
                               this->addChild(uiDepot);
                           }
                       }
                   
                   }
                    
                   else if (str==str2){
                      
                   }
                    
                }
                    break;
                    
                default:      break;
       }
            
            
    


    
}


void  UiHeroDetail::buttonPress(Ref *pSender){    //====按钮选项卡；
    
    if (!pSender) {   return;  }
    
    Button  *button1 = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonStar"));
    Button  *button2 = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonSkill"));
    Button  *button3 = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonProperty"));
    Button  *button4 = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonTie"));
    
    Text  *text1 = static_cast<Text*>(Helper::seekWidgetByName(m_pNode, "textStar"));
    Text  *text2 = static_cast<Text*>(Helper::seekWidgetByName(m_pNode, "textSkill"));
    Text  *text3 = static_cast<Text*>(Helper::seekWidgetByName(m_pNode, "textProperty"));
    Text  *text4 = static_cast<Text*>(Helper::seekWidgetByName(m_pNode, "textTie"));
    
    
    Layout  *panelStar = static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelStar"));
    ui::ScrollView  *scrollViewSkill = static_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pNode, "scrollViewSkill"));
    Layout  *panelProperty= static_cast<Layout*>(Helper::seekWidgetByName(m_pNode, "panelProperty"));
    ui::ListView  *listViewTie = static_cast<ui::ListView*>(Helper::seekWidgetByName(m_pNode, "listViewTie"));
    
    string  strShow="ui_cangku_02.png";
    string  strHide="ui_cangku_03.png";
    Color3B  colorShow=Color3B(255, 237, 222);
    Color3B  colorHide=Color3B(46, 28, 8);
    
    
    Button*  button=dynamic_cast<Button*>(pSender);
    string   str=button->getName();
    
    string  str1="buttonStar";
    string  str2="buttonSkill";
    string  str3="buttonProperty";
    string  str4="buttonTie";
    
    if (str==str2){
        Slider  *slider=static_cast<Slider*>(Helper::seekWidgetByName(m_pNode,"slider"));
        slider->setVisible(true);
    }
    else{
        Slider  *slider=static_cast<Slider*>(Helper::seekWidgetByName(m_pNode,"slider"));
        slider->setVisible(false);
    }
    
    
    if (str==str1) {
        button1->loadTextureNormal(strShow,TextureResType::PLIST);
        button1->loadTexturePressed(strHide,TextureResType::PLIST);
        button2->loadTextureNormal(strHide,TextureResType::PLIST);
        button2->loadTexturePressed(strShow,TextureResType::PLIST);
        button3->loadTextureNormal(strHide,TextureResType::PLIST);
        button3->loadTexturePressed(strShow,TextureResType::PLIST);
        button4->loadTextureNormal(strHide,TextureResType::PLIST);
        button4->loadTexturePressed(strShow,TextureResType::PLIST);
        
        text1->setColor(colorShow);
        text2->setColor(colorHide);
        text3->setColor(colorHide);
        text4->setColor(colorHide);
        
        panelStar ->setVisible(true);
        scrollViewSkill->setVisible(false);
        panelProperty->setVisible(false);
        listViewTie->setVisible(false);
        
    }
    else if(str==str2){
        
        button1->loadTextureNormal(strHide,TextureResType::PLIST);
        button1->loadTexturePressed(strShow,TextureResType::PLIST);
        button2->loadTextureNormal(strShow,TextureResType::PLIST);
        button2->loadTexturePressed(strHide,TextureResType::PLIST);
        button3->loadTextureNormal(strHide,TextureResType::PLIST);
        button3->loadTexturePressed(strShow,TextureResType::PLIST);
        button4->loadTextureNormal(strHide,TextureResType::PLIST);
        button4->loadTexturePressed(strShow,TextureResType::PLIST);
        
        text1->setColor(colorHide);
        text2->setColor(colorShow);
        text3->setColor(colorHide);
        text4->setColor(colorHide);
        
        panelStar ->setVisible(false);
        scrollViewSkill->setVisible(true);
        panelProperty->setVisible(false);
        listViewTie->setVisible(false);
        
    }
    
    else if(str==str3){
        
        button1->loadTextureNormal(strHide,TextureResType::PLIST);
        button1->loadTexturePressed(strShow,TextureResType::PLIST);
        button2->loadTextureNormal(strHide,TextureResType::PLIST);
        button2->loadTexturePressed(strShow,TextureResType::PLIST);
        button3->loadTextureNormal(strShow,TextureResType::PLIST);
        button3->loadTexturePressed(strHide,TextureResType::PLIST);
        button4->loadTextureNormal(strHide,TextureResType::PLIST);
        button4->loadTexturePressed(strShow,TextureResType::PLIST);
        
        text1->setColor(colorHide);
        text2->setColor(colorHide);
        text3->setColor(colorShow);
        text4->setColor(colorHide);
        
        panelStar ->setVisible(false);
        scrollViewSkill->setVisible(false);
        panelProperty->setVisible(true);
        listViewTie->setVisible(false);
    }
    else if(str==str4){
        
        
        button1->loadTextureNormal(strHide,TextureResType::PLIST);
        button1->loadTexturePressed(strShow,TextureResType::PLIST);
        button2->loadTextureNormal(strHide,TextureResType::PLIST);
        button2->loadTexturePressed(strShow,TextureResType::PLIST);
        button3->loadTextureNormal(strHide,TextureResType::PLIST);
        button3->loadTexturePressed(strShow,TextureResType::PLIST);
        button4->loadTextureNormal(strShow,TextureResType::PLIST);
        button4->loadTexturePressed(strHide,TextureResType::PLIST);
        
        text1->setColor(colorHide);
        text2->setColor(colorHide);
        text3->setColor(colorHide);
        text4->setColor(colorShow);
        
        panelStar ->setVisible(false);
        scrollViewSkill->setVisible(false);
        panelProperty->setVisible(false);
        listViewTie->setVisible(true);
        
    }
    
    
    
}













void UiHeroDetail::onEnter()
{
    Layer::onEnter();
}

void UiHeroDetail::onExit()
{
    Layer::onExit();
}




