//
//  PointUtil.h
//  game1
//  这个是创建一些基本的cocos2d类时会用到
//  Created by 俊盟科技1 on 8/25/14.
//
//

#ifndef __game1__PointUtil__
#define __game1__PointUtil__

#include "cocos2d.h"

class BaseSprite;

class PointUtil
{
    
public:
    //通过当前坐标，要攻击的目标坐标，以及攻击距离计算如果要攻击到目标，自已要移动到的坐标
   static cocos2d::Point getMoveToPoint(cocos2d::Point &startPo,cocos2d::Point &targetPo,int attackRange);
    //得到坐标po2到po1的向量角度
    static float getJiaoDuWithTowPoint(cocos2d::Point po1,cocos2d::Point po2);
    //查找近战攻击敌人时合适的攻击位
    static int getAttackSpace(std::map<int,BaseSprite*> spVector,std::vector<int> spaceVector);
    //得到某个角度上的长度为l的矢量
    static cocos2d::Vec2 getVec2With(float lenth,float jiaodu);
    //得到6个站位矢量
    //当前精灵的攻击位上是否有精灵，精灵近战攻击位编号如下
    /*
      1   6
     2  s  5
      3   4
     *///得到精灵的站位单位矢量
    static cocos2d::Vec2 Vec2WithAttackSpace(int n);
    
    //当两个精灵相向而行时的坐标计算
/*
 精灵Ａ，移动速度为Va,攻击距离为Ra,精灵B,移动速度为Vb,攻击距离为Rb.
 A与Ｂ的距离为l
 
    A点 o------------------------------------------------o B点
                                 t1时间
                         A点 o-------|-------------o B点
                             |<-Ra ->|
                             Ra = t1*Va
    当 Ra > Rb时，有t1 = (l-Ra)/(Va+Vb);t2 = (Ra+Rb)/Vb
    Ａ向Ｂ移动的总时间tA = t1;
    Ｂ向Ａ移动的总时间tB = t1 + t2;
    得出，Ａ向Ｂ移动的时间为tA,移动的长度lA = tA * Va;
         Ｂ向Ａ移动的时间为tB,移动的长度lB = tB * Vb;
 */
    //下边是算法
    static void TwoSpriteMoveAttackTimeAndLenth(float &tA,float &lA,cocos2d::Point Pa,int Va,int attackRa, float &tB,float &lB,cocos2d::Point Pb,int Vb,int attackRb);
    
};
#endif /* defined(__game1__PointUtil__) */
