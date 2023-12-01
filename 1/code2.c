
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int val, idx, rval, ridx;
} IndexData;


char *strrstr(const char *s, const char *m) {
    char *last = NULL;
    size_t n = strlen(m);

    while ((s = strchr(s, *m)) != NULL) {
        if (!strncmp(s, m, n))
            last = (char *)s;
        if (*s++ == '\0')
            break;
    }
    return last;
}


void findIdx(char* line, int len, IndexData* out) {
	char* t = NULL;
	const char* data[9];
	data[0] = "one";
	data[1] = "two";
	data[2] = "three",
	data[3] = "four";
	data[4] = "five";
	data[5] = "six";
	data[6] = "seven";
	data[7] = "eight";
	data[8] = "nine";

	out->idx = 10000;
	out->val = -100;

	out->ridx = -10000;
	out->rval = -100;

	for(int i=0; i<9; ++i) {
		if((t = strstr(line, data[i]))) {
			int idx = t - line;
			if(idx < out->idx){
				out->idx = idx;
				out->val = i + 1;
			}
		}

		if((t = strrstr(line, data[i]))) {
			int idx = t - line;
			if(idx > out->ridx){
				out->ridx = idx;
				out->rval = i + 1;
			}
		}
	}
}



int main(int argc, char** argv) {
	FILE* fp = fopen("data.txt", "r");
	int read = 0;
	size_t len = 0;
	char* line = NULL;
	int got = 0;

	IndexData idx;

	while ((read = getline(&line, &len, fp)) != -1) {
		if(read == 1) break;

		findIdx(line, len, &idx);
		for(int i=0; i<read; ++i) {
			if(line[i] > 47 && line[i] < 58 ){
				if(i <= idx.idx) {
					idx.idx = i;
					idx.val = line[i] - 48;
				}

				if(i >= idx.ridx) {
					idx.ridx = i;
					idx.rval = line[i] - 48;
				}

			}
		}

		got += idx.val * 10 + idx.rval;
		printf("got %i (%i) %s", got, idx.val * 10 + idx.rval, line);
	}
	free(line);
}



