//
//  AboutLayer.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/27.
//
//

#include "AboutLayer.h"
USING_NS_CC;



bool AboutLayer::init()
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
                                           CC_CALLBACK_1(AboutLayer::menuCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + closeItem->getContentSize().width / 3 ,
                                origin.y + visibleSize.height - closeItem->getContentSize().height / 3));
    closeItem->setScale(0.5f);
    /***************************/
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    auto bg = Sprite::create("about.png");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg);
    
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event) { return true; };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void AboutLayer::menuCallback(cocos2d::Ref* pSender){
    removeFromParent();
}


