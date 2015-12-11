//
//  RunLayer.h
//  LeftRight
//
//  Created by LinShulong on 15/10/16.
//
//

#ifndef LeftRight_RunLayer_h
#define LeftRight_RunLayer_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include <vector>
class MapData;
class MapLayer;
class RunDataDelegate;
class RunLayer : public cocos2d::Layer
{
private:
    enum DirectionType{
        DirectionType_NULL = 0,
        DirectionType_LEFT,
        DirectionType_RIGHT,
        DirectionType_UP,
        DirectionType_DOWN
    };
public:
    RunLayer();
    virtual bool init();
    virtual void update(float delta);
    // implement the "static create()" method manually
    CREATE_FUNC(RunLayer);
    void touchLeftEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchRightEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void startPlay();
    
    void addDelegate(RunDataDelegate* delegate);
    void deleteDelegate(RunDataDelegate* delegate);
    void toEndGame();
private:
    void toNext();
    bool toLeft();
    bool toRight();
    bool toUp();
    bool toDown();
    bool toNextMap();
    void endGame();
private:
    std::vector<RunDataDelegate*> _delegates;
    cocos2d::Layer* _ballLayer;
    cocos2d::Layer* _moveLayer;
    cocos2d::Size _itemSize;
    int _totalMoved;
    float _moved;
    float _moveSpeed;
    float _moveOverflow;
    DirectionType _curDirection;
    DirectionType _nextDirection;
    cocos2d::Point _curPoint;
    MapLayer* _curMapLayer;
    MapLayer* _nextMapLayer;
    MapLayer* _oldMapLayer;
    MapData* _curMapData;
    MapData* _nextMapData;
    
};


#endif
