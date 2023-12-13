

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

int findH(int num, int skip) {
    // sym H
    int w = strlen(data);
    for(int i=1; i<num; ++i) {

        if(i==skip) continue;

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
            //printf("derp H %i\n", i);
            return i;
        }
    }
    return 0;
}

int findV(int num, int skip) {
    int w = strlen(data);
    for(int i=1; i<w; ++i) {

        if(i==skip) continue;

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
            //printf("derp V %i\n", i);
            return i;
        }
    }
    return 0;
}

int smudgeH(int num) {
    int w = strlen(data);

    int o = findH(num, 0);
    for(int i=0; i<num; ++i) {
        for(int j=0; j<i; ++j) {
            if(i != j) {
                int t = valsH[i] ^ valsH[j];
                int n = 0;
                for(int k=0; k<w; ++k) {
                    if(t & (1 << k))
                        n++;
                }
                if(n == 1) {
                    //printf("h herp?? %i (%i %i)\n", n, i, j);
                    int p = valsH[i];
                    valsH[i] = valsH[j];
                    int h = findH(num, o);
                    valsH[i] = p;
                    if(h) return h;
                }
            }
        }
    }

    //printf("-------------------------\n\n");
    return 0;
}

int smudgeV(int num) {
    int w = strlen(data);

    int o = findV(num, 0);
    for(int i=0; i<w; ++i) {
        for(int j=0; j<i; ++j) {
            if(i != j) {
                int t = valsV[i] ^ valsV[j];
                int n = 0;
                for(int k=0; k<num; ++k) {
                    if (t & (1 << k)) 
                        n++;
                }
                if(n == 1) {
                    //printf("v herp?? %i (%i %i)\n", n, i, j);
                    int p = valsV[i];
                    valsV[i] = valsV[j];
                    int v = findV(num, o);
                    valsV[i] = p;
                    if(v) return v;
                }
            }
        }
    }

    //printf("-------------------------\n\n");
    return 0;
}

// ok the crappy way
int smudge2(int num) {
    int w = strlen(data);

    int v = findV(num, 0);
    int h = findH(num, 0);

    for(int y=0; y<num; ++y) {
        for(int x=0; x<w; ++x) {
            int t1 = (1 << x);
            int t2 = (1 << y);
            valsH[y] ^= t1;
            valsV[x] ^= t2;

            int v2 = findV(num, v); 
            int h2 = findH(num, h);

            if(v2) {
                //printf("V2 %i\n", v2);
                return v2;
            }

            if(h2) {
                //printf("H2 %i\n", h2);
                return h2 * 100;
            }


            valsH[y] ^= t1;
            valsV[x] ^= t2;
        }
    }

    assert(0);
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

        if(!num) continue;

        
        proc(num);
        //dump(num);

        // part 1
        //got += findH(num) * 100;
        //got += findV(num);

        // could be fast, but its too quick to measure
        got += smudgeH(num) * 100;
        got += smudgeV(num);

        // simpler but maybe slower ?? - meh
        //got += smudge2(num);
    }

    printf("got %i\n", got);
	free(line);
    return 0;
}


// 28210
