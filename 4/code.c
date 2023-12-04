
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int points = 0;
int numsA[64];
int numsB[64];
int a,b;

int scanNums(char* data, int* out, int* num) {
  int at, n;

  at = n = 0;
  while((out[n++] = atoi(data+at))) {
    at += 3;
  }
  *num = n - 1;
  return at;
}

void dump(int n, int* d) {
  for(int i=0; i<n; ++i) {
    printf("%i, ", d[i]);
  }
  printf(" | ");
}

int calcPoints() {
  int p = 0;
  for(int i=0; i<a; ++i) {
    for (int j=0; j < b; ++j) {
      if(numsA[i] == numsB[j]) { 
        printf("'%i', ", numsA[i]);
        p = (p) ? p*2 : 1;
      }
    }
  }
  printf(" %i\n", p);
  return p;
}

int main(int argc, char** argv) {
	FILE* fp = fopen("data.txt", "r");
	int read = 0;
	size_t len = 0;
	char* line = NULL;

  int t = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
		if(read == 1) break;

    a = b = t = 0;    
    while(line[t++] != ':'); 
    t = scanNums(line + t, numsA, &a);
    dump(a, numsA);
    
    while(line[t++] != '|'); 
    t = scanNums(line + t, numsB, &b);
    dump(b, numsB);


    points += calcPoints();
    
	}
	free(line);


  printf("got %i\n", points);
  return 0;
}
