//
//  AStarMap6SideManger.cpp
//  game3
//
//  Created by 俊盟科技1 on 10/20/14.
//
//

#include "AStarMap6SideManger.h"

//0,Pi/6,2*(pi/6),3*(pi/6),4*(pi/6),5*(pi/6),6*(pi/6)
#define mPI   3.14159

#define kjPI  (mPI/3)
#define kjp0  ((0*kjPI)+(mPI/6))
#define kjp1  ((1*kjPI)+(mPI/6))
#define kjp2  ((2*kjPI)+(mPI/6))

//中程攻击距离的角度
#define kzPI  (mPI/6)
#define kzp0  ((0*kzPI)+(mPI/12))
#define kzp1  ((1*kzPI)+(mPI/12))
#define kzp2  ((2*kzPI)+(mPI/12))
#define kzp3  ((3*kzPI)+(mPI/12))
#define kzp4  ((4*kzPI)+(mPI/12))
#define kzp5  ((5*kzPI)+(mPI/12))

//远程攻击距离的角度
#define kyPI  (mPI/9)
#define kyp0  ((0*kyPI)+(mPI/18))
#define kyp1  ((1*kyPI)+(mPI/18))
#define kyp2  ((2*kyPI)+(mPI/18))
#define kyp3  ((3*kyPI)+(mPI/18))
#define kyp4  ((4*kyPI)+(mPI/18))
#define kyp5  ((5*kyPI)+(mPI/18))
#define kyp6  ((6*kyPI)+(mPI/18))
#define kyp7  ((7*kyPI)+(mPI/18))
#define kyp8  ((8*kyPI)+(mPI/18))


using namespace cocos2d;
static AStarMap6SideManger *s_sharedAStarMap6SideManger = nullptr;


static inline Point getPointFromTiled(int a1,int b1)
{
    float x;
    float y;
    float sideLen = kTiledSidelen;
    if (b1%2 == 0) {
        x = a1*khalfTiledWidth*2 + kOPointX;
    }else{
        x = (a1*2*khalfTiledWidth + kOPointX + khalfTiledWidth);
    }
    y = int((sideLen*3/2)*b1+kOPointY);
    y = kMapHeight - y;
    return  Point(x,y);
}


static float getCast(int a1,int b1,int a2,int b2)
{
    //return sqrtf(((sqrt(3)*(a2-a1)/2)*(sqrt(3)*(a2-a1)/2)+(fabsf((a1-a2))/2+fabsf(b1-b2))*(fabsf(a1-a2)/2+fabsf(b1-b2))));
    Point sPo = getPointFromTiled(a1, b1);
    Point ePo = getPointFromTiled(a2, b2);
    sPo.subtract(ePo);
    return sPo.length();
}

static bool findInClosed(AStarTiledNodeCost findNode,std::vector<AStarTiledNodeCost> closedPointv)
{
    for (std::vector<AStarTiledNodeCost>::iterator it = closedPointv.begin(); it != closedPointv.end(); it++) {
        if (findNode.x == (*it).x && findNode.y == (*it).y) {
            return true;
        }
    }
    return false;
}

static bool cmpCast(AStarTiledNodeCost a,AStarTiledNodeCost b)
{
    return a>b;
}
static bool cmpCastBig(AStarTiledNodeCost a,AStarTiledNodeCost b)
{
    return a<b;
}


AStarMap6SideManger *AStarMap6SideManger::sharedAStarMap6SideManger()
{
    if (s_sharedAStarMap6SideManger == nullptr)
    {
        s_sharedAStarMap6SideManger = new AStarMap6SideManger();
        if (!s_sharedAStarMap6SideManger || !s_sharedAStarMap6SideManger->init())
        {
            CC_SAFE_DELETE(s_sharedAStarMap6SideManger);
        }
    }
    return s_sharedAStarMap6SideManger;
}

void AStarMap6SideManger::destroyInstance()
{
    
    CC_SAFE_RELEASE_NULL(s_sharedAStarMap6SideManger);
}

AStarMap6SideManger::AStarMap6SideManger(void)
{
  
}


AStarMap6SideManger::~AStarMap6SideManger(void)
{
   
}

//得到近战在某个方向的站位列表,f=1,2,3,4,5,6
std::list<AStarTiledPoint> AStarMap6SideManger::getJinZhanListFor(AStarTiledPoint basePo,int f)
{
    std::list<int> intlist;
    switch (f) {
        case 1:
        {
            intlist.push_back(1);
            intlist.push_back(2);
            intlist.push_back(6);
            intlist.push_back(3);
            intlist.push_back(5);
            intlist.push_back(4);
        }
            break;
        case 2:
        {
            intlist.push_back(2);
            intlist.push_back(3);
            intlist.push_back(1);
            intlist.push_back(4);
            intlist.push_back(6);
            intlist.push_back(5);
        }
            break;
        case 3:
        {
            intlist.push_back(3);
            intlist.push_back(4);
            intlist.push_back(2);
            intlist.push_back(5);
            intlist.push_back(1);
            intlist.push_back(6);
        }
            break;
        case 4:
        {
            intlist.push_back(4);
            intlist.push_back(5);
            intlist.push_back(3);
            intlist.push_back(6);
            intlist.push_back(2);
            intlist.push_back(1);
        }
            break;
        case 5:
        {
            intlist.push_back(5);
            intlist.push_back(4);
            intlist.push_back(6);
            intlist.push_back(3);
            intlist.push_back(1);
            intlist.push_back(2);
        }
            break;
        case 6:
        {
            intlist.push_back(6);
            intlist.push_back(1);
            intlist.push_back(5);
            intlist.push_back(2);
            intlist.push_back(4);
            intlist.push_back(3);
        }
            break;
        default:
            break;
    }
    
    std::list<AStarTiledPoint> outlist;
    do{
        int tf = intlist.front();
        AStarTiledPoint tmp = this->getTiledPointWithNumber(basePo,tf);
        if (tmp.x < 0 || tmp.x > kTiledMapWidth) {
            intlist.pop_front();
            continue;
        }
        intlist.pop_front();
        outlist.push_back(tmp);
        
    }while (!intlist.empty());
    return outlist;
}
//int AStarMap6SideManger::getFangXiangForJinZhan(Point po,Point Attack)
//{
    
//}
//得到中程在某个方向的站位列表,
//f=101,102,103,104,105,106,107,108,109,110,111,112
std::list<AStarTiledPoint> AStarMap6SideManger::getZhongChengListFor(AStarTiledPoint basePo,int f)
{
    std::list<int> intlist;
    switch (f) {
        case 101:
        {
            intlist.push_back(101);
            intlist.push_back(102);
            intlist.push_back(112);
            intlist.push_back(103);
            intlist.push_back(111);
            intlist.push_back(104);
            intlist.push_back(110);
            intlist.push_back(105);
            intlist.push_back(109);
            intlist.push_back(106);
            intlist.push_back(108);
            intlist.push_back(107);
            intlist.push_back(1);
            intlist.push_back(2);
            intlist.push_back(6);
            intlist.push_back(3);
            intlist.push_back(5);
            intlist.push_back(4);
        }
            break;
        case 102:
        {
            
            intlist.push_back(102);
            intlist.push_back(103);
            intlist.push_back(101);
            intlist.push_back(104);
            intlist.push_back(112);
            intlist.push_back(105);
            intlist.push_back(111);
            intlist.push_back(106);
            intlist.push_back(110);
            intlist.push_back(107);
            intlist.push_back(109);
            intlist.push_back(108);
            
            intlist.push_back(1);
            intlist.push_back(2);
            intlist.push_back(3);
            intlist.push_back(6);
            intlist.push_back(4);
            intlist.push_back(5);
        }
            break;
        case 103:
        {
            intlist.push_back(103);
            intlist.push_back(102);
            intlist.push_back(104);
            intlist.push_back(101);
            intlist.push_back(105);
            intlist.push_back(106);
            intlist.push_back(112);
            intlist.push_back(107);
            intlist.push_back(111);
            intlist.push_back(108);
            intlist.push_back(110);
            intlist.push_back(109);
            intlist.push_back(2);
            intlist.push_back(1);
            intlist.push_back(3);
            intlist.push_back(6);
            intlist.push_back(4);
            intlist.push_back(5);
        }
            break;
        case 104:
        {
            intlist.push_back(104);
            intlist.push_back(103);
            intlist.push_back(105);
            intlist.push_back(102);
            intlist.push_back(106);
            intlist.push_back(101);
            intlist.push_back(107);
            intlist.push_back(112);
            intlist.push_back(108);
            intlist.push_back(111);
            intlist.push_back(109);
            intlist.push_back(110);
            intlist.push_back(2);
            intlist.push_back(3);
            intlist.push_back(1);
            intlist.push_back(4);
            intlist.push_back(5);
            intlist.push_back(6);
        }
            break;
        case 105:
        {
            intlist.push_back(105);
            intlist.push_back(104);
            intlist.push_back(106);
            intlist.push_back(103);
            intlist.push_back(107);
            intlist.push_back(102);
            intlist.push_back(108);
            intlist.push_back(101);
            intlist.push_back(109);
            intlist.push_back(110);
            intlist.push_back(112);
            intlist.push_back(111);
            intlist.push_back(3);
            intlist.push_back(4);
            intlist.push_back(2);
            intlist.push_back(5);
            intlist.push_back(1);
            intlist.push_back(6);
        }
            break;
        case 106:
        {
            intlist.push_back(106);
            intlist.push_back(107);
            intlist.push_back(105);
            intlist.push_back(108);
            intlist.push_back(104);
            intlist.push_back(109);
            intlist.push_back(103);
            intlist.push_back(102);
            intlist.push_back(110);
            intlist.push_back(101);
            intlist.push_back(111);
            intlist.push_back(112);
            intlist.push_back(4);
            intlist.push_back(3);
            intlist.push_back(5);
            intlist.push_back(2);
            intlist.push_back(6);
            intlist.push_back(1);
        }
            break;
        case 107:
        {
            intlist.push_back(107);
            intlist.push_back(106);
            intlist.push_back(108);
            intlist.push_back(105);
            intlist.push_back(109);
            intlist.push_back(104);
            intlist.push_back(110);
            intlist.push_back(103);
            intlist.push_back(111);
            intlist.push_back(102);
            intlist.push_back(112);
            intlist.push_back(101);
            intlist.push_back(4);
            intlist.push_back(3);
            intlist.push_back(5);
            intlist.push_back(2);
            intlist.push_back(6);
            intlist.push_back(1);
        }
            break;
        case 108:
        {
            intlist.push_back(108);
            intlist.push_back(107);
            intlist.push_back(109);
            intlist.push_back(106);
            intlist.push_back(110);
            intlist.push_back(105);
            intlist.push_back(111);
            intlist.push_back(104);
            intlist.push_back(112);
            intlist.push_back(103);
            intlist.push_back(101);
            intlist.push_back(102);
            intlist.push_back(4);
            intlist.push_back(5);
            intlist.push_back(3);
            intlist.push_back(6);
            intlist.push_back(1);
            intlist.push_back(2);
        }
            break;
        case 109:
        {
            intlist.push_back(109);
            intlist.push_back(108);
            intlist.push_back(110);
            intlist.push_back(107);
            intlist.push_back(111);
            intlist.push_back(106);
            intlist.push_back(112);
            intlist.push_back(105);
            intlist.push_back(101);
            intlist.push_back(104);
            intlist.push_back(102);
            intlist.push_back(103);
            intlist.push_back(5);
            intlist.push_back(4);
            intlist.push_back(6);
            intlist.push_back(3);
            intlist.push_back(1);
            intlist.push_back(2);
        }
            break;
        case 110:
        {
            intlist.push_back(110);
            intlist.push_back(109);
            intlist.push_back(111);
            intlist.push_back(108);
            intlist.push_back(112);
            intlist.push_back(107);
            intlist.push_back(101);
            intlist.push_back(106);
            intlist.push_back(102);
            intlist.push_back(105);
            intlist.push_back(103);
            intlist.push_back(104);
            intlist.push_back(5);
            intlist.push_back(6);
            intlist.push_back(4);
            intlist.push_back(1);
            intlist.push_back(3);
            intlist.push_back(2);
        }
            break;
        case 111:
        {
            intlist.push_back(111);
            intlist.push_back(112);
            intlist.push_back(110);
            intlist.push_back(101);
            intlist.push_back(109);
            intlist.push_back(102);
            intlist.push_back(108);
            intlist.push_back(107);
            intlist.push_back(103);
            intlist.push_back(106);
            intlist.push_back(104);
            intlist.push_back(105);
            intlist.push_back(6);
            intlist.push_back(1);
            intlist.push_back(5);
            intlist.push_back(2);
            intlist.push_back(4);
            intlist.push_back(3);
        }
            break;
        case 112:
        {
            intlist.push_back(112);
            intlist.push_back(101);
            intlist.push_back(111);
            intlist.push_back(102);
            intlist.push_back(110);
            intlist.push_back(103);
            intlist.push_back(109);
            intlist.push_back(108);
            intlist.push_back(104);
            intlist.push_back(107);
            intlist.push_back(105);
            intlist.push_back(106);
            intlist.push_back(1);
            intlist.push_back(6);
            intlist.push_back(2);
            intlist.push_back(5);
            intlist.push_back(4);
            intlist.push_back(3);
        }
            break;
        default:
            break;
    }
    
    std::list<AStarTiledPoint> outlist;
    do{
        int tf = intlist.front();
        AStarTiledPoint tmp = this->getTiledPointWithNumber(basePo,tf);
        if (tmp.x < 0 || tmp.x > kTiledMapWidth) {
            intlist.pop_front();
            continue;
        }
        outlist.push_back(tmp);
        intlist.pop_front();
    }while (!intlist.empty());
    //outlist.merge(outlist);
    return outlist;
}
//int AStarMap6SideManger::getFangXiangForZhongCheng(Point po,Point Attack)
//{
    
//}
//得到远程在某个方向的站位列表
/*f=201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218
 */
std::list<AStarTiledPoint> AStarMap6SideManger::getYuanChengListFor(AStarTiledPoint basePo,int f)
{
    std::list<int> intlist;
    switch (f) {
        case 201:
        {
            
            intlist.push_back(201);
            intlist.push_back(202);
            intlist.push_back(218);
            intlist.push_back(203);
            intlist.push_back(217);
            intlist.push_back(204);
            intlist.push_back(216);
            intlist.push_back(205);
            intlist.push_back(215);
            intlist.push_back(206);
            intlist.push_back(214);
            intlist.push_back(207);
            intlist.push_back(213);
            intlist.push_back(208);
            intlist.push_back(212);
            intlist.push_back(209);
            intlist.push_back(211);
            intlist.push_back(210);
            
            intlist.push_back(101);
            intlist.push_back(102);
            intlist.push_back(112);
            intlist.push_back(103);
            intlist.push_back(111);
            intlist.push_back(104);
            intlist.push_back(110);
            intlist.push_back(105);
            intlist.push_back(109);
            intlist.push_back(106);
            intlist.push_back(108);
            intlist.push_back(107);
            intlist.push_back(1);
            intlist.push_back(2);
            intlist.push_back(6);
            intlist.push_back(3);
            intlist.push_back(5);
            intlist.push_back(4);

        }
            break;
        case 202:
        {
            intlist.push_back(202);
            intlist.push_back(203);
            intlist.push_back(201);
            intlist.push_back(204);
            intlist.push_back(218);
            intlist.push_back(205);
            intlist.push_back(217);
            intlist.push_back(206);
            intlist.push_back(216);
            intlist.push_back(207);
            intlist.push_back(215);
            intlist.push_back(208);
            intlist.push_back(214);
            intlist.push_back(209);
            intlist.push_back(213);
            intlist.push_back(210);
            intlist.push_back(212);
            intlist.push_back(211);
            
            intlist.push_back(102);
            intlist.push_back(103);
            intlist.push_back(101);
            intlist.push_back(104);
            intlist.push_back(112);
            intlist.push_back(105);
            intlist.push_back(111);
            intlist.push_back(106);
            intlist.push_back(110);
            intlist.push_back(107);
            intlist.push_back(109);
            intlist.push_back(108);
            
            intlist.push_back(1);
            intlist.push_back(2);
            intlist.push_back(3);
            intlist.push_back(6);
            intlist.push_back(4);
            intlist.push_back(5);

        }
            break;
        case 203:
        {
            intlist.push_back(203);
            intlist.push_back(204);
            intlist.push_back(202);
            intlist.push_back(205);
            intlist.push_back(201);
            intlist.push_back(206);
            intlist.push_back(218);
            intlist.push_back(207);
            intlist.push_back(217);
            intlist.push_back(208);
            intlist.push_back(216);
            intlist.push_back(209);
            intlist.push_back(215);
            intlist.push_back(210);
            intlist.push_back(214);
            intlist.push_back(211);
            intlist.push_back(213);
            intlist.push_back(212);
            
            intlist.push_back(102);
            intlist.push_back(103);
            intlist.push_back(101);
            intlist.push_back(104);
            intlist.push_back(112);
            intlist.push_back(105);
            intlist.push_back(111);
            intlist.push_back(106);
            intlist.push_back(110);
            intlist.push_back(107);
            intlist.push_back(109);
            intlist.push_back(108);
            
            intlist.push_back(1);
            intlist.push_back(2);
            intlist.push_back(3);
            intlist.push_back(6);
            intlist.push_back(4);
            intlist.push_back(5);

        }
            break;
        case 204:
        {
            intlist.push_back(204);
            intlist.push_back(205);
            intlist.push_back(203);
            intlist.push_back(206);
            intlist.push_back(202);
            intlist.push_back(207);
            intlist.push_back(201);
            intlist.push_back(208);
            intlist.push_back(218);
            intlist.push_back(209);
            intlist.push_back(217);
            intlist.push_back(210);
            intlist.push_back(216);
            intlist.push_back(211);
            intlist.push_back(215);
            intlist.push_back(212);
            intlist.push_back(214);
            intlist.push_back(213);
            
            intlist.push_back(103);
            intlist.push_back(102);
            intlist.push_back(104);
            intlist.push_back(101);
            intlist.push_back(105);
            intlist.push_back(106);
            intlist.push_back(112);
            intlist.push_back(107);
            intlist.push_back(111);
            intlist.push_back(108);
            intlist.push_back(110);
            intlist.push_back(109);
            intlist.push_back(2);
            intlist.push_back(1);
            intlist.push_back(3);
            intlist.push_back(6);
            intlist.push_back(4);
            intlist.push_back(5);

        }
            break;
        case 205:
        {
            
            intlist.push_back(205);
            intlist.push_back(206);
            intlist.push_back(204);
            intlist.push_back(207);
            intlist.push_back(203);
            intlist.push_back(208);
            intlist.push_back(202);
            intlist.push_back(209);
            intlist.push_back(201);
            intlist.push_back(210);
            intlist.push_back(218);
            intlist.push_back(211);
            intlist.push_back(217);
            intlist.push_back(212);
            intlist.push_back(216);
            intlist.push_back(213);
            intlist.push_back(215);
            intlist.push_back(214);
            
            intlist.push_back(104);
            intlist.push_back(103);
            intlist.push_back(105);
            intlist.push_back(102);
            intlist.push_back(106);
            intlist.push_back(101);
            intlist.push_back(107);
            intlist.push_back(112);
            intlist.push_back(108);
            intlist.push_back(111);
            intlist.push_back(109);
            intlist.push_back(110);
            intlist.push_back(2);
            intlist.push_back(3);
            intlist.push_back(1);
            intlist.push_back(4);
            intlist.push_back(5);
            intlist.push_back(6);

        }
            break;
        case 206:
        {
            intlist.push_back(206);
            intlist.push_back(207);
            intlist.push_back(205);
            intlist.push_back(208);
            intlist.push_back(204);
            intlist.push_back(209);
            intlist.push_back(203);
            intlist.push_back(210);
            intlist.push_back(202);
            intlist.push_back(211);
            intlist.push_back(201);
            intlist.push_back(212);
            intlist.push_back(218);
            intlist.push_back(213);
            intlist.push_back(217);
            intlist.push_back(214);
            intlist.push_back(216);
            intlist.push_back(215);
            
            intlist.push_back(104);
            intlist.push_back(103);
            intlist.push_back(105);
            intlist.push_back(102);
            intlist.push_back(106);
            intlist.push_back(101);
            intlist.push_back(107);
            intlist.push_back(112);
            intlist.push_back(108);
            intlist.push_back(111);
            intlist.push_back(109);
            intlist.push_back(110);
            intlist.push_back(2);
            intlist.push_back(3);
            intlist.push_back(1);
            intlist.push_back(4);
            intlist.push_back(5);
            intlist.push_back(6);

        }
            break;
        case 207:
        {
            intlist.push_back(207);
            intlist.push_back(208);
            intlist.push_back(206);
            intlist.push_back(209);
            intlist.push_back(205);
            intlist.push_back(210);
            intlist.push_back(204);
            intlist.push_back(211);
            intlist.push_back(203);
            intlist.push_back(212);
            intlist.push_back(202);
            intlist.push_back(213);
            intlist.push_back(201);
            intlist.push_back(214);
            intlist.push_back(218);
            intlist.push_back(215);
            intlist.push_back(217);
            intlist.push_back(216);
            
            intlist.push_back(105);
            intlist.push_back(104);
            intlist.push_back(106);
            intlist.push_back(103);
            intlist.push_back(107);
            intlist.push_back(102);
            intlist.push_back(108);
            intlist.push_back(101);
            intlist.push_back(109);
            intlist.push_back(110);
            intlist.push_back(112);
            intlist.push_back(111);
            intlist.push_back(3);
            intlist.push_back(4);
            intlist.push_back(2);
            intlist.push_back(5);
            intlist.push_back(1);
            intlist.push_back(6);

        }
            break;
        case 208:
        {
            intlist.push_back(208);
            intlist.push_back(209);
            intlist.push_back(207);
            intlist.push_back(210);
            intlist.push_back(206);
            intlist.push_back(211);
            intlist.push_back(205);
            intlist.push_back(212);
            intlist.push_back(204);
            intlist.push_back(213);
            intlist.push_back(203);
            intlist.push_back(214);
            intlist.push_back(202);
            intlist.push_back(215);
            intlist.push_back(201);
            intlist.push_back(216);
            intlist.push_back(218);
            intlist.push_back(217);
            
            intlist.push_back(106);
            intlist.push_back(107);
            intlist.push_back(105);
            intlist.push_back(108);
            intlist.push_back(104);
            intlist.push_back(109);
            intlist.push_back(103);
            intlist.push_back(102);
            intlist.push_back(110);
            intlist.push_back(101);
            intlist.push_back(111);
            intlist.push_back(112);
            intlist.push_back(4);
            intlist.push_back(3);
            intlist.push_back(5);
            intlist.push_back(2);
            intlist.push_back(6);
            intlist.push_back(1);

        }
            break;
        case 209:
        {
            intlist.push_back(209);
            intlist.push_back(210);
            intlist.push_back(208);
            intlist.push_back(211);
            intlist.push_back(207);
            intlist.push_back(212);
            intlist.push_back(206);
            intlist.push_back(213);
            intlist.push_back(205);
            intlist.push_back(214);
            intlist.push_back(204);
            intlist.push_back(215);
            intlist.push_back(203);
            intlist.push_back(216);
            intlist.push_back(202);
            intlist.push_back(217);
            intlist.push_back(201);
            intlist.push_back(218);
            
            intlist.push_back(106);
            intlist.push_back(107);
            intlist.push_back(105);
            intlist.push_back(108);
            intlist.push_back(104);
            intlist.push_back(109);
            intlist.push_back(103);
            intlist.push_back(102);
            intlist.push_back(110);
            intlist.push_back(101);
            intlist.push_back(111);
            intlist.push_back(112);
            intlist.push_back(4);
            intlist.push_back(3);
            intlist.push_back(5);
            intlist.push_back(2);
            intlist.push_back(6);
            intlist.push_back(1);

        }
            break;
        case 210:
        {
            
            intlist.push_back(210);
            intlist.push_back(211);
            intlist.push_back(209);
            intlist.push_back(212);
            intlist.push_back(208);
            intlist.push_back(213);
            intlist.push_back(207);
            intlist.push_back(214);
            intlist.push_back(206);
            intlist.push_back(215);
            intlist.push_back(205);
            intlist.push_back(216);
            intlist.push_back(204);
            intlist.push_back(217);
            intlist.push_back(203);
            intlist.push_back(218);
            intlist.push_back(202);
            intlist.push_back(201);
            
            intlist.push_back(107);
            intlist.push_back(106);
            intlist.push_back(108);
            intlist.push_back(105);
            intlist.push_back(109);
            intlist.push_back(104);
            intlist.push_back(110);
            intlist.push_back(103);
            intlist.push_back(111);
            intlist.push_back(102);
            intlist.push_back(112);
            intlist.push_back(101);
            intlist.push_back(4);
            intlist.push_back(3);
            intlist.push_back(5);
            intlist.push_back(2);
            intlist.push_back(6);
            intlist.push_back(1);

        }
            break;
        case 211:
        {
            intlist.push_back(211);
            intlist.push_back(212);
            intlist.push_back(210);
            intlist.push_back(213);
            intlist.push_back(209);
            intlist.push_back(214);
            intlist.push_back(208);
            intlist.push_back(215);
            intlist.push_back(207);
            intlist.push_back(216);
            intlist.push_back(206);
            intlist.push_back(217);
            intlist.push_back(205);
            intlist.push_back(218);
            intlist.push_back(204);
            intlist.push_back(201);
            intlist.push_back(203);
            intlist.push_back(202);
            
            intlist.push_back(108);
            intlist.push_back(107);
            intlist.push_back(109);
            intlist.push_back(106);
            intlist.push_back(110);
            intlist.push_back(105);
            intlist.push_back(111);
            intlist.push_back(104);
            intlist.push_back(112);
            intlist.push_back(103);
            intlist.push_back(101);
            intlist.push_back(102);
            intlist.push_back(4);
            intlist.push_back(5);
            intlist.push_back(3);
            intlist.push_back(6);
            intlist.push_back(1);
            intlist.push_back(2);

        }
            break;
        case 212:
        {
            intlist.push_back(212);
            intlist.push_back(213);
            intlist.push_back(211);
            intlist.push_back(214);
            intlist.push_back(210);
            intlist.push_back(215);
            intlist.push_back(209);
            intlist.push_back(216);
            intlist.push_back(208);
            intlist.push_back(217);
            intlist.push_back(207);
            intlist.push_back(218);
            intlist.push_back(206);
            intlist.push_back(201);
            intlist.push_back(205);
            intlist.push_back(202);
            intlist.push_back(204);
            intlist.push_back(203);

            
            intlist.push_back(108);
            intlist.push_back(107);
            intlist.push_back(109);
            intlist.push_back(106);
            intlist.push_back(110);
            intlist.push_back(105);
            intlist.push_back(111);
            intlist.push_back(104);
            intlist.push_back(112);
            intlist.push_back(103);
            intlist.push_back(101);
            intlist.push_back(102);
            intlist.push_back(4);
            intlist.push_back(5);
            intlist.push_back(3);
            intlist.push_back(6);
            intlist.push_back(1);
            intlist.push_back(2);

        }
            break;
        case 213:
        {
            intlist.push_back(213);
            intlist.push_back(214);
            intlist.push_back(212);
            intlist.push_back(215);
            intlist.push_back(211);
            intlist.push_back(216);
            intlist.push_back(210);
            intlist.push_back(217);
            intlist.push_back(209);
            intlist.push_back(218);
            intlist.push_back(208);
            intlist.push_back(201);
            intlist.push_back(207);
            intlist.push_back(202);
            intlist.push_back(206);
            intlist.push_back(203);
            intlist.push_back(205);
            intlist.push_back(204);
            
            intlist.push_back(109);
            intlist.push_back(108);
            intlist.push_back(110);
            intlist.push_back(107);
            intlist.push_back(111);
            intlist.push_back(106);
            intlist.push_back(112);
            intlist.push_back(105);
            intlist.push_back(101);
            intlist.push_back(104);
            intlist.push_back(102);
            intlist.push_back(103);
            intlist.push_back(5);
            intlist.push_back(4);
            intlist.push_back(6);
            intlist.push_back(3);
            intlist.push_back(1);
            intlist.push_back(2);

        }
            break;
        case 214:
        {
            intlist.push_back(214);
            intlist.push_back(215);
            intlist.push_back(213);
            intlist.push_back(216);
            intlist.push_back(212);
            intlist.push_back(217);
            intlist.push_back(211);
            intlist.push_back(218);
            intlist.push_back(210);
            intlist.push_back(201);
            intlist.push_back(209);
            intlist.push_back(202);
            intlist.push_back(208);
            intlist.push_back(203);
            intlist.push_back(207);
            intlist.push_back(204);
            intlist.push_back(206);
            intlist.push_back(205);
            
            intlist.push_back(110);
            intlist.push_back(109);
            intlist.push_back(111);
            intlist.push_back(108);
            intlist.push_back(112);
            intlist.push_back(107);
            intlist.push_back(101);
            intlist.push_back(106);
            intlist.push_back(102);
            intlist.push_back(105);
            intlist.push_back(103);
            intlist.push_back(104);
            intlist.push_back(5);
            intlist.push_back(6);
            intlist.push_back(4);
            intlist.push_back(1);
            intlist.push_back(3);
            intlist.push_back(2);

        }
            break;
        case 215:
        {
            intlist.push_back(215);
            intlist.push_back(216);
            intlist.push_back(214);
            intlist.push_back(217);
            intlist.push_back(213);
            intlist.push_back(218);
            intlist.push_back(212);
            intlist.push_back(201);
            intlist.push_back(211);
            intlist.push_back(202);
            intlist.push_back(210);
            intlist.push_back(203);
            intlist.push_back(209);
            intlist.push_back(204);
            intlist.push_back(208);
            intlist.push_back(205);
            intlist.push_back(207);
            intlist.push_back(206);
            
            intlist.push_back(110);
            intlist.push_back(109);
            intlist.push_back(111);
            intlist.push_back(108);
            intlist.push_back(112);
            intlist.push_back(107);
            intlist.push_back(101);
            intlist.push_back(106);
            intlist.push_back(102);
            intlist.push_back(105);
            intlist.push_back(103);
            intlist.push_back(104);
            intlist.push_back(5);
            intlist.push_back(6);
            intlist.push_back(4);
            intlist.push_back(1);
            intlist.push_back(3);
            intlist.push_back(2);

        }
            break;
        case 216:
        {
            intlist.push_back(216);
            intlist.push_back(217);
            intlist.push_back(215);
            intlist.push_back(218);
            intlist.push_back(214);
            intlist.push_back(201);
            intlist.push_back(213);
            intlist.push_back(202);
            intlist.push_back(212);
            intlist.push_back(203);
            intlist.push_back(211);
            intlist.push_back(204);
            intlist.push_back(210);
            intlist.push_back(205);
            intlist.push_back(209);
            intlist.push_back(206);
            intlist.push_back(208);
            intlist.push_back(207);
            
            intlist.push_back(111);
            intlist.push_back(112);
            intlist.push_back(110);
            intlist.push_back(101);
            intlist.push_back(109);
            intlist.push_back(102);
            intlist.push_back(108);
            intlist.push_back(107);
            intlist.push_back(103);
            intlist.push_back(106);
            intlist.push_back(104);
            intlist.push_back(105);
            intlist.push_back(6);
            intlist.push_back(1);
            intlist.push_back(5);
            intlist.push_back(2);
            intlist.push_back(4);
            intlist.push_back(3);

        }
            break;
        case 217:
        {
            intlist.push_back(217);
            intlist.push_back(218);
            intlist.push_back(216);
            intlist.push_back(201);
            intlist.push_back(215);
            intlist.push_back(202);
            intlist.push_back(214);
            intlist.push_back(203);
            intlist.push_back(213);
            intlist.push_back(204);
            intlist.push_back(212);
            intlist.push_back(205);
            intlist.push_back(211);
            intlist.push_back(206);
            intlist.push_back(210);
            intlist.push_back(207);
            intlist.push_back(209);
            intlist.push_back(208);
            
            intlist.push_back(112);
            intlist.push_back(101);
            intlist.push_back(111);
            intlist.push_back(102);
            intlist.push_back(110);
            intlist.push_back(103);
            intlist.push_back(109);
            intlist.push_back(108);
            intlist.push_back(104);
            intlist.push_back(107);
            intlist.push_back(105);
            intlist.push_back(106);
            intlist.push_back(1);
            intlist.push_back(6);
            intlist.push_back(2);
            intlist.push_back(5);
            intlist.push_back(4);
            intlist.push_back(3);

        }
            break;
        case 218:
        {
            intlist.push_back(218);
            intlist.push_back(201);
            intlist.push_back(217);
            intlist.push_back(202);
            intlist.push_back(216);
            intlist.push_back(203);
            intlist.push_back(215);
            intlist.push_back(204);
            intlist.push_back(214);
            intlist.push_back(205);
            intlist.push_back(213);
            intlist.push_back(206);
            intlist.push_back(212);
            intlist.push_back(207);
            intlist.push_back(211);
            intlist.push_back(208);
            intlist.push_back(210);
            intlist.push_back(209);
            
            intlist.push_back(112);
            intlist.push_back(101);
            intlist.push_back(111);
            intlist.push_back(102);
            intlist.push_back(110);
            intlist.push_back(103);
            intlist.push_back(109);
            intlist.push_back(108);
            intlist.push_back(104);
            intlist.push_back(107);
            intlist.push_back(105);
            intlist.push_back(106);
            intlist.push_back(1);
            intlist.push_back(6);
            intlist.push_back(2);
            intlist.push_back(5);
            intlist.push_back(4);
            intlist.push_back(3);

        }
            break;
        default:
            break;
    }
    
    std::list<AStarTiledPoint> outlist;
    do{
        int tf = intlist.front();
        AStarTiledPoint tmp = this->getTiledPointWithNumber(basePo,tf);
        if (tmp.x < 0 || tmp.x > kTiledMapWidth) {
            intlist.pop_front();
            continue;
        }
        outlist.push_back(tmp);
        intlist.pop_front();
    }while (!intlist.empty());
    //outlist.merge(outlist);
    return outlist;
}
//int AStarMap6SideManger::getFangXiangForYuanCheng(Point po,Point Attack)
//{
    
//}
bool AStarMap6SideManger::init()
{
    bool bRet = false;
    do
    {
        for (int a = 0; a < ka_LineWidth; a++) {
            for (int b = 0; b < kb_LineWidth; b++) {
                for (int c = 0; c < kc_LineWidth; c++) {
                    map_abc_Arr[a][b][c] = nullptr;
                }
            }
        }
        
        for (int x = 0; x < kTiledMapWidth; x++) {
            for (int y = 0; y < kTiledMapHeight; y++) {
                AStarTiledPoint tmp;
                tmp.x = x;
                tmp.y = y;
                tmp.value = &(mapArr[x][y]);
                AStar6SidePoint tmp6 = conventTiledPointTo6SidePoint(tmp);
                map_abc_Arr[tmp6.a][tmp6.b][tmp6.c+kc_LineOffect] = tmp6.value;
            }
        }
        
        //当y%2==0时的数组
        
        AStarTiledOffset tmpoff;
        tmpoff.ox = 1;
        tmpoff.oy = 0;
        offsetMap0[1] = tmpoff;
        tmpoff.ox = 0;
        tmpoff.oy = -1;
        offsetMap0[2] = tmpoff;
        tmpoff.ox = -1;
        tmpoff.oy = -1;
        offsetMap0[3] = tmpoff;
        tmpoff.ox = -1;
        tmpoff.oy = 0;
        offsetMap0[4] = tmpoff;
        tmpoff.ox = -1;
        tmpoff.oy = 1;
        offsetMap0[5] = tmpoff;
        tmpoff.ox = 0;
        tmpoff.oy = 1;
        offsetMap0[6] = tmpoff;
        
        tmpoff.ox = 2;
        tmpoff.oy = 0;
        offsetMap0[101] = tmpoff;
        tmpoff.ox = 1;
        tmpoff.oy = -1;
        offsetMap0[102] = tmpoff;
        tmpoff.ox = 1;
        tmpoff.oy = -2;
        offsetMap0[103] = tmpoff;
        tmpoff.ox = 0;
        tmpoff.oy = -2;
        offsetMap0[104] = tmpoff;
        tmpoff.ox = -1;
        tmpoff.oy = -2;
        offsetMap0[105] = tmpoff;
        tmpoff.ox = -2;
        tmpoff.oy = -1;
        offsetMap0[106] = tmpoff;
        tmpoff.ox = -2;
        tmpoff.oy = 0;
        offsetMap0[107] = tmpoff;
        tmpoff.ox = -2;
        tmpoff.oy = 1;
        offsetMap0[108] = tmpoff;
        tmpoff.ox = -1;
        tmpoff.oy = 2;
        offsetMap0[109] = tmpoff;
        tmpoff.ox = 0;
        tmpoff.oy = 2;
        offsetMap0[110] = tmpoff;
        tmpoff.ox = 1;
        tmpoff.oy = 2;
        offsetMap0[111] = tmpoff;
        tmpoff.ox = 1;
        tmpoff.oy = 1;
        offsetMap0[112] = tmpoff;
        
        
        tmpoff.ox = 3;
        tmpoff.oy = 0;
        offsetMap0[201] = tmpoff;
        tmpoff.ox = 2;
        tmpoff.oy = -1;
        offsetMap0[202] = tmpoff;
        tmpoff.ox = 2;
        tmpoff.oy = -2;
        offsetMap0[203] = tmpoff;
        tmpoff.ox = 1;
        tmpoff.oy = -3;
        offsetMap0[204] = tmpoff;
        tmpoff.ox = 0;
        tmpoff.oy = -3;
        offsetMap0[205] = tmpoff;
        tmpoff.ox = -1;
        tmpoff.oy = -3;
        offsetMap0[206] = tmpoff;
        tmpoff.ox = -2;
        tmpoff.oy = -3;
        offsetMap0[207] = tmpoff;
        tmpoff.ox = -2;
        tmpoff.oy = -2;
        offsetMap0[208] = tmpoff;
        tmpoff.ox = -3;
        tmpoff.oy = -1;
        offsetMap0[209] = tmpoff;
        tmpoff.ox = -3;
        tmpoff.oy = 0;
        offsetMap0[210] = tmpoff;
        tmpoff.ox = -3;
        tmpoff.oy = 1;
        offsetMap0[211] = tmpoff;
        tmpoff.ox = -2;
        tmpoff.oy = 2;
        offsetMap0[212] = tmpoff;
        tmpoff.ox = -2;
        tmpoff.oy = 3;
        offsetMap0[213] = tmpoff;
        tmpoff.ox = -1;
        tmpoff.oy = 3;
        offsetMap0[214] = tmpoff;
        tmpoff.ox = 0;
        tmpoff.oy = 3;
        offsetMap0[215] = tmpoff;
        tmpoff.ox = 1;
        tmpoff.oy = 3;
        offsetMap0[216] = tmpoff;
        tmpoff.ox = 2;
        tmpoff.oy = 2;
        offsetMap0[217] = tmpoff;
        tmpoff.ox = 2;
        tmpoff.oy = 1;
        offsetMap0[218] = tmpoff;
        
        
        //当y%2==1时的数组:
        tmpoff.ox = 1;
        tmpoff.oy = 0;
        offsetMap1[1] = tmpoff;
        tmpoff.ox = 1;
        tmpoff.oy = -1;
        offsetMap1[2] = tmpoff;
        tmpoff.ox = 0;
        tmpoff.oy = -1;
        offsetMap1[3] = tmpoff;
        tmpoff.ox = -1;
        tmpoff.oy = 0;
        offsetMap1[4] = tmpoff;
        tmpoff.ox = 0;
        tmpoff.oy = 1;
        offsetMap1[5] = tmpoff;
        tmpoff.ox = 1;
        tmpoff.oy = 1;
        offsetMap1[6] = tmpoff;
        
        tmpoff.ox = 2;
        tmpoff.oy = 0;
        offsetMap1[101] = tmpoff;
        tmpoff.ox = 2;
        tmpoff.oy = -1;
        offsetMap1[102] = tmpoff;
        tmpoff.ox = 1;
        tmpoff.oy = -2;
        offsetMap1[103] = tmpoff;
        tmpoff.ox = 0;
        tmpoff.oy = -2;
        offsetMap1[104] = tmpoff;
        tmpoff.ox = -1;
        tmpoff.oy = -2;
        offsetMap1[105] = tmpoff;
        tmpoff.ox = -1;
        tmpoff.oy = -1;
        offsetMap1[106] = tmpoff;
        tmpoff.ox = -2;
        tmpoff.oy = 0;
        offsetMap1[107] = tmpoff;
        tmpoff.ox = -1;
        tmpoff.oy = 1;
        offsetMap1[108] = tmpoff;
        tmpoff.ox = -1;
        tmpoff.oy = 2;
        offsetMap1[109] = tmpoff;
        tmpoff.ox = 0;
        tmpoff.oy = 2;
        offsetMap1[110] = tmpoff;
        tmpoff.ox = 1;
        tmpoff.oy = 2;
        offsetMap1[111] = tmpoff;
        tmpoff.ox = 2;
        tmpoff.oy = 1;
        offsetMap1[112] = tmpoff;
        
        
        tmpoff.ox = 3;
        tmpoff.oy = 0;
        offsetMap1[201] = tmpoff;
        tmpoff.ox = 3;
        tmpoff.oy = -1;
        offsetMap1[202] = tmpoff;
        tmpoff.ox = 2;
        tmpoff.oy = -2;
        offsetMap1[203] = tmpoff;
        tmpoff.ox = 2;
        tmpoff.oy = -3;
        offsetMap1[204] = tmpoff;
        tmpoff.ox = 1;
        tmpoff.oy = -3;
        offsetMap1[205] = tmpoff;
        tmpoff.ox = 0;
        tmpoff.oy = -3;
        offsetMap1[206] = tmpoff;
        tmpoff.ox = -1;
        tmpoff.oy = -3;
        offsetMap1[207] = tmpoff;
        tmpoff.ox = -2;
        tmpoff.oy = -2;
        offsetMap1[208] = tmpoff;
        tmpoff.ox = -2;
        tmpoff.oy = -1;
        offsetMap1[209] = tmpoff;
        tmpoff.ox = -3;
        tmpoff.oy = 0;
        offsetMap1[210] = tmpoff;
        tmpoff.ox = -2;
        tmpoff.oy = 1;
        offsetMap1[211] = tmpoff;
        tmpoff.ox = -2;
        tmpoff.oy = 2;
        offsetMap1[212] = tmpoff;
        tmpoff.ox = -1;
        tmpoff.oy = 3;
        offsetMap1[213] = tmpoff;
        tmpoff.ox = 0;
        tmpoff.oy = 3;
        offsetMap1[214] = tmpoff;
        tmpoff.ox = 1;
        tmpoff.oy = 3;
        offsetMap1[215] = tmpoff;
        tmpoff.ox = 2;
        tmpoff.oy = 3;
        offsetMap1[216] = tmpoff;
        tmpoff.ox = 2;
        tmpoff.oy = 2;
        offsetMap1[217] = tmpoff;
        tmpoff.ox = 3;
        tmpoff.oy = 1;
        offsetMap1[218] = tmpoff;
        bRet = true;
    }
    while (0);
    
    return bRet;
}
bool AStarMap6SideManger::getTiledPointNumber(int x,int y,int n)
{
    if (x < 0 || x > kTiledMapWidth -1 || y <0 || y > kTiledMapHeight-1) {
        return false;
    }
    //0,1,2,3,4,5,6
    //0b01111111
    switch (n) {
        case 0:
        {
            //log("out n = %d",(mapArrPointNumber[x][y]&0b001));
            return (mapArrPointNumber[x][y]&0b001) == 0;
        }
            break;
        case 1:
        {
            return (mapArrPointNumber[x][y]&0b010) == 0;
        }
            break;
        case 2:
        {
            return (mapArrPointNumber[x][y]&0b0100) == 0;
        }
            break;
        case 3:
        {
            return (mapArrPointNumber[x][y]&0b01000) == 0;
        }
            break;
        case 4:
        {
            return (mapArrPointNumber[x][y]&0b010000) == 0;
        }
            break;
        case 5:
        {
            return (mapArrPointNumber[x][y]&0b0100000) == 0;
        }
            break;
        case 6:
        {
            return (mapArrPointNumber[x][y]&0b01000000) == 0;
        }
            break;
        default:
            return false;
            break;
    }
    
}
void AStarMap6SideManger::setTiledPointNumber(int x,int y,int n)
{
    if (x < 0 || x > kTiledMapWidth -1 || y <0 || y > kTiledMapHeight-1) {
        return;
    }
    //0,1,2,3,4,5,6
    //0b01111111
    switch (n) {
        case 0:
        {
            mapArrPointNumber[x][y] = mapArrPointNumber[x][y]|0b001;
        }
            break;
        case 1:
        {
            mapArrPointNumber[x][y] = mapArrPointNumber[x][y]|0b010;
        }
            break;
        case 2:
        {
            mapArrPointNumber[x][y] = mapArrPointNumber[x][y]|0b0100;
        }
            break;
        case 3:
        {
            mapArrPointNumber[x][y] = mapArrPointNumber[x][y]|0b01000;
        }
            break;
        case 4:
        {
            mapArrPointNumber[x][y] = mapArrPointNumber[x][y]|0b010000;
        }
            break;
        case 5:
        {
            mapArrPointNumber[x][y] = mapArrPointNumber[x][y]|0b0100000;
        }
            break;
        case 6:
        {
            mapArrPointNumber[x][y] = mapArrPointNumber[x][y]|0b01000000;
        }
            break;
        default:
            
            break;
    }
}
void AStarMap6SideManger::cleanTiledPointNumber(int x,int y,int n)
{
    if (x < 0 || x > kTiledMapWidth -1 || y <0 || y > kTiledMapHeight-1) {
        return;
    }
    switch (n) {
        case 0:
        {
            mapArrPointNumber[x][y] = mapArrPointNumber[x][y]&0b01111110;
        }
            break;
        case 1:
        {
            mapArrPointNumber[x][y] = mapArrPointNumber[x][y]&0b01111101;
        }
            break;
        case 2:
        {
            mapArrPointNumber[x][y] = mapArrPointNumber[x][y]&0b01111011;
        }
            break;
        case 3:
        {
            mapArrPointNumber[x][y] = mapArrPointNumber[x][y]&0b01110111;
        }
            break;
        case 4:
        {
            mapArrPointNumber[x][y] = mapArrPointNumber[x][y]&0b01101111;
        }
            break;
        case 5:
        {
            mapArrPointNumber[x][y] = mapArrPointNumber[x][y]&0b01011111;
        }
            break;
        case 6:
        {
            mapArrPointNumber[x][y] = mapArrPointNumber[x][y]&0b00111111;
        }
            break;
        default:
            
            break;
    }
}
AStarTiledPoint AStarMap6SideManger::getTiledPointWithNumber(AStarTiledPoint basePo,int number)
{
    AStarTiledOffset tmp;
    if (basePo.y%2==0) {
        tmp = offsetMap0[number];
    }else{
        tmp = offsetMap1[number];
    }
    AStarTiledPoint tmpp;
    tmpp.x = basePo.x + tmp.ox;
    tmpp.y = basePo.y + tmp.oy;
    tmpp.value = &(mapArr[tmpp.x][tmpp.y]);
    return tmpp;
}

//为近战找到一个攻击站立瓦片地图坐标
AStarTiledPoint AStarMap6SideManger::findAttackPointFor1(Point tilEnamy,Point tilAttack)
{

    Point po = tilEnamy;
    AStarTiledPoint tiPo = this->getTiledPointFromPixelPoint(po);
    //判断自已在目标的那一个位置
    Point ang = tilAttack;
    ang.subtract(po);
    float jiaodu = ang.getAngle();
    
    int fangxiang = 0;
    if (( jiaodu >= 0 && jiaodu < kjp0 )||(jiaodu < 0 && jiaodu >= -kjp0))//说明敌人在右边方向
    {
        fangxiang = 1;
    }else if(jiaodu >= kjp0 && jiaodu < kjp1)//敌人在右上角
    {
        fangxiang = 2;
    }else if(jiaodu >= kjp1 && jiaodu < kjp2)//敌人在左上角
    {
        fangxiang = 3;
    }else if((jiaodu >= kjp2 && jiaodu <= 3.141593) || (jiaodu >-3.141596 && jiaodu < -kjp2)) //敌人在左边
    {
        fangxiang = 4;
    }else if(jiaodu >= -kjp2 && jiaodu < -kjp1)//敌人在左下角
    {
        fangxiang = 5;
    }else if(jiaodu >= -kjp1 && jiaodu < -kjp0)//敌人在右下角
    {
        fangxiang = 6;
    }else{
        fangxiang = 1;
    }

    std::list<AStarTiledPoint> tmplist = this->getJinZhanListFor(tiPo, fangxiang);
    AStarTiledPoint getPoint;
    bool isZo = false;
    for (std::list<AStarTiledPoint>::iterator it = tmplist.begin(); it != tmplist.end(); it++) {
        if (*((*it).value) == 0) {
            getPoint = (*it);
            isZo = true;
            break;
        }
    }
    if (!isZo) {//说明没有找到攻击位，则精灵会站在当前攻击位上，并且设置坐标大于1000
        getPoint = tmplist.front();
        getPoint.x += 1000;//加1000用以区分当前未找到攻击位
    }
    tmplist.clear();
    return getPoint;
}
//为中程找到一个攻击站立瓦片地图坐标
AStarTiledPoint AStarMap6SideManger::findAttackPointFor2(Point tilEnamy,Point tilAttack)
{
    
    Point po = tilEnamy;
    AStarTiledPoint tiPo = this->getTiledPointFromPixelPoint(po);
    //判断自已在目标的那一个位置
    Point ang = tilAttack;
    ang.subtract(po);
    float jiaodu = ang.getAngle();
    
    int fangxiang = 0;
    if (( jiaodu >= 0 && jiaodu < kzp0 )||(jiaodu < 0 && jiaodu >= -kzp0))//说明敌人在右边方向
    {
        fangxiang = 101;
    }else if(jiaodu >= kzp0 && jiaodu < kzp1)//敌人在右上角
    {
        fangxiang = 102;
    }else if(jiaodu >= kzp1 && jiaodu < kzp2)//敌人在左上角
    {
        fangxiang = 103;
    }else if(jiaodu >= kzp2 && jiaodu < kzp3)//敌人在左上角
    {
        fangxiang = 104;
    }else if(jiaodu >= kzp3 && jiaodu < kzp4)//敌人在左上角
    {
        fangxiang = 105;
    }else if(jiaodu >= kzp4 && jiaodu < kzp5)//敌人在左上角
    {
        fangxiang = 106;
    }else if((jiaodu >= kzp5 && jiaodu <= 3.141593) || (jiaodu >-3.141596 && jiaodu < -kzp5)) //敌人在左边
    {
        fangxiang = 107;
    }else if(jiaodu >= -kzp5 && jiaodu < -kzp4)//敌人在左下角
    {
        fangxiang = 108;
    }else if(jiaodu >= -kzp4 && jiaodu < -kzp3)//敌人在左下角
    {
        fangxiang = 109;
    }else if(jiaodu >= -kzp3 && jiaodu < -kzp2)//敌人在左下角
    {
        fangxiang = 110;
    }else if(jiaodu >= -kzp2 && jiaodu < -kzp1)//敌人在左下角
    {
        fangxiang = 111;
    }else if(jiaodu >= -kjp1 && jiaodu < -kjp0)//敌人在右下角
    {
        fangxiang = 112;
    }else{
        fangxiang = 101;
    }
    
    std::list<AStarTiledPoint> tmplist = this->getZhongChengListFor(tiPo, fangxiang);
    AStarTiledPoint getPoint;
    bool isZo = false;
    for (std::list<AStarTiledPoint>::iterator it = tmplist.begin(); it != tmplist.end(); it++) {
        if (*((*it).value) == 0) {
            getPoint = (*it);
            isZo = true;
            break;
        }
    }
    if (!isZo) {//说明没有找到攻击位，则精灵会站在当前攻击位上，并且设置坐标大于1000
        getPoint = tmplist.front();
        getPoint.x += 1000;//加1000用以区分当前未找到攻击位
    }
    tmplist.clear();
    return getPoint;

}
//为远程找到一个攻击站立瓦片地图坐标
AStarTiledPoint AStarMap6SideManger::findAttackPointFor3(Point tilEnamy,Point tilAttack)
{

    Point po = tilEnamy;
    AStarTiledPoint tiPo = this->getTiledPointFromPixelPoint(po);
    //判断自已在目标的那一个位置
    Point ang = tilAttack;
    ang.subtract(po);
    float jiaodu = ang.getAngle();
    
    int fangxiang = 0;
    if (( jiaodu >= 0 && jiaodu < kzp0 )||(jiaodu < 0 && jiaodu >= -kzp0))//说明敌人在右边方向
    {
        fangxiang = 201;
    }else if(jiaodu >= kyp0 && jiaodu < kyp1)//敌人在右上角
    {
        fangxiang = 202;
    }else if(jiaodu >= kyp1 && jiaodu < kyp2)//敌人在右上角
    {
        fangxiang = 203;
    }else if(jiaodu >= kyp2 && jiaodu < kyp3)//敌人在右上角
    {
        fangxiang = 204;
    }else if(jiaodu >= kyp3 && jiaodu < kyp4)//敌人在右上角
    {
        fangxiang = 205;
    }else if(jiaodu >= kyp4 && jiaodu < kyp5)//敌人在右上角
    {
        fangxiang = 206;
    }else if(jiaodu >= kyp5 && jiaodu < kyp6)//敌人在右上角
    {
        fangxiang = 207;
    }else if(jiaodu >= kyp6 && jiaodu < kyp7)//敌人在右上角
    {
        fangxiang = 208;
    }else if(jiaodu >= kyp7 && jiaodu < kyp8)//敌人在右上角
    {
        fangxiang = 209;
    }else if((jiaodu >= kyp8 && jiaodu <= 3.141593) || (jiaodu >-3.141593 && jiaodu < -kyp8)) //敌人在左边
    {
        fangxiang = 210;
    }else if(jiaodu >= -kyp8 && jiaodu < -kyp7)//敌人在左下角
    {
        fangxiang = 211;
    }else if(jiaodu >= -kyp7 && jiaodu < -kyp6)//敌人在左下角
    {
        fangxiang = 212;
    }else if(jiaodu >= -kyp6 && jiaodu < -kyp5)//敌人在左下角
    {
        fangxiang = 213;
    }else if(jiaodu >= -kyp5 && jiaodu < -kyp4)//敌人在左下角
    {
        fangxiang = 214;
    }else if(jiaodu >= -kyp4 && jiaodu < -kyp3)//敌人在左下角
    {
        fangxiang = 215;
    }else if(jiaodu >= -kyp3 && jiaodu < -kyp2)//敌人在左下角
    {
        fangxiang = 216;
    }else if(jiaodu >= -kyp2 && jiaodu < -kyp1)//敌人在左下角
    {
        fangxiang = 217;
    }else if(jiaodu >= -kyp1 && jiaodu < -kyp0)//敌人在左下角
    {
        fangxiang = 218;
    }else{
        fangxiang = 201;
    }
    
    std::list<AStarTiledPoint> tmplist = this->getYuanChengListFor(tiPo, fangxiang);
    AStarTiledPoint getPoint;
    bool isZo = false;
    for (std::list<AStarTiledPoint>::iterator it = tmplist.begin(); it != tmplist.end(); it++) {
        if (*((*it).value) == 0) {
            getPoint = (*it);
            isZo = true;
            break;
        }
    }
    if (!isZo) {//说明没有找到攻击位，则精灵会站在当前攻击位上，并且设置坐标大于1000
        getPoint = tmplist.front();
        getPoint.x += 1000;//加1000用以区分当前未找到攻击位
    }
    tmplist.clear();
    return getPoint;

}

//为近战找到一个攻击站立瓦片地图坐标,
AStarTiledPoint AStarMap6SideManger::findAttackPointForOneTiled1(Point tilEnamy,Point tilAttack)
{
    
    Point po = tilEnamy;
    AStarTiledPoint tiPo = this->getTiledPointFromPixelPoint(po);
    //判断自已在目标的那一个位置
    Point ang = tilAttack;
    ang.subtract(po);
    float jiaodu = ang.getAngle();
    
    int fangxiang = 0;
    if (( jiaodu >= 0 && jiaodu < kjp0 )||(jiaodu < 0 && jiaodu >= -kjp0))//说明敌人在右边方向
    {
        fangxiang = 1;
    }else if(jiaodu >= kjp0 && jiaodu < kjp1)//敌人在右上角
    {
        fangxiang = 2;
    }else if(jiaodu >= kjp1 && jiaodu < kjp2)//敌人在左上角
    {
        fangxiang = 3;
    }else if((jiaodu >= kjp2 && jiaodu <= 3.141593) || (jiaodu >-3.141596 && jiaodu < -kjp2)) //敌人在左边
    {
        fangxiang = 4;
    }else if(jiaodu >= -kjp2 && jiaodu < -kjp1)//敌人在左下角
    {
        fangxiang = 5;
    }else if(jiaodu >= -kjp1 && jiaodu < -kjp0)//敌人在右下角
    {
        fangxiang = 6;
    }else{
        fangxiang = 1;
    }
    
    std::list<AStarTiledPoint> tmplist = this->getJinZhanListFor(tiPo, fangxiang);
    AStarTiledPoint getPoint;

    //说明没有找到攻击位，则精灵会站在当前攻击位上，并且设置坐标大于1000
    getPoint = tmplist.front();
    getPoint.x += 1000;//加1000用以区分当前未找到攻击位
    
    tmplist.clear();
    return getPoint;
}
//为中程找到一个攻击站立瓦片地图坐标
AStarTiledPoint AStarMap6SideManger::findAttackPointForOneTiled2(Point tilEnamy,Point tilAttack)
{
    Point po = tilEnamy;
    AStarTiledPoint tiPo = this->getTiledPointFromPixelPoint(po);
    //判断自已在目标的那一个位置
    Point ang = tilAttack;
    ang.subtract(po);
    float jiaodu = ang.getAngle();
    
    int fangxiang = 0;
    if (( jiaodu >= 0 && jiaodu < kzp0 )||(jiaodu < 0 && jiaodu >= -kzp0))//说明敌人在右边方向
    {
        fangxiang = 101;
    }else if(jiaodu >= kzp0 && jiaodu < kzp1)//敌人在右上角
    {
        fangxiang = 102;
    }else if(jiaodu >= kzp1 && jiaodu < kzp2)//敌人在左上角
    {
        fangxiang = 103;
    }else if(jiaodu >= kzp2 && jiaodu < kzp3)//敌人在左上角
    {
        fangxiang = 104;
    }else if(jiaodu >= kzp3 && jiaodu < kzp4)//敌人在左上角
    {
        fangxiang = 105;
    }else if(jiaodu >= kzp4 && jiaodu < kzp5)//敌人在左上角
    {
        fangxiang = 106;
    }else if((jiaodu >= kzp5 && jiaodu <= 3.141593) || (jiaodu >-3.141596 && jiaodu < -kzp5)) //敌人在左边
    {
        fangxiang = 107;
    }else if(jiaodu >= -kzp5 && jiaodu < -kzp4)//敌人在左下角
    {
        fangxiang = 108;
    }else if(jiaodu >= -kzp4 && jiaodu < -kzp3)//敌人在左下角
    {
        fangxiang = 109;
    }else if(jiaodu >= -kzp3 && jiaodu < -kzp2)//敌人在左下角
    {
        fangxiang = 110;
    }else if(jiaodu >= -kzp2 && jiaodu < -kzp1)//敌人在左下角
    {
        fangxiang = 111;
    }else if(jiaodu >= -kjp1 && jiaodu < -kjp0)//敌人在右下角
    {
        fangxiang = 112;
    }else{
        fangxiang = 101;
    }
    
    std::list<AStarTiledPoint> tmplist = this->getZhongChengListFor(tiPo, fangxiang);
    AStarTiledPoint getPoint;
    
    //说明没有找到攻击位，则精灵会站在当前攻击位上，并且设置坐标大于1000
    getPoint = tmplist.front();
    getPoint.x += 1000;//加1000用以区分当前未找到攻击位
    
    tmplist.clear();
    return getPoint;
}
//为远程找到一个攻击站立瓦片地图坐标
AStarTiledPoint AStarMap6SideManger::findAttackPointForOneTiled3(Point tilEnamy,Point tilAttack)
{
    Point po = tilEnamy;
    AStarTiledPoint tiPo = this->getTiledPointFromPixelPoint(po);
    //判断自已在目标的那一个位置
    Point ang = tilAttack;
    ang.subtract(po);
    float jiaodu = ang.getAngle();
    
    int fangxiang = 0;
    if (( jiaodu >= 0 && jiaodu < kzp0 )||(jiaodu < 0 && jiaodu >= -kzp0))//说明敌人在右边方向
    {
        fangxiang = 201;
    }else if(jiaodu >= kyp0 && jiaodu < kyp1)//敌人在右上角
    {
        fangxiang = 202;
    }else if(jiaodu >= kyp1 && jiaodu < kyp2)//敌人在右上角
    {
        fangxiang = 203;
    }else if(jiaodu >= kyp2 && jiaodu < kyp3)//敌人在右上角
    {
        fangxiang = 204;
    }else if(jiaodu >= kyp3 && jiaodu < kyp4)//敌人在右上角
    {
        fangxiang = 205;
    }else if(jiaodu >= kyp4 && jiaodu < kyp5)//敌人在右上角
    {
        fangxiang = 206;
    }else if(jiaodu >= kyp5 && jiaodu < kyp6)//敌人在右上角
    {
        fangxiang = 207;
    }else if(jiaodu >= kyp6 && jiaodu < kyp7)//敌人在右上角
    {
        fangxiang = 208;
    }else if(jiaodu >= kyp7 && jiaodu < kyp8)//敌人在右上角
    {
        fangxiang = 209;
    }else if((jiaodu >= kyp8 && jiaodu <= 3.141593) || (jiaodu >-3.141593 && jiaodu < -kyp8)) //敌人在左边
    {
        fangxiang = 210;
    }else if(jiaodu >= -kyp8 && jiaodu < -kyp7)//敌人在左下角
    {
        fangxiang = 211;
    }else if(jiaodu >= -kyp7 && jiaodu < -kyp6)//敌人在左下角
    {
        fangxiang = 212;
    }else if(jiaodu >= -kyp6 && jiaodu < -kyp5)//敌人在左下角
    {
        fangxiang = 213;
    }else if(jiaodu >= -kyp5 && jiaodu < -kyp4)//敌人在左下角
    {
        fangxiang = 214;
    }else if(jiaodu >= -kyp4 && jiaodu < -kyp3)//敌人在左下角
    {
        fangxiang = 215;
    }else if(jiaodu >= -kyp3 && jiaodu < -kyp2)//敌人在左下角
    {
        fangxiang = 216;
    }else if(jiaodu >= -kyp2 && jiaodu < -kyp1)//敌人在左下角
    {
        fangxiang = 217;
    }else if(jiaodu >= -kyp1 && jiaodu < -kyp0)//敌人在左下角
    {
        fangxiang = 218;
    }else{
        fangxiang = 201;
    }
    
    std::list<AStarTiledPoint> tmplist = this->getYuanChengListFor(tiPo, fangxiang);
    AStarTiledPoint getPoint;

    getPoint = tmplist.front();
    getPoint.x += 1000;//加1000用以区分当前未找到攻击位
    
    tmplist.clear();
    return getPoint;
}

//坐标转换,
//将瓦片坐标转换为6边形三直线坐标
AStar6SidePoint AStarMap6SideManger::conventTiledPointTo6SidePoint(AStarTiledPoint tPo)
{
    AStar6SidePoint tmp6SidePoint;
    tmp6SidePoint.value = tPo.value;
    if (tPo.y%2 == 0) {
        int haly = (int)(tPo.y/2);
        tmp6SidePoint.a = tPo.x+tPo.y+haly;
        tmp6SidePoint.b = 2*tPo.x;
        tmp6SidePoint.c = tPo.x-(tPo.y+haly);
    }else{
        int haly = (int)((tPo.y-1)/2);
        tmp6SidePoint.a = tPo.x+tPo.y+haly+1;
        tmp6SidePoint.b = 2*tPo.x+1;
        tmp6SidePoint.c = tPo.x-(tPo.y+haly);
    }
    return tmp6SidePoint;
}
//将6边形三直线坐标转换为瓦片坐标
AStarTiledPoint AStarMap6SideManger::convent6SidePointPointToTiled(AStar6SidePoint sPo)
{
    AStarTiledPoint tmptiled;
    tmptiled.value = sPo.value;
    if (sPo.b%2==0) {
        tmptiled.x = (int)(sPo.b/2);
    }else{
        tmptiled.x = (int)((sPo.b-1)/2);
    }
    tmptiled.y = (int)((2*sPo.a-sPo.b)/3);
    return tmptiled;
}
//通过瓦片地图坐标得到瓦片坐标上的像素坐标
AStarPixelPoint AStarMap6SideManger::getPixelPointFromTiledPoint(AStarTiledPoint tPo)
{
    AStarPixelPoint tmpPoint;
    int x = 0;
    int y = 0;
    tmpPoint.value = tPo.value;
    float sideLen = kTiledSidelen;
    if (tPo.y%2 == 0) {
        x = tPo.x*khalfTiledWidth*2 + kOPointX;
    }else{
        x = (tPo.x*2*khalfTiledWidth + kOPointX + khalfTiledWidth);
    }
    y = int((sideLen*3/2)*tPo.y+kOPointY);
    y = kMapHeight - y;
    tmpPoint.po = Point(x,y);
    return tmpPoint;
}
//通过六边形三线坐标得到六边形瓦片像素坐标
AStarPixelPoint AStarMap6SideManger::getPixelPointFrom6Side_abcPoint(AStar6SidePoint sPo)
{
    AStarTiledPoint tmp = convent6SidePointPointToTiled(sPo);
    return getPixelPointFromTiledPoint(tmp);
}
//通过像素坐标得到6边形的三线坐标
AStar6SidePoint AStarMap6SideManger::get6SidePointFromPixelPoint(Point po)
{
    AStarTiledPoint tmpTiled = getTiledPointFromPixelPoint(po);
    return conventTiledPointTo6SidePoint(tmpTiled);
}
//通过像素坐标得到地图瓦片坐标
AStarTiledPoint AStarMap6SideManger::getTiledPointFromPixelPoint(Point po)
{
    AStarTiledPoint tmpTiled;
    tmpTiled.y = (int)(((kMapHeight - po.y) - kOPointY+kTiledSidelen)/(3*kTiledSidelen/2));
    if (tmpTiled.y%2 == 0) {
        tmpTiled.x = (int)((po.x - kOPointX+khalfTiledWidth)/(2*khalfTiledWidth));
    }else{
        tmpTiled.x = (int)((po.x - khalfTiledWidth+(kOPointX-khalfTiledWidth) )/(2*khalfTiledWidth));
    }
    tmpTiled.value = &(mapArr[tmpTiled.x][tmpTiled.y]);
    return tmpTiled;
}
AStarPixelPoint AStarMap6SideManger::getPixePointFromTiledPoint(Point tPo)
{
    AStarTiledPoint po;
    po.x = (int)tPo.x;
    po.y = (int)tPo.y;
    po.value = &(mapArr[po.x][po.y]);
    return getPixelPointFromTiledPoint(po);
}
//初始化地图瓦片数组,地图数据由xml表配制，加载进入mapArr的瓦片地图数组，然后再将值转换到6边形数组中。
void AStarMap6SideManger::initMapArrWithMapID(int mapID)
{
    for (int i = 0; i < kTiledMapWidth; i++) {
        for (int j = 0; j < kTiledMapHeight; j++) {
            mapArr[i][j] = 0;
            mapArrPointNumber[i][j] = 0;
        }
    }
}
void AStarMap6SideManger::addMapPointValue(int x,int y)
{
    if (x < 0 || x > (kTiledMapWidth-1) || y < 0 || y > (kTiledMapHeight-1)) {
        return;
    }
    mapArr[x][y] += 1;
}

//设置瓦片不可通过。
void AStarMap6SideManger::setMapPoint(int x,int y,int value)
{
    if (x < 0 || x > (kTiledMapWidth-1) || y < 0 || y > (kTiledMapHeight-1) || value < 0) {
        return;
    }
    mapArr[x][y] = value;
}
//得到某个瓦片通过花费
int  AStarMap6SideManger::getMapPointValue(int x,int y)
{
    if (x < 0 || x > (kTiledMapWidth-1) || y < 0 || y > (kTiledMapHeight-1))
    {
        return kMaxCast;
    }
    return mapArr[x][y];
}
//清除某个瓦片花费
void AStarMap6SideManger::cleanMapPoint(int x,int y)
{
    if (x < 0 || x > (kTiledMapWidth-1) || y < 0 || y > (kTiledMapHeight-1)) {
        return;
    }
    mapArr[x][y] = 0;
}
void AStarMap6SideManger::subMapPointValue(int x,int y)
{
    if (x < 0 || x > (kTiledMapWidth-1) || y < 0 || y > (kTiledMapHeight-1) || mapArr[x][y] == 0) {
        return;
    }
    mapArr[x][y] -= 1;
}
//通过像素点设置像素点所在瓦片花费值
void AStarMap6SideManger::setMapPointWithPixePoint(cocos2d::Point po,int value )
{
   AStarTiledPoint tmpTiled = getTiledPointFromPixelPoint(po);
    *(tmpTiled.value) = value;
}
//通过像素点清除瓦片花费值
void AStarMap6SideManger::cleanMapPointWithPixePoint(cocos2d::Point po)
{
    AStarTiledPoint tmpTiled = getTiledPointFromPixelPoint(po);
    *(tmpTiled.value) = 0;
}

std::list<AStarTiledPoint> AStarMap6SideManger::findRoadWithTiledPoint(cocos2d::Point pStart,cocos2d::Point pEnd)
{
    AStarTiledPoint tmps;
    tmps.x = (int)pStart.x;
    tmps.y = (int)pStart.y;
    tmps.value = &(mapArr[tmps.x][tmps.y]);
    
    AStarTiledPoint tmpe;
    tmpe.x = (int)pEnd.x;
    tmpe.y = (int)pEnd.y;
    tmpe.value = &(mapArr[tmps.x][tmps.y]);
    
    AStarTiledPoint side6PoStart = tmps;
    AStarTiledPoint side6PoEnd = tmpe;
    
    AStarTiledNodeCost startNode;
    AStarTiledNodeCost endNode;
    startNode.x = side6PoStart.x;
    startNode.y = side6PoStart.y;
    endNode.x = side6PoEnd.x;
    endNode.y = side6PoEnd.y;
    startNode.cast = getCast(startNode.x, startNode.y, endNode.x, endNode.y);
    endNode.cast = 0;
    AStarTiledNodeCost findNode = startNode;
    //std::make_heap()
    std::vector<AStarTiledNodeCost> openPointHeap; //打开的路点
    std::vector<AStarTiledNodeCost> closedPoint;   //关闭的路点
    std::list<AStarTiledPoint> findRoad;           //寻到的路径
    openPointHeap.push_back(findNode);
    //建立二叉堆
    std::make_heap(openPointHeap.begin(),openPointHeap.end(),cmpCast);
    do{
        std::pop_heap(openPointHeap.begin(),openPointHeap.end());
        findNode = openPointHeap.back();
        closedPoint.push_back(findNode);
        openPointHeap.pop_back();
        
        int xd = findNode.x;
        int yd = findNode.y;
        
        //point1 (a+1,b+2,c+1)

        int tmpx = xd+1;
        int tmpy = yd;
        if (getMapPointValue(tmpx, tmpy) == 0) {
            findNode.x = tmpx;
            findNode.y = tmpy;
            findNode.cast = 48.0f + getCast(findNode.x,findNode.y,endNode.x,endNode.y);
            if (!findInClosed(findNode,closedPoint) && !findInClosed(findNode, openPointHeap)) {
                openPointHeap.push_back(findNode);
                std::push_heap(openPointHeap.begin(), openPointHeap.end());
            }
        }
        log("1findNode=(%d,%d),startNode=(%d,%d),endNode=(%d,%d)",findNode.x,findNode.y,startNode.x,startNode.y,endNode.x,endNode.y);
        //point2 (a-1,b+1,c+2)
        if (yd%2 == 1) {
            tmpx = xd+1;
            tmpy = yd-1;
        }else{
            tmpx = xd;
            tmpy = yd-1;
        }
        if (getMapPointValue(tmpx, tmpy) == 0) {
            findNode.x = tmpx;
            findNode.y = tmpy;
            findNode.cast = 48.0f + getCast(findNode.x,findNode.y,endNode.x,endNode.y);
            if (!findInClosed(findNode,closedPoint) && !findInClosed(findNode, openPointHeap)) {
                openPointHeap.push_back(findNode);
                std::push_heap(openPointHeap.begin(), openPointHeap.end());
            }
            
        }
        log("2findNode=(%d,%d),startNode=(%d,%d),endNode=(%d,%d)",findNode.x,findNode.y,startNode.x,startNode.y,endNode.x,endNode.y);
        //point3 (a-2,b-1,c+1)
        if (yd%2 == 1) {
            tmpx = xd;
            tmpy = yd-1;
        }else{
            tmpx = xd-1;
            tmpy = yd-1;
        }
        
        if (getMapPointValue(tmpx, tmpy) == 0) {
            findNode.x = tmpx;
            findNode.y = tmpy;
            findNode.cast = 48.0f + getCast(findNode.x,findNode.y,endNode.x,endNode.y);
            if (!findInClosed(findNode,closedPoint) && !findInClosed(findNode, openPointHeap)) {
                openPointHeap.push_back(findNode);
                std::push_heap(openPointHeap.begin(), openPointHeap.end());
            }
            
        }
        log("3findNode=(%d,%d),startNode=(%d,%d),endNode=(%d,%d)",findNode.x,findNode.y,startNode.x,startNode.y,endNode.x,endNode.y);
        //point4 (a-1,b-2,c-1)
        tmpx = xd-1;
        tmpy = yd;
        if (getMapPointValue(tmpx, tmpy) == 0) {
            findNode.x = tmpx;
            findNode.y = tmpy;
            findNode.cast = 48.0f + getCast(findNode.x,findNode.y,endNode.x,endNode.y);
            if (!findInClosed(findNode,closedPoint) && !findInClosed(findNode, openPointHeap)) {
                openPointHeap.push_back(findNode);
                std::push_heap(openPointHeap.begin(), openPointHeap.end());
            }
            
        }
        log("4findNode=(%d,%d),startNode=(%d,%d),endNode=(%d,%d)",findNode.x,findNode.y,startNode.x,startNode.y,endNode.x,endNode.y);
        //point5 (a+1,b-1,c-2)
        if (yd%2 == 1) {
            tmpx = xd;
            tmpy = yd+1;
        }else{
            tmpx = xd-1;
            tmpy = yd+1;
        }
        
        if (getMapPointValue(tmpx, tmpy) == 0) {
            findNode.x = tmpx;
            findNode.y = tmpy;
            findNode.cast = 48.0f + getCast(findNode.x,findNode.y,endNode.x,endNode.y);
            if (!findInClosed(findNode,closedPoint) && !findInClosed(findNode, openPointHeap)) {
                openPointHeap.push_back(findNode);
                std::push_heap(openPointHeap.begin(), openPointHeap.end());
            }
            
        }
        log("5findNode=(%d,%d),startNode=(%d,%d),endNode=(%d,%d)",findNode.x,findNode.y,startNode.x,startNode.y,endNode.x,endNode.y);
        //point6 (a+2,b+1,c-1)
        if (yd%2 == 1) {
            tmpx = xd+1;
            tmpy = yd+1;
        }else{
            tmpx = xd;
            tmpy = yd+1;
        }
        
        if (getMapPointValue(tmpx, tmpy) == 0) {
            findNode.x = tmpx;
            findNode.y = tmpy;
            findNode.cast = 48.0f + getCast(findNode.x,findNode.y,endNode.x,endNode.y);
            if (!findInClosed(findNode,closedPoint) && !findInClosed(findNode, openPointHeap)) {
                openPointHeap.push_back(findNode);
                std::push_heap(openPointHeap.begin(), openPointHeap.end());
            }
            
        }
        log("6findNode=(%d,%d),startNode=(%d,%d),endNode=(%d,%d)",findNode.x,findNode.y,startNode.x,startNode.y,endNode.x,endNode.y);
        std::sort_heap(openPointHeap.begin(), openPointHeap.end());
        log("sort one");
    }while (findNode.x != endNode.x || findNode.y != endNode.y);
    
    closedPoint.push_back(endNode);//刚结尾节点放入关闭节点组中
    //到这里就得到了和路径相关的关闭节点，再在关闭组中由结尾节点反向查找回起始点，所得到的数组即寻路路径
    openPointHeap.clear();
    std::list<AStarTiledPoint> roadlisttmp;
    do{
        AStarTiledNodeCost tmp = closedPoint.back();
        AStarTiledPoint t6tmp;
        t6tmp.x = tmp.x;
        t6tmp.y = tmp.y;
        t6tmp.value = &(mapArr[t6tmp.x][t6tmp.y]);
        roadlisttmp.push_back(t6tmp);
        closedPoint.pop_back();
    }while (!closedPoint.empty());
    
//    std::list<AStarTiledPoint> refindroad = this->reFindRoadWithTiledPoint(pEnd, pStart);
//    
//    std::list<AStarTiledPoint> roadlist;
//    do{
//        AStarTiledPoint outPoint;
//        outPoint = roadlisttmp.back();
//        roadlisttmp.pop_back();
//        for (std::list<AStarTiledPoint>::iterator it = refindroad.begin(); it != refindroad.end(); it++) {
//            if (outPoint.x == (*it).x && outPoint.y == (*it).y) {
//                roadlist.push_back(outPoint);
//                continue;
//            }
//        }
//    }while (!roadlisttmp.empty());
    
    return roadlisttmp;
}

std::list<AStarTiledPoint> AStarMap6SideManger::reFindRoadWithTiledPoint(cocos2d::Point pStart,cocos2d::Point pEnd)
{
    AStarTiledPoint tmps;
    tmps.x = (int)pStart.x;
    tmps.y = (int)pStart.y;
    tmps.value = &(mapArr[tmps.x][tmps.y]);
    
    AStarTiledPoint tmpe;
    tmpe.x = (int)pEnd.x;
    tmpe.y = (int)pEnd.y;
    tmpe.value = &(mapArr[tmps.x][tmps.y]);
    
    AStarTiledPoint side6PoStart = tmps;
    AStarTiledPoint side6PoEnd = tmpe;
    
    AStarTiledNodeCost startNode;
    AStarTiledNodeCost endNode;
    startNode.x = side6PoStart.x;
    startNode.y = side6PoStart.y;
    endNode.x = side6PoEnd.x;
    endNode.y = side6PoEnd.y;
    startNode.cast = getCast(startNode.x, startNode.y, endNode.x, endNode.y);
    endNode.cast = 0;
    AStarTiledNodeCost findNode = startNode;
    //std::make_heap()
    std::vector<AStarTiledNodeCost> openPointHeap; //打开的路点
    std::vector<AStarTiledNodeCost> closedPoint;   //关闭的路点
    std::list<AStarTiledPoint> findRoad;           //寻到的路径
    openPointHeap.push_back(findNode);
    //建立二叉堆
    std::make_heap(openPointHeap.begin(),openPointHeap.end(),cmpCast);
    do{
        std::pop_heap(openPointHeap.begin(),openPointHeap.end());
        findNode = openPointHeap.back();
        closedPoint.push_back(findNode);
        openPointHeap.pop_back();
        
        int xd = findNode.x;
        int yd = findNode.y;
        
        //point1 (a+1,b+2,c+1)
        
        int tmpx = xd+1;
        int tmpy = yd;
        if (getMapPointValue(tmpx, tmpy) == 0) {
            findNode.x = tmpx;
            findNode.y = tmpy;
            findNode.cast = 48.0f + getCast(findNode.x,findNode.y,endNode.x,endNode.y);
            if (!findInClosed(findNode,closedPoint) && !findInClosed(findNode, openPointHeap)) {
                openPointHeap.push_back(findNode);
                std::push_heap(openPointHeap.begin(), openPointHeap.end());
            }
        }
        log("1findNode=(%d,%d),startNode=(%d,%d),endNode=(%d,%d)",findNode.x,findNode.y,startNode.x,startNode.y,endNode.x,endNode.y);
        //point2 (a-1,b+1,c+2)
        if (yd%2 == 1) {
            tmpx = xd+1;
            tmpy = yd-1;
        }else{
            tmpx = xd;
            tmpy = yd-1;
        }
        if (getMapPointValue(tmpx, tmpy) == 0) {
            findNode.x = tmpx;
            findNode.y = tmpy;
            findNode.cast = 48.0f + getCast(findNode.x,findNode.y,endNode.x,endNode.y);
            if (!findInClosed(findNode,closedPoint) && !findInClosed(findNode, openPointHeap)) {
                openPointHeap.push_back(findNode);
                std::push_heap(openPointHeap.begin(), openPointHeap.end());
            }
            
        }
        log("2findNode=(%d,%d),startNode=(%d,%d),endNode=(%d,%d)",findNode.x,findNode.y,startNode.x,startNode.y,endNode.x,endNode.y);
        //point3 (a-2,b-1,c+1)
        if (yd%2 == 1) {
            tmpx = xd;
            tmpy = yd-1;
        }else{
            tmpx = xd-1;
            tmpy = yd-1;
        }
        
        if (getMapPointValue(tmpx, tmpy) == 0) {
            findNode.x = tmpx;
            findNode.y = tmpy;
            findNode.cast = 48.0f + getCast(findNode.x,findNode.y,endNode.x,endNode.y);
            if (!findInClosed(findNode,closedPoint) && !findInClosed(findNode, openPointHeap)) {
                openPointHeap.push_back(findNode);
                std::push_heap(openPointHeap.begin(), openPointHeap.end());
            }
            
        }
        log("3findNode=(%d,%d),startNode=(%d,%d),endNode=(%d,%d)",findNode.x,findNode.y,startNode.x,startNode.y,endNode.x,endNode.y);
        //point4 (a-1,b-2,c-1)
        tmpx = xd-1;
        tmpy = yd;
        if (getMapPointValue(tmpx, tmpy) == 0) {
            findNode.x = tmpx;
            findNode.y = tmpy;
            findNode.cast = 48.0f + getCast(findNode.x,findNode.y,endNode.x,endNode.y);
            if (!findInClosed(findNode,closedPoint) && !findInClosed(findNode, openPointHeap)) {
                openPointHeap.push_back(findNode);
                std::push_heap(openPointHeap.begin(), openPointHeap.end());
            }
            
        }
        log("4findNode=(%d,%d),startNode=(%d,%d),endNode=(%d,%d)",findNode.x,findNode.y,startNode.x,startNode.y,endNode.x,endNode.y);
        //point5 (a+1,b-1,c-2)
        if (yd%2 == 1) {
            tmpx = xd;
            tmpy = yd+1;
        }else{
            tmpx = xd-1;
            tmpy = yd+1;
        }
        
        if (getMapPointValue(tmpx, tmpy) == 0) {
            findNode.x = tmpx;
            findNode.y = tmpy;
            findNode.cast = 48.0f + getCast(findNode.x,findNode.y,endNode.x,endNode.y);
            if (!findInClosed(findNode,closedPoint) && !findInClosed(findNode, openPointHeap)) {
                openPointHeap.push_back(findNode);
                std::push_heap(openPointHeap.begin(), openPointHeap.end());
            }
            
        }
        log("5findNode=(%d,%d),startNode=(%d,%d),endNode=(%d,%d)",findNode.x,findNode.y,startNode.x,startNode.y,endNode.x,endNode.y);
        //point6 (a+2,b+1,c-1)
        if (yd%2 == 1) {
            tmpx = xd+1;
            tmpy = yd+1;
        }else{
            tmpx = xd;
            tmpy = yd+1;
        }
        
        if (getMapPointValue(tmpx, tmpy) == 0) {
            findNode.x = tmpx;
            findNode.y = tmpy;
            findNode.cast = 48.0f + getCast(findNode.x,findNode.y,endNode.x,endNode.y);
            if (!findInClosed(findNode,closedPoint) && !findInClosed(findNode, openPointHeap)) {
                openPointHeap.push_back(findNode);
                std::push_heap(openPointHeap.begin(), openPointHeap.end());
            }
            
        }
        log("6findNode=(%d,%d),startNode=(%d,%d),endNode=(%d,%d)",findNode.x,findNode.y,startNode.x,startNode.y,endNode.x,endNode.y);
        std::sort_heap(openPointHeap.begin(), openPointHeap.end());
        log("sort one");
    }while (findNode.x != endNode.x || findNode.y != endNode.y);
    
    closedPoint.push_back(endNode);//刚结尾节点放入关闭节点组中
    //到这里就得到了和路径相关的关闭节点，再在关闭组中由结尾节点反向查找回起始点，所得到的数组即寻路路径
    openPointHeap.clear();
    std::list<AStarTiledPoint> roadlisttmp;
    do{
        AStarTiledNodeCost tmp = closedPoint.back();
        AStarTiledPoint t6tmp;
        t6tmp.x = tmp.x;
        t6tmp.y = tmp.y;
        t6tmp.value = &(mapArr[t6tmp.x][t6tmp.y]);
        roadlisttmp.push_back(t6tmp);
        closedPoint.pop_back();
    }while (!closedPoint.empty());
    return roadlisttmp;
}
//将6边形abc三线坐标路径转换为像素坐标路径
std::list<AStarPixelPoint> AStarMap6SideManger::conventFrom6Side_abclist(std::list<AStar6SidePoint> side6list)
{
    std::list<AStar6SidePoint> tmplist = side6list;
    std::list<AStarPixelPoint> outlist;
    AStar6SidePoint abcPoint;
    do{
        abcPoint = tmplist.front();
        AStarPixelPoint  pixeTmp= getPixelPointFrom6Side_abcPoint(abcPoint);
        outlist.push_back(pixeTmp);
        tmplist.pop_front();
    }while (!tmplist.empty());
    return outlist;
}

int AStarMap6SideManger::get6SidePointValue(int a,int b,int c)
{
    if (a<0 || a > (ka_LineWidth - 1) || b<0 || b> (kb_LineWidth -1) || (c+kc_LineOffect)<0 || (c+kc_LineOffect)>(kc_LineWidth -1)) {
        return kMaxCast;
    }
    if (map_abc_Arr[a][b][c+kc_LineOffect] == nullptr) {
        return kMaxCast;
    }
    return *(map_abc_Arr[a][b][c+kc_LineOffect]);
}
void AStarMap6SideManger::set6SidePointValue(int a,int b,int c,int value)
{
    if (a<0 || a > (ka_LineWidth - 1) || b<0 || b> (kb_LineWidth -1) || (c+kc_LineOffect)<0 || (c+kc_LineOffect)>(kc_LineWidth -1) || value < 0) {
        return;
    }
    *(map_abc_Arr[a][b][c+kc_LineOffect]) = value;
}

void AStarMap6SideManger::showTiledBox(cocos2d::Layer *lay)
{
    
    int maxX = kTiledMapWidth;
    int maxY = kTiledMapHeight;
    for (int i = 0; i < maxX; i++) {
        for (int j = 0; j < maxY; j++) {
            AStarPixelPoint tmpx = this->getPixePointFromTiledPoint(Vec2(i,j));
            Sprite* tSp = Sprite::create("test/tiled_wightbig.png");
            tSp->setPosition(tmpx.po);
            if(j%2==0){
                if (i%3 == 0) {
                    tSp->setColor(Color3B(255,0,0));
                    
                }else if(i%3 == 1)
                {
                    tSp->setColor(Color3B(0,255,0));
                }else if(i%3 == 2)
                {
                    tSp->setColor(Color3B(0,0,255));
                }
            }else{
                if (i%3 == 0) {
                    tSp->setColor(Color3B(255,0,255));
                    
                }else if(i%3 == 1)
                {
                    tSp->setColor(Color3B(255,0,0));
                }else if(i%3 == 2)
                {
                    tSp->setColor(Color3B(0,255,0));
                }
            }
            
            tSp->setCascadeOpacityEnabled(true);
            tSp->setOpacity(20);
            
            tSp->setTag(i+j*kTiledMapWidth+1000);
            lay->addChild(tSp);
            log("(i,j) = (%d,%d), pixel point (%f,%f) = %d",i,j,tmpx.po.x,tmpx.po.y,*(tmpx.value));
        }
    }
}
