#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
    char dir;
    int num;
    char col[32];
} Row;

Row rows[1024];
int num = 0;

#define W 1024
#define H 1024
char map[W*H];

void fill(int x, int y) {
    if(x < 0 || x >= W) return;
    if(y < 0 || y >= H) return;

    if(!map[y*W+x]) {
        map[y*W+x] = 1;
        fill(x+1,y);
        fill(x-1,y);
        fill(x,y-1);
        fill(x,y+1);
    }
}


int main(int argc, char** argv) {
    FILE* fp = fopen("data.txt", "r");
    while(fscanf(fp, "%c %i %s\n", 
        &rows[num].dir, 
        &rows[num].num, 
        rows[num].col) == 3) num++;

    memset(map, 0 ,W*H);
    int dx = W/2 - 5;
    int dy = H/2 - 5;

    map[dy*W+dx] = 1;
    for(int i=0 ;i<num; ++i) {
        for(int j=0; j<rows[i].num; ++j) {
            switch(rows[i].dir) {
                case 'R': dx += 1; break;
                case 'D': dy += 1; break;
                case 'L': dx -= 1; break;
                case 'U': dy -= 1; break;
            }
            assert(dx > 0 && dx < W);
            assert(dy > 0 && dy < H);
            map[dy*W+dx] = 2;
        }
    }

    int c = 0;
    fill(592, 117); // pick a point inside the shape
    for(int y=0; y<H; ++y) {
        for(int x=0; x<W; ++x) {
            printf("%i", map[y*W+x]);
            if(map[y*W+x]) ++c;
        }
        printf("\n");
    }

    printf("got %i\n", c);
    return 0;
}
