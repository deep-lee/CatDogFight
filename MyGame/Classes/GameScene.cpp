//
//  GameScene.cpp
//  MyGame
//
//  Created by 李冬 on 15/3/14.
//
//

#include "GameScene.h"
#include "GameMenuScene.h"
#include "GameEnemyBullet.h"
#include "GameHeroBullet.h"
#include "GameObjHero.h"

using namespace cocos2d;

CCScene* GameMain::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameMain *layer = GameMain::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void GameMain::releaseEnemyBullet(int x, int y)
{
    // 遍历子弹数组，不在使用的子弹释放
    for (int i = 0; i < enemyBulltes->capacity(); i++) {
        if (!((GameEnemyBullet *)(enemyBulltes->objectAtIndex(i)))->getIsVisible()) {
            // 设置位置，并设置为显示
            ((GameEnemyBullet *)(enemyBulltes->objectAtIndex(i)))->setPosition(ccp(x, y));
            ((GameEnemyBullet *)(enemyBulltes->objectAtIndex(i)))->setIsVisible();
            
            break;
        }
    }
}

void GameMain::releaseHeroBullet(int x, int y)
{
    // 遍历子弹数组，不在使用的子弹释放
    for (int i = 0; i < bulltes->capacity(); i++) {
        if (!((GameHeroBullet *)(bulltes->objectAtIndex(i)))->getIsVisible()) {
            // 设置位置，并设置为显示
            ((GameHeroBullet *)(bulltes->objectAtIndex(i)))->setPosition(ccp(x, y));
            ((GameHeroBullet *)(bulltes->objectAtIndex(i)))->setIsVisible();
            
            break;
        }
    }
    
}

// on "init" you need to initialize your instance
bool GameMain::init()
{
    
    if (!CCLayer::init()) {
        return false;
    }
    
    // 初始化
    // 创建背景
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    bg1 = CCSprite::create("bg.png");
    bg2 = CCSprite::create("bg.png");

    bg1->setAnchorPoint(ccp(0, 0));
    bg2->setAnchorPoint(ccp(0, 0));
    
    bg1->setPosition(ccp(0, 0));
    bg2->setPosition(ccp(0, size.height));
    
    this->addChild(bg1, 0);
    this->addChild(bg2, 0);
    
    // 创建主角
    hero = new GameObjHero();
    hero->setPosition(ccp(size.width / 2, -50));
    hero->setScale(0.5);
    hero->runAction(CCMoveBy::create(0.5, ccp(0, 150)));
    this->addChild(hero, 2, 1);
    
    // 创建敌人
    enemies = CCArray::createWithCapacity(4);
    for (int i = 0; i < 4; i++) {
        int type = i + 1;
        GameObjEnemy * enemy = new GameObjEnemy();
        enemy->setType(type);
        enemy->setPosition(ccp(size.width / 4 * type, size.height + 10));
        enemy->setScale(0.5);
        enemies->addObject(enemy);
        addChild(enemy, 1);
        enemy->moveStart();
    }
    enemies->retain();
    
    // 创建血量
    CCSpriteBatchNode *ui = CCSpriteBatchNode::create("cat.png");
    blood = 3;
    blood1 = CCSprite::createWithTexture(ui->getTexture());
    blood1->setPosition(ccp(20, size.height - 20));
    blood1->setScale(0.2);
    addChild(blood1);
    
    blood2 = CCSprite::createWithTexture(ui->getTexture());
    blood2->setPosition(ccp(50, size.height - 20));
    blood2->setScale(0.2);
    addChild(blood2);
    
    blood3 = CCSprite::createWithTexture(ui->getTexture());
    blood3->setPosition(ccp(80, size.height - 20));
    blood3->setScale(0.2);
    addChild(blood3);
    
    addChild(ui, 4);
    
    // 初始化主角子弹
    bulltes = CCArray::createWithCapacity(8);
    for (int i = 0 ; i < bulltes->capacity(); i++) {
        GameHeroBullet *bullte = new GameHeroBullet();
        bullte->setIsNotVisible(bullte);
        bullte->setScale(0.5);
        bulltes->addObject(bullte);
        this->addChild(bullte, 3);
    }
    bulltes->retain();
    
    // 初始化敌人子弹
    enemyBulltes = CCArray::createWithCapacity(10);
    for (int i = 0; i < enemyBulltes->capacity(); i++) {
        GameEnemyBullet *bullte = new GameEnemyBullet();
        bullte->setIsNotVisible(bullte);
        bullte->setScale(0.5);
        enemyBulltes->addObject(bullte);
        this->addChild(bullte, 3);
    }
    enemyBulltes->retain();
    
    // 显示分数
    scoreLabel = CCLabelTTF::create("0", "微软雅黑", 30);
    scoreLabel->setPosition(ccp(size.width * 0.9, size.height - 20));
    this->addChild(scoreLabel, 1);
    
    // 游戏结束弹板以及按钮
    gameover = CCSprite::create("gameover.png");
    gameover->setAnchorPoint(ccp(0.5, 0.5));
    gameover->setPosition(ccp(size.width / 2, size.height / 2 + 150));
    // gameover->setScale(0.5);
    gameover->setVisible(false);
    this->addChild(gameover, 5);
    
    // 返回主菜单按钮
    CCMenuItemImage *backMenu = CCMenuItemImage::create("back.png", "back.png", this, menu_selector(GameMain::menuBackCall));
    backMenu->setPosition(ccp(size.width / 2, size.height / 2 - 150));
    backMenu->setScale(2);
    
    CCMenu * pMenu = CCMenu::create(backMenu, NULL);
    pMenu->setPosition(ccp(0, 0));
    addChild(pMenu , 5 , 25);
    pMenu->setVisible(false);
    pMenu->setEnabled(false);
    
    // 当前分数
    current = CCLabelBMFont::create("Your score", "bitmapFontTest.fnt");
    current->setPosition(ccp(size.width * 0.35, size.height / 2 + 50));
    current->setVisible(false);
    this->addChild(current, 5);
    
    currentScore = CCLabelBMFont::create("0", "bitmapFontTest.fnt");
    currentScore->setPosition(ccp(size.width * 0.75, size.height / 2 + 50));
    currentScore->setVisible(false);
    this->addChild(currentScore, 5);
    
    // 最好分数
    best = CCLabelBMFont::create("Best score", "bitmapFontTest.fnt");
    best->setPosition(ccp(size.width * 0.35, size.height / 2 - 50));
    best->setVisible(false);
    this->addChild(best, 5);
    
    bestScore = CCLabelBMFont::create("0", "bitmapFontTest.fnt");
    bestScore->setPosition(ccp(size.width * 0.75 , size.height / 2 - 50));
    bestScore->setVisible(false);
    this->addChild(bestScore, 5);
    
    
    isReduce = false;
    isOver = false;
    
    scheduleUpdate();
    
    return true;
}

void GameMain::menuBackCall(CCObject *pSender)
{
    CCDirector::sharedDirector()->replaceScene(GameMenu::scene());
}

bool GameMain::isCollision(CCPoint p1, CCPoint p2, int w1, int h1, int w2, int h2)
{
    if ((abs(p1.x - p2.x) < w1 + w2) && (abs(p1.y - p2.y) < h1 + h2) ) {
        return true;
    }
    return false;
}

void GameMain::setOver()
{
    // 设置游戏结束
    CCMenu *pMenu = (CCMenu *)this->getChildByTag(25);
    pMenu->setVisible(true);
    pMenu->setEnabled(true);
    gameover->setVisible(true);
    pMenu->setScale(0);
    gameover->setScale(0);
    
    pMenu->runAction(CCScaleTo::create(0.5, 1));
    gameover->runAction(CCScaleTo::create(0.5, 1));
    
    // 保存记录
    const char *mark = scoreLabel->getString();
    int i = atoi(mark);
    int j = CCUserDefault::sharedUserDefault()->getIntegerForKey("best-score", 0);
    if (i > j) {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("best-score", i);
        j = i;
    }
    
    char cur[10];
    memset(cur, 0, 10);
    sprintf(cur, "%d", i);
    
    char bes[10];
    memset(bes, 0, 10);
    sprintf(bes, "%d", j);
    
    current->setVisible(true);
    currentScore->setVisible(true);
    currentScore->setString(cur);
    
    best->setVisible(true);
    bestScore->setVisible(true);
    bestScore->setString(bes);
    
    current->setScale(0);
    current->setScale(0);
    best->setScale(0);
    bestScore->setScale(0);
    current->runAction(CCScaleTo::create(0.5, 1));
    currentScore->runAction(CCScaleTo::create(0.5, 1));
    best->runAction(CCScaleTo::create(0.5, 1));
    bestScore->runAction(CCScaleTo::create(0.5, 1));
    
    hero->stopAllActions();
    

}

void GameMain::resetHurt(float f)
{
    isReduce = false;
}

void GameMain::setHeroHurt()
{
    // 主角受伤，减血
    hero->stopAllActions();
    switch (blood) {
        case 3:
            blood1->setVisible(false);
            blood--;
            break;
        case 2:
            blood2->setVisible(false);
            blood--;
            break;
        case 1:
            blood3->setVisible(false);
            blood--;
            break;
        case 0:
            if (!isOver) {
                isOver = true;
                
                setOver();
                
                hero->setHeroDie();
            }
            break;
        default:
            break;
    }
    
    // 闪烁
    CCActionInterval *action = CCBlink::create(5, 10);
    hero->runAction(action);
    schedule(schedule_selector(GameMain::resetHurt), 3.0f);
    isReduce = true;
}

void GameMain::addScore()
{
    
    const char *mark = scoreLabel->getString();
    int i = atoi(mark);
    i = i + 200;
    char ch[10];
    memset(ch, 0, 10);
    sprintf(ch, "%d", i);
    
    scoreLabel->setString(ch);
    
}

void GameMain::update(float time)
{
    // 背景移动
    bg1->setPosition(ccp(bg1->getPositionX(), bg1->getPositionY() - 2));
    bg2->setPosition(ccp(bg2->getPositionX(), bg2->getPositionY() - 2));
    
    if (bg2->getPositionY() < 0) {
        int temp = bg2->getPositionY() + 480;
        bg1->setPosition(ccp(bg1->getPositionX(), temp));
    }
    
    if (bg1->getPositionY() < 0) {
        int temp = bg1->getPositionY();
        bg2->setPosition(ccp(bg2->getPositionX(), temp));
    }
    
    
    CCPoint hpos = hero->getPosition();
    // 敌人与子弹碰撞检测
    for (int i = 0; i < 4; i++) {
        GameObjEnemy *enemy = (GameObjEnemy *)enemies->objectAtIndex(i);
        CCPoint epos = enemy->getPosition();
        if (enemy->isLife) {
            for (int j = 0; j < bulltes->capacity(); j++) {
                if (((GameHeroBullet *)bulltes->objectAtIndex(j))->isVisible) {
                    if (isCollision(((GameHeroBullet *)bulltes->objectAtIndex(j))->getPosition(), epos, 5, 13, 21, 28)) {
                        enemy->setDie();
                        addScore();
                        break;
                    }
                }
            }
        }
        
        // 敌人超出屏幕外
        if (enemy->getPositionY() < 0 && enemy->isLife) {
            enemy->setOutScreen();
        }
        
        // 主角与敌人碰撞
        if (!isReduce && enemy->isLife && isCollision(hpos, epos, 21, 22.5, 21, 28)) {
            enemy->setDie();
            setHeroHurt();
        }
        
    }
    // 主角与子弹碰撞
    if (!isReduce) {
        for (int i = 0; i < enemyBulltes->capacity(); i++) {
            if (isCollision(hpos, ((GameEnemyBullet *)(enemyBulltes->objectAtIndex(i)))->getPosition(), 21, 22.5, 5, 13)) {
                setHeroHurt();
            }
        }
    }
    
}
