#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {char name[4]; char left[4]; char right[4]; } Node;

char dirs[1024];
Node nodes[1024];
int num = 0;

int findNode(char* name) {
    // yeah yeah a tree blah, this will do
    for(int i=0; i<num; ++i) {
        if(memcmp(name, nodes[i].name, 3) == 0) {
            return i;
        }
    }
    return -1;
}


int wander(char* d, int n) {
    char* go;
    int i, s = strlen(d);
    i = 0;
    do {
        go = d[i % s] == 'L' ? nodes[n].left : nodes[n].right;
        n = findNode(go);
        i++;
    } while( memcmp(go, "ZZZ", 3) != 0);
    return i;
}

int main(int argc, char** argv ) {
    memset(dirs, 0, 1024);
    memset(nodes, 0, 1024 * sizeof(Node));

    FILE* fp = fopen("data.txt", "r");
    fscanf(fp, "%s", dirs);
    fscanf(fp, "\n\n");

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

    printf("dirs %s\n", dirs);
    for(int i=0; i<num; ++i) {
        printf("node %s = (%s | %s)\n", 
                nodes[i].name, nodes[i].left, nodes[i].right);
    }

    int n = findNode("AAA");
    int v = wander(dirs, n);
    printf("got %i\n", v);

    return 0;
}

// 21251