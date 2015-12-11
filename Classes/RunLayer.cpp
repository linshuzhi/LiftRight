//
//  RunLayer.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/16.
//
//

#include "RunLayer.h"
#include "MapLayer.h"
#include "MapData.h"
#include "BallSprite.h"
#include "RunDataDelegate.h"
#include "VolumeData.h"
USING_NS_CC;
namespace {
    const float kSpeedCount = 3;                    //每秒钟移动多少格
    //const int kMoveCount = 5;
    //const int kCanChange = 5;
    const int kBallOrder = 10;
    const int kButtonOrder = 20;
    const std::string kMaps[] = {"map_1.tmx","map_2.tmx","map_3.tmx","map_4.tmx","map_5.tmx","map_6.tmx","map_7.tmx","map_8.tmx","map_9.tmx","map_10.tmx"};
    const int kMapSize = 10;
    std::string getMap(){
        int id = rand() % kMapSize;
        return kMaps[id];
    }
}
RunLayer::RunLayer()
: _ballLayer(nullptr)
, _moved(0)
, _curDirection(DirectionType_NULL)
, _nextDirection(DirectionType_NULL)
, _curPoint(0,0)
, _curMapLayer(nullptr)
, _nextMapLayer(nullptr)
, _curMapData(nullptr)
, _nextMapData(nullptr)
, _moveSpeed(0)
, _moveLayer(nullptr)
, _itemSize(0,0)
, _oldMapLayer(nullptr)
, _moveOverflow(0)
, _totalMoved(0)
{
    
}


// on "init" you need to initialize your instance
bool RunLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    _moveLayer = Layer::create();
    addChild(_moveLayer);
    auto temp = Sprite::create("road.png");
    _itemSize = temp->getContentSize();
    _moveSpeed = _itemSize.width * kSpeedCount ;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _curMapLayer = MapLayer::create();
    //map->setPositionX(map->getPositionX() - visibleSize.width / 4);
    _moveLayer->addChild(_curMapLayer);
    _curMapData = new MapData(getMap());
    _curMapLayer->loadData(*_curMapData);
    int width = _curMapData->getWidth();
    int heigth = _curMapData->getHeigth();
    _curPoint = Point(width/2 - 1,0);

    
    _nextMapLayer = MapLayer::create();
    _nextMapLayer->setPositionY(_nextMapLayer->getPositionY() - _itemSize.height * heigth);
    _moveLayer->addChild(_nextMapLayer);
    _nextMapData = new MapData(getMap());
    _nextMapLayer->loadData(*_nextMapData);
    
    

    
    float startX = (visibleSize.width - _itemSize.width * width) / 2 + origin.x;
    float startY = visibleSize.height / 2 + origin.y;
    
    _ballLayer = BallSprite::create();
    _ballLayer->setPosition(startX + _curPoint.x *_itemSize.width,startY);
    _moveLayer->addChild(_ballLayer,kBallOrder);
    
    
    
    
    
    auto leftbtn = ui::Button::create("arrows_n.png","arrows_d.png");
    auto btnSize = leftbtn->getContentSize();
    leftbtn->setScale(-1);
    //leftbtn->setScale(0.5f);
    leftbtn->setPosition(Vec2(visibleSize.width/2 + origin.x - btnSize.width,origin.y + 50));
    leftbtn->addTouchEventListener(CC_CALLBACK_2(RunLayer::touchLeftEvent,this));
    addChild(leftbtn,kButtonOrder);
    
    auto rightbtn = ui::Button::create("arrows_n.png","arrows_d.png");
        //rightbtn->setScale(0.5f);
    rightbtn->setPosition(Vec2(visibleSize.width /2 + origin.x + btnSize.width,origin.y + 50));
    rightbtn->addTouchEventListener(CC_CALLBACK_2(RunLayer::touchRightEvent,this));
    addChild(rightbtn,kButtonOrder);
    
    //startPlay();
    return true;
}

void RunLayer::touchLeftEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type){
    if(ui::Widget::TouchEventType::BEGAN != type){
        return ;
    }
    //if (kMoveCount - _moveStep < kCanChange ) {
        _nextDirection = DirectionType_LEFT;
    //}
    //scheduleUpdate();
VolumeData::playEffect("hole_wood.ogg");
}


void RunLayer::touchRightEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type){
    if(ui::Widget::TouchEventType::BEGAN != type){
        return ;
    }
    //if (kMoveCount - _moveStep < kCanChange ) {
        _nextDirection = DirectionType_RIGHT;
    //}
    VolumeData::playEffect("hole_wood.ogg");
    //unscheduleUpdate();
}

void RunLayer::startPlay(){
    
    scheduleUpdate();
    
    _curDirection = DirectionType_NULL;
    _nextDirection = DirectionType_NULL;
    toNext();
}

void RunLayer::toNext(){
    //重新矫位
    bool bSecc = false;
    switch (_nextDirection) {
        case DirectionType_LEFT:
            bSecc = toLeft();
            break;
        case DirectionType_RIGHT:
            bSecc = toRight();
            break;
        case DirectionType_UP:
            bSecc = toUp();
            break;
        case DirectionType_DOWN:
            bSecc = toDown();
            break;
        default:
            break;
    }
    if(bSecc){
        _curDirection = _nextDirection;
        _nextDirection = DirectionType_NULL;
        return ;
    }
    
    switch (_curDirection) {
        case DirectionType_LEFT:
            if(toLeft()){
                _nextDirection = DirectionType_NULL;
            }else if(toDown()){
                _curDirection = DirectionType_DOWN;
                _nextDirection = DirectionType_NULL;
            }else if(toUp()){
                _curDirection = DirectionType_UP;
                _nextDirection = DirectionType_NULL;
            }else{
                endGame();
            }
            break;
        case DirectionType_RIGHT:
            if(toRight()){
                _nextDirection = DirectionType_NULL;
            }else if(toDown()){
                _curDirection = DirectionType_DOWN;
                _nextDirection = DirectionType_NULL;
            }else if(toUp()){
                _curDirection = DirectionType_UP;
                _nextDirection = DirectionType_NULL;
            }else{
                endGame();
            }
            break;
        case DirectionType_UP:
            if(toUp()){
                _nextDirection = DirectionType_NULL;
            }else if(toLeft()){
                _curDirection = DirectionType_LEFT;
                _nextDirection = DirectionType_NULL;
            }else if(toRight()){
                _curDirection = DirectionType_RIGHT;
                _nextDirection = DirectionType_NULL;
            }else{
                endGame();
            }
            break;
        case DirectionType_DOWN:
            if(toDown()){
                _nextDirection = DirectionType_NULL;
            }else if(rand() %2 == 0 && toRight()){
                
                _curDirection = DirectionType_RIGHT;
                _nextDirection = DirectionType_NULL;

            }
            else if(toLeft()){
                _curDirection = DirectionType_LEFT;
                _nextDirection = DirectionType_NULL;
            }else if(toRight()){
                _curDirection = DirectionType_RIGHT;
                _nextDirection = DirectionType_NULL;
            }else{
                endGame();
            }
            break;
        default:
            if(toDown()){
                _curDirection = DirectionType_DOWN;
                _nextDirection = DirectionType_NULL;
            }else if(toLeft()){
                _curDirection = DirectionType_LEFT;
                _nextDirection = DirectionType_NULL;
            }else if(toRight()){
                _curDirection = DirectionType_RIGHT;
                _nextDirection = DirectionType_NULL;
            }else{
                endGame();
            }

            break;
    }
}
void RunLayer::toEndGame(){
    unscheduleUpdate();
}
void RunLayer::endGame(){
    unscheduleUpdate();
    for (RunDataDelegate* delegate :_delegates) {
        delegate->gameEnd();
    }
    
    auto explosion = ParticleExplosion::create();
    explosion->setTexture(Director::getInstance()->getTextureCache()->addImage("ball.png"));
    explosion->setPosition(_ballLayer->getPosition());
    _ballLayer->setVisible(false);
    
    explosion->setTotalParticles(900);
    explosion->setEmissionRate(900);
    explosion->setLife(0.5f);
    explosion->setLifeVar(0);
    explosion->setStartColor(Color4F(0,0,0,255));
    explosion->setStartColorVar(Color4F(0,0,0,0));
    explosion->setEndColor(Color4F(0,0,0,0));
    explosion->setEndColorVar(Color4F(0,0,0,0));
    _moveLayer->addChild(explosion,100);
    VolumeData::playEffect("explosion.ogg");
    
}

bool RunLayer::toLeft(){
    if(_curDirection == DirectionType_RIGHT){
        return false;
    }
    int x = _curPoint.x-1;
    if (x < 0) {
        return false;
    }
    if (_curMapData->getItemData(x, _curPoint.y) != 0) {
        _curPoint.x = x;
        return true;
    }
    return false;
    
}

bool RunLayer::toRight(){
    if(_curDirection == DirectionType_LEFT){
        return false;
    }
    int x = _curPoint.x+1;
    if (x >= _curMapData->getWidth()) {
        return false;
    }
    if (_curMapData->getItemData(x, _curPoint.y) != 0) {
        _curPoint.x = x;
        return true;
    }
    return false;
}

bool RunLayer::toUp(){
    
    if(_curDirection == DirectionType_DOWN){
        return false;
    }
    int y = _curPoint.y-1;
    if (y < 0) {
        return false;
    }
    if (_curMapData->getItemData(_curPoint.x, y) != 0) {
        _curPoint.y = y;
        return true;
    }
    return false;
}

bool RunLayer::toDown(){
    if(_curDirection == DirectionType_UP){
        return false;
    }
    int y = _curPoint.y+1;
    if (y >= _curMapData->getHeigth()) {
        _curPoint.y = y;
        return true;
    }
    if (_curMapData->getItemData(_curPoint.x, y) != 0) {
        _curPoint.y = y;
        return true;
    }
    return false;
}

bool RunLayer::toNextMap(){
    float moveheight =  _itemSize.height * _curMapData->getHeigth();
    _ballLayer->setPositionY(_ballLayer->getPositionY() + moveheight);
    _moveLayer->setPositionY(_moveLayer->getPositionY() - moveheight);
    _nextMapLayer->setPositionY(_nextMapLayer->getPositionY() + moveheight);
    _curMapLayer->setPositionY(_curMapLayer->getPositionY() + moveheight);
    

    if(_oldMapLayer){
        _oldMapLayer->removeFromParent();
        _oldMapLayer = nullptr;
    }
    _nextDirection = DirectionType_NULL;
    _curPoint = Point(_curMapData->getWidth() / 2 - 1,0);
    _oldMapLayer = _curMapLayer;
    _curMapLayer = _nextMapLayer;
    
    delete _curMapData;
    _curMapData = _nextMapData;

    
    _nextMapLayer = MapLayer::create();
    _nextMapLayer->setPositionY(_nextMapLayer->getPositionY() - _itemSize.height * _curMapData->getHeigth());
    _moveLayer->addChild(_nextMapLayer);
    _nextMapData = new MapData(getMap());
    _nextMapLayer->loadData(*_nextMapData);

    _moved = 0;
    toNext();
    return true;
}

void RunLayer::update(float delta){
    float movelen = delta * _moveSpeed + _moveOverflow;
    _moveOverflow = 0;
    if (_moved + movelen >= _itemSize.width) {
        _moveOverflow = _moved + movelen - _itemSize.width;
        movelen = _itemSize.width - _moved;
    }

    switch (_curDirection) {
        case DirectionType_DOWN:
            _ballLayer->setPositionY(_ballLayer->getPositionY() - movelen);
            _moveLayer->setPositionY(_moveLayer->getPositionY() + movelen);
            break;
        case DirectionType_UP:
            _ballLayer->setPositionY(_ballLayer->getPositionY() - movelen);
            _moveLayer->setPositionY(_moveLayer->getPositionY() - movelen);
            break;
        case DirectionType_LEFT:
            _ballLayer->setPositionX(_ballLayer->getPositionX() - movelen);
            break;
        case DirectionType_RIGHT:
            _ballLayer->setPositionX(_ballLayer->getPositionX() + movelen);
            break;
        default:
            break;
    }
    _moved += movelen;
    _totalMoved += movelen;
//    for (RunDataDelegate* delegate :_delegates) {
//        delegate->updateScore(_totalMoved);
//    }
    if (_moved >= _itemSize.width){
        if (_curPoint.y >= _curMapData->getHeigth()) {
            _moved = 0;
            toNextMap();
            return;
        }
        if(_curMapData->getItemData(_curPoint.x, _curPoint.y) == 1){
            endGame();
            return;
        }
        _moved = 0;
        toNext();
        return ;
    }
    
}


void RunLayer::addDelegate(RunDataDelegate* delegate){
    _delegates.push_back(delegate);
    
}
void RunLayer::deleteDelegate(RunDataDelegate* delegate){
    for (std::vector<RunDataDelegate*>::iterator iter = _delegates.begin(); iter != _delegates.end(); iter++) {
        if (delegate == *iter) {
            _delegates.erase(iter);
            return;
        }
    }
    
}