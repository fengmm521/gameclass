//
//  TimeUtil.cpp
//  game2
//
//  Created by 俊盟科技1 on 9/11/14.
//
//

#include "TimeUtil.h"



string TimeUtil::secendToString_M_S(int secend)
{
    
    int m = (int)floor(secend/60);
    int s = secend%60;
//    int h = (int)floor(m/60);
//    int d = (int)floor(h/24);
    m = m%60;
    string dstr = "";
    string hstr = "";
    string mstr = "";
    string sstr = "";
    
    string tmp;

    if (m >9) {
        tmp = to_string(m) + ":" + to_string(s);
    }else{
        tmp = "0" + to_string(m) + ":" + to_string(s);
    }

    //cocos2d::log("show time mm:ss---->%s",tmp.c_str());
    return tmp;
}
string TimeUtil::secendToString_H_M_S(int secend)
{
    // 显示时分秒形如：2:32:12
    string tmp = "";
    return tmp;
}
string TimeUtil::secendToString_D_H_M_S(int secend)
{
    // 显示天时分秒形如：2天5时32分12秒
    string tmp = "";
    return tmp;
}