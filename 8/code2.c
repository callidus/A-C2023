#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {char name[4]; char left[4]; char right[4]; } Node;

char dirs[1024];
Node nodes[1024];
int num = 0;
long long int dirLen = 0;

typedef struct {
    int nIdx;
    int dIdx;
    long long int len;
    long long int cycles;
    int ok;
} Route;


int findNode(char* name) {
    // yeah yeah a tree blah, this will do
    for(int i=0; i<num; ++i) {
        if(memcmp(name, nodes[i].name, 3) == 0) {
            return i;
        }
    }
    return -1;
}


void step(Route* r) {
    char * go = dirs[r->dIdx] == 'L' ? nodes[r->nIdx].left : nodes[r->nIdx].right;
    r->nIdx = findNode(go);
    r->dIdx = (r->dIdx + 1) % dirLen;
    r->len++;

    if(nodes[r->nIdx].name[2] == 'Z') r->ok = 1;
    //else r->len++;
}


Route routes[1024];
int numRoutes = 0;

int main(int argc, char** argv ) {
    memset(dirs, 0, 1024);
    memset(nodes, 0, 1024 * sizeof(Node));

    FILE* fp = fopen("data.txt", "r");
    fscanf(fp, "%s", dirs);
    fscanf(fp, "\n\n");
    dirLen = strlen(dirs);

	int read = 0;
	size_t len = 0;
	char* line = NULL;
	while ((read = getline(&line, &len, fp)) != -1) {
		if(read == 1) break;

        memcpy(nodes[num].name, line, 3);
        memcpy(nodes[num].left, line + 7, 3);
        memcpy(nodes[num].right, line + 12, 3);
        num++;
    } 

    /*
    printf("dirs %s\n", dirs);
    for(int i=0; i<num; ++i) {
        printf("node %s = (%s | %s)\n", 
                nodes[i].name, nodes[i].left, nodes[i].right);
    }
    */

    for(int i=0; i<num; ++i) {
        if(nodes[i].name[2] == 'A') {
            routes[numRoutes].dIdx = 0;
            routes[numRoutes].nIdx = i;
            routes[numRoutes].len = 0;
            routes[numRoutes].ok = 0;
            numRoutes++;
        }
    }

    printf("got %i routes\n", numRoutes);

    long long int v = 0;
    int ok = 0;
    while(!ok) {
        ok = 1;
        for(int i=0; i<numRoutes; ++i) {
            if(routes[i].ok) continue;
            step(routes + i);
            ok = 0;
        }
    }

    printf("dirlen %lli\n", dirLen);
    for(int i=0; i<numRoutes; ++i) {
        long long int tt = routes[i].len % dirLen;
        long long int t = routes[i].len / dirLen;
        printf("%i len %lli (%lli and %lli) \n", i, routes[i].len, t, tt);
        routes[i].cycles = t;
    }


    ok = v = 0;
    while(!ok) {
        v++;
        ok = 1;
        for(int i=0; i<numRoutes; ++i) {
            if(v % routes[i].cycles) {
               ok = 0;
               break; 
            }
        }
    }
    printf("got %lli (%lli) step\n", v, v * dirLen);

    return 0;
}

// 21251