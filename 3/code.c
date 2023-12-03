#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//#define IPT_P "sample.txt"
//#define  IPT_W 10
//#define IPT_H 10

#define IPT_P "data.txt"
#define IPT_W 140
#define IPT_H 140

char data[IPT_W * IPT_H];


bool findSym(int s, int e, int y){
  int ty, x = s - 1;
  x = x < 0 ? 0 : x;
  
  ty = (y - 1 < 0) ? 0 : y - 1;
  for(int i=x ;i<e+1; ++i) {
   int idx = ty * IPT_W + i;
   if(!isdigit(data[idx]) && data[idx] != '.') return true; 
  }

  ty = y;
  for(int i=x ;i<e+1; ++i) {
   int idx = ty * IPT_W + i;
   if(!isdigit(data[idx]) && data[idx] != '.') return true; 
  }

  ty = (y + 1 < IPT_H) ? y + 1 : y;
  for(int i=x ;i<e+1; ++i) {
   int idx = ty * IPT_W + i;
   if(!isdigit(data[idx]) && data[idx] != '.') return true; 
  }
  return false;
}


int main(int argc, char** argv) {
  FILE* fp = fopen(IPT_P, "r");
  int got = 0;
  
  if(fp){
    memset(data, 0, IPT_H * IPT_W);
    for(int y=0; y<IPT_H; ++y) {
     for(int x=0; x<IPT_W; ++x) {
        int idx = y * IPT_W + x;
        data[idx] = fgetc(fp);
        printf("%c", data[idx]);
     } 
      fgetc(fp);
      printf("\n");
   }

    int val,s,e,t;

  val = s = e = t = 0;
  for(int y=0; y<IPT_H; ++y) {
    for(int x=0; x<IPT_W; ++x) {

      int idx = y * IPT_W + x;
        if(isdigit(data[idx])) {
          s = e = x;
        
      while(isdigit(data[idx])) {
        e++;
        x++;    
        idx = y * IPT_W + x;
      }

        if(findSym(s,e,y)) {
          idx = y * IPT_W + s;
          val = atoi(data+idx);
          got += val;
          t = 0;
          printf("derp %i\n", val);
        }
      }
    } 
  }
}
  printf("got %i\n", got);
}
