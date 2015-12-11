//
//  RankLayer.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/27.
//
//

#include "RankLayer.h"
#include "StringResources.h"
#include "RankData.h"
USING_NS_CC;



bool RankLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /***************************/
    //about
    auto closeItem = MenuItemImage::create(
                                           "back.png",
                                           "back.png",
                                           CC_CALLBACK_1(RankLayer::menuCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + closeItem->getContentSize().width / 3 ,
                                origin.y + visibleSize.height - closeItem->getContentSize().height / 3));
    closeItem->setScale(0.5f);
    /***************************/
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    auto bg = Sprite::create("rank.jpg");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg);
    
    auto aboutLabel = Label::create();//Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    aboutLabel->setString(StringResources::getInstance()->getText("RANK_LIST") );
    aboutLabel->setSystemFontSize(24);
    
    aboutLabel->setPosition(bg->getContentSize().width /2 ,bg->getContentSize().height /2 + 50);
    // position the label on the center of the screen
    bg->addChild(aboutLabel);
    
    
    auto rankList = RankData::getRankList();
    
    for(int i = 0;i<rankList.size() && i < 5 ;i++){
        auto rankLabel = Label::create();
        rankLabel->setString(StringUtils::format("%d",rankList[i]));
        rankLabel->setSystemFontSize(24);
        
        rankLabel->setPosition(bg->getContentSize().width /2 ,bg->getContentSize().height /2 - i * 47);
        bg->addChild(rankLabel);

    }
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event) { return true; };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void RankLayer::menuCallback(cocos2d::Ref* pSender){
    removeFromParent();
}