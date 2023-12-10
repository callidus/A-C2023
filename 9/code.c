#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int num = 0;

typedef struct {
    int data[32];
    int count;
} Generation;

typedef struct {
    Generation gens[32];
    int numGens;
} Input;

Input input[1024];

int diff(int a, int b) {
    //int c = ( a > b) ? a - b : b - a;
    //int c = a - b;
    int c = b - a;
    return c;
}

void dump() {
    printf("---------------------\n");
    for(int i=0; i<num; ++i) {
        for(int k=0; k<input[i].numGens; ++k) {
            printf("%*s", k, "");
            for(int j=0; j<input[i].gens[k].count; ++j) {
                printf("%i ", input[i].gens[k].data[j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}


int generate(Input* ipt) {
    int ok = 1;
    int g = ipt->numGens;
    for(int j=0; j<ipt->gens[g-1].count - 1; ++j) {
        int t = ipt->gens[g].data[j] = diff(ipt->gens[g-1].data[j], 
                                            ipt->gens[g-1].data[j+1]);
        if(t != 0) {
            ok = 0;
        }
    }
    ipt->gens[g].count = ipt->gens[g-1].count - 1;
    ipt->numGens++;
    return ok;
}

int propogate(Input* ipt) {
    int v = 0;
    for(int i=ipt->numGens-1; i>0; i--) {
        Generation* g2 = ipt->gens + i - 1;
        Generation* g1 = ipt->gens + i;

        v = g2->data[g2->count] = g2->data[g2->count-1] + g1->data[g1->count - 1];
        g2->count++;
    }
    return v;
}


void readSample() {
    FILE* fp = fopen("sample.txt", "r");
    while(fscanf(fp, 
        "%i %i %i %i %i %i\n",
        &input[num].gens[0].data[0],
        &input[num].gens[0].data[1],
        &input[num].gens[0].data[2],
        &input[num].gens[0].data[3],
        &input[num].gens[0].data[4],
        &input[num].gens[0].data[5]
        ) == 6) {
            input[num].gens[0].count = 6;
            input[num].numGens = 1;
            num++;
    }
}

void readData() {
    FILE* fp = fopen("data.txt", "r");
    while(fscanf(fp, 
        "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i\n",
        &input[num].gens[0].data[0],
        &input[num].gens[0].data[1],
        &input[num].gens[0].data[2],
        &input[num].gens[0].data[3],
        &input[num].gens[0].data[4],
        &input[num].gens[0].data[5],
        &input[num].gens[0].data[6],
        &input[num].gens[0].data[7],
        &input[num].gens[0].data[8],
        &input[num].gens[0].data[9],
        &input[num].gens[0].data[10],
        &input[num].gens[0].data[11],
        &input[num].gens[0].data[12],
        &input[num].gens[0].data[13],
        &input[num].gens[0].data[14],
        &input[num].gens[0].data[15],
        &input[num].gens[0].data[16],
        &input[num].gens[0].data[17],
        &input[num].gens[0].data[18],
        &input[num].gens[0].data[19],
        &input[num].gens[0].data[20]
        ) == 21) {
            input[num].gens[0].count = 21;
            input[num].numGens = 1;
            num++;
    }
}

int main(int argc, char** argv) {
    //readSample();
    readData();
    
    

    for(int i=0; i<num; ++i) {
        while(!generate(input + i));
    }
    dump();

    int v = 0;
    for(int i=0; i<num; ++i) {
        v += propogate(input + i);
    }
    dump();
    
    printf("got %i\n", v);
    return 0;
}
