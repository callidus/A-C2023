
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char label[16];
    char op;
    int box;
    int val;
} Lense; 

typedef struct {    
    Lense l[128];
    int num;
} Box;

Box box[256];

Lense hash(char* data) {
    int o, v, n, c;
    n = v = 0;

    while((c = data[n++])) {
        if(c == '-' || c == '=') break;
        v += c;
        v *= 17;
        v %= 256;
    }

    Lense l =  {.label = {0}, .op = c, .box = v, .val = atoi(data + n)};
    strncpy(l.label, data, n-1);
    return l;
}

void dumpLense(Lense* l) {
    printf("  %s %c %i (%i)\n", l->label, l->op, l->box, l->val);
}

void dumpBox(int b) {
    printf("Box %i (%i) [\n", b, box[b].num);
    for(int i=0; i<box[b].num; ++i) {
        dumpLense(box[b].l + i);
    }
    printf("]\n\n");
}

void boxSub(Lense* l) {
    Box* b = box + l->box;
    for(int i=0; i<b->num; ++i) {
        if(strcmp(b->l[i].label, l->label) == 0){
            memmove(b->l + i, 
                    b->l + i + 1, 
                    (b->num - i - 1) * sizeof(Lense));
            b->num--;
            return;
        }
    }
}

void boxAdd(Lense* l) {
    Box* b = box + l->box;
    for(int i=0; i<b->num; ++i) {
        if(strcmp(b->l[i].label, l->label) == 0){
            b->l[i] = *l;
            return;
        }
    }

    b->l[b->num++] = *l;
}


char buf[128] = {0};
long long int got = 0;
int main(int argc, char** argv) {
    FILE* fp = fopen("data.txt", "r");

    while(!feof(fp)) {
        char c;
        int num = 0;
        memset(buf, 0, 16);
        while((c = fgetc(fp)) != ',' && !feof(fp)) buf[num++] = c;
        if(feof(fp)) buf[num-1] = 0; 
        
        Lense l = hash(buf);

        if(l.op == '-') boxSub(&l);
        if(l.op == '=') boxAdd(&l);
    }

    for(int i=0; i<256; ++i) {
        for(int j=0; j<box[i].num; ++j) {
            int t = (i + 1) * (j + 1) * box[i].l[j].val;
            got += t;
        }
    }

    printf("got %lli\n", got);
    return 0;
}
