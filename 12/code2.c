
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
    char data[256];
    int region[64];
    int numData;
    int numReg;
} Row;

Row row[1024];

void dump(Row* r) {

    printf("%s : ", r->data);
    
    printf(" \n ");
    
    for(int j=0; j<r->numReg; ++j)
        printf(" %i, ", r->region[j]);

    //printf("\n");
}


#define MEM_A 32
#define MEM_B 128

long long int lut[MEM_A * MEM_B];

void setupMem() {
    for(int i=0; i<MEM_A * MEM_B; ++i) {
        lut[i] = -1;
    }
}

void storeThing(int rng, int at, long long int val) {
    assert(rng < MEM_A);
    assert(at < MEM_B);

    int idx = rng * MEM_B + at;
    assert(lut[idx] == -1 || lut[idx] == val);
    lut[idx] = val;
}

int findThing(int rng, int at, long long int* out) {
    assert(rng < MEM_A);
    assert(at < MEM_B);
    
    int idx = rng * MEM_B + at;
    if(lut[idx] == -1) return 0;

    *out  = lut[idx];
    return 1;
}

long long int dostuff(Row* ipt, int rng, int at) {
    if(at >= ipt->numData) {
        return (rng == ipt->numReg) ? 1 : 0;
    }

    if(rng == ipt->numReg) {
        return (strchr(ipt->data + at, '#')) ? 0 : 1;
    }

    long long int r = 0;
    if(findThing(rng, at, &r ))
        return r;
    
    if(ipt->data[at] != '#') { // . or ?
        r += dostuff(ipt, rng, at + 1);
    }

    if(ipt->data[at] != '.') { // # or ?
        if(ipt->numData - at >= ipt->region[rng] &&
           ipt->data[at + ipt->region[rng]] != '#') {

            int i=0;
            for(i=0; i<ipt->region[rng]; ++i) {
                if(ipt->data[at+i] == '.') break;
            }
    
            if(i == ipt->region[rng]) {
                r += dostuff(ipt, rng + 1, at + ipt->region[rng] + 1);
            }
        }
    }

    storeThing(rng, at, r);
    return r;
}


void unfold(Row* r) {    
    r->data[r->numData++] = '?';

    for(int i=1; i<5; ++i) {
        memcpy(r->data + r->numData * i, r->data, r->numData);
        memcpy(r->region + r->numReg * i,  r->region, r->numReg * sizeof(int));
    }

    r->numReg *= 5;
    r->numData *= 5;
    r->data[--r->numData] = '\0';

    assert(r->numData == strlen(r->data));
    
    dump(r);
    printf("\n\n");
}


int main(int argc, char** argv) {
	FILE* fp = fopen("data.txt", "r");
	
    int read = 0;
	int num = 0;

    memset(row, 0, sizeof(Row) * 1024);
	while ((read = fscanf(fp, "%s %i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i",
        row[num].data, 
        &row[num].region[0],
        &row[num].region[1],
        &row[num].region[2],
        &row[num].region[3],
        &row[num].region[4],
        &row[num].region[5],
        &row[num].region[6],
        &row[num].region[7],
        &row[num].region[8],
        &row[num].region[9],
        &row[num].region[10]
    )) > 0) {
        row[num].numReg = read - 1;
        row[num].numData = strlen(row[num].data);
        unfold(row + num);
        num++;
	}


    setupMem();
    printf("num %i\n", num);

    long long int t = 0;
    long long int val2 = 0;
    for(int i=0; i<num; ++i) {
        t = dostuff(row + i, 0, 0);
        val2 += t;
        printf("val %lli %lli \n", t, val2);
        setupMem();
    }
}
