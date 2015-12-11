//
//  RankData.h
//  LeftRight
//
//  Created by LinShulong on 15/10/28.
//
//

#ifndef __LeftRight__RankData__
#define __LeftRight__RankData__
#include <vector>
class RankData{
public:
    static std::vector<int> getRankList();
    static void setRankList(std::vector<int>& list);
    static void addScore(int score);
};


#endif /* defined(__LeftRight__RankData__) */
