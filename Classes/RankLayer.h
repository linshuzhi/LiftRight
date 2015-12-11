//
//  RankLayer.h
//  LeftRight
//
//  Created by LinShulong on 15/10/27.
//
//

#ifndef __LeftRight__RankLayer__
#define __LeftRight__RankLayer__

#include "cocos2d.h"

class RankLayer : public cocos2d::Layer
{
public:
    
    virtual bool init();
    void menuCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(RankLayer);
    
};
#endif /* defined(__LeftRight__RankLayer__) */
