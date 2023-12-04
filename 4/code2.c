 
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int points = 0;
int numsA[64];
int numsB[64];
int a,b;

int insts[2048];

int scanNums(char* data, int* out, int* num) {
  int at, n;

  at = n = 0;
  while((out[n++] = atoi(data+at))) {
    at += 3;
  }
  *num = n - 1;
  return at;
}

int calcPoints(int id, int num) {
  int p = 0;
  for(int i=0; i<a; ++i) {
    for (int j=0; j < b; ++j) {
      if(numsA[i] == numsB[j]) { 
        printf("'%i', ", numsA[i]);
        p++;
      }
    }
  }

  for(int i=0; i<p; ++i) {
    //printf(" --- %i\n", id+i+1+1 );
    insts[id + i + 1] += num;
  }
  printf(": p %i\n", p);
  return p;
}

int main(int argc, char** argv) {
	FILE* fp = fopen("data.txt", "r");
	int read = 0;
	size_t len = 0;
	char* line = NULL;

  int idx = 0;
  int t = 0;
  int done = 0;
  memset(insts,0, sizeof(int) * 2048);
  while ((read = getline(&line, &len, fp)) != -1) {
		if(read == 1) break;

    a = b = t = 0;    
    while(line[t++] != ':'); 
    t = scanNums(line + t, numsA, &a);
    
    while(line[t++] != '|'); 
    t = scanNums(line + t, numsB, &b);

    insts[idx] += 1;
    calcPoints(idx, insts[idx]);
    idx++;
    
	}
	free(line);

  points = 0;
  t = 0;
  while(insts[t]) {
    printf("%i: %i \n", t, insts[t]);
    points += insts[t];
    t++;
    
  }
  printf("got %i\n", points);
  return 0;
}


