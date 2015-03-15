//
//  GameObjHero.h
//  MyGame
//
//  Created by 李冬 on 15/3/13.
//
//

#ifndef __MyGame__GameObjHero__
#define __MyGame__GameObjHero__

#include "cocos2d.h"


using namespace cocos2d;

class Gamemain;

class GameObjHero : public cocos2d::CCNode, public CCTargetedTouchDelegate
{
public:
    
    CCSprite *leftHand;
    CCSprite *rightHand;
    CCPoint offset;
    bool isControl;
    
    // 爆炸
    CCSprite * boom;
    
    // 尾巴
    CCSprite *tail;
    
    CCSprite *mainBody;
    
    void setHeroDie();
    
    void removeBoom();
    
    GameObjHero();
    virtual ~GameObjHero();
    void releaseBullet(float f);
    CCRect rect();
    bool containsTouchLocation(CCTouch *touch);
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);
    
    virtual void touchDelegateretain();
    virtual void touchDelegaterelease();
    
    virtual void onEnter();
    virtual void onExit();
};

#endif /* defined(__MyGame__GameObjHero__) */
