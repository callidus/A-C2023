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

typedef struct {long long int x,y;} Vertex;
Vertex verts[1024];

int main(int argc, char** argv) {
    FILE* fp = fopen("data.txt", "r");
    while(fscanf(fp, "%c %i %s\n", 
        &rows[num].dir, 
        &rows[num].num, 
        rows[num].col) == 3) num++;
    
    for(int i=0; i<num; ++i) {
        rows[i].dir = atoi(rows[i].col + 7);
        rows[i].col[7] = 0;
        sscanf(rows[i].col + 2, "%x", &rows[i].num);

        printf("row %i %i\n", rows[i].dir, rows[i].num);
    }

    int x,y;
    x = y = 1;
    long long int perim = 0;
    for(int i=0; i<num; ++i) {
        switch(rows[i].dir) {
            case 0: x += rows[i].num; break;
            case 1: y += rows[i].num; break;
            case 2: x -= rows[i].num; break;
            case 3: y -= rows[i].num; break;
        }
        verts[i].x = x;
        verts[i].y = y;
        perim += rows[i].num;
    }

    for(int i=0; i<num; ++i) {
        printf("{%lli %lli}\n", verts[i].x, verts[i].y);
    }


    // shoelace theorem
    long long int area = 0;
    int j = num - 1;
    for (int i = 0; i < num; i++)
    {
        area += (verts[j].x + verts[i].x) * (verts[j].y - verts[i].y);
        j = i;  // j is previous vertex to i
    }

    area = llabs(area / 2);
    
    // and then Pick's theorem 
    area = area + perim / 2 + 1;

    printf("got %lli\n", area);
    return 0;
}
