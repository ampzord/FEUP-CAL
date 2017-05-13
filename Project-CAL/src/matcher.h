#ifndef PROJECT_CAL_SRC_MATCHER_H_
#define PROJECT_CAL_SRC_MATCHER_H_

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

void pre_kmp(std::string pattern, std::vector<int> & prefix);

int kmp(std::string text, std::string pattern);

int numStringMatching(std::string filename,std::string toSearch);

int editDistance(std::string pattern, std::string text);

float numApproximateStringMatching(std::string filename,std::string toSearch);

#endif /* PROJECT_CAL_SRC_MATCHER_H_ */
