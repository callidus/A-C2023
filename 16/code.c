

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#define W 1024
#define H 1024

int w = 0;
int h = 0;
typedef struct {
    char val, hit, dir;
} Tile;

Tile data[W*H];

typedef enum {
   U, D, L, R 
} Dirs;

typedef struct {int x,y;} Step;
Step step[4] = {
    {.x=0,  .y=-1},
    {.x=0,  .y=1 },
    {.x=-1, .y=0 },
    {.x=1,  .y=0 },
};

void proc(int x, int y, int dir) {
    int idx = y * W + x;

    if( x < 0 || x >= w ||
        y < 0 || y >= h ||
        (data[idx].hit && data[idx].dir == dir)) {
        return;
    }

    data[idx].hit = 1;
    data[idx].dir = dir;

    switch(data[idx].val) {
        case '.': 
            proc(x+step[dir].x, y+step[dir].y, dir); 
            break;

        case '|': 
            if(dir == L || dir == R) {
                proc(x+step[U].x, y+step[U].y, U); 
                proc(x+step[D].x, y+step[D].y, D); 
            }
            else
                proc(x+step[dir].x, y+step[dir].y, dir); 
            break;

        case '-':
            if(dir == U || dir == D) {
                proc(x+step[L].x, y+step[L].y, L); 
                proc(x+step[R].x, y+step[R].y, R); 
            }
            else
                proc(x+step[dir].x, y+step[dir].y, dir); 
            break;

        case '\\': 
            switch(dir) {
                case U: proc(x+step[L].x, y+step[L].y, L); break;
                case D: proc(x+step[R].x, y+step[R].y, R); break;
                case L: proc(x+step[U].x, y+step[U].y, U); break;
                case R: proc(x+step[D].x, y+step[D].y, D); break;
            }
            break;

        case '/': 
        switch(dir) {
                case U: proc(x+step[R].x, y+step[R].y, R); break;
                case D: proc(x+step[L].x, y+step[L].y, L); break;
                case L: proc(x+step[D].x, y+step[D].y, D); break;
                case R: proc(x+step[U].x, y+step[U].y, U); break;
            }
            break;
        default: assert(0); break;
    }
}

int dump() {
    int t = 0;
    for(int y=0; y<h; ++y) {
        for(int x=0; x<w; ++x) {
            //printf("{%c %c} ", 
            //    data[y*W+x].val, 
            //    data[y*W+x].hit ? '#' : '.');

            t += data[y*W+x].hit;
            printf("%c ", data[y*W+x].hit ? '#' : '.');
        }
        printf("\n");
    }
    printf("%i\n\n", t);
    return t;
}

void reset() {
    for(int y=0; y<h; ++y) {
        for(int x=0; x<w; ++x) {
            int idx = y * W + x;
            data[idx].hit = 0;
        }
    }
}

int main(int agrv, char ** argv){

    FILE* fp = fopen("data.txt", "r");

    char str[1024] = {0};
    memset(data, 0, sizeof(Tile) * W * H);
    while(fscanf(fp,"%s", str) == 1) {
        w = strlen(str);
        for(int i=0; i<w; ++i) {
            data[h * W + i].val = str[i];
        }
        h++;
    }
    
    // part 1
    int got = 0;
    //printf("w %i h% i\n", w, h);
    //proc(0,0,R);
    //got = dump();

    
    // part 2
    for(int i=0; i<w; ++i) {
        reset();
        printf("%i %i %i\n", i, 0, D);
        proc(i,0,D);
        int t = dump();
        got = t > got ? t : got;
    }

    for(int i=0; i<w; ++i) {
        reset();
        printf("%i %i %i\n", i, h-1, U);
        proc(i,h-1,U);
        int t = dump();
        got = t > got ? t : got;
    }

    for(int i=0; i<h; ++i) {
        reset();
        printf("%i %i %i\n", 0, i, R);
        proc(0,i,R);
        int t = dump();
        got = t > got ? t : got;
    }

    for(int i=0; i<h; ++i) {
        reset();
        printf("%i %i %i\n", w-1, i, L);
        proc(w-1,i,L);
        int t = dump();
        got = t > got ? t : got;
    }
    

    printf("got %i\n", got);
    return 0;
}
