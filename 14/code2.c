
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define W 101
#define H 101
char data[W*H] = {0};
int w = 0;
int h = 0;
int got = 0;

typedef struct {
    char data[W*H];
} Derp;

Derp derp;

void dump(Derp* d) {
    int n = 0;
    for(int i=0; i<h; ++i) {
        for(int j=0; j<w; ++j) {
            if(d->data[i*W+j] == 'O') n++;
        }
        printf("%s\n", d->data + i*W);
    }
    printf("%i stones\n\n", n);
}


void north(Derp* d) {
    int top = 0;
    for(int x=0; x<w; ++x) {
        top = 0;
        for(int y=0; y<h; ++y) {
            int idx = y * W + x;
            if(d->data[idx] == '#') top = y + 1;
            if(d->data[idx] == 'O') {
                d->data[idx] = '.';
                d->data[top * W + x] = 'O';
                got += h - top; 
                top++;
            }
        }
    }
}

void south(Derp* d) {
    int top = 0;
    for(int x=0; x<w; ++x) {
        top = h - 1;
        for(int y=h-1; y>=0; --y) {
            int idx = y * W + x;
            if(d->data[idx] == '#') top = y - 1;
            if(d->data[idx] == 'O') {
                d->data[idx] = '.';
                d->data[top * W + x] = 'O';
                got += h - top; 
                top--;
            }
        }
    }
}

void east(Derp* d) {
    int top = 0;
    for(int y=0; y<h; ++y) {
        top = w - 1;
        for(int x=w-1; x>=0; --x) {
            int idx = y * W + x;
            if(d->data[idx] == '#') top = x - 1;
            if(d->data[idx] == 'O') {
                d->data[idx] = '.';
                d->data[y * W + top] = 'O';
                got += h - y; 
                top--;
            }
        }
    }
}

void west(Derp* d) {
    int top = 0;
    for(int y=0; y<h; ++y) {
        top = 0;
        for(int x=0; x<w; ++x) {
            int idx = y * W + x;
            if(d->data[idx] == '#') top = x + 1;
            if(d->data[idx] == 'O') {
                d->data[idx] = '.';
                d->data[y * W + top] = 'O';
                got += h - y; 
                top++;
            }
        }
    }
}


unsigned int hash(char *str, int len)
{
    unsigned int hash = 5381;
    int c;

    for(int i=0; i<len; ++i) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        c = *str++;
    }

    return hash;
}


int main(int argc, char** argv) {
    FILE* fp = fopen("data.txt", "r");
    while(fscanf(fp, "%s", data + (h++*W)) == 1);
    w = strlen(data);
    h--;

    printf("size w %i h %i\n", w, h);
    memset(&derp, 0, sizeof(Derp));

    

    int loop = 0;
    memcpy(derp.data, data, W * H);
    dump(&derp);

    // smaple
    // loop start at 3 loop phase is 7
    /*
    for(int i=0; i<3; ++i) {
        north(&derp);
        west(&derp);
        south(&derp);
        east(&derp);
        printf("%u\n", hash(derp.data, W * H));
    }


    // (1000000000 - 3) % 7 = 3
    for(int i=0; i<3; ++i) {
        north(&derp);
        west(&derp);
        south(&derp);
        east(&derp);
        printf("%u\n", hash(derp.data, W * H));
    }
    */


    // loop starts at 96 iters
    for(int i=0; i<96; ++i) {
        north(&derp);
        west(&derp);
        south(&derp);
        east(&derp);
        printf("%u\n", hash(derp.data, W * H));
    }

    // loop phase is 156 iters
    // (1000000000 - 96) % 156 = 124


    for(int i=0; i<124; ++i) {
        north(&derp);
        west(&derp);
        south(&derp);
        east(&derp);
        printf("%u\n", hash(derp.data, W * H));
    }


    got = 0;
    //dump(&derp);
    for(int y=0;y<H;++y) {
        for(int x=0;x<H;++x) {
            int idx = y * W + x;
            if(derp.data[idx] == 'O') {
                got += (h - y);
            }
        }
    }
    printf("got %i\n", got);

    
    
    
    exit(0);
}

