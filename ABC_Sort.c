/*
*
* C implementation of abc sort from:
* Codeforces Task : https://codeforces.com/problemset/problem/1674/D
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 200000

void solve(int, char*);


int main(void){

  char buffer[BUFFER_SIZE];
  int duration;
  int arraysize;

  scanf("%i", &duration);

  for(int i = 0; i < duration; i++){

    //getting the lines
    do {scanf("%i", &arraysize);} while (getchar() != '\n');
    //getting the string
    do {scanf("%[^\n]", buffer);} while (getchar() != '\n');

    solve(arraysize, buffer);

  }


  return EXIT_SUCCESS;
}

void solve(int len, char* str){

  //solving process
  //making the arrays

  int *a;

  //mallocing
  a = (int*)(malloc(len * sizeof(int)));
  //setting
  memset(a, 0, len * sizeof(int));
  //setting the content
  char* div = strtok(str, " ");
  int counter = 0;

  while(div != NULL){

    //setting a
    a[counter] = atoi(div);
    counter++;
    div = strtok(NULL, " ");
  }

  int last = -1;
  for(int i = 0; i < len-1; i++){

    int smaller = (a[i] <= a[i+1] ? a[i] : a[i+1]);
    if(smaller < last){
      printf("NO\n");
      return;
    }
    if (smaller == a[i+1]){
      a[i+1] = a[i];
    }
    last = smaller;
  }
  if(a[len-1] < last) printf("NO\n");

  printf("YES\n");

  //cleaning up
  free(a);
}
