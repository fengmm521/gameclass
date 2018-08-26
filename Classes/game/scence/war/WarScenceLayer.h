//
//  WarScenceLayer.h
//  game1
//
//  Created by 俊盟科技1 on 8/22/14.
//
//  主战斗场景
//

#ifndef __game1__WarScenceLayer__
#define __game1__WarScenceLayer__

#include "cocos2d.h"
#include "BaseSprite.h"
#include "ui/CocosGUI.h"
#include "WarLayerBase.h"
#include "LocalDataManger.h"
#include "SplitDataConfig.h"
#include "cocostudio/CocoStudio.h"

#define kWarMaxCount 3

using namespace cocos2d;
using namespace std;
using namespace cocos2d::ui;
class Box2dWordManger;
class SkillEffectAction;
class WarScenceLayer : public WarLayerBase
{
protected:
    Sprite* s_MapBG;                //地图背景
    
    LayerColor* s_skillMaskBG;          //英雄释放技能时的黑色背景
    int showMaskCount;
    
    
    ui::ImageView* s_box;             //宝箱图标
    int s_boxNumber;
    //BitmapLabel
    ui::TextBMFont*   s_textBoxCount;    //宝箱数量
    int s_time;
    ui::TextBMFont*   s_timeText;    //宝箱数量
public:
    int m_ID;                       //地图数字id
    string m_strID;                 //地图文本id
    
    Configtab_checkpoints_sysDataST m_mapDataST;
    
    int m_mapNumber;
    
    
    std::string m_mapBG[kWarMaxCount];      //三张地图名
    CheckPointMonstersST m_enamyDataST[5]; //怪物序列数据
    DropItemsST m_enamyDropItem[5]; //副本物品掉物序列
    vector<DropItemsST> m_enamyDropItemVector;
    void addEnamyDropItem(int c);
    std::vector<int> m_dropShowIDVector;
    int ourSpCount;
    vector<BaseSprite*> getOurHeroVector();
    vector<BaseSprite*> getOurSoliderVector();
    //我方英雄位
    vector<BaseSprite*> m_ourHeroVector;        //我方英雄
    vector<BaseSprite*> m_ourSoliderVector;        //我方士兵
    int enemyCount;
    vector<BaseSprite*> getEnemyHeroVector();
    vector<BaseSprite*> getEnemySoliderVector();
    //敌人英雄位
    vector<BaseSprite*> m_enemyHeroVector;      //敌方英雄
    vector<BaseSprite*> m_enemySoliderVector;   //敌方士兵
    

    vector<Point> m_ourStartPointVecotr;       //我方英雄启始站位
    vector<Point> m_enemyStartPointVector; //敌方启始站位
    
    //战场当前状态:分为1战斗初始化，2战斗进行中，3战斗胜利
    int m_warstate;
    ui::Layout* _layout;
    ui::Button* m_backBtn;
    //ui::Button* m_goOnBtn;
public://初始化
    //初始化
    virtual bool init();
    //实例化对象方法
    static WarScenceLayer* createWarWithMapID(int ID);
    
    void loadnetData(string netConfig);     //载入地图网络数据
    void loadLocalData();                   //载入本地配置数据
    void initSpriteHero(vector<int> &ourHeroVect,vector<int> &enamyHeroVect);
    void initSpriteSolider(vector<string> ourSoliderVect,vector<string> enamySoliderVect);
public://交互
    //按钮交互回调方法
    void  buttonHeroEvent(Ref *pSender, ui::Widget::TouchEventType   type);
    
    //战场添加战斗单位,战场添加好单位之后，要在本方法中增加精灵死亡事件监听。
    void addSpriteInWar(BaseSprite* sp,int zoder,int tag);
    //某个精灵死亡动画开始时的回调方法,返回精灵名称，和精灵对象指针,战场可将目标移除
    void spriteDieCallBack(string name,Ref* sp);
    //某个精灵死亡动画结束时的回调方法，在这里设置一个奖励物品
    void spriteDieEndCallBack(string name,Ref* sp);
    //敌人进入警戒状态时的回调
    void CallBackWarStartForEnemy(string name,Ref* sp);
    
     //显示奖励动画,参数为敌人死亡时坐标，从这里创建一个宝箱
    void enemyHeroDieShowBox(Point po,int spaceNumber);//英雄死亡
    void enemySoliderDieShowBox(Point po,int spaceNumber);//小兵死亡
    
    //有子弹的单位攻击目标事件监听回调，在这个方法中战场进行子弹的初始化，并将子弹加入战场,即，有子弹的单位不直接攻击目标，而由战场创建的子弹对目标造成攻击
    void spriteAttackCallBack(string name,Ref* sp);
    
    //分解字符串，得到怪物数据
    void setEnamyDataWithSplitString(string &str);
    //设置副本怪物掉落
    void setEnamyDropItemsDataWithSplitString(string &str);
    //设置物理掉落动画展示id
    void setDropShowItemsIDWithSplitString(string &str);
    virtual void onExit();
    virtual void onEnter();
    
    //背景音乐淡出
    float soundValue;
    void backSoundEnd(float dt);
    
    
public://游戏逻辑
    void gameWarStart();                    //战斗开始
    void gameWarEnd(bool isWin);                      //战斗结束
    void warEndGetReward();                 //战斗结束获得奖励
    
    void showWinLayer();
    void showLoseLayer();
    void showWinLayer(float dt);
    void showLoseLayer(float dt);
    //精灵进入战斗状态完成时的注册回调
    void someSpriteWarStartMoveEnd(std::string name,cocos2d::Ref* sp);

private:

    void warUpdataZoder(float dt);//刷新地图中角色的z坐标
    
    
    void warEndUpdataZoder(float dt);//刷新地图中角色的z坐标
    
    
    //监听精灵死亡事件,当有精灵死亡时，会得到通知
    void warSpriteDieCallBack(std::string name,cocos2d::Ref* sp);
    
    //战场创建子弹，并开始移动，到达目标后对目标造成伤害,
    void bulletCreatAndAttack(BaseSprite* fromSp,BaseSprite* toSp);
    
private://网络交互
    
    void netWarEnd(bool isWin);             //向服务器发送战斗结束信息
    void netCallBackWarEnd(string json);    //服务器返回战斗结束奖励
private:
    //图层更新
    int count;
    void reOderZ(BaseSprite* sp,int z);

    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    
    Box2dWordManger* s_box2dWord;
    virtual void update(float dt);
    void showTimeUpdate(float dt);
    
    void scenceBackToMainCity();
    
public:
    //游戏角色ＵＩ
    Layout* hero1Layout;
    ImageView* heroicon1;
    Button* heroBtn1;
    ImageView* hero1StarVector[5];
    cocostudio::Armature* hero1skill; //能量满动画
    
    
    Layout* hero2Layout;
    ImageView* heroicon2;
    Button* heroBtn2;
    ImageView* hero2StarVector[5];
    cocostudio::Armature* hero2skill;  //能量满动画
    
    Layout* hero3Layout;
    ImageView* heroicon3;
    Button* heroBtn3;
    ImageView* hero3StarVector[5];
    cocostudio::Armature* hero3skill;  //能量满动画
    
    Layout* hero4Layout;
    ImageView* heroicon4;
    Button* heroBtn4;
    ImageView* hero4StarVector[5];
    cocostudio::Armature* hero4skill;  //能量满动画
    
    Layout* hero5Layout;
    ImageView* heroicon5;
    Button* heroBtn5;
    ImageView* hero5StarVector[5];
    cocostudio::Armature* hero5skill;  //能量满动画
    
    void setAllHeroButton();
    
    //释放技能时添加黑色背景
    void showMaskLayer();
    void hideMaskLayer();
    
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    BaseSprite* m_touchSprite;
    BaseSprite* m_touchAttackSprite;
    Point m_touchMovePoint;
    
    Point m_tmpPoint;
    
    
    cocostudio::Armature* m_MoveToAction;  //移动到动画
    void setSelectMoveToFlog(Point po);//设置移动到动画
    void hideSelectMoveToFlog(BaseSprite* moveSp = nullptr);
    std::list<Sprite*> m_selectShowLine; //显示的选择移动线路
    void showSelectLine(Point fromPo,Point toPo);
    void hideShowSelectLine();
    
    //技能播放动画
    SkillEffectAction* m_skillEAction;
    void showSkillRunForHero(BaseSprite* runSkillSp);
    
    //暂停所有角色，释放技能
    void whenRunSkillStopMoveAction();//当技能运行时停止移动动画
    void pauseAllSprite();
    void resumeAllSprite();
    
    std::set<void*> s_pausm;
    
    //战场中的所有子弹
    std::list<SkillBullet*> m_bullet;
    //在战场中增加一颗子弹
    void addWarBullte(SkillBullet* bullet);
    //将一颗子弹从战场移除
    void removeWarBullet(SkillBullet* bullet);
    
    bool m_isWarEnd;
    
//-----------------------
    //战斗场数
    int m_warCount;
    void initMapBG();
    void initWarEnemyData();
    void initSpriteHeroNext(vector<int> &enamyHeroVect);
    void nextWarStart();
    int m_isSetWarEnd;
//-----------------------
    
};
#endif /* defined(__game1__WarScenceLayer__) */
