//
//  GameScene.h
//  MyGame
//
//  Created by 李冬 on 15/3/14.
//
//

#ifndef __MyGame__GameScene__
#define __MyGame__GameScene__

#include "cocos2d.h"
#include "GameObjEnemy.h"


using namespace cocos2d;

class GameObjHero;

class GameMain : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // 主角子弹数组
    CCArray *bulltes;
    // 敌人子弹数组
    CCArray *enemyBulltes;
    
    // 三滴血
    CCSprite *blood1;
    CCSprite *blood2;
    CCSprite *blood3;
    short blood;
    
    // 分数
    CCSprite *score;
    CCLabelTTF *scoreLabel;
    
    // 最佳分数与当前分数
    CCLabelBMFont *best;
    CCLabelBMFont *current;
    CCLabelBMFont *bestScore;
    CCLabelBMFont *currentScore;
    
    // 游戏结束
    CCSprite *gameover;
    
    // 交替的两个背景
    CCSprite *bg1;
    CCSprite *bg2;
    
    // 血量是否在减少
    bool isReduce;
    // 游戏是否结束
    bool isOver;
    
    // 游戏主角
    GameObjHero *hero;
    
    // 敌人
    CCArray *enemies;
    
    
    // 重置伤害
    void resetHurt(float f);
    
    // 释放子弹
    void releaseEnemyBullet(int x, int y);
    void releaseHeroBullet(int x, int y);
    
    // 碰撞检测
    bool isCollision(CCPoint p1, CCPoint p2, int w1, int h1, int w2, int h2);
    
    // 分数增加
    void addScore();
    
    // 主角收到伤害
    void setHeroHurt();
    
    // 设置游戏结束
    void setOver();
    
    
    void menuBackCall(CCObject *pSender);
    
    void update(float time);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameMain);
    
};

#endif /* defined(__MyGame__GameScene__) */
