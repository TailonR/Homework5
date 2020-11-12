// build.cpp
// Author: Tailon Russell
// Date: 11/9/2020.
// Purpose: The source file for the build function
//    and various other helper functions

#include <iostream>
#include <algorithm>
#include "../Header/build.hpp"

int build(int w, int e, const Bridges &bridges) {
    return buildWorker(w,e,bridges);
}
int buildWorker(int w, int e, const Bridges &bridges) {

    if(bridges.empty())
        return 0;
    std::vector<std::vector<int>> results(w+1, std::vector<int>(e+1));

    for (int windex = 0; windex < w; windex++) {
        for(int eindex = 0; eindex < e; eindex++) {
            auto bridgeijIndices = findBridge(windex, eindex, bridges);
            for(auto bridgeij: bridgeijIndices) {
                if (windex == 0 && eindex == 0) {
                    results[windex][eindex] = (*bridgeij)[2];
                } else if (windex == 0) {
                    if(results[windex][eindex] > (*bridgeij)[2]) continue;
                    results[windex][eindex] = std::max({(*bridgeij)[2], 0, results[windex][eindex - 1]});
                } else if (eindex == 0) {
                    if(results[windex][eindex] > (*bridgeij)[2]) continue;
                    results[windex][eindex] = std::max({(*bridgeij)[2], results[windex - 1][eindex], 0});

                } else {
                    if(results[windex][eindex] > (*bridgeij)[2]) continue;
                    results[windex][eindex] = std::max({(*bridgeij)[2] + results[windex - 1][eindex - 1],
                                                        results[windex - 1][eindex],
                                                        results[windex][eindex - 1]});

                }
            }

            if(bridgeijIndices.empty()){
                if (windex == 0 && eindex == 0) {
                    results[windex][eindex] = 0;
                } else if (windex == 0) {
                    results[windex][eindex] = std::max(0, results[windex][eindex-1]);

                } else if (eindex == 0) {
                    results[windex][eindex] = std::max(results[windex-1][eindex], 0);

                } else {
                    results[windex][eindex] = std::max(results[windex-1][eindex], results[windex][eindex-1]);
                }
            }
        }
    }
    return results[w-1][e-1];
}

std::vector<BridgeIter> findBridge(int windex, int eindex, const Bridges& bridges){
    std::vector<BridgeIter> temp;
    for(auto it = std::find_if(bridges.begin(), bridges.end(), [windex, eindex](auto item){
        return item[0] == windex && item[1] == eindex;
    }); it != bridges.end(); it = std::find_if(++it, bridges.end(), [windex, eindex](auto item){
        return item[0] == windex && item[1] == eindex;
    })) {
        temp.push_back(it);
    }
    return temp;
}
