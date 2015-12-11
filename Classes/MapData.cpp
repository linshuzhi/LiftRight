//
//  MapData.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/16.
//
//

#include "MapData.h"
#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"


using namespace tinyxml2;
USING_NS_CC;

MapData::MapData(const std::string& filename){
    _filename = filename;
    init();
}


int MapData::getItemData(int x, int y)const{
    CC_ASSERT(x < _width);
    CC_ASSERT(y < _heigth);
    
    
    return _datas[y*_width + x];
}

int MapData::getWidth()const{
    return _width;
}

int MapData::getHeigth()const{
    return _heigth;
}


void MapData::init(){
    
    _datas.clear();
    
    auto data = FileUtils::getInstance()->getStringFromFile(_filename);
    
    XMLDocument* myDocment = new tinyxml2::XMLDocument();
    //加载文件
    myDocment->Parse(data.c_str());
    
    tinyxml2::XMLElement* rootElement = myDocment->RootElement();
    
    
    XMLElement* layerElement = rootElement->FirstChildElement();
    
    while (layerElement) {
        
        auto  name = layerElement->Attribute("name");
        if(name == nullptr)
            break;
        std::string att = name;
        if(att == "map"){
            _width = layerElement->IntAttribute("width");
            _heigth = layerElement->IntAttribute("height");

            auto datas = layerElement->FirstChildElement();
            auto titles = datas->FirstChildElement();
            while (titles) {
                auto  gid = titles->IntAttribute("gid");
                _datas.push_back(gid);
                titles = titles->NextSiblingElement();
            }
            break;
        }
        layerElement = layerElement->NextSiblingElement();
        
    }
}