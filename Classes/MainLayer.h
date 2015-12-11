//
//  MainLayer.h
//  LeftRight
//
//  Created by LinShulong on 15/10/26.
//
//

#ifndef __LeftRight__MainLayer__
#define __LeftRight__MainLayer__

#include "cocos2d.h"

class MainLayer : public cocos2d::Layer
{
public:
    
    virtual bool init();
    void menuAboutCallback(cocos2d::Ref* pSender);
    void menuPlayCallback(cocos2d::Ref* pSender);
    void menuSettingCallback(cocos2d::Ref* pSender);
    void menuRankCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(MainLayer);
    void showRank();

};
#endif /* defined(__LeftRight__MainLayer__) */
