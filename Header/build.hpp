// build.hpp
// Author: Tailon Russell
// Date: 11/9/2020.
// Purpose: The header file for the build function
//    and it's workhorse function

#ifndef HOMEWORK2_BUILD_H
#define HOMEWORK2_BUILD_H

#include <vector>
using Bridge = std::vector<int>;
using Bridges = std::vector<Bridge>;
int build(int w, int e, const Bridges &bridges);
int buildWorker(int w, int e, const Bridges &bridges);
#endif //HOMEWORK2_BUILD_H
