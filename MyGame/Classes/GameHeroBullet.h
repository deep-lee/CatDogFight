//
//  GameHeroBullet.h
//  MyGame
//
//  Created by 李冬 on 15/3/13.
//
//

#ifndef __MyGame__GameHeroBullet__
#define __MyGame__GameHeroBullet__

#include "cocos2d.h"

using namespace cocos2d;
USING_NS_CC;

class GameHeroBullet : public cocos2d::CCNode
{
public:
    bool isVisible;
    GameHeroBullet();
    virtual ~GameHeroBullet(void);
    void setIsVisible();
    void setIsNotVisible(CCObject *pSender);
    bool getIsVisible();
    virtual void onEnter();
    virtual void onExit();
};

#endif /* defined(__MyGame__GameHeroBullet__) */
