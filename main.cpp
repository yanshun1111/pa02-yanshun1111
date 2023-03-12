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

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " filename prefix1 prefix2 ... prefix n " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
  // Create an object of a STL data-structure to store all the movies
  vector<movies> storage;

  string line, movieName;
  double movieRating;
  // Read each file and store the name and rating
  while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
        movies lol = {movieName, movieRating};
        storage.push_back(lol);
  }

  movieFile.close();

  if (argc == 2){
        //print all the movies in ascending alphabetical order of movie names
        sortAlphabetical(storage);
        printElements(storage);
        return 0;
  }

  //  For each prefix, Find all movies that have that prefix and store them in an appropriate data structure
  vector<movies> bestMovies;
  vector<string> prefixes; //m
  for (int i = 2; i < argc; i++){ //m
    vector<movies> preMovies; //1
     for (size_t j = 0; j < storage.size(); j++){ //n
        if (storage[j].name.find(argv[i]) == 0){ //n
            preMovies.push_back(storage[j]); //k
        }
     }
     //n^2k
     //  If no movie with that prefix exists print the following message
     if (preMovies.size() == 0){ //1
        cout << "No movies found with prefix "<< argv[i] << endl << endl; //1
        }
    //1
    else{
        prefixes.push_back(argv[i]); //1
        sortRating(preMovies); //k(log k)
        bestMovies.push_back(preMovies[0]); //k
        printElements(preMovies);//k
        cout << endl;
    }
    //2k+k(log k)
  }
  //m+1+ k + m(n^2k+2k+k(log k)), simplify O(mn^2k + mk log k), simplify to O(mkn^2)

  //  For each prefix, Print the highest rated movie with that prefix if it exists.
  for (size_t i = 0; i < bestMovies.size(); i++){ //k
      cout << "Best movie with prefix " << prefixes[i] << " is: " << bestMovies[i].name << " with rating " << std::fixed << std::setprecision(1) << bestMovies[i].rating << endl; //1
  }
  //k
  
  return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/
/*

time complexity:
m+1+ k + m(n^2k+2k+k(log k)), simplify O(mn^2k + mk log k), simplify to O(mkn^2)

space complexity:


I did it for 
*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    if (line.length() <= 0) return false;
    string tempRating = "";

    bool flag = false;
    movieName = tempRating = "", movieRating = 0.0, flag = false;

    for (int i = 0; i < line.length(); i++){
        if(flag) tempRating += line[i];
        else if(line[i]==','&& line[0]!='"') flag = true;
        else {
            if(i==0 && line[0]=='"') continue;
            if(line[i]=='"'){ i++; flag=true; continue;}
            movieName += line[i];
        }
    }
    
    movieRating = stod(tempRating);
    return true;
}
