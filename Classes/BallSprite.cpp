//
//  BallSprite.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/17.
//
//

#include "BallSprite.h"
USING_NS_CC;
// on "init" you need to initialize your instance
bool BallSprite::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    auto ball = Sprite::create("ball.png");
    addChild(ball);
    return true;
}