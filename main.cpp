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

// Part 1
  if (argc == 2){
        //print all the movies in ascending alphabetical order of movie names
        sortAlphabetical(storage);
        printElements(storage);
        return 0;
  }

// Part 2
  //  For each prefix, Find all movies that have that prefix and store them in an appropriate data structure
  vector<movies> bestMovies; //O(1)
  vector<string> prefixes; //O(1)
  for (int i = 2; i < argc; i++){ //O(m)
    vector<movies> preMovies; //O(1)
     for (size_t j = 0; j < storage.size(); j++){ //O(n)
        if (storage[j].name.find(argv[i]) == 0){ //O(n)
            preMovies.push_back(storage[j]); //O(k)
        }//O(kn)
     }//O(k(n^2))
     //  If no movie with that prefix exists print the following message
     if (preMovies.size() == 0){ //O(1)
        cout << "No movies found with prefix "<< argv[i] << endl << endl; //O(1)
    }//O(1)
    else{
        prefixes.push_back(argv[i]); //O(m)
        sortRating(preMovies); //O(k(log k))
        bestMovies.push_back(preMovies[0]); //O(m)
        printElements(preMovies);//O(k))
        cout << endl;//O(1)
    }//O(1+k+2m+k(log k)) = O(k(log k))
  }//O(m(1+k(n^2)+1+k(log k))) = O(mk(n^2))

  //  For each prefix, Print the highest rated movie with that prefix if it exists.
  for (size_t i = 0; i < bestMovies.size(); i++){ //O(m)
      cout << "Best movie with prefix " << prefixes[i] << " is: " << bestMovies[i].name << " with rating " << std::fixed << std::setprecision(1) << bestMovies[i].rating << endl; //O(1)
  }//O(m)
  
  return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/
/*

3a: time complexity:

each line of the code from part 2 is commented with their Big-O time complexity, with each body of code simplified at its end bracket. The four blocks of code remaining summarizes into O(1) + O (1) + O(mk(n^2)) + O(m), which simiplifies into O(mk(n^2)), with it dominating the other three in Big-O notation. Hence, the time complexity of Part 2 is O(mk(n^2)).

3b: space complexity:

the following data structures are used in the program:

vector<movies> bestMovies
size equalling or smaller than the number of prefixes, m, so space complexity is O(m)

vector<string> prefixes
size equalling or smaller than the number of prefixes, m, so space complexity is O(m)

vector<movies> preMovies
size is equalling to the number of movies begining with a designated prefix, so space complexity is O(k), but since it only exists within each for loop, the space complexity of it in the whole part 2 of the program is negligible, hence O(1)

so the space complexity of the program is O(m) O(m+k)

3c: trade-offs
I did it for both low time complexity and low space complexity. I actually started out with a program that worked but with a lot of time and space redundancy, such as a 2D-vector to store every prefix movie, or three for loops iterating over the same thing. But I was able to trim the complexity down in both directions. I think I achieved both time and space complexity, optimizing both the algorithm time and space. I combined the three for loops into one single loop with if-else blocks inside, trimmed down unnecessary .erase() statements by pushing back prefixes in the correct block of code (though it doesn't shift the Big-O runtime, it does reduce some time complexity). For space complexity, I removed my 2D vector that stored the prefix vectors, and instead built it inside a for loop that destroys the vector right after printing one vector of movies with the same prefix. I think low space complexity is harder to achieve, since the time complexity is always dominated by a O(mk(n^2)) in that double for loop, and it's pretty much useless to optimize anything else; and to achieve low space complexity, I had to change up my whole program structure by removing the 2D vector that took up a whole lot space.
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
