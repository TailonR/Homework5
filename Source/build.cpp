// build.cpp
// Author: Tailon Russell
// Date: 11/9/2020.
// Purpose: The source file for the build function
//    and it's workhorse function

#include <iostream>
#include <algorithm>
#include "../Header/build.hpp"

// int build
// given the number of west and east cities and a list of bridges
//  return the max toll to charge of bridges built following client defined requirements
// Pre: bridges needs to be a valid vector of ints
int build(int w, int e, const Bridges &bridges) {
    return buildWorker(w,e,bridges);
}

// int build
// given the number of west and east cities and a list of bridges
//  find the max toll to charge
// Pre: bridges needs to be a valid vector of ints
int buildWorker(int w, int e, const Bridges &bridges) {

    if(bridges.empty())
        return 0;
    std::vector<std::vector<int>> results(w+1, std::vector<int>(e+1));
    std::vector<std::vector<int>> tollsOfBridges(w, std::vector<int>(e));
    for(auto bridge: bridges)
        if(tollsOfBridges[bridge[0]][bridge[1]] < bridge[2])
        tollsOfBridges[bridge[0]][bridge[1]] = bridge[2];

    for (int windex = 1; windex <= w; windex++) {
        for(int eindex = 1; eindex <= e; eindex++) {
            if(tollsOfBridges[windex-1][eindex-1] > 0) {
                results[windex][eindex] = std::max({results[windex - 1][eindex - 1]+tollsOfBridges[windex-1][eindex-1],
                                                    results[windex - 1][eindex],
                                                    results[windex][eindex - 1]});
            } else {
                results[windex][eindex] = std::max(results[windex-1][eindex], results[windex][eindex-1]);
            }
        }
    }

    return results[w][e];
}
