//
//  OnlyMarkingManger.cpp
//  game1
//
//  Created by 俊盟科技1 on 8/22/14.
//
//

#include "OnlyMarking.h"

static unsigned long long s_getcount = 0;

std::string OnlyMarking::getNewMarking()
{
    s_getcount++;
    std::string tmp = std::to_string(s_getcount);
    return tmp;
}

