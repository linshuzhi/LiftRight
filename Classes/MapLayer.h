//
//  MapLayer.h
//  LeftRight
//
//  Created by LinShulong on 15/10/16.
//
//

#ifndef __LeftRight__MapLayer__
#define __LeftRight__MapLayer__

#include "cocos2d.h"

class MapData;
class MapLayer : public cocos2d::Layer
{
public:
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MapLayer);
    
    void loadData(const MapData& data);
};

#endif /* defined(__LeftRight__MapLayer__) */
