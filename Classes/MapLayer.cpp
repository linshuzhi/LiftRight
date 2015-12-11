//
//  MapLayer.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/16.
//
//

#include "MapLayer.h"

#include "tinyxml2/tinyxml2.h"
#include "MapData.h"
#include <string>
USING_NS_CC;
// on "init" you need to initialize your instance
bool MapLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    return true;
}

void MapLayer::loadData(const MapData& data){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto temp = Sprite::create("road.png");
    auto itemSize = temp->getContentSize();
    int width = data.getWidth();
    int heigth = data.getHeigth();
    
    int startX = (visibleSize.width - itemSize.width * width) / 2 + origin.x;
    int startY = visibleSize.height / 2 + origin.y;
    for(int x = 0;x < width; x++){
        for (int y = 0; y < heigth; y++) {
            int state =data.getItemData(x, y);
            std::string png = "";
            if(state == 1){
                png = "boom.png";
                
            }else if (state == 2){
                png = "road.png";
            }
            if(png != ""){
                auto sp = Sprite::create(png);
                sp->setPosition(startX + x * itemSize.width,startY - y * itemSize.height);
                addChild(sp);

            }
        }
    }
    
    

}
