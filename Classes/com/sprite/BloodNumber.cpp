//
//  BloodNumber.cpp
//  game1
//
//  Created by 俊盟科技1 on 8/20/14.
//
//

#include "BloodNumber.h"

#define kNumberImage0 "number0.png"
#define kNumberImage1 "number1.png"
#define kNumberImage2 "number2.png"
#define kNumberImage3 "number3.png"
#define kNumberImage4 "number4.png"
#define kNumberImage5 "number5.png"
#define kNumberImage6 "number6.png"
#define kNumberImage7 "number7.png"
#define kNumberImage8 "number8.png"
#define kNumberImage9 "number9.png"
#define kNumberImage_ "number_.png"


bool BloodNumber::init()
{
	bool bRet = false;
	do
	{
		CCSprite::init();
		currIndex=-1;
		bRet = true;
	} while (0);
    
	return bRet;
}
void BloodNumber::setData(int index)
{
	if(currIndex!=index)
	{
		currIndex=index;
		this->removeAllChildrenWithCleanup(true);
		int c=0;
		while(index>0)
		{
			int num=index%10;
			index=(index-num)/10;
			c++;
		}
		index=currIndex;
		int maxX=(c-1)*10;
		for(int i=0;i<c;i++)
		{
			int num=index%10;
			index=(index-num)/10;
			string url=getSprite(num);
			Sprite* sp=CCSprite::createWithSpriteFrameName(url.c_str());
			sp->setPosition(Vec2(maxX,0));
			this->addChild(sp);
			maxX-=20;
		}
	}
}
string BloodNumber::getSprite(int i)
{
	string str;
	switch(i)
	{
        case 0:
            str=kNumberImage0;
            break;
        case 1:
            str=kNumberImage1;
            break;
        case 2:
            str=kNumberImage2;
            break;
        case 3:
            str=kNumberImage3;
            break;
        case 4:
            str=kNumberImage4;
            break;
        case 5:
            str=kNumberImage5;
            break;
        case 6:
            str=kNumberImage6;
            break;
        case 7:
            str=kNumberImage7;
            break;
        case 8:
            str=kNumberImage8;
            break;
        case 9:
            str=kNumberImage9;
            break;
        case 10:
            str=kNumberImage_;
            break;
	}
	return str;
}
void BloodNumber::onEnter()
{
	CCSprite::onEnter();
}
void BloodNumber::onExit()
{
	CCSprite::onExit();
}
