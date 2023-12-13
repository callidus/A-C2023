

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define W 128
#define H 128

char data[W * H];
unsigned int valsH[W];
unsigned int valsV[W];

void proc(int num) {
    int n = 0;
    int w = strlen(data);
    assert(w < 32);

    for(int y=0; y<num; ++y) {
        valsH[y] = 0;
        for(int x=0; x<w; ++x) {
            if(data[y * W + x] == '#')
                valsH[y] = valsH[y] | (1 << x);
        }
    }

    for(int x=0; x<w; ++x) {
        valsV[x] = 0;
        for(int y=0; y<num; ++y) {
            if(data[y * W + x] == '#')
                valsV[x] = valsV[x] | (1 << y);
        }
    }
}

int findH(int num) {
    // sym H
    int w = strlen(data);
    for(int i=1; i<num; ++i) {

        int g = 1;
        int a = i;
        int b = i - 1;
        while(a < num && b >= 0 ) {
            if(valsH[a] != valsH[b]) {
                g = 0;
                break;
            }

            a++;
            b--;
        }

        if(g) {
            printf("derp H %i\n", i);
            return i;
        }
    }
    return 0;
}

int findV(int num) {
    // sym H
    int w = strlen(data);
    for(int i=1; i<w; ++i) {

        int g = 1;
        int a = i;
        int b = i - 1;
        while(a < w && b >= 0 ) {
                        if(valsV[a] != valsV[b]) {
                g = 0;
                break;
            }

            a++;
            b--;
        }

        if(g) {
            printf("derp V %i\n", i);
            return i;
        }
    }
    return 0;
}

void dump(int num) {
    printf("num %i\n", num);
    for(int y=0; y<num; ++y) {
        printf("%s %i\n", data + y * W, valsH[y]);
    }

    int w = strlen(data);
    for(int i=0; i<w; ++i) {
        printf("%i ", valsV[i]);
    }
    printf("\n\n");
}


int main(int argc, char** argv) {
	FILE* fp = fopen("data.txt", "r");
	int read = 0;
	size_t len = 0;
	char* line = NULL;
	
    int got = 0;
    while(!feof(fp)) {
        int num = 0;
        memset(data, 0, W * H);
        while ((read = getline(&line, &len, fp)) != -1) {
            if(read == 1) break;

            memcpy(data + num * W, line, read - 1);    
            num++;
        }

        
        proc(num);
        dump(num);
        got += findH(num) * 100;
        got += findV(num);
    }

    printf("got %i\n", got);
	free(line);
    return 0;
}
