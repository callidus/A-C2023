
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define W 128
#define H 128
char data[W*H] = {0};
int w = 0;
int h = 0;

void dump() {
    for(int i=0; i<h; ++i) {
        printf("%s\n", data + i*W);
    }
    printf("\n");
}


int main(int argc, char** argv) {
    FILE* fp = fopen("data.txt", "r");
    while(fscanf(fp, "%s", data + (h++*W)) == 1);
    w = strlen(data);
    h--;

    printf("size w %i h %i\n", w, h);


    dump();

    int got = 0;
    int top = 0;
    for(int x=0; x<w; ++x) {
        top = 0;
        for(int y=0; y<h; ++y) {
            int idx = y * W + x;
            if(data[idx] == '#') top = y + 1;
            if(data[idx] == 'O') {
                data[idx] = '.';
                data[top * W + x] = 'O';
                got += h - top; 
                top++;
            }
        }
    }

    dump();
    printf("got %i\n", got);
}

