//
//  VolumeLayer.h
//  LeftRight
//
//  Created by LinShulong on 15/10/28.
//
//

#ifndef __LeftRight__VolumeLayer__
#define __LeftRight__VolumeLayer__

#include "cocos2d.h"
#include "VolumeDataDelegate.h"
class VolumeLayer : public cocos2d::Layer , VolumeDataDelegate
{
public:
    VolumeLayer();
    ~VolumeLayer();
    virtual bool init();
    void menuCallback(cocos2d::Ref* pSender);
    void menuDisableCallback(cocos2d::Ref* pSender);
    void menuAbleCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(VolumeLayer);
    void updateData();
private:
    cocos2d::MenuItemImage* _disableItem;
    cocos2d::MenuItemImage* _ableItem;
};

#endif /* defined(__LeftRight__VolumeLayer__) */
