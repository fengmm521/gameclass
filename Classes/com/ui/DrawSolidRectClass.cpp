#include "DrawSolidRectClass.h"

using namespace cocos2d;

DrawSolidRectClass* DrawSolidRectClass::creatSolidRectWithPoint(cocos2d::Point leftDownPoint,cocos2d::Point RightUpPoint,Color4F color4f)
{
	DrawSolidRectClass* tmp = new DrawSolidRectClass;
	tmp->autorelease();
	tmp->initDrawData(leftDownPoint,RightUpPoint,color4f);
	//CCLog("4f(%f,%f,%f,%f)",color4f.r,color4f.g,color4f.b,color4f.a);
	return tmp;
}
void DrawSolidRectClass::initDrawData(cocos2d::Point leftDownPoint,cocos2d::Point RightUpPoint,Color4F color4f)
{
	
	sLeftDownPoint = leftDownPoint;
	sRightUpPoint = RightUpPoint;
	sColor4f = color4f;
	//CCLog("xx,point(%f,%f),4f(%f,%f,%f,%f)",sRightUpPoint.x,sRightUpPoint.y,sColor4f.r,sColor4f.g,sColor4f.b,sColor4f.a);
	this->init();
}
// on "init" you need to initialize your instance
bool DrawSolidRectClass::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! Sprite::init());
		this->setPosition(Vec2(0.0f,0.0f));
		this->setAnchorPoint(Vec2(0.0f,0.0f));

        bRet = true;
    } while (0);

    return bRet;
}

void DrawSolidRectClass::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(DrawSolidRectClass::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void DrawSolidRectClass::onDraw(const cocos2d::Mat4 &transform, bool transformUpdated)
{
    //利用Stack缓存
    Director *director = Director::getInstance();
    //CCASSERT(nullptr != director, "Director is null when setting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    
    CHECK_GL_ERROR_DEBUG();
    
    DrawPrimitives::setPointSize(8);
    DrawPrimitives::drawSolidRect(sLeftDownPoint, sRightUpPoint, sColor4f);
    
    CHECK_GL_ERROR_DEBUG();
    
    //绘制停止，释放
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
}

void DrawSolidRectClass::setColor(cocos2d::Color4F color4f)
{
	sColor4f = color4f;
}
