//
//  VolumeData.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/28.
//
//

#include "VolumeData.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "VolumeDataDelegate.h"
USING_NS_CC;
using namespace CocosDenshion;





namespace  {
    const char* kEffectsKey = "EFFECTS_KEY";
    const char* kMusicKey = "MUSIC_KEY";
    const char* kAbleKey = "ABLE_KEY";
}


std::vector<VolumeDataDelegate*> VolumeData::_delegates;
void VolumeData::setVolumeAble(bool bAble){
    bool able = UserDefault::getInstance()->getBoolForKey(kAbleKey,true);
    if (bAble == able) {
        return;
    }else{
        UserDefault::getInstance()->setBoolForKey(kAbleKey, bAble);
        UserDefault::getInstance()->flush();
        updateData();
    }

}


bool VolumeData::getVolumeAble(){
    bool able = UserDefault::getInstance()->getBoolForKey(kAbleKey,true);
    return able;
}

void VolumeData::updateData(){
    bool bAble = UserDefault::getInstance()->getBoolForKey(kAbleKey,true);
    if (bAble) {
        int eff = UserDefault::getInstance()->getIntegerForKey(kEffectsKey,-1);
        if (eff != -1) {
            SimpleAudioEngine::getInstance()->setEffectsVolume(eff);
        }
        int mus = UserDefault::getInstance()->getIntegerForKey(kMusicKey,-1);
        if (mus != -1) {
            SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(mus);
        }
        
        
        
    }else{
        int eff = SimpleAudioEngine::getInstance()->getEffectsVolume();
        UserDefault::getInstance()->setIntegerForKey(kEffectsKey, eff);
        
        int mus = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
        UserDefault::getInstance()->setIntegerForKey(kMusicKey, mus);
        
        SimpleAudioEngine::getInstance()->setEffectsVolume(0);
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);
        
        
        
    }
    UserDefault::getInstance()->flush();
    
    for(VolumeDataDelegate* delegate : _delegates){
        delegate->updateData();
    }

}
void VolumeData::playEffect(const char* filePath){
    bool bAble = UserDefault::getInstance()->getBoolForKey(kAbleKey,true);
    if (!bAble) {
        return ;
    }
    SimpleAudioEngine::getInstance()->playEffect(filePath);
}
void VolumeData::stopBackgroundMusic(){
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void VolumeData::playBackgroundMusic(const char* filePath){
    bool bAble = UserDefault::getInstance()->getBoolForKey(kAbleKey,true);
    if (!bAble) {
        return ;
    }
    SimpleAudioEngine::getInstance()->playBackgroundMusic(filePath,true);
}


void VolumeData::addDelegate(VolumeDataDelegate* delegate){
    _delegates.push_back(delegate);
    
}
void VolumeData::deleteDelegate(VolumeDataDelegate* delegate){
    for (std::vector<VolumeDataDelegate*>::iterator iter = _delegates.begin(); iter != _delegates.end(); iter++) {
        if (delegate == *iter) {
            _delegates.erase(iter);
            return;
        }
    }
    
}
