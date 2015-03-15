//
//  GameObjHero.cpp
//  MyGame
//
//  Created by 李冬 on 15/3/13.
//
//

#include "GameObjHero.h"
#include "GameScene.h"

GameObjHero::GameObjHero()
{
    
}
GameObjHero::~GameObjHero()
{
    
}
void GameObjHero::releaseBullet(float f)
{
    if (isControl) {
        CCPoint pos = this->getPosition();
        GameMain *p = (GameMain *)this->getParent();
        p->releaseHeroBullet(pos.x, pos.y + 30);
    }
}

void GameObjHero::setHeroDie()
{
    isControl = false;
    mainBody->setVisible(false);
    tail->setVisible(false);
    leftHand->setVisible(false);
    rightHand->setVisible(false);
    boom->setVisible(true);
    
    this->stopAllActions();
    
    CCAnimation *animation = CCAnimation::create();
    animation->addSpriteFrameWithFileName("boom1.png");
    animation->addSpriteFrameWithFileName("boom2.png");
    animation->addSpriteFrameWithFileName("boom3.png");
    animation->addSpriteFrameWithFileName("boom4.png");
    animation->addSpriteFrameWithFileName("boom5.png");
    
    animation->setRestoreOriginalFrame(true);
    animation->setDelayPerUnit(0.1f);
    
    boom->runAction(CCSequence::create(CCAnimate::create(animation), CCCallFuncN::create(this, callfuncN_selector(GameObjHero::removeBoom))));
}

void GameObjHero::removeBoom()
{
    boom->setVisible(false);
}

CCRect GameObjHero::rect()
{
    CCSize s = CCSizeMake(85, 90);
    return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}
bool GameObjHero::containsTouchLocation(CCTouch *touch)
{
    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}
bool GameObjHero::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
    // 游戏是否结束
    if (((GameMain *)(this->getParent()))->isOver) {
        return false;
    }
    // 触摸点是否在精灵上
    else if(!containsTouchLocation(touch))
    {
        return false;
    }
    else
    {
        // 获取触摸偏移位置
        isControl = true;
        
        CCPoint touchPoint = touch->getLocationInView();
        touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
        offset.x = touchPoint.x - this->getPositionX();
        offset.y = touchPoint.y - this->getPositionY();
        
    }
    
    return true;
}
void GameObjHero::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
    if(isControl)
    {
        CCPoint touchPoint = touch->getLocationInView();
        touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
        // 设置左右手上下
        float x = touchPoint.x - offset.x;
        float y = touchPoint.y - offset.y;
        if (x < this->getPositionX()) {
            leftHand->setFlipY(true);
            rightHand->setFlipY(false);
        }
        else
        {
            leftHand->setFlipY(false);
            rightHand->setFlipY(true);
        }
        
        this->setPosition(x, y);
    }
}
void GameObjHero::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
    if (isControl) {
        isControl = false;
        leftHand->setFlipY(false);
        rightHand->setFlipY(false);
    }
}

void GameObjHero::touchDelegateretain()
{
    this->retain();
}
void GameObjHero::touchDelegaterelease()
{
    this->release();
}

void GameObjHero::onEnter()
{
    CCNode::onEnter();
    this->setContentSize(CCSizeMake(85, 90));
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    mainBody = CCSprite::create("catBody1.png");
    // 主体动画
    CCAnimation *animation = CCAnimation::create();
    animation->addSpriteFrameWithFileName("catBody1.png");
    animation->addSpriteFrameWithFileName("catBody2-4.png");
    animation->addSpriteFrameWithFileName("catBody3.png");
    animation->addSpriteFrameWithFileName("catBody2-4.png");
    
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(true);
    mainBody->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
    this->addChild(mainBody);
    
    // 尾巴
    tail = CCSprite::create("catTail.png");
    tail->setAnchorPoint(CCPoint(0.5, 1));
    tail->setPosition(ccp(-5, -29));
    tail->setScale(0.5);
    tail->setRotation(20);
    tail->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(CCRotateBy::create(0.5,-40),CCRotateBy::create(0.5,40),NULL)));
    addChild(tail);
    
    // 两只手
    leftHand = CCSprite::create("catHand1.png");
    leftHand->setAnchorPoint(ccp(1, 0.5));
    leftHand->setPosition(ccp(-18, -20));
    addChild(leftHand);
    
    rightHand = CCSprite::create("catHand2.png");
    rightHand->cocos2d::CCNode::setAnchorPoint(ccp(0, 0.5));
    rightHand->setPosition(ccp(18, -20));
    addChild(rightHand);
    
    boom = CCSprite::create("boom1.png");
    boom->setVisible(false);
    addChild(boom);
    
    // 偏移量
    offset = ccp(0, 0);
    isControl = false;
    
    // 每隔一秒释放子弹
    schedule(schedule_selector(GameObjHero::releaseBullet), 0.8f);
    
    
}
void GameObjHero::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}