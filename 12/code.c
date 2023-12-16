
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char data[32];
    int region[16];
    int numData;
    int numReg;
} Row;

Row row[1024];

int stamp(char* data, int len, int loc, int num)
{
    int ok = 1;
    for(int i=0; i<num; ++i) {
        if( loc + i >= len || data[loc + i] == '.' ) {
            ok = 0;
            break;
        }
    }

    ok = ok && loc + num <= len && data[loc + num] != '#';

    if(ok) {
        for(int i=0; i<loc; ++i) {
            if(data[i] == '?') data[i] = '.';
        }

        for(int i=0; i<num; ++i) {
            data[loc + i] = '#';
        }
        data[loc + num] = '.';
    }

    return ok;
}

int count(char* data, int len, int loc) {
    int ret = 0;

    if(loc && data[loc - 1] == '#') return 1000;

    for(int i=0; i<(len - loc); ++i) {
        if(data[loc + i] == '#') ret++;
        else break;
    }
    return ret; 
}

void dump(Row* r) {

    printf("%s : ", r->data);
    
    printf(" : ");
    
    for(int j=0; j<r->numReg; ++j)
        printf(" %i, ", r->region[j]);

    //printf("\n");
}

int validate(Row* row) {
    int r = 0;
    for(int i=0; i<row->numData; ++i) {
        if(row->data[i] == '#' ) {
            int c = count(row->data, row->numData, i);
            //printf("derp %i %i (%i and %i)\n", c, row->region[r], r, row->numReg);
            if( c != row->region[r] ) {
                return 0;
            }
            r++;
            if(r > row->numReg) return 0;
            i += c;
        }
    }
    return 1;
}

int val = 0;
void dostuff(Row* ipt, int rng, int at) {
    Row temp;
    int meh;
    for(int i=at; i<ipt->numData; ++i) {
        memcpy(&temp, ipt, sizeof(Row));

        stamp(temp.data, temp.numData, i, ipt->region[rng]);
        meh = count(temp.data, temp.numData, i);
        if(meh == temp.region[rng]) {
            if(rng < temp.numReg - 1) {
                temp.data[i + ipt->region[rng]] = '.';
                dostuff(&temp, rng + 1, i + ipt->region[rng]);
            } else {
                if(validate(&temp)) {
                    dump(&temp);
                    printf(" -- got one %i!\n", rng);
                    val++;
                }
            }  
        }
    }
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
        num++;
	}


    for(int i=0; i<num; ++i) {
        //dump(row + i);
        dostuff(row + i, 0, 0);
        printf("\n\n");
    }
    printf("val %i\n", val);
}
