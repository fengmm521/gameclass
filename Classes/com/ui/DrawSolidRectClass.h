#ifndef __DRAWSOLIDRECTCLASS_H__
#define __DRAWSOLIDRECTCLASS_H__

#include "cocos2d.h"


class DrawSolidRectClass : public cocos2d::Sprite
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	static DrawSolidRectClass* creatSolidRectWithPoint(cocos2d::Point leftDownPoint,cocos2d::Point RightUpPoint,cocos2d::Color4F color4f);


	//重载draw方法
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    void onDraw(const cocos2d::Mat4 &transform, bool transformUpdated);
    cocos2d::CustomCommand _customCommand;
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    // implement the "static node()" method manually
    CREATE_FUNC(DrawSolidRectClass);

	void setColor(cocos2d::Color4F color4f);
		

private:
	void initDrawData(cocos2d::Point leftDownPoint,cocos2d::Point RightUpPoint,cocos2d::Color4F color4f);
	cocos2d::Point sLeftDownPoint;
	cocos2d::Point sRightUpPoint;
	cocos2d::Color4F sColor4f;


};

#endif  // __HELLOWORLD_SCENE_H__