//
//  LocalDataConfig.h
//  game1
//  使用结构体来进行游戏属性存储会比较方便快捷
//
//  Created by 俊盟科技1 on 8/22/14.
//
//

#ifndef game1_LocalDataConfig_h
#define game1_LocalDataConfig_h
#include "cocos2d.h"
using namespace std;

//示例宏定义，不使用时可删除
#define ktestWar 1

struct tab_card_attribute_sysDataStruct
{
    int ID = 0;       //英雄ID 
    string hero_name = "";        //名字 
    string hero_icon = "";        //英雄ICON 
    string hero_half_image = "";        //英雄半身像 
    int hero_type = 0;        //英雄类型 
    string hero_description = "";        //描述 
    int hero_faceto = 0;        //面向 
    int hero_fighting_capacity = 0;        //战斗力 
    int hero_level = 0;        //等级 
    int hero_quality = 0;        //品质 
    int hero_star = 0;        //星级 
    int hero_camp = 0;        //英雄阵营 
    int hero_skill_id1 = 0;        //奥义技能 
    int hero_skill_id2 = 0;        //普通攻击 
    int hero_skill_id3 = 0;        //技能ID3 
    int hero_skill_id4 = 0;        //技能ID4 
    int hero_skill_id5 = 0;        //技能ID5 
    int hero_skill_id6 = 0;        //技能ID6 
    string hero_skillrelease_rule = "";        //技能释放规则 
    int energy_pool = 0;        //能量槽 
    float injured_conversion_factor = 0.0f;        //受伤能量转换系数 
    float attack_conversion_factor = 0.0f;        //普攻能量转换系数 
    int hero_power = 0;        //力量 
    float power_grow = 0.0f;        //力量成长 
    int agile = 0;        //敏捷 
    float agile_grow = 0.0f;        //敏捷成长 
    int mental = 0;        //智力 
    float mental_grow = 0.0f;        //智力成长 
    int hero_hp = 0;        //生命 
    int physics_act = 0;        //物理攻击 
    int magic_strength = 0;        //魔法强度 
    int armor = 0;        //护甲 
    int magic_resist = 0;        //魔抗 
    int physics_crit = 0;        //物理暴击 
    int magic_crit = 0;        //魔法暴击 
    int hp_restore = 0;        //生命恢复 
    int energy_restore = 0;        //能量恢复 
    int armor_strike = 0;        //护甲穿透 
    int ignore_magic_resist = 0;        //忽视魔抗 
    int cure_effect_promote = 0;        //治疗效果提升 
    int hero_hit = 0;        //命中 
    int hero_evade = 0;        //闪避 
    int suck_blood_level = 0;        //吸血等级 
    int move_speed = 0;        //移动速度 
    int attact_interval = 0;        //攻击间隔 
    int group_hero_id = 0;        //组合英雄 
    string hero_dialoge = "";        //英雄对白 
    string voice_resource = "";        //语音文件 
    string skill_buff_coor = "";        //Buff效果坐标 
    string skill_hit_coor = "";        //命中效果坐标 
    string skill_track_coor = "";        //技能弹道坐标 
    int star_quene = 0;        //升星序号 
    string star_shard_needs = "";        //升星碎片消耗 
};
typedef struct tab_card_attribute_sysDataStruct Configtab_card_attribute_sysDataST;

struct tab_card_quality_sysDataStruct
{
    int ID = 0;       //全局编号 
    int quality_id = 0;        //品质 
    int hero_advance_level = 0;        //进阶等级 
    string hero_advance_materials = "";        //进阶材料 
    int gold_expend = 0;        //进阶金币 
    int hero_power_add = 0;        //力量增加 
    int agile_add = 0;        //敏捷增加 
    int mental_add = 0;        //智力增加 
    int hero_hp_add = 0;        //生命增加 
    int physics_act_add = 0;        //物理攻击增加 
    int magic_strength_add = 0;        //魔法强度增加 
    int armor_add = 0;        //护甲增加 
    int magic_resist_add = 0;        //魔抗增加 
    int physics_crit_add = 0;        //物理暴击增加 
    int magic_crit_add = 0;        //魔法暴击增加 
    int hp_restore_add = 0;        //生命恢复增加 
    int energy_restore_add = 0;        //能量恢复增加 
    int armor_strike_add = 0;        //护甲穿透增加 
    int ignore_magic_resist_add = 0;        //忽视魔抗增加 
    int cure_effect_promote_add = 0;        //治疗效果提升增加 
    int hero_hit_add = 0;        //命中增加 
    int hero_evade_add = 0;        //闪避增加 
    int suck_blood_level_add = 0;        //吸血等级增加 
};
typedef struct tab_card_quality_sysDataStruct Configtab_card_quality_sysDataST;

struct tab_card_star_sysDataStruct
{
    int ID = 0;       //全局编号 
    int hero_id = 0;        //英雄ID 
    float one_star_power_grow = 0.0f;        //一星力量成长 
    float two_star_power_grow = 0.0f;        //二星力量成长 
    float three_star_power_grow = 0.0f;        //三星力量成长 
    float four_star_power_grow = 0.0f;        //四星力量成长 
    float five_star_power_grow = 0.0f;        //五星力量成长 
    float one_star_agile_grow = 0.0f;        //一星敏捷成长 
    float two_star_agile_grow = 0.0f;        //二星敏捷成长 
    float three_star_agile_grow = 0.0f;        //三星敏捷成长 
    float four_star_agile_grow = 0.0f;        //四星敏捷成长 
    float five_star_agile_grow = 0.0f;        //五星敏捷成长 
    float one_star_mental_grow = 0.0f;        //一星智力成长 
    float two_star_mental_grow = 0.0f;        //二星智力成长 
    float three_star_mental_grow = 0.0f;        //三星智力成长 
    float four_star_mental_grow = 0.0f;        //四星智力成长 
    float five_star_mental_grow = 0.0f;        //五星智力成长 
};
typedef struct tab_card_star_sysDataStruct Configtab_card_star_sysDataST;

struct tab_charge_databaseDataStruct
{
    int ID = 0;       //编号 
    string charge_icon = "";        //充值图标 
    int charge_type = 0;        //充值类型 
    string charge_name = "";        //充值名字 
    string charge_description = "";        //充值描述 
    int charge_num = 0;        //充值效果 
    int additional_num = 0;        //额外赠送 
    int charge_times = 0;        //限购次数 
    int rmb_demand = 0;        //RMB消耗 
};
typedef struct tab_charge_databaseDataStruct Configtab_charge_databaseDataST;

struct tab_checkpoints_sysDataStruct
{
    int ID = 0;       //关卡ID 
    int checkpoint_type = 0;        //关卡类型 
    string checkpoint_name = "";        //关卡名字 
    string checkpoint_description = "";        //关卡描述 
    string checkpoint_resource = "";        //关卡资源 
    string checkpoint_monsters = "";        //怪物序列1 
    string checkpoint_monsters2 = "";        //怪物序列2 
    string checkpoint_monsters3 = "";        //怪物序列3 
    int checkpoint_group_last_id = 0;        //关卡组最后关卡ID 
    int propose_checkpoint_id = 0;        //前置关卡ID 
    int level_demand = 0;        //等级要求 
    int through_times = 0;        //通关次数 
    int restart_expent = 0;        //重置消耗 
    int min_people = 0;        //最少英雄数目 
    int max_people = 0;        //最大英雄数目 
    int energy_expend = 0;        //体力消耗 
    int city_exp_reward = 0;        //主城经验奖励 
    int hero_exp_reward = 0;        //英雄经验奖励 
    int gold_reward = 0;        //金币奖励 
    string drop_show = "";        //掉落展示 
    string drop_items = "";        //小怪掉落 
    string boss_drop_items = "";        //BOSS掉落 
    string start_date = "";        //开启日期 
    string end_date = "";        //结束日期 
    int start_time = 0;        //开启时间 
    int end_time = 0;        //结束时间 
    int refresh_time = 0;        //刷新时间 
    int cd_time = 0;        //冷却时间 
};
typedef struct tab_checkpoints_sysDataStruct Configtab_checkpoints_sysDataST;

struct tab_city_expDataStruct
{
    int ID = 0;       //等级 
    int exp_upgrade = 0;        //升级所需经验 
    int power_reward = 0;        //升级奖励体力 
    int hero_up_grade = 0;        //英雄升级经验 
};
typedef struct tab_city_expDataStruct Configtab_city_expDataST;

struct tab_equipbase_sysDataStruct
{
    int ID = 0;       //装备ID 
    string equip_name = "";        //装备名字 
    string equip_icon = "";        //装备图标 
    string equip_description = "";        //装备描述 
    int equip_type = 0;        //装备类型 
    int equip_subtype = 0;        //装备子类型 
    int equip_quality = 0;        //装备品质 
    int equip_apparel_level = 0;        //装备穿戴等级 
    int equip_apparel_quality = 0;        //装备穿戴英雄品质 
    int equip_advance_gola_expend = 0;        //装备进阶金币消耗 
    string equip_advance_material = "";        //装备进阶材料 
    int equip_decompose_gold_expend = 0;        //分解所得消耗 
    string equip_decompose_materials = "";        //分解所得材料 
    int equip_next_id = 0;        //装备下阶ID 
    string equip_source = "";        //装备来源 
    int equip_exclusive = 0;        //装备专属 
    int exclusive_add = 0;        //专属加成 
    string equip_power = "";        //力量 
    string equip_mental = "";        //智力 
    string equip_agile = "";        //敏捷 
    string equip_physic_act = "";        //物理攻击 
    string equip_magic_act = "";        //法术强度 
    string equip_hp = "";        //气血 
    string equip_energy = "";        //能量 
    string equip_armor = "";        //护甲 
    string equip_magic_resist = "";        //魔抗 
    string equip_armor_strike = "";        //护甲穿透 
    string equip_ignore_magic = "";        //忽视魔抗 
    string equip_hp_restore = "";        //生命恢复 
    string equip_energy_restore = "";        //能量恢复 
    string equip_physics_crit = "";        //物理暴击 
    string equip_magic_crit = "";        //魔法暴击 
    string equip_evade = "";        //闪避 
    string equip_suck = "";        //吸血等级 
    string equip_hit = "";        //命中 
    string equip_cure = "";        //治疗效果提升 
    string equip_energy_expend = "";        //能量消耗降低 
    int equip_gold_price = 0;        //装备金币价格 
    int equip_diamond_price = 0;        //装备钻石价格 
    int equip_sell_price = 0;        //装备售卖价格 
};
typedef struct tab_equipbase_sysDataStruct Configtab_equipbase_sysDataST;

struct tab_hero_group_sysDataStruct
{
    int ID = 0;       //组合ID 
    string group_name = "";        //组合名字 
    string group_describe = "";        //组合描述 
    int group_effect_id = 0;        //组合效果 
};
typedef struct tab_hero_group_sysDataStruct Configtab_hero_group_sysDataST;

struct tab_intensify_demand_sysDataStruct
{
    int ID = 0;       //全局编号 
    int intensify_level = 0;        //强化等级 
    int gold_expend = 0;        //金币消耗 
};
typedef struct tab_intensify_demand_sysDataStruct Configtab_intensify_demand_sysDataST;

struct tab_item_base_sysDataStruct
{
    int ID = 0;       //道具ID 
    string item_name = "";        //道具名字 
    string item_icon = "";        //道具ICON 
    string item_desc = "";        //道具描述 
    int item_quality = 0;        //道具品质 
    int item_type = 0;        //道具类型 
    int item_sub_item = 0;        //道具子类型 
    bool is_use = false;        //是否可直接使用 
    int item_use_effect = 0;        //道具使用效果 
    int use_low_level = 0;        //使用最低等级 
    int use_high_level = 0;        //使用最高等级 
    int item_gold_price = 0;        //金币价格 
    int item_diamond_price = 0;        //钻石价格 
    int sell_gold_price = 0;        //售卖金币价格 
    int pile_number = 0;        //堆叠数量 
    string item_compound = "";        //道具合成 
    int rucksack_sort = 0;        //背包排序 
};
typedef struct tab_item_base_sysDataStruct Configtab_item_base_sysDataST;

struct tab_lottery_baseDataStruct
{
    int ID = 0;       //类型 
    int lottery_node = 0;        //概率节点 
    int expend_num = 0;        //货币消耗 
    int lottery_free_times = 0;        //免费次数 
    int free_refresh_time = 0;        //免费刷新CD 
    string fix_reward = "";        //固定奖励 
    int open_condition = 0;        //开启条件 
};
typedef struct tab_lottery_baseDataStruct Configtab_lottery_baseDataST;

struct tab_lottery_data_sysDataStruct
{
    int ID = 0;       //编号 
    int lottery_type = 0;        //抽奖类型 
    int lottery_item_id = 0;        //道具ID 
    int item_numbers = 0;        //道具数量 
    bool is_repeat = false;        //是否可重复 
    int first_cycle_probability = 0;        //一轮概率 
    int second_cycle_probability = 0;        //二轮概率 
};
typedef struct tab_lottery_data_sysDataStruct Configtab_lottery_data_sysDataST;

struct tab_market_database_sysDataStruct
{
    int ID = 0;       //序列ID 
    int currency_type = 0;        //货币类型 
    int item_id = 0;        //售卖物品ID 
    int item_numbers = 0;        //道具数量 
    int item_price = 0;        //售卖价格 
    int refresh_percent = 0;        //刷新概率 
};
typedef struct tab_market_database_sysDataStruct Configtab_market_database_sysDataST;

struct tab_monster_additionDataStruct
{
    int ID = 0;       //编号 
    int type = 0;        //类型 
    int sub_type = 0;        //子类型 
    float base_value = 0.0f;        //基值 
    float stage1 = 0.0f;        //白色 
    float stage2 = 0.0f;        //绿色 
    float stage3 = 0.0f;        //绿色_1 
    float stage4 = 0.0f;        //蓝色 
    float stage5 = 0.0f;        //蓝色_1 
    float stage6 = 0.0f;        //蓝色_2 
    float stage7 = 0.0f;        //紫色 
    float stage8 = 0.0f;        //紫色_1 
    float stage9 = 0.0f;        //紫色_2 
};
typedef struct tab_monster_additionDataStruct Configtab_monster_additionDataST;

struct tab_pvp_item_sysDataStruct
{
    int ID = 0;       //编号 
    int item_id = 0;        //道具ID 
    int item_numbers = 0;        //道具数量 
    int item_price = 0;        //售卖价格 
    int refresh_percent = 0;        //刷新概率 
};
typedef struct tab_pvp_item_sysDataStruct Configtab_pvp_item_sysDataST;

struct tab_pvp_rank_sysDataStruct
{
    int ID = 0;       //编号 
    int low_limit = 0;        //区间下限 
    int hight_limit = 0;        //区间上限 
    string item_reward = "";        //道具奖励 
    int gold_reward = 0;        //金币奖励 
    int pvp_currency_reward = 0;        //PVP代币奖励 
    int diamond_reward = 0;        //钻石奖励 
};
typedef struct tab_pvp_rank_sysDataStruct Configtab_pvp_rank_sysDataST;

struct tab_pvp_timesDataStruct
{
    int ID = 0;       //编号 
    int pvp_free_times = 0;        //免费次数 
    int cd_times = 0;        //cd时间 
    int reset_times_diamond = 0;        //重置钻石消耗 
};
typedef struct tab_pvp_timesDataStruct Configtab_pvp_timesDataST;

struct tab_sign_data_sysDataStruct
{
    int ID = 0;       //全局编号 
    int sign_days = 0;        //天数 
    string item_reward = "";        //道具奖励 
    int diamond_reward = 0;        //钻石奖励 
    int gold_reward = 0;        //金币奖励 
    string vip_addition = "";        //VIP加成 
};
typedef struct tab_sign_data_sysDataStruct Configtab_sign_data_sysDataST;

struct tab_skill_effectDataStruct
{
    int ID = 0;       //技能效果ID 
    int skill_demage_type = 0;        //技能伤害类型 
    int skill_main_type = 0;        //技能主类型 
    int skill_sub_type = 0;        //技能子类型 
    int skill_effect_type = 0;        //技能效果类型 
    int skill_effect_probability = 0;        //概率参数 
    int skill_base_damage = 0;        //技能基本伤害 
    int skill_effect_time = 0;        //效果时间参数 
    int skill_effect_interval = 0;        //效果时间间隔 
    float self_act_parameter = 0.0f;        //自身攻击参数 
    float skill_add_parameter = 0.0f;        //技能附加伤害参数 
    int skill_upgrade_effect = 0;        //技能升级效果 
    string specil_effect_resource = "";        //特殊效果资源 
};
typedef struct tab_skill_effectDataStruct Configtab_skill_effectDataST;

struct tab_skill_trajectoryDataStruct
{
    int ID = 0;       //弹道ID 
    int track_type = 0;        //弹道类型 
    int track_sub_type = 0;        //弹道子类型 
    float enlarge_multiple = 0.0f;        //弹道放大倍数 
    string bullet_texture = "";        //弹道贴图 
    int speed = 0;        //飞行速度 
};
typedef struct tab_skill_trajectoryDataStruct Configtab_skill_trajectoryDataST;

struct tab_skill_upgradeDataStruct
{
    int ID = 0;       //全局编号 
    int skill_level = 0;        //等级 
    int skill_upgrade_gold = 0;        //金钱 
};
typedef struct tab_skill_upgradeDataStruct Configtab_skill_upgradeDataST;

struct tab_skill_visual_effectDataStruct
{
    int ID = 0;       //技能ID 
    string skill_name = "";        //技能名称 
    string skill_icon = "";        //技能图片 
    int skill_level = 0;        //技能等级 
    string skill_desc = "";        //技能描述 
    float skill_effect_enlarge = 0.0f;        //特效放大倍数 
    string skill_animation_resource = "";        //技能动画资源 
    string skill_hit_resource = "";        //技能命中效果资源 
    int track_id = 0;        //弹道轨迹ID 
    int level_demand = 0;        //等级要求 
    int star_demand = 0;        //星级要求 
    int quality_demand = 0;        //品质要求 
    int target_type = 0;        //目标类型 
    int skill_attact_distance = 0;        //技能距离 
    int skill_range = 0;        //技能范围 
    string conjure_interrupt = "";        //施法中断 
    string skill_sound_effect = "";        //技能音效 
    string skill_effect_id = "";        //技能效果ID 
    int skill_base_capacity = 0;        //技能基本战斗力 
    int skill_upgrade_capacity = 0;        //技能升级战斗力 
    int skill_effect_location = 0;        //技能特效位置 
    int skill_effect_layer = 0;        //技能效果层 
};
typedef struct tab_skill_visual_effectDataStruct Configtab_skill_visual_effectDataST;

struct tab_task_sysDataStruct
{
    int ID = 0;       //任务id 
    string task_name = "";        //任务名称 
    string task_description = "";        //任务描述 
    int task_type = 0;        //任务类型 
    int start_condition = 0;        //开启条件 
    int task_prepose_id = 0;        //前置ID 
    int task_postpose_id = 0;        //后置ID 
    int task_complete_type = 0;        //任务完成条件类型 
    int task_complete_condition = 0;        //任务完成条件 
    int task_complete_condition_num = 0;        //任务完成条件数量 
    string task_item_reward = "";        //任务道具奖励 
    int task_gold_reward = 0;        //任务金币奖励 
    int task_diamond_reward = 0;        //任务钻石奖励 
    int task_equip_reward = 0;        //任务装备奖励 
    int task_skip = 0;        //任务跳转 
};
typedef struct tab_task_sysDataStruct Configtab_task_sysDataST;

struct tab_vip_sysDataStruct
{
    int ID = 0;       //全局编号 
    int vip_level = 0;        //会员等级 
    int free_wipe_times = 0;        //每日免费扫荡次数 
    int onekey_wipe = 0;        //一键扫荡次数 
    int energy_buy_times = 0;        //每日购买体力次数 
    int golden_times = 0;        //点金次数 
    int reset_elite_checkpoints_times = 0;        //重置精英关卡次数 
    bool reset_skill_cd = false;        //重置技能CD 
    bool onekey_enchanting = false;        //一键装备附魔 
    int reset_pvp_cd = 0;        //立即重置竞技场CD 
    int skill_point_limit = 0;        //技能点上限 
    int treasure_seat = 0;        //藏宝洞位子 
    int brother_currency_addition = 0;        //兄弟币加成 
    float society_dungeons_gold_addition = 0.0f;        //工会副本金币加成 
    int worship_times = 0;        //膜拜大神 
    bool luxury_worship_times = false;        //豪华膜拜 
    int market = 0;        //地精商人 
    int expedition_times = 0;        //远征次数 
    float expedition_addition = 0.0f;        //远征加成 
    bool black_market = false;        //黑市 
    int lansquenet_numbers = 0;        //雇佣兵 
    int charge_demand = 0;        //充值要求 
};
typedef struct tab_vip_sysDataStruct Configtab_vip_sysDataST;


#endif