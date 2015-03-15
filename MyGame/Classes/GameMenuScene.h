//
//  GameMenuScene.h
//  MyGame
//
//  Created by 李冬 on 15/3/13.
//
//

#ifndef __MyGame__GameMenuScene__
#define __MyGame__GameMenuScene__

#include "cocos2d.h"
#include "GameScene.h"

using namespace cocos2d;
USING_NS_CC;

class GameMenu : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameMenu);
    
    bool isSound;
    CCMenuItemImage *soundItem;
    
    virtual void onEnter();
    virtual void onExit();
    void menuEnter(CCObject *pSender);
    void menuNewGameCallback(CCObject *pSender);
    void menuContinueCallback(CCObject *pSender);
    void menuAboutCallback(CCObject *pSender);
    void menuSoundCallback(CCObject *pSender);

};


#endif /* defined(__MyGame__GameMenuScene__) */
