//
//  GameObjEnemy.h
//  MyGame
//
//  Created by 李冬 on 15/3/13.
//
//

#ifndef __MyGame__GameObjEnemy__
#define __MyGame__GameObjEnemy__

#include "cocos2d.h"
#include "GameScene.h"

using namespace cocos2d;
USING_NS_CC;

class GameObjEnemy : public cocos2d::CCNode
{
public:

    // 敌人的身体和爆炸
    CCSprite *mainBody;
    CCSprite *boom;
    
    // 是否还活着
    bool isLife;
    
    void setDie();
    
    // 超出屏幕
    void setOutScreen();
    
    GameObjEnemy();
    virtual ~GameObjEnemy(void);
    void releaseBullet(float f);
    void moveStart();
    void restart(CCObject *pSender);
    short type;
    void setType(short var);
    
    virtual void onEnter();
    virtual void onExit();
};


#endif /* defined(__MyGame__GameObjEnemy__) */
