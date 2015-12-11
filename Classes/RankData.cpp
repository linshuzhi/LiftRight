//
//  RankData.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/28.
//
//

#include "RankData.h"
#include "cocos2d.h"

USING_NS_CC;

namespace  {
    const char* kKeyFormat = "RANK_%d";
    const int kSize = 5;
}

std::vector<int> RankData::getRankList(){
    std::vector<int> ret;
    for (int i = 1; i <= kSize; i++) {
        auto s = StringUtils::format(kKeyFormat,i);
        int rank = UserDefault::getInstance()->getIntegerForKey(s.c_str(), 0);
        ret.push_back(rank);
    }
    
    
    return ret;
}

void RankData::setRankList(std::vector<int>& list){
    std::vector<int> ret;
    for (int i = 1; i <= kSize; i++) {
        auto s = StringUtils::format(kKeyFormat,i);
        UserDefault::getInstance()->setIntegerForKey(s.c_str(), list[i-1]);
        UserDefault::getInstance()->flush();
        
    }
}


void RankData::addScore(int score){
    std::vector<int> list = getRankList();
    for (int i = 0; i < kSize; i++) {
        if(score >= list[i]){
            for (int j = kSize - 1; j > i; j--) {
                list[j] = list[j-1];
            }
            list[i] = score;
            setRankList(list);
            return;
        }
    }
}