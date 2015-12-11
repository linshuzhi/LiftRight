//
//  GameScene.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/16.
//
//

#include "GameScene.h"
#include "GameLayer.h"

cocos2d::Scene* GameScene::createScene(){
    // 'scene' is an autorelease object
    auto scene = cocos2d::Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}