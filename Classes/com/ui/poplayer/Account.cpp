/**********************************************
 账号类；
  与服务器的接口；
 **********************************************/

#include "Account.h"

using namespace cocos2d::ui;


Account::Account(){
    //m_hero=null;
    m_accountID="";
    m_message100="";
    m_message105="";
    m_sendTrue100=true;
    m_sendTrue105=true;
    m_second=0;
}

Account::~Account(){
    
    m_hero.clear();                //一个账号里的英雄
    m_heroProperty.clear();        //一个英雄的属性；
    
    m_skill.clear();                //一个账号里的技能
    m_skillProperty.clear();         //技能；
    
    m_equip.clear();               //一个账号里的装备
    m_equipProperty.clear();        //装备；
    
    m_prop.clear();                //一个账号里的道具
    m_propProperty.clear();         //道具；材料
    
    m_campST.m_mainCamp.clear();        //阵容;
    m_campST.m_arenaCamp.clear();
    
    
    
}



//账号；
//static Account* s_account=Account::sharedAccount();
static Account* s_account=nullptr;            //

Account*  Account::sharedAccount()
{
    if (s_account == nullptr)
    {
        s_account= new Account();
        //if (s_account){  s_account->m_accountID=accountID;  }
        if (!s_account|| !s_account->init()){ CC_SAFE_DELETE(s_account);}
    }
    return s_account;
}

static  void  destroyAccount(){

  CC_SAFE_RELEASE_NULL(s_account);
}





bool Account::init()
{
    //if(!Node::init()){ return false;}
    
    //网络;
    m_connect=false;   //是否连接上服务器；
    
    
    
    
    
    //英雄；   一个账号有多少个英雄，放入m_hero就行；  每个英雄的属性由setHero设置结构体里设置；
    m_hero.clear();
    
 
    m_hero.push_back("1001");
    m_hero.push_back("1002");
    m_hero.push_back("1003");
    m_hero.push_back("1004");
    m_hero.push_back("1008");
    m_hero.push_back("1010");
    m_hero.push_back("1012");
    m_hero.push_back("1015");
    m_hero.push_back("1029");
    
    
    setHero();     //------
    
    
    //技能；
    m_skill.clear();
    
    m_skill.push_back("210010");
    m_skill.push_back("210011");
    m_skill.push_back("210012");
    m_skill.push_back("210013");
    m_skill.push_back("210014");
    m_skill.push_back("210015");
    m_skill.push_back("210016");
    m_skill.push_back("210017");
    m_skill.push_back("210018");
    m_skill.push_back("210019");

    setSkill( );           //-------
    
    //装备；
    m_equip.clear();
    
    m_equip.push_back("300001");
    m_equip.push_back("300010");
    m_equip.push_back("300019");
    m_equip.push_back("300028");
    m_equip.push_back("300037");
    m_equip.push_back("300046");
    
    m_equip.push_back("300002");
    m_equip.push_back("300011");
    m_equip.push_back("300020");
    m_equip.push_back("300029");
    m_equip.push_back("300038");
    m_equip.push_back("300047");
    
    setEquip( );  //-------
    
    
    //道具；材料；
    
    m_prop.clear();
    
    m_prop.push_back("100001");
    m_prop.push_back("100002");
    m_prop.push_back("100003");
    m_prop.push_back("100004");
    m_prop.push_back("100005");
    m_prop.push_back("100006");
    m_prop.push_back("100007");
    
    m_prop.push_back("100001");
    m_prop.push_back("100002");
    m_prop.push_back("100003");
    m_prop.push_back("100004");
    m_prop.push_back("100005");
    m_prop.push_back("100006");
    m_prop.push_back("100007");

    setProp( );  //--------
    
    
    
     //阵容
    vector<string>  camp;
    setCamp(camp, 1);     //=====阵容; (英雄ID,类型1主阵2竞技场)；
    camp.clear();
    setCamp( camp, 2);     //=====阵容; (英雄ID,类型1主阵2竞技场)；
    
    
    
   // schedule(schedule_selector(Account::sendCallback),1);

    
    return true;
}


void  Account::setAccountID(string accountID ){

    m_accountID=accountID;

}

///////////////////////
//设置结构体；默认设置；

void  Account::setHero( ){              //英雄结构体；

    if (m_hero.empty()) { log("heroID is empty");  return ;   }

    for (string str:m_hero) {
        HeroST  heroST;
        heroST.table=LocalDataManger::sharedLocalDataManger()->getConfigtab_card_attribute_sysDataST(atoi(str.c_str()));
        heroST.table.hero_level=58;
        heroST.table.hero_star=3;
        
        m_heroProperty[atoi(str.c_str())]=heroST;
    }
    


}


void  Account::setSkill( ){              //技能结构体；
    
    if (m_skill.empty()) { log("m_skill ID is empty");  return ;   }
    
    for (string str:m_skill) {
        SkillST  heroST;
        heroST.table=LocalDataManger::sharedLocalDataManger()->getConfigtab_skill_visual_effectDataST(atoi(str.c_str()));
        //heroST.table.hero_level=58;
        //heroST.table.hero_star=3;
        
        m_skillProperty[ atoi(str.c_str()) ]=heroST;
    }
    
   
    
}



void  Account::setEquip( ){              //装备结构体；
    
    if (m_equip.empty()) { log("m_equip ID is empty");  return ;   }
    
    for (string str:m_equip) {
        EquipST  heroST;
        heroST.table=LocalDataManger::sharedLocalDataManger()->getConfigtab_equipbase_sysDataST(atoi(str.c_str()));
        //heroST.table.hero_level=58;
        //heroST.table.hero_star=3;
        
        m_equipProperty[ atoi(str.c_str()) ]=heroST;
    }
    
    
}



void  Account::setProp( ){              //道具结构体；
    
    if (m_prop.empty()) { log("Prop ID is empty");  return ;   }
    
    for (string str:m_prop) {
        PropST  heroST;
        heroST.table=LocalDataManger::sharedLocalDataManger()->getConfigtab_item_base_sysDataST(atoi(str.c_str()));
        //heroST.table.hero_level=58;
        //heroST.table.hero_star=3;
        
        m_propProperty[ atoi(str.c_str()) ]=heroST;
    }
    
    
}


void  Account::setCamp(vector<string> camp, int type){     //=====阵容; (英雄ID,类型1主阵2竞技场)；
    
    if (camp.size()>0) {
        
        if(type==1){ m_campST.m_mainCamp.clear(); m_campST.m_mainCamp=camp; }
        else if(type==2){ m_campST.m_arenaCamp.clear(); m_campST.m_arenaCamp=camp; }
    }
    else{
        if(type==1){
             m_campST.m_mainCamp.clear();
        string camp1 = UserDefault::getInstance()->getStringForKey("camp1", "1012");
        string camp2 = UserDefault::getInstance()->getStringForKey("camp2", "1002");
        string camp3 = UserDefault::getInstance()->getStringForKey("camp3", "1029");
        string camp4 = UserDefault::getInstance()->getStringForKey("camp4", "1015");
        string camp5 = UserDefault::getInstance()->getStringForKey("camp5", "1004");
        m_campST.m_mainCamp.push_back(camp1);
        m_campST.m_mainCamp.push_back(camp2);
        m_campST.m_mainCamp.push_back(camp3);
        m_campST.m_mainCamp.push_back(camp4);
        m_campST.m_mainCamp.push_back(camp5);
        }
        if(type==2){
            m_campST.m_arenaCamp.clear();
           // m_campST.m_arenaCamp.push_back("1001");
            m_campST.m_arenaCamp.push_back("1002");
            m_campST.m_arenaCamp.push_back("1003");
            m_campST.m_arenaCamp.push_back("1008");
            m_campST.m_arenaCamp.push_back("1010");
        }
        
    }
    
    
}



void  Account::saveCamp(){
    UserDefault::getInstance()->setStringForKey("camp1", m_campST.m_mainCamp[0]);
    UserDefault::getInstance()->setStringForKey("camp2", m_campST.m_mainCamp[1]);
    UserDefault::getInstance()->setStringForKey("camp3", m_campST.m_mainCamp[2]);
    UserDefault::getInstance()->setStringForKey("camp4", m_campST.m_mainCamp[3]);
    UserDefault::getInstance()->setStringForKey("camp5", m_campST.m_mainCamp[4]);
}



//////////////////////////////////////////////
//网络；

void  Account::sendCallback(float  dt){
    m_second++;
    if (m_second==2||m_second==10) {
        m_sendTrue100=true;
        m_sendTrue105=true;
        
    }
    
    login();

}




void Account::reciveDataHandler(std::string &data,int type,bool ispush){    //===自动接收到的服务器的信息（消息，接口号），发送消息：ClientSockeManeger::send()
    log("UiArena::  recive");
    
    if(ispush){
        log("UiArena::UiArena::push message======%s",data.c_str());
    }
    else{
        log("UiArena::UiArena::back   message===________===%s",data.c_str());
      
        if (type==100) {  m_message100=data;  }
        if (type==105) {  m_message105=data;  }
        
        
        
    }
}



void  Account::login(){
    


        //1发送设备号
        string  str100="012345";     //设备号
        
        if (m_message100==""&&m_sendTrue100){
            
            if(!m_connect){
                ClientSocketManger::sharedClientSocketManger()->connectSocket();//连接；
                m_connect=true;
            }
            else{
                send100(str100.c_str());
                log("m_message100>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%s",m_message100.c_str());
                if (m_message100!="") { m_sendTrue100=false;}
                
            }
        }
        
       else if(m_message100!=""&&m_sendTrue105){
      
            //2
           string  username="jkjkjk";
           string password="dsdsds";
        
        
            
            //md51 =   用户名+密码；
            string  str1=username+password;
           char  *ch1=const_cast<char*>(str1.c_str());
//            char  *ch1=new  char();
//            sprintf(ch1, str1.c_str());
           
           char  *md51=new  char();
            MD5  md5;
            md5.MD5Made(ch1, md51);
            log("md51>>>>>>>>>>>>>>>>>>%s",md51);
            
            //md52   = md51+设备号+服务器返回的时间；
            string  str3=md51;
           
            vector<string> skillEfectvec = StrSplit::split(m_message100,";");
            str3=str3+str100+skillEfectvec[1];
           
            char  *ch4=const_cast<char*>(str3.c_str());
//            char  *ch4=new  char();
//            sprintf(ch4, str3.c_str());
            log("md52>>>>>>>>>>>>>>>>>>%s",ch4);
            char  *md52=new  char();
            md5.MD5Made(ch4, md52);
            log("md52>>>>>>>>>>>>>>>>>>%s",md52);
            
            //发送的信息=用户名+“；”+md52
            string str5=username+";"+md52;
            send105(str5);
            log("m_message105>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%s",m_message105.c_str());

            m_sendTrue105=false;
        }
    if(!m_sendTrue105){
      log("m_message100>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%s",m_message100.c_str());
      log("m_message105>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%s",m_message105.c_str());
    }
}



void  Account::send100(string  sendstr){      //=========发送设备码；

//    if(!m_connect){
//        ClientSocketManger::sharedClientSocketManger()->connectSocket();//连接；
//        m_connect=true;
//        log("UiArena::  connect");
//    }
//    else{
      //  ClientSocketManger::sharedClientSocketManger()->send(sendstr.c_str(),100,this);  //发送；
        log("UiArena::  send");
        
  //  }

  
}


void  Account::send105(string  sendstr){   //=======（账号+密码=MD51）+设备码+时间=MD52；
    
//    if(!m_connect){
//        ClientSocketManger::sharedClientSocketManger()->connectSocket();//连接；
//        m_connect=true;
//        log("UiArena::  connect");
//    }
//    else{
      //  ClientSocketManger::sharedClientSocketManger()->send(sendstr.c_str(),105,this);  //发送；
        log("UiArena::  send");
        
//    }
    
    
}




void Account::onExit(){
    
    
   // login();
    
}

void Account::onEnter(){

    
}







