//
//  GameLayer.h
//  LeftRight
//
//  Created by LinShulong on 15/10/16.
//
//

#ifndef LeftRight_GameLayer_h
#define LeftRight_GameLayer_h
#include "RunDataDelegate.h"
#include "cocos2d.h"


class RunLayer;
class GameLayer : public cocos2d::Layer , RunDataDelegate
{
public:
    GameLayer();
    ~GameLayer();
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
    void menuCallback(cocos2d::Ref* pSender);
    
    virtual void updateScore(int score);
    virtual void gameEnd();
private:
    RunLayer* _runLayer;
    RunLayer* _run1Layer;
    cocos2d::Label* _numLabel;
    int _totalMoved;
};

#endif
