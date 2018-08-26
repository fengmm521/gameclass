//
//  LocalDataManger.h
//  game1
//  C++单例类模板，非线程安全单例类，并且实例化后会常注内存
//
//  Created by 俊盟科技1 on 8/22/14.
//
//  本地数据管理类
//

#ifndef __game1__LocalDataManger__
#define __game1__LocalDataManger__

#include "cocos2d.h"
#include "LocalDataConfig.h"
using namespace std;
class LocalDataManger:public cocos2d::Ref
{
public:
    static LocalDataManger* sharedLocalDataManger();
    static void destroyInstance();
private:
    /**
     * @js ctor
     */
    LocalDataManger(void);
    /**
     * @js NA
     * @lua NA
     */
    ~LocalDataManger(void);
    
    map<int,Configtab_card_attribute_sysDataST>  maptab_card_attribute_sysData;
    map<int,Configtab_card_quality_sysDataST>  maptab_card_quality_sysData;
    map<int,Configtab_card_star_sysDataST>  maptab_card_star_sysData;
    map<int,Configtab_charge_databaseDataST>  maptab_charge_databaseData;
    map<int,Configtab_checkpoints_sysDataST>  maptab_checkpoints_sysData;
    map<int,Configtab_city_expDataST>  maptab_city_expData;
    map<int,Configtab_equipbase_sysDataST>  maptab_equipbase_sysData;
    map<int,Configtab_hero_group_sysDataST>  maptab_hero_group_sysData;
    map<int,Configtab_intensify_demand_sysDataST>  maptab_intensify_demand_sysData;
    map<int,Configtab_item_base_sysDataST>  maptab_item_base_sysData;
    map<int,Configtab_lottery_baseDataST>  maptab_lottery_baseData;
    map<int,Configtab_lottery_data_sysDataST>  maptab_lottery_data_sysData;
    map<int,Configtab_market_database_sysDataST>  maptab_market_database_sysData;
    map<int,Configtab_monster_additionDataST>  maptab_monster_additionData;
    map<int,Configtab_pvp_item_sysDataST>  maptab_pvp_item_sysData;
    map<int,Configtab_pvp_rank_sysDataST>  maptab_pvp_rank_sysData;
    map<int,Configtab_pvp_timesDataST>  maptab_pvp_timesData;
    map<int,Configtab_sign_data_sysDataST>  maptab_sign_data_sysData;
    map<int,Configtab_skill_effectDataST>  maptab_skill_effectData;
    map<int,Configtab_skill_trajectoryDataST>  maptab_skill_trajectoryData;
    map<int,Configtab_skill_upgradeDataST>  maptab_skill_upgradeData;
    map<int,Configtab_skill_visual_effectDataST>  maptab_skill_visual_effectData;
    map<int,Configtab_task_sysDataST>  maptab_task_sysData;
    map<int,Configtab_vip_sysDataST>  maptab_vip_sysData;

    string getXmlFile(string path);
public:
    
    /**
     * Init LocalDataManger
     */
    virtual bool init();

    void readConfigtab_card_attribute_sysData();
    Configtab_card_attribute_sysDataST  getConfigtab_card_attribute_sysDataST(int ID);

    void readConfigtab_card_quality_sysData();
    Configtab_card_quality_sysDataST  getConfigtab_card_quality_sysDataST(int ID);

    void readConfigtab_card_star_sysData();
    Configtab_card_star_sysDataST  getConfigtab_card_star_sysDataST(int ID);

    void readConfigtab_charge_databaseData();
    Configtab_charge_databaseDataST  getConfigtab_charge_databaseDataST(int ID);

    void readConfigtab_checkpoints_sysData();
    Configtab_checkpoints_sysDataST  getConfigtab_checkpoints_sysDataST(int ID);

    void readConfigtab_city_expData();
    Configtab_city_expDataST  getConfigtab_city_expDataST(int ID);

    void readConfigtab_equipbase_sysData();
    Configtab_equipbase_sysDataST  getConfigtab_equipbase_sysDataST(int ID);

    void readConfigtab_hero_group_sysData();
    Configtab_hero_group_sysDataST  getConfigtab_hero_group_sysDataST(int ID);

    void readConfigtab_intensify_demand_sysData();
    Configtab_intensify_demand_sysDataST  getConfigtab_intensify_demand_sysDataST(int ID);

    void readConfigtab_item_base_sysData();
    Configtab_item_base_sysDataST  getConfigtab_item_base_sysDataST(int ID);

    void readConfigtab_lottery_baseData();
    Configtab_lottery_baseDataST  getConfigtab_lottery_baseDataST(int ID);

    void readConfigtab_lottery_data_sysData();
    Configtab_lottery_data_sysDataST  getConfigtab_lottery_data_sysDataST(int ID);

    void readConfigtab_market_database_sysData();
    Configtab_market_database_sysDataST  getConfigtab_market_database_sysDataST(int ID);

    void readConfigtab_monster_additionData();
    Configtab_monster_additionDataST  getConfigtab_monster_additionDataST(int ID);

    void readConfigtab_pvp_item_sysData();
    Configtab_pvp_item_sysDataST  getConfigtab_pvp_item_sysDataST(int ID);

    void readConfigtab_pvp_rank_sysData();
    Configtab_pvp_rank_sysDataST  getConfigtab_pvp_rank_sysDataST(int ID);

    void readConfigtab_pvp_timesData();
    Configtab_pvp_timesDataST  getConfigtab_pvp_timesDataST(int ID);

    void readConfigtab_sign_data_sysData();
    Configtab_sign_data_sysDataST  getConfigtab_sign_data_sysDataST(int ID);

    void readConfigtab_skill_effectData();
    Configtab_skill_effectDataST  getConfigtab_skill_effectDataST(int ID);

    void readConfigtab_skill_trajectoryData();
    Configtab_skill_trajectoryDataST  getConfigtab_skill_trajectoryDataST(int ID);

    void readConfigtab_skill_upgradeData();
    Configtab_skill_upgradeDataST  getConfigtab_skill_upgradeDataST(int ID);

    void readConfigtab_skill_visual_effectData();
    Configtab_skill_visual_effectDataST  getConfigtab_skill_visual_effectDataST(int ID);

    void readConfigtab_task_sysData();
    Configtab_task_sysDataST  getConfigtab_task_sysDataST(int ID);

    void readConfigtab_vip_sysData();
    Configtab_vip_sysDataST  getConfigtab_vip_sysDataST(int ID);

    
};

#endif /* defined(__game1__LocalDataManger__) */