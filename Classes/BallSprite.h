//
//  BallSprite.h
//  LeftRight
//
//  Created by LinShulong on 15/10/17.
//
//

#ifndef __LeftRight__BallSprite__
#define __LeftRight__BallSprite__

#include "cocos2d.h"


class BallSprite : public cocos2d::Layer
{
public:
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(BallSprite);
    
};


#endif /* defined(__LeftRight__BallSprite__) */
