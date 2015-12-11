//
//  RunDataDelegate.h
//  LeftRight
//
//  Created by LinShulong on 15/10/29.
//
//

#ifndef __LeftRight__RunDataDelegate__
#define __LeftRight__RunDataDelegate__
class RunDataDelegate{
public:
    virtual void updateScore(int score) = 0;
    virtual void gameEnd() = 0;
};

#endif /* defined(__LeftRight__RunDataDelegate__) */
