//
//  GameObjEnemy.cpp
//  MyGame
//
//  Created by 李冬 on 15/3/13.
//
//

#include "GameObjEnemy.h"


void GameObjEnemy::setDie()
{
    isLife = false;
    mainBody->setVisible(false);
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
    
    boom->runAction(CCSequence::create(CCAnimate::create(animation), CCCallFuncN::create(this, callfuncN_selector(GameObjEnemy::restart))));
}

void GameObjEnemy::setOutScreen()
{
    isLife = false;
    mainBody->setVisible(false);
    this->stopAllActions();
    
    this->restart(this);
}

GameObjEnemy::GameObjEnemy()
{
    
}
GameObjEnemy::~GameObjEnemy(void)
{
    
}
void GameObjEnemy::releaseBullet(float f)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPoint pos = this->getPosition();
    
    if (pos.y > 20 && pos.y < size.height && isLife) {
        GameMain *p = (GameMain *)this->getParent();
        // 在下方30处显示子弹
        p->releaseEnemyBullet(pos.x, pos.y - 30);
    }
}
void GameObjEnemy::moveStart()
{
    isLife = true;
    int type = CCRANDOM_0_1() * 3;
    // 贝塞尔曲线运动
    ccBezierConfig bezier2;
    bezier2.controlPoint_1 = CCPointMake(this->getPositionX() - 400, 330);
    bezier2.controlPoint_2 = CCPointMake(this->getPositionX() + 400, 280);
    bezier2.endPosition = CCPointMake(this->getPositionX(), -70);
    
    CCBezierTo *bezierTo2 = CCBezierTo::create(6, bezier2);
    
    ccBezierConfig bezier1;
    bezier1.controlPoint_1 = CCPointMake(this->getPositionX() + 400, 330);
    bezier1.controlPoint_2 = CCPointMake(this->getPositionX() - 400, 280);
    bezier1.endPosition = CCPointMake(this->getPositionX(), -70);
    CCBezierTo *bezierTo1 = CCBezierTo::create(6, bezier1);
    
    switch (type) {
        case 0:
            this->runAction(CCSequence::create(CCMoveBy::create(6, ccp(0, -600)), CCCallFuncN::create(this, callfuncN_selector(GameObjEnemy::restart)), NULL));
            break;
        case 1:
            this->runAction(CCSequence::create(bezierTo2, CCCallFuncN::create(this, callfuncN_selector(GameObjEnemy::restart)), NULL));
            break;
        case 2:
            this->runAction(CCSequence::create(bezierTo1, CCCallFuncN::create(this, callfuncN_selector(GameObjEnemy::restart)), NULL));
            break;
        default:
            break;
    }
    
    // 定时器，每隔0.5秒释放子弹
    schedule(schedule_selector(GameObjEnemy::releaseBullet), 0.5f, kCCRepeatForever, 0);
    
}
void GameObjEnemy::restart(CCObject *pSender)
{
    mainBody->setVisible(true);
    boom->setVisible(false);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    this->setPosition(ccp(size.width / 4 * type, size.height + 50));
    
    isLife = true;
    mainBody->setVisible(true);
    boom->setVisible(false);
    
    this->moveStart();
}
void GameObjEnemy::setType(short var)
{
    type = var;
}

void GameObjEnemy::onEnter()
{
    CCNode::onEnter();
    this->setContentSize(CCSizeMake(99, 111));
    mainBody = CCSprite::create("DrDog1.png");
    
    // 创建动画
    CCAnimation *animation = CCAnimation::create();
    animation->addSpriteFrameWithFileName("DrDog1.png");
    animation->addSpriteFrameWithFileName("DrDog2.png");
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(true);
    mainBody->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
    addChild(mainBody);
    
    boom = CCSprite::create("boom1.png");
    boom->setVisible(false);
    addChild(boom);
    
    isLife = true;
}
void GameObjEnemy::onExit()
{
    CCNode::onExit();
}
