//
//  MainLayer.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/26.
//
//

#include "MainLayer.h"
#include "StringResources.h"
#include "GameScene.h"
#include "AboutLayer.h"
#include "RankLayer.h"
#include "VolumeLayer.h"
#include "VolumeData.h"
#include <stdlib.h>
USING_NS_CC;

namespace  {
    const int kbgZ = 100;
}

bool MainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    const int txtHight = 2;
    /**********************/
    //play
    auto playItem = MenuItemImage::create(
                                           "button.png",
                                           "button.png",
                                           CC_CALLBACK_1(MainLayer::menuPlayCallback, this));
    playItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                origin.y + visibleSize.height / 2  + 30 + 10 + 20 + 60));
    auto playLabel = Label::create();//Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    playLabel->setString(StringResources::getInstance()->getText("MAIN_PLAY") );
    playLabel->setSystemFontSize(24);
    
    playLabel->setPosition(playItem->getContentSize().width /2 ,playItem->getContentSize().height /2+txtHight);
    // position the label on the center of the screen
    playItem->addChild(playLabel);
    
    /***************************/
    //setting
    auto settingItem = MenuItemImage::create(
                                          "button.png",
                                          "button.png",
                                          CC_CALLBACK_1(MainLayer::menuSettingCallback, this));
    settingItem->setPosition(Vec2(origin.x + visibleSize.width / 2  ,
                               origin.y + visibleSize.height / 2 + 30 + 10 ));
    auto settingLabel = Label::create();//Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    settingLabel->setString(StringResources::getInstance()->getText("MAIN_SETTING") );
    settingLabel->setSystemFontSize(24);
    
    settingLabel->setPosition(settingItem->getContentSize().width /2 ,settingItem->getContentSize().height /2+txtHight);
    // position the label on the center of the screen
    settingItem->addChild(settingLabel);

    /***************************/
    //rank
    auto rankItem = MenuItemImage::create(
                                          "button.png",
                                          "button.png",
                                          CC_CALLBACK_1(MainLayer::menuRankCallback, this));
    rankItem->setPosition(Vec2(origin.x + visibleSize.width /2 ,
                               origin.y + visibleSize.height / 2 -  (30 + 10)));
    auto rankLabel = Label::create();//Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    rankLabel->setString(StringResources::getInstance()->getText("MAIN_RANK") );
    rankLabel->setSystemFontSize(24);
    
    rankLabel->setPosition(rankItem->getContentSize().width /2 ,rankItem->getContentSize().height /2+txtHight);
    // position the label on the center of the screen
    rankItem->addChild(rankLabel);

    /***************************/
    //about
    auto aboutItem = MenuItemImage::create(
                                           "button.png",
                                           "button.png",
                                           CC_CALLBACK_1(MainLayer::menuAboutCallback, this));
    
    aboutItem->setPosition(Vec2(origin.x + visibleSize.width /2 ,
                                origin.y + visibleSize.height / 2 - (30 + 10 + 20 + 60)));
    auto aboutLabel = Label::create();//Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    aboutLabel->setString(StringResources::getInstance()->getText("MAIN_ABOUT") );
    aboutLabel->setSystemFontSize(24);
    
    aboutLabel->setPosition(aboutItem->getContentSize().width /2 ,aboutItem->getContentSize().height /2+txtHight);
    // position the label on the center of the screen
    aboutItem->addChild(aboutLabel);

    /***************************/
    // create menu, it's an autorelease object
    auto menu = Menu::create( playItem,settingItem,rankItem,aboutItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    
    auto bg = Sprite::create("main.png");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg);
    
    




    return true;
}

void MainLayer::menuAboutCallback(cocos2d::Ref* pSender){
    VolumeData::playEffect("ball_ball_collision.ogg");
    auto about = AboutLayer::create();

    this->addChild(about,kbgZ);
}

void MainLayer::menuPlayCallback(cocos2d::Ref* pSender){
    VolumeData::playEffect("ball_ball_collision.ogg");
    Director::getInstance()->replaceScene(GameScene::createScene());

}

void MainLayer::menuSettingCallback(cocos2d::Ref* pSender){
    VolumeData::playEffect("ball_ball_collision.ogg");
    auto rank = VolumeLayer::create();
    this->addChild(rank,kbgZ);
    
}

void MainLayer::menuRankCallback(cocos2d::Ref* pSender){
    VolumeData::playEffect("ball_ball_collision.ogg");
    showRank();
}

void MainLayer::showRank(){
    auto rank = RankLayer::create();
    this->addChild(rank,kbgZ);
}
