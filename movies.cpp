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
#include "movies.h"

using namespace std;

bool compA(movies a, movies b){
    return a.name < b.name;
}

bool compR(movies a, movies b){
    return (a.rating > b.rating) && (a.name < b.name) ;
}

void sortAlphabetical(vector<movies> &space){
    sort(space.begin(), space.end(), compA);
}

void sortRating(vector<movies> &space){
    sort(space.begin(), space.end(),compR);
}

void printElements(vector<movies> &space){
    for (int i = 0; i < space.size(); i++){
        cout << space.at(i).name << ", " << fixed << setprecision(1) << space.at(i).rating << endl;
    }
}

