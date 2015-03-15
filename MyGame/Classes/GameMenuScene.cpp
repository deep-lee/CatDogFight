#include "GameMenuScene.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameMenu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameMenu *layer = GameMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize size = CCDirector::sharedDirector()->getWinSize();
  
    // 初始化背景
    CCSprite *bg = CCSprite::create("bg.png");
    bg->setPosition(ccp(size.width / 2, size.height / 2));
    // 第三个参数是tag
    addChild(bg, 0, 0);
    
    // 初始化月亮背景
    CCSprite *moon = CCSprite::create("moon.png");
    moon->setAnchorPoint(ccp(0.5, 0));
    moon->setPosition(ccp(size.width / 3 * 2, 0));
    addChild(moon, 1, 1);
    
    // 标题
//    CCNode *title = CCNode::create();
//    title->setContentSize(CCSizeMake(size.width - 40, 50));
    CCSprite * ptmlabel = CCSprite::create("meowstar.png");
    ptmlabel->setPosition(ccp(size.width / 2, size.height -100));
    this->addChild(ptmlabel, 2, 20);
//    title->addChild(ptmlabel);
    
    CCSprite *ptbLabel = CCSprite::create("battle.png");
    ptbLabel->setPosition(ccp(size.width / 2, size.height - 200));
    this->addChild(ptbLabel, 2, 21);
//    title->addChild(ptbLabel);
    
//    title->setPosition(ccp(size.width / 2, size.height - 80));
//    addChild(title, 2, 2);
    
    // 初始化按钮
    CCMenuItemImage *newGameBtn = CCMenuItemImage::create("newgameA.png", "newgameB.png", this, menu_selector(GameMenu::menuNewGameCallback));
    newGameBtn->setPosition(ccp(size.width / 2, size.height / 2 + 20));
    newGameBtn->setEnabled(false);
    
    CCMenuItemImage *continueBtn = CCMenuItemImage::create("continueA.png", "continueB.png", this, menu_selector(GameMenu::menuContinueCallback));
    continueBtn->setPosition(ccp(size.width / 2, size.height / 2 - 80));
    continueBtn->setEnabled(false);
    
    CCMenuItemImage *aboutBtn = CCMenuItemImage::create("aboutA.png", "aboutB.png", this, menu_selector(GameMenu::menuAboutCallback));
    aboutBtn->setPosition(ccp(size.width / 2, size.height / 2 - 180));
    aboutBtn->setEnabled(false);
    
    soundItem = CCMenuItemImage::create("sound-on-A.png", "sound-on-B.png", this, menu_selector(GameMenu::menuSoundCallback));
    soundItem->setPosition(ccp(40, 40));
    soundItem->cocos2d::CCMenuItem::setEnabled(false);
    
    CCMenu * mainMenu = CCMenu::create(newGameBtn, continueBtn, aboutBtn, soundItem, NULL);
    mainMenu->setPosition(ccp(0, 0));
    addChild(mainMenu, 1, 3);
    
    // 播放音效
    isSound = true;
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("background.mp3");
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3", true);
    
    
    
    return true;
}

void GameMenu::onEnter()
{
    CCLayer::onEnter();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // 菜单进入
    CCNode * mainMenu = this->getChildByTag(3);
    mainMenu->setPositionX(-200);
    mainMenu->runAction(CCSequence::create(CCEaseElasticIn::create(CCMoveTo::create(0.5, ccp(0, 0))), CCCallFuncN::create(this, callfuncN_selector(GameMenu::menuEnter))));
    
//    CCNode *title = this->getChildByTag(2);
//    title->setPositionY(size.height + 20);
//    title->runAction(CCEaseElasticIn::create(CCMoveBy::create(0.5, ccp(0, -100))));
    
    CCSprite *ptmLabel = (CCSprite *)this->getChildByTag(20);
    ptmLabel->setPositionY(size.height + 40);
    ptmLabel->runAction(CCEaseElasticIn::create(CCMoveTo::create(0.5, ccp(size.width / 2, size.height -100))));
    
    CCSprite *ptbLabel = (CCSprite *)this->getChildByTag(21);
    ptbLabel->setPositionY(size.height + 20);
    ptbLabel->runAction(CCEaseElasticIn::create(CCMoveTo::create(0.5, ccp(size.width / 2, size.height -200))));
    
    CCNode *bgStar = this->getChildByTag(1);
    bgStar->setPositionY(size.width / 3);
    bgStar->runAction(CCMoveTo::create(0.5, ccp(size.width / 3 * 2, 0)));
    
}

void GameMenu::onExit()
{
    CCLayer::onExit();
}

void GameMenu::menuEnter(CCObject *pSender)
{
    //菜单进入后，菜单项点击有效
    CCNode *mainMenu = this->getChildByTag(3);
    CCArray *menuItem = mainMenu->getChildren();
    for (int i = 0; i < menuItem->count(); i++) {
        ((CCMenuItem *)menuItem->objectAtIndex(i))->setEnabled(true);
    }
}
void GameMenu::menuNewGameCallback(CCObject *pSender)
{
    CCDirector::sharedDirector()->replaceScene(GameMain::scene());
}
void GameMenu::menuContinueCallback(CCObject *pSender)
{
    
}
void GameMenu::menuAboutCallback(CCObject *pSender)
{
    
}
void GameMenu::menuSoundCallback(CCObject *pSender)
{
    // 此时没有播放音乐
    if (!isSound) {
        soundItem->setNormalImage(CCSprite::create("sound-on-A.png"));
        soundItem->setSelectedImage(CCSprite::create("sound-on-B.png"));
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3", true);
        isSound = true;
    }
    else
    {
        soundItem->setNormalImage(CCSprite::create("sound-off-A.png"));
        soundItem->setSelectedImage(CCSprite::create("sound-off-B.png"));
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        isSound = false;
    }
}

void GameMenu::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}