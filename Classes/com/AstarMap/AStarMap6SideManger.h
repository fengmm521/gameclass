//
//  AStarMap6SideManger.h
//  game3
//  C++单例类模板，非线程安全单例类，并且实例化后会常注内存
//
//  Created by fengmm521 on 10/20/14.
//
//

#ifndef __game3__AStarMap6SideManger__
#define __game3__AStarMap6SideManger__

#include "cocos2d.h"
#include "GameViewConfig.h"
#define kAStarTiled6SideLen 40

#define kMapWidth kWidthWindow   //720像素
#define kMapHeight kHeightWindow //1280像素
/*
使用六边形地图的A*寻路,要确定一个当前的像素是在那个地图块中使用下边的方法进行判断。具体的思路是：
当要确定一个点是在那个图块中时，先通过点得到点所在瓦片地图坐标，再通过换算公式得到a,b,c坐标，同时也可以通过公式逆换算得到瓦片地图坐标和像素坐标。具体算法如下：
    
    a,b,c分别为:
       ^   ^   ^
     a/ \ / \ / \               c     b    a
1   b|0,0|1,0|2,0|               \    |    /
     c\ / \ / \ /                 \   |   /
       X   X   X                   \  |  /
      / \ / \ / \                   \ | /
2    |0,1|1,1|2,1|     三条直线分别为  \｜/
      \ / \ / \ /                     X
       X   X   X                     /|\
      / \ / \ / \                   / | \
3    |0,2|1,2|2,2|                 /  |  \
      \ / \ / \ /                 /   |   \
       v   v   v
    a,b,c三条直线设定为(0,0,0)三方向原点。
    a向右下为正方向，b向右为正方向,c向右上为正方向
 
   六边形地图块三方向坐标与瓦片地图的二维坐标换算方法：
地图x轴坐标与b直线的坐标相同
地图y轴坐标的确定比较复杂，我们取a直线的坐标来确定
 #          *           *           *           *
 #       *     *     *     *     *     *     *     *
 #    *    0,0    *    1,0    *    2,0    *    3,0    *
 #    *   0,0,0   *   1,2,1   *   2,4,2   *   3,6,3   *
 #    *           *           *           *           *
 #       *     *     *     *     *     *     *     *     *
 #          *    0,1    *    1,1    *    2,1    *    3,1    *
 #          *   2,1,-1  *   3,3,0   *   4,5,1   *   5,7,2   *
 #          *           *           *           *           *
 #       *     *     *     *     *     *     *     *     *
 #    *    0,2    *    1,2    *    2,2    *    3,2    *
 #    *   3,0,-3  *   4,2,-2  *   5,4,-1  *   6,6,0   *
 #    *           *           *           *           *
 #       *     *     *     *     *     *     *     *     *
 #          *    0,2    *    1,2    *    2,2    *    3,2    *
 #          *   5,1,-4  *   6,3,-3  *   7,5,-2  *   8,7,-1  *
 #          *           *           *           *           *
 #       *     *     *     *     *     *     *     *     *
 #    *    0,3    *    1,3    *    2,3    *    3,3    *
 #    *   6,0,-6  *   7,2,-5  *   8,4,-4  *   9,6,-3  *
 #    *           *           *           *           *
 #       *     *     *     *     *     *     *     *
 #          *           *           *           *
 */
//通过上图可以得出:已知瓦片地图的坐标(x,y),可以求得6边形中心点斜三轴坐标(a,b,c)
//a直线坐标与直角坐标系中的(x,y)坐标关系为：
//当y%2==0时，a=x+y+(y/2)
//当y%2==1时，a=x+y+((y-1)/2)+1
//b直线坐标与直角坐标系中的(x,y)坐标关系为:
//当y%2==0时，b=x*2
//当y%2==1时，b=x*2+1
//c直线坐标与直角坐标系中的(x,y)坐标关系为:
//当y%2==0时，c=x-(y+(y/2))
//当y%2==1时，c=x-(y+(y-1)/2)

//下边计算已知abc坐标来求(x,y)坐标
//首先通过b轴坐标来得知当前的y坐标是否是偶数行
//当b%2==0时，得到以下方程组：
//  a=x+y+(y/2)
//  b=x*2
//  c=x-(y+(y/2))
//当b%2==1时，得到以下方程组:
//  a=x+y+((y-1)/2)+1
//  b=x*2+1
//  c=c=x-(y+(y-1)/2)
//我们使用a和b两个直线来表示一个斜夹角为60度的斜坐标系如下图：
//
//      |
//    \ |
//     \|
//      |\
//      | \
//      |  \
//      V   v
//     b轴   a轴
//通过解上边的方程组，我们使用a和b为表示x,y.得到：
//当b%2==0时，得到以下方程组：
//  x=b/2
//  y=(2a-b)/3
//当b%2==1时，得到以下方程组:
//  x=(b-1)/2
//  y=(2a-b)/3
//瓦片地图的原点在坐上角，x轴正方向向右，y轴正方向向下
//a,b,c的三坐标系中的a轴为右斜下，b轴向右,c轴向右斜上
//
//下边分别是将瓦片地图坐标与原点在左下角的像素坐标互换计算，以及在斜坐标系中使用A*寻路，和斜坐标系与像素坐标换算。
//6边形A*寻路是使用周围6个方向的时间花费来作记算的。分别延a,b,c的正方向和反方向的6个方向查找最近点。当找到路径时，使用MoveTo来按路径移动精灵。而没有使用物理引擎或者刷帧。
//当得到路径坐标时，再使用坐标变换，将abc,斜坐标系与像系坐标换算。
//
//第一步，先通过瓦片地图坐标标记的图块是否可通过，得到abc斜坐标系下瓦片是否可通过情况。
//第二步，通过abc斜坐标系下的A*寻路，找到可行走路径
//第三步，由可行走路径上的abc斜坐标系，换算出像素坐标点，然后，操作精灵移动。
//已知m点的abc坐标为(a0,b0,c0)：则通过坐标换算得到瓦片地图坐标(tx,ty),再经过比较简单的换算就可得到m点的像素坐标，具体的换算方法查看代码。
//已知n点像素坐标(x0,y0)，求abc坐标系的坐标(a,b,c),且已知abc坐标系的原点坐标为(xo,yo),计算方法如下:
//同样是先将像素坐标换算成瓦片地图坐标，再使用公式计算得到abc的三轴坐标。


//六边形三线坐标
struct AStar6SidePointST
{
    int a;
    int b;
    int c;
    int *value; //地图中的瓦片点数据指针
};
typedef struct AStar6SidePointST AStar6SidePoint;
//瓦片坐标
struct AstarTiledPointST
{
    int x;
    int y;
    int *value;
};
typedef struct AstarTiledPointST AStarTiledPoint;
//像素坐标
struct AStarPixelPointST
{
    cocos2d::Point po;
    int *value;
};
typedef struct AStarPixelPointST AStarPixelPoint;

struct AStarTiledOffsetSt
{
    int ox;
    int oy;
};
typedef struct AStarTiledOffsetSt AStarTiledOffset;

//六边形abc三轴坐标节点
class AStar6SideNodeCost
{
public:
    int a;
    int b;
    int c;
    float cast;
    inline bool operator< (const AStar6SideNodeCost& t) const
    {
        return this->cast < t.cast;
    }
    inline bool operator> (const AStar6SideNodeCost& t) const
    {
        return this->cast > t.cast;
    }
};



class AStarTiledNodeCost
{
public:
    int x;
    int y;
    float cast;
    inline bool operator< (const AStarTiledNodeCost& t) const
    {
        return this->cast < t.cast;
    }
    inline bool operator> (const AStarTiledNodeCost& t) const
    {
        return this->cast > t.cast;
    }
};

#define kSqrt3          1.732051f  //根号3的取值
#define khalfTiledWidth     72     //24
#define kTiledSidelen   ((khalfTiledWidth*2)/kSqrt3)
#define kTiledMapWidth  5  //15 //这个值是使用720/(40*sqrt(3))算出来然后取整数得到的
#define kTiledMapHeight 10  //这个值是1280/((72⋅2/√3)⋅3/2)

//a直线坐标与直角坐标系中的(x,y)坐标关系为：
//当y%2==0时，a=x+y+(y/2)
//当y%2==1时，a=x+y+((y-1)/2)+1
//b直线坐标与直角坐标系中的(x,y)坐标关系为:
//当y%2==0时，b=x*2
//当y%2==1时，b=x*2+1
//c直线坐标与直角坐标系中的(x,y)坐标关系为:
//当y%2==0时，c=x-(y+(y/2))
//当y%2==1时，c=x-(y+(y-1)/2)
//这里的y值为16,x=10,所以取上边，得a=x+y+(y/2)=5+10+5=20
#define ka_LineWidth 20
//当y%2==0时，b=x*2,得b=2*5=10
#define kb_LineWidth 10
//当y%2==0时，c=x-(y+(y/2)),c应该取(0,10)和(15,0)然后作差
//c1=-15,c2=5
//c值范围为20
#define kc_LineWidth 20 //在数组中取值时，一直保持给c+15
#define kc_LineOffect 15  //为了将c轴坐标补为正值，以方便从数组中取值
#define kMaxCast -1

#define kOPointX 72   //瓦片地图原点的x像素值
#define kOPointY 83   //瓦片地图原点的y像素值


using namespace cocos2d;
class AStarMap6SideManger:public cocos2d::Ref
{
public:
    static AStarMap6SideManger* sharedAStarMap6SideManger();
    static void destroyInstance();
private:
	/**
     * @js ctor
     */
    AStarMap6SideManger(void);
    /**
     * @js NA
     * @lua NA
     */
    ~AStarMap6SideManger(void);
    
public:
    
    
    //坐标转换,
    //将瓦片坐标转换为6边形三直线坐标
    AStar6SidePoint conventTiledPointTo6SidePoint(AStarTiledPoint tPo);
    //将6边形三直线坐标转换为瓦片坐标
    AStarTiledPoint convent6SidePointPointToTiled(AStar6SidePoint sPo);
    //通过瓦片地图坐标得到瓦片坐标上的像素坐标
    AStarPixelPoint getPixelPointFromTiledPoint(AStarTiledPoint tPo);
    //通过六边形三线坐标得到六边形瓦片像素坐标
    AStarPixelPoint getPixelPointFrom6Side_abcPoint(AStar6SidePoint sPo);
    //通过像素坐标得到6边形的三线坐标
    AStar6SidePoint get6SidePointFromPixelPoint(Point po);
    //通过像素坐标得到地图瓦片坐标
    AStarTiledPoint getTiledPointFromPixelPoint(Point po);
    //初始化地图瓦片数组,地图数据由xml表配制，加载进入mapArr的瓦片地图数组，然后再将值转换到6边形数组中。
    AStarPixelPoint getPixePointFromTiledPoint(Point tPo);
    
    void initMapArrWithMapID(int mapID);
    
    //设置瓦片不可通过。
    void setMapPoint(int x,int y,int value = 10);
    void addMapPointValue(int x,int y);
    //得到某个瓦片通过花费
    int  getMapPointValue(int x,int y);
    //清除某个瓦片花费
    void cleanMapPoint(int x,int y);
    void subMapPointValue(int x,int y);
    //通过像素点设置像素点所在瓦片花费值
    void setMapPointWithPixePoint(cocos2d::Point po,int value = 10);
    //通过像素点清除瓦片花费值
    void cleanMapPointWithPixePoint(cocos2d::Point po);

    //A*寻路，已知起始像素坐标和终点像素坐标。得到一条像素坐标的可通过路径，精灵将延这个路径移动。
    //std::list<AStarPixelPoint> findRoad(cocos2d::Point pStart,cocos2d::Point pEnd);
    //通过瓦片地图坐标找到瓦片地图路径
    std::list<AStarTiledPoint> findRoadWithTiledPoint(cocos2d::Point pStart,cocos2d::Point pEnd);
    
    
    
    //将6边形abc三线坐标路径转换为像素坐标路径
    std::list<AStarPixelPoint> conventFrom6Side_abclist(std::list<AStar6SidePoint> side6list);
    /**
     * Init AStarMap6SideManger
     */
    
    int get6SidePointValue(int a,int b,int c);
    void set6SidePointValue(int a,int b,int c,int value = 10);
    
    virtual bool init();
    
    //绘制地图格子
    void showTiledBox(cocos2d::Layer *lay);
    
    AStarTiledPoint getTiledPointWithNumber(AStarTiledPoint basePo,int number);
    
    //为近战找到一个攻击站立瓦片地图坐标
    AStarTiledPoint findAttackPointFor1(Point tilEnamy,Point tilAttack);
    //为中程找到一个攻击站立瓦片地图坐标
    AStarTiledPoint findAttackPointFor2(Point tilEnamy,Point tilAttack);
    //为远程找到一个攻击站立瓦片地图坐标
    AStarTiledPoint findAttackPointFor3(Point tilEnamy,Point tilAttack);
    
    //为近战找到一个攻击站立瓦片地图坐标
    AStarTiledPoint findAttackPointForOneTiled1(Point tilEnamy,Point tilAttack);
    //为中程找到一个攻击站立瓦片地图坐标
    AStarTiledPoint findAttackPointForOneTiled2(Point tilEnamy,Point tilAttack);
    //为远程找到一个攻击站立瓦片地图坐标
    AStarTiledPoint findAttackPointForOneTiled3(Point tilEnamy,Point tilAttack);
    
    
    
    //得到近战在某个方向的站位列表,f=1,2,3,4,5,6
    std::list<AStarTiledPoint> getJinZhanListFor(AStarTiledPoint basePo,int f);
    //int getFangXiangForJinZhan(Point po,Point Attack);
    //得到中程在某个方向的站位列表,
    //f=101,102,103,104,105,106,107,108,109,110,111,112
    std::list<AStarTiledPoint> getZhongChengListFor(AStarTiledPoint basePo,int f);
    //int getFangXiangForZhongCheng(Point po,Point Attack);
    //得到远程在某个方向的站位列表
    /*f=201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218
     */
    std::list<AStarTiledPoint> getYuanChengListFor(AStarTiledPoint basePo,int f);
    //int getFangXiangForYuanCheng(Point po,Point Attack);
    
    bool getTiledPointNumber(int x,int y,int n);
    void setTiledPointNumber(int x,int y,int n);
    void cleanTiledPointNumber(int x,int y,int n);
private:
    int mapArr[kTiledMapWidth][kTiledMapHeight] = {0};//瓦片地图坐标
    int *map_abc_Arr[ka_LineWidth][kb_LineWidth][kc_LineWidth] = {nullptr}; //六边形瓦片地图
    
    int mapArrPointNumber[kTiledMapWidth][kTiledMapHeight] = {0};
    
    
    
    std::map<int,AStarTiledOffset> offsetMap0;
    std::map<int,AStarTiledOffset> offsetMap1;

    std::list<AStarTiledPoint> reFindRoadWithTiledPoint(cocos2d::Point pStart,cocos2d::Point pEnd);

    
};

#endif /* defined(__game3__AStarMap6SideManger__) */
