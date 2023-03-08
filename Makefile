#Makefile
CXXFLAGS = -std=c++11 -g -O0

all: runMovies

runMovies: movies.cpp main.cpp
	g++ $(CXXFLAGS) movies.cpp main.cpp -o runMovies

clean:
	rm runMovies