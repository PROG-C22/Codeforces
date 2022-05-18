/*
*
* implementation of : http://codeforces.com/problemset/problem/1680/E
*
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <bitset>

#define DEBUG

#define MAX 200000



//structure that indicates the position of a chip
struct POS{
  int row, index;
};

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
static struct POS c1;
static struct POS c2;

int num_chips(int);       //returns the number of chips depending in the size
int num_row1(int);        //number of chips in first row
int num_row2(int);        //number of chips in second row
bool get(int, int);       //getter for bits used like : get(row, index)
bool set(int, int, bool); //setter for bits used like : set(row, index, value)
int solve(int);           //solves the problem

//for the algorithm
int fill_holes(int); // fills all holes, returns the moves
void find_leftest(int, struct POS*); //finds leftest chip and assigns it its position
void find_rightest(int, struct POS*); //finds  rightest chip and assigns it its position


#ifdef DEBUG
void print_rows(int size){
  for(int i = 0; i < size; i++){
    char p = (get(0, i) ? CHIP : EMPTY);
    std::cout << p;
  }
  std::cout << std::endl;
  for(int i = 0; i < size; i++){
    char p = (get(1, i) ? CHIP : EMPTY);
    std::cout << p;
  }
  std::cout << std::endl;
}
#endif


int main(int argc, char** argv){

  int tests;
  int n; //size of a row

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

  //checking if already won
  if (num_chips(size) == 1) return 0;

  int moves = 0;
  //filling holes
  moves += fill_holes(size);
  //setting the position
  find_leftest(size, &c1);
  find_rightest(size, &c2);

  while (num_chips(size) > 1){

    //if in row 0
    if(c1.row == 0){
      if (get(1, c1.index)){
        //gotten, now removing
        set(0, c1.index, 0);
        c1.row = 1;
      }else{
        set(0, c1.index, 0);
        set(0, c1.index+1, 1);
        c1.index++;
      }
    }
    else{
      //in row 1
      if (get(0, c1.index)){
        //gotten, now removing
        set(1, c1.index, 0);
        c1.row = 0;
      }else{
        set(1, c1.index, 0);
        set(1, c1.index+1, 1);
        c1.index++;
      }
    }

    moves++;

    if(num_chips(size) <= 1) return moves;

    //for c2

    //if in row 0
    if(c2.row == 0){
      if (get(1, c2.index)){
        //gotten, now removing
        set(0, c2.index, 0);
        c2.row = 1;
      }else{
        set(0, c2.index, 0);
        set(0, c2.index-1, 1);
        c2.index--;
      }
    }
    else{
      //in row 1
      if (get(0, c2.index)){
        //gotten, now removing
        set(1, c2.index, 0);
        c2.row = 0;
      }else{
        set(1, c2.index, 0);
        set(1, c2.index-1, 1);
        c2.index--;
      }
    }

    moves++;


  }

  return moves;

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

int num_row1(int size){

  //gives back the amount of chips
  int back = 0;
  for(int i = 0; i < size; i++){
    if(bits[i] == 1) back++;
  }

  return back;

}
int num_row2(int size){

  //gives back the amount of chips
  int back = 0;
  for(int i = 0; i < size; i++){
    if(bits[i + MAX] == 1) back++;
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

int fill_holes(int size){

  int back = 0;

  for(int i = 0; i < size-2; i++){

    if(get(0, i) && !get(0, i+1) && get(0, i+2) && get(1, i+1) && !(get(1, i) && get(1, i+2))){
      set(0, i+1, 1);
      set(1, i+1, 0);
      back++;
    }
    if(get(1, i) && !get(1, i+1) && get(1, i+2) && get(0, i+1) && !(get(0, i) && get(0, i+2))){
      set(1, i+1, 1);
      set(0, i+1, 0);
      back++;
    }

  }
  return back;
}

void find_leftest(int size, struct POS* P){

  for(int i = 0; i < size; i++){

    if (get(0, i) && !get(1, i)) {
      P->row = 0;
      P->index = i;
      break;
    }
    else if(!get(0, i) && get(1, i)){
      P->row = 1;
      P->index = i;
      break;
    }
    else if(get(0, i) && get(1, i)){

      P->row = (num_row1(size) < num_row2(size) ? 0 : 1);
      P->index = i;
      break;

    }

  }

}

void find_rightest(int size, struct POS* P){

  for(int i = size-1; i >= 0; i--){

    if (get(0, i) && !get(1, i)) {
      P->row = 0;
      P->index = i;
      break;
    }
    else if(!get(0, i) && get(1, i)){
      P->row = 1;
      P->index = i;
      break;
    }
    else if(get(0, i) && get(1, i)){

      P->row = (num_row1(size) < num_row2(size) ? 0 : 1);
      P->index = i;
      break;

    }

  }

}
