//
//  VolumeLayer.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/28.
//
//

#include "VolumeLayer.h"
#include "StringResources.h"
#include "RankData.h"
#include "VolumeData.h"
USING_NS_CC;

VolumeLayer::VolumeLayer()
: _ableItem(nullptr)
, _disableItem(nullptr)
{
    
}

VolumeLayer::~VolumeLayer(){
    VolumeData::deleteDelegate(this);
}

bool VolumeLayer::init()
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
                                           CC_CALLBACK_1(VolumeLayer::menuCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + closeItem->getContentSize().width / 3 ,
                                origin.y + visibleSize.height - closeItem->getContentSize().height / 3));
    closeItem->setScale(0.5f);
    /***************************/
    //able
    _disableItem = MenuItemImage::create(
                                             "volume_able.png",
                                             "volume_able.png",
                                             CC_CALLBACK_1(VolumeLayer::menuDisableCallback, this));
    _disableItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2));
    _disableItem->setScale(3.0f);
    /***************************/
    //disable
    _ableItem = MenuItemImage::create(
                                             "volume_disable.png",
                                             "volume_disable.png",
                                             CC_CALLBACK_1(VolumeLayer::menuAbleCallback, this));
    
    _ableItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2));

    _ableItem->setScale(3.0f);
    /***************************/
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,_disableItem,_ableItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    auto color = LayerColor::create(Color4B(133,133,133,255));
    addChild(color);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event) { return true; };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    VolumeData::addDelegate(this);
    updateData();
    return true;
}

void VolumeLayer::menuCallback(cocos2d::Ref* pSender){
    removeFromParent();
}

void VolumeLayer::menuDisableCallback(cocos2d::Ref* pSender){
    VolumeData::setVolumeAble(false);
}
void VolumeLayer::menuAbleCallback(cocos2d::Ref* pSender){
    VolumeData::setVolumeAble(true);
}

void VolumeLayer::updateData(){
    bool able = VolumeData::getVolumeAble();
    if(able){
        _disableItem->setEnabled(true);
        _disableItem->setVisible(true);
        _ableItem->setEnabled(false);
        _ableItem->setVisible(false);
    }else{
        _disableItem->setEnabled(false);
        _disableItem->setVisible(false);
        _ableItem->setEnabled(true);
        _ableItem->setVisible(true);
    }
}


