//
//  LocalDataManger.cpp
//  game1
//
//  Created by 俊盟科技1 on 8/22/14.
//
//

#include "LocalDataManger.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include "LocalFileManger.h"
using namespace rapidxml;
using namespace cocos2d;
static LocalDataManger *s_sharedLocalDataManger = nullptr;

LocalDataManger *LocalDataManger::sharedLocalDataManger()
{
    if (s_sharedLocalDataManger == nullptr)
    {
        s_sharedLocalDataManger = new LocalDataManger();
        if (!s_sharedLocalDataManger || !s_sharedLocalDataManger->init())
        {
            CC_SAFE_DELETE(s_sharedLocalDataManger);
        }
    }
    return s_sharedLocalDataManger;
}

void LocalDataManger::destroyInstance()
{
    
    CC_SAFE_RELEASE_NULL(s_sharedLocalDataManger);
}

LocalDataManger::LocalDataManger(void)
{
  
}

LocalDataManger::~LocalDataManger(void)
{
   
}


bool LocalDataManger::init()
{
    bool bRet = false;
    do
    {
        maptab_card_attribute_sysData.clear();
        maptab_card_quality_sysData.clear();
        maptab_card_star_sysData.clear();
        maptab_charge_databaseData.clear();
        maptab_checkpoints_sysData.clear();
        maptab_city_expData.clear();
        maptab_equipbase_sysData.clear();
        maptab_hero_group_sysData.clear();
        maptab_intensify_demand_sysData.clear();
        maptab_item_base_sysData.clear();
        maptab_lottery_baseData.clear();
        maptab_lottery_data_sysData.clear();
        maptab_market_database_sysData.clear();
        maptab_monster_additionData.clear();
        maptab_pvp_item_sysData.clear();
        maptab_pvp_rank_sysData.clear();
        maptab_pvp_timesData.clear();
        maptab_sign_data_sysData.clear();
        maptab_skill_effectData.clear();
        maptab_skill_trajectoryData.clear();
        maptab_skill_upgradeData.clear();
        maptab_skill_visual_effectData.clear();
        maptab_task_sysData.clear();
        maptab_vip_sysData.clear();
#if 1
        readConfigtab_card_attribute_sysData();
        readConfigtab_card_quality_sysData();
        readConfigtab_card_star_sysData();
        readConfigtab_charge_databaseData();
        readConfigtab_checkpoints_sysData();
        readConfigtab_city_expData();
        readConfigtab_equipbase_sysData();
        readConfigtab_hero_group_sysData();
        readConfigtab_intensify_demand_sysData();
        readConfigtab_item_base_sysData();
        readConfigtab_lottery_baseData();
        readConfigtab_lottery_data_sysData();
        readConfigtab_market_database_sysData();
        readConfigtab_monster_additionData();
        readConfigtab_pvp_item_sysData();
        readConfigtab_pvp_rank_sysData();
        readConfigtab_pvp_timesData();
        readConfigtab_sign_data_sysData();
        readConfigtab_skill_effectData();
        readConfigtab_skill_trajectoryData();
        readConfigtab_skill_upgradeData();
        readConfigtab_skill_visual_effectData();
        readConfigtab_task_sysData();
        readConfigtab_vip_sysData();
#endif
        bRet = true;
    }
    while (0);
    
    return bRet;
}
//tab_card_attribute_sys
void LocalDataManger::readConfigtab_card_attribute_sysData()
{
    if(!maptab_card_attribute_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_card_attribute_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *hero_namex = node->first_node("hero_name");
        xml_node<> *hero_iconx = node->first_node("hero_icon");
        xml_node<> *hero_half_imagex = node->first_node("hero_half_image");
        xml_node<> *hero_typex = node->first_node("hero_type");
        xml_node<> *hero_descriptionx = node->first_node("hero_description");
        xml_node<> *hero_facetox = node->first_node("hero_faceto");
        xml_node<> *hero_fighting_capacityx = node->first_node("hero_fighting_capacity");
        xml_node<> *hero_levelx = node->first_node("hero_level");
        xml_node<> *hero_qualityx = node->first_node("hero_quality");
        xml_node<> *hero_starx = node->first_node("hero_star");
        xml_node<> *hero_campx = node->first_node("hero_camp");
        xml_node<> *hero_skill_id1x = node->first_node("hero_skill_id1");
        xml_node<> *hero_skill_id2x = node->first_node("hero_skill_id2");
        xml_node<> *hero_skill_id3x = node->first_node("hero_skill_id3");
        xml_node<> *hero_skill_id4x = node->first_node("hero_skill_id4");
        xml_node<> *hero_skill_id5x = node->first_node("hero_skill_id5");
        xml_node<> *hero_skill_id6x = node->first_node("hero_skill_id6");
        xml_node<> *hero_skillrelease_rulex = node->first_node("hero_skillrelease_rule");
        xml_node<> *energy_poolx = node->first_node("energy_pool");
        xml_node<> *injured_conversion_factorx = node->first_node("injured_conversion_factor");
        xml_node<> *attack_conversion_factorx = node->first_node("attack_conversion_factor");
        xml_node<> *hero_powerx = node->first_node("hero_power");
        xml_node<> *power_growx = node->first_node("power_grow");
        xml_node<> *agilex = node->first_node("agile");
        xml_node<> *agile_growx = node->first_node("agile_grow");
        xml_node<> *mentalx = node->first_node("mental");
        xml_node<> *mental_growx = node->first_node("mental_grow");
        xml_node<> *hero_hpx = node->first_node("hero_hp");
        xml_node<> *physics_actx = node->first_node("physics_act");
        xml_node<> *magic_strengthx = node->first_node("magic_strength");
        xml_node<> *armorx = node->first_node("armor");
        xml_node<> *magic_resistx = node->first_node("magic_resist");
        xml_node<> *physics_critx = node->first_node("physics_crit");
        xml_node<> *magic_critx = node->first_node("magic_crit");
        xml_node<> *hp_restorex = node->first_node("hp_restore");
        xml_node<> *energy_restorex = node->first_node("energy_restore");
        xml_node<> *armor_strikex = node->first_node("armor_strike");
        xml_node<> *ignore_magic_resistx = node->first_node("ignore_magic_resist");
        xml_node<> *cure_effect_promotex = node->first_node("cure_effect_promote");
        xml_node<> *hero_hitx = node->first_node("hero_hit");
        xml_node<> *hero_evadex = node->first_node("hero_evade");
        xml_node<> *suck_blood_levelx = node->first_node("suck_blood_level");
        xml_node<> *move_speedx = node->first_node("move_speed");
        xml_node<> *attact_intervalx = node->first_node("attact_interval");
        xml_node<> *group_hero_idx = node->first_node("group_hero_id");
        xml_node<> *hero_dialogex = node->first_node("hero_dialoge");
        xml_node<> *voice_resourcex = node->first_node("voice_resource");
        xml_node<> *skill_buff_coorx = node->first_node("skill_buff_coor");
        xml_node<> *skill_hit_coorx = node->first_node("skill_hit_coor");
        xml_node<> *skill_track_coorx = node->first_node("skill_track_coor");
        xml_node<> *star_quenex = node->first_node("star_quene");
        xml_node<> *star_shard_needsx = node->first_node("star_shard_needs");
        Configtab_card_attribute_sysDataST st;

        st.ID = atoi(idx->value());
        st.hero_name = hero_namex->value();
        st.hero_icon = hero_iconx->value();
        st.hero_half_image = hero_half_imagex->value();
        st.hero_type = atoi(hero_typex->value());
        st.hero_description = hero_descriptionx->value();
        st.hero_faceto = atoi(hero_facetox->value());
        st.hero_fighting_capacity = atoi(hero_fighting_capacityx->value());
        st.hero_level = atoi(hero_levelx->value());
        st.hero_quality = atoi(hero_qualityx->value());
        st.hero_star = atoi(hero_starx->value());
        st.hero_camp = atoi(hero_campx->value());
        st.hero_skill_id1 = atoi(hero_skill_id1x->value());
        st.hero_skill_id2 = atoi(hero_skill_id2x->value());
        st.hero_skill_id3 = atoi(hero_skill_id3x->value());
        st.hero_skill_id4 = atoi(hero_skill_id4x->value());
        st.hero_skill_id5 = atoi(hero_skill_id5x->value());
        st.hero_skill_id6 = atoi(hero_skill_id6x->value());
        st.hero_skillrelease_rule = hero_skillrelease_rulex->value();
        st.energy_pool = atoi(energy_poolx->value());
        st.injured_conversion_factor = atof(injured_conversion_factorx->value());
        st.attack_conversion_factor = atof(attack_conversion_factorx->value());
        st.hero_power = atoi(hero_powerx->value());
        st.power_grow = atof(power_growx->value());
        st.agile = atoi(agilex->value());
        st.agile_grow = atof(agile_growx->value());
        st.mental = atoi(mentalx->value());
        st.mental_grow = atof(mental_growx->value());
        st.hero_hp = atoi(hero_hpx->value());
        st.physics_act = atoi(physics_actx->value());
        st.magic_strength = atoi(magic_strengthx->value());
        st.armor = atoi(armorx->value());
        st.magic_resist = atoi(magic_resistx->value());
        st.physics_crit = atoi(physics_critx->value());
        st.magic_crit = atoi(magic_critx->value());
        st.hp_restore = atoi(hp_restorex->value());
        st.energy_restore = atoi(energy_restorex->value());
        st.armor_strike = atoi(armor_strikex->value());
        st.ignore_magic_resist = atoi(ignore_magic_resistx->value());
        st.cure_effect_promote = atoi(cure_effect_promotex->value());
        st.hero_hit = atoi(hero_hitx->value());
        st.hero_evade = atoi(hero_evadex->value());
        st.suck_blood_level = atoi(suck_blood_levelx->value());
        st.move_speed = atoi(move_speedx->value());
        st.attact_interval = atoi(attact_intervalx->value());
        st.group_hero_id = atoi(group_hero_idx->value());
        st.hero_dialoge = hero_dialogex->value();
        st.voice_resource = voice_resourcex->value();
        st.skill_buff_coor = skill_buff_coorx->value();
        st.skill_hit_coor = skill_hit_coorx->value();
        st.skill_track_coor = skill_track_coorx->value();
        st.star_quene = atoi(star_quenex->value());
        st.star_shard_needs = star_shard_needsx->value();

        maptab_card_attribute_sysData[st.ID] = st;
    }
}
Configtab_card_attribute_sysDataST LocalDataManger::getConfigtab_card_attribute_sysDataST(int ID)
{
    return maptab_card_attribute_sysData[ID];
}

//tab_card_quality_sys
void LocalDataManger::readConfigtab_card_quality_sysData()
{
    if(!maptab_card_quality_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_card_quality_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *quality_idx = node->first_node("quality_id");
        xml_node<> *hero_advance_levelx = node->first_node("hero_advance_level");
        xml_node<> *hero_advance_materialsx = node->first_node("hero_advance_materials");
        xml_node<> *gold_expendx = node->first_node("gold_expend");
        xml_node<> *hero_power_addx = node->first_node("hero_power_add");
        xml_node<> *agile_addx = node->first_node("agile_add");
        xml_node<> *mental_addx = node->first_node("mental_add");
        xml_node<> *hero_hp_addx = node->first_node("hero_hp_add");
        xml_node<> *physics_act_addx = node->first_node("physics_act_add");
        xml_node<> *magic_strength_addx = node->first_node("magic_strength_add");
        xml_node<> *armor_addx = node->first_node("armor_add");
        xml_node<> *magic_resist_addx = node->first_node("magic_resist_add");
        xml_node<> *physics_crit_addx = node->first_node("physics_crit_add");
        xml_node<> *magic_crit_addx = node->first_node("magic_crit_add");
        xml_node<> *hp_restore_addx = node->first_node("hp_restore_add");
        xml_node<> *energy_restore_addx = node->first_node("energy_restore_add");
        xml_node<> *armor_strike_addx = node->first_node("armor_strike_add");
        xml_node<> *ignore_magic_resist_addx = node->first_node("ignore_magic_resist_add");
        xml_node<> *cure_effect_promote_addx = node->first_node("cure_effect_promote_add");
        xml_node<> *hero_hit_addx = node->first_node("hero_hit_add");
        xml_node<> *hero_evade_addx = node->first_node("hero_evade_add");
        xml_node<> *suck_blood_level_addx = node->first_node("suck_blood_level_add");
        Configtab_card_quality_sysDataST st;

        st.ID = atoi(idx->value());
        st.quality_id = atoi(quality_idx->value());
        st.hero_advance_level = atoi(hero_advance_levelx->value());
        st.hero_advance_materials = hero_advance_materialsx->value();
        st.gold_expend = atoi(gold_expendx->value());
        st.hero_power_add = atoi(hero_power_addx->value());
        st.agile_add = atoi(agile_addx->value());
        st.mental_add = atoi(mental_addx->value());
        st.hero_hp_add = atoi(hero_hp_addx->value());
        st.physics_act_add = atoi(physics_act_addx->value());
        st.magic_strength_add = atoi(magic_strength_addx->value());
        st.armor_add = atoi(armor_addx->value());
        st.magic_resist_add = atoi(magic_resist_addx->value());
        st.physics_crit_add = atoi(physics_crit_addx->value());
        st.magic_crit_add = atoi(magic_crit_addx->value());
        st.hp_restore_add = atoi(hp_restore_addx->value());
        st.energy_restore_add = atoi(energy_restore_addx->value());
        st.armor_strike_add = atoi(armor_strike_addx->value());
        st.ignore_magic_resist_add = atoi(ignore_magic_resist_addx->value());
        st.cure_effect_promote_add = atoi(cure_effect_promote_addx->value());
        st.hero_hit_add = atoi(hero_hit_addx->value());
        st.hero_evade_add = atoi(hero_evade_addx->value());
        st.suck_blood_level_add = atoi(suck_blood_level_addx->value());

        maptab_card_quality_sysData[st.ID] = st;
    }
}
Configtab_card_quality_sysDataST LocalDataManger::getConfigtab_card_quality_sysDataST(int ID)
{
    return maptab_card_quality_sysData[ID];
}

//tab_card_star_sys
void LocalDataManger::readConfigtab_card_star_sysData()
{
    if(!maptab_card_star_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_card_star_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *hero_idx = node->first_node("hero_id");
        xml_node<> *one_star_power_growx = node->first_node("one_star_power_grow");
        xml_node<> *two_star_power_growx = node->first_node("two_star_power_grow");
        xml_node<> *three_star_power_growx = node->first_node("three_star_power_grow");
        xml_node<> *four_star_power_growx = node->first_node("four_star_power_grow");
        xml_node<> *five_star_power_growx = node->first_node("five_star_power_grow");
        xml_node<> *one_star_agile_growx = node->first_node("one_star_agile_grow");
        xml_node<> *two_star_agile_growx = node->first_node("two_star_agile_grow");
        xml_node<> *three_star_agile_growx = node->first_node("three_star_agile_grow");
        xml_node<> *four_star_agile_growx = node->first_node("four_star_agile_grow");
        xml_node<> *five_star_agile_growx = node->first_node("five_star_agile_grow");
        xml_node<> *one_star_mental_growx = node->first_node("one_star_mental_grow");
        xml_node<> *two_star_mental_growx = node->first_node("two_star_mental_grow");
        xml_node<> *three_star_mental_growx = node->first_node("three_star_mental_grow");
        xml_node<> *four_star_mental_growx = node->first_node("four_star_mental_grow");
        xml_node<> *five_star_mental_growx = node->first_node("five_star_mental_grow");
        Configtab_card_star_sysDataST st;

        st.ID = atoi(idx->value());
        st.hero_id = atoi(hero_idx->value());
        st.one_star_power_grow = atof(one_star_power_growx->value());
        st.two_star_power_grow = atof(two_star_power_growx->value());
        st.three_star_power_grow = atof(three_star_power_growx->value());
        st.four_star_power_grow = atof(four_star_power_growx->value());
        st.five_star_power_grow = atof(five_star_power_growx->value());
        st.one_star_agile_grow = atof(one_star_agile_growx->value());
        st.two_star_agile_grow = atof(two_star_agile_growx->value());
        st.three_star_agile_grow = atof(three_star_agile_growx->value());
        st.four_star_agile_grow = atof(four_star_agile_growx->value());
        st.five_star_agile_grow = atof(five_star_agile_growx->value());
        st.one_star_mental_grow = atof(one_star_mental_growx->value());
        st.two_star_mental_grow = atof(two_star_mental_growx->value());
        st.three_star_mental_grow = atof(three_star_mental_growx->value());
        st.four_star_mental_grow = atof(four_star_mental_growx->value());
        st.five_star_mental_grow = atof(five_star_mental_growx->value());

        maptab_card_star_sysData[st.ID] = st;
    }
}
Configtab_card_star_sysDataST LocalDataManger::getConfigtab_card_star_sysDataST(int ID)
{
    return maptab_card_star_sysData[ID];
}

//tab_charge_database
void LocalDataManger::readConfigtab_charge_databaseData()
{
    if(!maptab_charge_databaseData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_charge_database.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *charge_iconx = node->first_node("charge_icon");
        xml_node<> *charge_typex = node->first_node("charge_type");
        xml_node<> *charge_namex = node->first_node("charge_name");
        xml_node<> *charge_descriptionx = node->first_node("charge_description");
        xml_node<> *charge_numx = node->first_node("charge_num");
        xml_node<> *additional_numx = node->first_node("additional_num");
        xml_node<> *charge_timesx = node->first_node("charge_times");
        xml_node<> *rmb_demandx = node->first_node("rmb_demand");
        Configtab_charge_databaseDataST st;

        st.ID = atoi(idx->value());
        st.charge_icon = charge_iconx->value();
        st.charge_type = atoi(charge_typex->value());
        st.charge_name = charge_namex->value();
        st.charge_description = charge_descriptionx->value();
        st.charge_num = atoi(charge_numx->value());
        st.additional_num = atoi(additional_numx->value());
        st.charge_times = atoi(charge_timesx->value());
        st.rmb_demand = atoi(rmb_demandx->value());

        maptab_charge_databaseData[st.ID] = st;
    }
}
Configtab_charge_databaseDataST LocalDataManger::getConfigtab_charge_databaseDataST(int ID)
{
    return maptab_charge_databaseData[ID];
}

//tab_checkpoints_sys
void LocalDataManger::readConfigtab_checkpoints_sysData()
{
    if(!maptab_checkpoints_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_checkpoints_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *checkpoint_typex = node->first_node("checkpoint_type");
        xml_node<> *checkpoint_namex = node->first_node("checkpoint_name");
        xml_node<> *checkpoint_descriptionx = node->first_node("checkpoint_description");
        xml_node<> *checkpoint_resourcex = node->first_node("checkpoint_resource");
        xml_node<> *checkpoint_monstersx = node->first_node("checkpoint_monsters");
        xml_node<> *checkpoint_monsters2x = node->first_node("checkpoint_monsters2");
        xml_node<> *checkpoint_monsters3x = node->first_node("checkpoint_monsters3");
        xml_node<> *checkpoint_group_last_idx = node->first_node("checkpoint_group_last_id");
        xml_node<> *propose_checkpoint_idx = node->first_node("propose_checkpoint_id");
        xml_node<> *level_demandx = node->first_node("level_demand");
        xml_node<> *through_timesx = node->first_node("through_times");
        xml_node<> *restart_expentx = node->first_node("restart_expent");
        xml_node<> *min_peoplex = node->first_node("min_people");
        xml_node<> *max_peoplex = node->first_node("max_people");
        xml_node<> *energy_expendx = node->first_node("energy_expend");
        xml_node<> *city_exp_rewardx = node->first_node("city_exp_reward");
        xml_node<> *hero_exp_rewardx = node->first_node("hero_exp_reward");
        xml_node<> *gold_rewardx = node->first_node("gold_reward");
        xml_node<> *drop_showx = node->first_node("drop_show");
        xml_node<> *drop_itemsx = node->first_node("drop_items");
        xml_node<> *boss_drop_itemsx = node->first_node("boss_drop_items");
        xml_node<> *start_datex = node->first_node("start_date");
        xml_node<> *end_datex = node->first_node("end_date");
        xml_node<> *start_timex = node->first_node("start_time");
        xml_node<> *end_timex = node->first_node("end_time");
        xml_node<> *refresh_timex = node->first_node("refresh_time");
        xml_node<> *cd_timex = node->first_node("cd_time");
        Configtab_checkpoints_sysDataST st;

        st.ID = atoi(idx->value());
        st.checkpoint_type = atoi(checkpoint_typex->value());
        st.checkpoint_name = checkpoint_namex->value();
        st.checkpoint_description = checkpoint_descriptionx->value();
        st.checkpoint_resource = checkpoint_resourcex->value();
        st.checkpoint_monsters = checkpoint_monstersx->value();
        st.checkpoint_monsters2 = checkpoint_monsters2x->value();
        st.checkpoint_monsters3 = checkpoint_monsters3x->value();
        st.checkpoint_group_last_id = atoi(checkpoint_group_last_idx->value());
        st.propose_checkpoint_id = atoi(propose_checkpoint_idx->value());
        st.level_demand = atoi(level_demandx->value());
        st.through_times = atoi(through_timesx->value());
        st.restart_expent = atoi(restart_expentx->value());
        st.min_people = atoi(min_peoplex->value());
        st.max_people = atoi(max_peoplex->value());
        st.energy_expend = atoi(energy_expendx->value());
        st.city_exp_reward = atoi(city_exp_rewardx->value());
        st.hero_exp_reward = atoi(hero_exp_rewardx->value());
        st.gold_reward = atoi(gold_rewardx->value());
        st.drop_show = drop_showx->value();
        st.drop_items = drop_itemsx->value();
        st.boss_drop_items = boss_drop_itemsx->value();
        st.start_date = start_datex->value();
        st.end_date = end_datex->value();
        st.start_time = atoi(start_timex->value());
        st.end_time = atoi(end_timex->value());
        st.refresh_time = atoi(refresh_timex->value());
        st.cd_time = atoi(cd_timex->value());

        maptab_checkpoints_sysData[st.ID] = st;
    }
}
Configtab_checkpoints_sysDataST LocalDataManger::getConfigtab_checkpoints_sysDataST(int ID)
{
    return maptab_checkpoints_sysData[ID];
}

//tab_city_exp
void LocalDataManger::readConfigtab_city_expData()
{
    if(!maptab_city_expData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_city_exp.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *exp_upgradex = node->first_node("exp_upgrade");
        xml_node<> *power_rewardx = node->first_node("power_reward");
        xml_node<> *hero_up_gradex = node->first_node("hero_up_grade");
        Configtab_city_expDataST st;

        st.ID = atoi(idx->value());
        st.exp_upgrade = atoi(exp_upgradex->value());
        st.power_reward = atoi(power_rewardx->value());
        st.hero_up_grade = atoi(hero_up_gradex->value());

        maptab_city_expData[st.ID] = st;
    }
}
Configtab_city_expDataST LocalDataManger::getConfigtab_city_expDataST(int ID)
{
    return maptab_city_expData[ID];
}

//tab_equipbase_sys
void LocalDataManger::readConfigtab_equipbase_sysData()
{
    if(!maptab_equipbase_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_equipbase_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *equip_namex = node->first_node("equip_name");
        xml_node<> *equip_iconx = node->first_node("equip_icon");
        xml_node<> *equip_descriptionx = node->first_node("equip_description");
        xml_node<> *equip_typex = node->first_node("equip_type");
        xml_node<> *equip_subtypex = node->first_node("equip_subtype");
        xml_node<> *equip_qualityx = node->first_node("equip_quality");
        xml_node<> *equip_apparel_levelx = node->first_node("equip_apparel_level");
        xml_node<> *equip_apparel_qualityx = node->first_node("equip_apparel_quality");
        xml_node<> *equip_advance_gola_expendx = node->first_node("equip_advance_gola_expend");
        xml_node<> *equip_advance_materialx = node->first_node("equip_advance_material");
        xml_node<> *equip_decompose_gold_expendx = node->first_node("equip_decompose_gold_expend");
        xml_node<> *equip_decompose_materialsx = node->first_node("equip_decompose_materials");
        xml_node<> *equip_next_idx = node->first_node("equip_next_id");
        xml_node<> *equip_sourcex = node->first_node("equip_source");
        xml_node<> *equip_exclusivex = node->first_node("equip_exclusive");
        xml_node<> *exclusive_addx = node->first_node("exclusive_add");
        xml_node<> *equip_powerx = node->first_node("equip_power");
        xml_node<> *equip_mentalx = node->first_node("equip_mental");
        xml_node<> *equip_agilex = node->first_node("equip_agile");
        xml_node<> *equip_physic_actx = node->first_node("equip_physic_act");
        xml_node<> *equip_magic_actx = node->first_node("equip_magic_act");
        xml_node<> *equip_hpx = node->first_node("equip_hp");
        xml_node<> *equip_energyx = node->first_node("equip_energy");
        xml_node<> *equip_armorx = node->first_node("equip_armor");
        xml_node<> *equip_magic_resistx = node->first_node("equip_magic_resist");
        xml_node<> *equip_armor_strikex = node->first_node("equip_armor_strike");
        xml_node<> *equip_ignore_magicx = node->first_node("equip_ignore_magic");
        xml_node<> *equip_hp_restorex = node->first_node("equip_hp_restore");
        xml_node<> *equip_energy_restorex = node->first_node("equip_energy_restore");
        xml_node<> *equip_physics_critx = node->first_node("equip_physics_crit");
        xml_node<> *equip_magic_critx = node->first_node("equip_magic_crit");
        xml_node<> *equip_evadex = node->first_node("equip_evade");
        xml_node<> *equip_suckx = node->first_node("equip_suck");
        xml_node<> *equip_hitx = node->first_node("equip_hit");
        xml_node<> *equip_curex = node->first_node("equip_cure");
        xml_node<> *equip_energy_expendx = node->first_node("equip_energy_expend");
        xml_node<> *equip_gold_pricex = node->first_node("equip_gold_price");
        xml_node<> *equip_diamond_pricex = node->first_node("equip_diamond_price");
        xml_node<> *equip_sell_pricex = node->first_node("equip_sell_price");
        Configtab_equipbase_sysDataST st;

        st.ID = atoi(idx->value());
        st.equip_name = equip_namex->value();
        st.equip_icon = equip_iconx->value();
        st.equip_description = equip_descriptionx->value();
        st.equip_type = atoi(equip_typex->value());
        st.equip_subtype = atoi(equip_subtypex->value());
        st.equip_quality = atoi(equip_qualityx->value());
        st.equip_apparel_level = atoi(equip_apparel_levelx->value());
        st.equip_apparel_quality = atoi(equip_apparel_qualityx->value());
        st.equip_advance_gola_expend = atoi(equip_advance_gola_expendx->value());
        st.equip_advance_material = equip_advance_materialx->value();
        st.equip_decompose_gold_expend = atoi(equip_decompose_gold_expendx->value());
        st.equip_decompose_materials = equip_decompose_materialsx->value();
        st.equip_next_id = atoi(equip_next_idx->value());
        st.equip_source = equip_sourcex->value();
        st.equip_exclusive = atoi(equip_exclusivex->value());
        st.exclusive_add = atoi(exclusive_addx->value());
        st.equip_power = equip_powerx->value();
        st.equip_mental = equip_mentalx->value();
        st.equip_agile = equip_agilex->value();
        st.equip_physic_act = equip_physic_actx->value();
        st.equip_magic_act = equip_magic_actx->value();
        st.equip_hp = equip_hpx->value();
        st.equip_energy = equip_energyx->value();
        st.equip_armor = equip_armorx->value();
        st.equip_magic_resist = equip_magic_resistx->value();
        st.equip_armor_strike = equip_armor_strikex->value();
        st.equip_ignore_magic = equip_ignore_magicx->value();
        st.equip_hp_restore = equip_hp_restorex->value();
        st.equip_energy_restore = equip_energy_restorex->value();
        st.equip_physics_crit = equip_physics_critx->value();
        st.equip_magic_crit = equip_magic_critx->value();
        st.equip_evade = equip_evadex->value();
        st.equip_suck = equip_suckx->value();
        st.equip_hit = equip_hitx->value();
        st.equip_cure = equip_curex->value();
        st.equip_energy_expend = equip_energy_expendx->value();
        st.equip_gold_price = atoi(equip_gold_pricex->value());
        st.equip_diamond_price = atoi(equip_diamond_pricex->value());
        st.equip_sell_price = atoi(equip_sell_pricex->value());

        maptab_equipbase_sysData[st.ID] = st;
    }
}
Configtab_equipbase_sysDataST LocalDataManger::getConfigtab_equipbase_sysDataST(int ID)
{
    return maptab_equipbase_sysData[ID];
}

//tab_hero_group_sys
void LocalDataManger::readConfigtab_hero_group_sysData()
{
    if(!maptab_hero_group_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_hero_group_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *group_namex = node->first_node("group_name");
        xml_node<> *group_describex = node->first_node("group_describe");
        xml_node<> *group_effect_idx = node->first_node("group_effect_id");
        Configtab_hero_group_sysDataST st;

        st.ID = atoi(idx->value());
        st.group_name = group_namex->value();
        st.group_describe = group_describex->value();
        st.group_effect_id = atoi(group_effect_idx->value());

        maptab_hero_group_sysData[st.ID] = st;
    }
}
Configtab_hero_group_sysDataST LocalDataManger::getConfigtab_hero_group_sysDataST(int ID)
{
    return maptab_hero_group_sysData[ID];
}

//tab_intensify_demand_sys
void LocalDataManger::readConfigtab_intensify_demand_sysData()
{
    if(!maptab_intensify_demand_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_intensify_demand_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *intensify_levelx = node->first_node("intensify_level");
        xml_node<> *gold_expendx = node->first_node("gold_expend");
        Configtab_intensify_demand_sysDataST st;

        st.ID = atoi(idx->value());
        st.intensify_level = atoi(intensify_levelx->value());
        st.gold_expend = atoi(gold_expendx->value());

        maptab_intensify_demand_sysData[st.ID] = st;
    }
}
Configtab_intensify_demand_sysDataST LocalDataManger::getConfigtab_intensify_demand_sysDataST(int ID)
{
    return maptab_intensify_demand_sysData[ID];
}

//tab_item_base_sys
void LocalDataManger::readConfigtab_item_base_sysData()
{
    if(!maptab_item_base_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_item_base_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *item_namex = node->first_node("item_name");
        xml_node<> *item_iconx = node->first_node("item_icon");
        xml_node<> *item_descx = node->first_node("item_desc");
        xml_node<> *item_qualityx = node->first_node("item_quality");
        xml_node<> *item_typex = node->first_node("item_type");
        xml_node<> *item_sub_itemx = node->first_node("item_sub_item");
        xml_node<> *is_usex = node->first_node("is_use");
        xml_node<> *item_use_effectx = node->first_node("item_use_effect");
        xml_node<> *use_low_levelx = node->first_node("use_low_level");
        xml_node<> *use_high_levelx = node->first_node("use_high_level");
        xml_node<> *item_gold_pricex = node->first_node("item_gold_price");
        xml_node<> *item_diamond_pricex = node->first_node("item_diamond_price");
        xml_node<> *sell_gold_pricex = node->first_node("sell_gold_price");
        xml_node<> *pile_numberx = node->first_node("pile_number");
        xml_node<> *item_compoundx = node->first_node("item_compound");
        xml_node<> *rucksack_sortx = node->first_node("rucksack_sort");
        Configtab_item_base_sysDataST st;

        st.ID = atoi(idx->value());
        st.item_name = item_namex->value();
        st.item_icon = item_iconx->value();
        st.item_desc = item_descx->value();
        st.item_quality = atoi(item_qualityx->value());
        st.item_type = atoi(item_typex->value());
        st.item_sub_item = atoi(item_sub_itemx->value());
        st.is_use = atoi(is_usex->value());
        st.item_use_effect = atoi(item_use_effectx->value());
        st.use_low_level = atoi(use_low_levelx->value());
        st.use_high_level = atoi(use_high_levelx->value());
        st.item_gold_price = atoi(item_gold_pricex->value());
        st.item_diamond_price = atoi(item_diamond_pricex->value());
        st.sell_gold_price = atoi(sell_gold_pricex->value());
        st.pile_number = atoi(pile_numberx->value());
        st.item_compound = item_compoundx->value();
        st.rucksack_sort = atoi(rucksack_sortx->value());

        maptab_item_base_sysData[st.ID] = st;
    }
}
Configtab_item_base_sysDataST LocalDataManger::getConfigtab_item_base_sysDataST(int ID)
{
    return maptab_item_base_sysData[ID];
}

//tab_lottery_base
void LocalDataManger::readConfigtab_lottery_baseData()
{
    if(!maptab_lottery_baseData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_lottery_base.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *lottery_nodex = node->first_node("lottery_node");
        xml_node<> *expend_numx = node->first_node("expend_num");
        xml_node<> *lottery_free_timesx = node->first_node("lottery_free_times");
        xml_node<> *free_refresh_timex = node->first_node("free_refresh_time");
        xml_node<> *fix_rewardx = node->first_node("fix_reward");
        xml_node<> *open_conditionx = node->first_node("open_condition");
        Configtab_lottery_baseDataST st;

        st.ID = atoi(idx->value());
        st.lottery_node = atoi(lottery_nodex->value());
        st.expend_num = atoi(expend_numx->value());
        st.lottery_free_times = atoi(lottery_free_timesx->value());
        st.free_refresh_time = atoi(free_refresh_timex->value());
        st.fix_reward = fix_rewardx->value();
        st.open_condition = atoi(open_conditionx->value());

        maptab_lottery_baseData[st.ID] = st;
    }
}
Configtab_lottery_baseDataST LocalDataManger::getConfigtab_lottery_baseDataST(int ID)
{
    return maptab_lottery_baseData[ID];
}

//tab_lottery_data_sys
void LocalDataManger::readConfigtab_lottery_data_sysData()
{
    if(!maptab_lottery_data_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_lottery_data_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *lottery_typex = node->first_node("lottery_type");
        xml_node<> *lottery_item_idx = node->first_node("lottery_item_id");
        xml_node<> *item_numbersx = node->first_node("item_numbers");
        xml_node<> *is_repeatx = node->first_node("is_repeat");
        xml_node<> *first_cycle_probabilityx = node->first_node("first_cycle_probability");
        xml_node<> *second_cycle_probabilityx = node->first_node("second_cycle_probability");
        Configtab_lottery_data_sysDataST st;

        st.ID = atoi(idx->value());
        st.lottery_type = atoi(lottery_typex->value());
        st.lottery_item_id = atoi(lottery_item_idx->value());
        st.item_numbers = atoi(item_numbersx->value());
        st.is_repeat = atoi(is_repeatx->value());
        st.first_cycle_probability = atoi(first_cycle_probabilityx->value());
        st.second_cycle_probability = atoi(second_cycle_probabilityx->value());

        maptab_lottery_data_sysData[st.ID] = st;
    }
}
Configtab_lottery_data_sysDataST LocalDataManger::getConfigtab_lottery_data_sysDataST(int ID)
{
    return maptab_lottery_data_sysData[ID];
}

//tab_market_database_sys
void LocalDataManger::readConfigtab_market_database_sysData()
{
    if(!maptab_market_database_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_market_database_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *currency_typex = node->first_node("currency_type");
        xml_node<> *item_idx = node->first_node("item_id");
        xml_node<> *item_numbersx = node->first_node("item_numbers");
        xml_node<> *item_pricex = node->first_node("item_price");
        xml_node<> *refresh_percentx = node->first_node("refresh_percent");
        Configtab_market_database_sysDataST st;

        st.ID = atoi(idx->value());
        st.currency_type = atoi(currency_typex->value());
        st.item_id = atoi(item_idx->value());
        st.item_numbers = atoi(item_numbersx->value());
        st.item_price = atoi(item_pricex->value());
        st.refresh_percent = atoi(refresh_percentx->value());

        maptab_market_database_sysData[st.ID] = st;
    }
}
Configtab_market_database_sysDataST LocalDataManger::getConfigtab_market_database_sysDataST(int ID)
{
    return maptab_market_database_sysData[ID];
}

//tab_monster_addition
void LocalDataManger::readConfigtab_monster_additionData()
{
    if(!maptab_monster_additionData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_monster_addition.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *typex = node->first_node("type");
        xml_node<> *sub_typex = node->first_node("sub_type");
        xml_node<> *base_valuex = node->first_node("base_value");
        xml_node<> *stage1x = node->first_node("stage1");
        xml_node<> *stage2x = node->first_node("stage2");
        xml_node<> *stage3x = node->first_node("stage3");
        xml_node<> *stage4x = node->first_node("stage4");
        xml_node<> *stage5x = node->first_node("stage5");
        xml_node<> *stage6x = node->first_node("stage6");
        xml_node<> *stage7x = node->first_node("stage7");
        xml_node<> *stage8x = node->first_node("stage8");
        xml_node<> *stage9x = node->first_node("stage9");
        Configtab_monster_additionDataST st;

        st.ID = atoi(idx->value());
        st.type = atoi(typex->value());
        st.sub_type = atoi(sub_typex->value());
        st.base_value = atof(base_valuex->value());
        st.stage1 = atof(stage1x->value());
        st.stage2 = atof(stage2x->value());
        st.stage3 = atof(stage3x->value());
        st.stage4 = atof(stage4x->value());
        st.stage5 = atof(stage5x->value());
        st.stage6 = atof(stage6x->value());
        st.stage7 = atof(stage7x->value());
        st.stage8 = atof(stage8x->value());
        st.stage9 = atof(stage9x->value());

        maptab_monster_additionData[st.ID] = st;
    }
}
Configtab_monster_additionDataST LocalDataManger::getConfigtab_monster_additionDataST(int ID)
{
    return maptab_monster_additionData[ID];
}

//tab_pvp_item_sys
void LocalDataManger::readConfigtab_pvp_item_sysData()
{
    if(!maptab_pvp_item_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_pvp_item_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *item_idx = node->first_node("item_id");
        xml_node<> *item_numbersx = node->first_node("item_numbers");
        xml_node<> *item_pricex = node->first_node("item_price");
        xml_node<> *refresh_percentx = node->first_node("refresh_percent");
        Configtab_pvp_item_sysDataST st;

        st.ID = atoi(idx->value());
        st.item_id = atoi(item_idx->value());
        st.item_numbers = atoi(item_numbersx->value());
        st.item_price = atoi(item_pricex->value());
        st.refresh_percent = atoi(refresh_percentx->value());

        maptab_pvp_item_sysData[st.ID] = st;
    }
}
Configtab_pvp_item_sysDataST LocalDataManger::getConfigtab_pvp_item_sysDataST(int ID)
{
    return maptab_pvp_item_sysData[ID];
}

//tab_pvp_rank_sys
void LocalDataManger::readConfigtab_pvp_rank_sysData()
{
    if(!maptab_pvp_rank_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_pvp_rank_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *low_limitx = node->first_node("low_limit");
        xml_node<> *hight_limitx = node->first_node("hight_limit");
        xml_node<> *item_rewardx = node->first_node("item_reward");
        xml_node<> *gold_rewardx = node->first_node("gold_reward");
        xml_node<> *pvp_currency_rewardx = node->first_node("pvp_currency_reward");
        xml_node<> *diamond_rewardx = node->first_node("diamond_reward");
        Configtab_pvp_rank_sysDataST st;

        st.ID = atoi(idx->value());
        st.low_limit = atoi(low_limitx->value());
        st.hight_limit = atoi(hight_limitx->value());
        st.item_reward = item_rewardx->value();
        st.gold_reward = atoi(gold_rewardx->value());
        st.pvp_currency_reward = atoi(pvp_currency_rewardx->value());
        st.diamond_reward = atoi(diamond_rewardx->value());

        maptab_pvp_rank_sysData[st.ID] = st;
    }
}
Configtab_pvp_rank_sysDataST LocalDataManger::getConfigtab_pvp_rank_sysDataST(int ID)
{
    return maptab_pvp_rank_sysData[ID];
}

//tab_pvp_times
void LocalDataManger::readConfigtab_pvp_timesData()
{
    if(!maptab_pvp_timesData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_pvp_times.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *pvp_free_timesx = node->first_node("pvp_free_times");
        xml_node<> *cd_timesx = node->first_node("cd_times");
        xml_node<> *reset_times_diamondx = node->first_node("reset_times_diamond");
        Configtab_pvp_timesDataST st;

        st.ID = atoi(idx->value());
        st.pvp_free_times = atoi(pvp_free_timesx->value());
        st.cd_times = atoi(cd_timesx->value());
        st.reset_times_diamond = atoi(reset_times_diamondx->value());

        maptab_pvp_timesData[st.ID] = st;
    }
}
Configtab_pvp_timesDataST LocalDataManger::getConfigtab_pvp_timesDataST(int ID)
{
    return maptab_pvp_timesData[ID];
}

//tab_sign_data_sys
void LocalDataManger::readConfigtab_sign_data_sysData()
{
    if(!maptab_sign_data_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_sign_data_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *sign_daysx = node->first_node("sign_days");
        xml_node<> *item_rewardx = node->first_node("item_reward");
        xml_node<> *diamond_rewardx = node->first_node("diamond_reward");
        xml_node<> *gold_rewardx = node->first_node("gold_reward");
        xml_node<> *vip_additionx = node->first_node("vip_addition");
        Configtab_sign_data_sysDataST st;

        st.ID = atoi(idx->value());
        st.sign_days = atoi(sign_daysx->value());
        st.item_reward = item_rewardx->value();
        st.diamond_reward = atoi(diamond_rewardx->value());
        st.gold_reward = atoi(gold_rewardx->value());
        st.vip_addition = vip_additionx->value();

        maptab_sign_data_sysData[st.ID] = st;
    }
}
Configtab_sign_data_sysDataST LocalDataManger::getConfigtab_sign_data_sysDataST(int ID)
{
    return maptab_sign_data_sysData[ID];
}

//tab_skill_effect
void LocalDataManger::readConfigtab_skill_effectData()
{
    if(!maptab_skill_effectData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_skill_effect.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *skill_demage_typex = node->first_node("skill_demage_type");
        xml_node<> *skill_main_typex = node->first_node("skill_main_type");
        xml_node<> *skill_sub_typex = node->first_node("skill_sub_type");
        xml_node<> *skill_effect_typex = node->first_node("skill_effect_type");
        xml_node<> *skill_effect_probabilityx = node->first_node("skill_effect_probability");
        xml_node<> *skill_base_damagex = node->first_node("skill_base_damage");
        xml_node<> *skill_effect_timex = node->first_node("skill_effect_time");
        xml_node<> *skill_effect_intervalx = node->first_node("skill_effect_interval");
        xml_node<> *self_act_parameterx = node->first_node("self_act_parameter");
        xml_node<> *skill_add_parameterx = node->first_node("skill_add_parameter");
        xml_node<> *skill_upgrade_effectx = node->first_node("skill_upgrade_effect");
        xml_node<> *specil_effect_resourcex = node->first_node("specil_effect_resource");
        Configtab_skill_effectDataST st;

        st.ID = atoi(idx->value());
        st.skill_demage_type = atoi(skill_demage_typex->value());
        st.skill_main_type = atoi(skill_main_typex->value());
        st.skill_sub_type = atoi(skill_sub_typex->value());
        st.skill_effect_type = atoi(skill_effect_typex->value());
        st.skill_effect_probability = atoi(skill_effect_probabilityx->value());
        st.skill_base_damage = atoi(skill_base_damagex->value());
        st.skill_effect_time = atoi(skill_effect_timex->value());
        st.skill_effect_interval = atoi(skill_effect_intervalx->value());
        st.self_act_parameter = atof(self_act_parameterx->value());
        st.skill_add_parameter = atof(skill_add_parameterx->value());
        st.skill_upgrade_effect = atoi(skill_upgrade_effectx->value());
        st.specil_effect_resource = specil_effect_resourcex->value();

        maptab_skill_effectData[st.ID] = st;
    }
}
Configtab_skill_effectDataST LocalDataManger::getConfigtab_skill_effectDataST(int ID)
{
    return maptab_skill_effectData[ID];
}

//tab_skill_trajectory
void LocalDataManger::readConfigtab_skill_trajectoryData()
{
    if(!maptab_skill_trajectoryData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_skill_trajectory.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *track_typex = node->first_node("track_type");
        xml_node<> *track_sub_typex = node->first_node("track_sub_type");
        xml_node<> *enlarge_multiplex = node->first_node("enlarge_multiple");
        xml_node<> *bullet_texturex = node->first_node("bullet_texture");
        xml_node<> *speedx = node->first_node("speed");
        Configtab_skill_trajectoryDataST st;

        st.ID = atoi(idx->value());
        st.track_type = atoi(track_typex->value());
        st.track_sub_type = atoi(track_sub_typex->value());
        st.enlarge_multiple = atof(enlarge_multiplex->value());
        st.bullet_texture = bullet_texturex->value();
        st.speed = atoi(speedx->value());

        maptab_skill_trajectoryData[st.ID] = st;
    }
}
Configtab_skill_trajectoryDataST LocalDataManger::getConfigtab_skill_trajectoryDataST(int ID)
{
    return maptab_skill_trajectoryData[ID];
}

//tab_skill_upgrade
void LocalDataManger::readConfigtab_skill_upgradeData()
{
    if(!maptab_skill_upgradeData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_skill_upgrade.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *skill_levelx = node->first_node("skill_level");
        xml_node<> *skill_upgrade_goldx = node->first_node("skill_upgrade_gold");
        Configtab_skill_upgradeDataST st;

        st.ID = atoi(idx->value());
        st.skill_level = atoi(skill_levelx->value());
        st.skill_upgrade_gold = atoi(skill_upgrade_goldx->value());

        maptab_skill_upgradeData[st.ID] = st;
    }
}
Configtab_skill_upgradeDataST LocalDataManger::getConfigtab_skill_upgradeDataST(int ID)
{
    return maptab_skill_upgradeData[ID];
}

//tab_skill_visual_effect
void LocalDataManger::readConfigtab_skill_visual_effectData()
{
    if(!maptab_skill_visual_effectData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_skill_visual_effect.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *skill_namex = node->first_node("skill_name");
        xml_node<> *skill_iconx = node->first_node("skill_icon");
        xml_node<> *skill_levelx = node->first_node("skill_level");
        xml_node<> *skill_descx = node->first_node("skill_desc");
        xml_node<> *skill_effect_enlargex = node->first_node("skill_effect_enlarge");
        xml_node<> *skill_animation_resourcex = node->first_node("skill_animation_resource");
        xml_node<> *skill_hit_resourcex = node->first_node("skill_hit_resource");
        xml_node<> *track_idx = node->first_node("track_id");
        xml_node<> *level_demandx = node->first_node("level_demand");
        xml_node<> *star_demandx = node->first_node("star_demand");
        xml_node<> *quality_demandx = node->first_node("quality_demand");
        xml_node<> *target_typex = node->first_node("target_type");
        xml_node<> *skill_attact_distancex = node->first_node("skill_attact_distance");
        xml_node<> *skill_rangex = node->first_node("skill_range");
        xml_node<> *conjure_interruptx = node->first_node("conjure_interrupt");
        xml_node<> *skill_sound_effectx = node->first_node("skill_sound_effect");
        xml_node<> *skill_effect_idx = node->first_node("skill_effect_id");
        xml_node<> *skill_base_capacityx = node->first_node("skill_base_capacity");
        xml_node<> *skill_upgrade_capacityx = node->first_node("skill_upgrade_capacity");
        xml_node<> *skill_effect_locationx = node->first_node("skill_effect_location");
        xml_node<> *skill_effect_layerx = node->first_node("skill_effect_layer");
        Configtab_skill_visual_effectDataST st;

        st.ID = atoi(idx->value());
        st.skill_name = skill_namex->value();
        st.skill_icon = skill_iconx->value();
        st.skill_level = atoi(skill_levelx->value());
        st.skill_desc = skill_descx->value();
        st.skill_effect_enlarge = atof(skill_effect_enlargex->value());
        st.skill_animation_resource = skill_animation_resourcex->value();
        st.skill_hit_resource = skill_hit_resourcex->value();
        st.track_id = atoi(track_idx->value());
        st.level_demand = atoi(level_demandx->value());
        st.star_demand = atoi(star_demandx->value());
        st.quality_demand = atoi(quality_demandx->value());
        st.target_type = atoi(target_typex->value());
        st.skill_attact_distance = atoi(skill_attact_distancex->value());
        st.skill_range = atoi(skill_rangex->value());
        st.conjure_interrupt = conjure_interruptx->value();
        st.skill_sound_effect = skill_sound_effectx->value();
        st.skill_effect_id = skill_effect_idx->value();
        st.skill_base_capacity = atoi(skill_base_capacityx->value());
        st.skill_upgrade_capacity = atoi(skill_upgrade_capacityx->value());
        st.skill_effect_location = atoi(skill_effect_locationx->value());
        st.skill_effect_layer = atoi(skill_effect_layerx->value());

        maptab_skill_visual_effectData[st.ID] = st;
    }
}
Configtab_skill_visual_effectDataST LocalDataManger::getConfigtab_skill_visual_effectDataST(int ID)
{
    return maptab_skill_visual_effectData[ID];
}

//tab_task_sys
void LocalDataManger::readConfigtab_task_sysData()
{
    if(!maptab_task_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_task_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *task_namex = node->first_node("task_name");
        xml_node<> *task_descriptionx = node->first_node("task_description");
        xml_node<> *task_typex = node->first_node("task_type");
        xml_node<> *start_conditionx = node->first_node("start_condition");
        xml_node<> *task_prepose_idx = node->first_node("task_prepose_id");
        xml_node<> *task_postpose_idx = node->first_node("task_postpose_id");
        xml_node<> *task_complete_typex = node->first_node("task_complete_type");
        xml_node<> *task_complete_conditionx = node->first_node("task_complete_condition");
        xml_node<> *task_complete_condition_numx = node->first_node("task_complete_condition_num");
        xml_node<> *task_item_rewardx = node->first_node("task_item_reward");
        xml_node<> *task_gold_rewardx = node->first_node("task_gold_reward");
        xml_node<> *task_diamond_rewardx = node->first_node("task_diamond_reward");
        xml_node<> *task_equip_rewardx = node->first_node("task_equip_reward");
        xml_node<> *task_skipx = node->first_node("task_skip");
        Configtab_task_sysDataST st;

        st.ID = atoi(idx->value());
        st.task_name = task_namex->value();
        st.task_description = task_descriptionx->value();
        st.task_type = atoi(task_typex->value());
        st.start_condition = atoi(start_conditionx->value());
        st.task_prepose_id = atoi(task_prepose_idx->value());
        st.task_postpose_id = atoi(task_postpose_idx->value());
        st.task_complete_type = atoi(task_complete_typex->value());
        st.task_complete_condition = atoi(task_complete_conditionx->value());
        st.task_complete_condition_num = atoi(task_complete_condition_numx->value());
        st.task_item_reward = task_item_rewardx->value();
        st.task_gold_reward = atoi(task_gold_rewardx->value());
        st.task_diamond_reward = atoi(task_diamond_rewardx->value());
        st.task_equip_reward = atoi(task_equip_rewardx->value());
        st.task_skip = atoi(task_skipx->value());

        maptab_task_sysData[st.ID] = st;
    }
}
Configtab_task_sysDataST LocalDataManger::getConfigtab_task_sysDataST(int ID)
{
    return maptab_task_sysData[ID];
}

//tab_vip_sys
void LocalDataManger::readConfigtab_vip_sysData()
{
    if(!maptab_vip_sysData.empty()) {
        return;
    }
    //rapidxml
    string xmlfile = getXmlFile("xml/tab_vip_sys.xml");
    log("%s",xmlfile.c_str());
    char* text = const_cast<char*>(xmlfile.c_str());
    xml_document<>  doc;
    doc.parse<0>(text);
    
    xml_node<>* root = doc.first_node();
    for (xml_node<> *node = root->first_node("id"); node != NULL; node = node->next_sibling())
    {
        xml_node<> *idx = node->first_node("id");
        xml_node<> *vip_levelx = node->first_node("vip_level");
        xml_node<> *free_wipe_timesx = node->first_node("free_wipe_times");
        xml_node<> *onekey_wipex = node->first_node("onekey_wipe");
        xml_node<> *energy_buy_timesx = node->first_node("energy_buy_times");
        xml_node<> *golden_timesx = node->first_node("golden_times");
        xml_node<> *reset_elite_checkpoints_timesx = node->first_node("reset_elite_checkpoints_times");
        xml_node<> *reset_skill_cdx = node->first_node("reset_skill_cd");
        xml_node<> *onekey_enchantingx = node->first_node("onekey_enchanting");
        xml_node<> *reset_pvp_cdx = node->first_node("reset_pvp_cd");
        xml_node<> *skill_point_limitx = node->first_node("skill_point_limit");
        xml_node<> *treasure_seatx = node->first_node("treasure_seat");
        xml_node<> *brother_currency_additionx = node->first_node("brother_currency_addition");
        xml_node<> *society_dungeons_gold_additionx = node->first_node("society_dungeons_gold_addition");
        xml_node<> *worship_timesx = node->first_node("worship_times");
        xml_node<> *luxury_worship_timesx = node->first_node("luxury_worship_times");
        xml_node<> *marketx = node->first_node("market");
        xml_node<> *expedition_timesx = node->first_node("expedition_times");
        xml_node<> *expedition_additionx = node->first_node("expedition_addition");
        xml_node<> *black_marketx = node->first_node("black_market");
        xml_node<> *lansquenet_numbersx = node->first_node("lansquenet_numbers");
        xml_node<> *charge_demandx = node->first_node("charge_demand");
        Configtab_vip_sysDataST st;

        st.ID = atoi(idx->value());
        st.vip_level = atoi(vip_levelx->value());
        st.free_wipe_times = atoi(free_wipe_timesx->value());
        st.onekey_wipe = atoi(onekey_wipex->value());
        st.energy_buy_times = atoi(energy_buy_timesx->value());
        st.golden_times = atoi(golden_timesx->value());
        st.reset_elite_checkpoints_times = atoi(reset_elite_checkpoints_timesx->value());
        st.reset_skill_cd = atoi(reset_skill_cdx->value());
        st.onekey_enchanting = atoi(onekey_enchantingx->value());
        st.reset_pvp_cd = atoi(reset_pvp_cdx->value());
        st.skill_point_limit = atoi(skill_point_limitx->value());
        st.treasure_seat = atoi(treasure_seatx->value());
        st.brother_currency_addition = atoi(brother_currency_additionx->value());
        st.society_dungeons_gold_addition = atof(society_dungeons_gold_additionx->value());
        st.worship_times = atoi(worship_timesx->value());
        st.luxury_worship_times = atoi(luxury_worship_timesx->value());
        st.market = atoi(marketx->value());
        st.expedition_times = atoi(expedition_timesx->value());
        st.expedition_addition = atof(expedition_additionx->value());
        st.black_market = atoi(black_marketx->value());
        st.lansquenet_numbers = atoi(lansquenet_numbersx->value());
        st.charge_demand = atoi(charge_demandx->value());

        maptab_vip_sysData[st.ID] = st;
    }
}
Configtab_vip_sysDataST LocalDataManger::getConfigtab_vip_sysDataST(int ID)
{
    return maptab_vip_sysData[ID];
}
string LocalDataManger::getXmlFile(string path)
{
    string file = FileUtils::getInstance()->getStringFromFile(path);
    log("file size is %d",(int)file.size());
    return file;
}