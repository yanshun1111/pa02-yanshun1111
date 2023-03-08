// Spring'22
// Instructor: Diba Mirza
// Student name: Shun Yan

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>

using namespace std;

#ifndef MOVIES_H
#define MOVIES_H

struct movies{
    string name;
    double rating;
};
bool comp(movies a, movies b);
bool compR(movies a, movies b);
void sortRating(vector<movies> &space);
void sortAlphabetical(vector<movies> &space);
void printElements(vector<movies> &space);

#endif
