
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


long long int got = 0;
int hash(char* data) {
    int c, v = 0;
    while((c = *data++)) {
        v += c;
        v *= 17;
        v %= 256;
    }
    return v;
}

char buf[128] = {0};
int main(int argc, char** argv) {
    FILE* fp = fopen("data.txt", "r");

    printf("HASH = %i\n", hash("HASH"));

    while(!feof(fp)) {
        char c;
        int num = 0;
        memset(buf, 0, 16);
        while((c = fgetc(fp)) != ',' && !feof(fp)) buf[num++] = c;
        if(feof(fp)) buf[num-1] = 0; 
        int i = hash(buf);
        printf("%s %i\n", buf, i);
        got += i;
    }
    printf("got %lli\n", got);
    return 0;
}
