//
//  GameEnemyBullet.h
//  MyGame
//
//  Created by 李冬 on 15/3/13.
//
//

#ifndef __MyGame__GameEnemyBullet__
#define __MyGame__GameEnemyBullet__

#include "cocos2d.h"

using namespace cocos2d;
USING_NS_CC;

class GameEnemyBullet : public cocos2d::CCNode
{
public:
    bool isVisible;
    GameEnemyBullet();
    virtual ~GameEnemyBullet(void);
    void setIsVisible();
    void setIsNotVisible(CCObject *pSender);
    bool getIsVisible();
    virtual void onEnter();
    virtual void onExit();
};

#endif /* defined(__MyGame__GameEnemyBullet__) */
