//
//  PointUtil.cpp
//  game1
//
//  Created by 俊盟科技1 on 8/25/14.
//
//

#include "PointUtil.h"
#include "BaseSprite.h"
#include "WarConfig.h"
cocos2d::Point PointUtil::getMoveToPoint(cocos2d::Point &startPo,cocos2d::Point &targetPo,int attackRange)
{
    cocos2d::Point po1 = startPo;
    cocos2d::Point po2 = targetPo;
    float tmp = attackRange;
    cocos2d::Point p2_p1;
    
    if (p2_p1.length() > (float)attackRange) {
        
        cocos2d::Vec2::subtract(po2,po1,&p2_p1);
        p2_p1.normalize();
        p2_p1.scale(tmp);
        cocos2d::Point pomoveto = po1 + p2_p1;
        return pomoveto;
    }else{
        return nullptr;
    }
}

float PointUtil::getJiaoDuWithTowPoint(cocos2d::Point po1,cocos2d::Point po2)
{
    cocos2d::Point pox ;
    cocos2d::Vec2::subtract(po1,po2,&pox);
    return (pox.getAngle()*360/(2*3.14159));
}


//查找近战攻击敌人时合适的攻击位
int PointUtil::getAttackSpace(std::map<int,BaseSprite*> spVector,std::vector<int> spaceVector)
{
    if (spVector[spaceVector[0]] != nullptr) {
        //说明5号位已经有人站，则找4号位，如果4号位也有人，则查找6号位，6号位有人，则找3号，3号位有人，则找1号，最后找2号
        if (spVector[spaceVector[1]] != nullptr) {
            if (spVector[spaceVector[2]] != nullptr) {
                if (spVector[spaceVector[3]] != nullptr) {
                    if (spVector[spaceVector[4]] != nullptr) {
                        
                        if (spVector[spaceVector[5]] != nullptr) {
                            //走到这里说明，所有位已被人占领，近战将没有攻击位可用。
                            return -1;
                            
                        }else{
                            return spaceVector[5];
                        }
                    }else{
                        return spaceVector[4];
                    }
                    
                }else{
                    return spaceVector[3];
                }
                
            }else{
                return spaceVector[2];
            }
        }else{
            return spaceVector[1];
        }
    }else{
        return spaceVector[0];
    }
    
}

//得到某个角度上的长度为l的矢量
cocos2d::Vec2 PointUtil::getVec2With(float lenth,float jiaodu)
{
    //得到6个位置的精灵位
    Point oPo = Vec2(1,0);
    Point tmpx = oPo.rotateByAngle(Vec2(0,0), 2*3.1415926*jiaodu/360);
    tmpx.scale(lenth);
    return tmpx;
}
cocos2d::Vec2 PointUtil::Vec2WithAttackSpace(int n)
{
    //当前精灵的攻击位上是否有精灵，精灵近战攻击位编号如下
    /*
      1   6
     2  s  5
      3   4
     */
    switch (n) {
        case 1:
            return  PointUtil::getVec2With(1.0f, kAttackJiaoDu1);
            break;
        case 2:
            return  PointUtil::getVec2With(1.0f, kAttackJiaoDu2);
            break;
        case 3:
            return  PointUtil::getVec2With(1.0f, kAttackJiaoDu3);
            break;
        case 4:
            return  PointUtil::getVec2With(1.0f, kAttackJiaoDu4);
            break;
        case 5:
            return  PointUtil::getVec2With(1.0f, kAttackJiaoDu5);
            break;
        case 6:
            return  PointUtil::getVec2With(1.0f, kAttackJiaoDu6);
            break;
        default:
            return Vec2(0,0);
            break;
    }
}

//计算两个相向而行的目标移动坐标
void PointUtil::TwoSpriteMoveAttackTimeAndLenth(float &tA,float &lA,cocos2d::Point Pa,int Va,int attackRa, float &tB,float &lB,cocos2d::Point Pb,int Vb,int attackRb)
{
    if (attackRa >= attackRb) {
        cocos2d::Point ptmp = Pa;
        ptmp.subtract(Pb);
        float Ra = (float)attackRa;
        float Rb = (float)attackRb;
        float l = ptmp.length();
        float t1 = (l - Ra)/(Va + Vb);
        float t2 = (Ra - Rb)/Vb;
        tA = t1;
        tB = t1+t2;
        lA = tA*Va;
        lB = tB*Vb;
    }else{
        cocos2d::Point ptmp = Pa;
        ptmp.subtract(Pb);
        float Ra = (float)attackRa;
        float Rb = (float)attackRb;
        float l = ptmp.length();
        float t1 = (l - Ra)/(Vb + Va);
        float t2 = (Rb-Ra)/Va;
        tA = t1;
        tB = t1+t2;
        lA = tA*Va;
        lB = tB*Vb;
    }
}
