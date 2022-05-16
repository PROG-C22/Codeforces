/*
*
* implementation of : http://codeforces.com/problemset/problem/1680/E
*
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <bitset>

#define MAX 200000

static std::bitset<2*MAX> bits;
/*
*
* bits is structured like: 0-MAX first row, MAX+1 - 2*MAX second row
*
* chip is 1, none is 0
*
*
*/
static char buffer[MAX];
static const char CHIP = '*';
static const char EMPTY = '.';

int num_chips(int);
bool get(int, int);       //getter for bits
bool set(int, int, bool); //setter for bits
int solve(int);



int main(int argc, char** argv){

  int tests;
  int n;

  //begin: get the number of tests
  std::cin.getline(buffer, MAX);
  tests = std::atoi(buffer);
  for(int i = 0; i < tests; i++){

    std::cin.getline(buffer, MAX);
    n = std::atoi(buffer);


    //getting the fields
    std::cin.getline(buffer, MAX);
    for(int i = 0; i < n; i++) (buffer[i] == CHIP ? set(0, i, 1) : set(0, i, 0));

    std::cin.getline(buffer, MAX);
    for(int i = 0; i < n; i++) (buffer[i] == CHIP ? set(1, i, 1) : set(1, i, 0));

    //solving
    int answer = solve(n);
    std::cout << answer << std::endl;


  }


  return EXIT_SUCCESS;
}

int solve(int size){

  if (num_chips(size) == 1) return 0;

  return 5;

}

int num_chips(int size){

  //gives back the amount of chips
  int back = 0;
  for(int i = 0; i < size; i++){
    if(bits[i] == 1) back++;
    if(bits[i+MAX] == 1) back++;
  }

  return back;

}

bool get(int row, int index){

  return bits[row*MAX + index];

}

bool set(int row, int index, bool value){
  bits[row*MAX + index] = value;
  return value;
}
