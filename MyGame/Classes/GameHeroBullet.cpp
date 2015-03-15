//
//  GameHeroBullet.cpp
//  MyGame
//
//  Created by 李冬 on 15/3/13.
//
//

#include "GameHeroBullet.h"

GameHeroBullet::GameHeroBullet()
{
    isVisible = false;
}
GameHeroBullet:: ~GameHeroBullet(void)
{
    
}
void GameHeroBullet::setIsVisible()
{
    this->setVisible(true);
    isVisible = true;
    this->runAction(CCSequence::create(CCMoveTo::create((960 - this->getPositionY()) / 200, ccp(this->getPositionX(), 960)), CCCallFuncN::create(this, callfuncN_selector(GameHeroBullet::setIsNotVisible)), NULL));
    
    
}
void GameHeroBullet::setIsNotVisible(CCObject *pSender)
{
    this->setVisible(false);
    isVisible = false;
    this->stopAllActions();
}
bool GameHeroBullet::getIsVisible()
{
    return isVisible;
}
void GameHeroBullet::onEnter()
{
    CCNode::onEnter();
    this->setContentSize(CCSizeMake(21, 52));
    CCSprite *mainBody = CCSprite::create("YuGuZD.png");
    
    addChild(mainBody);
}
void GameHeroBullet::onExit()
{
    CCNode::onExit();
}
