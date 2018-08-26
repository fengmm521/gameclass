//
//  BloodBar.cpp
//  game1
//
//  Created by 俊盟科技1 on 8/20/14.
//
//

#include "BloodBar.h"
BloodBar* BloodBar::createBarRed(int maxValue,BaseSprite* target)
{
    BloodBar* tmp = new BloodBar();
    tmp->autorelease();
    tmp->s_isGree = false;
    tmp->m_maxBlood = maxValue;
    tmp->s_targetSp = target;
    tmp->init();
    return tmp;
}
BloodBar* BloodBar::createBarGree(int maxValue,BaseSprite* target)
{
    BloodBar* tmp = new BloodBar();
    tmp->autorelease();
    tmp->s_isGree = true;
    tmp->m_maxBlood = maxValue;
    tmp->s_targetSp = target;
    tmp->init();
    return tmp;
    
}
bool BloodBar::init()
{
    //////////////////////////////
    // 1. super init first
    if (!cocos2d::Sprite::init()) {
        return false;
    }
    
    
    bool bRet = false;
    do
    {
        m_blood = m_maxBlood;
        m_realBlood = m_maxBlood;
        
        bgSprite = Sprite::create("bar/bloodbarbg.png");
        addChild(bgSprite, 0, 0);
        
        std::string imageColor;
        if (s_isGree) {
            imageColor = "bar/ourbloodbar.png";
        }else{
            imageColor = "bar/enemybloodbar.png";
        }
        
        hpSprite = Sprite::create(imageColor);
        
        progressTimer = ProgressTimer::create(hpSprite);
        
        progressTimer->setType(ProgressTimer::Type::BAR);
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////
        //从左到右
        //progressTimer->setMidpoint(Vec2(0, 0.5));
        //progressTimer->setBarChangeRate(Vec2(1, 0));
        
        //从右到左
        //    progressTimer->setMidpoint(ccp(1, 0.5));
        //    progressTimer->setBarChangeRate(ccp(1, 0));
        
        //从上到下
        //    progressTimer->setMidpoint(ccp(0.5, 1));
        //    progressTimer->setBarChangeRate(ccp(0, 1));
        
        //从下到上
        //    progressTimer->setMidpoint(ccp(0.5, 0));
        //    progressTimer->setBarChangeRate(ccp(0, 1));
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        progressTimer->setMidpoint(Point(0, 0.5));
        progressTimer->setBarChangeRate(Point(1, 0));
        
        progressTimer->setPercentage(100);//满值 100%
        
        addChild(progressTimer, 0, 0);
        
        m_barPercent = 1.0f;
        this->setVisible(false);
        
        
        s_bloodSlider = nullptr;
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}
void BloodBar::setBloodSlider(ui::LoadingBar* slider)
{
    s_bloodSlider = slider;
}

//被攻击掉血
void BloodBar::attackBloodSub(int subValue,bool isBaoJi)
{
    m_blood -= subValue;
    m_barPercent = (float)m_blood/(float)m_maxBlood;
    int percent = (int)(m_barPercent*100);
    if (s_bloodSlider) {
        s_bloodSlider->setPercent(percent);
    }
    progressTimer->setPercentage(percent);
    this->stopAllActions();
    this->setVisible(true);
    progressTimer->setVisible(true);
    bgSprite->setVisible(true);
    
    if (m_blood <= 0) {
        m_blood = 0;
        this->bloodDie(); //角色死亡
    }else{
        CallFunc* func = CallFunc::create([=]()->void{
            this->setVisible(false);
        });
        this->runAction(Sequence::create(DelayTime::create(3.0f),func, NULL));
    }
    

    if (isBaoJi) {
        Label* bloodText = Label::createWithBMFont("ui/WarUI/baojiFont.fnt", to_string(subValue));
        
        //判断数字的是几位数,用来调整飘字坐标
        int i = 0;
        while (subValue != 0) {
            subValue /= 10;
            i++;
        }
        
        Sprite* labelx = Sprite::create("ui/WarUI/warbaoji.png");
        labelx->setPosition(Vec2((-10-13*i),35));
        bloodText->setAnchorPoint(Vec2(0,0));
        bloodText->setPosition(Vec2(100,2));
        labelx->addChild(bloodText);
        this->addChild(labelx);
        
        MoveBy* moveby = MoveBy::create(0.5f, Vec2(0,100));
        CallFuncN* funcn = CallFuncN::create([this](Node *sender)->void{
            sender->removeFromParent();
        });
        labelx->runAction(Sequence::create(moveby,funcn, NULL));
    } else {
        Label* bloodText = Label::createWithBMFont("ui/WarUI/bloodFont.fnt", to_string(subValue));
        bloodText->setPosition(Vec2(0,35));
        this->addChild(bloodText);
        
        MoveBy* moveby = MoveBy::create(0.5f, Vec2(0,100));
        CallFuncN* funcn = CallFuncN::create([this](Node *sender)->void{
            sender->removeFromParent();
        });
        bloodText->runAction(Sequence::create(moveby,funcn, NULL));
    }
}
//攻击被闪避
void BloodBar::attackFinding()
{
    if (!isVisible()) {
        progressTimer->setVisible(false);
        bgSprite->setVisible(false);
        this->setVisible(true);
    }
    Sprite* labelx = Sprite::create("ui/WarUI/warshanbi.png");
//    Label* lablex = Label::createWithSystemFont("闪避","Arial",30);
//    lablex->setColor(Color3B(30,250,10));
    labelx->setPosition(Vec2(0,35));
    this->addChild(labelx);
    
    MoveBy* moveby = MoveBy::create(0.5f, Vec2(0,50));
    CallFuncN* funcn = CallFuncN::create([this](Node *sender)->void{
        sender->removeFromParent();
        
    });
    
    CallFunc* func = CallFunc::create([=]()->void{
        this->setVisible(false);
        progressTimer->setVisible(true);
        bgSprite->setVisible(true);
    });
    
    labelx->runAction(Sequence::create(moveby,funcn, NULL));
    
    this->runAction(Sequence::create(DelayTime::create(3.0f),func, NULL));
}
//加血
void BloodBar::addBloodValue(int addValue)
{
    m_blood += addValue;
    if (m_blood > m_maxBlood){
        m_blood = m_maxBlood;
    }
    m_barPercent = (float)m_blood/(float)m_maxBlood;
    int percent = (int)(m_barPercent*100);
    if (s_bloodSlider) {
        s_bloodSlider->setPercent(percent);
    }
    progressTimer->setPercentage(percent);
    this->stopAllActions();
    this->setVisible(true);
    progressTimer->setVisible(true);
    bgSprite->setVisible(true);
    
    Label* bloodText = Label::createWithBMFont("ui/WarUI/lifeFont.fnt", to_string(addValue));
    bloodText->setPosition(Vec2(0,35));

    this->addChild(bloodText);
    
    MoveBy* moveby = MoveBy::create(0.5f, Vec2(0,100));
    CallFuncN* funcn = CallFuncN::create([this](Node *sender)->void{
        sender->removeFromParent();
    });
    
    CallFunc* func = CallFunc::create([=]()->void{
        this->setVisible(false);
    });
    
    bloodText->runAction(Sequence::create(moveby,funcn, NULL));
    
    this->runAction(Sequence::create(DelayTime::create(3.0f),func, NULL));
}
void BloodBar::bloodDie()//血条空血角色死亡
{
    this->cleanBloodWhenDie();
    s_targetSp->warBloodEmpty();//通知精灵已经空血
}
void BloodBar::cleanBloodWhenDie()
{
    if (s_bloodSlider) {
        s_bloodSlider->setPercent(0);
    }
}


