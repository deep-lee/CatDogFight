//
//  GameEnemyBullet.cpp
//  MyGame
//
//  Created by 李冬 on 15/3/13.
//
//

#include "GameEnemyBullet.h"

GameEnemyBullet::GameEnemyBullet()
{
    isVisible = false;
}
GameEnemyBullet:: ~GameEnemyBullet(void)
{
    
}
void GameEnemyBullet::setIsVisible()
{
    this->setVisible(true);
    isVisible = true;
    this->runAction(CCRepeatForever::create(CCRotateBy::create(1, 360)));
    this->runAction(CCSequence::create(CCMoveTo::create((this->getPositionY() + 50) / 150, ccp(this->getPositionX(), -50)), CCCallFuncN::create(this, callfuncN_selector(GameEnemyBullet::setIsNotVisible)), NULL));
    
    
}
void GameEnemyBullet::setIsNotVisible(CCObject *pSender)
{
    this->setVisible(false);
    isVisible = false;
    this->stopAllActions();
}
bool GameEnemyBullet::getIsVisible()
{
    return isVisible;
}
void GameEnemyBullet::onEnter()
{
    CCNode::onEnter();
    this->setContentSize(CCSizeMake(21, 52));
    CCSprite *mainBody = CCSprite::create("DrDogZD.png");
    mainBody->runAction(CCRepeatForever::create(CCRotateBy::create(1, 360)));
    
    addChild(mainBody);
}
void GameEnemyBullet::onExit()
{
    CCNode::onExit();
}