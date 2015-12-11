//
//  MainScene.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/27.
//
//

#include "MainScene.h"
#include "MainLayer.h"
#include "VolumeData.h"
cocos2d::Scene* MainScene::createScene(){
    // 'scene' is an autorelease object
    auto scene = cocos2d::Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    VolumeData::updateData();
    // return the scene
    return scene;
}

cocos2d::Scene* MainScene::createRankScene(){
    // 'scene' is an autorelease object
    auto scene = cocos2d::Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainLayer::create();
    layer->showRank();
    // add layer as a child to scene
    scene->addChild(layer);
    VolumeData::updateData();
    // return the scene
    return scene;
}