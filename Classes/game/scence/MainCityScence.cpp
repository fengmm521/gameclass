//
//  MainCityScence.cpp
//  game1
//
//  Created by 俊盟科技1 on 9/5/14.
//
//

#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace std;
using namespace cocostudio;

#include "MainCityScence.h"


////////
#include "FubeiMapUILayer.h"
#include "WinDialog.h"
#include "LossDialog.h"
#include "AnimationConfig.h"

#include "UiEmail.h"
#include "UiMarket.h"
#include "UiRecharge.h"
#include "UiSign.h"
#include "UiTask.h"
#include "UiVIP.h"

#include "UiTavern.h"
#include "UiDepot.h"
#include "UiCamp.h"
#include "UiArena.h"
#include "UiSmithy.h"
#include "UiHeroSet.h"
#include "UiHeroDetail.h"
#include "UiExperience.h"
#include "UiArm.h"

#include "WarNetDataManger.h"

MainCityScence::MainCityScence()
{
    m_account=nullptr;
    m_pNode=nullptr;
    m_resoursePath.clear();
    m_heroID.clear();
    m_heroArmature.clear();
    m_buttonPress=Color3B(160,160,160);
    
    
    
    
    
    
}

MainCityScence::~MainCityScence()
{
    m_resoursePath.clear();
    m_heroID.clear();
    m_heroArmature.clear();
}



bool MainCityScence::init()
{
    if ( !Layer::init() ){    return false;  }
    
    do{
        Size visibleSize = Director::getInstance()->getWinSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        //添加资源路径； 导入文件可以直接使用名字；
        setResoursePath();
        
        //加载头像
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("WarUI0.plist");
        //账号；
        m_account=Account::sharedAccount();
        //音乐；
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("maincitymusic.mp3",true);
        
        
        //导入界面
        m_pNode = GUIReader::getInstance()->widgetFromJsonFile("MainCityUI_1.ExportJson");
        this->addChild(m_pNode);
        
     
        
        
        //宝石动画;
        ArmatureDataManager::getInstance()->addArmatureFileInfo("tx_nengliangshi.ExportJson");
        Armature *armatureGem = Armature::create("tx_nengliangshi");
        armatureGem->getAnimation()->playByIndex(0);
        
        Point  pt = Helper::seekWidgetByName(m_pNode, "buttonMainCity")->getPosition();
        pt += Point(-45, -15);
        armatureGem->setPosition(pt);
        m_pNode->addChild(armatureGem);
        
        
        
       //英雄走动传入参数赋值；

        initHeroST(m_account->m_campST.m_mainCamp);     //初始化英雄动画结构体；
        heroLoad();               //初始位置；
        
        
        //定时器；
        //this->monsterCallback1(0);
        this->schedule(schedule_selector(MainCityScence::monsterCallback1),8.0f,-1,0.5);
       // this->monsterCallback2(0);
        this->schedule(schedule_selector(MainCityScence::monsterCallback2), 6.0f);
        
        //this->monsterCallback3(0);
        this->schedule(schedule_selector(MainCityScence::monsterCallback3),7.0f,-1,1);
        //this->monsterCallback4(0);
        this->schedule(schedule_selector(MainCityScence::monsterCallback4), 5.0f);
        //this->monsterCallback5(0);
        this->schedule(schedule_selector(MainCityScence::monsterCallback5),9.0f,-1,0.4);

        
        
        this->schedule(schedule_selector(MainCityScence::monsterCallback6),0.1f);
        
        //按钮；
        buttonLoad();
        

    }while (0);
    
    if (WarNetDataManger::sharedWarNetDataManger()->m_reopenWarLayer) {
        WarNetDataManger::sharedWarNetDataManger()->m_reopenWarLayer = false;
        this->openUI("buttonWarpath" , 1);
    }
    
    
    return  true;
}




void  MainCityScence::setResoursePath(){      //=====添加整个工程的资源路径；
    
    m_resoursePath.push_back("bar");
    m_resoursePath.push_back("fonts");
    m_resoursePath.push_back("map");
    m_resoursePath.push_back("particle");
    m_resoursePath.push_back("skill");
    m_resoursePath.push_back("skill/skillbuff");
    m_resoursePath.push_back("skill/skillbullet");
    m_resoursePath.push_back("skill/skillsjtx");
    
    m_resoursePath.push_back("sound");
    m_resoursePath.push_back("sound/skillsound");
    
    m_resoursePath.push_back("sprite/1001");
    m_resoursePath.push_back("sprite/1002");
    m_resoursePath.push_back("sprite/1003");
    m_resoursePath.push_back("sprite/1004");
    m_resoursePath.push_back("sprite/1008");
    m_resoursePath.push_back("sprite/1010");
    m_resoursePath.push_back("sprite/1012");
    m_resoursePath.push_back("sprite/1015");
    m_resoursePath.push_back("sprite/1029");
    m_resoursePath.push_back("sprite/1501");
    m_resoursePath.push_back("sprite/1502");
    m_resoursePath.push_back("sprite/1503");
    m_resoursePath.push_back("sprite/1504");
    m_resoursePath.push_back("sprite/1505");
    m_resoursePath.push_back("sprite/1506");
    m_resoursePath.push_back("sprite/6003");
    m_resoursePath.push_back("sprite/tx_nengliangshi_1");
    
    m_resoursePath.push_back("test");
    
    m_resoursePath.push_back("ui/FubeiMapUI");
    m_resoursePath.push_back("ui/FubeiUI");
    m_resoursePath.push_back("ui/MainCityUI");
    m_resoursePath.push_back("ui/tx");
    m_resoursePath.push_back("ui/VIPRecharge");
    m_resoursePath.push_back("ui/WarUI");
    m_resoursePath.push_back("ui/winLoss");
    
    m_resoursePath.push_back("xml");
    
    FileUtils::getInstance()->setSearchPaths(m_resoursePath);
    
    
}



///////////////功能函数；

//定时器；
void  MainCityScence::monsterCallback1(float  dt1)     //====定时器0英雄怪物移动8；
{
    if(m_heroArmature.size()>0){
        heroMove(m_heroArmature[0],  dt1);
    }
}

void  MainCityScence::monsterCallback2(float  dt2)     //====定时器1英雄怪物移动6；
{
    
   if(m_heroArmature.size()>1){
       heroMove(m_heroArmature[1], dt2);
   }

}
void  MainCityScence::monsterCallback3(float  dt3)     //====定时器2英雄怪物移动7；
{
    if(m_heroArmature.size()>2){heroMove(m_heroArmature[2],  dt3);}
}

void  MainCityScence::monsterCallback4(float  dt4)     //====定时器3英雄怪物移动5；
{
    
    if(m_heroArmature.size()>3){heroMove(m_heroArmature[3], dt4);}
    
}
void  MainCityScence::monsterCallback5(float  dt5)     //====定时器4英雄怪物移动9；
{
    if(m_heroArmature.size()>4){heroMove(m_heroArmature[4],  dt5);}
}




void  MainCityScence::monsterCallback6(float  dt)     //====定时器6设置Z坐标0.1；
{
    for(int i=0;  i<m_heroArmature.size();i++){
        
        setZ(m_heroArmature[i].armature,m_heroArmature[i].Dialog );      //位置和Z；
       
    }
    
    
}



void  MainCityScence::setZ(Armature *armatureHero, ImageView *textDialog)   //==位置和Z；
{
    Point  p=armatureHero->getPosition();
    armatureHero->setZOrder(1280-p.y);
    textDialog->setZOrder(1280-p.y);
    
}

Armature *  MainCityScence::getArmature(string  ID){           //===用ID获取动画；
    
    string  str=ID+".ExportJson";
    ArmatureDataManager::getInstance()->addArmatureFileInfo(str);
    Armature *armature= Armature::create(ID);
    armature->getAnimation()->play(kAnimationStand);
    armature->setScale(0.75);
    armature->setScaleX(-0.75);
    m_pNode->addChild(armature);
    return armature;

}



void  MainCityScence::heroLoad()//===初始位置
{
  for(int i=0;  i<m_heroArmature.size();i++){
      m_heroArmature[i].armature->setPosition(m_heroArmature[i].pointV[m_heroArmature[i].vIndex]);

  }
    
}



void  MainCityScence::initHeroST(vector<string> heroID){            //初始化英雄动画结构体；(英雄ID)
    
    //清空；
    if(m_heroArmature.size()>0){
    
        for(int i=(int)m_heroArmature.size()-1;  i>=0;i--){
            m_heroArmature[i].armature->removeFromParent();
            m_heroArmature[i].Dialog->removeFromParent();
            m_heroArmature[i].vIndex=0;
            m_heroArmature[i].stop=true;
            m_heroArmature[i].Direction=true;
            m_heroArmature[i].pointV.clear();
            m_heroArmature[i].showWordV.clear();
            
        }
        m_heroArmature.clear();
    }
    //
    for(int i=0;  i<heroID.size();i++){

        HERO   hero1;
        //英雄动画；
        hero1.armature=getArmature(heroID[i]);
        
        //对话框；
        hero1.Dialog=static_cast<ImageView*>(Helper::seekWidgetByName(m_pNode, "imageDialog")->clone());
        hero1.Dialog->setPosition(hero1.armature->getPosition()+Point(0, 100));
        hero1.Dialog->setVisible(false);
        m_pNode->addChild(hero1.Dialog);
        static_cast<ImageView*>(Helper::seekWidgetByName(m_pNode, "imageDialog"))->setVisible(false);
        
        
        hero1.vIndex=0;                        //起点的索引；
        
        hero1.stop=true;                        //是否站立；
      
        hero1.Direction=true;                  //行走方向；
        
        
        //TILED定位点容器；
        hero1.pointV.clear();
        
        TMXTiledMap*  mapObject=nullptr;
        
        mapObject= TMXTiledMap::create("ui/tt.tmx");                  //TMX地图
        addChild(mapObject);
       
        string obj="ob"+to_string(i+1);                                       /////++==
        
        TMXObjectGroup*  group = mapObject->getObjectGroup(obj);          //TMX地图中地对象层名字;
        ValueVector objects = group->getObjects();                        // 获取全部对象；
        
        for (const auto v : objects)
        {
            const ValueMap dict = v.asValueMap();
            Point  p=Point(0,0);
            p.x=dict.at("x").asInt();                          //每块的宽40，高40；  //转换成像素坐标；
            p.y=dict.at("y").asInt();                             //Y是从上面开始的；
            hero1.pointV.push_back(p);                          //vector <Point>  pointV;
           

            
        }
        
        
        //显示的信息容器；
        hero1.showWordV.clear();
        string  str=m_account->m_heroProperty[atoi(heroID[i].c_str())].table.hero_dialoge;   //读取表中的数据；
        vector<string> strV;
        StrSplit   ss;
        ss.split(str, ";", strV);
        for (string  str1:strV) {
            hero1.showWordV.push_back(str1);
        }
        
       m_heroArmature.push_back(hero1);              //走动的英雄ID集；
    }
    


}



void  MainCityScence::heroMove(HERO  & hero,  float & moveT)
{
    
    //位置和Z；
    do{
        int sizev = (int)hero.showWordV.size();
        if(hero.Direction)
        {
            //改变方向；
            if(hero.pointV[hero.vIndex].x>hero.pointV[hero.vIndex+1].x)  {  hero.armature->setScaleX(-0.75);hero.armature->setScaleY(0.75);}  //
            else{  hero.armature->setScaleX(0.75); hero.armature->setScaleY(0.75);}
            
            //站立；
            
            if (hero.vIndex==1||hero.vIndex==5||hero.vIndex==8) { hero.stop=false; }   //不站立的点；
            if (hero.stop==true) {
                
                hero.Dialog->setVisible(true);
                Text  *textGold = static_cast<Text*>(Helper::seekWidgetByName(hero.Dialog, "labelDialog"));
                textGold->setString(hero.showWordV[rand()%sizev]);
                
                hero.armature->getAnimation()->play(kAnimationStand);
                hero.vIndex--;
                hero.stop=false;
                
            }
            else{
                hero.Dialog->setVisible(false);
                hero.armature->getAnimation()->play(kAnimationRun);
                hero.stop=true;
            }
            
            //移动；
            hero.armature->runAction(MoveTo::create(moveT,hero.pointV[hero.vIndex+1]));
            hero.Dialog->setPosition(hero.armature->getPosition()+Point(0,hero.armature->getContentSize().height/2));
            hero.Dialog->setAnchorPoint(Point(0.3,0));
            hero.Dialog->setScale(0.1);
            hero.Dialog->runAction(ScaleTo::create(0.3, 1));
            
            
            hero.vIndex++;
            if (hero.vIndex==hero.pointV.size()-1) {   hero.Direction=false;  hero.stop=true; }    //往回走；
        }  //if;
        
        else
        {
            //改变方向；
            if(hero.pointV[hero.vIndex].x>hero.pointV[hero.vIndex-1].x)  {  hero.armature->setScaleX(-0.75);hero.armature->setScaleY(0.75);}
            else{  hero.armature->setScaleX(0.75); hero.armature->setScaleY(0.75);}
            
            //站立；
            if (hero.stop==true) {
                hero.Dialog->setVisible(true);
                Text  *textGold = static_cast<Text*>(Helper::seekWidgetByName(hero.Dialog, "labelDialog"));
                textGold->setString(hero.showWordV[hero.vIndex%sizev]);
                hero.armature->getAnimation()->play(kAnimationStand);
                hero.vIndex++;
                hero.stop=false;
            }
            else{
                hero.Dialog->setVisible(false);
                hero.armature->getAnimation()->play(kAnimationRun);
                hero.stop=true;
            }
            
            
            //移动；
            hero.armature->runAction(MoveTo::create(moveT,hero.pointV[hero.vIndex-1]));
            hero.Dialog->setPosition(hero.armature->getPosition()+Point(0,hero.armature->getContentSize().height/2));
            hero.Dialog->setAnchorPoint(Point(0.3,0));
            hero.Dialog->setScale(0.1);
            hero.Dialog->runAction(ScaleTo::create(0.3, 1));
            
            hero.vIndex--;
            if (hero.vIndex==0) {   hero.Direction=true;  hero.stop=true;  }
            
        }  //else;
        
    }while (0);
    
}





/////////////////////////////////////////////////////////////////
/////////////////设置文本；

void  MainCityScence::setTextLevel(std::string  str)
{
    Text  *textLevel = static_cast<Text*>(Helper::seekWidgetByName(m_pNode, "textLevel"));
    if (!textLevel){ return ; }
    textLevel->setString(str);
    
}
void  MainCityScence::setTextName(std::string  str)
{
    Text  *textName = static_cast<Text*>(Helper::seekWidgetByName(m_pNode, "textName"));
    if (!textName){ return; }
    textName->setString(str);
    
}
void  MainCityScence::setTextScore(std::string  str)
{
    Text  *textScore = static_cast<Text*>(Helper::seekWidgetByName(m_pNode, "textScore"));
    if (!textScore){ return; }
    textScore->setString(str);
    
}
void  MainCityScence::setTextGold(std::string  str)
{
    Text  *textGold = static_cast<Text*>(Helper::seekWidgetByName(m_pNode, "textGold"));
    if (!textGold){ return ; }
    textGold->setString(str);
    
}

void  MainCityScence::setTextDialog(std::string  str)
{
    Text  *textGold = static_cast<Text*>(Helper::seekWidgetByName(m_pNode, "labelDialog"));
    if (!textGold){ return ; }
    textGold->setString(str);
    
}



/////////////////////////////////////////////////////////////////
/////////按钮函数；

bool  MainCityScence::buttonLoad()
{
    Button  *buttonMainCity = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonMainCity"));             //1主城
    if (!buttonMainCity){ log("MainCityScence::button----error");return false; }
    buttonMainCity->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    
    
//    Button  *buttonUnion = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonUnion"));                  //2联盟
//    if (!buttonUnion){ return false; }
//    buttonUnion->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
//    //buttonUnion->setZOrder(1280-buttonUnion->getPositionY()+buttonUnion->getContentSize().height/2);
//    //buttonUnion->setAnchorPoint(Point(0.5,0));
    
    Button  *buttonMinerals = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonMarket"));             //3 市场
    if (!buttonMinerals){ log("MainCityScence::button----error");return false; }
    buttonMinerals->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    buttonMinerals->setZOrder(1280-buttonMinerals->getPositionY()+buttonMinerals->getContentSize().height/2);
    //buttonMinerals->setAnchorPoint(Point(0.5,0));
    
    Button  *buttonArena = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonArena"));                     // 4竞技场
    if (!buttonArena){ log("MainCityScence::button----error");return false; }
    buttonArena->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    buttonArena->setZOrder(1280-buttonArena->getPositionY()+buttonArena->getContentSize().height/2);
    //buttonCamp->setAnchorPoint(Point(0.5,0));
    
    Button  *buttonTavern = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonTavern"));                //5酒馆
    if (!buttonTavern){ log("MainCityScence::button----error");return false; }
    buttonTavern->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    //buttonTavern->setZOrder(1280-buttonTavern->getPositionY()+buttonTavern->getContentSize().height/2);
    //buttonTavern->setAnchorPoint(Point(0.5,0));
    
    Button  *buttonPrison = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonPrison"));                //6监狱
    if (!buttonPrison){ log("MainCityScence::button----error");return false; }
    buttonPrison->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    buttonPrison->setZOrder(1280-buttonPrison->getPositionY()+buttonPrison->getContentSize().height/2);
    //buttonPrison->setAnchorPoint(Point(0.5,0));
    
    Button  *buttonWarpath = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonWarpath"));              //7征战
    if (!buttonWarpath){ log("MainCityScence::button----error");return false; }
    buttonWarpath->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    buttonWarpath->setZOrder(1280-buttonWarpath->getPositionY()+buttonWarpath->getContentSize().height/2);
    //buttonWarpath->setAnchorPoint(Point(0.5,0));
    
    Button  *buttonCasern = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonExpedition"));                //8 远征
    if (!buttonCasern){ log("MainCityScence::button----error");return false; }
    buttonCasern->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    // buttonCasern->setZOrder(1280-buttonCasern->getPositionY()+buttonCasern->getContentSize().height/2);
    // buttonCasern->setAnchorPoint(Point(0.5,0));
    
    Button  *buttonSmithy = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonSmithy"));                 //9铁匠铺
    if (!buttonSmithy){ log("MainCityScence::button----error");return false; }
    buttonSmithy->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    buttonSmithy->setZOrder(1280-buttonSmithy->getPositionY()+buttonSmithy->getContentSize().height/2);
    //buttonSmithy->setAnchorPoint(Point(0.5,0));
    
    //下边的按钮
    Button  *buttonHero = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonHero"));             //10英雄
    if (!buttonHero){ log("MainCityScence::button----error");return false; }
    buttonHero->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    
    Button  *buttonEmail = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonEmail"));           //11邮箱
    if (!buttonEmail){ log("MainCityScence::button----error");return false; }
    buttonEmail->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    
    Button  *buttonTask = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonTask"));             //12任务
    if (!buttonTask){ log("MainCityScence::button----error");return false; }
    buttonTask->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    
    Button  *buttonDepot = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonDepot"));            //13仓库
    if (!buttonDepot){ log("MainCityScence::button----error");return false; }
    buttonDepot->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    
    Button  *buttonCamp = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonCamp"));            //14阵容
    if (!buttonCamp){ log("MainCityScence::button----error");return false; }
    buttonCamp->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    
    Button  *buttonAddScore = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonAddScore"));      //15加分
    if (!buttonAddScore){ log("MainCityScence::button----error");return false; }
    buttonAddScore->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    
    Button  *buttonAddGold = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonAddGold"));         //16加钱
    if (!buttonAddGold){ log("MainCityScence::button----error");return false; }
    buttonAddGold->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    
    Button  *buttonHead = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "buttonHead"));                //17头像
    if (!buttonHead){ log("MainCityScence::button----error");return false; }
    buttonHead->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));

    //新增，左边的按钮
    Button  *button1 = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "button1"));                //18状态
    if (!button1){ log("MainCityScence::button----error");return false; }
    button1->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    button1->setTag(18);
    button1->setZOrder(1280);
    
    Button  *button2 = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "button2"));                //19VIP
    if (!button2){ log("MainCityScence::button----error");return false; }
    button2->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    button2->setTag(19);
    button2->setZOrder(1280);
    
    Button  *button3 = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "button3"));                //20充值
    if (!button3){ log("MainCityScence::button----error");return false; }
    button3->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    button3->setTag(20);
    button3->setZOrder(1280);
    
    Button  *button4 = static_cast<Button*>(Helper::seekWidgetByName(m_pNode, "button4"));                //21登录
    if (!button4){ log("MainCityScence::button----error");return false; }
    button4->addTouchEventListener(CC_CALLBACK_2(MainCityScence::buttonEvent, this));
    button4->setTag(21);
    button4->setZOrder(1280);
    
    return  true;
}




void  MainCityScence::buttonEvent(Ref *pSender, Widget::TouchEventType   type){
    
    Button  * button=static_cast<Button*>(pSender);
    string  str=button->getName();
    int  tag=button->getTag();
    
    //公共部分；
    switch (type)
    {
        case  Widget::TouchEventType::BEGAN:
        {
            button->setColor(m_buttonPress);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Click_Button.wav");
            
        }
            break;
        case  Widget::TouchEventType::MOVED:
        {
  
            button->setColor(Color3B(255,255,255));
        }
            break;
            
        case  Widget::TouchEventType::ENDED:
        {
            
            button->setColor(Color3B(255,255,255));
            
            openUI(str ,tag);    //----打开界面；
            
        }
            break;
            
        case  Widget::TouchEventType::CANCELED:
        {
            
        }
            break;
            
        default:
            break;
    }
}

void  MainCityScence::openUI(string  strUI, int tag){    //====打开界面；

    string  str=strUI;
    
    string  str1="buttonMainCity";
    //string  str2="buttonUnion";
    string  str3="buttonMarket";
    string  str4="buttonArena";
    string  str5="buttonTavern";
    string  str6="buttonPrison";
    string  str7="buttonWarpath";
    string  str8="buttonExpedition";
    string  str9="buttonSmithy";
    
    string  str10="buttonHero";
    string  str11="buttonEmail";
    string  str12="buttonTask";
    string  str13="buttonDepot";
    string  str14="buttonCamp";
    string  str15="buttonAddScore";
    string  str16="buttonAddGold";
    string  str17="buttonHead";
    
    if (str==str1) {
        UiSign* uiSign=UiSign::create();              //签到，需要修改；
        this->addChild(uiSign);
    }
//    else if(str==str2){
//
//        
//    }
    
    else if(str==str3){
        UiMarket* uiMarket=UiMarket::create();        //3市场，
        this->addChild(uiMarket);
        
       
        
    }
    else if(str==str4){                              //4竞技场，
        
        UiArena* uiArena=UiArena::create();          //
        this->addChild(uiArena);
        

        
    }
    else if(str==str5){                              //5酒馆
        UiTavern* uiTavern=UiTavern::create();
        this->addChild(uiTavern);
        
    }
    
    else if(str==str6){                             //6监狱
        UiExperience*  experience=UiExperience::create();          //经验， 需要换；
        this->addChild(experience);
        
    }
    else if(str==str7){                            //7征战
        FubeiMapUILayer* fubeiMap = FubeiMapUILayer::createForScence(this);
        this->addChild(fubeiMap);

    }
    
    else if(str==str8){                           //8远征

        UiArm* uiArm=UiArm::create();                            //武器，需要换；
        this->addChild(uiArm);
    }
    
    else if(str==str9){                           //9铁匠铺
        UiSmithy* uiSmithy=UiSmithy::create();
        this->addChild(uiSmithy);
        
    }
    
    ////
    else if(str==str10){                         //10英雄
        UiHeroSet* herol = UiHeroSet::create();
        this->addChild(herol);
        
    }
    else if(str==str11){                       //11邮箱
        UiEmail* uiEmail=UiEmail::create();
        this->addChild(uiEmail);
        
    }
    
    else if(str==str12){                       //12任务
        UiTask* uiTask=UiTask::create();
        this->addChild(uiTask);
        
    }
    else if(str==str13){                       //13仓库
        UiDepot* uiDepot=UiDepot::create();
        this->addChild(uiDepot);
        
    }
    
    else if(str==str14){                      //14阵容
       UiCamp* uiCamp=UiCamp::create();
       uiCamp->setType(2);    //标明是谁打开的；
        uiCamp->setCamp();
       this->addChild(uiCamp);
        
    }
    else if(str==str15){                      //15加分
        
        
    }
    
    else if(str==str16){                     //16加钱
        
        
    }
    else if(str==str17){                    //17  帐号信息；
        
        
    }

    ///////////
    else if(tag==18){                    //18状态
        
        
    }
    
    else if(tag==19){                  //19VIP
        UiVIP* uiVIP=UiVIP::create();
        this->addChild(uiVIP);
        
    }

    else if(tag==20){               //20充值
        UiRecharge* uiRecharge=UiRecharge::create();
        this->addChild(uiRecharge);
        
    }
    
    else if(tag==21){              //21登录
        
        
    }
    
    
    
}



















