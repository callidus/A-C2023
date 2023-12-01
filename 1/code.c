
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
	FILE* fp = fopen("data.txt", "r");
	int read = 0;
	size_t len = 0;
	char* line = NULL;
	int got = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		if(read == 1) break;

		char v[3] = {0,0,0};
		for(int i=0; i<read; ++i) {
			if(line[i] > 47 && line[i] < 58 ){
				v[0] = v[0] ? v[0] : line[i];
				v[1] = line[i];
			}
		}
		got += atoi(v);
	}
	free(line);
	printf("got %i\n", got);
}
