
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define W 4096
#define H 4096

char points[W * H];

typedef struct {
	int x, y;
	int ex, ey;
} Galaxy;

Galaxy galaxies[W];

#define max(a,b) (a>b) ? a : b;
#define min(b,a) (a<b) ? a : b;


int main(int argc, char** argv) {
	FILE* fp = fopen("data.txt", "r");
	int read = 0;
	size_t len = 0;
	char* line = NULL;

	int exp = 0;
	int num = 0;
	memset(points, '.', W * H);
	while ((read = getline(&line, &len, fp)) != -1) {
		if(read == 1) break;

		exp = 1;
		for(int i=0; i<read - 1; ++i) {
			points[num * W + i] = line[i];
			if(line[i] == '#') {
				exp = 0;
			}
		}

		num++;
		if(exp) {
			memset(points + num * W, 'A', W);
			num++;
		}
	}


	// expand h
	for(int x=0; x<num; ++x) {
		exp = 1;
		for(int y=0; y<num; ++y) {
			if(points[y * W + x] == '#') exp = 0;
		}
		
		if(exp) {
			for(int y=0; y<num; ++y) {
				memmove(points + y * W + x + 1, 
						points + y * W + x, 
						W - x - 1);
				points[y * W + x] = 'A';
			}	
			num++;
			x++;
		}
	}
	
	// note galaxies
	int numG = 0;
	for(int y=0; y<num; ++y) {
		for(int x=0; x<num; ++x) {
			printf("%c ", points[y * W + x]);
			if(points[y * W + x] == '#') {
				galaxies[numG++] = (Galaxy){.x = x, .y = y};
			}
		}
		printf("\n");
	}



	printf("\n");
	for(int i=0; i<numG; ++i) {
		printf("G %i : %i %i\n", i, galaxies[i].x, galaxies[i].y);
	}

	// work out distance
	printf("got %i g\n", numG);
	int numP = 0;
	long long int val = 0;
	for(int i=0; i<numG; ++i) {
		for(int j=i; j<numG; ++j) {
			if(i==j) continue;

			numP++;

			long long int maxX = max(galaxies[j].x, galaxies[i].x);	
			long long int maxY = max(galaxies[j].y, galaxies[i].y);
			long long int minX = min(galaxies[j].x, galaxies[i].x);	
			long long int minY = min(galaxies[j].y, galaxies[i].y);

			long long int expX = 0;
			for(int k=minX; k<maxX; ++k) {
				if( points[minY * W + k] == 'A') {
					expX++;
				}
			}

			long long int expY = 0;
			for(int k=minY; k<maxY; ++k) {
				if( points[k * W + minX] == 'A') {
					expY++;
				}
			}

			// add in expansion for part 2
			maxX += expX * (1000000 - 2);
			maxY += expY * (1000000 - 2);

			val += 
				(maxX - minX) + (maxY - minY);

			// part one answer ....
			// val += 
			//	abs((galaxies[j].x - galaxies[i].x))
			//	 + 
			//	abs((galaxies[j].y - galaxies[i].y));

		}
	}

	printf("got %lli  (%i)\n", val, numP);
	free(line);
}


