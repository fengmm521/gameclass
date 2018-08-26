//
//  AStarMapManger.h
//  game3
//  C++单例类模板，非线程安全单例类，并且实例化后会常注内存
//  地图 A*寻路算法管理。
//  当每一次进入一个地图时，要求将tmx的地图转入当前管理类，由当前管理类对地图数据解析，得到地图块行走成本状态信息，
//  当每一次有角色要进行移动时，其每进入一个新地图瓦块，要先设置其下一个地图瓦块，并清除上一个地图瓦块的占位。当角色在行走的过程中，其前方被其他角色当住时，要求其再次重新计算行走路径。
//  Created by 俊盟科技1 on 10/18/14.
//下边是相关参考资料
//参考
//A*寻路算法：
//http://blog.csdn.net/lufy_legend/article/details/5733733
//二叉堆排序算法：
//http://blog.csdn.net/morewindows/article/details/6709644
//STL中的二叉堆：
//http://blog.csdn.net/morewindows/article/details/6967409
//
//

#ifndef __game3__AStarMapManger__
#define __game3__AStarMapManger__

#include "cocos2d.h"

#define kAstarWidght 18
#define kAstarHeight 32
#define kTiledWidght 40
#define kMapWidght 720
#define kMapHeight 1280
struct AStarPointST
{
    int x;
    int y;
    int *value; //地图中的瓦片点数据指针
};
typedef struct AStarPointST AStarPoint;
class AStarNodeCost
{
public:
    int x;
    int y;
    float cast;
    inline bool operator< (const AStarNodeCost& a) const
    {
        return this->cast < a.cast;
    }
    inline bool operator> (const AStarNodeCost& a) const
    {
        return this->cast > a.cast;
    }
};

//typedef struct AstarNodeST AStarNodeCost;


class AStarMapManger:public cocos2d::Ref
{
public:
    static AStarMapManger* sharedAStarMapManger();
    static void destroyInstance();
private:
	/**
     * @js ctor
     */
    AStarMapManger(void);
    /**
     * @js NA
     * @lua NA
     */
    ~AStarMapManger(void);
    
public:
    
    virtual bool init();
    /**
     * Init AStarMapManger
     初步设定地图中的每一个瓦块大小为40x40。当前游戏屏为1280x720,所以整个屏的地图为32x18的图块组成。
    （0,0）    18
     ｜－－－－－－－－｜
     ｜             ｜
     ｜             ｜
     ｜             ｜
     ｜             ｜
     ｜             ｜
     ｜             ｜ 32
     ｜             ｜
     ｜             ｜   _
     ｜             ｜  |_|40
     ｜             ｜   40
     ｜             ｜
     ｜－－－－－－－－｜
                    (mx,my)
     */
    //         x   y
    int m_mapArr[kAstarWidght][kAstarHeight];
    //设置地图不可行走值为10,可行走值为0.将来可能会使用沼泽，或者沙里等非正常行走难度的图块。
    bool initTmxMapForAStarArr(cocos2d::TMXLayer *tiledLayer,cocos2d::TMXMapInfo* mapinfo);
    void setMapPoint(int x,int y,int value = 10);
    int  getMapPointValue(int x,int y);
    void cleanMapPoint(int x,int y);
    AStarPoint getAStarPointWithPixelPoint(cocos2d::Point po);
    void setMapPointWithPixePoint(cocos2d::Point po,int value = 10);
    void cleanMapPointWithPixePoint(cocos2d::Point po);
    
    std::list<AStarPoint> findRoad(cocos2d::Point pStart,cocos2d::Point pEnd);
    cocos2d::Point conventPointForPixe(AStarPoint& apo);
    //使用std中的二叉树堆进行A*寻路算法
    
    
};




#endif /* defined(__game3__AStarMapManger__) */
