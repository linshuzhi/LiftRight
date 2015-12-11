//
//  GameLayer.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/16.
//
//

#include "GameLayer.h"
#include "MapData.h"
#include <RunLayer.h>
#include "MainScene.h"
#include "StringResources.h"
#include "RankData.h"
#include "VolumeData.h"
USING_NS_CC;

GameLayer::GameLayer()
: _run1Layer(nullptr)
, _runLayer(nullptr)
, _numLabel(nullptr)
, _totalMoved(0)
{
    
}

GameLayer::~GameLayer(){
    _runLayer->deleteDelegate(this);
    _run1Layer->deleteDelegate(this);
    VolumeData::stopBackgroundMusic();
}
// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    //VolumeData::playBackgroundMusic("ball_roll_plastic.ogg");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto bg = Sprite::create("bg.jpg");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg);
    _runLayer = RunLayer::create();
    _runLayer->setPositionX(_runLayer->getPositionX() - visibleSize.width / 4);
    this->addChild(_runLayer);
    _runLayer->addDelegate(this);
    
    
    _run1Layer = RunLayer::create();
    _run1Layer->setPositionX(_run1Layer->getPositionX() + visibleSize.width / 4);
    
    this->addChild(_run1Layer);
    _run1Layer->addDelegate(this);
    
    /***************************/
    //close
    auto closeItem = MenuItemImage::create(
                                           "back.png",
                                           "back.png",
                                           CC_CALLBACK_1(GameLayer::menuCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + closeItem->getContentSize().width / 3 ,
                                origin.y + visibleSize.height - closeItem->getContentSize().height / 3));
    closeItem->setScale(0.5f);
    auto menu = Menu::create(closeItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    /***************************/
    
    auto num = Label::createWithCharMap("number_red.png", 90, 90, '0');
    num->setString("3");
    num->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(num,10);
    float scale = 0.2f;
    _numLabel = Label::createWithCharMap("number_red.png", 90, 90, '0');
    _numLabel->setScale(scale);
    _numLabel->setString("0");
    _numLabel->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - _numLabel->getContentSize().height * scale));
    addChild(_numLabel,10);

    float t = 0.6f;
    
    auto act = Sequence::create(DelayTime::create(t),
                                CallFuncN::create([num](Node* node){
                                    num->setString("2");
                                    VolumeData::playEffect("checkpoint.ogg");
                                    }),
                                DelayTime::create(t),
                                CallFuncN::create([num](Node* node){
                                    num->setString("1");
                                    VolumeData::playEffect("checkpoint.ogg");
                                    }),
                                DelayTime::create(t),
                                CallFuncN::create([this,num](Node* node){
                                    VolumeData::playEffect("checkpoint.ogg");
                                    num->removeFromParent();
                                    _run1Layer->startPlay();
                                    _runLayer->startPlay();
                                    }),
                                nullptr
                            );
    this->runAction(act);
    
    
    return true;
}

void GameLayer::menuCallback(cocos2d::Ref* pSender){
    //removeFromParent();
    auto sc = MainScene::createScene();
    Director::getInstance()->replaceScene(sc);
}

void GameLayer::updateScore(int score){
    if(score <= _totalMoved){
        return ;
    }
    _totalMoved = score;
    _numLabel->setString(StringUtils::format("%d",score));
}

void GameLayer::gameEnd(){
    _runLayer->toEndGame();
    _run1Layer->toEndGame();
    RankData::addScore(_totalMoved);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto aboutLabel = Label::create();
    aboutLabel->setString(StringResources::getInstance()->getText("GAME_OVER") );
    aboutLabel->setSystemFontSize(96);
    
    
    aboutLabel->setPosition(visibleSize.width / 2 + origin.x ,visibleSize.height / 2 + origin.y);
    // position the label on the center of the screen
    addChild(aboutLabel,100);
    aboutLabel->setScale(0.5f);
    
    
    float t = 0.6f;
    aboutLabel->runAction(ScaleTo::create(t, 1.0f));
    
    auto act = Sequence::create(
                                DelayTime::create(t*2),
                                CallFuncN::create([](Node* node){
                                    auto sc = MainScene::createRankScene();
                                    Director::getInstance()->replaceScene(sc);

                                    }),
                                nullptr);
    runAction(act);
//    float t = 0.6f;
//    auto act = Sequence::create(DelayTime::create(t),
//                                CallFuncN::create([num](Node* node){
//        num->setString("2");
//    }),
//                                DelayTime::create(t),
//                                CallFuncN::create([num](Node* node){
//        num->setString("1");
//    }),
//                                DelayTime::create(t),
//                                CallFuncN::create([this,num](Node* node){
//        num->removeFromParent();
//        _run1Layer->startPlay();
//        _runLayer->startPlay();
//    }),
//                                nullptr
//                                );
//    this->runAction(act);
}
