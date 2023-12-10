

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

//#define W 5
//#define H 5

#define W 140
#define H 140


typedef struct { 
    char pipe, loop;
    int nx, ny;
    int px, py; 
} Node ;

Node nodes[W * H];

int main(int argc, char** argv)  {

    FILE* fp = fopen("data.txt", "r");

    int read = 0;
	size_t len = 0;
	char* line = NULL;
	int num = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
        if(read == 1) break;
        printf("%i\n", read);

        for(int i=0; i<read - 1; ++i) {
            nodes[num * W + i].pipe = line[i];
            nodes[num * W + i].loop = 0;
            nodes[num * W + i].nx = 0;
            nodes[num * W + i].ny = 0;
            nodes[num * W + i].px = 0;
            nodes[num * W + i].py = 0;
        }
        num++;
    }

    int sx, sy;
    for(int y=0; y<H; ++y) {
        for(int x=0; x<W; ++x) {
            int idx = y * W + x;
            if(nodes[idx].pipe =='S') {
                sx = x;
                sy = y;
            }

            printf("%c ", nodes[idx].pipe);
        }
        printf("\n");
    }
    printf("\n");


    // setup start, make arbitary choice between valid exits from S
    int go = 1;
    int ax = sx;
    int ay = sy - 1;

    int at = ay * W + ax;

    nodes[at].px = sx;
    nodes[at].py = sy;

    // walk the pipe starting at S + 1 step until we get back to S 
    do
    {
        nodes[at].nx = ax;
        nodes[at].ny = ay;
        nodes[at].loop = 1;

        printf("(%i %i) %i %i > '%c'\n", 
            nodes[at].px, nodes[at].py,
            ax, ay, nodes[at].pipe);

        switch(nodes[at].pipe) {
            case '|': 
                nodes[at].ny = (nodes[at].py < ay) ? ay+1 : ay-1;
                break;

            case '-': 
                nodes[at].nx = (nodes[at].px < ax) ? ax+1 : ax-1;
                break;

            case 'L': 
                if(nodes[at].px > ax) nodes[at].ny = ay - 1;
                else nodes[at].nx = ax + 1;
                break;

            case 'J':
                if(nodes[at].px < ax) nodes[at].ny = ay - 1;
                else nodes[at].nx = ax - 1;
                break;

            case '7': 
                if(nodes[at].px < ax) nodes[at].ny = ay + 1;
                else nodes[at].nx = ax - 1;
                break;

            case 'F': 
                if(nodes[at].px > ax) nodes[at].ny = ay + 1;
                else nodes[at].nx = ax + 1;
                break;

            case '.': 
                assert(0);
                break;

            case 'S': 
                nodes[at].nx = ax;
                nodes[at].ny = ay - 1;
                go = 0;
                break;
        }

        nodes[nodes[at].ny * W + nodes[at].nx].px = ax;
        nodes[nodes[at].ny * W + nodes[at].nx].py = ay;

        ax = nodes[at].nx;
        ay = nodes[at].ny;        
        at = nodes[at].ny * W + nodes[at].nx;

    } while(go);


    // scan lines to find enclosed area, but we have to ignore counter-clockwise turns
    int val = 0;
    int sense = 0;
    for(int y=0; y<H; ++y) {
        for(int x=0; x<W; ++x) {
            int idx = y * W + x;
            if(nodes[idx].loop) {
                if(nodes[idx].pipe == 'F' || nodes[idx].pipe == '7' || nodes[idx].pipe == '|' )  {
                    sense = !sense;
                }
                printf("%c", nodes[idx].pipe);
            }
            else {
                if(sense) printf("1");
                else printf("0");

                val += sense;
            }
        }
        printf("\n");
    }

    printf("val %i\n", val);
    return 0;
}
