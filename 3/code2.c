#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define IPT_P "data.txt"
#define IPT_W 140
#define IPT_H 140

//#define IPT_P "sample.txt"
//#define IPT_W 10
//#define IPT_H 10

char data[IPT_W * IPT_H];


typedef struct {int s,e,v,y;} Range;

Range readNum(int x, int y) {
  Range range = {0,0,0};
  if(x < 0 || x > IPT_W) return range;
  if(y < 0 || y > IPT_H) return range;

  int t = x;
  while(t >= 0) { // x
    int idx = y * IPT_W + t;
    if(isdigit(data[idx])) {
      range.s = t;
      t--;
    } else {
      break;
    }
  }
  
  t = x;
  while(t < IPT_W) { // x
    int idx = y * IPT_W + t;
    if(isdigit(data[idx])) {
      range.e = t;
      t++;
    } else {
      break;
    }
  }

  if(range.e) {
    int idx = y * IPT_W + range.s;
    range.v = atoi(data + idx);
    range.y = y;
  }

  //printf("range %i (%i -> %i)\n", range.v, range.s, range.e);
  //if(range.v) {
  //  printf("range %i (%i -> %i)\n", range.v, range.s, range.e);
  //}
  return range;
}

int main(int argc, char** argv) {
  FILE* fp = fopen(IPT_P, "r");
  Range range[8];
  long long int got = 0;
  
  if(fp){
    memset(data, 0, IPT_H * IPT_W);
    for(int y=0; y<IPT_H; ++y) {
     for(int x=0; x<IPT_W; ++x) {
        int idx = y * IPT_W + x;
        data[idx] = fgetc(fp);
     }
    fgetc(fp); 
   }

    for(int y=0; y<IPT_H; ++y) {
     for(int x=0; x<IPT_W; ++x) {
        int idx = y * IPT_W + x;
        char c = data[idx];
        if (c == '*') {
        //if(!isdigit(data[idx]) && data[idx] != '.') {
          range[0] = readNum(x - 1, y - 1);                    
          range[1] = readNum(x + 1, y - 1);                    
          range[2] = readNum(x - 1, y + 1);                    
          range[3] = readNum(x + 1, y + 1);
          range[4] = readNum(x - 1, y);
          range[5] = readNum(x + 1, y);
          range[6] = readNum(x, y - 1);
          range[7] = readNum(x, y + 1);

          
          for(int i=0; i<8; ++i) {
            for(int j=0; j<8; ++j) {
              if (i != j && range[j].s == range[i].s &&
                      range[j].e == range[i].e && range[j].y == range[i].y) {
                range[j].v = 0;
                range[j].s = 0;
                range[j].e = 0;
                range[j].y = 0;
              }
            }
          }

          int cnt = 0;
          int val = 1;
          for(int i=0; i<8; ++i) {
            //printf("range %i (%i -> %i)\n", range[i].v, range[i].s, range[i].e);
            //got += range[i].v;
            if(range[i].v) {
              val *= range[i].v;
              cnt++;
            }
          }
          //printf("\n");
          if(cnt == 2) {
            printf("cnt %i %i\n", cnt, val);
            got += val;
          }
        }
      } 
    }
  }
  printf("got %lli\n", got);
}
