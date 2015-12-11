//
//  VolumeData.h
//  LeftRight
//
//  Created by LinShulong on 15/10/28.
//
//

#ifndef __LeftRight__VolumeData__
#define __LeftRight__VolumeData__
#include <vector>
class VolumeDataDelegate;
class VolumeData{
public:
    static void setVolumeAble(bool bAble);
    static bool getVolumeAble();
    static void updateData();
    
    
    static void addDelegate(VolumeDataDelegate* delegate);
    static void deleteDelegate(VolumeDataDelegate* delegate);
    static void playEffect(const char* filePath);
    
    static void stopBackgroundMusic();
    static void playBackgroundMusic(const char* filePath);
private:
    static std::vector<VolumeDataDelegate*> _delegates;
};

#endif /* defined(__LeftRight__VolumeData__) */
