//
//  AStarMapManger.cpp
//  game3
//
//  Created by 俊盟科技1 on 10/18/14.
//
//

#include "AStarMapManger.h"
#include <functional>


static void printRoad(std::list<AStarNodeCost> li)
{
    std::string outstr = "road:";
    for (std::list<AStarNodeCost>::iterator it = li.begin(); it != li.end(); it++) {
        outstr += "(" + std::to_string((*it).x) + "," + std::to_string((*it).y)+"),";
    }
    cocos2d::log("");
    
}

static bool cmpCast(AStarNodeCost a,AStarNodeCost b)
{
    return a<b;
}
static bool cmpCastBig(AStarNodeCost a,AStarNodeCost b)
{
    return a>b;
}
static inline float getCast(int x1,int y1,int x2,int y2)
{
    return sqrtf((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
static AStarMapManger *s_sharedAStarMapManger = nullptr;

AStarMapManger *AStarMapManger::sharedAStarMapManger()
{
    if (s_sharedAStarMapManger == nullptr)
    {
        s_sharedAStarMapManger = new AStarMapManger();
        if (!s_sharedAStarMapManger || !s_sharedAStarMapManger->init())
        {
            CC_SAFE_DELETE(s_sharedAStarMapManger);
        }
    }
    return s_sharedAStarMapManger;
}

void AStarMapManger::destroyInstance()
{
    
    CC_SAFE_RELEASE_NULL(s_sharedAStarMapManger);
}

AStarMapManger::AStarMapManger(void)
{
  
}


AStarMapManger::~AStarMapManger(void)
{
   
}


bool AStarMapManger::init()
{
    bool bRet = false;
    do
    {
        
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}
bool AStarMapManger::initTmxMapForAStarArr(cocos2d::TMXLayer *tiledLayer,cocos2d::TMXMapInfo* mapinfo)
{
    
    return true;
}
void AStarMapManger::setMapPoint(int x,int y,int value)
{
    m_mapArr[x][y] = value;
}
int  AStarMapManger::getMapPointValue(int x,int y)
{
    return m_mapArr[x][y];
}
void AStarMapManger::cleanMapPoint(int x,int y)
{
    m_mapArr[x][y] = 0;
}
AStarPoint AStarMapManger::getAStarPointWithPixelPoint(cocos2d::Point po)
{
    
    int x = (int)(po.x/kTiledWidght);
    int y = (int)((kMapHeight - po.y)/kTiledWidght);
    AStarPoint tmp;
    tmp.x = x;
    tmp.y = y;
    tmp.value = &(m_mapArr[x][y]);
    return tmp;
}
void AStarMapManger::setMapPointWithPixePoint(cocos2d::Point po,int value)
{
    int x = (int)(po.x/kTiledWidght);
    int y = (int)((kMapHeight - po.y)/kTiledWidght);
    m_mapArr[x][y] = value;
}
void AStarMapManger::cleanMapPointWithPixePoint(cocos2d::Point po)
{
    int x = (int)(po.x/kTiledWidght);
    int y = (int)((kMapHeight - po.y)/kTiledWidght);
    m_mapArr[x][y] = 0;
}

std::list<AStarPoint> AStarMapManger::findRoad(cocos2d::Point pStart,cocos2d::Point pEnd)
{
    AStarNodeCost startNode;
    AStarNodeCost endNode;
    startNode.x = (int)(pStart.x/kTiledWidght);
    startNode.y = (int)((kMapHeight - pStart.y)/kTiledWidght);
    endNode.x = (int)(pEnd.x/kTiledWidght);
    endNode.y = (int)((kMapHeight - pEnd.y)/kTiledWidght);
    startNode.cast = getCast(startNode.x, startNode.y, endNode.x, endNode.y);
    endNode.cast = 0;
    AStarNodeCost findNode = startNode;
    //std::make_heap()
    std::vector<AStarNodeCost> openPointHeap; //打开的路点
    std::vector<AStarNodeCost> closedPoint;   //关闭的路点
    std::list<AStarPoint> findRoad;           //寻到的路径
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
        for (int i =  xd- 1; i <= xd + 1; i++) {
            for (int j = yd -1; j <= yd +1; j++) {
                if (i<0 || i > (kAstarWidght-1) || j < 0 || j > (kAstarHeight-1) || this->getMapPointValue(i, j) > 0) {
                    continue;
                }
                if (i != xd || j != yd){
                    findNode.x = i;
                    findNode.y = j;
                    if (i == xd || j == yd) {
                        findNode.cast += 1.0f + getCast(i, j, endNode.x, endNode.y);
                    }else{
                        findNode.cast += 1.141f + getCast(i, j, endNode.x, endNode.y);
                    }
                    openPointHeap.push_back(findNode);
                    std::push_heap(openPointHeap.begin(), openPointHeap.end());
                }
            }
        }
    }while (findNode.x != endNode.x || findNode.y != endNode.y);
    
    closedPoint.push_back(endNode);//刚结尾节点放入关闭节点组中
    //到这里就得到了和路径相关的关闭节点，再在关闭组中由结尾节点反向查找回起始点，所得到的数组即寻路路径
    openPointHeap.clear();
    std::list<AStarNodeCost> roadlisttmp;
    do{
        AStarNodeCost tmp = closedPoint.back();
        closedPoint.pop_back();
        roadlisttmp.push_back(tmp);
    }while (!closedPoint.empty());
    
    printRoad(roadlisttmp);
    
//    do{
//        
//    }while(findNode.x != startNode.x || findNode.y != startNode.y);
//    
    return findRoad;
}


////动态申请vector 并对vector建堆
//vector<int> *pvet = new vector<int>(40);
//pvet->assign(a, a + MAXN);
//
////建堆
//make_heap(pvet->begin(), pvet->end());
//PrintfVectorInt(*pvet);
//
////加入新数据 先在容器中加入，再调用push_heap()
//pvet->push_back(25);
//push_heap(pvet->begin(), pvet->end());
//PrintfVectorInt(*pvet);
//
////删除数据  要先调用pop_heap()，再在容器中删除
//pop_heap(pvet->begin(), pvet->end());
//pvet->pop_back();
//pop_heap(pvet->begin(), pvet->end());
//pvet->pop_back();
//PrintfVectorInt(*pvet);
//
////堆排序
//sort_heap(pvet->begin(), pvet->end());
//PrintfVectorInt(*pvet);
cocos2d::Point AStarMapManger::conventPointForPixe(AStarPoint& apo)
{
    cocos2d::Point po = cocos2d::Vec2(apo.x*kTiledWidght + kTiledWidght/2.0f,apo.y*kTiledWidght + kTiledWidght/2.0f);
    return po;
}


